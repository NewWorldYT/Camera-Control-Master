//----------------------------------------------------------------------------
#ifndef DistributeCarCamSetH
#define DistributeCarCamSetH
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
//----------------------------------------------------------------------------
class TdlgDistributeCarCamSet : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
    TLabel *Label1;
    TCheckBox *chkLotus;
    TCheckBox *chkHonda;
    TCheckBox *chkCooper;
    TCheckBox *chkFerrari;
    TCheckBox *chkEagle;
    TCheckBox *chkBrabham;
    TCheckBox *chkBrm;
        TBevel *Bevel2;
        TLabel *Label2;
        TCheckBox *chkNormalCar;
        TCheckBox *chkPacecar;
private:
public:
	virtual __fastcall TdlgDistributeCarCamSet(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgDistributeCarCamSet *dlgDistributeCarCamSet;
//----------------------------------------------------------------------------
#endif    
