/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards.
  created by JLA 11/2018
 ****************************************************/
struct TFTShapeBuilder{
    static TFTLinestripShape buildSpline(std::initializer_list<VEC2> verts,int substeps);
    static TFTLinestripShape buildSpline(VEC2 * buffer ,int numPoints,int substeps);
    static TFTLinestripShape buildSplineLoop(VEC2 * buffer,int numVerts,int steps);
    
    static TFTLineShape buildLineGrid(int rows, int columns,int width, int height);

    static TFTShape buildNgon(int corners, int radius);
    static TFTShape buildNgon(int corners, int rw, int rh);
    static TFTShape buildCircle(int segments, int radius) {return buildNgon(segments,radius);}
    static TFTShape buildEllipse(int segments, int r1, int r2) {return buildNgon(segments,r1,r2);}
    static TFTShape buildStar(int corners, int r1, int r2);
    static TFTShape buildRect(int w, int h);
    static TFTShape buildRect(int wh);
    static TFTShape buildArc(int segments, int radius,float start, float spanAngle);
    static TFTShape buildWedge(int segments, int radius,float start, float spanAngle);
    static TFTShape buildAnnularWedge(int segments, int r1,int r2, float start, float spanAngle);
    static TFTShape buildGrid(int rows, int columns,int width, int height,bool alternate=false);
    
};
