/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#include "TFTShape.h" 
void TFTLinestripShape::draw(TFT_eSPI* display, int x0, int y0, int16_t color) {
  VEC2 *v=vertices;
    for(int i=0,j=1;i<numVerts-1;i++,j=(j+1)) {
      VEC2 vi=TRANSFORM(v[i]);
      VEC2 vj=TRANSFORM(v[j]);
      drawOptimizedLine(display,x0,y0,vi.x,vi.y,vj.x,vj.y,color);
    }
}

VEC2  TFTLinestripShape::getSplinePoint(VEC2* points, int numPoints,float t, bool bLooped)
  {
    
    int p0, p1, p2, p3;
    if (!bLooped)
    {
      p1 = (int)t + 1;
      p2 = p1 + 1;
      p3 = p2 + 1;
      p0 = p1 - 1;
    }
    else
    {
      p1 = (int)t;
      p2 = (p1 + 1) % numPoints;
      p3 = (p2 + 1) % numPoints;
      p0 = p1 >= 1 ? p1 - 1 : numPoints - 1;
    }

    t = t - (int)t;
  //Serial.println(t);
 // Serial.printf("%d %d %d %d ",p0,p1,p2,p3);Serial.println(t);
    float tt = t * t;
    float ttt = tt * t;

    float q1 = -ttt + 2.0f*tt - t;
    float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
    float q3 = -3.0f*ttt + 4.0f*tt + t;
    float q4 = ttt - tt;

    float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
    float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);
//Serial.printf("%d %d %d\n",(int)ttt*100,(int)tx,(int)ty);
    return{ tx, ty };
  }

