//----------------------------------------------------------------------------
#ifndef AboutH
#define AboutH
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
#include <jpeg.hpp>
//----------------------------------------------------------------------------
class TdlgAbout : public TForm
{
__published:        
	TButton *OKBtn;
    TPanel *Panel1;
    TImage *imgGplForever;
    TLabel *lblName;
    TLabel *Label2;
    void __fastcall lblSiteClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);
private:
public:
	virtual __fastcall TdlgAbout(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TdlgAbout *dlgAbout;
//----------------------------------------------------------------------------
#endif    
