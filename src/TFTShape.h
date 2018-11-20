/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards.
  created by JLA 11/2018
 ****************************************************/
#ifndef TFTSHAPE_H
#define TFTSHAPE_H
//#include <ego.h>
#include <TFT_eSPI.h>
#define min(a,b)(a<b?a:b)
#define max(a,b)(a>b?a:b)
#define DEBUG

#define CC_String(d,s,y,f,fg){d.setTextDatum(CC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,d.height()/2+y,f);}
#define CC_StringB(d,s,y,f,fg,bg){d.setTextDatum(CC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,d.height()/2+y,f);}
#define BC_String(d,s,y,f,fg){d.setTextDatum(BC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,d.height()-y,f);}
#define BC_StringB(d,s,y,f,fg,bg){d.setTextDatum(BC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,d.height()-y,f);}
#define TC_String(d,s,y,f,fg){d.setTextDatum(TC_DATUM);d.setTextColor(fg);d.drawString(s,d.width()/2,y,f);}
#define TC_StringB(d,s,y,f,fg,bg){d.setTextDatum(TC_DATUM);d.setTextColor(fg,bg);d.drawString(s,d.width()/2,y,f);}

#define TRANSFORM(a)trans(a);

struct CR{
  int16_t c;
  int16_t from=-1;
  int16_t to=-1;
  CR(int16_t color);
  CR(int16_t f,int16_t t);
  static uint16_t color565(uint8_t r, uint8_t g, uint8_t b);
  static void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
  static void RGBtoBW(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);
  static int16_t colorFromHSV(int16_t hue,float s, float v);
};

struct VEC2;
struct VEC2 {
  float x;
  float y;
  VEC2();
  VEC2(float a, float b);
  void operator*=(const VEC2& b);
  void operator+=(const VEC2& b);
  void operator-=(const VEC2& b);
  void rotate(const VEC2& b);
  VEC2 &operator=(const VEC2 &v);
};

enum SHAPETYPE { ST_POLY, ST_NGON, ST_STAR, ST_LINE, ST_GRID, ST_ARC,ST_TURTLE, ST_UNKNOWN };
enum BUFFERTYPE { BT_POINTS, BT_LINES, BT_LINESTRIP, BT_LINELOOP };

class TFTShape {
  SHAPETYPE stype;
  VEC2 pivot; 			//pivot point for scaling and rotation
  VEC2 scalefac=VEC2(1,1); 	//scale
  VEC2 offset; //relative offset to drawing position
  float rotation=0; //rotation degrees
  bool rotationFixed=false; //rotate to pivot of parent shape
  VEC2 sincos=VEC2(sin(rotation*M_PI/180),cos(rotation*M_PI/180));
  VEC2 min; //updated via calcBounds
  VEC2 dim; //updated via calcBounds
protected:
  friend class TFTShapeBuilder;
  friend class TFTLines;
  BUFFERTYPE btype;
  VEC2 *vertices=NULL;   //vertices buffer
  int numVerts;      //num of vertices
  void drawOptimizedLine(TFT_eSPI*display,int x,int y,int x0,int y0, int x1,int y1, int textcolor);
  VEC2 trans(VEC2 a);
public:
  TFTShape(std::initializer_list<VEC2> verts);
  TFTShape();
  TFTShape( VEC2 * buffer, int numVerts);
  TFTShape( TFTShape ** buffer, int shapes);
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
  void fillDraw(TFT_eSPI* display, int x0, int y0,const CR & colorOutline, CR color,int every=1);
  void fillDrawH(TFT_eSPI* display, int x0, int y0,const CR & colorOutline, CR color,int every=1);
  void fillH(TFT_eSPI* display, int x0, int y0,const CR & color,int every=1);
  void fill(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & color,int every=1);
  void fillDraw(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & colorOutline, const CR & color,int every=1);
  void fillDrawH(TFT_eSPI* display, int x0, int y0,TFTShape &, const CR & colorOutline, const CR & color,int every=1);

#ifdef DEBUG  
  void dumpVerts();
#endif
  ~TFTShape();

};
#include "TFTLinestripShape.h"
#include "TFTLineShape.h"
#include "TFTShapeBuilder.h"
#endif
