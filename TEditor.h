#ifndef TEDITOR_HH
#define TEDITOR_HH
#include "xPolMon.h"

class Editor : public TGTransientFrame {

private:
  TString fname;
  TGTextEdit       *fEdit;   // text edit widget
  TGTextButton     *fOK;     // OK button
  TGLayoutHints    *fL1;     // layout of TGTextEdit
  TGLayoutHints    *fL2;     // layout of OK button
  
 public:
  Editor(const TGWindow *main, UInt_t w, UInt_t h);
  virtual ~Editor();
  
  void   LoadBuffer(const char *buffer );
  void   LoadFile(const char *file, Long_t start, Long_t lenght);
  
  TGTextEdit *GetEditor() const { return fEdit; }
  
  void   SetTitle();
  void   Popup();
  virtual void   CloseWindow();
  virtual Bool_t ProcessMessage(Long_t msg, Long_t parm1, Long_t parm2);
};

#endif
