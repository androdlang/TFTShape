/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards.
  created by JLA 11/2018
 ****************************************************/
#include "TFTShape.h"
TFTLinestripShape TFTShapeBuilder::buildSpline(std::initializer_list<VEC2> verts,int substeps) {
    
    int numPoints=verts.size();
    VEC2 buffer[numPoints];
    
    std::copy(verts.begin(), verts.end(), buffer);
    return TFTShapeBuilder::buildSpline(buffer,numPoints,substeps);
    
}

TFTLinestripShape TFTShapeBuilder::buildSpline(VEC2 * buffer ,int numPoints,int substeps) {
   TFTLinestripShape spline= TFTLinestripShape();
    int ix=0; 
    float fstep=1./substeps;
    spline.numVerts=(numPoints-3)*substeps+1;
    spline.vertices = new VEC2[spline.numVerts];
    for (float t = 0; t < (float)(numPoints-3); t += fstep)
      {
        if(ix<(spline.numVerts-1)) {
          spline.vertices[ix]=TFTLinestripShape::getSplinePoint(buffer,numPoints,t,false);
          ix++;
        }
     }
     spline.vertices[ix]=buffer[numPoints-2];
    return spline;     
}
TFTShape TFTShapeBuilder::buildNgon(int corners, int radius) {
    TFTShape ngon= TFTShape();
    VEC2 *vertices = new VEC2[corners];
    ngon.vertices=vertices;
    //ngon.btype=BT_PONTS;
    ngon.numVerts=corners;
    float a=360/corners;
    for(int i=0;i<corners;i++) {
      float al=+a*i*M_PI/180;
      vertices[i].x=sin(al)*radius;
      vertices[i].y=-cos(al)*radius;
    }
    return ngon;
}
TFTShape TFTShapeBuilder::buildNgon(int corners, int rw, int rh) {
    TFTShape ngon= TFTShape();
    VEC2 *vertices = new VEC2[corners];
    ngon.vertices=vertices;
    //ngon.btype=BT_PONTS;
    ngon.numVerts=corners;
    float a=360/corners;
    for(int i=0;i<corners;i++) {
      float al=+a*i*M_PI/180;
      vertices[i].x=sin(al)*rw;
      vertices[i].y=-cos(al)*rh;
    }
    return ngon;
}
TFTShape TFTShapeBuilder::buildStar(int corners, int r1, int r2) {
    TFTShape ngon= TFTShape();
    ngon.numVerts=corners*2;
    VEC2 *vertices = new VEC2[ngon.numVerts];
    ngon.vertices=vertices;
    float a=360/corners;
    for(int i=0,ix=0;i<corners;i++) {
      float al=+a*i*M_PI/180;
      vertices[ix].x=sin(al)*r1;
      vertices[ix].y=-cos(al)*r1;
      ix++;
      vertices[ix].x=sin(al+a/2*M_PI/180)*r2;
      vertices[ix].y=-cos(al+a/2*M_PI/180)*r2;
      ix++;
    }
   // vertices[ngon.numVerts-1].x=vertices[0].x;
   // vertices[ngon.numVerts-1].y=vertices[0].y;
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
TFTLinestripShape TFTShapeBuilder::buildSplineLoop(VEC2 * buffer,int numPoints,int substeps) {
  TFTLinestripShape spline= TFTLinestripShape();
  int ix=0; 
  float fstep=1./substeps;
  spline.numVerts=(numPoints)*substeps;
  VEC2 *vertices = new VEC2[spline.numVerts];
  spline.vertices=vertices;
  for (float t = 0; t < (float)(numPoints); t += fstep)
    {
      if(ix<spline.numVerts) {
        
        spline.vertices[ix]=TFTLinestripShape::getSplinePoint(buffer,numPoints,t,true);
        ix++;
      }
   }
   spline.vertices[ix-1]=buffer[0];
   return spline;
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