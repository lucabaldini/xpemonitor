#ifndef TDETECTOR_HH
#define TDETECTOR_HH

#include "TCluster.h"
using namespace std;

class TDetector {

 private:
  ifstream pixiMap;
 
  MatrixUshort fPixMask;
  MatrixUshort fBorderPixel;
 
  float WeightLengthScale;
  float SmallCircleRadius;
  float WideCircleRadius;
  float Threshold;

 public:
  ifstream infoPar;
  TCluster *fAllClusts[MAXNUMCLUSTS];
  MatrixInt fPixMap;
  MatrixFloat PixToCartX;
  MatrixFloat PixToCartY;
  MatrixFloat fSignalMatrix;

  bool OneClusFlag;
  int Roi[4], numPix;    
  unsigned short time1, time2;
  double timestamp;
  int bufferID;
  float fPedSubtrSignal[NCHANS];
  float fCluPH[NCHANS];
  float fPixelThresh;

  TDetector();
  int FindClusters(float[NCHANS]);
  inline void SetWeight(float Weight) {WeightLengthScale = Weight;}
  inline void SetSmallRadius(float SmallRadius) {SmallCircleRadius = SmallRadius;}
  inline void SetWideRadius(float WideRadius) {WideCircleRadius = WideRadius;}
  inline void SetThreshold(float Thresh) { Threshold = Thresh;}
};

#endif

