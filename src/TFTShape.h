/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#ifndef TFTSHAPE_H
#define TFTSHAPE_H


#include <TFT_eSPI.h>


#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
namespace tftshape {
 // #define min(a,b)(a<b?a:b)
 // #define max(a,b)(a>b?a:b)
}
#define DEBUG

#define CC_String(d,s,y,f,fg){d.setTextDatum(CC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,d.height()/2+y,f);}
#define CC_StringB(d,s,y,f,fg,bg){d.setTextDatum(CC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,d.height()/2+y,f);}
#define BC_String(d,s,y,f,fg){d.setTextDatum(BC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,d.height()-y,f);}
#define BC_StringB(d,s,y,f,fg,bg){d.setTextDatum(BC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,d.height()-y,f);}
#define TC_String(d,s,y,f,fg){d.setTextDatum(TC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,y,f);}
#define TC_StringB(d,s,y,f,fg,bg){d.setTextDatum(TC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,y,f);}
const uint16_t PROGMEM rgb320s1v1[] = {
0xf800,0xf820,0xf840,0xf860,0xf880,0xf8a0,0xf8c0,0xf8e0,0xf920,0xf940,0xf960,0xf980,0xf9a0,0xf9c0,0xf9e0,0xfa20,0xfa60,
0xfa80,0xfaa0,0xfac0,0xfae0,0xfb00,0xfb20,0xfb40,0xfb80,0xfba0,0xfbc0,0xfbe0,0xfc20,0xfc40,0xfc60,0xfc80,0xfcc0,0xfce0,
0xfd00,0xfd20,0xfd40,0xfd60,0xfd80,0xfda0,0xfde0,0xfe20,0xfe40,0xfe60,0xfe80,0xfea0,0xfec0,0xfee0,0xff20,0xff40,0xff60,
0xff80,0xffa0,0xffc0,0xffe0,0xffe0,0xf7e0,0xefe0,0xefe0,0xe7e0,0xe7e0,0xdfe0,0xdfe0,0xd7e0,0xcfe0,0xcfe0,0xc7e0,0xbfe0,
0xbfe0,0xb7e0,0xb7e0,0xafe0,0xa7e0,0xa7e0,0x9fe0,0x9fe0,0x97e0,0x97e0,0x8fe0,0x8fe0,0x7fe0,0x7fe0,0x77e0,0x77e0,0x6fe0,
0x6fe0,0x67e0,0x67e0,0x5fe0,0x57e0,0x57e0,0x4fe0,0x4fe0,0x47e0,0x3fe0,0x3fe0,0x37e0,0x2fe0,0x2fe0,0x27e0,0x27e0,0x1fe0,
0x1fe0,0x17e0,0x0fe0,0x0fe0,0x07e0,0x07e0,0x07e0,0x07e1,0x07e1,0x07e2,0x07e2,0x07e3,0x07e4,0x07e4,0x07e5,0x07e5,0x07e6,
0x07e6,0x07e7,0x07e8,0x07e9,0x07e9,0x07ea,0x07ea,0x07eb,0x07eb,0x07ec,0x07ed,0x07ed,0x07ee,0x07ee,0x07ef,0x07ef,0x07f0,
0x07f1,0x07f2,0x07f2,0x07f3,0x07f3,0x07f4,0x07f4,0x07f5,0x07f6,0x07f6,0x07f7,0x07f7,0x07f8,0x07f9,0x07f9,0x07fa,0x07fb,
0x07fb,0x07fc,0x07fc,0x07fd,0x07fd,0x07fe,0x07fe,0x07ff,0x07df,0x07bf,0x079f,0x077f,0x075f,0x073f,0x071f,0x06df,0x06bf,
0x069f,0x067f,0x065f,0x063f,0x05ff,0x05df,0x059f,0x057f,0x055f,0x053f,0x051f,0x04ff,0x04df,0x04bf,0x049f,0x045f,0x043f,
0x03ff,0x03df,0x03bf,0x039f,0x037f,0x033f,0x031f,0x02ff,0x02df,0x02bf,0x029f,0x027f,0x025f,0x01ff,0x01df,0x01bf,0x019f,
0x017f,0x015f,0x013f,0x011f,0x00df,0x00bf,0x009f,0x007f,0x005f,0x003f,0x001f,0x001f,0x081f,0x101f,0x101f,0x181f,0x181f,
0x201f,0x201f,0x281f,0x281f,0x301f,0x381f,0x381f,0x401f,0x481f,0x481f,0x501f,0x581f,0x581f,0x601f,0x601f,0x681f,0x681f,
0x701f,0x701f,0x781f,0x801f,0x881f,0x881f,0x901f,0x901f,0x981f,0x981f,0xa01f,0xa81f,0xa81f,0xb01f,0xb01f,0xb81f,0xb81f,
0xc01f,0xc81f,0xd01f,0xd01f,0xd81f,0xd81f,0xe01f,0xe01f,0xe81f,0xf01f,0xf01f,0xf81f,0xf81f,0xf81f,0xf81e,0xf81e,0xf81d,
0xf81c,0xf81c,0xf81b,0xf81b,0xf81a,0xf81a,0xf819,0xf819,0xf817,0xf817,0xf816,0xf816,0xf815,0xf815,0xf814,0xf814,0xf813,
0xf812,0xf812,0xf811,0xf811,0xf810,0xf80f,0xf80f,0xf80e,0xf80d,0xf80d,0xf80c,0xf80c,0xf80b,0xf80b,0xf80a,0xf809,0xf809,
0xf808,0xf807,0xf807,0xf806,0xf806,0xf805,0xf804,0xf804,0xf803,0xf803,0xf802,0xf802,0xf801,0xf801};


#define TRANSFORM(a)trans(a);

struct CR{
  uint16_t c;
  int16_t from=-1;
  int16_t to=-1;
  CR(uint16_t color);
  CR(int16_t f,int16_t t);
  static void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
  static void RGBtoBW(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
  static uint16_t colorFromHSV(int16_t hue,float s, float v);
};

struct VEC2;
struct VEC2 {
  float x;
  float y;
  VEC2();
  VEC2(float a, float b);
  VEC2(float ab);
  void operator*=(const VEC2& b);
  void operator+=(const VEC2& b);
  void operator-=(const VEC2& b);
  void rotate(const VEC2& b);
  VEC2 &operator=(const VEC2 &v);
};



class TFTShape {
 
  VEC2 pivot; 			            //pivot point for scaling and rotation
  VEC2 scalefac=VEC2(1,1); 	    //scale
  VEC2 offset;                  //relative offset of vertices
  float rotation=0;             //rotation degrees
  bool rotationFixed=false;     //if false: head to pivot of parent shape
  VEC2 sincos=VEC2(sin(rotation*M_PI/180),cos(rotation*M_PI/180)); //updated on every rotation change
protected:
  friend class TFTShapeBuilder;
  VEC2 *vertices=NULL;          //vertices buffer
  int numVerts;                 //number of vertices
  void drawOptimizedLine(TFT_eSPI*display,int x,int y,int x0,int y0, int x1,int y1, int textcolor);
  VEC2 trans(VEC2 a);           //transpose function
public:
  TFTShape(std::initializer_list<VEC2> verts);
  TFTShape();
  TFTShape( VEC2 * buffer, int numVerts);
  void setPivot(int,int);
  void setRotation(float a);
  void setRotationBy(float a);
  float getRotation();
  void setRotationFixed(bool b);
  bool isRotationFixed();
  void setScale(float sx, float sy);
  void setScale(float s);
  void setScaleBy(float s);
  VEC2 getScale();
  void setOffset(float sx, float sy);
  VEC2 getOffset();
  void reset() {setOffset(0,0);setScale(1);setRotation(0);}
  VEC2 * getPoints() {return vertices;}
  int getNumPoints() {return numVerts;} 
  TFTShape * scale(float s) {setScale(s); return this;}
  TFTShape * scaleBy(float s) {setScaleBy(s); return this;}
  TFTShape * rotate(float deg) {setRotation(deg); return  this;}
  TFTShape * rotateBy(float deg) {setRotationBy(deg); return  this;}
  TFTShape * spivot(int x,int y) {setPivot(x,y); return  this;}
  virtual void draw(TFT_eSPI* display, int x0, int y0, int16_t color);
  void draw(TFT_eSPI* display, int x0, int y0, TFTShape &, const CR & color,int every=1);
  void fill(TFT_eSPI* display, int x0, int y0, CR color,int every=1);
  void fill(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & color,int every=1);
  void fillH(TFT_eSPI* display, int x0, int y0,const CR & color,int every=1);
  void fillDraw(TFT_eSPI* display, int x0, int y0,const CR & colorOutline, CR color,int every=1);
  void fillDraw(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & colorOutline, const CR & color,int every=1);
  void fillDrawH(TFT_eSPI* display, int x0, int y0,const CR & colorOutline, CR color,int every=1);
  void fillDrawH(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & colorOutline, const CR & color,int every=1);

#ifdef DEBUG  
  void dumpVerts();
#endif
  ~TFTShape();

};
#include "TFTLinestripShape.h"
#include "TFTSplineShape.h"
#include "TFTLineShape.h"
#include "TFTShapeBuilder.h"
#include "TFTSimplexNoise.h"
#endif
