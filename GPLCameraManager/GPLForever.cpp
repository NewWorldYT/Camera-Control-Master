//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("GPLForever.res");
USEPACKAGE("vcl50.bpi");
USEUNIT("GPLCarCamera.cpp");
USEUNIT("GPLCarCameraSet.cpp");
USEPACKAGE("vcljpg50.bpi");
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
    return 1;
}
//---------------------------------------------------------------------------
