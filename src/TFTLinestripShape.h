/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#ifndef TFTLSSHAPE_H
#define TFTLSSHAPE_H

class TFTLinestripShape :public TFTShape{
  public:
  TFTLinestripShape(std::initializer_list<VEC2> verts) {
    numVerts=verts.size();
    vertices = new VEC2[numVerts];
    std::copy(verts.begin(), verts.end(), vertices);
  }
  TFTLinestripShape(VEC2*buffer,int n) {
    numVerts=n;
    vertices = new VEC2[numVerts];
    memcpy(vertices,buffer,sizeof(VEC2)*numVerts);
  }
  void addPoints(std::initializer_list<VEC2> verts) {
    VEC2 *newVerts= new VEC2[numVerts+verts.size()];
    memcpy(newVerts,vertices,sizeof(VEC2)*numVerts);
    std::copy(verts.begin(), verts.end(), &newVerts[numVerts]);
    delete[] vertices;
    vertices=newVerts;
    numVerts=numVerts+verts.size();
  }
  TFTLinestripShape() {}
  virtual void draw(TFT_eSPI* display, int x0, int y0, int16_t color);
  static VEC2 getSplinePoint(VEC2* points, int numPoints,float t, bool bLooped = false);
   
};

#endif
