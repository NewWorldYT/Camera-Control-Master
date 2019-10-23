//----------------------------------------------------------------------------
#ifndef NameH
#define NameH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>

#include "GPLCarCameraSet.h"

//----------------------------------------------------------------------------
class TdlgName : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
    TGroupBox *grpName;
    TEdit *edtName;
    TGroupBox *grpType;
    TRadioButton *radCarCamSet;
    TRadioButton *radEffect;
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:
public:
	virtual __fastcall TdlgName(TComponent* AOwner);

    eCameraSetType getType() const;
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgName *dlgName;
//----------------------------------------------------------------------------
#endif    
