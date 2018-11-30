/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#include "TFTShape.h"
#ifdef DEBUG
void TFTShape::dumpVerts() {
  Serial.printf("Vertices in buffer:%d\n",numVerts);
   for(int i=0,j=1;i<numVerts;i++,j=(j+1)%numVerts) {
    Serial.printf("%d:(%d,%d) ",i,(int)vertices[i].x,(int)vertices[i].y);
    if(i%8==7) Serial.println();
  }
  Serial.println();
}
#endif
CR::CR(uint16_t color) {
  c=color;
}
CR::CR(int16_t fromHue,int16_t toHue) {
  from=fromHue;
  to=toHue;
}
void CR::HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float fC = fV * fS; // Chroma
  float fHPrime = fmod(fH / 60.0, 6);
  float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
  float fM = fV - fC;

  if(0 <= fHPrime && fHPrime < 1) {
    fR = fC;   fG = fX;   fB = 0;
  } else if(1 <= fHPrime && fHPrime < 2) {
    fR = fX;   fG = fC;   fB = 0;
  } else if(2 <= fHPrime && fHPrime < 3) {
    fR = 0;   fG = fC;   fB = fX;
  } else if(3 <= fHPrime && fHPrime < 4) {
    fR = 0;   fG = fX;   fB = fC;
  } else if(4 <= fHPrime && fHPrime < 5) {
    fR = fX;   fG = 0;   fB = fC;
  } else if(5 <= fHPrime && fHPrime < 6) {
    fR = fC;   fG = 0;   fB = fX;
  } else {
    fR = 0;   fG = 0;   fB = 0;
  }

  fR += fM;  fG += fM;  fB += fM;
}
void CR::RGBtoBW(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV) {
  float avg=(fR+fG+fB)/3.;
  fR=avg; fG=avg; fB=avg;
}
uint16_t CR::colorFromHSV(int16_t hue,float s, float v) {
  float fR,fG,fB,fH=hue,fS=s,fV=v;
  HSVtoRGB(fR, fG,  fB, fH,fS , fV);
  int r=fR*31.99,g=fG*63.99,b=fB*31.99;
   return ((r<<11) |(g<<5)|b );
 }
VEC2::VEC2():x(0),y(0) {}
VEC2::VEC2(float a, float b):x(a),y(b) {}
VEC2::VEC2(float ab):x(ab),y(ab) {}
void VEC2::operator*=(const VEC2& b) {
  x *= b.x;   y *= b.y;
}
void VEC2::operator+=(const VEC2& b) {
  x += b.x;   y += b.y;
}
void VEC2::operator-=(const VEC2& b) {
  x -= b.x;   y -= b.y;
}
void VEC2::rotate(const VEC2& b) {
  float xtmp=x;
  x=b.y*x-b.x*y;
  y=b.x*xtmp+b.y*y;
}
VEC2 & VEC2::operator=(const VEC2 &v)
  {
    this->x = v.x;
    this->y = v.y;
    return *this;
}
TFTShape::TFTShape(std::initializer_list<VEC2> verts):numVerts(verts.size()) {
  vertices = new VEC2[numVerts];
  std::copy(verts.begin(), verts.end(), vertices);
}
TFTShape::TFTShape(){
}
TFTShape::~TFTShape() {
  //Serial.println(esp_get_free_heap_size());

  if(vertices!=NULL) {
    //Serial.println("DESTRUCTOR vertices!!!!");
   delete vertices;
   vertices=NULL;
  }
    //Serial.println(esp_get_free_heap_size());

}
void TFTShape::setPivot(int x,int y) {
  pivot.x=x; pivot.y=y;
}
void TFTShape::setRotation(float a) {
  rotation=a;
  //ca=cos(rotation*M_PI/180);
  //sa=sin(rotation*M_PI/180);
  
  sincos.x=sin(rotation*M_PI/180);
  sincos.y=cos(rotation*M_PI/180);

}
void TFTShape::setRotationBy(float a) {
  rotation+=a;
  sincos.x=sin(rotation*M_PI/180);
  sincos.y=cos(rotation*M_PI/180);
}
float TFTShape::getRotation() {
 return rotation;
}
void TFTShape::setRotationFixed(bool b) {
  rotationFixed=b;
}
bool TFTShape::isRotationFixed() {
  return rotationFixed;
}
void TFTShape::setScale(float sx, float sy) {
   scalefac.x=sx; scalefac.y=sy;
}
void TFTShape::setScale(float s) {
   scalefac.x=scalefac.y=s;
}
void TFTShape::setScaleBy(float s) {
   scalefac.x*=s;
   scalefac.y*=s;
}
VEC2 TFTShape::getScale() {
  return scalefac;
}
void TFTShape::setOffset(float x, float y) {
   offset.x=x;offset.y=y;
}
VEC2 TFTShape::getOffset() {
  return offset;
}
void TFTShape::drawOptimizedLine(TFT_eSPI*display,int x,int y,int x0,int y0, int x1,int y1, int textcolor) {
  display->drawLine(x+x0,y+y0,x+x1,y+y1,textcolor);
}
void TFTShape::draw(TFT_eSPI* display, int x0, int y0, int16_t color) {
  int n=numVerts;
  VEC2 *v=vertices;
    for(int i=0,j=1;i<n;i++,j=(j+1)%n) {
      VEC2 vi=TRANSFORM(v[i]);
      VEC2 vj=TRANSFORM(v[j]);
      drawOptimizedLine(display,x0,y0,vi.x,vi.y,vj.x,vj.y,color);
    }
}
void TFTShape::draw(TFT_eSPI* display, int x0, int y0, TFTShape& s, const CR & color,int every) {
  VEC2 *v=vertices;
  float originalRotation=s.getRotation();
  for(int i=0,j=1;i<numVerts;i++,j=(j+1)%numVerts) {
    VEC2 vi=TRANSFORM(v[i]);
    if(!s.isRotationFixed()) {
      VEC2 p=vi;
      p+=s.pivot;
      p-=pivot;
      if(abs(p.x)<.01 && abs(p.y)<.01) {
        s.setRotation(rotation+originalRotation);
      } else 
        s.setRotation((-atan2(p.x,p.y)*180/M_PI)+originalRotation);
    }
    uint16_t c=color.c;
    if(color.from>=0) {
      c=CR::colorFromHSV(map(i,0,numVerts,color.from,color.to),1,1);
    }
    s.draw(display,x0+vi.x,y0+vi.y,c);
  }
  s.setRotation(originalRotation);
}
void TFTShape::fill(TFT_eSPI* display, int x0, int y0, TFTShape& s, const CR & color,int every) {
  VEC2 *v=vertices;
  float originalRotation=s.getRotation();
  for(int i=0,j=1;i<numVerts;i++,j=(j+1)%numVerts) {
    VEC2 vi=TRANSFORM(v[i]);
    if(!s.isRotationFixed()) {
      VEC2 p=vi;
      p+=s.pivot;
      p-=pivot;
      if(abs(p.x)<.01 && abs(p.y)<.01) {
        s.setRotation(rotation+originalRotation);
      } else 
      s.setRotation((-atan2(p.x,p.y)*180/M_PI)+originalRotation);
    }
    uint16_t c=color.c;
    if(color.from>=0) {
      c=CR::colorFromHSV(map(i,0,numVerts,color.from,color.to),1,1);
    }
    s.fill(display,x0+vi.x,y0+vi.y,c,every);
  }
  s.setRotation(originalRotation);
}
void TFTShape::fillDraw(TFT_eSPI* display, int x0, int y0,TFTShape & s, const CR & colorOutline, const CR & color,int every) {
  fill(display,x0,y0,s,color,every);
  draw(display,x0,y0,s,colorOutline);
}
void TFTShape::fillH(TFT_eSPI* display, int x0, int y0, const CR & color,int every) {
  int16_t n=numVerts;
  VEC2 *v=vertices;
  
  int16_t minx, maxx;
  int x1, y1;
  int x2, y2;
  int16_t ix;

  int polyints[n];
  //create a copy
  VEC2 vv[n];

  // find y-min/max and transform vertices
  vv[0]=TRANSFORM(v[0]);
  minx = vv[0].x;
  maxx = vv[0].x;
  for (int i=1; (i < n); i++)
  {
    vv[i]=TRANSFORM(v[i]);
    minx = min(minx, vv[i].x);
    maxx = max(maxx, vv[i].x);

  }

  //scan y lines
  for(int scanline=minx; (scanline <= maxx); scanline++) {
    if(scanline%every) continue;
    ix = 0;
    for (int i=0,ii=n-1; (i < n); i++,ii=i-1) {
      x1 = vv[ii].x; //A
      x2 = vv[i].x; //B
      if(x1 == x2) continue;
      if (x1 < x2) {
        y1 = vv[ii].y; //a
        y2 = vv[i].y; //b
      } else {
        y1 = vv[i].y; //b
        y2 = vv[ii].y; //a
        x1 = vv[i].x; //B
        x2 = vv[ii].x; //A
      }
      if ((scanline >= x1) && (scanline < x2)) {
        polyints[ix++] = (scanline-x1) * (y2-y1) / (x2-x1) + y1;
      } else if ((scanline == maxx) && (scanline > x1) && (scanline <= x2)) {
        polyints[ix++] = (scanline-x1) * (y2-y1) / (x2-x1) + y1;
      }
    }
    qsort(polyints, ix, sizeof(int), [](const void *a, const void *b){return (*(const int *)a) - (*(const int *)b);});
    uint16_t c=color.c;
    if(color.from>=0) {
      c=CR::colorFromHSV(map(scanline,minx,maxx,color.from,color.to),1,1);
    }
    for (int i=0; i<ix; i+=2) {
       display->drawFastVLine(x0+scanline,y0+polyints[i], polyints[i+1]- polyints[i],c);
    }
  }
}
void TFTShape::fillDraw(TFT_eSPI* display, int x0, int y0, const CR & colorOutline,CR color,int every) {
  fill(display,x0,y0,color,every);
  draw(display,x0,y0,colorOutline.c);
}
void TFTShape::fillDrawH(TFT_eSPI* display, int x0, int y0, const CR & colorOutline,CR color,int every) {
  fillH(display,x0,y0,color,every);
  draw(display,x0,y0,colorOutline.c);
}
void TFTShape::fill(TFT_eSPI* display, int x0, int y0, CR color,int every) {
    int16_t n=numVerts;
    VEC2 *v=vertices;
  
    int16_t miny, maxy;
    int x1, y1;
    int x2, y2;
    int16_t ix;
  
    int polyints[n];
    //create a copy
    VEC2 vv[n];
  
    // find y-min/max and transform vertices
    vv[0]=TRANSFORM(v[0]);
    miny = vv[0].y;
    maxy = vv[0].y;
    for (int i=1; (i < n); i++)
    {
      vv[i]=TRANSFORM(v[i]);
      miny = min(miny, vv[i].y);
      maxy = max(maxy, vv[i].y);
  
    }
  
    //scan y lines
    for(int scanline=miny; (scanline <= maxy); scanline++) {
      if(scanline%every) continue;
      ix = 0;
      for (int i=0,ii=n-1; (i < n); i++,ii=i-1) {
        y1 = vv[ii].y; //A
        y2 = vv[i].y; //B
        if(y1 == y2) continue;
        if (y1 < y2) {
          x1 = vv[ii].x; //a
          x2 = vv[i].x; //b
        } else {
          x1 = vv[i].x; //b
          x2 = vv[ii].x; //a
          y1 = vv[i].y; //B
          y2 = vv[ii].y; //A
        }
        if ((scanline >= y1) && (scanline < y2)) {
          polyints[ix++] = (scanline-y1) * (x2-x1) / (y2-y1) + x1;
        } else if ((scanline == maxy) && (scanline > y1) && (scanline <= y2)) {
          polyints[ix++] = (scanline-y1) * (x2-x1) / (y2-y1) + x1;
        }
      }
      qsort(polyints, ix, sizeof(int), [](const void *a, const void *b){return (*(const int *)a) - (*(const int *)b);});
      // int16_t==slower !!! qsort(polyints, ix, sizeof(int16_t), [](const void *a, const void *b){return (*(const int16_t *)a) - (*(const int16_t *)b);});
      uint16_t c=color.c;
      if(color.from>=0) {
        c=CR::colorFromHSV(map(scanline,miny,maxy,color.from,color.to),1,1);
      }
  
      for (int i=0; i<ix; i+=2) {
        display->drawFastHLine(x0+polyints[i],y0+scanline, polyints[i+1]- polyints[i],c);
      }
    }
}
VEC2 TFTShape::trans(VEC2 aa) {
    
    VEC2 a=aa;
    a+=offset;
    a-=pivot;
    a*=scalefac;
    a.rotate(sincos);
    a+=pivot;
    return a;
}


  
