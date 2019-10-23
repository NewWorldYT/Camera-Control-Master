//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Comment.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmComment *frmComment;
//---------------------------------------------------------------------------
__fastcall TfrmComment::TfrmComment(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmComment::FormShow(TObject *Sender)
{
    a_changed = false;    
}
//---------------------------------------------------------------------------
void __fastcall TfrmComment::mmoCommentChange(TObject *Sender)
{
    a_changed = true;    
}
//---------------------------------------------------------------------------
