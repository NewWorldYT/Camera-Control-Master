//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GPLForeverCCM.res");
USEFORM("Page.cpp", frmPage);
USEFORM("View.cpp", frmView);
USEFORM("Values.cpp", frmValues);
USEFORM("Name.cpp", dlgName);
USEFORM("Options.cpp", dlgOptions);
USEFORM("Properties.cpp", dlgProperties);
USEUNIT("GPLCarCamera.cpp");
USEUNIT("GPLCarCameraSet.cpp");
USEFORM("About.cpp", dlgAbout);
USEFORM("Effect.cpp", frmEffect);
USEUNIT("DirectControl.cpp");
USEFORM("Main.cpp", frmMain);
USEFORM("DistributeCarCamSet.cpp", dlgDistributeCarCamSet);
USEFORM("Comment.cpp", frmComment);
USEFORM("SavedPositions.cpp", frmSavedPositions);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "GPLForever Camera Control Master";
         Application->HelpFile = "GPLForeverCCM.hlp";
         Application->CreateForm(__classid(TfrmMain), &frmMain);
         Application->CreateForm(__classid(TfrmValues), &frmValues);
         Application->CreateForm(__classid(TdlgName), &dlgName);
         Application->CreateForm(__classid(TdlgOptions), &dlgOptions);
         Application->CreateForm(__classid(TdlgProperties), &dlgProperties);
         Application->CreateForm(__classid(TdlgAbout), &dlgAbout);
         Application->CreateForm(__classid(TfrmEffect), &frmEffect);
         Application->CreateForm(__classid(TdlgDistributeCarCamSet), &dlgDistributeCarCamSet);
         Application->CreateForm(__classid(TfrmComment), &frmComment);
         Application->CreateForm(__classid(TfrmSavedPositions), &frmSavedPositions);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
