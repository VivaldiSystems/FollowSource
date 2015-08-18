//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CouponForm01.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCouponForm *CouponForm;
//---------------------------------------------------------------------------
__fastcall TCouponForm::TCouponForm(TComponent* Owner)
	: TForm(Owner)
{



			ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "select * from Coupon where storeno = "+ MainMenuForm->strStoreNo+ " Order by Coupon";
	  ADOQuery1->Active = true;

}
//---------------------------------------------------------------------------
void __fastcall TCouponForm::SpeedButton4Click(TObject *Sender)
{
  ADOQuery1->Active = false;
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TCouponForm::ComboBox1Change(TObject *Sender)
{
	 // strSelectedClass = ComboBox1->Selected->Text;

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "select * from Coupon where storeno = "+ MainMenuForm->strStoreNo+ " Order by Coupon";
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

void __fastcall TCouponForm::SpeedButton1Click(TObject *Sender)
{
   //	SaveChangesIListBoxItem->Enabled = true;

      if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Store")->AsString = MainMenuForm->strStoreNo;


}
//---------------------------------------------------------------------------

void __fastcall TCouponForm::SpeedButton3Click(TObject *Sender)
{
	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

     ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------

void __fastcall TCouponForm::SpeedButton2Click(TObject *Sender)
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

