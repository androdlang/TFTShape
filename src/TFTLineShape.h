/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#ifndef TFTLINESHAPE_H
#define TFTLINESHAPE_H

class TFTLineShape :public TFTShape{
  public:
  TFTLineShape(std::initializer_list<VEC2> verts) {
    numVerts=verts.size();
    vertices = new VEC2[numVerts];
    std::copy(verts.begin(), verts.end(), vertices);
  }

  TFTLineShape() {}
  virtual void draw(TFT_eSPI* display, int x0, int y0, int16_t color);
};
#endif