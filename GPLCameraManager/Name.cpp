//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Name.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TdlgName *dlgName;
//---------------------------------------------------------------------
__fastcall TdlgName::TdlgName(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TdlgName::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if (ModalResult==mrOk)
    {
        edtName->Text = edtName->Text.Trim();
        if (edtName->Text == "")
        {
            MessageDlg("Empty name is not allowed!", mtInformation, TMsgDlgButtons() << mbOK, 0);
            CanClose = false;
            return;
        }
    }
    CanClose = true;
}
//---------------------------------------------------------------------------
eCameraSetType TdlgName::getType() const
{
    if (radCarCamSet->Checked)
      return CstCarCamSet;
    else
      return CstRollBarCam;
}

