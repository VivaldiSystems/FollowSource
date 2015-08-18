//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "CustomerForm2.h"
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
TCustomerForm01 *CustomerForm01;
//---------------------------------------------------------------------------
__fastcall TCustomerForm01::TCustomerForm01(TComponent* Owner)
	: TForm(Owner)
{
		 TabControl1->TabIndex = 0;
		// SaveChangesIListBoxItem->Visible = false;
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

			 ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;
			Label26->Text = "Sub Total:   $0.00";
			 ADOQuery4->Active = true;

			  ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = "+ MainMenuForm->strStoreNo+ " Order by ROUTE");
			ADOQuery5->Active = true;


			Edit1->Text = MainMenuForm->strLastSearch;

			Label23->Text = "Select Item";
		 Edit1->SetFocus();

		 	if( MainMenuForm->strLastSearch != "" && MainMenuForm->blnAutoSelectLastCustomer )
				Button1Click(Owner);

}
//---------------------------------------------------------------------------
void __fastcall TCustomerForm01::HeaderButtonClick(TObject *Sender)
{


 if( ! ADOQuery1->Eof && (Edit3->Text == "" ||  Edit4->Text == "" ) )
  {
	ADOQuery1->Active = false;
  ADOQuery2->Active = false;
   ADOQuery3->Active = false;
	ADOQuery4->Active = false;
	 ADOQuery5->Active = false;
	  ADOQuery6->Active = false;

	Close();

  }
   else
   {


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

		   if(  ComboBox1->Selected != NULL && ComboBox1->Selected->Text  != "" )
		   {
					ADOQuery5->First();
					TLocateOptions SearchOptions;
					SearchOptions << loCaseInsensitive;

					ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

				if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
				{

					 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

				}
		    }

		 ADOQuery1->Post();
	   }



 ADOQuery1->Active = false;
  ADOQuery2->Active = false;
   ADOQuery3->Active = false;
	ADOQuery4->Active = false;
	 ADOQuery5->Active = false;
	  ADOQuery6->Active = false;

	Close();
	   }

}
//---------------------------------------------------------------------------

void TCustomerForm01::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TCustomerForm01::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";
	  MainMenuForm->strLastSearch = Edit1->Text;
	  //ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	   if( Edit35->Text != "" )
	  {

		  ADOQuery1->SQL->Clear();

		 ADOQuery1->SQL->Text = "Select * from customer where accountnumber like '%"+Edit35->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by accountnumber";



	  }
	  else
	  {

	  if( Edit34->Text == "" )
	  {

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {
	   ADOQuery1->SQL->Clear();

	   ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
	   ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by name";


	  }
	  }
	  else
	  {

		   if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {
		ADOQuery1->SQL->Clear();

		ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND ROUTE = '"+Edit34->Text +"' order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")  AND ROUTE = '"+Edit34->Text +"' order by name";


	  }


	  }
	   }
	  ADOQuery1->Active = true;

	  if( ADOQuery1->Eof == false )
	  {
		 // WriteTicketListBoxItem->Enabled = true;
		 // QuickTicketListBoxItem->Enabled = true;
		 // EditCustomerListBoxItem->Enabled = true;
	  }
	  else
	  {
		 // WriteTicketListBoxItem->Enabled = false;
		 // QuickTicketListBoxItem->Enabled = false;
		 // EditCustomerListBoxItem->Enabled = false;
      }

}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TCustomerForm01::SelectCustomerListBoxItemClick(TObject *Sender)
{




 //SaveChangesIListBoxItem->SubTitle = "";

	 //MetropolisUIListBoxItem1->Enabled = false;

      Label41->Visible = false;


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

		   if(  ComboBox1->Selected != NULL && ComboBox1->Selected->Text  != "" )
		   {
					ADOQuery5->First();
					TLocateOptions SearchOptions;
					SearchOptions << loCaseInsensitive;

					ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

				if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
				{

					 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

				}
		    }

		 ADOQuery1->Post();
	   }




		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

		  //	SaveChangesIListBoxItem->Visible = false;
		   //	SavePrintListBoxItem->Visible = false;
		   //	QuickTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Enabled = true;

            if( ADOQuery1->Eof == false )
	  {
		 // WriteTicketListBoxItem->Enabled = true;
		 // QuickTicketListBoxItem->Enabled = true;
		//  EditCustomerListBoxItem->Enabled = true;
	  }
	  else
	  {
		 // WriteTicketListBoxItem->Enabled = false;
		 // QuickTicketListBoxItem->Enabled = false;
		  // EditCustomerListBoxItem->Enabled = false;
      }


}




void __fastcall TCustomerForm01::EditCustomerListBoxItemClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

   //	SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;

	Edit4->Enabled = false;
   //	 SaveChangesIListBoxItem->SubTitle = "";
	ComboEdit1->Text = ADOQuery1->FieldByName("STARCH")->AsString;

	CalendarEdit2->Text = ADOQuery1->FieldByName("VACATIONTILL")->AsString;

	  ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = "+ ADOQuery1->FieldByName("STORE")->AsString+ " Order by ROUTE");
			ADOQuery5->Active = true;

     Label41->Visible = false;
	//MetropolisUIListBoxItem1->Enabled = true;
   //WriteTicketListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::AddCustomerListBoxItemClick(TObject *Sender)
{


	if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	{
			if(  ADOQuery1->FieldByName("ACCT")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Phone number for the Account before trying to Save a Customer Record.  If you don't have a phone number then press the Assign button to Assign a Sequential number for the account.");

		}

		if(  ADOQuery1->FieldByName("NAME")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Name for the Customer before trying to Save a Customer Record.");

		}

		 ADOQuery1->Post();

	 }
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;
   //	SaveChangesIListBoxItem->Visible = true;
	// SaveChangesIListBoxItem->SubTitle = "";
     Edit4->Enabled = true;

     Label41->Visible = false;

	if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

	if(  ADOQuery1->Active == false )
	{
	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from customer where id = -1 And STORE IN ("+MainMenuForm->strEnterprise +") order by acct";
	  ADOQuery1->Active = true;
	}
   	Edit4->Enabled = true;


	ADOQuery10->Active = false;
	ADOQuery10->SQL->Clear();
	ADOQuery10->SQL->Add("Select CITY,STATE,ZIP from Store where Store = "+ MainMenuForm->strStoreNo+ "");
	ADOQuery10->Active = true;


	 ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = "+ MainMenuForm->strStoreNo+ " Order by ROUTE");
			ADOQuery5->Active = true;


	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Store")->AsString = MainMenuForm->strStoreNo;
	ADOQuery1->FieldByName("LASTTRAN")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
	ADOQuery1->FieldByName("OPENDATE")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
	ADOQuery1->FieldByName("LASTTRANS")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
	ADOQuery1->FieldByName("Cash")->AsBoolean = false;
	ADOQuery1->FieldByName("CLHotel")->AsBoolean = false;
	ADOQuery1->FieldByName("Loyalty")->AsBoolean = false;

		ADOQuery1->FieldByName("DEFAULTLOYALTY")->AsBoolean = false;
				ADOQuery1->FieldByName("ONVACATION")->AsBoolean = false;
						ADOQuery1->FieldByName("ONETIMEPICKUP")->AsBoolean = false;

							ADOQuery1->FieldByName("USEDELIVERYVACATION")->AsBoolean = false;
				ADOQuery1->FieldByName("ALERT")->AsBoolean = false;
						ADOQuery1->FieldByName("REGULARROUTE")->AsBoolean = false;

		ADOQuery1->FieldByName("VIP")->AsBoolean = false;
	ADOQuery1->FieldByName("Account")->AsBoolean = false;
	ADOQuery1->FieldByName("WholeSale")->AsBoolean = false;
	ADOQuery1->FieldByName("Tax")->AsBoolean =  MainMenuForm->blnDefaultNewTaxable;
	ADOQuery1->FieldByName("IsActive")->AsBoolean = true;


		ADOQuery1->FieldByName("CITY")->AsString = ADOQuery10->FieldByName("CITY")->AsString;
	ADOQuery1->FieldByName("STATE")->AsString =  ADOQuery10->FieldByName("STATE")->AsString;
	ADOQuery1->FieldByName("ZIP")->AsString =   ADOQuery10->FieldByName("ZIP")->AsString;

	if( MainMenuForm->blnDefaultLoyalty )
		ADOQuery1->FieldByName("LOYALTY")->AsBoolean = true;


		ADOQuery10->Active = false;


		CalendarEdit2->Text = "";

    ComboEdit1->Text = "(Select)";
 

	 Edit3->SetFocus();
}
//---------------------------------------------------------------------------



void __fastcall TCustomerForm01::Button5Click(TObject *Sender)
{


    ADOQuery3->Active = false;
	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("Select * from UPCHARGE where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
	ADOQuery3->Active = true;
	blnUpcharge = true;

	Label23->Text = "Select Upcharge";

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{

	if(  ADOQuery1->FieldByName("ACCT")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Phone number for the Account before trying to Save a Customer Record.  If you don't have a phone number then press the Assign button to Assign a Sequential number for the account.");

		}

		if(  ADOQuery1->FieldByName("NAME")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Name for the Customer before trying to Save a Customer Record.");

		}

	ADOQuery11->Active = false;
	ADOQuery11->SQL->Clear();
	ADOQuery11->SQL->Add("select max(id) AS ID from customer c1 where c1.Acct = '"+ ADOQuery1->FieldByName("ACCT")->AsString +"' and c1.STORE = "+MainMenuForm->strStoreNo  +"  and 1 < (select count(id) from customer where c1.store = customer.store and c1.acct = customer.acct)");
	ADOQuery11->Active = true;

		if( ADOQuery11->Eof == false && ADOQuery11->FieldByName("ID")->AsString != "")
		{
		   ShowMessage("This customer Account is already in your Store!  Try searching by Account Number and you will find it.  You should eithor change the Account number under Tools using the Global account change or remove this customer.  Some reports will not work with duplicate account numbers.  If this customer has the same phone number as another customer then put an A,B,C at the end of the account");

		}
	   ADOQuery11->Active = false;

	   if( CalendarEdit2->Text != "" )
	   {
			ADOQuery1->Edit();
		   ADOQuery1->FieldByName("VACATIONTILL")->AsString = CalendarEdit2->Text;
		}

	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

		   if(  ComboBox1->Selected != NULL && ComboBox1->Selected->Text  != "" )
		   {
					ADOQuery5->First();
					TLocateOptions SearchOptions;
					SearchOptions << loCaseInsensitive;

					ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

				if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
				{
					  ADOQuery1->Edit();
					 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

				}
			}
			Edit4->Enabled = false;


		 ADOQuery1->Post();

		 Label41->Visible = true;
	   //	 SaveChangesIListBoxItem->SubTitle = "Saved";
          ShowMessage("Changes Saved");

	   }

	

}
//---------------------------------------------------------------------------



void __fastcall TCustomerForm01::Label24Click(TObject *Sender)
{
	  //	LeftLayout->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::TicketItemsListBoxClick(TObject *Sender)
{

	int iLBI = TicketItemsListBox->ItemIndex;
	ADOQuery3->First();
	ADOQuery3->MoveBy(iLBI);

	if( ! ADOQuery3->Eof )
	{
		if( blnUpcharge )
		{


			float ftempqty = StrToFloat( strQty );


			strUpcharge = strUpcharge + " "+  ADOQuery3->FieldByName("Item")->AsString+"("+strQty+")";
			fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;
			aPrices[TempListQty->Count - 1] = aPrices[TempListQty->Count - 1] + fltPrice;
			aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice * ftempqty );

			TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
			UpdateTicketView();

			blnUpcharge = false;

			blnSubDCItem = false;

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;

			ListBox1->Enabled = true;
            Label23->Text = "Select SubItem";
		}
		else
		{
		if( blnSubDCItem == false )
		{
			AnsiString strItem = ADOQuery3->FieldByName("Code")->AsString + "-"+  ADOQuery3->FieldByName("Item")->AsString ;
			AnsiString strItemCode =   ADOQuery3->FieldByName("Code")->AsString;
			AnsiString newClass = "("+strClass+")";



			AnsiString newString = strItem + newClass;

			TempListItemDescription->Add(newString);
			TempListQty->Add(strQty.Trim());

			fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;
			aPrices[TempListQty->Count - 1] = fltPrice;
			aLinePrices[TempListQty->Count - 1] = fltPrice * StrToFloat(strQty);




			if( strUpcharge.IsEmpty() || strUpcharge == NULL ||  strUpcharge != ""  )
				 strUpcharge = " ";

			TempListItemUpcharge->Add(strUpcharge);

			strUpcharge = "";

			UpdateTicketView();

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from SUBDCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' and ItemCode = '"+ strItemCode+"' Order by Code");
			ADOQuery3->Active = true;

			if( ! ADOQuery3->Eof )
			{
				  Label23->Text = "Select SubItem";
				  blnSubDCItem = true;
				  ListBox1->Enabled = false;
			}
			else
			{
				blnSubDCItem = false;

				ADOQuery3->Active = false;
				ADOQuery3->SQL->Clear();
				ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
				ADOQuery3->Active = true;
				Label23->Text = "Select Item";
				ListBox1->Enabled = true;
				strQty = "1";

			 }


		}
		else
		{

			float ftempqty = StrToFloat( strQty );
			Label23->Text = "Select Item";

			strUpcharge = strUpcharge + " "+  ADOQuery3->FieldByName("Item")->AsString;
			fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;
			aPrices[TempListQty->Count - 1] = aPrices[TempListQty->Count - 1] + fltPrice;
			aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice * ftempqty );

			TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
			UpdateTicketView();


			blnSubDCItem = false;

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;

			ListBox1->Enabled = true;
			strQty = "1";
		}
		}

    }



}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TCustomerForm01::UpdateTicketView()
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
void __fastcall TCustomerForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button4Click(TObject *Sender)
{

ADOQuery3->Active = false;
ADOQuery3->SQL->Clear();
ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
ADOQuery3->Active = true;


}
//---------------------------------------------------------------- -----------

void __fastcall TCustomerForm01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button8Click(TObject *Sender)
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

void __fastcall TCustomerForm01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ListBox1Click(TObject *Sender)
{
	int iLBI = ListBox1->ItemIndex;


	ADOQuery4->First();
	ADOQuery4->MoveBy(iLBI);


	if( ! ADOQuery4->Eof )
	{

		strClass = ADOQuery4->FieldByName("Code")->AsString;


		ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = "+ MainMenuForm->strStoreNo+ " and Class = '"+strClass+"' Order by Code");
		ADOQuery3->Active = true;


   }
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button9Click(TObject *Sender)
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


void __fastcall TCustomerForm01::Button12Click(TObject *Sender)
{
	 ADOQuery7->Active = false;
			ADOQuery7->SQL->Clear();
			ADOQuery7->SQL->Add("Select * from INVOICEHISTORY where Storeno = "+ MainMenuForm->strStoreNo+ " AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' Order by ORDERNO");
			ADOQuery7->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button11Click(TObject *Sender)
{
	 ADOQuery7->Active = false;
			ADOQuery7->SQL->Clear();
			ADOQuery7->SQL->Add("Select * from INVOICEHISTORY where Storeno = "+ MainMenuForm->strStoreNo+ " AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' and EventDate > GetDate() - 30 Order by ORDERNO");
			ADOQuery7->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button27Click(TObject *Sender)
{
  ADOQuery6->Active = false;
			ADOQuery6->SQL->Clear();
			ADOQuery6->SQL->Add("Select ORDERNO,ACCT,NAME,DATEIN,DATEOUT,QTY,AMT,STATUS,AMTPAID from INVOICE where Store = "+ MainMenuForm->strStoreNo+ " AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' AND DATEIN > GetDate() - 30 Order by ORDERNO");
			ADOQuery6->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button28Click(TObject *Sender)
{
  ADOQuery6->Active = false;
			ADOQuery6->SQL->Clear();
			ADOQuery6->SQL->Add("Select ORDERNO,ACCT,NAME,DATEIN,DATEOUT,QTY,AMT,STATUS,AMTPAID from INVOICE where Store = "+ MainMenuForm->strStoreNo+ " AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' Order by ORDERNO");
			ADOQuery6->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::CornerButton1Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
		   MainMenuForm->strReportFileName = "CustomerTicketReport.rdl";
			MainMenuForm->strReportName = "Customer Ticket Report";
			MainMenuForm->strReportFilter = "FILE";
			MainMenuForm->strDataSet = "INVOICE" ;
			MainMenuForm->strAdditionalFilter = "ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"'";
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::CheckBox3Exit(TObject *Sender)
{
if( ADOQuery1->FieldByName("ADDRESS1B")->AsString == "" )
 {

		 ADOQuery1->Edit();
		 ADOQuery1->FieldByName("ADDRESS1B")->AsString =  ADOQuery1->FieldByName("ADDRESS1")->AsString;
		 ADOQuery1->FieldByName("ADDRESS2B")->AsString =  ADOQuery1->FieldByName("ADDRESS2")->AsString;
		  ADOQuery1->FieldByName("CITYB")->AsString =  ADOQuery1->FieldByName("CITY")->AsString;

		   ADOQuery1->FieldByName("STATEB")->AsString =  ADOQuery1->FieldByName("STATE")->AsString;
 ADOQuery1->FieldByName("ZIPB")->AsString =  ADOQuery1->FieldByName("ZIP")->AsString;
  ADOQuery1->FieldByName("PHONEB")->AsString =  ADOQuery1->FieldByName("PHONE")->AsString;

 }
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button29Click(TObject *Sender)
{
  if( ! ADOQuery1->Eof && (Edit3->Text == "" ||  Edit4->Text == "" ) )
  {
	 ShowMessage("Customer Name and Account (Phone) are required to Save");
	// Edit3->SetFocus();
	 return;

  }



	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

			ADOQuery5->First();
			TLocateOptions SearchOptions;
			SearchOptions << loCaseInsensitive;

			ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

		if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
		{

			 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

		}


		 ADOQuery1->Post();
	   }
	   ADOQuery1->MoveBy(-1);

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button30Click(TObject *Sender)
{
  if( ! ADOQuery1->Eof && (Edit3->Text == "" ||  Edit4->Text == "" ) )
  {
	 ShowMessage("Customer Name and Account (Phone) are required to Save");
	// Edit3->SetFocus();
	 return;

  }



	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

			ADOQuery5->First();
			TLocateOptions SearchOptions;
			SearchOptions << loCaseInsensitive;

			ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

		if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
		{

			 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

		}


		 ADOQuery1->Post();
	   }
	   ADOQuery1->MoveBy(1);
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button13Click(TObject *Sender)
{
	MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Customer?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{

    ShowMessage("Warning!!! You will never be able to find tickets for this customer Again if you do this.  This will Permanently remove this customer!!!!!");

		ADOQuery1->Delete();
		ShowMessage("Customers is Deleted");
	}
}
//---------------------------------------------------------------------------



void __fastcall TCustomerForm01::Edit4Change(TObject *Sender)
{
 if( ADOQuery1->FieldByName("ID")->AsString == "" )
	 {
	  ADOQuery8->Active = false;
	  ADOQuery8->SQL->Clear();
	  ADOQuery8->SQL->Text = "Select * from customer where STORE IN ("+MainMenuForm->strEnterprise +") And ACCT = '"+ Edit4->Text +"'";
	  ADOQuery8->Active = true;

	  //if(  ADOQuery8->Eof == false )
	 //	 ShowMessage("Customer with this Account number already exists!");


	   ADOQuery8->Active = false;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button25Click(TObject *Sender)
{
	 Label19->Visible = true;
	 Edit31->Visible = true;
	 Button31->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button31Click(TObject *Sender)
{

				MainMenuForm->strQuestion = "Are you absolutely sure you wish replace the Acct Number for this customer?";

				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
				if (Form )
				{
					Form->ShowModal();
					delete Form;
				}
			   if( Edit31->Text == "" )
			   {
				 ShowMessage("Please enter an account number to change to!");
				 return;
			   }

				if( MainMenuForm->blnOK == true )
				{
						ShowMessage("Warning:  We are replacing all the files, changing the old customer Account # with the new one entered");


						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE INVOICE SET ACCT = '"+Edit31->Text+"' WHERE STORE = '"+MainMenuForm->strStoreNo  +"' AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();


						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE ORDERS SET ACCT = '"+Edit31->Text+"' WHERE STORE = '"+MainMenuForm->strStoreNo  +"' AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();

						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE AR SET ACCT = '"+Edit31->Text+"' WHERE STORENO = '"+MainMenuForm->strStoreNo  +"' AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();

						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE CASHBOX SET ACCT = '"+Edit31->Text+"' WHERE STORENO = '"+MainMenuForm->strStoreNo  +"' AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();



						ADOQuery1->Edit();
						ADOQuery1->FieldByName("ACCT")->AsString = Edit31->Text;
						ADOQuery1->FieldByName("PHONE")->AsString = Edit31->Text;
						ADOQuery1->Post();


                        ShowMessage("Customer Acount and Phone # has been changed");

				}


				Label19->Visible = false;
				Edit31->Visible = false;
				Button31->Visible = false;


	}


//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ComboEdit1Change(TObject *Sender)
{

	if( ADOQuery1->Active && ADOQuery5->Active )
	{
		  ADOQuery1->Edit();
		   ADOQuery1->FieldByName("STARCH")->AsString = ComboEdit1->Text;


		   if(  ComboBox1->Selected != NULL && ComboBox1->Selected->Text  != "" )
		   {
					ADOQuery5->First();
					TLocateOptions SearchOptions;
					SearchOptions << loCaseInsensitive;

					ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

				if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
				{

					 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;

				}
			}


		  // ADOQuery1->Post();
	}
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button10Click(TObject *Sender)
{
	  ADOQuery1->Edit();
	  ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
	  ADOQuery1->Post();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button32Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\VIVALDI8\\FreeVK.exe";
				   AnsiString strParam = "";
				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run FreeVK Free Virtual Keyboard. Install the FreeVK under Help!");
						return;
				   }


					Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button33Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button35Click(TObject *Sender)
{
  Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button38Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button39Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button40Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button41Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button42Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button43Click(TObject *Sender)
{
Edit1->Text = "";
}
//---------------------------------------------------------------------------




void __fastcall TCustomerForm01::Grid1DblClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

   //	SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;

	Edit4->Enabled = false;
	// SaveChangesIListBoxItem->SubTitle = "";
	ComboEdit1->Text = ADOQuery1->FieldByName("STARCH")->AsString;

	 Label41->Visible = false;

   //WriteTicketListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button44Click(TObject *Sender)
{
	 //https://maps.google.com/?q=9412+sapphire+ave,hesperia,ca,92344


				   AnsiString strAddress1 = ADOQuery1->FieldByName("ADDRESS1")->AsString;


					 strAddress1 = AnsiReplaceStr(strAddress1," ","+");

				   AnsiString strCity = ADOQuery1->FieldByName("CITY")->AsString;

					strCity = AnsiReplaceStr(strCity," ","+");

				   AnsiString strState = ADOQuery1->FieldByName("STATE")->AsString;
				   strState = AnsiReplaceStr(strState," ","+");

				   AnsiString strZip = ADOQuery1->FieldByName("ZIP")->AsString ;
				   AnsiString strTemp = "http://maps.google.com?q=\""+ strAddress1+","+ strCity +","+ strState+","+ strZip+"\"";
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


}

//wchar_t *AnsiTowchar_t(AnsiString Str)
//{
//  wchar_t *str = new wchar_t[Str.WideCharBufSize()];
//  return Str.WideChar(str, Str.WideCharBufSize());
//  delete str;
//}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::ComboBox1Change(TObject *Sender)
{
	if( ADOQuery1->Active && ADOQuery5->Active )
	{

		   if(  ComboBox1->Selected != NULL && ComboBox1->Selected->Text  != "" )
		   {
					ADOQuery5->First();
					TLocateOptions SearchOptions;
					SearchOptions << loCaseInsensitive;

					ADOQuery5->Locate("NAME",ComboBox1->Selected->Text , SearchOptions  );

				if( ADOQuery1->FieldByName("ROUTE")->AsString != ADOQuery5->FieldByName("ROUTE")->AsString)
				{
					  ADOQuery1->Edit();
					 ADOQuery1->FieldByName("ROUTE")->AsString =  ADOQuery5->FieldByName("ROUTE")->AsString;
                     // ADOQuery1->Post();
				}
		    }

       }

}
//---------------------------------------------------------------------------



void __fastcall TCustomerForm01::MetropolisUIListBoxItem1Click(TObject *Sender)
{
		MainMenuForm->strReportFileName = "ARStatement.rdl";
			MainMenuForm->strReportName = "AR Statement Report";
			MainMenuForm->strReportFilter = ADOQuery1->FieldByName("ACCT")->AsString;
			MainMenuForm->strDataSet = "ARSTATEMENT" ;

				FILE *stream;
		stream = fopen("c:\\VIVALDI8\\REPORT.TXT", "w+");

		AnsiString  s;
		s = "ACCT='"+ADOQuery1->FieldByName("ACCT")->AsString+"'";
		fprintf(stream , "%s", s);
		fclose(stream);


		 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

	if( MainMenuForm->blnLocalDatabase ) {

				execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

   } else {


	execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";


   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = MainMenuForm->strStoreNo+ "  ARSTATEMENT.RDL 1 PREVIEW ARSTATEMENT FILE FALSE";
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


void __fastcall TCustomerForm01::MetropolisUIListBoxItem2Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "CustomerReport.rdl";
			MainMenuForm->strReportName = "Customer Listing Report";
              AnsiString strNumber = "1234567890";
			MainMenuForm->strLastSearch = Edit1->Text;
	  //ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	   if( Edit35->Text != "" )
	  {



		MainMenuForm->strReportFilter = "accountnumber like '%"+Edit35->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")";



	  }
	  else
	  {

	  if( Edit34->Text == "" )
	  {

		  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
		  {


				MainMenuForm->strReportFilter = "acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")";

		  }
		  else
		  {

				MainMenuForm->strReportFilter = "name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")";


		  }
	  }
	  else
	  {
		  if( Edit1->Text.Trim() == "" )
		  {
			  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
			  {


				MainMenuForm->strReportFilter = "acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND ROUTE = '"+Edit34->Text +"'";

			  }
			  else
			  {

				MainMenuForm->strReportFilter = "name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")  AND ROUTE = '"+Edit34->Text +"'";


			  }
		 }
		 else
		 {

			MainMenuForm->strReportFilter = "STORE IN ("+MainMenuForm->strEnterprise +")  AND ROUTE = '"+Edit34->Text +"'";


         }

	  }

	  }




			MainMenuForm->strDataSet = "CUSTOMER" ;
			//Form->Label3->Text = "Customer Listing Report";
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Button45Click(TObject *Sender)
{
ShowMessage("Warning:  Assign will assign a sequential Customer Account number.  Do not press this button if you want to use Phone numbers for Account Numbers! If you pressed this by mistake then put the phone number back in");

	ADOQuery10->Active = false;
ADOQuery10->SQL->Clear();
ADOQuery10->SQL->Add("UPDATE STORE SET CUSTNUM = CUSTNUM + 1 where Store = "+ MainMenuForm->strStoreNo+ ";Select CUSTNUM from Store where Store = "+ MainMenuForm->strStoreNo+ "");
ADOQuery10->Active = true;

 ADOQuery1->Edit();
 ADOQuery1->FieldByName("ACCT")->AsString = ADOQuery10->FieldByName("CUSTNUM")->AsString;

}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::Image1Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "A";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image2Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "B";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image3Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "C";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image4Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "D";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image5Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "E";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image6Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "F";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image7Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "G";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image8Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "H";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image9Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "I";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image10Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "J";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image11Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "K";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image12Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "L";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image13Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "M";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image27Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image28Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image29Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image30Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image31Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image32Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image33Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image35Click(TObject *Sender)
{
   Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "-";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image14Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "N";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image15Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "O";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image16Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "P";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image17Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Q";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image18Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "R";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image19Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "S";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image20Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "T";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image23Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "U";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image21Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "V";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image22Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "W";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image24Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "X";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image25Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Y";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image26Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "Z";
}
//---------------------------------------------------------------------------

void __fastcall TCustomerForm01::Image38Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text.SubString(0,Edit1->Text.Length() - 1);
}
//---------------------------------------------------------------------------


void __fastcall TCustomerForm01::SpeedButton4Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\VIVALDI8\\FreeVK.exe";
				   AnsiString strParam = "";
				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run FreeVK Free Virtual Keyboard. Install the FreeVK under Help!");
						return;
				   }


				   //	Edit1->SetFocus();
}
//---------------------------------------------------------------------------

