//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "StoreForm01.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TStoreForm *StoreForm;
//---------------------------------------------------------------------------
__fastcall TStoreForm::TStoreForm(TComponent* Owner)
	: TForm(Owner)
{



		 //SaveChangesIListBoxItem->Visible = false;
		 strUpcharge = "";
		 strClass = "D";
		  strQty = "1";
		  blnSubDCItem = false;
		  aPrices = new float[100];
		  aPrices = new float[100];
		  aLinePrices = new float[100];
		  fTotalPrices = 0.00;
		  blnUpcharge = false;

		 TempListQty = new TStringList; // declare the list
		  TempListItemCode = new TStringList; // declare the list
		   TempListItemDescription = new TStringList; // declare the list
			TempListPrice = new TStringList; // declare the list
			 TempListTax = new TStringList; // declare the list
			 TempListItemUpcharge = new TStringList; // declare the list

			ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from Store where Store = "+ MainMenuForm->strStoreNo+ " Order by Store";
	  ADOQuery1->Active = true;

}
//---------------------------------------------------------------------------
void __fastcall TStoreForm::SpeedButton4Click(TObject *Sender)
{
  ADOQuery1->Active = false;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TStoreForm::ComboBox1Change(TObject *Sender)
{
	 // strSelectedClass = ComboBox1->Selected->Text;

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from Store where Store = "+ MainMenuForm->strStoreNo+ " Order by Store";
	  ADOQuery1->Active = true;


	  if( ADOQuery1->Eof == false )
	  {
		   //	SaveChangesIListBoxItem->Enabled = true;
			//EditCustomerListBoxItem->Enabled = true;
		   //	 MetropolisUIListBoxItem1->Enabled = true;



	  }
	  else
	  {
		  // SaveChangesIListBoxItem->Enabled = false;
		  // EditCustomerListBoxItem->Enabled = false;
		  //	MetropolisUIListBoxItem1->Enabled = false;
	  }

}
//---------------------------------------------------------------------------

void __fastcall TStoreForm::SpeedButton1Click(TObject *Sender)
{
   //	SaveChangesIListBoxItem->Enabled = true;

      if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Store")->AsString = MainMenuForm->strStoreNo;


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm::SpeedButton3Click(TObject *Sender)
{
	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

     ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm::SpeedButton2Click(TObject *Sender)
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

