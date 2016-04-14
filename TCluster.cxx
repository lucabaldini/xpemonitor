
#include "TCluster.h"

TCluster::TCluster(MatrixFloat SignalMatrix, MatrixInt OverThresh, MatrixInt AssociatedCluster, 
		    int ClusterNum, int SeedPixelX, int SeedPixelY) {
  int ExploredPixels;
  int StartPixelX, StartPixelY;
  int i, j;
  //--------------------------------------------------
  fClusterNumber = ClusterNum;
  fPulseHeight = 0.0;
  fCenterOfGravityX = fCenterOfGravityY = 0.0;
  fClusterSize = 0;
  fTheta = 0.0;
  fTheta2 = 0.0;
  fMomentumX = 0.0;
  fMomentumY = 0.0;
  //---------------------------------------------------
  // Determine which of the pixels above threshold belong to this cluster.
  fClusterSize = 1;   // Since one pixel already found over thresh, initialise cluster size to 1.
  ExploredPixels = 0;   // Zero the number of explored pixels other than the one already found.
  // Set the X and Y coords of the first pixel in the cluster (pixel 0) to the values for the
  // seed pixel passed from TDetector.cxx...
  fPixelsInCluster[0][0] = SeedPixelX;
  fPixelsInCluster[0][1] = SeedPixelY;
  AssociatedCluster[SeedPixelX][SeedPixelY] = fClusterNumber;  // Set associated cluster for pixel 0.
  // Initialise variables for tracking pixel with highest signal.
  HighestSig = SignalMatrix[SeedPixelX][SeedPixelY];
  fHighestPix = 0;

  i = 0;
  j = 0;

   while(ExploredPixels < fClusterSize) {
    // Look in a hexagonal region around the seed pixel for other hits above threshold.  Update cluster size
    // counter if found.  Then do the same for all pixels adjacent to the seed, each time updating the ExploredPixels
    // counter.  Continue in this way and exit loop when all pixels in cluster have been explored.  The ExploredPixels
    // counter will always be lower than the cluster size until the end of this process.

    // Set the coordinates of the pixel being explored.
    StartPixelX = fPixelsInCluster[ExploredPixels][0];
    StartPixelY = fPixelsInCluster[ExploredPixels][1];	

    ///Pixel low left respect to seed ///1
    if(StartPixelX%2==0) { // i pari  j pari o dispari
      i = StartPixelX - 1;
      if(i < 0) i = 0;
      j = StartPixelY;
    }
    else {                /// i dispari j pari o dispari
      i = StartPixelX - 1;
      if(i < 0) i = 0;
      j = StartPixelY - 1;
      if(j < 0) j = 0;
    }
    if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    
    //Pixel high left respect to seed  ///2
    if(StartPixelX%2==0) {
      i = StartPixelX - 1;
      if(i < 0) i = 0;
      j = StartPixelY + 1;
      if(j >= 300) j = 299; 
    }
    else {
      i = StartPixelX - 1;
      if(i < 0) i = 0;
      j = StartPixelY;
    }
     if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    
    //Pixel top respect to seed  ///3
    i = StartPixelX;
    j = StartPixelY + 1;
    if (j >= 300) j = 299; 
    if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    
    //Pixel high right respect to seed  ///4
    if(StartPixelX%2==0) {
      i = StartPixelX + 1;
      if(i >= 352) i = 351;
      j = StartPixelY + 1;
      if(j >= 300) j = 299; 
    }
    else {
      i = StartPixelX + 1;
      if(i >= 352) i = 351;
      j = StartPixelY;
    }
    if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    
    //Pixel low right respect to seed  ///5
    if(StartPixelX%2==0) {
      i = StartPixelX + 1;
      if (i >= 352) i = 351;
      j = StartPixelY;
    }
    else {
      i = StartPixelX + 1;
      if (i >= 352) i = 351;
      j = StartPixelY - 1;
      if(j < 0) j = 0;
    }
    if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    //////////////////////////////////////////////
    
    //Pixel bottom respect to seed  ///6
    i = StartPixelX;
    j = StartPixelY-1;
    if(j < 0) j = 0;
    if (OverThresh[i][j] && AssociatedCluster[i][j] < 0 ) {
      fPixelsInCluster[fClusterSize][0] = i;
      fPixelsInCluster[fClusterSize][1] = j;
      AssociatedCluster[i][j] = fClusterNumber;
      // Keep track of the pixel with highest signal.
      if (SignalMatrix[i][j] > HighestSig) {
	HighestSig = SignalMatrix[i][j];
	fHighestPix = fClusterSize;
      }
      ++fClusterSize;
      if (fClusterSize == MAXCLUSIZE) return;
    }
    ++ExploredPixels;
  }
}

/************************************************************************
 * TCluster::CalcProperties - Determine the cluster properties, such as *
 *                            pulse height, centers of gravity, etc.    *
 ************************************************************************/

void TCluster::CalcProperties(MatrixFloat SignalMatrix, unsigned short BorderPixel[PIX_X_DIM][PIX_Y_DIM],
			      MatrixFloat PixToCartX, MatrixFloat PixToCartY, float Weight,  
			      float SmallCircleRadius, float WideCircleRadius) {
  double XResid, YResid; 
  double A = 0.0, B = 0.0;
  double CosTh, SinTh;
  float MomX;
  int u, v;
  float x, y;       ;
  int i;
  fHighestCharge = 0;
  impactFlag = 0;
  for (i=0; i<fClusterSize; ++i) {
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    x = PixToCartX[u][v];
    y = PixToCartY[u][v];
    fPixelsCoordInCluster[i][0] = x;
    fPixelsCoordInCluster[i][1] = y;
    fPulseHeight += SignalMatrix[u][v];
    if(SignalMatrix[u][v] > fHighestCharge) fHighestCharge = SignalMatrix[u][v];
    if (BorderPixel[u][v]) fBorderCharge += SignalMatrix[u][v];  // Total cluster charge on border pixels.
    fCenterOfGravityX += x*SignalMatrix[u][v];
    fCenterOfGravityY += y*SignalMatrix[u][v];
   }
  if (fPulseHeight) {
    fCenterOfGravityX /= fPulseHeight;
    fCenterOfGravityY /= fPulseHeight;
  }    
  
  // *************** POLARISATION STUDIES ****************
  // This stuff needs large clusters!
  if (fClusterSize < 3) return;
  // Angle of main axis of cluster.
  // Calculate the angle (between -kPI/4 and kPI/4 ) that minimize fMomentumX for rotations around the baricenter.
  for (i=0; i<fClusterSize; ++i) {
    x = fPixelsCoordInCluster[i][0];
    y = fPixelsCoordInCluster[i][1];
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    XResid = x - fCenterOfGravityX;
    YResid = y - fCenterOfGravityY;
    A += SignalMatrix[u][v]*XResid*YResid;
    B += SignalMatrix[u][v]*(-XResid*XResid + YResid*YResid);
  }

  fTheta = -0.5*atan2(2.0*A,B);
  CosTh = cos(fTheta);
  SinTh = sin(fTheta);

  // Now calculate the principal momenta of the cluster.
  // Calculate Second and Third momenta along principal axes.
  fThirdMomentumX = 0;
  fThirdMomentumY = 0;
  for ( i=0; i<fClusterSize; ++i ) {
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    x = fPixelsCoordInCluster[i][0];
    y = fPixelsCoordInCluster[i][1];
    XResid = x - fCenterOfGravityX;
    YResid = y - fCenterOfGravityY;
    fMomentumX += float(SignalMatrix[u][v]*pow((CosTh*XResid + SinTh*YResid), 2.0));
    fMomentumY += float(SignalMatrix[u][v]*pow((-SinTh*XResid + CosTh*YResid), 2.0));
    fThirdMomentumX += float(SignalMatrix[u][v]*pow((CosTh*XResid + SinTh*YResid), 3.0));
    fThirdMomentumY += float(SignalMatrix[u][v]*pow((-SinTh*XResid + CosTh*YResid), 3.0));
  }
  if (fPulseHeight > 0.0) {
    fMomentumX /= fPulseHeight;
    fMomentumY /= fPulseHeight;
    fThirdMomentumX /= fPulseHeight;
    fThirdMomentumY /= fPulseHeight;
  }
  // At the moment theta represents the angle of the cluster axis ( major OR minor ) which lies in the range
  // -kPI/4 -> kPI/4.  Now that we can distinguish major and minor axes ( from the momenta ), we can translate
  // theta to represent the angle of just the MAJOR axis ( ranging from -kPI/2 to kPI/2 ).
  float TMomX;

  if (fMomentumX < fMomentumY) {
    MomX = fMomentumX;
    fMomentumX = fMomentumY;
    fMomentumY = MomX;
    TMomX = fThirdMomentumX;
    fThirdMomentumX = fThirdMomentumY;
    fThirdMomentumY = TMomX; 
    if (fTheta > 0.0) fTheta -= 0.5*kPI;
    else fTheta += 0.5*kPI;
    if (fTheta < 0.0)
      fThirdMomentumX = -fThirdMomentumX;
  }
  CosTh = cos(fTheta);
  SinTh = sin(fTheta);
  Shape = fMomentumX/fMomentumY;


  float projMax = -999999;
  float projMin = 999999;
  for ( i=0; i<fClusterSize; ++i ) {
    float projection = CosTh*fPixelsCoordInCluster[i][0]+SinTh*fPixelsCoordInCluster[i][1];
    if(projection>projMax) projMax = projection;
    if(projection<projMin) projMin = projection;
  }
  cluLenght = projMax - projMin;


  // Algorithm 2: evaluate baricenter of all the pixels ~2 stdv far from
  // the baricenter, checking that they lie on the "right side".

  float fPartialPHeight = 0;
  float fDistanceFromBaricenter = 0; 
  int   pixelcounter = 0;
  fImpactPosX = 0;
  fImpactPosY = 0;
  
  if (SmallCircleRadius && WideCircleRadius){
    for ( i=0; i<fClusterSize; ++i ) {
      u = fPixelsInCluster[i][0];
      v = fPixelsInCluster[i][1];
      x = fPixelsCoordInCluster[i][0];
      y = fPixelsCoordInCluster[i][1];
      XResid = x - fCenterOfGravityX;
      YResid = y - fCenterOfGravityY;
      if (fMomentumX != 0.0 && fThirdMomentumX != 0.0)
	{
	  fDistanceFromBaricenter = sqrt(XResid*XResid + YResid*YResid)/sqrt(fMomentumX);
	  if (fDistanceFromBaricenter > SmallCircleRadius && fDistanceFromBaricenter < WideCircleRadius)
	    {
	      if ((CosTh*XResid + SinTh*YResid)/fThirdMomentumX > 0.0)
		{
		  fImpactPosX += float(SignalMatrix[u][v]*x);
		  fImpactPosY += float(SignalMatrix[u][v]*y);
		  fPartialPHeight += float(SignalMatrix[u][v]);
		  impactFlag = 1;
		}
	    }
	}
    }
  }

  ////////////////////////////////////////////////////////////////////////////
  else {
  
    // Conditions for SmallRadius and WideRadius from MC (10 Oct 2005)
    float PH[14] = {500.,900.,1100.,1350.,1450.,1550.,1650.,1750.,1900.,2150.,2350.,2650.,3100.,999999.};
    float RMIN[13] ={0.5,0.5,1.3,2.5,1.9,1.9,1.3,2.3,2.7,1.7,1.7,2.5,2.5};
    float RMAX[13] = {1.,2.5,3.3,3.,2.4,3.9,3.3,4.3,3.7,2.7,2.7,4.5,3.5};
   
  // ==========>>>>> NEW Conditions for SmallRadius and WideRadius in accordance with parameters in MC /29 Nov. 2006 
  //  float PH[10] = {540.,670.,930.,1190.,1440.,1700.,1960.,2220.,2990.,99999.};
  //  float RMIN[10] ={0.4, 0.9, 1.1, 1.3, 1.5, 1.55, 1.65, 1.7, 2., 2.5};
  //  float RMAX[10] = {1., 1.5, 2.0, 2.3, 2.5, 2.7, 2.8, 3.0, 4.0, 4.};
  // ==========>>>>>===============================================================================================
 
    for (int index =0; index<13; index++) {
      if(fPulseHeight<=PH[index+1] && fPulseHeight>=PH[index]){
	index0 = index;
	break;
      }
    }
    //Starting point
    SmallCircleRadius = RMIN[index0];
    WideCircleRadius = RMAX[index0];                     // Implementazione di Francesco nell'analisi MC parte se SmallRadiuse WideRadius sono entrambi zero
    while(pixelcounter <= 4 && SmallCircleRadius > 0.2 ){// partendo da un SmallRadius fissato e dipendente dal PH, finche' non ho un numero di pixel 
      pixelcounter = 0;                                  // sufficiente (>=4) riduco SmallRadius (ogni volta di 0.2) fino ad un minimo di 0.2.
      fImpactPosX = 0;
      fImpactPosY = 0;
      fPartialPHeight = 0;
      impactFlag = 0;
      
      for ( i=0; i<fClusterSize; ++i ) {
	u = fPixelsInCluster[i][0];
	v = fPixelsInCluster[i][1];
	x = fPixelsCoordInCluster[i][0];
	y = fPixelsCoordInCluster[i][1];
	XResid = x - fCenterOfGravityX;
	YResid = y - fCenterOfGravityY;
	if (fMomentumX != 0.0 && fThirdMomentumX != 0.0)
	  {
	    fDistanceFromBaricenter = sqrt(XResid*XResid + YResid*YResid)/sqrt(fMomentumX);
	    if (fDistanceFromBaricenter > SmallCircleRadius && fDistanceFromBaricenter < WideCircleRadius 
		&& ((CosTh*XResid + SinTh*YResid)/fThirdMomentumX) > 0.)
	    {	    
	      pixelcounter++;
	      fImpactPosX += float(SignalMatrix[u][v]*x);
	      fImpactPosY += float(SignalMatrix[u][v]*y);
	      fPartialPHeight += float(SignalMatrix[u][v]);
	      impactFlag = 1;
	    }
	    
	  }
	else {
		fImpactPosX = fCenterOfGravityX;
		fImpactPosY = fCenterOfGravityY;
		fPartialPHeight = 1;
	}
      }// end loop on cluster!!
      
      SmallCircleRadius -= 0.2;
    }// while loop.
  }
  ///////////////////////////////////////////////////
 
  if(fPartialPHeight)
    {
      fImpactPosX /= fPartialPHeight;
      fImpactPosY /= fPartialPHeight;
    }
  else {
    fImpactPosX = fCenterOfGravityX;
    fImpactPosY = fCenterOfGravityY;
  }  

  // Again on Theta!
  // Now that we know the sign of the third momentum, we can even
  // distinguish the direction of the photoelectron (ranging from -kPI to kPI).
  if (fThirdMomentumX > 0){
    if (fTheta > 0) fTheta -= kPI;
    else fTheta += kPI;
  }
  // Try to use the reconstructed conversion point as to have a better estimate for Theta
  // To be implemented!
  fTheta2 = fTheta;
  // Evaluate new baricenter and new Pulse Height.
  float fBaricenter2X = 0.0;
  float fBaricenter2Y = 0.0;
  float fPulseHeight2 = 0.0;
  for (i=0; i<fClusterSize; ++i) {
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    x = PixToCartX[u][v];
    y = PixToCartY[u][v];
    float DistanceFromStart = sqrt((x-fImpactPosX)*(x-fImpactPosX) + (y-fImpactPosY)*(y-fImpactPosY));
    fPixelsCoordInCluster[i][0] = x;
    fPixelsCoordInCluster[i][1] = y;
    fPulseHeight2 += SignalMatrix[u][v]*PixelWeight(DistanceFromStart, Shape, fThirdMomentumX,Weight);
    fBaricenter2X += x*SignalMatrix[u][v]*PixelWeight(DistanceFromStart, Shape, fThirdMomentumX,Weight);
    fBaricenter2Y += y*SignalMatrix[u][v]*PixelWeight(DistanceFromStart, Shape, fThirdMomentumX,Weight);
  }
  if (fPulseHeight2) {
    fBaricenter2X /= fPulseHeight2;
    fBaricenter2Y /= fPulseHeight2;
  }
  // Angle of main axis of cluster (between -kPI/4 and kPI/4 ).
  double A2 = 0.0;
  double B2 = 0.0;
  double CosTh2, SinTh2;
  for (i=0; i<fClusterSize; ++i) {
    x = fPixelsCoordInCluster[i][0];
    y = fPixelsCoordInCluster[i][1];
    XResid = x - fBaricenter2X;
    YResid = y - fBaricenter2Y;
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    float DistanceFromStart = sqrt((x-fImpactPosX)*(x-fImpactPosX) + (y-fImpactPosY)*(y-fImpactPosY));
    A2 += SignalMatrix[u][v]*XResid*YResid*PixelWeight(DistanceFromStart, Shape, fThirdMomentumX,Weight);
    B2 += SignalMatrix[u][v]*(-XResid*XResid + YResid*YResid)*PixelWeight(DistanceFromStart, Shape, fThirdMomentumX,Weight);
  }

  fTheta2 = -0.5*atan2(2.0*A2,B2);
  CosTh2 = cos(fTheta2);
  SinTh2 = sin(fTheta2);
  // Now calculate the principal momenta of the cluster.
  float fMomentum2X = 0;
  float fMomentum2Y = 0;
  for ( i=0; i<fClusterSize; ++i ) {
    u = fPixelsInCluster[i][0];
    v = fPixelsInCluster[i][1];
    x = fPixelsCoordInCluster[i][0];
    y = fPixelsCoordInCluster[i][1];
    XResid = x - fBaricenter2X;
    YResid = y - fBaricenter2Y;
    fMomentum2X += float(SignalMatrix[u][v]*pow((CosTh2*XResid + SinTh2*YResid), 2.0));
    fMomentum2Y += float(SignalMatrix[u][v]*pow((-SinTh2*XResid + CosTh2*YResid), 2.0));
  }
  if (fPulseHeight2 > 0.0) {
    fMomentum2X /= fPulseHeight2;
    fMomentum2Y /= fPulseHeight2;
  }
  // At the moment theta represents the angle of the cluster axis ( major OR minor ) which lies in the range
  // -kPI/4 -> kPI/4.  Now that we can distinguish major and minor axes ( from the momenta ), we can translate
  // theta to represent the angle of just the MAJOR axis ( ranging from -kPI/2 to kPI/2 ).
  float Mom2X;
  if (fMomentum2X < fMomentum2Y) {
    Mom2X = fMomentum2X;
    fMomentum2X = fMomentum2Y;
    fMomentum2Y = Mom2X;
    if (fTheta2 > 0.0) fTheta2 -= 0.5*kPI;
    else fTheta2 += 0.5*kPI;
  }
  if (fabs(fTheta2 - fTheta) > kPI/2.0)
    {
      if (fTheta2 > 0) fTheta2 -= kPI;
      else fTheta2 += kPI;
    }
}

float TCluster::PixelWeight(float Distance, float Shape, float fThirdMomentumX, float WeightLengthScale){
  float Weight;
  float ds = 2;
  float dm = 0.001;
  float kWeight2 = 0.05;//0.070;
  //Weight = pow((1/(kWeightLengthScale + Distance)), kWeightIndex);
  //Set the Weight according to the shape and charge asimmetry of the cluster
  if (Shape <(1+ds) || (fThirdMomentumX > -dm && fThirdMomentumX < dm)) Weight = exp(-Distance/kWeight2);
  else Weight = exp(-Distance/WeightLengthScale);
  return Weight; 
}










