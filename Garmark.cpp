//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
#include "GridView.h"

#include "Garmark.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TGarmarkForm *GarmarkForm;
//---------------------------------------------------------------------------
__fastcall TGarmarkForm::TGarmarkForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TGarmarkForm::Button2Click(TObject *Sender)
{

  // ADOQuery3->Close();
  Close();
}
//---------------------------------------------------------------------------




void __fastcall TGarmarkForm::FormShow(TObject *Sender)
{


  Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TGarmarkForm::Button4Click(TObject *Sender)
{

//if( Edit1->Text != "" )
//{
//
//	ADOQuery3->Active = false;
//	ADOQuery3->SQL->Clear();
//	ADOQuery3->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1 from INVOICE where Store = '"+ GridViewForm->strStoreNo+ "'  AND ORDERNO = '"+ Edit1->Text   +"' Order by ORDERNO");
//	ADOQuery3->Active = true;
//}
//else
//{
//   if( CheckBox2->IsChecked )
//   {
//	ADOQuery3->Active = false;
//	ADOQuery3->SQL->Clear();
//	ADOQuery3->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1  from INVOICE where Store = '"+ GridViewForm->strStoreNo+ "'  AND (GARMARK LIKE '%"+ Edit2->Text   +"%' OR  GARMARK1 LIKE '%"+ Edit2->Text   +"%') AND (STATUS = 'I' OR STATUS = 'R') Order by ORDERNO");
//	ADOQuery3->Active = true;
//	}
//	else
//	{
//      ADOQuery3->Active = false;
//	ADOQuery3->SQL->Clear();
//	ADOQuery3->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE,GARMARK, GARMARK1  from INVOICE where Store = '"+ GridViewForm->strStoreNo+ "'  AND (GARMARK LIKE '%"+ Edit2->Text   +"%' OR  GARMARK1 LIKE '%"+ Edit2->Text   +"%')  Order by ORDERNO");
//	ADOQuery3->Active = true;
//
//
//    }
//
//}

}
//---------------------------------------------------------------------------

