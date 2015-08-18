//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "ColorForm01.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TColorForm *ColorForm;
//---------------------------------------------------------------------------
__fastcall TColorForm::TColorForm(TComponent* Owner)
	: TForm(Owner)
{


			ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from Colors where Storeno = "+ MainMenuForm->strStoreNo+ " Order by CODE";
	  ADOQuery1->Active = true;

}
//---------------------------------------------------------------------------
void __fastcall TColorForm::SpeedButton4Click(TObject *Sender)
{
  ADOQuery1->Active = false;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TColorForm::ComboBox1Change(TObject *Sender)
{
	 // strSelectedClass = ComboBox1->Selected->Text;

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from Colors where Storeno = "+ MainMenuForm->strStoreNo+ " Order by CODE";
	  ADOQuery1->Active = true;



}
//---------------------------------------------------------------------------

void __fastcall TColorForm::SpeedButton1Click(TObject *Sender)
{
   //	SaveChangesIListBoxItem->Enabled = true;

      if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Storeno")->AsString = MainMenuForm->strStoreNo;


}
//---------------------------------------------------------------------------

void __fastcall TColorForm::SpeedButton3Click(TObject *Sender)
{
	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

     ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------

void __fastcall TColorForm::SpeedButton2Click(TObject *Sender)
{
    	MainMenuForm->strQuestion = "Are you absolutely sure you wish to Remove this Record?";
			TQuestionForm* QuestionForm;
				Application->CreateForm(__classid(TQuestionForm), &QuestionForm);


		if (QuestionForm )
		{
			QuestionForm->ShowModal();
			delete QuestionForm;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery1->Delete();

	}
}
//---------------------------------------------------------------------------

