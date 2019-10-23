//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>

#include "View.h"
#include <ActnList.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>

#include "GPLCarCameraSet.h"
#include "GPLCarCamera.h"
#include "DirectControl.h"
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include "pvlUrl.hpp"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
    TImageList *imgList;
    TCoolBar *cbrMain;
    TToolBar *tbrMenu;
    TToolButton *btnFile;
    TToolButton *btnExtra;
    TActionList *aclMain;
    TAction *actExit;
    TAction *actAbout;
    TAction *actPreferences;
    TToolButton *btnHelp;
    TAction *actNewCamSet;
    TToolButton *btnCameraSet;
    TAction *actDeleteCamSet;
    TAction *actRenameCamSet;
    TPopupMenu *pmuFile;
    TMenuItem *mniExportGPLcamfile1;
    TMenuItem *mniExit;
    TPopupMenu *pmuCameraSet;
    TMenuItem *mniNew;
    TMenuItem *mniDelete;
    TMenuItem *Rename1;
    TPopupMenu *pmuTools;
    TPopupMenu *pmuHelp;
    TMenuItem *About1;
    TAction *actSave;
    TMenuItem *mniSave;
    TMenuItem *N2;
    TMenuItem *Options1;
    TToolButton *btnCamera;
    TPopupMenu *pmuCamera;
    TAction *actCopyCamSet;
    TAction *actPasteCamSet;
    TAction *actPropertiesCamera;
    TMenuItem *mniCopyCamera;
    TMenuItem *mniPasteCamera;
    TMenuItem *N3;
    TMenuItem *mniPropertiesCamera;
    TOpenDialog *dlgOpenCmf;
    TAction *actImportGPLCamfile;
    TAction *actExportGPLCamfile;
    TMenuItem *mniImportGPLcamfile1;
    TMenuItem *N5;
    TOpenDialog *dlgOpenCam;
    TSaveDialog *dlgSaveCmf;
    TSaveDialog *dlgSaveCam;
    TAction *actHelp;
    TMenuItem *hlpGPLForeverCCMHelp;
    TMenuItem *N1;
    TAction *actGettingStarted;
    TMenuItem *GettingStarted1;
    TToolBar *tbrTools;
    TPageControl *pagMain;
    TTabSheet *tabMain;
    TGroupBox *grpSetActivation;
    TLabel *lblDirectControl;
    TCheckBox *chkHotkeyDirectControl;
    TPanel *pnlLogo;
    TAction *actOpen;
    TAction *actClose;
    TMenuItem *mniOpen;
    TMenuItem *actClose1;
    TToolButton *btnNew;
    TToolButton *btnOpen;
    TToolButton *btnSave;
    TToolButton *btnCutCamSet;
    TAction *actCutCamSet;
    TAction *actCopyCamera;
    TAction *actPasteCamera;
    TAction *actNew;
    TAction *actSaveAs;
    TToolButton *ToolButton1;
    TToolButton *btnCopyCamSet;
    TToolButton *btnPasteCamSet;
    TToolButton *btnNewCamSet;
    TToolButton *btnDeleteCamSet;
    TToolButton *ToolButton2;
    TToolButton *btnCopyCamera;
    TToolButton *btnPasteCamera;
    TMenuItem *mniNewFile;
    TMenuItem *N4;
    TMenuItem *SaveAs1;
    TAction *actDistributeCamSet;
    TMenuItem *N6;
    TMenuItem *mniCopyCamSet;
    TMenuItem *mniCutCamSet;
    TMenuItem *mniPasteCamSet;
    TMenuItem *N7;
    TMenuItem *mniDistribute;
    TToolBar *tbrApplications;
    TSpeedButton *btnGPL;
    TSpeedButton *btnVideoCapture;
    TSpeedButton *btnMovieEditor;
    TSpeedButton *btnImageCapture;
    TAction *actGPL;
    TPanel *pnlLinks;
    TLabel *Label1;
    TAction *actVideoCapture;
    TAction *actMovieEditor;
    TAction *actImageCapture;
    TAction *actReplayAnalyser;
    TSpeedButton *btnReplayAnalyser;
    TAction *actCameraEditor;
    TGroupBox *gplSettings;
    TCheckBox *chkGPLInWindow;
    TAction *actSavedPositions;
    TMenuItem *mniSavedPositions;
    TStatusBar *stbStatus;
    TpvlUrl *pvlUrl;
    TTrackBar *tbrSpeed;
    TTrackBar *tbrSmooth;
    TLabel *lblSpeed;
    TLabel *lblSmooth;
    TLabel *lblSpeedValue;
    TLabel *lblSmoothValue;
    TCheckBox *chkDefaultLookMode;
    TCheckBox *chkDefaultBankMode;
        TGroupBox *grpGPLNascar;
        TLabel *lblNascarWindow;
        TComboBox *cbxGameSelector;
        TImage *imgGPLNascar;
        TImage *imgLogo;
    TMenuItem *NR2003Notes1;
    TAction *actNR2003Notes;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall actExitExecute(TObject *Sender);
    void __fastcall actSaveExecute(TObject *Sender);
    void __fastcall actNewCamSetExecute(TObject *Sender);
    void __fastcall actDeleteCamSetExecute(TObject *Sender);
    void __fastcall actRenameCamSetExecute(TObject *Sender);
    void __fastcall actPreferencesExecute(TObject *Sender);
    void __fastcall actAboutExecute(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
    void __fastcall actHelpExecute(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
    void __fastcall setMode(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall actGettingStartedExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall actOpenExecute(TObject *Sender);
    void __fastcall actCloseExecute(TObject *Sender);
    void __fastcall actCopyCamSetExecute(TObject *Sender);
    void __fastcall actPasteCamSetExecute(TObject *Sender);
    void __fastcall actImportGPLCamfileExecute(TObject *Sender);
    void __fastcall actExportGPLCamfileExecute(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall actCopyCameraExecute(TObject *Sender);
    void __fastcall actPasteCameraExecute(TObject *Sender);
    void __fastcall actCutCamSetExecute(TObject *Sender);
    void __fastcall actPropertiesCameraExecute(TObject *Sender);
    void __fastcall actNewExecute(TObject *Sender);
    void __fastcall actSaveAsExecute(TObject *Sender);
    void __fastcall actDistributeCamSetExecute(TObject *Sender);
    void __fastcall pagMainChange(TObject *Sender);
    void __fastcall actGPLExecute(TObject *Sender);
    void __fastcall LinkClick(TObject *Sender);
    void __fastcall actVideoCaptureExecute(TObject *Sender);
    void __fastcall actMovieEditorExecute(TObject *Sender);
    void __fastcall actImageCaptureExecute(TObject *Sender);
    void __fastcall actReplayAnalyserExecute(TObject *Sender);
    void __fastcall imgLogoClick(TObject *Sender);
    void __fastcall actSavedPositionsExecute(TObject *Sender);
    void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
    void __fastcall tbrSpeedChange(TObject *Sender);
    void __fastcall tbrSmoothChange(TObject *Sender);
    void __fastcall chkDefaultLookModeClick(TObject *Sender);
    void __fastcall chkDefaultBankModeClick(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall FormDeactivate(TObject *Sender);
        void __fastcall cbxGameSelectorChange(TObject *Sender);
    void __fastcall actNR2003NotesExecute(TObject *Sender);
private:	// User declarations
    struct {
        char sectionType[4];
        char reserved[4];
        long dataSize;
        CarCameraValuesList carCameraValuesList;
    } a_cameraFile;

    // first time execution
    bool a_firstRun;
    bool a_firstNR2003;

    // set mode is allowed now
    bool a_setModeAllowed;

    // journal call back hook
    HHOOK a_hhk;

    // remember replace all
    bool a_replaceAll;

    // direct control thread
    DirectControl *a_directControl;

    // info off gpl process
    PROCESS_INFORMATION gplInfo;

    // new counter
    int a_newFileCounter;

    // current list with sets
    TList *a_setList;
    TList *a_effectList;

    int a_activeSet;
    int a_activeEffect;

    bool a_resetdone;

public:		// User declarations
    __fastcall TfrmMain(TComponent* Owner);

    TGPLCarCameraSet * __fastcall castCamSet(void *);
    TGPLCarCameraSet * __fastcall getActiveCamSet();
    TGPLCarCameraSet * __fastcall getActiveEffect();

    void writeCmfFilesToIni();
    void readCmfFilesFromIni();

    DirectControl *getDirectControl() const { return a_directControl; }

    void __fastcall evaluateKey(WORD pressedKey);

    void __fastcall exportGPLCamfileToFile(TGPLCarCameraSet *camSet, String Name);
    void __fastcall importGPLCamfileToFile(TGPLCarCameraSet *camSet, String Name);

};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
