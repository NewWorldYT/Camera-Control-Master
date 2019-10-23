//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DirectControl.h"
#include "Options.h"
#include "Main.h"
#include "Page.h"
#include "Options.h"
#include "SavedPositions.h"
#include <math.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)

static char buf[0x100000];
unsigned long baseAddress;

//---------------------------------------------------------------------------
void DirectControl::acceptSettings(bool finish)
{
    if (finish)
    {
        // make saved cameras invalid
        a_carcamSaved = false;
        a_pitcamSaved = false;
        a_desViewMode = VmStatic;
    }
    a_acceptSettings = true;
    Suspended = false;
}

//---------------------------------------------------------------------------
void DirectControl::stepPressed()
{
    if (a_singleStep)
    {
        a_frames++;
        doAction();
    }
}

//---------------------------------------------------------------------------
void DirectControl::toggleSingleStep()
{
    if (a_singleStep)
    {
        a_singleStep = false;
        Suspended = false;
    }
    else
        a_singleStep = true;
    showStatus();
}

//---------------------------------------------------------------------------
bool DirectControl::attachToGPL()
{
    DWORD count;

    if (a_nascarMode)
        baseAddress = 0xC30000;    //NR2003
    else
        baseAddress = 0x5F0000;    //GPL

    a_hwndGPL = GetForegroundWindow();

    char title[100];
    GetWindowText(
        a_hwndGPL,	// handle of window or control with text
        title,	// address of buffer for text
        99 	// maximum number of characters to copy
    );

    if (a_nascarMode)
    {
        if (AnsiString(title) != "NR2003")
        {
            a_hwndGPL = 0;
            return false;
        }
    }
    else
    {
        if (AnsiString(title) != "Papyrus Window")
        {
            a_hwndGPL = 0;
            return false;
        }
    }

    DWORD dwProcessId;

    GetWindowThreadProcessId(a_hwndGPL, &dwProcessId);

    a_hGplProcess = OpenProcess(
        PROCESS_ALL_ACCESS,	// access flag
        false,	// handle inheritance flag
        dwProcessId 	// process identifier
    );

    bool result = ReadProcessMemory(
        a_hGplProcess,	// handle of the process whose memory is read
        (void *)(baseAddress),	// address to start reading
        &buf,	// address of buffer to place read data
        sizeof(buf),	// number of bytes to read
        &count 	// address of number of bytes read
    );

    if (result)
    {
        // import brabham camfile
        TGPLCarCameraSet *camSet = new TGPLCarCameraSet(0);
        AnsiString camfilePath;
        if (frmMain->cbxGameSelector->ItemIndex == 1)
            camfilePath = ExtractFilePath(dlgOptions->edtNR2003Path->Text) + "series\\cup\\pacecar.cam";
        else if (frmMain->cbxGameSelector->ItemIndex == 2)
            camfilePath = ExtractFilePath(dlgOptions->edtGTPPath->Text) + "series\\RDgtp\\pacecar.cam";
        else
            camfilePath = ExtractFilePath(dlgOptions->edtGPLPath->Text) + "cars\\cars67\\brabham\\brabham.cam";
        try
        {
            frmMain->importGPLCamfileToFile(camSet, camfilePath);
        }
        catch(...)
        {
            delete camSet;
            return false;
        }

        // brabham file imported, now search for tag
        union __Test
        {
            float floatVal;
            unsigned long val;
        };

        __Test xpos;
        __Test ypos;
        __Test zpos;

        camSet->getValues(&a_actValuesList);

        xpos.floatVal = a_actValuesList[0].xPos;
        ypos.floatVal = a_actValuesList[0].yPos;
        zpos.floatVal = a_actValuesList[0].zPos;

        delete camSet;

        unsigned long *pMemVal;
        for (int i = 0; i < sizeof(buf)-100; i++)
        {
            pMemVal = (unsigned long *)&(buf[i]);
            if (pMemVal[0] == xpos.val && pMemVal[1] == ypos.val && pMemVal[2] == zpos.val)
            {
                a_startAddress = baseAddress+i;
                if (frmMain->cbxGameSelector->ItemIndex == 1 || frmMain->cbxGameSelector->ItemIndex == 2)
                    a_pitAddress = a_startAddress-0xD8;
                else
                    a_pitAddress = a_startAddress+(7*sizeof(a_actValuesList))+39*56*4+8;

                a_attachedToGPL = true;

                return true;
            }
        }
    }
    return false;
}

//---------------------------------------------------------------------------
void DirectControl::saveOriginalCarCam()
{
    if (!a_carcamSaved)
    {
        ReadProcessMemory(
            a_hGplProcess,	// handle of the process whose memory is written
            (void *)(a_startAddress),	// address to start reading
            &a_actValuesList,
            sizeof(a_actValuesList),
            0 );

        memcpy(a_savedValuesList, a_actValuesList, sizeof(a_savedValuesList) );
        a_carcamSaved = true;
    }
}

//---------------------------------------------------------------------------
void DirectControl::restoreOriginalCarCam()
{
    if (a_carcamSaved)
        memcpy(a_actValuesList, a_savedValuesList, sizeof(a_savedValuesList) );
}

//---------------------------------------------------------------------------
void DirectControl::saveOriginalPitCam()
{
    if (!a_pitcamSaved)
    {
        ReadProcessMemory(
            a_hGplProcess,	// handle of the process whose memory is written
            (void *)(a_pitAddress),	// address to start reading
            &a_actPitValues,
            sizeof(a_actPitValues),
            0 );

        memcpy(&a_savedPitValues, &a_actPitValues, sizeof(a_savedPitValues) );
        a_pitcamSaved = true;
    }
}

//---------------------------------------------------------------------------
void DirectControl::restoreOriginalPitCam()
{
    if (a_pitcamSaved)
        memcpy(&a_actPitValues, &a_savedPitValues, sizeof(a_savedPitValues) );
}

//---------------------------------------------------------------------------
void __fastcall DirectControl::Execute()
{
    Priority = tpHighest;

    while ( !Terminated )
    {
        if (!a_attachedToGPL)
            attachToGPL();

        if (a_attachedToGPL)
        {
            if (a_acceptSettings)
            {
                 a_frames = 1;
                 a_prevFrames = 0;
                 a_acceptSettings = false;
                 a_actViewMode = a_desViewMode;

                 if (a_hwndGPL != GetForegroundWindow())
                 {
                     detachFromGPL();
                     continue;
                 }
                 showStatus();

                 // check for new set
                 if (a_pDesCamSet)
                 {
                     // use it as the saved and restore it to the actual
                     a_pDesCamSet->getValues(&a_savedValuesList);
                     a_carcamSaved = true;
                     a_pDesCamSet = 0;
                     restoreOriginalCarCam();
                 }

                 // check for new effect
                 if (a_desEffect != "")
                 {
                     dlgOptions->ccmExParser->Expression->Text = a_desEffect;
                     a_desEffect = "";
                 }

                 if (a_resetCarCamRequest)
                 {
                     restoreOriginalCarCam();
                     a_resetCarCamRequest = false;
                 }

                 if (a_resetPitCamRequest)
                 {
                     restoreOriginalPitCam();
                     a_resetPitCamRequest = false;
                 }

                 // init mouse control
                 if (a_actViewMode == VmMouseRollBar)
                 {
                     saveOriginalCarCam();

                     a_screenWidth = Screen->Width;
                     a_screenHeight = Screen->Height;
                     SetCursorPos(a_screenWidth/2,a_screenHeight/2);

                     a_lastDYaw = 0;
                     a_lastDPitch = 0;
                     a_lastDBank = 0;
                     a_lastDX = 0;
                     a_lastDY = 0;
                     a_lastDZ = 0;
                     a_lastDZoomAngle = 0;
                 }

                 // init pit cam control
                 if (a_actViewMode == VmMousePitCam)
                 {
                     saveOriginalPitCam();

                     a_screenWidth = Screen->Width;
                     a_screenHeight = Screen->Height;
                     SetCursorPos(a_screenWidth/2,a_screenHeight/2);

                     a_lastDYaw = 0;
                     a_lastDPitch = 0;
                     a_lastDBank = 0;
                     a_lastDX = 0;
                     a_lastDY = 0;
                     a_lastDZ = 0;
                     a_lastDZoomAngle = 0;
                 }

                 // init effect
                 if (a_actViewMode == VmEffectRollBar)
                 {
                     saveOriginalCarCam();

                     dlgOptions->ccmEPVarsFRAMES->Value = a_frames;
                     dlgOptions->ccmEPVarsX->Value     = a_actValuesList[3].xPos;
                     dlgOptions->ccmEPVarsY->Value     = a_actValuesList[3].yPos;
                     dlgOptions->ccmEPVarsZ->Value     = a_actValuesList[3].zPos;
                     dlgOptions->ccmEPVarsYAW->Value   = a_actValuesList[3].yaw;
                     dlgOptions->ccmEPVarsPITCH->Value = a_actValuesList[3].pitch;
                     dlgOptions->ccmEPVarsBANK->Value  = a_actValuesList[3].bank;
                     dlgOptions->ccmEPVarsZOOM->Value  = a_actValuesList[3].zoomAngle;
                 }

                 // init effect
                 if (a_actViewMode == VmEffectPitCam)
                 {
                     saveOriginalPitCam();

                     dlgOptions->ccmEPVarsFRAMES->Value = a_frames;
                     dlgOptions->ccmEPVarsX->Value     = a_actPitValues.xPos;
                     dlgOptions->ccmEPVarsY->Value     = a_actPitValues.yPos;
                     dlgOptions->ccmEPVarsZ->Value     = a_actPitValues.zPos;
                     dlgOptions->ccmEPVarsYAW->Value   = a_actPitValues.yaw;
                     dlgOptions->ccmEPVarsPITCH->Value = a_actPitValues.pitch;
                     dlgOptions->ccmEPVarsBANK->Value  = a_actPitValues.bank;
                     dlgOptions->ccmEPVarsZOOM->Value  = a_actPitValues.zoomAngle;
                 }
            }

            doAction();

            // increase frame counter if not single step
            if (!a_singleStep)
               a_frames++;

        }

        if (a_attachedToGPL == false || a_actViewMode == VmStatic || a_singleStep )
        {
            Suspended = true;
        }
        else
            Sleep(1000/36);
     }
}

//---------------------------------------------------------------------------
void  DirectControl::doAction()
{
    if (!a_attachedToGPL)
      return;

    // do action for each new frame dependent on mode
    switch(a_actViewMode)
    {
        case VmEffectRollBar:
            runEffectRollBar();
            break;
        case VmEffectPitCam:
            runEffectPitCam();
            break;
        case VmMouseRollBar:
            runMouseRollBar();
            break;
        case VmMousePitCam:
            runMousePitCam();
            break;
    }

    if (a_actViewMode == VmMousePitCam || a_actViewMode == VmEffectPitCam)
    {
        // write pitcam
        if (!WriteProcessMemory(
              a_hGplProcess,	// handle of the process whose memory is written
              (void *)(a_pitAddress),	// address to start reading
              &a_actPitValues,
              sizeof(a_actPitValues),
              0 ))
        {
            detachFromGPL();
        }
    }
    else
    {
        if (frmMain->cbxGameSelector->ItemIndex == 1 || frmMain->cbxGameSelector->ItemIndex == 2)
        {
            // write in memory for each car (9 cars, skip 2,3 and 4) NR2003
            for (int i=0; i<20; i++)
            {
//                if (i == 1 || i == 2 || i == 3)
//                    continue;
                if (!WriteProcessMemory(
                      a_hGplProcess,	// handle of the process whose memory is written
                      (void *)(a_startAddress+(i*sizeof(a_actValuesList))),	// address to start reading
                      &(a_actValuesList[0]),
                      sizeof(a_actValuesList),
                      0 ))
                {
                    detachFromGPL();
                    break;
                }
            }
        }
        else
        {
            // write in memory for each car (7 cars) GPL
            for (int i=0; i<7; i++)
            {
                if (!WriteProcessMemory(
                      a_hGplProcess,	// handle of the process whose memory is written
                      (void *)(a_startAddress+(i*sizeof(a_actValuesList))),	// address to start reading
                      &(a_actValuesList[0]),
                      sizeof(a_actValuesList),
                      0 ))
                {
                    detachFromGPL();
                    break;
                }
            }
        }
    }

    // remember old frame count
    a_prevFrames = a_frames;
}


//---------------------------------------------------------------------------
void DirectControl::runEffectRollBar()
{
    dlgOptions->ccmEPVarsFRAMES->Value = a_frames;
    dlgOptions->ccmExParser->F(OPENARRAY(Variant,(0)));
    a_actValuesList[3].xPos = dlgOptions->ccmEPVarsX->Value;
    a_actValuesList[3].yPos = dlgOptions->ccmEPVarsY->Value;
    a_actValuesList[3].zPos = dlgOptions->ccmEPVarsZ->Value;
    a_actValuesList[3].yaw = dlgOptions->ccmEPVarsYAW->Value;
    a_actValuesList[3].pitch = dlgOptions->ccmEPVarsPITCH->Value;
    a_actValuesList[3].bank = dlgOptions->ccmEPVarsBANK->Value;
    a_actValuesList[3].zoomAngle = dlgOptions->ccmEPVarsZOOM->Value;
}

//---------------------------------------------------------------------------
void DirectControl::runEffectPitCam()
{
    dlgOptions->ccmEPVarsFRAMES->Value = a_frames;
    dlgOptions->ccmExParser->F(OPENARRAY(Variant,(0)));
    a_actPitValues.xPos = dlgOptions->ccmEPVarsX->Value;
    a_actPitValues.yPos = dlgOptions->ccmEPVarsY->Value;
    a_actPitValues.zPos = dlgOptions->ccmEPVarsZ->Value;
    a_actPitValues.yaw = dlgOptions->ccmEPVarsYAW->Value;
    a_actPitValues.pitch = dlgOptions->ccmEPVarsPITCH->Value;
    a_actPitValues.bank = dlgOptions->ccmEPVarsBANK->Value;
    a_actPitValues.zoomAngle = dlgOptions->ccmEPVarsZOOM->Value;
}

//---------------------------------------------------------------------------
void DirectControl::runMouseRollBar()
{
    if (a_frames > a_prevFrames)
    {
        // get input
        tagPOINT point;
        GetCursorPos(&point);
        int X=point.x;
        int Y=point.y;

        // bring divX range of -1 to 1
        float mouseDeadZoneX = 0.06;
        float divX = ((float(X*2) / float(a_screenWidth)) - 1);
        // do dead zone correction
        float tempX = fabs(divX) - mouseDeadZoneX;  // deadzone correction
        tempX = (tempX < 0) ? 0 : (tempX / (1-mouseDeadZoneX));
        divX = (divX < 0) ? tempX : -tempX;

        // bring divY range of -1 to 1
        float mouseDeadZoneY = 0.06;
        float divY = ((float(Y*2) / float(a_screenHeight)) - 1);
        // do dead zone correction
        float tempY = fabs(divY) - mouseDeadZoneY;  // deadzone correction
        tempY = (tempY < 0) ? 0 : (tempY / (1-mouseDeadZoneY));
        divY = (divY < 0) ? tempY : -tempY;

        // determine speed of movement for key controls
        if (GetKeyState(190) & 0x80)
        {
            a_speed += 0.1;
            if (a_speed > 0.20)
                a_speed = 0.20;
        }
        if (GetKeyState(188) & 0x80)
        {
            a_speed -= 0.1;
            if (a_speed < 0.01)
                a_speed = 0.01;
        }

        // do only for roll bar
        CarCameraValues *cam = &(a_actValuesList[3]);

        float dXPos = 0;
        float dYPos = 0;
        float dZPos = 0;
        float dYaw = 0;
        float dPitch = 0;
        float dBank = 0;
        float dZoomAngle = 0;
        float dForward = 0;

        float invSmooth = 100-a_smooth;

        // do zooming
        if (GetKeyState(109) & 0x80)
        {
            dZoomAngle += 0.15 * a_speed;
        }
        if (GetKeyState(107) & 0x80)
        {
            dZoomAngle -= 0.15 * a_speed;
        }

        a_lastDZoomAngle = (dZoomAngle * invSmooth + a_lastDZoomAngle * a_smooth) / 100;
        cam->zoomAngle += a_lastDZoomAngle;
        if (cam->zoomAngle > M_PI)
            cam->zoomAngle = M_PI;
        else if (cam->zoomAngle < 0.01)
            cam->zoomAngle = 0.01;
        float zoomFactor = (cam->zoomAngle / M_PI) * 2;

        // do pitch
        if (GetKeyState(38) & 0x80)
        {
            if (a_lookMode)
                dForward += a_speed * 1;
            else
                dPitch += a_speed * 0.1;
        }
        if (GetKeyState(40) & 0x80)
        {
            if (a_lookMode)
                dForward -= a_speed * 1;
            else
                dPitch -= a_speed * 0.1;
        }


        // do up down
        if (a_mouseRightDown)
        {
            dZPos += a_speed / 2;
        }
        if (a_mouseLeftDown)
        {
            dZPos -= a_speed / 2;
        }

        // do bank
        if (!a_nascarMode)
        {
            if (GetKeyState('D') & 0x80)
            {
                dBank += a_speed * 0.05;
            }
            if (GetKeyState('F') & 0x80)
            {
                dBank -= a_speed * 0.05;
            }
        }
        // do bank for GPL and Nascar
        if (GetKeyState('W') & 0x80)
        {
            dBank += a_speed * 0.05;
        }
        if (GetKeyState('E') & 0x80)
        {
            dBank -= a_speed * 0.05;
        }

        // calculate pitch or forward
        if (a_lookMode)
            dPitch = -(divY / 20);
        else
            dForward += divY/6;

        // adjust dPitch
        dPitch *= zoomFactor;

        // do yaw and adjust
        dYaw = (divX / 5) * zoomFactor;

        // calculate auto bank
        if (a_bankMode)
            dBank = -divX * (M_PI / 2);

        // start to calculate angle deltas
        a_lastDYaw = (dYaw * invSmooth + a_lastDYaw * a_smooth) / 100;
        cam->yaw += a_lastDYaw;

        if (a_bankMode)
            cam->bank = (dBank * invSmooth + cam->bank * a_smooth) / 100;
        else
        {
            a_lastDBank = (dBank * invSmooth + a_lastDBank * a_smooth) / 100;
            cam->bank -= a_lastDBank;
        }

        a_lastDPitch = (dPitch * invSmooth + a_lastDPitch * a_smooth) / 100;
        cam->pitch += a_lastDPitch;

        dYPos+=sin(cam->yaw) * dForward;
        dXPos+=cos(cam->yaw) * dForward;

        // do left right
        if (GetKeyState(37) & 0x80)
        {
            dYPos+=cos(cam->yaw) * a_speed;
            dXPos-=sin(cam->yaw) * a_speed;
        }
        if (GetKeyState(39) & 0x80)
        {
            dYPos-=cos(cam->yaw) * a_speed;
            dXPos+=sin(cam->yaw) * a_speed;
        }

        // add deltas with smoothing factor
        a_lastDX = (dXPos * invSmooth + a_lastDX * a_smooth) / 100;
        a_lastDY = (dYPos * invSmooth + a_lastDY * a_smooth) / 100;
        a_lastDZ = (dZPos * invSmooth + a_lastDZ * a_smooth) / 100;

        cam->xPos+=a_lastDX;
        cam->yPos+=a_lastDY;
        cam->zPos+=a_lastDZ;

        if (cam->zPos < 0)
           cam->zPos = 0;

    }
}

//---------------------------------------------------------------------------
void DirectControl::runMousePitCam()
{
    if (a_frames > a_prevFrames)
    {
        // get input
        tagPOINT point;
        GetCursorPos(&point);
        int X=point.x;
        int Y=point.y;

        // bring divX range of -1 to 1
        float mouseDeadZoneX = 0.06;
        float divX = ((float(X*2) / float(a_screenWidth)) - 1);
        // do dead zone correction
        float tempX = fabs(divX) - mouseDeadZoneX;  // deadzone correction
        tempX = (tempX < 0) ? 0 : (tempX / (1-mouseDeadZoneX));
        divX = (divX < 0) ? tempX : -tempX;

        // bring divY range of -1 to 1
        float mouseDeadZoneY = 0.06;
        float divY = ((float(Y*2) / float(a_screenHeight)) - 1);
        // do dead zone correction
        float tempY = fabs(divY) - mouseDeadZoneY;  // deadzone correction
        tempY = (tempY < 0) ? 0 : (tempY / (1-mouseDeadZoneY));
        divY = (divY < 0) ? tempY : -tempY;

        // determine speed of movement for key controls
        if (GetKeyState(190) & 0x80)
        {
            a_speed += 0.1;
            if (a_speed > 0.20)
                a_speed = 0.20;
        }
        if (GetKeyState(188) & 0x80)
        {
            a_speed -= 0.1;
            if (a_speed < 0.01)
                a_speed = 0.01;
        }

        // do only for pit cam
        CarCameraValues *cam = &a_actPitValues;

        float dXPos = 0;
        float dYPos = 0;
        float dZPos = 0;
        float dYaw = 0;
        float dPitch = 0;
        float dBank = 0;
        float dZoomAngle = 0;
        float dForward = 0;

        float invSmooth = 100-a_smooth;

        // do zooming
        if (GetKeyState(109) & 0x80)
        {
            dZoomAngle += 0.1 * a_speed;
        }
        if (GetKeyState(107) & 0x80)
        {
            dZoomAngle -= 0.1 * a_speed;
        }

        a_lastDZoomAngle = (dZoomAngle * invSmooth + a_lastDZoomAngle * a_smooth) / 100;
        cam->zoomAngle += a_lastDZoomAngle;
        if (cam->zoomAngle > M_PI)
            cam->zoomAngle = M_PI;
        else if (cam->zoomAngle < 0.01)
            cam->zoomAngle = 0.01;
        float zoomFactor = (cam->zoomAngle / M_PI) * 2;

        // do up down
        if (a_mouseRightDown)
        {
            dZPos += a_speed * 2;
        }
        if (a_mouseLeftDown)
        {
            dZPos -= a_speed * 2;
        }

        // do pitch
        if (GetKeyState(38) & 0x80)
        {
            if (a_lookMode)
                dForward += a_speed * 10;
            else
                dPitch += a_speed * 0.1;
        }
        if (GetKeyState(40) & 0x80)
        {
            if (a_lookMode)
                dForward -= a_speed * 10;
            else
                dPitch -= a_speed * 0.1;
        }

        // do up down
        if (GetKeyState('D') & 0x80)
        {
            dBank += a_speed * 0.05;
        }
        if (GetKeyState('F') & 0x80)
        {
            dBank -= a_speed * 0.05;
        }

        // calculate pitch or forward
        if (a_lookMode)
            dPitch = -(divY / 20);
        else
            dForward += divY*4;

        // adjust dPitch
        dPitch *= zoomFactor;

        // do yaw and adjust
        dYaw = (divX / 5) * zoomFactor;

        // calculate auto bank
        if (a_bankMode)
            dBank = -divX * (M_PI / 2);

        // start to calculate angle deltas
        a_lastDYaw = (dYaw * invSmooth + a_lastDYaw * a_smooth) / 100;
        cam->yaw += a_lastDYaw;

        if (a_bankMode)
            cam->bank = (dBank * invSmooth + cam->bank * a_smooth) / 100;
        else
        {
            a_lastDBank = (dBank * invSmooth + a_lastDBank * a_smooth) / 100;
            cam->bank -= a_lastDBank;
        }

        a_lastDPitch = (dPitch * invSmooth + a_lastDPitch * a_smooth) / 100;
        cam->pitch += a_lastDPitch;

        // do forward backward
        dYPos+=sin(cam->yaw) * dForward;
        dXPos+=cos(cam->yaw) * dForward;

        // do left right
        if (GetKeyState(37) & 0x80)
        {
            dYPos+=cos(cam->yaw) * a_speed * 10;
            dXPos-=sin(cam->yaw) * a_speed * 10;
        }
        if (GetKeyState(39) & 0x80)
        {
            dYPos-=cos(cam->yaw) * a_speed * 10;
            dXPos+=sin(cam->yaw) * a_speed * 10;
        }

        // add deltas with smoothing factor
        a_lastDX = (dXPos * invSmooth + a_lastDX * a_smooth) / 100;
        a_lastDY = (dYPos * invSmooth + a_lastDY * a_smooth) / 100;
        a_lastDZ = (dZPos * invSmooth + a_lastDZ * a_smooth) / 100;

        cam->xPos+=a_lastDX;
        cam->yPos+=a_lastDY;
        cam->zPos+=a_lastDZ;
    }
}

//---------------------------------------------------------------------------
void DirectControl::detachFromGPL()
{
    a_attachedToGPL = false;
    a_pDesCamSet = 0;
    a_startAddress = 0;
    a_hwndGPL = 0;
    frmMain->stbStatus->Panels->Items[0]->Text = "Not Attached";

    // make saved cameras invalid
    a_carcamSaved = false;
    a_pitcamSaved = false;
    a_desViewMode = VmStatic;
}

//---------------------------------------------------------------------------
void DirectControl::storeRollBarCam()
{
    if (!isAttachedToGPL())
        return;

   CarCameraValues tempValues;

   ReadProcessMemory(
        a_hGplProcess,	// handle of the process whose memory is written
        (void *)(a_startAddress+3*sizeof(tempValues)),	// address to start reading
        &tempValues,
        sizeof(tempValues),
        0 );

    frmSavedPositions->addRollBarCam("",
        tempValues.xPos,
        tempValues.yPos,
        tempValues.zPos,
        tempValues.yaw,
        tempValues.pitch,
        tempValues.bank,
        tempValues.zoomAngle);
}

//---------------------------------------------------------------------------
void DirectControl::storePitCam()
{
    if (!isAttachedToGPL())
        return;

    CarCameraValues tempValues;

    ReadProcessMemory(
        a_hGplProcess,	// handle of the process whose memory is written
        (void *)(a_pitAddress),	// address to start reading
        &tempValues,
        sizeof(tempValues),
        0 );

    frmSavedPositions->addPitCam("",
        tempValues.xPos,
        tempValues.yPos,
        tempValues.zPos,
        tempValues.yaw,
        tempValues.pitch,
        tempValues.bank,
        tempValues.zoomAngle);
}

//---------------------------------------------------------------------------
void DirectControl::showStatus()
{
    if (a_hwndGPL == GetForegroundWindow() && isAttachedToGPL())
    {
       TCanvas *canvas = new TCanvas();
       canvas->Handle = GetWindowDC(a_hwndGPL);
       canvas->Font->Color = clWhite;
       canvas->Brush->Color = clBlack;
       AnsiString s = "Mode=";
       switch (a_actViewMode)
       {
           case VmStatic:
              s=s+"Static";
              break;
           case VmMouseRollBar:
              s=s+"MouseRollBar";
              break;
           case VmMousePitCam:
              s=s+"MousePitCam";
              break;
           case VmEffectRollBar:
              s=s+"EffectRollBar";
              break;
           case VmEffectPitCam:
              s=s+"EffectPitCam";
              break;
       }
       if (a_setName=="")
           a_setName="<default>";
       if (a_effectName=="")
           a_effectName="<none>";
       s = s + AnsiString(" / Set=") + a_setName +
               AnsiString(" / Effect=") + a_effectName +
               AnsiString(" / Speed=") + a_speedSetting +
               AnsiString(" / Smooth=") + a_smoothSetting +
               AnsiString(" / Single Step=") + ((a_singleStep) ? "on" : "off");
       TRect rect(15,8,640,20);
       canvas->TextRect(rect, 15, 8, s.c_str());
       ReleaseDC(a_hwndGPL, canvas->Handle);
       delete canvas;
       frmMain->stbStatus->Panels->Items[0]->Text = s;
    }
}

//---------------------------------------------------------------------------
void DirectControl::setSpeed(int speed)
{
    a_speedSetting = speed;
    a_speed = 0.2 * (float(speed) / 100);

    showStatus();
}

//---------------------------------------------------------------------------
void DirectControl::setSmooth(int smooth)
{
    a_smoothSetting = smooth;
    a_smooth = (float(smooth) / 102) * 100;  // prevent from getting 100

    showStatus();
}


