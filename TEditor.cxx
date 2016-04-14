#include "TEditor.h"

Editor::Editor(const TGWindow *main, UInt_t w, UInt_t h) :
    TGTransientFrame(gClient->GetRoot(), main, w, h)
{
   // Create an editor in a dialog.

   fEdit = new TGTextEdit(this, w, h, kSunkenFrame | kDoubleBorder);
   fL1 = new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 3, 3, 3, 3);
   AddFrame(fEdit, fL1);

   fOK = new TGTextButton(this, "  &OK  ");
   fL2 = new TGLayoutHints(kLHintsBottom | kLHintsCenterX, 0, 0, 5, 5);
   AddFrame(fOK, fL2);

   SetTitle();

   MapSubwindows();
   Resize();   // resize to default size

   // position relative to the parent's window
   Window_t wdum;
   int ax, ay;
   // editor covers right half of parent window
   gVirtualX->TranslateCoordinates(main->GetId(), GetParent()->GetId(),
                        0,
                        (Int_t)(((TGFrame *) main)->GetHeight() - fHeight) >> 1,
                        ax, ay, wdum);
   Move((((TGFrame *) main)->GetWidth() >> 1) + ax, ay);
   SetWMPosition((((TGFrame *) main)->GetWidth() >> 1) + ax, ay);
}

Editor::~Editor()
{
   // Delete editor dialog.

   delete fEdit;
   delete fOK;
   delete fL1;
   delete fL2;
}

void Editor::SetTitle()
{
  char title[256];
  sprintf(title, "%s","Parmeters Setting" );
  SetWindowName(title);
  SetIconName(title);
}

void Editor::Popup()
{
   // Show editor.

   MapWindow();
}

void Editor::LoadBuffer(const char *buffer)
{
   // Load a text buffer in the editor.

   fEdit->LoadBuffer(buffer);
}

void Editor::LoadFile(const char *file, Long_t start, Long_t lenght)
{
   // Load a file in the editor.

   fEdit->LoadFile(file);
   fname = file;
}

void Editor::CloseWindow()
{
   // Called when closed via window manager action.
  
   DeleteWindow();
}

Bool_t Editor::ProcessMessage(Long_t msg, Long_t, Long_t)
{
   // Process OK button.
  switch (GET_MSG(msg)) {
  case kC_COMMAND:
    switch (GET_SUBMSG(msg)) {
    case kCM_BUTTON:
      // Only one button and one action...
      fEdit->SaveFile(fname);
      DeleteWindow();
      break;
    default:
      break;
    }
    break;
    
      default:
	break;
  }
  
  return kTRUE;
}
