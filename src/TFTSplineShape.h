/***************************************************
  Arduino TFT 2D graphics library targeted at ESP8266
  and ESP32 based boards using the TFT_eSPI library (https://github.com/Bodmer/TFT_eSPI).
  created by JLA 11/2018 (https://github.com/androdlang/TFTShape).
 ****************************************************/
#ifndef TFT_SPLINESHAPE
#define TFT_SPLINESHAPE

class TFTSplineShape:public TFTLinestripShape {
  int subSamples;
  int numSamples;
  bool isLooped;
  public:
  TFTSplineShape(int numsamples,int subsamples,bool islooped):isLooped(islooped),subSamples(subsamples),numSamples(numsamples) {
    numVerts=isLooped?(numSamples*subSamples):((numSamples-3)*subSamples+1);
    vertices = new VEC2[numVerts];
  }

  TFTSplineShape(std::initializer_list<VEC2> samples,int subsamples,bool islooped):isLooped(islooped),subSamples(subsamples),numSamples(samples.size()) {
    numVerts=isLooped?(numSamples*subSamples):((numSamples-3)*subSamples+1);
    vertices = new VEC2[numVerts];
    VEC2 buffer[samples.size()];
    std::copy(samples.begin(), samples.end(), buffer);
    updateData(buffer);
   }

  TFTSplineShape(VEC2*samples,int numsamples,int subsamples,bool islooped):isLooped(islooped),subSamples(subsamples),numSamples(numsamples) {
    numVerts=isLooped?(numSamples*subSamples):((numSamples-3)*subSamples+1);
    vertices = new VEC2[numVerts];
    updateData(samples);
   }

  void updateData(VEC2*samples) {
    int ix=0; 
    float fstep=1./subSamples;
    if(isLooped) {
        for (float t = 0; t < (float)(numSamples); t += fstep) {
            if(ix<numVerts) {
                vertices[ix]=TFTLinestripShape::getSplinePoint(samples,numSamples,t,true);
                ix++;
            }
        }
        vertices[ix-1]=samples[0];
    } else {
        for (float t = 0; t < (float)(numSamples-3); t += fstep)
        {
            if(ix<(numVerts-1)) {
            vertices[ix]=TFTLinestripShape::getSplinePoint(samples,numSamples,t,false);
            ix++;
            }
        }
        vertices[ix]=samples[numSamples-2];
    }
  }
};
#endif
