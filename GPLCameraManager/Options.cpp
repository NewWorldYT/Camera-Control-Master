//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Options.h"
#include "Main.h"
#include <Inifiles.hpp>
//---------------------------------------------------------------------
#pragma link "ExPars"
#pragma link "Vars"
#pragma link "ExFuncs"
#pragma resource "*.dfm"
TdlgOptions *dlgOptions;
//---------------------------------------------------------------------
__fastcall TdlgOptions::TdlgOptions(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TdlgOptions::btnBrowseGPLPathClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "gpl.exe";
    dlgOpenGPLPath->InitialDir = edtGPLPath->Text;
    if (dlgOpenGPLPath->Execute())
        edtGPLPath->Text = dlgOpenGPLPath->FileName;
}

//---------------------------------------------------------------------------

void __fastcall TdlgOptions::btnBrowseNR2003PathClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "nr2003.exe";
    dlgOpenGPLPath->InitialDir = edtNR2003Path->Text;
    if (dlgOpenGPLPath->Execute())
        edtNR2003Path->Text = dlgOpenGPLPath->FileName;
}

//---------------------------------------------------------------------------
void __fastcall TdlgOptions::btnBrowseGTPPathClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "GTP_launcher.exe";
    dlgOpenGPLPath->InitialDir = edtGTPPath->Text;
    if (dlgOpenGPLPath->Execute())
        edtGTPPath->Text = dlgOpenGPLPath->FileName;
}

//---------------------------------------------------------------------------
void __fastcall TdlgOptions::FormCreate(TObject *Sender)
{
   TIniFile *ini;
   ini = new TIniFile(
      ChangeFileExt( Application->ExeName, ".INI" ) );
   edtGPLPath->Text =  ini->ReadString( "Files", "GPL", "C:\\Sierra\\gpl\\gpl.exe" );
   edtNR2003Path->Text =  ini->ReadString( "Files", "NR2003", "C:\\Papyrus\\NASCAR Racing 2003 Season\\nr2003.exe" );
   edtGTPPath->Text =  ini->ReadString( "Files", "RedlineGTP", "C:\\Program Files\\Redline GTP\\GTP_Launcher.exe" );
   edtVideoCapturePath->Text =  ini->ReadString( "Files", "VideoCapture", "" );
   edtImageCapturePath->Text =  ini->ReadString( "Files", "ImageCapture", "" );
   edtMovieEditorPath->Text =  ini->ReadString( "Files", "MovieEditor", "" );
   edtReplayAnalyserPath->Text =  ini->ReadString( "Files", "ReplayAnalyser", "" );

   initCamTagFiles();

   frmMain->Label1->Caption = ini->ReadString( "Best Links", "Title1", "Camera Control Master" );
   frmMain->Label1->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link1", "http://gplforever.m4driving.sm/" ));
/*   frmMain->Label2->Caption = ini->ReadString( "Best Links", "Title2", "GPL++ The Addons" );
   frmMain->Label2->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link2", "http://www.gplpp.com/" ));
   frmMain->Label3->Caption = ini->ReadString( "Best Links", "Title3", "Racesimcentral (forums)" );
   frmMain->Label3->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link3", "http://forum.racesimcentral.com/" ));
   frmMain->Label4->Caption = ini->ReadString( "Best Links", "Title4", "Ultimate GPL Linkspage" );
   frmMain->Label4->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link4", "http://members.rott.chello.nl/jvandam01/links.html" ));
   frmMain->Label5->Caption = ini->ReadString( "Best Links", "Title5", "GPLEA" );
   frmMain->Label5->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link5", "http://www.sportplanet.com/gpl/" ));
   frmMain->Label6->Caption = ini->ReadString( "Best Links", "Title6", "VROC" );
   frmMain->Label6->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link6", "http://didnt.doit.wisc.edu/vroc/" ));
   frmMain->Label7->Caption = ini->ReadString( "Best Links", "Title7", "GPLRank" );
   frmMain->Label7->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link7", "http://gplrank.schuerkamp.de/" ));
   frmMain->Label8->Caption = ini->ReadString( "Best Links", "Title8", "F2 Hotlaps and Setups" );
   frmMain->Label8->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link8", "http://jc.simracing.dk/default.htm" ));
   frmMain->Label9->Caption = ini->ReadString( "Best Links", "Title9", "Bruce's Stuff" );
   frmMain->Label9->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link9", "http://homepage.ntlworld.com/bruce.johnson/" ));
   frmMain->Label10->Caption = ini->ReadString( "Best Links", "Title10", "Bapom" );
   frmMain->Label10->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link10", "http://www.trilon.com/bapom" ));
   frmMain->Label11->Caption = ini->ReadString( "Best Links", "Title11", "RaceSim.net (forums)" );
   frmMain->Label11->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link11", "http://forum.racesim.net/" ));
   frmMain->Label12->Caption = ini->ReadString( "Best Links", "Title12", "GPL Movies" );
   frmMain->Label12->Tag = (unsigned int)new AnsiString(ini->ReadString( "Best Links", "Link12", "http://www.gplegends.net/movies/" ));

   frmMain->Label13->Caption = ini->ReadString( "Misc Links", "Title1", "Wild South Racing Team" );
   frmMain->Label13->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link1", "http://www.wsrt.de" ));
   frmMain->Label14->Caption = ini->ReadString( "Misc Links", "Title2", "CarCam Editor" );
   frmMain->Label14->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link2", "http://www.fortunecity.com/underworld/3d/797/" ));
   frmMain->Label15->Caption = ini->ReadString( "Misc Links", "Title3", "Dave Mack Race Reports" );
   frmMain->Label15->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link3", "http://www.geocities.com/dmackf2/" ));
   frmMain->Label16->Caption = ini->ReadString( "Misc Links", "Title4", "Brit League" );
   frmMain->Label16->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link4", "http://www.durber.co.uk/gpl/" ));
   frmMain->Label17->Caption = ini->ReadString( "Misc Links", "Title5", "Jimmi Bo's Bad Driving Guide" );
   frmMain->Label17->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link5", "http://home.clara.net/jimmibo/baddriving1.htm" ));
   frmMain->Label18->Caption = ini->ReadString( "Misc Links", "Title6", "sbdev - 3D Programming" );
   frmMain->Label18->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link6", "http://www.sbdev.pwp.blueyonder.co.uk" ));
   frmMain->Label19->Caption = ini->ReadString( "Misc Links", "Title7", "GPL the setup page" );
   frmMain->Label19->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link7", "http://stop.at/GPLsetups" ));
   frmMain->Label20->Caption = ini->ReadString( "Misc Links", "Title8", "Malcolm Edeson (Maxx)" );
   frmMain->Label20->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link8", "http://jc.simracing.dk/celebs/malcolm_edeson/malcolm.htm" ));
   frmMain->Label21->Caption = ini->ReadString( "Misc Links", "Title9", "GenlyAi's Page" );
   frmMain->Label21->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link9", "http://www.racesim.net/pagpers/balzus/" ));
   frmMain->Label22->Caption = ini->ReadString( "Misc Links", "Title10", "GPL Junk" );
   frmMain->Label22->Tag = (unsigned int)new AnsiString(ini->ReadString( "Misc Links", "Link10", "http://www.gpljunk.nildram.co.uk/~kclark/index.htm" ));

   frmMain->Label23->Caption = ini->ReadString( "User Links", "Title1", "Put user links in GPLForeverCCM.ini" );
   frmMain->Label23->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link1", "http://gplforever.m4driving.sm/" ));
   frmMain->Label24->Caption = ini->ReadString( "User Links", "Title2", "" );
   frmMain->Label24->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link2", "" ));
   frmMain->Label25->Caption = ini->ReadString( "User Links", "Title3", "" );
   frmMain->Label25->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link3", "" ));
   frmMain->Label26->Caption = ini->ReadString( "User Links", "Title4", "" );
   frmMain->Label26->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link4", "" ));
   frmMain->Label27->Caption = ini->ReadString( "User Links", "Title5", "" );
   frmMain->Label27->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link5", "" ));
   frmMain->Label28->Caption = ini->ReadString( "User Links", "Title5", "" );
   frmMain->Label28->Tag = (unsigned int)new AnsiString(ini->ReadString( "User Links", "Link6", "" ));
*/
   delete ini;
}

//---------------------------------------------------------------------------
void __fastcall TdlgOptions::FormDestroy(TObject *Sender)
{
   TIniFile *ini;
   ini = new TIniFile(ChangeFileExt( Application->ExeName, ".INI" ) );
   ini->WriteString ( "Files", "GPL", edtGPLPath->Text );
   ini->WriteString ( "Files", "NR2003", edtNR2003Path->Text );
   ini->WriteString ( "Files", "RedlineGTP", edtGTPPath->Text );
   ini->WriteString ( "Files", "VideoCapture", edtVideoCapturePath->Text );
   ini->WriteString ( "Files", "ImageCapture", edtImageCapturePath->Text );
   ini->WriteString ( "Files", "MovieEditor", edtMovieEditorPath->Text );
   ini->WriteString ( "Files", "ReplayAnalyser", edtReplayAnalyserPath->Text );

//   ini->WriteString ( "User Links", "Title1", frmMain->Label23->Caption );
//   ini->WriteString ( "User Links", "Link1", *((AnsiString *)frmMain->Label23->Tag) );

   delete ini;
}


//---------------------------------------------------------------------------

void __fastcall TdlgOptions::btnBrowseVideoCaptureClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "";
    dlgOpenGPLPath->InitialDir = edtVideoCapturePath->Text;
    if (dlgOpenGPLPath->Execute())
        edtVideoCapturePath->Text = dlgOpenGPLPath->FileName;
}

//---------------------------------------------------------------------------

void __fastcall TdlgOptions::btnBrowseScreenCaptureClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "";
    dlgOpenGPLPath->InitialDir = edtImageCapturePath->Text;
    if (dlgOpenGPLPath->Execute())
        edtImageCapturePath->Text = dlgOpenGPLPath->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TdlgOptions::btnBrowseMovieEditorClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "";
    dlgOpenGPLPath->InitialDir = edtMovieEditorPath->Text;
    if (dlgOpenGPLPath->Execute())
        edtMovieEditorPath->Text = dlgOpenGPLPath->FileName;
}
//---------------------------------------------------------------------------

void __fastcall TdlgOptions::btnBrowseReplayAnalyserClick(TObject *Sender)
{
    dlgOpenGPLPath->FileName = "";
    dlgOpenGPLPath->InitialDir = edtReplayAnalyserPath->Text;
    if (dlgOpenGPLPath->Execute())
        edtReplayAnalyserPath->Text = dlgOpenGPLPath->FileName;
}
//---------------------------------------------------------------------------


void TdlgOptions::initCamTagFiles()
{
    AnsiString camfilePath;
    AnsiString srcPath;

    TSearchRec sr;

    // find all directories in the series dir (for NR2003)
    AnsiString path = ExtractFilePath(dlgOptions->edtNR2003Path->Text) + "series\\";
    if (FindFirst(path + "*.*", faDirectory, sr) == 0)
    {
        do
        {
            if ((sr.Attr & faDirectory) == faDirectory)
            {
                if (sr.Name != "." && sr.Name != "..")
                {
                    camfilePath = path + sr.Name+"\\pacecar.cam";
                    srcPath = ExtractFilePath(Forms::Application->ExeName) + "pacecar.cam";

                    CopyFile(srcPath.c_str(),
                             camfilePath.c_str(),
                             false); 	// force copy , necessary to have the same in all dirs
                }
            }
        }   while (FindNext(sr) == 0);
        FindClose(sr);
    }


    // find all directories in the series dir (for GTP)
    path = ExtractFilePath(dlgOptions->edtGTPPath->Text) + "series\\";
    if (FindFirst(path + "*.*", faDirectory, sr) == 0)
    {
        do
        {
            if ((sr.Attr & faDirectory) == faDirectory)
            {
                if (sr.Name != "." && sr.Name != "..")
                {
                    camfilePath = path + sr.Name+"\\pacecar.cam";
                    srcPath = ExtractFilePath(Forms::Application->ExeName) + "pacecar.cam";

                    CopyFile(srcPath.c_str(),
                             camfilePath.c_str(),
                             false); 	// force copy , necessary to have the same in all dirs
                }
            }
        }   while (FindNext(sr) == 0);
        FindClose(sr);
    }


    camfilePath = ExtractFilePath(dlgOptions->edtGPLPath->Text) + "cars\\cars67\\brabham\\brabham.cam";
    srcPath = ExtractFilePath(Forms::Application->ExeName) + "brabham.cam";

    CopyFile(srcPath.c_str(),
             camfilePath.c_str(),
             true); 	// fail if file exists
}

//---------------------------------------------------------------------------

void __fastcall TdlgOptions::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    initCamTagFiles();
}
//---------------------------------------------------------------------------


