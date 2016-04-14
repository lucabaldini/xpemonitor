#ifndef XPOLMON_H
#define XPOLMON_H

// Standard Libraries.
#include <stdlib.h>
#include <iomanip>
#include <algorithm>
#include <time.h>
#include <string>
#include <iostream>
#include <cmath>

//ROOT staff
#include "Riostream.h"
#include <TROOT.h>
#include <TGFrame.h>
#include <TApplication.h>
#include <TGClient.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2F.h>
#include <TRandom.h>
#include <TGButton.h>
#include <TRootEmbeddedCanvas.h>
#include <TRint.h>
#include <TSystem.h>
#include <TGTextEdit.h>
#include <TGTextView.h>
#include <TVirtualX.h>
#include <TGMsgBox.h>
#include <TGTab.h>
#include <TGTextBuffer.h>
#include <TGTextEntry.h>
#include <TGLabel.h>
#include <TGStatusBar.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TColor.h>
#include <TStyle.h>
#include <TPaveStats.h>

#define PIX_X_DIM 352
#define PIX_Y_DIM 300
#define NCHANS 105600  //TOT_NUM_PIX
#define PITCH  0.050 
#define MAXNUMCLUSTS 200       
#define MAXCLUSIZE 400         
#define MINCLUSIZE 6           
#define kPI 3.14159

const int CHxCLU = 13200;
const int NCLU = 8; 

#define COMB(x1,x2) (((x2 & 0xff)<<8)|x1 & 0xff)
#define UNPACK(datagram, index) (COMB(datagram[index], datagram[index+1]))

typedef unsigned short MatrixUshort[PIX_X_DIM][PIX_Y_DIM];
typedef int MatrixInt[PIX_X_DIM][PIX_Y_DIM];
typedef float MatrixFloat[PIX_X_DIM] [PIX_Y_DIM];
#endif
