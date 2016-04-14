#include "TDetector.h"
 
TDetector::TDetector(){
  pixiMap.open("pixmap.dat",ios::in);
  std::cout << "Read PIXMAP for cluster reconstruction.." << std::endl;
  char DummyString[8];
  int DummyInt;
  int i, j;
  float x,y;
  for (i=0; i< PIX_X_DIM; i++)
    {
      for (j=0; j< PIX_Y_DIM; j++)
	{
	  fPixMap[i][j] = -1;
	  fPixMask[i][j] = 0;
	  fBorderPixel[i][j] = 0; 
	} 
    }
  for (i=0; i<2; i++) {
    pixiMap >> DummyInt; 
  }
  for (i=0; i<7; ++i) {
    pixiMap >> DummyString; 
  }
  while(!pixiMap.eof()) {
    pixiMap >> x >> y >> i >> j;
    pixiMap >> fPixMap[i][j] >> fPixMask[i][j] >> fBorderPixel[i][j];
    PixToCartX[i][j] = x;
    PixToCartY[i][j] = y;
  }
  pixiMap.close();
  std::cout << "===>> Pixels MAP read !!!" << std::endl;
}

int TDetector::FindClusters(float fPedSubtrSignal[NCHANS]) {
  int ClusterCounter;
  bool OverMaxClusts;
  MatrixInt OverThresh;          // Matrix of flags indicating which pixels are over threshold.
  MatrixInt AssociatedCluster;   // Matrix indicating to which cluster each pixel is associated 
  int chan;

 // Create signal matrix.
  for (int i=0; i<PIX_X_DIM; ++i) {
    for (int j=0; j<PIX_Y_DIM; ++j) {
      chan = fPixMap[i][j]; 
      // Invert signal polarity if initially negative ( now a hit means POSITIVE signal ).
      fSignalMatrix[i][j] = fPixMask[i][j]*fPedSubtrSignal[chan]; 
    }
  }
  // Select pixels over threshold.
  for (int i=0; i<PIX_X_DIM; ++i) {
    for (int j=0; j<PIX_Y_DIM; ++j) {
      AssociatedCluster[i][j] = -1;
      if (fSignalMatrix[i][j] > Threshold)  OverThresh[i][j] = 1;
      else OverThresh[i][j] = 0;
    }
  }
  
  // Find clusters algorithm...
  ClusterCounter = 0;
  OverMaxClusts = false;
  for (int i=0; i<PIX_X_DIM; ++i) {
    for (int j=0; j<PIX_Y_DIM; ++j) {
      if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
	// NEW CLUSTER!
	if (ClusterCounter == MAXNUMCLUSTS) {
	  std::cout << "\nNumber of clusters in event exceeded maximum ( " << MAXNUMCLUSTS
	       << " ).\n";
	  OverMaxClusts = true;
	  break;
	}
	fAllClusts[ClusterCounter] = new TCluster(fSignalMatrix, OverThresh, AssociatedCluster, ClusterCounter, i, j);

	if(fAllClusts[ClusterCounter]->fClusterSize <MINCLUSIZE) {
	  delete fAllClusts[ClusterCounter];
	  fAllClusts[ClusterCounter] = 0;
	  continue;
       	}
	if(fAllClusts[ClusterCounter]->fClusterSize >=MAXCLUSIZE) {
	  delete fAllClusts[ClusterCounter];
	  fAllClusts[ClusterCounter] = 0;
	  return(0);
	  break;
       	}
      	fAllClusts[ClusterCounter]->CalcProperties(fSignalMatrix, fBorderPixel, PixToCartX, PixToCartY, 
						   WeightLengthScale, SmallCircleRadius, WideCircleRadius);
	++ClusterCounter;
      }
    }
    if (OverMaxClusts == true) {
      return(0);
      break;
    }
  }
  return (ClusterCounter);
}

