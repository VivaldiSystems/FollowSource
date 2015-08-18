//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainMenu.h"
#include "QuestionForm1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TQuestionForm *QuestionForm;
//---------------------------------------------------------------------------
__fastcall TQuestionForm::TQuestionForm(TComponent* Owner)
	: TForm(Owner)
{

  Label1->Text =  MainMenuForm->strQuestion;

  if( MainMenuForm->strQuestion == "Is this Alteration Attached to the Item Above?" )
  {
		Button1->Text = "Yes";
		Button2->Text = "No";
  }
  else
  {
		Button1->Text = "OK";
		Button2->Text = "Cancel";
  }


}
//---------------------------------------------------------------------------
void __fastcall TQuestionForm::Button1Click(TObject *Sender)
{


  MainMenuForm->blnOK = true;
  this->Close();

}
//---------------------------------------------------------------------------
void __fastcall TQuestionForm::Button2Click(TObject *Sender)
{
   MainMenuForm->blnOK = false;
   this->Close();
}
//---------------------------------------------------------------------------
