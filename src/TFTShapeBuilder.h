/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
struct TFTShapeBuilder{
    static void  fillNgonVertices(VEC2 *v ,int corners, VEC2 radius);
    static VEC2 * createNgonVertices(int corners, VEC2 radius);
    static void fillStarVertices(VEC2 *v ,int corners, VEC2 r1,VEC2 r2);
    static VEC2 * createStarVertices(int corners, VEC2 r1,VEC2 r2);
    static TFTLineShape buildLineGrid(int rows, int columns,int width, int height);
    static TFTShape buildNgon(int corners, int radius);
    static TFTLinestripShape buildNgonLinestrip(int corners, VEC2 radius);
    static TFTShape buildNgon(int corners, int rw, int rh);
    static TFTShape buildCircle(int segments, int radius) {return buildNgon(segments,radius);}
    static TFTShape buildEllipse(int segments, int r1, int r2) {return buildNgon(segments,r1,r2);}
    static TFTShape buildStar(int corners, int r1, int r2);
    static TFTShape buildStar(int corners, VEC2 r1, VEC2 r2);
    static TFTShape buildGear(int corners, int r1, int r2,float toothAngle);
    static TFTShape buildRect(int w, int h);
    static TFTShape buildRect(int wh);
    static TFTShape buildArc(int segments, int radius,float start, float spanAngle);
    static TFTShape buildWedge(int segments, int radius,float start, float spanAngle);
    static TFTShape buildAnnularWedge(int segments, int r1,int r2, float start, float spanAngle);
    static TFTShape buildGrid(int rows, int columns,int width, int height,bool alternate=false);
    static TFTShape buildRandomPoints(int num);
 
    
};
