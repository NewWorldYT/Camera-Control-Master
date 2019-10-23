//---------------------------------------------------------------------------

#ifndef DirectControlH
#define DirectControlH

#include "GPLCarCameraSet.h"


enum eViewMode {
    VmStatic,
    VmMouseRollBar,
    VmMousePitCam,
    VmEffectRollBar,
    VmEffectPitCam,
};

//---------------------------------------------------------------------------
class DirectControl : public TThread
{
private:
    // car values lists
    TGPLCarCameraSet  *a_pDesCamSet;
    AnsiString  a_desEffect;
    CarCameraValuesList a_actValuesList;
    CarCameraValues a_actPitValues;

    // reset requests
    bool a_resetCarCamRequest;
    bool a_resetPitCamRequest;
    bool a_finishRequest;

    // mode
    eViewMode a_desViewMode;
    eViewMode a_actViewMode;

    // accept new settings
    bool a_acceptSettings;

    // saved positions
    bool a_carcamSaved;
    bool a_pitcamSaved;
    CarCameraValuesList a_savedValuesList;
    CarCameraValues a_savedPitValues;

    // names
    AnsiString a_setName;
    AnsiString a_effectName;

    // GPL attachment for direct control
    bool a_attachedToGPL;
    HANDLE  a_hGplProcess;   // GPL process
    unsigned long a_startAddress; // start address of first camfile in GPL memory
    unsigned long a_pitAddress; // start address of pit camera in GPL memory
    HWND a_hwndGPL;

    // timing
    int a_frames;  // starting when new setting is done
    int a_prevFrames;  // previous number of frames
    bool a_singleStep;   // single step mode - timer is increased by steps

    float a_speed;  // speed of flying

    // screen info
    int a_screenWidth;
    int a_screenHeight;

    // previous deltas
    float a_lastDYaw;
    float a_lastDPitch;
    float a_lastDBank;
    float a_lastDX;
    float a_lastDY;
    float a_lastDZ;
    float a_lastDZoomAngle;

    float a_smooth;

    bool  a_mouseRightDown;
    bool  a_mouseLeftDown;

    bool  a_lookMode;
    bool  a_bankMode;
    bool  a_nascarMode;
    
    int a_speedSetting;
    int a_smoothSetting;

    virtual void __fastcall Execute(void);

    void doAction();

protected:
    // attach to the GPL process
    bool attachToGPL();

    void runEffectRollBar();
    void runEffectPitCam();
    void runMouseRollBar();
    void runMousePitCam();

public:
    DirectControl() :
        TThread(true),
        a_hGplProcess(0),
        a_startAddress(0),
        a_attachedToGPL(false),
        a_frames(0),
        a_carcamSaved(false),
        a_pitcamSaved(false),
        a_pDesCamSet(0),
        a_speed(0),
        a_smooth(0),
        a_resetCarCamRequest(false),
        a_resetPitCamRequest(false),
        a_hwndGPL(0),
        a_mouseRightDown(false),
        a_mouseLeftDown(false),
        a_lookMode(false),
        a_bankMode(false)

      {
          detachFromGPL();
      }

    void setDesCarCameraSet(AnsiString name, TGPLCarCameraSet *camSet) { a_setName = name; a_pDesCamSet = camSet; }
    void setDesEffect(AnsiString name, AnsiString effect) { a_effectName = name; a_desEffect = effect; }
    void setDesViewMode(eViewMode viewMode) { a_desViewMode = viewMode; }
    void resetCarCam() { a_resetCarCamRequest = true; }
    void resetPitCam() { a_resetPitCamRequest = true; }
    void acceptSettings(bool finish = false);

    void setMouseRightDown(bool down) { a_mouseRightDown = down; }
    void setMouseLeftDown(bool down) { a_mouseLeftDown = down; }

    // save and restore current camera positions
    void saveOriginalCarCam();
    void saveOriginalPitCam();
    void restoreOriginalCarCam();
    void restoreOriginalPitCam();

    void toggleSingleStep();
    void stepPressed();
    void showStatus();

    void setSpeed(int speed);
    void setSmooth(int smooth);

    void toggleLookMode() { a_lookMode = (a_lookMode) ? false : true; }
    void toggleBankMode() { a_bankMode = (a_bankMode) ? false : true; }

    void setLookMode(bool look) { a_lookMode = look; }
    void setBankMode(bool bank) { a_bankMode = bank; }
    void setNascarMode(bool nascar) { a_nascarMode = nascar; }

    // store actual camera positions in the saved positions form
    void storeRollBarCam();
    void storePitCam();

    bool isAttachedToGPL() const { return a_attachedToGPL; }
    void detachFromGPL();
};

//---------------------------------------------------------------------------

#endif
