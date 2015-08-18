//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "AccountForm2.h"
#include "FM_DATEPICKER01.h"
#include "QuestionForm1.h"
#include "MainMenu.h"
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TAccountForm01 *AccountForm01;
//---------------------------------------------------------------------------
__fastcall TAccountForm01::TAccountForm01(TComponent* Owner)
	: TForm(Owner)
{
		 TabControl1->TabIndex = 0;
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

         	Label23->Text = "Select Item";


}
//---------------------------------------------------------------------------
void __fastcall TAccountForm01::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
   //	ShowToolbar(Button == TMouseButton::mbRight);
}
//---------------------------------------------------------------------------
void TAccountForm01::ShowToolbar(bool AShow)
{

}

//---------------------------------------------------------------------------


void __fastcall TAccountForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------





void __fastcall TAccountForm01::SelectCustomerListBoxItemClick(TObject *Sender)
{
		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

}




void __fastcall TAccountForm01::EditCustomerListBoxItemClick(TObject *Sender)
{

	  TabControl1->TabIndex = 1;


	 // MetropolisUIListBoxItem1->Enabled = true;
	
	  ADOQuery2->Active = false;

       	if( MainMenuForm->strDataBaseType == "MSACCESS" )
		{
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = "+MainMenuForm->strStoreNo  +" And AMTPAID <> DUE  order by ID ";
	  ADOQuery2->Active = true;
		  }
		  else
		  {
                ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = '"+MainMenuForm->strStoreNo  +"' And AMTPAID != DUE  order by ID ";
	  ADOQuery2->Active = true;


          }
	  double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }

		double dbalance  = dPaid - dTotal;
		if ( dbalance < .01 && dbalance > 0 ) {
		if ( dbalance > -.01 && dbalance < 0 ) {
			dbalance = 0;
		}
		}

	   Label3->Text =   FloatToStrF(dbalance, ffGeneral, 12, 2);
	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);
        ADOQuery2->First();


}
//---------------------------------------------------------------------------


void __fastcall TAccountForm01::AddCustomerListBoxItemClick(TObject *Sender)
{

	Button12Click(Sender);

}
//---------------------------------------------------------------------------




void __fastcall TAccountForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{
	   if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

     double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }



      Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);
	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);


	  ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Label24Click(TObject *Sender)
{
	   //	LeftLayout->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TAccountForm01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TAccountForm01::UpdateTicketView()
{
Memo1->Lines->Clear();

AnsiString sQty;
AnsiString sItemDescription;
AnsiString sUpcharge;
AnsiString sPrice;
float fTotal = 0;


	for( int i = 0; i < TempListQty->Count; i++ )
	{

		sQty = "";
		sItemDescription = "";
		sUpcharge = "";
		sPrice = "$0.00";

		if( i < TempListQty->Count )
			sQty = TempListQty->Strings[i];

			//sQty = Format('%8.2f', sQty );

		if( i < TempListItemDescription->Count   )
		{
			sItemDescription = TempListItemDescription->Strings[i];
			sPrice = FloatToStrF(aLinePrices[i]  , ffCurrency, 12, 2);
			fTotal = fTotal + aLinePrices[i];
		}


		 sItemDescription = sItemDescription +  sItemDescription.StringOfChar(' ', 20 - sItemDescription.Length() );

		   Memo1->Lines->Add(sQty+"  "+sItemDescription + "   " + sPrice);

		if( TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
			  Memo1->Lines->Add("   "+ TempListItemUpcharge->Strings[i] );

	}

	Label26->Text = "Sub Total:  "+ FloatToStrF(fTotal  , ffCurrency, 12, 2);
}
void __fastcall TAccountForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TAccountForm01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button8Click(TObject *Sender)
{
   SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
	execinfo.lpVerb = L"open";

	execinfo.lpFile = L"C:\\CML\\CML.exe";

	//AnsiString pw;
	//pw =  " /TC:\\VIVALDI\\REPORTS\\RPTFMT.TXT ";

   execinfo.lpParameters = L" C:\\CML\\CustomerReport.rpt /L1 C:\\FOLLOW\\vivaldi.dsn,DB_53817_vivaldis,db_53817_vivaldis_user,DMNN";  //pw.c_str();
   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_SHOWDEFAULT;

  //ShellExecute( NULL,"C:\\VIVALDI\\REPORTS\\RRWRUN.EXE",NULL," /TC:\\VIVALDI\\REPORTS\\RPTFMT.TXT ","C:\\VIVALDI\\REPORTS\\", SW_SHOWNORMAL );

	if(! ShellExecuteEx(&execinfo))
   {
		ShowMessage("Could Not Run Report Writer. Check that Crystal is Installed!");
		return;
   }
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button13Click(TObject *Sender)
{

if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

   ADOQuery2->Active = false;


	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct like '%"+ADOQuery1->FieldByName("ACCT")->AsString+"%' AND STORENO = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;



}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button9Click(TObject *Sender)
{
	Memo1->Lines->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();
	TempListPrice->Clear();
	TempListTax->Clear();
	TempListItemUpcharge->Clear();

	UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TAccountForm01::FormShow(TObject *Sender)
{
   // this->Fill->Color = MainMenuForm->iBackgroundColor ;
	 EditCustomerListBoxItem->Enabled = false;
	 //MetropolisUIListBoxItem2->Enabled = false;
	 Edit2->SetFocus();

}
//---------------------------------------------------------------------------




void __fastcall TAccountForm01::MetropolisUIListBoxItem1Click(TObject *Sender)
{

		MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Account Transaction?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
        //ShowMessage("Customers can not be Deleted");
	   ADOQuery2->Delete();
	}
}
//---------------------------------------------------------------------------



void __fastcall TAccountForm01::Button1Click(TObject *Sender)
{
	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";

		if( MainMenuForm->strDataBaseType == "MSACCESS" )
		{


	  if( strNumber.AnsiPos( Edit2->Text.SubString(0,1) ) > 0 )
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where Account = TRUE and acct like '%"+Edit2->Text+"%' AND STORE = "+ MainMenuForm->strStoreNo+ " order by acct";

	  }
	  else
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where  Account = TRUE and name like '%"+Edit2->Text+"%' AND STORE = "+ MainMenuForm->strStoreNo+ " order by name";


	  }
		}
		else
		{

	  if( strNumber.AnsiPos( Edit2->Text.SubString(0,1) ) > 0 )
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where Account = 1 and acct like '%"+Edit2->Text+"%' AND STORE = "+ MainMenuForm->strStoreNo+ " order by acct";

	  }
	  else
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where  Account = 1 and name like '%"+Edit2->Text+"%' AND STORE = "+ MainMenuForm->strStoreNo+ " order by name";


	  }




        }
	  ADOQuery1->Active = true;

	  if( ADOQuery1->Eof == false )
	  {
		 // WriteTicketListBoxItem->Enabled = true;
		 // QuickTicketListBoxItem->Enabled = true;
		  EditCustomerListBoxItem->Enabled = true;
		 // MetropolisUIListBoxItem2->Enabled = true;
	  }
	  else
	  {

		ShowMessage("No Account Customer Found with that condition!");

		 // WriteTicketListBoxItem->Enabled = false;
		 // QuickTicketListBoxItem->Enabled = false;
		   EditCustomerListBoxItem->Enabled = false;
		  // MetropolisUIListBoxItem2->Enabled = false;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button12Click(TObject *Sender)
{

 	double fLocalTendered = 0;
	TCommonCustomForm *Form = Application->GetDeviceForm(L"CashdrawerView");
		if(Form)
		{

		  MainMenuForm->fTendered  = 0; //MainMenuForm->fTicketSubTotal +  MainMenuForm->fTicketTax - MainMenuForm->fPrepayment - MainMenuForm->fCouponTotal;

		   Form->ShowModal();
		   fLocalTendered =  MainMenuForm->fTendered;
		   delete Form;

		}
	 if( MainMenuForm->blnCancel == false )
	 {



		ADOQuery2->Insert() ;
		ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		ADOQuery2->FieldByName("AMT")->AsFloat = fLocalTendered;
			ADOQuery2->FieldByName("AMTPAID")->AsString  = "0";
				ADOQuery2->FieldByName("DUE")->AsFloat  = fLocalTendered;
        	ADOQuery2->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
            	ADOQuery2->FieldByName("NAME")->AsString = ADOQuery1->FieldByName("NAME")->AsString;
			ADOQuery2->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
			ADOQuery2->FieldByName("REFERENCE")->AsString = "INVOICE";

	       ADOQuery2->Post();

	 }
       double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }
		// SaveChangesIListBoxItem->Enabled = true;

	    Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
		Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);

	    Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button10Click(TObject *Sender)
{
   MainMenuForm->blnReturnTendered = true;

	if( MainMenuForm->blnUseCashDrawer )
	{

		WinExec("c:\\FOLLOW\\CashDrawer.bat", SW_HIDE);

 	}

	double fLocalTendered = 0;
	TCommonCustomForm *Form = Application->GetDeviceForm(L"CashdrawerView");
		if(Form)
		{

		  MainMenuForm->fTendered  = 0; //MainMenuForm->fTicketSubTotal +  MainMenuForm->fTicketTax - MainMenuForm->fPrepayment - MainMenuForm->fCouponTotal;

		   Form->ShowModal();
		   fLocalTendered =  MainMenuForm->fTendered;
		   delete Form;

		}
	 if( MainMenuForm->blnCancel == false )
	 {

			ADOQuery2->Insert();
			ADOQuery2->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
			ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;

			ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery2->FieldByName("NAME")->AsString = ADOQuery1->FieldByName("NAME")->AsString;
			ADOQuery2->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
			ADOQuery2->FieldByName("REFERENCE")->AsString = "PAYMENT";
			ADOQuery2->FieldByName("AMT")->AsString = 0;

			ADOQuery2->FieldByName("AMTPAID")->AsFloat = MainMenuForm->fTendered;
			ADOQuery2->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			ADOQuery2->FieldByName("DUE")->AsString = 0;
			ADOQuery2->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery2->FieldByName("STATUS")->AsString =  "OPEN";

			ADOQuery2->Post();



		 ADOQuery3->Active = false;
		 ADOQuery3->SQL->Clear();
		 ADOQuery3->SQL->Add("Select * from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and id = -1");
		 ADOQuery3->Active = true;
		 ADOQuery3->Insert();
			ADOQuery3->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery3->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery3->FieldByName("AMTPAID")->AsFloat =  MainMenuForm->fTendered;
			ADOQuery3->FieldByName("ACCT")->AsString =  	ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery3->FieldByName("NAME")->AsString =  	ADOQuery1->FieldByName("NAME")->AsString;
			//ADOQuery3->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery3->FieldByName("AMT")->AsString =  	MainMenuForm->fTendered;
			ADOQuery3->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery3->FieldByName("DUE")->AsFloat = MainMenuForm->fTendered;
			ADOQuery3->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			//ADOQuery3->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery3->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery3->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery3->Post();
			ADOQuery3->Active = false;
	 }

	  double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }

		 ADOQuery4->Active = false;
		 ADOQuery4->SQL->Clear();
		 ADOQuery4->SQL->Add("Select * from INVOICEHISTORY where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and id = -1");
		 ADOQuery4->Active = true;


		ADOQuery4->Open();
		ADOQuery4->Insert();
	   ADOQuery4->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

	   ADOQuery4->FieldByName("DESCRIPTION")->AsString = "Payment Made: "+ FloatToStrF(MainMenuForm->fTendered  , ffCurrency, 12, 2);
	   ADOQuery4->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	   ADOQuery4->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
	   ADOQuery4->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
	   ADOQuery4->FieldByName("ORDERNO")->AsString = "0";
	   ADOQuery4->FieldByName("ACCT")->AsString = 	ADOQuery1->FieldByName("ACCT")->AsString;
	   ADOQuery4->Post();
	   ADOQuery4->Close();


	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);

	   Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);


     MainMenuForm->blnReturnTendered = false;
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button25Click(TObject *Sender)
{

if( ADOQuery1->Eof)
{
	ShowMessage("No Customer Selected");
}
	MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
	TCommonCustomForm *FM_DATEPICKERFORM = Application->GetDeviceForm(L"FM_DATEPICKER");
		if (FM_DATEPICKERFORM)
		{


			if( FM_DATEPICKERFORM->ShowModal() == mrOk )
			{

			}

			delete FM_DATEPICKERFORM;

		}

				  AnsiString strDateCommand = "UPDATE STORE SET DATEOUTPARAM = '"+MainMenuForm->strDateOut +"' where Store = '"+ MainMenuForm->strStoreNo+ "'";

					 ADOQuery6->Active = false;
					ADOQuery6->SQL->Clear();
					ADOQuery6->SQL->Add(strDateCommand);
						ADOQuery6->ExecSQL();


					MainMenuForm->strReportFileName = "ARStatement.rdl";



			MainMenuForm->strReportName = "AR Statement Report";
			MainMenuForm->strReportFilter = ADOQuery1->FieldByName("ACCT")->AsString;

			MainMenuForm->strDataSet = "ARSTATEMENT" ;

				FILE *stream;
		stream = fopen("c:\\FOLLOW\\REPORT.TXT", "w+");

		AnsiString  s;
		s = "ACCT='"+ADOQuery1->FieldByName("ACCT")->AsString+"'";
		fprintf(stream , "%s", s);
		fclose(stream);


		 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

	if( MainMenuForm->blnLocalDatabase ) {

				execinfo.lpFile = L"C:\\FOLLOW\\ReportViewerLocal.exe";

   } else {


	execinfo.lpFile = L"C:\\FOLLOW\\ReportViewer.exe";


   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = MainMenuForm->strStoreNo+ "  "+MainMenuForm->strReportFileName+" 1 PREVIEW ARSTATEMENT FILE FALSE";
				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
						return;
				   }
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button27Click(TObject *Sender)
{
 if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
 {
		 ADOQuery2->Post();
 }
	  ADOQuery1->MoveBy(1);
	   ADOQuery2->Active = false;
	if( MainMenuForm->strDataBaseType == "MSACCESS" )
		{
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = "+MainMenuForm->strStoreNo  +" And AMTPAID <> DUE  order by ID ";
	  ADOQuery2->Active = true;
		  }
		  else
		  {
                ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = '"+MainMenuForm->strStoreNo  +"' And AMTPAID != DUE  order by ID ";
	  ADOQuery2->Active = true;


          }
        double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }



	   Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);
	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);

}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button26Click(TObject *Sender)
{
 if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
 {
		 ADOQuery2->Post();
 }



	  ADOQuery1->MoveBy(-1);
	   ADOQuery2->Active = false;
	if( MainMenuForm->strDataBaseType == "MSACCESS" )
		{
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = "+MainMenuForm->strStoreNo  +" And AMTPAID <> DUE  order by ID ";
	  ADOQuery2->Active = true;
		  }
		  else
		  {
                ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND STORENO = '"+MainMenuForm->strStoreNo  +"' And AMTPAID != DUE  order by ID ";
	  ADOQuery2->Active = true;


		  }
                      double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }



	   Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);
	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);

}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button28Click(TObject *Sender)
{

	MainMenuForm->strQuestion = "Are you sure you wish to Delete this AR Transaction?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery2->Delete();

	}

      double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }


	  Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);

	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Button29Click(TObject *Sender)
{

					AnsiString strCC =  ADOQuery1->FieldByName("CCARD")->AsString;
					AnsiString strExpDate =  ADOQuery1->FieldByName("EXPDATE")->AsString;

				   //	ADOQuery1->Active = false;

					if( strCC == "" )
					{
					   ShowMessage(ADOQuery1->FieldByName("ACCT")->AsString+" CUSTOMER IS MISSING A CREDIT CARD IN THE CUSTOMER RECORD.");
                       return;
					}

					FILE *stream;
					 FILE *stream2;

					 AnsiString strPath = "C:\\FOLLOW\\X-CHARGE\\";
					  if( MainMenuForm->strCreditCardPath != "" )
					  {
						  strPath = MainMenuForm->strCreditCardPath+ "\\";
					  }

					 AnsiString filename =  strPath+ TDateTime::CurrentDateTime().FormatString("MMDDYYYY")+".req" ;
					 AnsiString filename2 =  strPath+ TDateTime::CurrentDateTime().FormatString("MMDDYYYY")+".ans" ;


					 DeleteFile(filename2.c_str());
					 DeleteFile(filename.c_str());

					 Caption = filename;
					 stream2 = fopen(filename.c_str(), "w+");


					double dtotalvalue = StrToFloat( Label3->Text );
					dtotalvalue = dtotalvalue * -1;

					if( dtotalvalue <= 0 )
					{
					   ShowMessage("No Amount Due to Charge");
					   return;

                    }


					AnsiString sexp;

					AnsiString s;
					AnsiString sexpdate = strExpDate;
					AnsiString scard = strCC;
					AnsiString svalue = FloatToStr(dtotalvalue);
					AnsiString ssec = "";

					sexpdate = sexpdate.SubString(3,2)+sexpdate.SubString(1,2);
					s = "\"C1\",\"VIVALDI5\",\""+MainMenuForm->strPickupAccount.Trim()+"\",\""+scard.Trim()+"\",\""+sexpdate.Trim()+"\",\""+svalue+"\",\""+MainMenuForm->strPickupZip+"\",\""+MainMenuForm->strPickupAddress+"\",\""+ssec+"\"";


					fprintf(stream2 , "%s \n", s );


					fclose(stream2);



					Caption = filename2+" - Waiting for Response ";
				   	if( scard.SubString(0,4) == "4111" )
					  ShowMessage("Card Swipe is: "+ scard+"  Press OK to Send the Card to Process!");




				  Caption = filename;
				   Caption = "Opening Answer File";
				 AnsiString stag = ".";
				 int i = 0;

				 while ((stream = fopen(filename2.c_str(), "r")) == NULL)
				   {
					 // sleep(50);
					 i++ ;
					 if( i == 20 )
					 {
					   stag = ".";
					   i = 0;
					 }
					 else
						 stag = stag + ".";

					  /* display an error message */
					  Caption = filename2+" - Waiting for Response "+stag;

				   }


				char msg[200];
				 AnsiString scheck2,sBuf;


				 while( sBuf.Length() == 0  )
				 {
				  Caption = "Waiting for Credit Card to Process";
				   fseek(stream, 0, SEEK_SET);
				   fgets(msg, 200, stream);  // gets the Contract
				   sBuf = msg;
				   scheck2 = sBuf.SubString(2,1);
				 }
				 fclose(stream);



				 if( scheck2 != "Y" )
				 {
				 if( MainMenuForm->blnCancel == false )
	 {

			ADOQuery2->Insert();
			ADOQuery2->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
			ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;

			ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery2->FieldByName("NAME")->AsString = ADOQuery1->FieldByName("NAME")->AsString;
			ADOQuery2->FieldByName("REFERENCE")->AsString = "PAYMENT";
			ADOQuery2->FieldByName("AMT")->AsString = 0;
			ADOQuery2->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
			ADOQuery2->FieldByName("AMTPAID")->AsFloat = MainMenuForm->fTendered;
			ADOQuery2->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			ADOQuery2->FieldByName("DUE")->AsString = 0;
			ADOQuery2->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery2->FieldByName("STATUS")->AsString =  "OPEN";

			ADOQuery2->Post();



		 ADOQuery3->Active = false;
		 ADOQuery3->SQL->Clear();
		 ADOQuery3->SQL->Add("Select * from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and id = -1");
		 ADOQuery3->Active = true;
		 ADOQuery3->Insert();
			ADOQuery3->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery3->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery3->FieldByName("AMTPAID")->AsFloat =  MainMenuForm->fTendered;
			ADOQuery3->FieldByName("ACCT")->AsString =  	ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery3->FieldByName("NAME")->AsString =  	ADOQuery1->FieldByName("NAME")->AsString;
			//ADOQuery3->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery3->FieldByName("AMT")->AsString =  	MainMenuForm->fTendered;
			ADOQuery3->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery3->FieldByName("DUE")->AsFloat = MainMenuForm->fTendered;
			ADOQuery3->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			//ADOQuery3->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery3->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery3->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery3->Post();
			ADOQuery3->Active = false;
	 }

	  double dTotal = 0;
	  double dPaid = 0;

	  ADOQuery2->First();
	  while(! ADOQuery2->Eof )
	  {
		 dTotal = dTotal +  ADOQuery2->FieldByName("AMT")->AsFloat;
		 dPaid = dPaid +  ADOQuery2->FieldByName("AMTPAID")->AsFloat;
		 ADOQuery2->MoveBy(1);

	  }

		 ADOQuery4->Active = false;
		 ADOQuery4->SQL->Clear();
		 ADOQuery4->SQL->Add("Select * from INVOICEHISTORY where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and id = -1");
		 ADOQuery4->Active = true;


		ADOQuery4->Open();
		ADOQuery4->Insert();
	   ADOQuery4->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

	   ADOQuery4->FieldByName("DESCRIPTION")->AsString = "Payment Made: "+ FloatToStrF(MainMenuForm->fTendered  , ffCurrency, 12, 2);
	   ADOQuery4->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	   ADOQuery4->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
	   ADOQuery4->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
	   ADOQuery4->FieldByName("ORDERNO")->AsString = "0";
	   ADOQuery4->FieldByName("ACCT")->AsString = 	ADOQuery1->FieldByName("ACCT")->AsString;
	   ADOQuery4->Post();
	   ADOQuery4->Close();


	  Label5->Text =  FloatToStrF(dTotal, ffGeneral, 12, 2);
	  Label6->Text =  FloatToStrF(dPaid, ffGeneral, 12, 2);

	   Label3->Text =   FloatToStrF(dPaid - dTotal, ffGeneral, 12, 2);


	 MainMenuForm->blnReturnTendered = false;
				 }
				 else
				 {
				ShowMessage("Credit Card Declined "+sBuf );

				 }
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::MetropolisUIListBoxItem2Click(TObject *Sender)
{
    Button25Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::MetropolisUIListBoxItem3Click(TObject *Sender)
{
AnsiString semail =  ADOQuery1->FieldByName("EMAIL")->AsString;
AnsiString sname =  ADOQuery1->FieldByName("NAME")->AsString;
AnsiString sOrderNo =  Edit1->Text;

 if( ADOQuery1->Eof == false && semail.AnsiPos("@") != 0 && MainMenuForm->blnSendReadyEmail)
{
		 Label4->Text = "Sending Email now... Please Wait";
			SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\FOLLOW\\BLAT.EXE";

   AnsiString strParam;


   strParam =  "-to "+ semail +"  -body \" "+"Bill reminder from "+  MainMenuForm->strStoreName  +". Just a reminder that your current bill of $"+Label3->Text+" is overdue.     \" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Bill Reminder from "+MainMenuForm->strStoreName +"\" ";



   int iSize = strParam.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   strParam.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_MINIMIZE;


   if(! ShellExecuteEx(&execinfo))
   {
		ShowMessage("Could Not Run Report Writer. Check that Blat.exe is Installed!");
		return;
   }

   ShowMessage("Email has been Sent");


   }
   else
   {

     ShowMessage("Customer has no emai on account");
   }

}


//---------------------------------------------------------------------------






void __fastcall TAccountForm01::MetropolisUIListBoxItem4Click(TObject *Sender)
{

if( ADOQuery1->Eof)
{
	ShowMessage("No Customer Selected");
}
	MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
	TCommonCustomForm *FM_DATEPICKERFORM = Application->GetDeviceForm(L"FM_DATEPICKER");
		if (FM_DATEPICKERFORM)
		{


			if( FM_DATEPICKERFORM->ShowModal() == mrOk )
			{

			}

			delete FM_DATEPICKERFORM;

		}

				  AnsiString strDateCommand = "UPDATE STORE SET DATEOUTPARAM = '"+MainMenuForm->strDateOut +"' where Store = '"+ MainMenuForm->strStoreNo+ "'";

					 ADOQuery6->Active = false;
					ADOQuery6->SQL->Clear();
					ADOQuery6->SQL->Add(strDateCommand);
						ADOQuery6->ExecSQL();


					if( MainMenuForm->strCustomerARStatement == "" )
			{
					MainMenuForm->strReportFileName = "ARStatementAll.rdl";
			}
			else
			{
				 MainMenuForm->strReportFileName = MainMenuForm->strCustomerARStatement;
            }


			MainMenuForm->strReportName = "AR Statement Report";
			MainMenuForm->strReportFilter = "";

			MainMenuForm->strDataSet = "ARSTATEMENT" ;




		 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

	if( MainMenuForm->blnLocalDatabase ) {

				execinfo.lpFile = L"C:\\FOLLOW\\ReportViewerLocal.exe";

   } else {


	execinfo.lpFile = L"C:\\FOLLOW\\ReportViewer.exe";


   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = MainMenuForm->strStoreNo+ "  "+MainMenuForm->strReportFileName+" 1 PREVIEW ARSTATEMENT ALL FALSE";
				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
						return;
				   }
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image27Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image28Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image29Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image30Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image31Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image32Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image33Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image35Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "-";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image1Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "A";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image2Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "B";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image3Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "C";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image4Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "D";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image5Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "E";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image6Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "F";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image7Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "G";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image8Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "H";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image9Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "I";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image10Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "J";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image11Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "K";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image12Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "L";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image13Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "M";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image14Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "N";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image15Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "O";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image16Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "P";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image17Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Q";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image18Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "R";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image19Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "S";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image20Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "T";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image23Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "U";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image21Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "V";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image22Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "W";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image24Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "X";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image25Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Y";
}
//---------------------------------------------------------------------------

void __fastcall TAccountForm01::Image26Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Z";
}
//---------------------------------------------------------------------------

