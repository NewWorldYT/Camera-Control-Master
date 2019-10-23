//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GPLCarCameraSet.h"
#include <ComCtrls.hpp>

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TGPLCarCameraSet *)
{
    new TGPLCarCameraSet(NULL);
}

//---------------------------------------------------------------------------
__fastcall TGPLCarCameraSet::TGPLCarCameraSet(TComponent* Owner)
    : TComponent(Owner),
    a_selectedCamera(0),
    a_version(1),
    a_activationKey(hcNone),
    a_type(CstCarCamSet)
{
    for (int i = 0; i < 6; i++)
        a_camera[i] = new TGPLCarCamera();
}

//---------------------------------------------------------------------------
__fastcall TGPLCarCameraSet::~TGPLCarCameraSet()
{
    for (int i = 0; i < 6; i++)
        delete a_camera[i];
}

//---------------------------------------------------------------------------
void TGPLCarCameraSet::setValues(CarCameraValuesList *list)
{
    // roll bar always
    a_camera[0]->getCameraValues() = (*list)[3];

    if (Type == CstCarCamSet)
    {
        a_camera[1]->getCameraValues() = (*list)[0];
        a_camera[2]->getCameraValues() = (*list)[1];
        a_camera[3]->getCameraValues() = (*list)[4];
        a_camera[4]->getCameraValues() = (*list)[5];
        a_camera[5]->getCameraValues() = (*list)[2];
    }
}

//---------------------------------------------------------------------------
void TGPLCarCameraSet::getValues(CarCameraValuesList *list)
{
    // roll bar always
    (*list)[3] = a_camera[0]->getCameraValues();
    
    if (Type == CstCarCamSet)
    {
        (*list)[0] = a_camera[1]->getCameraValues();
        (*list)[4] = a_camera[3]->getCameraValues();
        (*list)[1] = a_camera[2]->getCameraValues();
        (*list)[5] = a_camera[4]->getCameraValues();
        (*list)[2] = a_camera[5]->getCameraValues();
    }
}


//---------------------------------------------------------------------------

