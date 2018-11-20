/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards.
  created by JLA 11/2018
 ****************************************************/
#ifndef TFTLSSHAPE_H
#define TFTLSSHAPE_H
//#include "TFTShape.h"
class TFTLinestripShape :public TFTShape{
  public:
  TFTLinestripShape(std::initializer_list<VEC2> verts) {
    numVerts=verts.size();
    vertices = new VEC2[numVerts];
    std::copy(verts.begin(), verts.end(), vertices);
  }
  TFTLinestripShape() {btype=BT_LINESTRIP;}
  virtual void draw(TFT_eSPI* display, int x0, int y0, int16_t color);
  //static TFTLinestripShape buildSpline(std::initializer_list<VEC2> verts,int steps);
  //static TFTLinestripShape buildSpline(VEC2 * buffer ,int numVerts,int steps);
  //static TFTLinestripShape buildSplineLoop(VEC2 * buffer,int numVerts,int steps);
  static VEC2 getSplinePoint(VEC2* points, int numPoints,float t, bool bLooped = false);
   
};
#endif
  