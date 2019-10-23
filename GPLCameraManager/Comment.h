//---------------------------------------------------------------------------

#ifndef CommentH
#define CommentH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TfrmComment : public TForm
{
__published:	// IDE-managed Components
    TMemo *mmoComment;
    void __fastcall FormShow(TObject *Sender);
    void __fastcall mmoCommentChange(TObject *Sender);
private:	// User declarations
    bool a_changed;

public:		// User declarations
    __fastcall TfrmComment(TComponent* Owner);

    bool isChanged() const { return a_changed; }
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmComment *frmComment;
//---------------------------------------------------------------------------
#endif
