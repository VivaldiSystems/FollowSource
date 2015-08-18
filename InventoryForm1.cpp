//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "InventoryForm1.h"
#include "MainMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TInventoryForm *InventoryForm;
//---------------------------------------------------------------------------
__fastcall TInventoryForm::TInventoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TInventoryForm::Button1Click(TObject *Sender)
{



Edit2->Text = "";
Edit1->Text = "";
Edit1->SetFocus();



 // Button1->Default = false;
//Button4->Default = true;
 //  Select TOP 100 ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORENO
//FROM INVOICE
//WHERE STORENO = 1
 //ORDER BY ORDERNO
}
//---------------------------------------------------------------------------




void __fastcall TInventoryForm::Button3Click(TObject *Sender)
{

Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TInventoryForm::FormShow(TObject *Sender)
{
//  Button3->Default = false;
 // Button4->Default = true;
  Edit1->SetFocus();
   //	this->Fill->Color = MainMenuForm->iBackgroundColor ;
}
//---------------------------------------------------------------------------



void __fastcall TInventoryForm::Button4Click(TObject *Sender)
{

if( Edit1->Text != "" )
{

 ADOQuery1->Active = false;
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE , INVENTORYERROR, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND ORDERNO = "+ Edit1->Text   +" Order by ORDERNO");
ADOQuery1->Active = true;
}
else
{
  ShowMessage("Please Enter a Ticket Number First");
  Edit2->Text = "";
  Edit1->Text = "";
  Edit1->SetFocus();
   return;
}

 if (ADOQuery1->Eof)
 {
	 ShowMessage("Ticket Number Not Found! Perhaps you entered the number wrong!");
	 Edit2->Text = "";
	 Edit1->Text = "";

	 Memo1->Lines->Add("Ticket # "+ Edit1->Text +" Scanned - Ticket Not found in System!");
	 Edit1->SetFocus();

	 return;
 }



 // Button3Click(Sender);
if( ADOQuery1->FieldByName("STATUS")->AsString == "R" ||  ADOQuery1->FieldByName("STATUS")->AsString == "I"  )
{
	ADOQuery1->Edit();
	ADOQuery1->FieldByName("INVENTORYERROR")->AsString = "OK";
	ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
	ADOQuery1->Post();
 }
 if( ADOQuery1->FieldByName("STATUS")->AsString == "V"  )
{
	ADOQuery1->Edit();
	ADOQuery1->FieldByName("INVENTORYERROR")->AsString = "ERROR: TICKET VOIDED";
	ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
	ADOQuery1->Post();
 }
  if( ADOQuery1->FieldByName("STATUS")->AsString == "P"  )
{
	ADOQuery1->Edit();
	ADOQuery1->FieldByName("INVENTORYERROR")->AsString = "ERROR: TICKET PICKED UP";
	ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
	ADOQuery1->Post();
 }
   if( ADOQuery1->FieldByName("STATUS")->AsString == "D"  )
{
	ADOQuery1->Edit();
	ADOQuery1->FieldByName("INVENTORYERROR")->AsString = "ERROR: TICKET DELIVERED";
	ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
	ADOQuery1->Post();
 }
  if( CheckBox2->IsChecked )
  {
	 ADOQuery2->Active = false;
	 ADOQuery2->SQL->Clear();
	 if( CheckBox1->IsChecked )
		ADOQuery2->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYERROR, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND INVENTORYDATE IS NOT NULL Order by INVENTORYDATE DESC");
	 else
		ADOQuery2->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYERROR, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND INVENTORYDATE IS NOT NULL AND INVENTORYERROR != 'OK' Order by INVENTORYDATE DESC");


	  ADOQuery2->Active = true;

  }
Label3->Text = "Ticket # "+ Edit1->Text+" Scanned - "+ ADOQuery1->FieldByName("INVENTORYERROR")->AsString;


Memo1->Lines->Add(Label3->Text);

Edit2->Text = "";
Edit1->Text = "";



  Button4->Default = true;
//Button4->Default = false;
Edit1->SetFocus();

}
//---------------------------------------------------------------------------

void __fastcall TInventoryForm::Button5Click(TObject *Sender)
{
 ADOQuery2->Active = false;
	 ADOQuery2->SQL->Clear();
	 if( CheckBox1->IsChecked )
		ADOQuery2->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYERROR, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND INVENTORYDATE IS NOT NULL Order by INVENTORYDATE DESC");
	 else
		ADOQuery2->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYERROR, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND INVENTORYDATE IS NOT NULL AND INVENTORYERROR != 'OK' Order by INVENTORYDATE DESC");


	  ADOQuery2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TInventoryForm::Button6Click(TObject *Sender)
{

Memo1->Lines->Clear();

ADOQuery3->Active = false;
ADOQuery3->SQL->Clear();
ADOQuery3->SQL->Add("UPDATE INVOICE SET INVENTORYDATE = NULL where Store = "+ MainMenuForm->strStoreNo+ ";Select COUNT(ID) from Store where Store = "+ MainMenuForm->strStoreNo+ "");
ADOQuery3->Active = true;

ADOQuery3->Active = false;
}
//---------------------------------------------------------------------------

void __fastcall TInventoryForm::SpeedButton4Click(TObject *Sender)
{
 ADOQuery2->Close();
   ADOQuery1->Close();
  Close();
}
//---------------------------------------------------------------------------

