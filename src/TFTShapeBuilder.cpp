/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#include "TFTShape.h"

void  TFTShapeBuilder::fillNgonVertices(VEC2 *v ,int corners, VEC2 radius) {
  float a=360/corners;
  for(int i=0;i<corners;i++) {
    float al=+a*i*M_PI/180;
    v[i].x=sin(al)*radius.x;
    v[i].y=-cos(al)*radius.y;
  }
}   

VEC2 * TFTShapeBuilder::createNgonVertices(int corners, VEC2 radius) {
    VEC2 *v = new VEC2[corners];
    fillNgonVertices(v,corners,radius);
    return v;
}

void TFTShapeBuilder::fillStarVertices(VEC2 *v ,int corners, VEC2 r1, VEC2 r2) {
    float a=360/corners;
    for(int i=0,ix=0;i<corners;i++) {
      float al=+a*i*M_PI/180;
      v[ix].x=sin(al)*r1.x;
      v[ix].y=-cos(al)*r1.y;
      ix++;
      v[ix].x=sin(al+a/2*M_PI/180)*r2.x;
      v[ix].y=-cos(al+a/2*M_PI/180)*r2.y;
      ix++;
    }
}

VEC2 * TFTShapeBuilder::createStarVertices(int corners, VEC2 r1, VEC2 r2) {
    VEC2 *v = new VEC2[corners*2];
    fillStarVertices(v,corners,r1,r2);
    return v;
}
TFTLinestripShape TFTShapeBuilder::buildNgonLinestrip(int corners, VEC2 radius) {
    TFTLinestripShape ngon= TFTLinestripShape();
    ngon.vertices=createNgonVertices(corners,radius);
    ngon.numVerts=corners;
    return ngon;
}
TFTShape TFTShapeBuilder::buildNgon(int corners, int radius) {
    TFTShape ngon= TFTShape();
    ngon.vertices=createNgonVertices(corners,VEC2(radius));
    ngon.numVerts=corners;
    return ngon;
}
TFTShape TFTShapeBuilder::buildNgon(int corners, int rw, int rh) {
    TFTShape ngon= TFTShape();
    ngon.vertices=createNgonVertices(corners,VEC2(rw,rh));
    ngon.numVerts=corners;
    return ngon;
}
TFTShape TFTShapeBuilder::buildStar(int corners, VEC2 r1, VEC2 r2) {
    TFTShape ngon= TFTShape();
    ngon.vertices=createStarVertices(corners,r1,r2);
    ngon.numVerts=corners*2;
    return ngon;
}
TFTShape TFTShapeBuilder::buildStar(int corners, int r1, int r2) {
    return buildStar(corners,VEC2(r1),VEC2(r2));
}
TFTShape TFTShapeBuilder::buildGear(int corners, int r1, int r2,float toothAngle) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=corners*4;
    VEC2 *vertices = new VEC2[ngon.numVerts];
    ngon.vertices=vertices;
    float a=360/corners;
    if(toothAngle<2.f)toothAngle=2.f;
    float a7=a/toothAngle;
    float a1=a/1;
    float a2=a/2;
    for(int i=0,ix=0;i<corners;i++) {
      float al=a*i*M_PI/180;
      float al7=a7*M_PI/180;
      float al1=a1*M_PI/180;
      float al2=a2*M_PI/180;
      vertices[ix].x=sin(al-al7)*r1;
      vertices[ix].y=-cos(al-al7)*r1;
      ix++;
      vertices[ix].x=sin(al+al7)*r1;
      vertices[ix].y=-cos(al+al7)*r1;
      ix++;
      vertices[ix].x=sin(al+al2-al7)*r2;
      vertices[ix].y=-cos(al+al2-al7)*r2;
      ix++;
      vertices[ix].x=sin(al+al2+al7)*r2;
      vertices[ix].y=-cos(al+al2+al7)*r2;
      ix++;
    }
    return ngon;
}

TFTShape TFTShapeBuilder::buildRect(int wh) {
  return buildRect(wh,wh);
}
TFTShape TFTShapeBuilder::buildRect(int w, int h) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=4;
    VEC2 *vertices = new VEC2[ngon.numVerts];
    ngon.vertices=vertices;
    ngon.vertices[0]=VEC2(-w/2,-h/2);
    ngon.vertices[1]=VEC2(w/2,-h/2);
    ngon.vertices[2]=VEC2(w/2,h/2);
    ngon.vertices[3]=VEC2(-w/2,h/2);
    return ngon;
}
TFTShape TFTShapeBuilder::buildArc(int segments, int radius,float start, float spanAngle) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=segments+1;
    ngon.vertices = new VEC2[ngon.numVerts];
    float a=spanAngle/segments;
    for(int i=0;i<=segments;i++) {
      float al=start*M_PI/180+ a*i*M_PI/180;
      ngon.vertices[i].x=sin(al)*radius;
      ngon.vertices[i].y=-cos(al)*radius;
    }
    return ngon;
}
TFTShape TFTShapeBuilder::buildWedge(int segments, int radius,float start, float spanAngle) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=segments+2;
    ngon.vertices = new VEC2[ngon.numVerts];
    float a=spanAngle/segments;
    for(int i=0;i<=segments;i++) {
      float al=start*M_PI/180+ a*i*M_PI/180;
      ngon.vertices[i].x=sin(al)*radius;
      ngon.vertices[i].y=-cos(al)*radius;
    }
    ngon.vertices[ngon.numVerts-1].x=0;
    ngon.vertices[ngon.numVerts-1].y=0;
    return ngon;
}
TFTShape TFTShapeBuilder::buildAnnularWedge(int segments, int r1,int r2,float start, float spanAngle) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=2*segments+2;
    ngon.vertices = new VEC2[ngon.numVerts];
    float a=spanAngle/segments;
    int ix=0;
    for(int i=0;i<=segments;i++) {
      float al=start*M_PI/180+ a*i*M_PI/180;
      ngon.vertices[ix].x=sin(al)*r1;
      ngon.vertices[ix].y=-cos(al)*r1;
      ix++;
    }
    for(int i=segments;i>=0;i--) {
      float al=start*M_PI/180+ a*i*M_PI/180;
      ngon.vertices[ix].x=sin(al)*r2;
      ngon.vertices[ix].y=-cos(al)*r2;
      ix++;
    }
    //ngon.vertices[ngon.numVerts-1].x=0;
    //ngon.vertices[ngon.numVerts-1].y=0;
    return ngon;
}

TFTShape TFTShapeBuilder::buildGrid(int columns, int rows,int w, int h, bool alternate) {
  TFTShape grid= TFTShape();
  grid.numVerts=rows*columns;
  VEC2 *vertices = new VEC2[grid.numVerts]; //max possible verts
  grid.vertices=vertices;
  float w2=w/2.; float h2=h/2.;
  double xstep= 1.0*w/(columns-1);double ystep= 1.0*h/(rows-1);
  int ix=0,cnt=0;
  for(int y=0;y<rows;y++) {
    for(int x=0;x<columns;x++) {
      if(!alternate || (ix%2)==0) {
        vertices[cnt]=VEC2(xstep*x-w2,ystep*y-h2);
        if(ix>=grid.numVerts) break;
        cnt++;
        
      }
      ix++;
      
    }
  }
  if(alternate) grid.numVerts=cnt; //reduce count if alternate
  return grid;
}

TFTLineShape TFTShapeBuilder::buildLineGrid(int rows, int columns,int w, int h) {
  TFTLineShape grid= TFTLineShape();
  grid.numVerts=2*((rows+1)+(columns+1));
  VEC2 *vertices = new VEC2[grid.numVerts];
  grid.vertices=vertices;
  double xstep= 1.0*w/rows;double ystep= 1.0*h/columns;
  float w2=w/2.; float h2=h/2.;
  int vc=0;
  for(int  y=0;y<=columns;y++) {
    vertices[vc].x=0-w2;
    vertices[vc].y=y*ystep-h2;
    vc++;
    vertices[vc].x=w-w2;
    vertices[vc].y=y*ystep-h2;
    vc++;
  }
  for(int  x=0;x<=rows;x++){
    vertices[vc].y=0-h2;
    vertices[vc].x=x*xstep-w2;
    vc++;
    vertices[vc].x=x*xstep-w2;
    vertices[vc].y=h-h2;
    vc++;
    }
    return grid;
}
//range -128 to +128
TFTShape TFTShapeBuilder::buildRandomPoints(int num){
    TFTShape ngon= TFTShape();
    ngon.numVerts=num;
    VEC2 *vertices = new VEC2[ngon.numVerts];
    ngon.vertices=vertices;
    for(int i=0;i<ngon.numVerts;i++) {
      ngon.vertices[i].x=128-random(256);
      ngon.vertices[i].y=128-random(256);
    }
    return ngon;
  
}
