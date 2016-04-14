#include "TPixy.h"
#include "TMainGUI_new_v2.h"

TMainGUI *theGUI;
//TRint *theApp;


int main(int argc, char **argv) {
  TRint theApp("Pixy", &argc, argv);
  //theApp = new TRint("Pixy", 0, 0);
  if (gROOT->IsBatch()) {
    fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
    return 1;
  }
  theGUI = new TMainGUI(gClient->GetRoot(), 520, 320);
  theApp.Run();
  gSystem->ProcessEvents();
  return (0);
}
