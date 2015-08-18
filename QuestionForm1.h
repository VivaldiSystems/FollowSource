//---------------------------------------------------------------------------

#ifndef QuestionForm1H
#define QuestionForm1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TQuestionForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
    TButton *Button1;
	TButton *Button2;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TQuestionForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TQuestionForm *QuestionForm;
//---------------------------------------------------------------------------
#endif
