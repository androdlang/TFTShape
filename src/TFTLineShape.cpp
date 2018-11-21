/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#include "TFTShape.h" 
void TFTLineShape::draw(TFT_eSPI* display, int x0, int y0, int16_t color) {
  VEC2 *v=vertices;
    for(int i=0;i<numVerts;i+=2) {
      VEC2 vi=TRANSFORM(v[i]);
      VEC2 vj=TRANSFORM(v[i+1]);
      drawOptimizedLine(display,x0,y0,vi.x,vi.y,vj.x,vj.y,color);
    }
}
