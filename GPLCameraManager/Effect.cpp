//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Effect.h"
#include "Options.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmEffect *frmEffect;
//---------------------------------------------------------------------------
__fastcall TfrmEffect::TfrmEffect(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmEffect::FormShow(TObject *Sender)
{
    a_changed = false;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmEffect::mmoEffectChange(TObject *Sender)
{
    a_changed = true;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmEffect::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    CanClose = false;
    if (a_changed && ModalResult==mrOk)
    {
        dlgOptions->ccmExParser->Expression->Text = mmoEffect->Text;
        if (!dlgOptions->ccmExParser->Check(false))
        {
            return;
        }
    }
    CanClose = true;
}

//---------------------------------------------------------------------------

