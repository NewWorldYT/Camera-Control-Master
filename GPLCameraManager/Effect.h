//---------------------------------------------------------------------------

#ifndef EffectH
#define EffectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmEffect : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *grpEffect;
    TMemo *mmoEffect;
    TButton *btnOk;
    TButton *btnCancel;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mmoEffectChange(TObject *Sender);
    void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:	// User declarations
    bool a_changed;

public:		// User declarations
    __fastcall TfrmEffect(TComponent* Owner);

    bool isChanged() const { return a_changed; }
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmEffect *frmEffect;
//---------------------------------------------------------------------------
#endif
