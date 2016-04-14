
#include "xPolMon.h"
#include "pMainGui.h"

pMainGui *theGUI;

int main(int argc, char**argv){
  TRint theApp("Monitor", &argc, argv);
  if (gROOT->IsBatch()) {
    fprintf(stderr, "%s: cannot run in batch mode\n", argv[0]);
    return 1;
  }
  theGUI = new pMainGui(gClient->GetRoot(), 600, 200);
  theApp.Run();
  return 0;
}
