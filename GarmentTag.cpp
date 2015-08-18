//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "MainMenu.h"
#include "GarmentTag.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TGarmentTagForm *GarmentTagForm;
//---------------------------------------------------------------------------
__fastcall TGarmentTagForm::TGarmentTagForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGarmentTagForm::Button1Click(TObject *Sender)
{
if( Edit1->Text != "" )
{

	ADOQuery1->Active = false;
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1, GARMARK2, GARMARK3, GARMARK4, GARMARK5 from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND ORDERNO = "+ Edit1->Text   +" Order by ORDERNO");
	ADOQuery1->Active = true;
}
else
{
   if( CheckBox1->IsChecked )
   {
	ADOQuery1->Active = false;
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1, GARMARK2, GARMARK3, GARMARK4, GARMARK5   from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND (GARMARK LIKE '%"+ Edit2->Text   +"%' OR  GARMARK1 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK2 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK3 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK4 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK5 LIKE '%"+ Edit2->Text   +"%') AND (STATUS = 'I' OR STATUS = 'R') Order by ORDERNO");
	ADOQuery1->Active = true;
	}
	else
	{
	  ADOQuery1->Active = false;
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1, GARMARK2, GARMARK3, GARMARK4, GARMARK5   from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND (GARMARK LIKE '%"+ Edit2->Text   +"%' OR  GARMARK1 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK2 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK3 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK4 LIKE '%"+ Edit2->Text   +"%' OR  GARMARK5 LIKE '%"+ Edit2->Text   +"%') Order by ORDERNO");
	ADOQuery1->Active = true;


    }

}
}
//---------------------------------------------------------------------------
void __fastcall TGarmentTagForm::Button2Click(TObject *Sender)
{

 if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

 ADOQuery1->Close();
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TGarmentTagForm::Button3Click(TObject *Sender)
{
  if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

}
//---------------------------------------------------------------------------

