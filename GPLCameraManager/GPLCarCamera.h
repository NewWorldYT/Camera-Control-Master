//---------------------------------------------------------------------------

#ifndef GPLCarCameraH
#define GPLCarCameraH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <jpeg.hpp>
                             
struct CarCameraValues {
    float xPos;
    float yPos;
    float zPos;
    float yaw;
    float pitch;
    float bank;
    float zoomAngle;
    float unknown1;
    float unknown2;
};

typedef CarCameraValues CarCameraValuesList[6];

//---------------------------------------------------------------------------
class PACKAGE TGPLCarCamera : public TPersistent
{
private:
    CarCameraValues a_values;

    TJPEGImage *a_image;

    String a_caption;

    String a_effect;

public:
    __fastcall TGPLCarCamera();
    virtual __fastcall ~TGPLCarCamera();

    virtual void operator=( const TGPLCarCamera &camera );

    CarCameraValues &getCameraValues() { return a_values; }

    void __fastcall setImage(TJPEGImage *image);
    TJPEGImage * __fastcall getImage();

    String getInfo();

    void removeImage();

__published:
    __property TJPEGImage *Image = { read = getImage, write = setImage };

    __property float xPos = { read = a_values.xPos, write = a_values.xPos };
    __property float yPos = { read = a_values.yPos, write = a_values.yPos };
    __property float zPos = { read = a_values.zPos, write = a_values.zPos };
    __property float yaw = { read = a_values.yaw, write = a_values.yaw };
    __property float pitch = { read = a_values.pitch, write = a_values.pitch };
    __property float bank = { read = a_values.bank, write = a_values.bank };
    __property float zoomAngle = { read = a_values.zoomAngle, write = a_values.zoomAngle };
    __property float unknown1 = { read = a_values.unknown1, write = a_values.unknown1 };
    __property float unknown2 = { read = a_values.unknown2, write = a_values.unknown2 };

    __property String Caption = { read = a_caption, write = a_caption };
    __property String Effect = { read = a_effect, write = a_effect };
};



//---------------------------------------------------------------------------
#endif
 