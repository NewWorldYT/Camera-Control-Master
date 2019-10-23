//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "Main.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TdlgAbout *dlgAbout;
//---------------------------------------------------------------------
__fastcall TdlgAbout::TdlgAbout(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TdlgAbout::lblSiteClick(TObject *Sender)
{
    ShellExecute(Handle,"open","http://www.pvdb.mbit.nl",0,0,SW_SHOW);
}
//---------------------------------------------------------------------------

void __fastcall TdlgAbout::FormShow(TObject *Sender)
{
    lblName->Caption = frmMain->Caption;
}
//---------------------------------------------------------------------------

