#ifndef TCLUSTER_HH
#define TCLUSTER_HH

#include "xPolMon.h"

class TCluster {

 private:

  int fClusterNumber;

 public:
  float cluLenght;
  MatrixFloat fPGVMatrix;     // Matrix for "average cluster" plot.
  int fHighestPix;            // Number of pixel with highest signal.

  int fPixelsInCluster[MAXCLUSIZE][2];
  float fPixelsCoordInCluster[MAXCLUSIZE][2];
  
  float fPulseHeight;
  float fBorderCharge;        // Total charge on border pixels.
  float fHighestCharge;
  float fCenterOfGravityX;
  float fCenterOfGravityY;
  double fTheta;              // Angle of cluster main axis, using beam spot or barycentre method.
  double fTheta2;             // Angle calculated by another method, e.g. using furthest pix.
  float fThetaDiff;
  float fMomentumX, fMomentumY;   // Principal momenta of cluster ( comments for fTheta apply ).
  float fMom2X, fMom2Y;
  float fThirdMomentumX, fThirdMomentumY;
  float fFurthestPosX, fFurthestPosY;
  float fImpactPosX, fImpactPosY;
  int   fClusterSize;
  float Shape;
  int   impactFlag;
  int   index0;
  float HighestSig;   // Highest signal in cluster.

  TCluster(MatrixFloat, MatrixInt, MatrixInt, int, int, int);
  //~TCluster();   // Default destructor.

  void CalcProperties(MatrixFloat, unsigned short[PIX_X_DIM][PIX_Y_DIM], MatrixFloat, MatrixFloat, 
		      float, float, float);
  float PixelWeight(float, float, float, float);
  
};

#endif


























