//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "RouteForm2.h"
#include "MainMenu.h"
#include "DeliveryForm2.h"
#include <shellapi.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TRouteForm1 *RouteForm1;
//---------------------------------------------------------------------------
__fastcall TRouteForm1::TRouteForm1(TComponent* Owner)
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
void __fastcall TRouteForm1::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void TRouteForm1::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------


void __fastcall TRouteForm1::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TRouteForm1::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TRouteForm1::SelectCustomerListBoxItemClick(TObject *Sender)
{


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

			//SaveChangesIListBoxItem->Visible = false;
		   //	SavePrintListBoxItem->Visible = false;
		   //	QuickTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Enabled = true;
}




void __fastcall TRouteForm1::EditCustomerListBoxItemClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;


}
//---------------------------------------------------------------------------


void __fastcall TRouteForm1::AddCustomerListBoxItemClick(TObject *Sender)
{
	//SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;

	if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();




	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Storeno")->AsString = MainMenuForm->strStoreNo;





}
//---------------------------------------------------------------------------




void __fastcall TRouteForm1::SaveChangesIListBoxItemClick(TObject *Sender)
{
	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();



}
//---------------------------------------------------------------------------





void __fastcall TRouteForm1::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TRouteForm1::UpdateTicketView()
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
void __fastcall TRouteForm1::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TRouteForm1::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button8Click(TObject *Sender)
{
   SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
	execinfo.lpVerb = L"open";

	execinfo.lpFile = L"C:\\CML\\CML.exe";

	//AnsiString pw;
	//pw =  " /TC:\\VIVALDI\\REPORTS\\RPTFMT.TXT ";

   execinfo.lpParameters = L" C:\\CML\\CustomerReport.rpt /L1 C:\\vivaldi8\\vivaldi.dsn,DB_53817_vivaldis,db_53817_vivaldis_user,DMNN";  //pw.c_str();
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

void __fastcall TRouteForm1::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button13Click(TObject *Sender)
{
		TDeliveryForm01* DeliveryForm01;
		Application->CreateForm(__classid(TDeliveryForm01), &DeliveryForm01);
		if (DeliveryForm01 )
		{
			DeliveryForm01->ShowModal();
			delete DeliveryForm01;
		}

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button9Click(TObject *Sender)
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


void __fastcall TRouteForm1::FormShow(TObject *Sender)
{

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from HOTELRTE where Storeno = '"+ MainMenuForm->strStoreNo+ "'  Order by Route";
	  ADOQuery1->Active = true;


		  this->Fill->Color = MainMenuForm->iBackgroundColor ;



}
//---------------------------------------------------------------------------




void __fastcall TRouteForm1::MetropolisUIListBoxItem1Click(TObject *Sender)
{
			MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Record?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery1->Delete();

	}
}
//---------------------------------------------------------------------------




void __fastcall TRouteForm1::Button1Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryPickup.rdl";
			MainMenuForm->strReportName = "Delivery Pickup Report";
			MainMenuForm->blnDisableDates  = true;
			MainMenuForm->strReportFilter = "ALL";
			MainMenuForm->strAdditionalFilter =  "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"'";
			MainMenuForm->strDataSet = "CUSTOMER";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::MetropolisUIListBoxItem2Click(TObject *Sender)
{
 if( MainMenuForm->blnUseDeliveryVacation )
	 {

	  ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
	  ADOQuery3->SQL->Text = "UPDATE CUSTOMER SET  ONVACATION = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND VACATIONTILL <= GETDATE() AND VACATIONTILL IS NOT NULL AND ONVACATION = 1";
	  ADOQuery3->ExecSQL();
		}


TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryPickup.rdl";
			MainMenuForm->strReportName = "Delivery Pickup Report";
			MainMenuForm->blnDisableDates  = true;
			MainMenuForm->strReportFilter = "ALL";
					if( MainMenuForm->blnUseDeliveryVacation )
	 {
			MainMenuForm->strAdditionalFilter =  "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' And IsActive = '1'  And And (OnVacation = 0 or Onvacation is Null) ";
	  }
	  else
	  {
			MainMenuForm->strAdditionalFilter =  "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' And IsActive = '1' ";


	  }
			MainMenuForm->strDataSet = "CUSTOMER";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button10Click(TObject *Sender)
{
//http://www.gebweb.net/optimap/


ShowMessage("After copying the list of addresses, Select the bulk add by address option and paste the addresses in.  Then select Add list of locations.  Then select Calculate faster A - Z Trip.");

//Memo2->CopyToClipboard();

 //ADOQuery5->Active = false;


	  //ADOQuery5->SQL->Clear();
	 // ADOQuery5->SQL->Text = "Select TOP 1 ACCT,NAME, ADDRESS1, CITY, STATE, ZIP, EMAIL from CUSTOMER where acct like '%"+ADOQuery2->FieldByName("ACCT")->AsString+"%' AND STORE = '"+MainMenuForm->strStoreNo  +"'";
	 // ADOQuery5->Active = true;


				  // AnsiString strAddress1 = ADOQuery5->FieldByName("ADDRESS1")->AsString;

				  // AnsiString strCity = ADOQuery5->FieldByName("CITY")->AsString;
				  // AnsiString strState = ADOQuery5->FieldByName("STATE")->AsString;
				 //  AnsiString strZip = ADOQuery5->FieldByName("ZIP")->AsString ;
				   AnsiString strTemp = "http://www.gebweb.net/optimap/"; //"+ ADOQuery5->FieldByName("ADDRESS1")->AsString+","+ strCity +","+ strState+","+ strZip+"\"";
				   AnsiString strParam = "";


				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   wchar_t *str = new wchar_t[strTemp.WideCharBufSize()];

				   execinfo.lpFile = strTemp.WideChar(str, strTemp.WideCharBufSize()); // strTemp.c_str();                                  // \L"http:\\\\maps.google.com\\";
					 

				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not connect to the Vivaldi Web site!");
						return;
				   }

		   //ADOQuery5->Active = true;



}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button12Click(TObject *Sender)
{

//Memo2->CopyToClipboard();

Memo2->SelectAll();

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button11Click(TObject *Sender)
{
	 ADOQuery2->Active = false;

     Memo2->Lines->Clear();

	 ADOQuery2->SQL->Clear();
	 ADOQuery2->SQL->Text = "Select ACCT,NAME, ADDRESS1, CITY, STATE, ZIP, EMAIL from CUSTOMER where ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND ADDRESS1 IS NOT NULL AND CITY IS NOT NULL AND ISACTIVE = 1 ORDER BY STOP";
	 ADOQuery2->Active = true;

	 AnsiString strAddress1, strCity,strState, strZip, strTemp;

	 ADOQuery2->First();

	 while( ! ADOQuery2->Eof )
	 {
			strAddress1 = ADOQuery2->FieldByName("ADDRESS1")->AsString;
			strCity = ADOQuery2->FieldByName("CITY")->AsString;
			strState = ADOQuery2->FieldByName("STATE")->AsString;
			strZip = ADOQuery2->FieldByName("ZIP")->AsString ;
			strTemp = strAddress1+","+ strCity +","+ strState+","+strZip;

			Memo2->Lines->Add(strTemp);

		 ADOQuery2->MoveBy(1);
     }



   ADOQuery2->Active = false;

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button25Click(TObject *Sender)
{
 ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
	  ADOQuery3->SQL->Text = "UPDATE CUSTOMER SET ONETIMEPICKUP = 0, ROUTE = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND ONETIMEPICKUP = 1";
	  ADOQuery3->ExecSQL();

	  ShowMessage("Update Complete");
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::SpeedButton5Click(TObject *Sender)
{

	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


		TabControl1->TabIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::SpeedButton6Click(TObject *Sender)
{
	TabControl1->TabIndex = 1;

	//SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
	//SaveChangesIListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::SpeedButton2Click(TObject *Sender)
{
	MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Record?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery1->Delete();

	}
}
//---------------------------------------------------------------------------

void __fastcall TRouteForm1::Button26Click(TObject *Sender)
{
if( MainMenuForm->blnUseDeliveryVacation )
	 {

	  ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
	  ADOQuery3->SQL->Text = "UPDATE CUSTOMER SET  ONVACATION = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND VACATIONTILL <= GETDATE() AND VACATIONTILL IS NOT NULL AND ONVACATION = 1";
	  ADOQuery3->ExecSQL();
		}


TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryPickup.rdl";
			MainMenuForm->strReportName = "Delivery Pickup Report";
			MainMenuForm->blnDisableDates  = true;
			MainMenuForm->strReportFilter = "ALL";
					if( MainMenuForm->blnUseDeliveryVacation )
	 {
			MainMenuForm->strAdditionalFilter =  "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' And IsActive = '1'  And And (OnVacation = 0 or Onvacation is Null) ";
	  }
	  else
	  {
			MainMenuForm->strAdditionalFilter =  "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' And IsActive = '1' ";


	  }
			MainMenuForm->strDataSet = "CUSTOMER";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

