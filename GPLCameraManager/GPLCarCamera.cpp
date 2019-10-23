//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GPLCarCamera.h"
#include <math.hpp>

#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

//---------------------------------------------------------------------------
__fastcall TGPLCarCamera::TGPLCarCamera()
{
    a_values.xPos = 0;
    a_values.yPos = 0;
    a_values.zPos = 0;
    a_values.yaw = 0;
    a_values.pitch = 0;
    a_values.bank = 0;
    a_values.zoomAngle = 0;
    a_values.unknown1 = 0;
    a_values.unknown2 = 0;

    a_image = new TJPEGImage();
}

//---------------------------------------------------------------------------
__fastcall TGPLCarCamera::~TGPLCarCamera()
{
    if (a_image)
      delete a_image;
}

//---------------------------------------------------------------------------
void TGPLCarCamera::operator=( const TGPLCarCamera &camera )
{
    a_image->Assign(camera.a_image);

    a_values = camera.a_values;
    a_caption = camera.a_caption;
}

//---------------------------------------------------------------------------
String TGPLCarCamera::getInfo()
{
    return  "XPos=" + FloatToStrF(a_values.xPos,ffGeneral,3,2) +
            "\nYPos=" + FloatToStrF(a_values.yPos,ffGeneral,3,2) +
            "\nZPos=" + FloatToStrF(a_values.zPos,ffGeneral,3,2) +
            "\nYaw=" + FloatToStrF(RadToDeg(a_values.yaw),ffGeneral,3,2) +
            "\nPitch=" + FloatToStrF(RadToDeg(a_values.pitch),ffGeneral,3,2) +
            "\nBank=" + FloatToStrF(RadToDeg(a_values.bank),ffGeneral,3,2) +
            "\nZoomAngle=" + FloatToStrF(RadToDeg(a_values.zoomAngle),ffGeneral,3,2);
}

//---------------------------------------------------------------------------

void __fastcall TGPLCarCamera::setImage(TJPEGImage *image)
{
    a_image = image;
}

//---------------------------------------------------------------------------
TJPEGImage * __fastcall TGPLCarCamera::getImage()
{
    return a_image;
}

//---------------------------------------------------------------------------
void TGPLCarCamera::removeImage()
{
    delete a_image;
    a_image = new TJPEGImage;
}

//---------------------------------------------------------------------------

