//---------------------------------------------------------------------------

#ifndef GPLCarCameraSetH
#define GPLCarCameraSetH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>

#include "GPLCarCamera.h"

enum eCameraSetType { CstCarCamSet, CstRollBarCam };

//---------------------------------------------------------------------------
class PACKAGE TGPLCarCameraSet : public TComponent
{
private:
    int a_version;    // used to identify changes in newer versions

    String a_caption;
    String a_comment;
    TShortCut a_activationKey;

    eCameraSetType a_type;

    TGPLCarCamera *a_camera[6];
    int a_selectedCamera;

public:
    __fastcall TGPLCarCameraSet(TComponent* Owner);
    virtual __fastcall ~TGPLCarCameraSet();

    void setValues(CarCameraValuesList *list);
    void getValues(CarCameraValuesList *list);

    TGPLCarCamera *getCamera(int index) const { return a_camera[index]; }
    TGPLCarCamera *getSelectedCamera() const { return a_camera[a_selectedCamera]; }

    String getEffect() const { return a_camera[0]->Effect; } // roll bar
    void setEffect(AnsiString effect) { a_camera[0]->Effect = effect; } // roll bar

__published:

    __property Name;

    __property eCameraSetType Type = { read=a_type, write=a_type };

    __property int Version = { read=a_version, write=a_version };
    __property String Caption = { read = a_caption, write = a_caption };
    __property String Comment = { read = a_comment, write = a_comment };
    __property TShortCut ActivationKey = { read = a_activationKey, write = a_activationKey };

    __property TGPLCarCamera *Camera0 = { read=a_camera[0], write=a_camera[0] };
    __property TGPLCarCamera *Camera1 = { read=a_camera[1], write=a_camera[1] };
    __property TGPLCarCamera *Camera2 = { read=a_camera[2], write=a_camera[2] };
    __property TGPLCarCamera *Camera3 = { read=a_camera[3], write=a_camera[3] };
    __property TGPLCarCamera *Camera4 = { read=a_camera[4], write=a_camera[4] };
    __property TGPLCarCamera *Camera5 = { read=a_camera[5], write=a_camera[5] };

    __property int SelectedCamera = { read=a_selectedCamera, write=a_selectedCamera };

};

//---------------------------------------------------------------------------
#endif
 