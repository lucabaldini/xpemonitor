#ifndef PMAINGUI_H
#define PMAINGUI_H

#include "xPolMon.h"
#include "TDetector.h"
#include "TEditor.h"

class pMainGui : public TGMainFrame {
 private:
  ifstream settingIn;
  ofstream settingOut;
  float PHeight, CluSize, BaricenterX, BaricenterY, Theta2;  
  float ImpactX, ImpactY;
  float RawChannelData[NCHANS];
  int retval, buttons;
  int winsize, threshold;
  float phRaw;
  int eventCnt, singleEvfreq, HistDisplay ;
  int HitDisplayFreq;
  int port, to;
  bool OneClu;
  bool isRunning;
  bool histosLM, histosFM;
  bool LMon;

  vector <double> rawchan;
  vector <double> X;
  vector <double> Y;
  vector <double> rawEvent;
  double Xa[NCHANS];
  double Ya[NCHANS];
  double Event[NCHANS];
  vector <TGTextEntry*> inTab1;
  vector <TGTextBuffer*> inBufTab1;
  vector <TGTextEntry*> outTab1;
  vector <TGTextBuffer*> outBufTab1;
  vector <TGTextEntry*> inTab2;
  vector <TGTextBuffer*> inBufTab2;
  vector <TGTextEntry*> outTab2;
  vector <TGTextBuffer*> outBufTab2;
  vector <TPad*> LMpad;

  TDetector *Polarimeter;
  Editor *ed;
  TString tt;
  TString varray01[4], varray02[6];
  TRootEmbeddedCanvas *feCanvas1,*feCanvas2;
  TCanvas *m_FMcanvas, *m_LMcanvas;
  TCanvas *m_LMcanvas1,*m_LMcanvas2 ;
  TPad *p0, *p1;

  TColor *color;
  TGMsgBox *box;
  EMsgBoxIcon      icontype;
  TH1F *hCluSize;
  TH1F *hPulseHeight;
  TH1F *hTheta1Histo;
  TH2F *hHitMap2D;
  TH1F *numPixHisto;
  TH1F *rawPhHisto;
  TH1F *rawEv1D;
  TH2F *cumulativeHisto;
  TH2F *rawEv2D;

  TGCompositeFrame *m_buttonFrame;
  TGCompositeFrame *fRightFrame, *fLeftFrame;
  TGCompositeFrame *tf;
  TGCompositeFrame *fF1, *fF2;
  TGGroupFrame *fLeftVerticalFrame, *fLeftVerticalFrame1, *fLeftVerticalFrame0;
  TGHorizontalFrame *m_canvasFrame;

  TGLayoutHints *fL1, *fL2;
  TGLayoutHints *buttonLayout;
  TGTab *fTab;
  TGTabElement *fTabEl;
  TGStatusBar *status, *status2;
  TGTextButton *m_editButton;
  TGTextButton *m_connectButton;
  TGTextButton *m_stopButton;
  TGTextButton *m_quitButton;
  TGTextButton *m_resetButton;
  TPaveStats *st;
  TGraph *gr;
  TGraph2D *gr2d; 

 public:
  pMainGui(const TGWindow *parent, UInt_t width, UInt_t height);
  virtual ~pMainGui();
  void SetupHistograms();
  void DrawHistos();
  void UpdateHistos();
  void Connect();
  void Stop();
  void Quit();
  void Reset();
  void Myedit(); 
  void DoTab(int id);
  void FullMon();
  void LightMon();
  void SetPaletteColdBlue();
  void SetPaletteHotRed();
  void SetHitBkWhite();
  void SetHitBkBlack();
  void ReadSettings();
  void WriteSettings();
  void LoadSettings();
  void ExecEvent(int,int,int,TObject*);
  ClassDef(pMainGui, 0)
 };

#endif
