
#include "pMainGui.h"
#ifdef R__WIN32
      #include "MyUdpSocket.h"
#else
       #include "pUdpSocket.h"
#endif

class pUdpSocket;

pMainGui::pMainGui(const TGWindow *parent, UInt_t width, UInt_t height)
  : TGMainFrame(parent, width, height)
{
  HitDisplayFreq = 100; // display 2D raw map every 200 ev
  string tarray[] = {"PixelThr (adc):","EvDisp every:","Socket port:","Timeout (ms):"};
  string varray[] = {"10","10","50001","5000"};

  string tarray1[] = {"EvNum:", "BufferId:","WindowSize:","TStamp (s):","Loops/s:"};
  string varray1[] = {"0","0","0","0","0"};

  string tarray2[] = {"PixelThr (adc):","Rmin:","Rmax:","Weight:","HighClu only:","EvDisp every: ",
		      "Socket port:","Timeout (ms):"};
  string varray2[] = {"10","1.5","3.5","0.05","1","10","50001","5000"};
 

  if((!gSystem->AccessPathName("Settings.txt", kFileExists))){
    LoadSettings();
    for(int j=0; j<4; j++)varray[j] = varray01[j];
    for(int j=0; j<6; j++)varray2[j] = varray02[j];
    varray2[6] = varray01[2];
    varray2[7] = varray01[3];
  }

  m_canvasFrame = new TGHorizontalFrame(this, 800, 1200);

  TGTab *fTab = new TGTab(m_canvasFrame, 900, 600);
  fTab->Connect("Selected(int)", "pMainGui", this, "DoTab(int)");

  fL1 = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5);

  ///tab 1 ==========================================================================================
  tf = fTab->AddTab("RawData Monitor");
  fF1 = new TGCompositeFrame(tf, 600, 600, kHorizontalFrame);
  tf->AddFrame(fF1, fL1);

  fRightFrame = new TGCompositeFrame(fF1, 300, 600, kVerticalFrame | kRaisedFrame);
  fLeftFrame = new TGCompositeFrame(fF1, 300, 600, kVerticalFrame | kRaisedFrame);
  fF1->AddFrame(fLeftFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandY,2,2,2,2));
  fF1->AddFrame(fRightFrame, new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsExpandY,2,2,2,2));

  fLeftVerticalFrame = new TGGroupFrame(fLeftFrame, "Input", kVerticalFrame);  
  fLeftVerticalFrame->SetTitlePos(TGGroupFrame::kLeft); 
  fLeftFrame->AddFrame(fLeftVerticalFrame, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
  fLeftVerticalFrame->SetLayoutManager(new TGMatrixLayout(fLeftVerticalFrame, 0, 2, 10));  
  for (int j = 0; j < 4; j++) {
    TString buff = tarray[j];
    fLeftVerticalFrame->AddFrame(new TGLabel(fLeftVerticalFrame, new TGHotString(buff)));     
    TGTextBuffer *tbuf = new TGTextBuffer(10);
    TString vbuff = varray[j];
    tbuf->AddText(0, vbuff);
    TGTextEntry *tent  = new TGTextEntry(fLeftVerticalFrame, tbuf); 
    inTab1.push_back(tent);
    inBufTab1.push_back(tbuf);
    tent->Resize(90, tent->GetDefaultHeight());
    tent->SetFont("-adobe-courier-bold-r-*-*-12-*-*-*-*-*-iso8859-1");
    fLeftVerticalFrame->AddFrame(tent);
  }
  fLeftVerticalFrame->Resize(); // resize to default size 

  
  fLeftVerticalFrame1 = new TGGroupFrame(fLeftFrame, "Output", kVerticalFrame);  
  fLeftVerticalFrame1->SetTitlePos(TGGroupFrame::kLeft); 
  fLeftFrame->AddFrame(fLeftVerticalFrame1, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
  fLeftVerticalFrame1->SetLayoutManager(new TGMatrixLayout(fLeftVerticalFrame1, 0, 2, 10));  
  for (int j = 0; j < 5; j++) {
    TString buff = tarray1[j];
    fLeftVerticalFrame1->AddFrame(new TGLabel(fLeftVerticalFrame1, new TGHotString(buff)));     
    TGTextBuffer *tbuf = new TGTextBuffer(10);
    TString vbuff = varray1[j];
    tbuf->AddText(0, vbuff);
    TGTextEntry *tent  = new TGTextEntry(fLeftVerticalFrame1, tbuf);   
    outTab1.push_back(tent);
    outBufTab1.push_back(tbuf);
    tent->Resize(90, tent->GetDefaultHeight());
    tent->SetFont("-adobe-courier-bold-r-*-*-12-*-*-*-*-*-iso8859-1");
    tent->SetState(false);
    fLeftVerticalFrame1->AddFrame(tent);
  }

  feCanvas1 = new TRootEmbeddedCanvas("ec1", fRightFrame, 750, 650);
  fRightFrame->AddFrame(feCanvas1, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));


  ///tab 2 ==========================================================================================
  tf = fTab->AddTab("ReconData Monitor");
  fF2 = new TGCompositeFrame(tf, 60, 20, kHorizontalFrame);
  tf->AddFrame(fF2, fL1);

  TGCompositeFrame *fRightFrame2 = new TGCompositeFrame(fF2, 300, 600, kVerticalFrame | kRaisedFrame);
  TGCompositeFrame *fLeftFrame2 = new TGCompositeFrame(fF2, 300, 600, kVerticalFrame | kRaisedFrame);
  fF2->AddFrame(fLeftFrame2, new TGLayoutHints(kLHintsLeft | kLHintsExpandY,2,2,2,2));
  fF2->AddFrame(fRightFrame2, new TGLayoutHints(kLHintsLeft | kLHintsExpandX | kLHintsExpandY,2,2,2,2));

  TGGroupFrame *fLeftVerticalFrame2 = new TGGroupFrame(fLeftFrame2, "Input", kVerticalFrame);  
  fLeftVerticalFrame2->SetTitlePos(TGGroupFrame::kLeft); 
  fLeftFrame2->AddFrame(fLeftVerticalFrame2, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
  fLeftVerticalFrame2->SetLayoutManager(new TGMatrixLayout(fLeftVerticalFrame2, 0, 2, 10));  
  for (int j = 0; j < 8; j++) {
    TString buff = tarray2[j];
    fLeftVerticalFrame2->AddFrame(new TGLabel(fLeftVerticalFrame2, new TGHotString(buff)));     
    TGTextBuffer *tbuf = new TGTextBuffer(10);
    TString vbuff = varray2[j];
    tbuf->AddText(0, vbuff);
    TGTextEntry *tent  = new TGTextEntry(fLeftVerticalFrame2, tbuf); 
    inTab2.push_back(tent);
    inBufTab2.push_back(tbuf);
    tent->Resize(90, tent->GetDefaultHeight());
    tent->SetFont("-adobe-courier-bold-r-*-*-12-*-*-*-*-*-iso8859-1");
    fLeftVerticalFrame2->AddFrame(tent);
  }
  fLeftVerticalFrame2->Resize(); // resize to default size 

  string tarray3[] = {"BufferId:","WindowSize:","TimeStamp:","Dummy:"};
  string varray3[] = {"0","0","0","0"};
  TGGroupFrame *fLeftVerticalFrame3 = new TGGroupFrame(fLeftFrame2, "Output", kVerticalFrame);  
  fLeftVerticalFrame3->SetTitlePos(TGGroupFrame::kLeft); 
  fLeftFrame2->AddFrame(fLeftVerticalFrame3, new TGLayoutHints(kLHintsTop | kLHintsExpandX, 5, 5, 5, 5));
  fLeftVerticalFrame3->SetLayoutManager(new TGMatrixLayout(fLeftVerticalFrame3, 0, 2, 10));  
  for (int j = 0; j < 4; j++) {
    TString buff = tarray3[j];
    fLeftVerticalFrame3->AddFrame(new TGLabel(fLeftVerticalFrame3, new TGHotString(buff)));     
    TGTextBuffer *tbuf = new TGTextBuffer(10);
    TString vbuff = varray3[j];
    tbuf->AddText(0, vbuff);
    TGTextEntry *tent  = new TGTextEntry(fLeftVerticalFrame3, tbuf);   
    outTab2.push_back(tent);
    outBufTab2.push_back(tbuf);
    tent->Resize(90, tent->GetDefaultHeight());
    tent->SetFont("-adobe-courier-bold-r-*-*-12-*-*-*-*-*-iso8859-1");
    tent->SetState(false);
    fLeftVerticalFrame3->AddFrame(tent);
  }

  feCanvas2 = new TRootEmbeddedCanvas("PixMon", fRightFrame2, 750,650);
  fRightFrame2->AddFrame(feCanvas2,new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

  
  fL2 = new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY, 2, 2, 5, 1);
  m_canvasFrame->AddFrame(fTab, fL2);
  
  // make FullMon tab yellow 
  Pixel_t yellow;
  fClient->GetColorByName("yellow", yellow);
  TGTabElement *tabel = fTab->GetTabTab("FullRec Monitor");;
  tabel->ChangeBackground(yellow);
  
  AddFrame(m_canvasFrame, new TGLayoutHints(kLHintsCenterX| kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 0));

  // Bottom Frame  ==========================================================================================
  int sizeb = 60;
  TGLayoutHints *buttonLayout = new TGLayoutHints(kLHintsCenterX | kLHintsExpandY, 3, 3, 0, 0);
  m_buttonFrame = new TGCompositeFrame(this, 100, 100 ,kHorizontalFrame);
  m_buttonFrame->SetLayoutManager(new TGMatrixLayout(m_buttonFrame, 0, 5, 10));

  m_editButton = new TGTextButton(m_buttonFrame, "Info");
  m_buttonFrame->AddFrame(m_editButton, buttonLayout); 
  m_editButton->Connect("Clicked()", "pMainGui", this, "Myedit()");
  m_editButton->Resize(sizeb, m_editButton->GetDefaultHeight()); 
			
  m_resetButton = new TGTextButton(m_buttonFrame, "Reset");
  m_buttonFrame->AddFrame(m_resetButton, buttonLayout);  
  m_resetButton->Connect("Clicked()", "pMainGui", this, "Reset()");
  m_resetButton->Resize(sizeb, m_resetButton->GetDefaultHeight());
				  
  m_connectButton = new TGTextButton(m_buttonFrame, "Connect");
  m_buttonFrame->AddFrame(m_connectButton, buttonLayout); 
  m_connectButton->Connect("Clicked()", "pMainGui", this, "Connect()");
  m_connectButton->Resize(sizeb, m_connectButton->GetDefaultHeight());
  // Change background of fTestButton to green
  Pixel_t green;
  fClient->GetColorByName("green", green);
  m_connectButton->ChangeBackground(green);
					
  m_stopButton = new TGTextButton(m_buttonFrame, "Stop");
  m_buttonFrame->AddFrame(m_stopButton, buttonLayout); 
  m_stopButton->Connect("Clicked()", "pMainGui", this, "Stop()");
  m_stopButton->Resize(sizeb, m_stopButton->GetDefaultHeight());
  Pixel_t red;
  fClient->GetColorByName("red", red);
  m_stopButton->ChangeBackground(red);
						
  m_quitButton = new TGTextButton(m_buttonFrame, "Quit");
  m_buttonFrame->AddFrame(m_quitButton,buttonLayout);  
  m_quitButton->Connect("Clicked()", "pMainGui", this, "Quit()");
  m_quitButton->Resize(sizeb, m_quitButton->GetDefaultHeight());
   
  AddFrame(m_buttonFrame, new TGLayoutHints(kLHintsCenterX, 2, 2, 2, 2));

  SetWindowName("XPol monitor");
  MapSubwindows();
  Resize(GetDefaultSize());
  MapWindow();

  m_LMcanvas = feCanvas1->GetCanvas();
  m_LMcanvas->SetFillColor(42);
  m_LMcanvas->Divide(1, 2, 0.002,0.002);
  
  p0 = (TPad*) m_LMcanvas->GetPad(1);
  p0->Divide(2,1,0.002,0.002,10);

  p1 = (TPad*) m_LMcanvas->GetPad(2);
  p1->Divide(2, 1,0.002,0.002,10);
  m_LMcanvas->Update();

  m_FMcanvas = feCanvas2->GetCanvas();
  m_FMcanvas->SetFillColor(10);
  m_FMcanvas->Divide(2, 2);

  histosLM = false;
  histosFM = false;

  LMon = true;
  SetupHistograms();
  //gStyle->Reset();
  //gStyle->SetPalette(51);
  SetPaletteColdBlue();
  //SetHitBkBlack();
 
  Polarimeter = new TDetector();
}

pMainGui::~pMainGui()
{
  WriteSettings();
  gApplication->Terminate(0);
}

void pMainGui::Quit()
{
  WriteSettings();
  gApplication->Terminate(0);
}

void pMainGui::DoTab(int id){
  
  if(id==0){
    LMon = true;
  }
  if(id==1) {
    LMon = false;
  }
  SetupHistograms();
}

void pMainGui::Reset(){
   for(int i=2;i<4;i++)((TGTextEntry*)inTab1[i])->SetState(true);
  if(LMon == false){
    hPulseHeight->Reset();
    hHitMap2D->Reset();
    hTheta1Histo->Reset();
    hCluSize->Reset();
    UpdateHistos();
  }
  else {
    rawPhHisto->Reset();
    rawEv1D->Reset();
    cumulativetHisto->Reset();
    rawEv2D->Reset();
    UpdateHistos();
  }
 }

void pMainGui::Stop(){
  isRunning = false;
  m_connectButton->SetState(kButtonUp);
  m_quitButton->SetState(kButtonUp);
  m_editButton->SetState(kButtonUp);
  m_resetButton->SetState(kButtonUp);
  m_stopButton->SetState(kButtonDisabled);
  std::cout << "Client stopped!!" << std::endl;
  if(LMon==true)
    for(int i=0;i<2;i++)((TGTextEntry*)inTab1[i])->SetState(true);
  if(LMon==false)
    for(int i=0;i<6;i++)((TGTextEntry*)inTab2[i])->SetState(true);
}

void pMainGui::Myedit(){
  ed = new Editor(this, 500, 250);
  ed->LoadFile("info.dat",0,-1);
  ed->Popup();
}

void pMainGui::UpdateHistos(){
  if(LMon == false){
    m_FMcanvas->cd(1);
    hPulseHeight->Draw();
    m_FMcanvas->cd(2);
    hCluSize->Draw();
    m_FMcanvas->cd(3);  
    hTheta1Histo->Draw();
    m_FMcanvas->cd(4);  
    hHitMap2D->Draw();
    m_FMcanvas->cd();
    m_FMcanvas->Update();
  }
  else { 
    if(!(eventCnt%singleEvfreq)){  
      p0->cd(1);
      rawEv2D->Draw("colz");
      p1->cd(1);
      rawEv1D->Draw(); 
    }   
      if(!(eventCnt%HitDisplayFreq)){  
	p0->cd(2);
	cumulativetHisto->Draw("colz");
      }  
    p1->cd(2);
    rawPhHisto->Draw(); 
    m_LMcanvas->cd();
    m_LMcanvas->Update();
  }
}

void pMainGui::DrawHistos(){
 if(LMon == false){
    m_FMcanvas->cd(1);
    hPulseHeight->Draw();
    m_FMcanvas->cd(2);
    hCluSize->Draw();
    m_FMcanvas->cd(3);  
    hTheta1Histo->Draw();
    m_FMcanvas->cd(4);  
    hHitMap2D->Draw();
    m_FMcanvas->cd();
    m_FMcanvas->Update();
  }
  else {
    p0->cd(1);
    rawEv2D->Draw();
    p0->cd(2);
    cumulativetHisto->Draw();
    p1->cd(1);
    rawEv1D->Draw(); 
    p1->cd(2);
    rawPhHisto->Draw();  
    m_LMcanvas->cd();
    m_LMcanvas->Update();
    TPaveStats *s = (TPaveStats*)rawPhHisto->GetListOfFunctions()->FindObject("stats");
    s->SetX1NDC(0.55);
    p1->cd(2);
    rawPhHisto->Draw();  
    m_LMcanvas->cd();
    m_LMcanvas->Modified();
  }
}


void pMainGui::SetupHistograms()
{
  if(LMon == false){
    if(histosFM == false){
 
      hCluSize = new TH1F("ClusterSize", "ClusterSize", 50,0,500);  
      hCluSize->SetFillColor(60);
      hCluSize->GetXaxis()->SetTitle("Cluster size");

      hPulseHeight = new TH1F("PulseHeight", "PulseHeight", 300,0,30000); 
      hPulseHeight->SetFillColor(60);
      hPulseHeight->GetXaxis()->SetTitle("Pulse height (ADC counts)");
      
      hHitMap2D   = new TH2F("HitMap2D", "HitMap2D", 260, -7.8, 7.8, 260, -7.8, 7.8);
      hHitMap2D->SetFillColor(60);
      hHitMap2D->SetStats(false);
      hHitMap2D->GetXaxis()->SetTitle("ImpactX (mm)");
      hHitMap2D->GetYaxis()->SetTitle("ImpactY (mm)");
      
      hTheta1Histo = new TH1F("Theta1", "Angular Distribution - iteration 1", 100, -kPI, kPI);
      hTheta1Histo->SetFillColor(50);
      hTheta1Histo->GetXaxis()->SetTitle("Phi (rad)");
      hTheta1Histo->SetMinimum(0);
      histosFM = true;
    } 
    DrawHistos();
  }
  if (LMon == true){
    if(histosLM == false){

      rawEv2D = new TH2F("RawEv2D","2D Event Display",25,0,25,25,0,25);
      rawEv2D->SetStats(false);
      rawEv1D = new TH1F("RawEv1D","1D Raw Event",600,0,600);
      rawEv1D->SetStats(false);

      rawPhHisto = new TH1F("RawPulseHeight", "Pulse Height", 300,0,30000); 
      rawPhHisto->SetFillColor(60);
      rawPhHisto->GetXaxis()->SetTitle("Pulse height (ADC counts)");
      
      cumulativetHisto = new TH2F("CumulativeHisto", "Raw Hit Map ", 352, 0, 352, 300, 0, 300 );
      cumulativetHisto->SetStats(false);
      histosLM = true;
    }
    DrawHistos();
  }
}

void pMainGui::ReadSettings(){
  threshold = atoi(((TGTextBuffer*)inBufTab1[0])->GetString());
  singleEvfreq = atoi(((TGTextBuffer*)inBufTab1[1])->GetString());
  port = atoi(((TGTextBuffer*)inBufTab1[2])->GetString());
  to = atoi(((TGTextBuffer*)inBufTab1[3])->GetString());

  Polarimeter->SetThreshold(atof(((TGTextBuffer*)inBufTab2[0])->GetString()));
  Polarimeter->SetSmallRadius(atof(((TGTextBuffer*)inBufTab2[1])->GetString()));
  Polarimeter->SetWideRadius(atof(((TGTextBuffer*)inBufTab2[2])->GetString()));
  Polarimeter->SetWeight(atof(((TGTextBuffer*)inBufTab2[3])->GetString()));

  OneClu  = (bool)atoi(((TGTextBuffer*)inBufTab2[4])->GetString());
  HistDisplay = atoi(((TGTextBuffer*)inBufTab2[5])->GetString());
}

void pMainGui::WriteSettings(){
  settingOut.open("Settings.txt",ios::out);
  settingOut << "PixelThresh(LM): " << ((TGTextBuffer*)inBufTab1[0])->GetString() << endl;
  settingOut << "SingleEvfreq: " << ((TGTextBuffer*)inBufTab1[1])->GetString() << endl;
  settingOut << "ServerPort: " << ((TGTextBuffer*)inBufTab1[2])->GetString() << endl;
  settingOut << "TimeOut: " << ((TGTextBuffer*)inBufTab1[3])->GetString() << endl;
  
  settingOut << "PixelThresh(FM): " << ((TGTextBuffer*)inBufTab2[0])->GetString() << endl;
  settingOut << "Rmin: " << ((TGTextBuffer*)inBufTab2[1])->GetString() << endl;
  settingOut << "Rmax: " << ((TGTextBuffer*)inBufTab2[2])->GetString() << endl;
  settingOut << "Weight: " << ((TGTextBuffer*)inBufTab2[3])->GetString() << endl;
  settingOut << "HighClu: " << ((TGTextBuffer*)inBufTab2[4])->GetString() << endl;
  settingOut << "Displyfreq: " << ((TGTextBuffer*)inBufTab2[5])->GetString() << endl;  
  settingOut.close();
}

void pMainGui::LoadSettings(){  

  settingIn.open("Settings.txt",ios::in);
  for(int j=0; j<4;j++)
    settingIn >> varray01[j] >> varray01[j];
  for(int j=0; j<6;j++)
     settingIn >> varray02[j] >> varray02[j];
  settingIn.close(); 
}

void pMainGui::Connect()
{  
  ReadSettings();
  eventCnt = 0;
  m_connectButton->SetState(kButtonDisabled);
  m_quitButton->SetState(kButtonDisabled);
  m_editButton->SetState(kButtonDisabled);
  m_resetButton->SetState(kButtonDisabled);
  m_stopButton->SetState(kButtonUp);

  if(LMon==true){
    for(int i=0;i<4;i++)((TGTextEntry*)inTab1[i])->SetState(false);
    LightMon();
  }
  else {
    for(int i=0;i<8;i++)((TGTextEntry*)inTab2[i])->SetState(false);
    FullMon();
  }
}

void pMainGui::LightMon(){
  double sigOver;
  int status,tag,xmin,xmax,ymin,ymax,buffId;
  int dindex, maxEvsize;
  int nx,ny;
  int chan,signal;
  int buffId0, buffId1;
  unsigned short time1,time2;
  float timeStamp, timestamp0, timestamp1;
  float deltastamp;
  float rate;
  float dt = 8e-7; //(sec)
  isRunning = true; 
  pUdpSocket *m_udpSocket = new pUdpSocket();
  bool retvalue = m_udpSocket->connect(port,to);
  if(retvalue)std::cout << "Connected!!!!!!" << std::endl;
  else {
    delete m_udpSocket;
    return;
  }
  timestamp0 = 0;
  buffId0 = 0;
  timestamp1 = 1;
  buffId1 = 0;
  while(isRunning)
    {
      gSystem->ProcessEvents();
      dindex = 20;
      maxEvsize = 10000; 
      char datagram[11000];
      status = m_udpSocket->readDataGram(datagram, maxEvsize); 
      if(status == -1){
	box = new TGMsgBox(gClient->GetRoot(), gClient->GetRoot(),"Message", 
			     "TIMEOUT: connection closed!!!", kMBIconExclamation, kMBClose, &retval);
	break;
      }
      if(status == 0){
	box = new TGMsgBox(gClient->GetRoot(), gClient->GetRoot(),"Message", 
			     "ERROR: connection closed!!!", kMBIconExclamation, kMBClose, &retval);
	break;
      }

      tag =  UNPACK(datagram, 0);  
      if(tag != 65535) {
	std::cout << "WRONG TAG -> read next DataGram " << std::endl;
	continue;
      }
     
      xmin = UNPACK(datagram, 2);
      xmax = UNPACK(datagram, 4);
      ymin = UNPACK(datagram, 6);
      ymax = UNPACK(datagram, 8); 

      buffId = UNPACK(datagram, 10);
      tt.Form("%d",buffId);
      ((TGTextEntry*)outTab1[1])->Clear();
      ((TGTextBuffer*)outBufTab1[1])->AddText(0,tt);

      time1 = UNPACK(datagram, 12);
      time2 = UNPACK(datagram, 14);
      timeStamp = (time1 + time2*65534)*dt;
      tt.Form("%d",(int)timeStamp);
      ((TGTextEntry*)outTab1[3])->Clear();
      ((TGTextBuffer*)outBufTab1[3])->AddText(0,tt);

      nx = (xmax+1- xmin);
      ny = (ymax+1- ymin);
      winsize = nx*ny;
      tt.Form("%d",winsize);
      ((TGTextEntry*)outTab1[2])->Clear();
      ((TGTextBuffer*)outBufTab1[2])->AddText(0,tt);
      timestamp1 = timeStamp;
      buffId1 = buffId;
      deltastamp = timestamp1 - timestamp0;
      if (deltastamp)rate = (buffId1-buffId0)/deltastamp;
      else rate = 0;
      timestamp0 = timestamp1;
      buffId0 = buffId1;
      phRaw = 0;        
      X.clear();
      Y.clear();
      rawEvent.clear();
      rawchan.clear();    
      for (int jj=0; jj<NCHANS; jj++)RawChannelData[jj] = 0;
      for (int iy=ymin; iy<=ymax; iy++)
	{
	  for (int ix=xmin; ix<=xmax; ix++)
	    {    
	      sigOver = 1;
	      chan = PIX_Y_DIM * iy + ix;    
	      RawChannelData[chan] = UNPACK(datagram, dindex);
	      signal = (int)RawChannelData[chan];
	      dindex+=2; 	  
	      X.push_back((double)(ix-xmin));
	      Y.push_back((double)(iy-ymin));	
	      rawchan.push_back((double)chan);
	      //cumulativetHisto->Fill((float)iy ,(float)ix ,RawChannelData[chan]);
	      if(signal>=threshold) {
		cumulativetHisto->Fill((float)iy ,(float)ix ,RawChannelData[chan]);
		phRaw+=RawChannelData[chan];
		sigOver = (double)RawChannelData[chan];
	      }
	      rawEvent.push_back(sigOver);
	    }
	}
      //Fill histos..
      if(!(eventCnt%singleEvfreq)){
	if(rawEv1D) delete rawEv1D;
	rawEv1D = 0;
	rawEv1D = new TH1F("RawEv1D","1D Raw Event",winsize,rawchan[0],rawchan[winsize-1]);
	rawEv1D->SetLineColor(4);
	rawEv1D->SetStats(false);
	rawEv1D->FillN(winsize,&rawchan[0],&rawEvent[0]);
	
	if(rawEv2D) delete rawEv2D;
	rawEv2D = 0;
	rawEv2D = new TH2F("RawEv2D","2D Event Display",ny,0,ny,nx,0,nx);// inverted x with y respect to old online monitor 
	rawEv2D->SetStats(false);
	rawEv2D->FillN(winsize,&Y[0],&X[0],&rawEvent[0]);   // same coord system of offline
      }
      rawPhHisto->Fill(phRaw);
      tt.Form("%4.2f",rate);
      ((TGTextEntry*)outTab1[4])->Clear();
      ((TGTextBuffer*)outBufTab1[4])->AddText(0,tt);
      UpdateHistos();
      eventCnt++;
      tt.Form("%d",eventCnt);
      ((TGTextEntry*)outTab1[0])->Clear();
      ((TGTextBuffer*)outBufTab1[0])->AddText(0,tt);
    }
  isRunning = false;
  delete m_udpSocket;	
  Stop();
}


void pMainGui::FullMon(){
  isRunning = true;
  pUdpSocket *m_udpSocket = new pUdpSocket();
  bool retvalue = m_udpSocket->connect(port,to);
  if(retvalue)std::cout << "Connected!!!!!!" << std::endl;
  else {
    delete m_udpSocket;
    return;
  }
  while(isRunning)
    {
      gSystem->ProcessEvents();
      int dindex = 20;
      int maxEvsize = 10000; 
      char datagram[11000];
      int nclus;
      int status = m_udpSocket->readDataGram(datagram, maxEvsize); 
      if(status == -1){
	box = new TGMsgBox(gClient->GetRoot(), gClient->GetRoot(),"Message", 
			     "TIMEOUT: connection closed!!!", kMBIconExclamation, kMBClose, &retval);
	break;
      }
      if(status == 0){
	box = new TGMsgBox(gClient->GetRoot(), gClient->GetRoot(),"Message", 
			     "ERROR: connection closed!!!", kMBIconExclamation, kMBClose, &retval);
	break;
      }

      int tag =  UNPACK(datagram, 0);  
      if(tag != 65535) {
	std::cout << "WRONG TAG -> read next DataGram " << std::endl;
	continue;
      }
      int xmin = UNPACK(datagram, 2);
      int xmax = UNPACK(datagram, 4);
      int ymin = UNPACK(datagram, 6);
      int ymax = UNPACK(datagram, 8); 
      int buffId = UNPACK(datagram, 10);
      tt.Form("%d",buffId);
      ((TGTextEntry*)outTab2[0])->Clear();
      ((TGTextBuffer*)outBufTab2[0])->AddText(0,tt);

      unsigned short time1 = UNPACK(datagram, 12);
      unsigned short time2 = UNPACK(datagram, 14);

      double dt = 0.8; //(in microsec)
      int numPix = (xmax+1- xmin)*(ymax+1- ymin);
      tt.Form("%d",numPix);
      ((TGTextEntry*)outTab2[1])->Clear();
      ((TGTextBuffer*)outBufTab2[1])->AddText(0,tt);
      long int timeStamp = (long int)((time1 + time2*65534)*dt);
      tt.Form("%ld",timeStamp);
      ((TGTextEntry*)outTab2[2])->Clear();
      ((TGTextBuffer*)outBufTab2[2])->AddText(0,tt);

      for (int jj=0; jj<NCHANS; jj++)RawChannelData[jj] = 0;
      for (int iy=ymin; iy<=ymax; iy++)
	{
	  for (int ix=xmin; ix<=xmax; ix++)
	    {     
	      int chan = PIX_Y_DIM * iy + ix;       
	      RawChannelData[chan] = UNPACK(datagram, dindex);
	      dindex+=2;     
	    }
	}
     
      float PHmax = 0;
      int jmax = 0;
      nclus = Polarimeter->FindClusters(RawChannelData);      
      if(nclus>0){
	if(OneClu==true){
	  //find Max
	  for (int i=0; i<nclus; i++){
	    PHeight = Polarimeter->fAllClusts[i]->fPulseHeight;
	    if(PHeight>PHmax){
	      PHmax=PHeight;
	      jmax = i;
	    }
	  }
	  PHeight           = Polarimeter->fAllClusts[jmax]->fPulseHeight;
	  CluSize           = Polarimeter->fAllClusts[jmax]->fClusterSize;
	  //BaricenterX       = Polarimeter->fAllClusts[jmax]->fCenterOfGravityX;
	  //BaricenterY       = Polarimeter->fAllClusts[jmax]->fCenterOfGravityY;
	  ImpactX             = Polarimeter->fAllClusts[jmax]->fImpactPosX;
	  ImpactY             = Polarimeter->fAllClusts[jmax]->fImpactPosY;
	  Theta2            = Polarimeter->fAllClusts[jmax]->fTheta2;
	  hPulseHeight->Fill(PHeight);
	  hCluSize->Fill(CluSize);
	  //hHitMap2D->Fill(BaricenterX,BaricenterY);
	  hHitMap2D->Fill(ImpactX,ImpactY);
	  hTheta1Histo->Fill(Theta2);
	}
	else{
	  for (int i=0; i<nclus; i++){
	    PHeight           = Polarimeter->fAllClusts[i]->fPulseHeight;
	    CluSize           = Polarimeter->fAllClusts[jmax]->fClusterSize;
	    //BaricenterX       = Polarimeter->fAllClusts[i]->fCenterOfGravityX;
	    //BaricenterY       = Polarimeter->fAllClusts[i]->fCenterOfGravityY;
	    ImpactX             = Polarimeter->fAllClusts[i]->fImpactPosX;
	    ImpactY             = Polarimeter->fAllClusts[i]->fImpactPosY;
	    Theta2            = Polarimeter->fAllClusts[i]->fTheta2;
	    hPulseHeight->Fill(PHeight);
	    hCluSize->Fill(CluSize);
	    //hHitMap2D->Fill(BaricenterX,BaricenterY);
	    hHitMap2D->Fill(ImpactX,ImpactY);
	    hTheta1Histo->Fill(Theta2);	
	  }
	}
	eventCnt++;
      }
	  for (int i=0; i<nclus; i++){
	    delete Polarimeter->fAllClusts[i];  //free memory
	    Polarimeter->fAllClusts[i] = 0;
	  }
      if(!(eventCnt%HistDisplay))UpdateHistos();
    }
  isRunning = false;
  delete m_udpSocket;
  Stop();	      
}


void pMainGui::SetHitBkBlack(){
  cumulativetHisto->GetXaxis()->SetLabelColor(kWhite);
  cumulativetHisto->GetXaxis()->SetTitleColor(kWhite);
  cumulativetHisto->GetXaxis()->SetAxisColor(kWhite);
  cumulativetHisto->GetYaxis()->SetLabelColor(kWhite);
  cumulativetHisto->GetYaxis()->SetTitleColor(kWhite);
  cumulativetHisto->GetYaxis()->SetAxisColor(kWhite);
  p0->cd(2);
  gPad->SetFillColor(kBlack);
  m_LMcanvas->cd();
  m_LMcanvas->Update();
}

void pMainGui::SetHitBkWhite(){
  cumulativetHisto->GetXaxis()->SetLabelColor(kBlack);
  cumulativetHisto->GetXaxis()->SetTitleColor(kBlack);
  cumulativetHisto->GetXaxis()->SetAxisColor(kBlack);
  cumulativetHisto->GetYaxis()->SetLabelColor(kBlack);
  cumulativetHisto->GetYaxis()->SetTitleColor(kBlack);
  cumulativetHisto->GetYaxis()->SetAxisColor(kBlack);
  p0->cd(2);
  gPad->SetFillColor(kWhite);
}

void pMainGui::SetPaletteColdBlue(){
  const Int_t colNum = 89; 
  Int_t palette[colNum];
  Int_t pt;
   for (pt=0;pt<int(colNum-1)/2;pt++) {
     color = new TColor(501+pt
				,0
				,0
				,Float_t(pt)/((colNum - 3) / 2),"");
     palette[pt] = 501+pt;
   }
   for (; pt<int(colNum-1) ;pt++) {
     color = new TColor(501+pt
     				,Float_t(pt-(colNum -1) /2)/((colNum - 3) / 2)
				,Float_t(pt-(colNum -1) /2)/((colNum - 3) / 2)
				,1,"");
     palette[pt] = 501+pt;
   }
   gStyle->SetPalette(colNum,palette);
}

void pMainGui::SetPaletteHotRed(){
  const Int_t colNum = 89; 
  Int_t palette[colNum];
  Int_t pt;
   for (pt=0;pt<int(colNum-1)/2;pt++) {
     color = new TColor(501+pt
				,Float_t(pt)/((colNum - 3) / 2)
				,0
				,0,"");
     palette[pt] = 501+pt;
   }
   for (; pt<int(colNum-1) ;pt++) {
     color = new TColor(501+pt
     				,1
				,Float_t(pt-(colNum -1) /2)/((colNum - 3) / 2)
				,Float_t(pt-(colNum -1) /2)/((colNum - 3) / 2),"");
     palette[pt] = 501+pt;
   }
   gStyle->SetPalette(colNum,palette);
}

