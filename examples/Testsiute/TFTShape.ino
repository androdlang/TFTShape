#include <TFT_eSPI.h>
#include <TFTShape.h>
TFT_eSPI tft = TFT_eSPI(); 

//uncomment this for offscreen display
//#define OFFSCREEN

#ifdef OFFSCREEN
  TFT_eSprite tft2 = TFT_eSprite(&tft);
#else
  #define tft2 tft
#endif
#define TFT_GREY 0xa514
long start,startRender;

void header(String title) {
  tft2.fillScreen(TFT_NAVY);
  tft2.drawFastVLine(120,0,360,TFT_DARKGREY);
  tft2.drawFastHLine(0,160,240,TFT_DARKGREY);
  TC_String(tft2,title,5,4,TFT_GREEN);
  start=millis();
  startRender=start;
}
void footer() {
  BC_String(tft2,"render/total time : "+String(millis()-startRender)+"/"+String(millis()-start)+" ms",5,2,TFT_WHITE);
  #ifdef OFFSCREEN
    tft2.pushSprite(0,0);
  #endif
  delay(2000);
}

void setup() {
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLUE);
  #ifdef OFFSCREEN
    tft2.setColorDepth(8); //!!COLOR_DEPTH!!
    tft2.createSprite(240,320); //Display dimension
 #endif
  runTests();

}

void loop() {}

  //****************************************
void tetris() {
header("tetris");
  TFTShape block=TFTShape({{0,-1},{0,0},{1,0},{2,0}}); block.setScale(20);
  TFTShape r= TFTShapeBuilder::buildRect(20);
  block.fillDraw(&tft2,120,160,r,TFT_WHITE,TFT_DARKGREEN);
  block.rotateBy(90);
  block.fillDraw(&tft2,120,40,r,TFT_WHITE,TFT_RED);
  block.rotateBy(90);
  block.fillDraw(&tft2,120,240,r,TFT_BLACK,TFT_YELLOW);
  footer();
} 

  //****************************************
void pivotScale() {
header("pivot scale");
  TFTShape r=TFTShapeBuilder::buildRect(80);
  
  r.setPivot(0,-40);
  for(int i=0;i<10;i++) {
    r.scaleBy(.8)->draw(&tft2,120,100,TFT_WHITE);
  }
  r.reset(); r.draw(&tft2,120,100,TFT_GREEN);
  tft2.drawFastHLine(120-100,60,200,TFT_YELLOW);
  tft2.drawFastVLine(120,60-100,200,TFT_YELLOW);

  r.setPivot(0,0);
  for(int i=0;i<10;i++) {
    r.scaleBy(.8)->draw(&tft2,120,240,TFT_WHITE);
  }
  r.reset(); r.draw(&tft2,120,240,TFT_GREEN);
  tft2.drawFastHLine(120-100,240,200,TFT_YELLOW);
  tft2.drawFastVLine(120,240-100,200,TFT_YELLOW);


  footer();
} 

  //****************************************
void pivotRot() {
header("pivot rotation");
  TFTShape r=TFTShapeBuilder::buildRect(80);
  
  r.setPivot(0,-40);r.setRotation(-30);
  for(int i=0;i<10;i++) {
    r.rotateBy(6)->draw(&tft2,120,100,TFT_WHITE);
  }
  r.reset(); r.draw(&tft2,120,100,TFT_GREEN);
  tft2.drawFastHLine(120-100,60,200,TFT_YELLOW);
  tft2.drawFastVLine(120,60-100,200,TFT_YELLOW);

  r.setPivot(0,0);r.setRotation(-30);
  for(int i=0;i<10;i++) {
    r.rotateBy(6)->draw(&tft2,120,240,TFT_WHITE);
  }
  r.reset(); r.draw(&tft2,120,240,TFT_GREEN);
  tft2.drawFastHLine(120-100,240,200,TFT_YELLOW);
  tft2.drawFastVLine(120,240-100,200,TFT_YELLOW);

  footer();
} 
  //****************************************
void clock1() {
header("analog-clock");
  TFTShape dot=TFTShapeBuilder::buildNgon(3,12); dot.setScale(.5,1);
  TFTShape face=TFTShapeBuilder::buildNgon(12,100);
  //clock-face 
  face.draw(&tft2,120,160,dot,TFT_WHITE);
  //hour-hand
  TFTShape hand=TFTShapeBuilder::buildNgon(5,60);
  hand.setScale(.08,.8); hand.setOffset(0,-30); hand.setRotation(170);
  hand.fill(&tft2,120,160,TFT_GREY);
  //minutes-hand
  hand.setScale(.08,1); hand.setRotation(240);
  hand.fill(&tft2,120,160,TFT_LIGHTGREY);
  //seconds-hand
  hand.setScale(.03,1); hand.setRotation(30); 
  hand.fill(&tft2,120,160,TFT_RED);
  dot.fill(&tft2,120,160,TFT_RED);
  dot.setScale(.4);
  dot.fill(&tft2,120,160,TFT_DARKGREY);
  footer();
  
  
} 
  //****************************************
  void euro() {
  header("euro");
  TFTShape s=TFTShapeBuilder::buildStar(5,12,5);
  s.setRotationFixed(true);
  TFTShape n=TFTShapeBuilder::buildNgon(12,80);
  startRender=millis();
  n.fill(&tft2,120,160,s,TFT_YELLOW);
  footer();
  }
  //****************************************
  void fillstyles2() {
  header("fillstyles-2");
  TFTShape r=TFTShapeBuilder::buildRect(8,16);
  TFTShape arc=TFTShapeBuilder::buildArc(24,80,210,300);
  startRender=millis();
  arc.fill(&tft2,120,160,r,CR(120,0));
  footer();
  }

  //****************************************
  void fillstyles1() {
  header("fillstyles-1");
  
  TFTShape r=TFTShapeBuilder::buildRect(40);
  startRender=millis();
  r.fill(&tft2,120-80,160-60,TFT_GREEN);
  r.fill(&tft2,120-80,160,TFT_GREEN,2);
  r.fillH(&tft2,120-80,160+60,TFT_GREEN,2);
  r.fill(&tft2,120,160-60,TFT_GREEN,4);
  r.fillH(&tft2,120,160-60,TFT_GREEN,4);
  r.fill(&tft2,120,160,CR(0,120));
  r.fillH(&tft2,120,160+60,CR(0,120));
  
  
  r.fill(&tft2,120+80,160-60,TFT_WHITE,3);
  r.fillH(&tft2,120+80,160-60,TFT_WHITE,3);
  //r.draw(&tft2,120+80,160-60,TFT_WHITE);
  
  r.fill(&tft2,120+80,160,TFT_WHITE);
  r.fill(&tft2,120+80,160,TFT_BLACK,4);
  r.fillH(&tft2,120+80,160,TFT_BLACK,4);

  
  
  //r.fill(&tft2,120+80,160+60,TFT_WHITE);
  r.fill(&tft2,120+80,160+60,TFT_WHITE,7);
  r.fill(&tft2,120+80,160+60,TFT_WHITE,5);
  r.fillH(&tft2,120+80,160+60,TFT_WHITE,7);
  r.fillH(&tft2,120+80,160+60,TFT_WHITE,5);
  //for(int i=0;i<160;i++) {
    //tft2.drawFastHLine(120+80, 80+i,20,CR::colorFromHSV(100,0,i/160.));
  //}

  footer();
 }
  //****************************************
  void lines2() {
  header("lines");
  
  TFTLineShape lines=TFTLineShape({{-1,0},{1,0},{0,-1},{0,1}});

  lines.setScale(50);
  lines.setRotation(30);
  startRender=millis();
  lines.draw(&tft2,120,160-60,TFT_WHITE);
  lines.fill(&tft2,120,160+60,TFT_WHITE);
  footer();
 }
  //****************************************
  void grid_2() {
    header("grid-2");
    TFTShape r=TFTShapeBuilder::buildRect(8);
    r.setRotationFixed(true);
    TFTShape grid=TFTShapeBuilder::buildGrid(9,9,160,160,true);
    startRender=millis();
    grid.draw(&tft2,120,160,r,TFT_WHITE);
 
    footer();
  }
  //****************************************
  void grid_1() {
    header("grid-1");
    TFTShape triangle=TFTShapeBuilder::buildRect(8);
    triangle.setRotationFixed(true);
    TFTShape grid=TFTShapeBuilder::buildGrid(9,9,160,160,false);
    startRender=millis();
    grid.draw(&tft2,120,160,triangle,TFT_WHITE);
    //grid.dumpVerts();

    footer();
  }

   //****************************************
  void star2() {
    header("star");
    TFTShape star=TFTShapeBuilder::buildStar(12,80,40);
    startRender=millis();
    star.fillDraw(&tft2,120,160,TFT_WHITE,TFT_DARKGREEN,2);

    footer();
  }
   //****************************************
  void linegrid() {
    header("linegrid");
    TFTLineShape grid=TFTShapeBuilder::buildLineGrid(6,6,160,160);
    startRender=millis();
    grid.draw(&tft2,120,160,TFT_WHITE);

    footer();
  }
   //****************************************
  void ngon() {
    header("Ngon");
    TFTShape n1=TFTShapeBuilder::buildNgon(3,35);
    TFTShape n2=TFTShapeBuilder::buildNgon(4,35);
    TFTShape n3=TFTShapeBuilder::buildNgon(5,35);
    TFTShape n4=TFTShapeBuilder::buildNgon(6,35);
    TFTShape n5=TFTShapeBuilder::buildNgon(7,35);
    TFTShape n6=TFTShapeBuilder::buildNgon(8,35);
    startRender=millis();
    n1.fillDrawH(&tft2,120-60,160-80,TFT_WHITE,TFT_DARKGREEN,2);
    n2.fillDrawH(&tft2,120-60,160,TFT_WHITE,TFT_DARKGREEN,2);
    n3.fillDrawH(&tft2,120-60,160+80,TFT_WHITE,TFT_DARKGREEN,2);
    n4.fillDrawH(&tft2,120+60,160-80,TFT_WHITE,TFT_DARKGREEN,2);
    n5.fillDrawH(&tft2,120+60,160,TFT_WHITE,TFT_DARKGREEN,2);
    n6.fillDrawH(&tft2,120+60,160+80,TFT_WHITE,TFT_DARKGREEN,2);
    
    
    footer();
  }
   //****************************************
  void splineLoop() {
    header("splineloop");
    TFTShape star=TFTShapeBuilder::buildStar(5,80,40);
    //std::initializer_list<VEC2> pts=(<VEC2>)star.getPoints();
    TFTLinestripShape spline=TFTShapeBuilder::buildSplineLoop( star.getPoints(),star.getNumPoints(),8);
    startRender=millis();
    spline.fillH(&tft2,120,160,TFT_DARKGREEN,2);
    spline.draw(&tft2,120,160,TFT_WHITE);
    
    
    footer();
  }
   //****************************************
  void spline() {
    header("spline");
    TFTLinestripShape spline=TFTShapeBuilder::buildSpline( {{0,0},{1,0},{2,0},{3,-1},{4,0},{5,-5},{6,1},{7,0},{8,-1},{9,-1.5},{10,-1},{11,0},{12,0},{12,0}},3);
    spline.setScale(15); spline.setOffset(-6,0);
    startRender=millis();
    spline.draw(&tft2,120,160-40,TFT_WHITE);
    spline.fillH(&tft2,120,160+80,TFT_WHITE);
    
    footer();
  }
   //****************************************
  void annularWedge() {
    header("annular wedge");
    
    TFTShape w=TFTShapeBuilder::buildAnnularWedge(32,80,65,210,300);
    startRender=millis();
    w.fillDrawH(&tft2,120,160,TFT_WHITE,TFT_DARKGREEN,2);
 
    footer();
  }
 //****************************************
  void arc2() {
    header("arc");
    
    TFTShape a1=TFTShapeBuilder::buildArc(24,80,0,180);
    TFTShape a2=TFTShapeBuilder::buildArc(24,80,210,120);
    startRender=millis();
    a1.fillDraw(&tft2,120,160,TFT_WHITE,TFT_DARKGREEN,2);
    a2.fillH(&tft2,120,160,TFT_RED,2);

    footer();
  }
  //****************************************
  void wedge2() {
    header("wedge");
    
    TFTShape w1=TFTShapeBuilder::buildWedge(18,80,180,240);
    TFTShape w2=TFTShapeBuilder::buildWedge(18,80,60,120);
    startRender=millis();
    w1.fillDraw(&tft2,120,160,TFT_WHITE,TFT_DARKGREEN,2);
    w2.fillDrawH(&tft2,130,170,TFT_WHITE,TFT_RED,2);

    footer();
  }
  //****************************************
  void rect() {
    header("rect");
    
    TFTShape rect=TFTShapeBuilder::buildRect(200,250);
    startRender=millis();
    rect.draw(&tft2,120,160,TFT_WHITE);
    for(int i=0;i<8;i++) {
      rect.scaleBy(.9)->draw(&tft2,120,160,TFT_WHITE);
    }
    rect.fillH(&tft2,120,160,TFT_DARKGREEN,2);
    
    footer();
  }
  //****************************************
  void ellipse() {
    header("ellipse");
    
    TFTShape ellipse=TFTShapeBuilder::buildEllipse(36,100,50);
    startRender=millis();
    ellipse.fill(&tft2,120,160,TFT_DARKGREEN,2);
    for(int i=0;i<4;i++) {
      ellipse.rotateBy(45)->draw(&tft2,120,160,TFT_WHITE);
    }
    footer();
  }
  //****************************************
void clock2() {
header("analog-clock");
  TFTShape dot=TFTShapeBuilder::buildNgon(3,8);
  TFTShape face=TFTShapeBuilder::buildNgon(12,100);
  //clock-face 
  face.fill(&tft2,120,160,dot,TFT_GREY);
  int pivy=35;
  //hour-hand
  TFTShape hand=TFTShapeBuilder::buildNgon(5,60);
  hand.setScale(.08,.8); hand.setPivot(0,pivy); hand.setRotation(170);
  hand.fill(&tft2,120,160-pivy,TFT_GREY);
  //minutes-hand
  hand.setScale(.08,1); hand.setRotation(240);
  hand.fill(&tft2,120,160-pivy,TFT_LIGHTGREY);
  //seconds-hand
  hand.setScale(.03,1); hand.setRotation(30); 
  hand.fill(&tft2,120,160-pivy,TFT_RED);
  dot.fill(&tft2,120,160,TFT_RED);
  dot.setScale(.4);
  dot.fill(&tft2,120,160,TFT_DARKGREY);
  footer();
} 
  
  //****************************************
  void runTests() {
    ellipse();
   rect();
   wedge2();
   arc2();
   annularWedge();
   spline();
   splineLoop();
   linegrid();
    star2();
    grid_1();
    grid_2();
    lines2();
    fillstyles1();
    fillstyles2();
    euro();
    clock1();
    pivotRot();
    pivotScale();
    tetris();
    ngon();
  }
