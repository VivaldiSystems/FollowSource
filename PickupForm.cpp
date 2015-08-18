//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "PickupForm.h"

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
TPickupWindow01 *PickupWindow01;
//---------------------------------------------------------------------------
__fastcall TPickupWindow01::TPickupWindow01(TComponent* Owner)
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
          dTotalSelected = 0;
		 TempListQty = new TStringList; // declare the list
		  TempListItemCode = new TStringList; // declare the list
		   TempListItemDescription = new TStringList; // declare the list
			TempListPrice = new TStringList; // declare the list
			 TempListTax = new TStringList; // declare the list
			 TempListItemUpcharge = new TStringList; // declare the list

			   Edit1->Text = MainMenuForm->strLastSearch;
               MainMenuForm->dCouponAmount = 0;
		
			 ADOQuery4->Active = true;

			  ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' Order by ROUTE");
			ADOQuery5->Active = true;



			  ADOQuery12->Active = false;
			ADOQuery12->SQL->Clear();
			ADOQuery12->SQL->Add("Select * from Coupon where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and couponamt is not null Order by Coupon");
			ADOQuery12->Active = true;

         	Label23->Text = "Select Item";
		 Edit1->SetFocus();
        	if( MainMenuForm->strLastSearch != "" && MainMenuForm->blnAutoSelectLastCustomer )
			     Button1Click(Owner);

}
//---------------------------------------------------------------------------
void __fastcall TPickupWindow01::HeaderButtonClick(TObject *Sender)
{
	ADOQuery6->Close();
	ADOQuery5->Close();
	ADOQuery4->Close();
	ADOQuery3->Close();
	ADOQuery2->Close();
	ADOQuery1->Close();


		  MainMenuForm->blnPrePayAllToday = false;
		  MainMenuForm->strPrePayAccount = "";



	Close();
}
//---------------------------------------------------------------------------

void TPickupWindow01::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------


void __fastcall TPickupWindow01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPickupWindow01::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";

	  MainMenuForm->strLastSearch = Edit1->Text;


	  if( Edit19->Text != "" )
	  {

          ADOQuery1->SQL->Clear();

	     ADOQuery1->SQL->Text = "Select * from customer where accountnumber like '%"+Edit19->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by accountnumber";



	  }
	  else
	  {

	 // ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {

	  

	  ADOQuery8->Active = false;

	   ADOQuery1->SQL->Clear();

	   ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by name";

      }
	  }
	  ADOQuery1->Active = true;

	  if( ADOQuery1->Eof == false )
	  {
		 // WriteTicketListBoxItem->Enabled = true;
		  //QuickTicketListBoxItem->Enabled = true;
		  //EditCustomerListBoxItem->Enabled = true;

		  if( ADOQuery1->RecordCount == 1 )
		  {
             //QuickTicketListBoxItemClick(Sender);

          }
          Grid1->SetFocus();
	  }
	  else
	  {

		 ShowMessage("No Records Found! Try another search.");
		 Edit1->SetFocus();

		  // QuickTicketListBoxItem->Enabled = false;
		  // EditCustomerListBoxItem->Enabled = false;
		   return;
      }

		ADOQuery9->Active = false;
		ADOQuery9->SQL->Clear();
		ADOQuery9->SQL->Text = "Select * from AR where STORENO = '"+MainMenuForm->strStoreNo  +"' AND ID = -1";

        MainMenuForm->strCustomerAcct  = ADOQuery1->FieldByName("Acct")->AsString;


}
//---------------------------------------------------------------------------


void __fastcall TPickupWindow01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TPickupWindow01::SelectCustomerListBoxItemClick(TObject *Sender)
{
		TabControl1->TabIndex = 0;

}




void __fastcall TPickupWindow01::EditCustomerListBoxItemClick(TObject *Sender)
{
     QuickTicketListBoxItemClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::QuickTicketListBoxItemClick(TObject *Sender)
{
 MainMenuForm->blnPayInFull = false;

 if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }

		MainMenuForm->dGiftCard = 0;

	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();



		TabControl1->TabIndex = 2;
		dTotalSelected = 0;


		ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();
		if( MainMenuForm->blnPrePayAllToday )
		{

		  ADOQuery6->SQL->Add("SELECT Top 20 *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' AND  (STATUS = 'R' OR STATUS = 'I') And Convert(varchar(10),DateIn) = Convert(Varchar(10),GetDate()) AND AMT <> AMTPAID Order by ORDERNO");

		}
		else
		{
			if(	MainMenuForm->blnShowReadyOnly )
			{
			  ADOQuery6->SQL->Add("SELECT Top 20 *,AMT - AMTPAID AS DUE from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' AND  STATUS = 'R' Order by ORDERNO");
			}
			else
			{
			   ADOQuery6->SQL->Add("SELECT Top 20 *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' AND  (STATUS = 'R' OR STATUS = 'I') Order by ORDERNO");
			}
		}

		ADOQuery6->Active = true;
		ADOQuery6->First();



		if( ADOQuery6->Eof )
		{
		   ShowMessage("This Customer has no Tickets Ready for Pickup"   );
		   return;
		}




		  MainMenuForm->strPickupAccount = ADOQuery1->FieldByName("ACCT")->AsString.Trim();
		  MainMenuForm->strPickupZip = ADOQuery1->FieldByName("ZIP")->AsString.Trim();
		  MainMenuForm->strPickupAddress = ADOQuery1->FieldByName("ADDRESS1")->AsString.Trim();

		  MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
         ADOQuery6->First();
		while( ADOQuery6->Eof == false )
		{
		if( ADOQuery6->FieldByName("Status")->AsString == "R" || MainMenuForm->blnPrePayAllToday  )
		{
			dTotalSelected = dTotalSelected + 	ADOQuery6->FieldByName("Amt")->AsFloat - (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat);

			ADOQuery6->Edit();
			ADOQuery6->FieldByName("IsActive")->AsBoolean = true;
			ADOQuery6->Post();
		}
		else
		{
			ADOQuery6->Edit();
			ADOQuery6->FieldByName("IsActive")->AsBoolean = false;
			ADOQuery6->Post();

		}

		ADOQuery6->MoveBy(1);

		}

		//Grid3->Selected = false;

		//Button30Click(Sender);
		CalculateTotalPickup();


        ADOQuery6->First();


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::AddCustomerListBoxItemClick(TObject *Sender)
{
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;
   //	SaveChangesIListBoxItem->Visible = true;

	if(  ADOQuery1->Active == false )
	{
	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from customer where id = -1 AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";
	  ADOQuery1->Active = true;
	}

    Edit4->Enabled = true;
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

     Edit3->SetFocus();



}
//---------------------------------------------------------------------------



void __fastcall TPickupWindow01::Button5Click(TObject *Sender)
{


    ADOQuery3->Active = false;
	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("Select * from UPCHARGE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
	ADOQuery3->Active = true;
	blnUpcharge = true;

	Label23->Text = "Select Upcharge";

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::SaveChangesIListBoxItemClick(TObject *Sender)
{
	  if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }

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


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


}
//---------------------------------------------------------------------------


void __fastcall TPickupWindow01::Button3Click(TObject *Sender)
{
  	ADOQuery6->Close();
	ADOQuery5->Close();
	ADOQuery4->Close();
	ADOQuery3->Close();
	ADOQuery2->Close();
	ADOQuery1->Close();


		  MainMenuForm->blnPrePayAllToday = false;
		  MainMenuForm->strPrePayAccount = "";



	Close();

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Label24Click(TObject *Sender)
{
	   //	LeftLayout->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::TicketItemsListBoxClick(TObject *Sender)
{

	int iLBI = TicketItemsListBox->ItemIndex;
	ADOQuery3->First();
	ADOQuery3->MoveBy(iLBI);

	if( ! ADOQuery3->Eof )
	{
		if( blnUpcharge )
		{


			double ftempqty = StrToFloat( strQty );


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
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
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
			ADOQuery3->SQL->Add("Select * from SUBDCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' and ItemCode = '"+ strItemCode+"' Order by Code");
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
				ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
				ADOQuery3->Active = true;
				Label23->Text = "Select Item";
				ListBox1->Enabled = true;
				strQty = "1";

			 }


		}
		else
		{

			double ftempqty = StrToFloat( strQty );
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
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;

			ListBox1->Enabled = true;
			strQty = "1";
		}
		}

    }



}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TPickupWindow01::UpdateTicketView()
{
Memo1->Lines->Clear();

AnsiString sQty;
AnsiString sItemDescription;
AnsiString sUpcharge;
AnsiString sPrice;
double fTotal = 0;


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


		 //sItemDescription = sItemDescription +  sItemDescription.StringOfChar(' ', 35 - sItemDescription.Length() );

		   Memo1->Lines->Add(sQty+"  "+sItemDescription + " (" + sPrice+")");

		if( TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
			  Memo1->Lines->Add("   "+ TempListItemUpcharge->Strings[i] );

	}

	Label26->Text = "Sub Total:  "+ FloatToStrF(fTotal  , ffCurrency, 12, 2);


}
void __fastcall TPickupWindow01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button4Click(TObject *Sender)
{

ADOQuery3->Active = false;
ADOQuery3->SQL->Clear();
ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
ADOQuery3->Active = true;


}
//---------------------------------------------------------------- -----------

void __fastcall TPickupWindow01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button8Click(TObject *Sender)
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

void __fastcall TPickupWindow01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------


void __fastcall TPickupWindow01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ListBox1Click(TObject *Sender)
{
	int iLBI = ListBox1->ItemIndex;


	ADOQuery4->First();
	ADOQuery4->MoveBy(iLBI);


	if( ! ADOQuery4->Eof )
	{

		strClass = ADOQuery4->FieldByName("Code")->AsString;


		ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
		ADOQuery3->Active = true;


   }
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button9Click(TObject *Sender)
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




void __fastcall TPickupWindow01::Grid3Click(TObject *Sender)
{

  if( Button2->Enabled == false )
  {

     return;
  }


    	ADOQuery6->Edit();

 if(  ADOQuery6->FieldByName("IsActive")->AsBoolean )
 {
	//ADOQuery6->FieldByName("IsActive")->AsBoolean = false;
	//dTotalSelected = dTotalSelected - 	(ADOQuery6->FieldByName("Amt")->AsFloat - (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat));

  //Grid3->Selected = false;
  ADOQuery6->FieldByName("IsActive")->AsBoolean = false;

  dTotalSelected = dTotalSelected - (ADOQuery6->FieldByName("Amt")->AsFloat - (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat));



  }
  else
  {
	ADOQuery6->FieldByName("IsActive")->AsBoolean = true;
	dTotalSelected = dTotalSelected +  (ADOQuery6->FieldByName("Amt")->AsFloat - (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat));


  }
	ADOQuery6->Post();
	CalculateTotalPickup();


	ADOQuery2->Active = false;
	ADOQuery2->SQL->Clear();
	ADOQuery2->SQL->Add("Select * from ORDERS where Store = '"+ MainMenuForm->strStoreNo+ "' AND ORDERNO = '"+ADOQuery6->FieldByName("ORDERNO")->AsString.Trim()+"' ORDER BY ID");
	ADOQuery2->Active = true;

	AnsiString sQty, sItemDescription, sUpcharge, sPrice;


	ADOQuery2->First();


	ListBox2->Items->Clear();
	while( ADOQuery2->Eof == false )
	{

		sQty = 	ADOQuery2->FieldByName("QTY")->AsString;
		sItemDescription = 	ADOQuery2->FieldByName("ItemDesc")->AsString;
		sUpcharge = 	ADOQuery2->FieldByName("Upcharge")->AsString;
		sPrice = 	ADOQuery2->FieldByName("AMT")->AsString;

		//sItemDescription = sItemDescription +  sItemDescription.StringOfChar(' ', 35 - sItemDescription.Length() );



		ListBox2->Items->Add(sQty+"  "+sItemDescription + " (" + sPrice+")");

		if(  sUpcharge != " ")
			  ListBox2->Items->Add("   "+ sUpcharge );

		ADOQuery2->MoveBy(1);

	}

	ADOQuery2->Active = false;



}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button2Click(TObject *Sender)
{

	MainMenuForm->blnPayInFull  = false;
	MainMenuForm->strPaidType = "";
	ADOQuery6->First();
	double fTotal = 0;
	MainMenuForm->fDeposit = 0;

	int iTotalTickets = 0;

	MainMenuForm->strCustomerAcct = ADOQuery1->FieldByName("ACCT")->AsString;
	 MainMenuForm->blnAccountCustomer  =   ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
		{
			fTotal = fTotal + ( ADOQuery6->FieldByName("AMT")->AsFloat - (ADOQuery6->FieldByName("AMTPAID")->AsFloat  ));
			MainMenuForm->fDeposit = MainMenuForm->fDeposit +  ADOQuery6->FieldByName("DEPOSIT")->AsFloat;
			iTotalTickets++;
		}

		ADOQuery6->MoveBy(1);

	}

	if( iTotalTickets == 0 )
	{
		ShowMessage("No Tickets Are Selected");
		return;
    }


	double fLocalTendered = 0;
	TCommonCustomForm *Form = Application->GetDeviceForm(L"CashdrawerView");
		if(Form)
		{

		   MainMenuForm->fTendered  = fTotal - MainMenuForm->dGiftCard;

		   Form->ShowModal();
		   fLocalTendered =  MainMenuForm->fTendered + MainMenuForm->dGiftCard;
		   delete Form;

		}
	 if( MainMenuForm->blnCancel == false )
	 {
		double fApplied = 0;

		 ADOQuery11->Active = false;

		 ADOQuery11->SQL->Clear();
		 ADOQuery11->SQL->Add("Select * from Store where Store = '"+MainMenuForm->strStoreNo  +"'");

		ADOQuery11->Active = true;




	if(true )
	{
	ADOQuery6->First();

	//float ftotalselected =  StrToFloat(Label19->Text);
	double famtpaid = 0;

	ADOQuery1->Edit();
	if( ADOQuery1->FieldByName("YTDTOTAL")->AsString == "" )
	{
		ADOQuery1->FieldByName("YTDTOTAL")->AsFloat = 0;

	}
	if( ADOQuery1->FieldByName("SPENT")->AsString == "" )
	{
		ADOQuery1->FieldByName("SPENT")->AsFloat = 0;

	}
    ADOQuery1->FieldByName("LASTTRAN")->AsString = DateTimeToStr(Now()).SubString(0,10);
	ADOQuery1->FieldByName("LASTTRANS")->AsString = DateTimeToStr(Now()).SubString(0,10);
	ADOQuery1->FieldByName("YTDTOTAL")->AsFloat = ADOQuery1->FieldByName("YTDTOTAL")->AsFloat + fLocalTendered;
	ADOQuery1->FieldByName("SPENT")->AsFloat = ADOQuery1->FieldByName("SPENT")->AsFloat + fLocalTendered;

	if( ADOQuery1->FieldByName("SPENT")->AsFloat < 100 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "NEW";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 2000 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "PLATIUM";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 1000 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "GOLD";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 500 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "SILVER";



	if( ADOQuery11->FieldByName("LOYALTY")->AsBoolean && MainMenuForm->blnDefaultLoyalty )
	{

	   if( ADOQuery11->FieldByName("BYTICKETS")->AsBoolean )
	   {
			if( ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat >= ADOQuery11->FieldByName("LOYALTYLEVEL")->AsFloat )
			{

				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
				ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat =  ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat +  ADOQuery11->FieldByName("REWARD")->AsFloat;

				ShowMessage("Customer has received "+  ADOQuery11->FieldByName("REWARD")->AsString+ " Loyalty Reward Dollars. Total of "+ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsString+" on their account. These Dollars can be used on their next Ticket.");

			}
			else
			{
				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 	ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat  + iTotalTickets;
			}


	   }
	   else
	   {
			if( ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat >= ADOQuery11->FieldByName("LOYALTYLEVEL")->AsFloat )
			{

				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
				ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat =  ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat +  ADOQuery11->FieldByName("REWARD")->AsFloat;
				ShowMessage("Customer has received "+  ADOQuery11->FieldByName("REWARD")->AsString+ " Loyalty Reward Dollars. Total of "+ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsString+" on their account. These Dollars can be used on their next Ticket.");


			}
			else
			{
				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 	ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat  + fLocalTendered;
            }

	   }
    }



	ADOQuery1->Post();

	ADOQuery11->Active = false;

	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
		{



		   ADOQuery10->Open();
		   ADOQuery10->Insert();
		   ADOQuery10->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

		  if( MainMenuForm->blnPrePayAllToday )
		  {
			   ADOQuery10->FieldByName("DESCRIPTION")->AsString = "Ticket Prepaid" ;

		  }
		  else
		  {
			 ADOQuery10->FieldByName("DESCRIPTION")->AsString = "Ticket Picked Up" ;

		  }



		   ADOQuery10->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery10->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
		   ADOQuery10->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
		   ADOQuery10->FieldByName("ORDERNO")->AsString = ADOQuery6->FieldByName("ORDERNO")->AsString;
		   ADOQuery10->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("ACCT")->AsString;
		   ADOQuery10->Post();
		   ADOQuery10->Close();


		   //ShowMessage(ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat);
		   //ShowMessage( fLocalTendered );

			ADOQuery6->Edit();
			if( ADOQuery6->FieldByName("Deposit")->AsString == "" )
		         ADOQuery6->FieldByName("Deposit")->AsString = 0;


			Currency dCleanAmt = StrToCurr(FloatToStrF(  ADOQuery6->FieldByName("AMT")->AsFloat, ffGeneral , 12, 0));
			Currency dCleanAmtPaid  =  StrToCurr(FloatToStrF( ADOQuery6->FieldByName("AmtPaid")->AsFloat , ffGeneral , 12, 0));

			fLocalTendered =  StrToFloat(FloatToStrF( fLocalTendered , ffGeneral , 12, 0));

			if( MainMenuForm->fDeposit > 0 )
			{
				if( ADOQuery6->FieldByName("AMT")->AsFloat <=  ADOQuery6->FieldByName("DEPOSIT")->AsString )
				{
				   ADOQuery6->FieldByName("DEPOSIT")->AsString = ADOQuery6->FieldByName("AMT")->AsFloat;
				   MainMenuForm->fDeposit = MainMenuForm->fDeposit - ADOQuery6->FieldByName("AMT")->AsFloat;
				}
				else
				{
					ADOQuery6->FieldByName("DEPOSIT")->AsString = MainMenuForm->fDeposit;
                    MainMenuForm->fDeposit = 0;
				}


				 MainMenuForm->strPaidType = "DEPOSIT";

			}
			else if( dCleanAmt - dCleanAmtPaid <=  fLocalTendered  )
			{
				   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;
				   ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;

                   	if( MainMenuForm->blnPrePayAllToday == false )
				   ADOQuery6->FieldByName("STATUS")->AsString = "P";


				   ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				   if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
			          ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";


			}
			else if( dCleanAmt - dCleanAmtPaid > fLocalTendered   &&  MainMenuForm->strPaidType != "ACCOUNT"  )
			{
				  fApplied = fLocalTendered;
				  ShowMessage("Customer is underpaying!  Ticket will not be marked Picked Up. Paid: "+FloatToStrF( fLocalTendered  , ffCurrency, 12, 2)+ "  Due: "+FloatToStrF( ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat  , ffCurrency, 12, 2) );
				  ADOQuery6->FieldByName("LOCATION")->AsString = "CUSTOMER/NOT PAID";
				  ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
			}
			else if( dCleanAmt - dCleanAmtPaid <= 0 )
			{
				   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;
				   ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;

					if( MainMenuForm->blnPrePayAllToday == false )
					   ADOQuery6->FieldByName("STATUS")->AsString = "P";


				   ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				  if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
					ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";

			}

			if( MainMenuForm->strPaidType == "ACCOUNT" )
			{

                   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;


			if( MainMenuForm->blnPrePayAllToday == false )
					   ADOQuery6->FieldByName("STATUS")->AsString = "P";



				   ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				   if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
						ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";

			}
			if(  MainMenuForm->blnPayInFull )
			{
				if( MainMenuForm->blnPrePayAllToday == false )
				 ADOQuery6->FieldByName("STATUS")->AsString = "P";


				 ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());


            }


			fLocalTendered = fLocalTendered - fApplied;

			if( ADOQuery6->FieldByName("AMTPAID")->AsString != "" )
			  famtpaid = (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat);
			else
			  famtpaid = 0;

			ADOQuery6->FieldByName("PAIDDATE")->AsString =  DateTimeToStr(Now());
			ADOQuery6->FieldByName("PAIDTYPE")->AsString = MainMenuForm->strPaidType;
			ADOQuery6->FieldByName("AMTPAID")->AsFloat = famtpaid + fApplied;
			ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;
			//ADOQuery6->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery6->Post();

			//ftotalselected =  ftotalselected - fApplied;
			ADOQuery7->Open();
			ADOQuery7->Insert();
			ADOQuery7->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery7->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery7->FieldByName("AMTPAID")->AsFloat =  fApplied;
			ADOQuery7->FieldByName("ACCT")->AsString =  	ADOQuery6->FieldByName("ACCT")->AsString;
			ADOQuery7->FieldByName("NAME")->AsString =  	ADOQuery6->FieldByName("NAME")->AsString;
			ADOQuery7->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery7->FieldByName("AMT")->AsString =  	ADOQuery6->FieldByName("AMT")->AsString;
			ADOQuery7->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery7->FieldByName("DUE")->AsFloat = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
			ADOQuery7->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
			ADOQuery7->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery7->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
			ADOQuery7->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery7->Post();

			if( Label59->Text != "" )
			{


			ADOQuery7->Insert();
			ADOQuery7->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery7->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery7->FieldByName("AMTPAID")->AsString =  Label59->Text;
			ADOQuery7->FieldByName("ACCT")->AsString =  	ADOQuery6->FieldByName("ACCT")->AsString;
			ADOQuery7->FieldByName("NAME")->AsString =  	ADOQuery6->FieldByName("NAME")->AsString;
			ADOQuery7->FieldByName("TAX")->AsString =  	0;
			ADOQuery7->FieldByName("AMT")->AsString =  	Label59->Text;
			ADOQuery7->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery7->FieldByName("DUE")->AsFloat = 0;
			ADOQuery7->FieldByName("PAYMENTTYPE")->AsString = "COUPON";
			ADOQuery7->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery7->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
			ADOQuery7->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery7->Post();


            }


			if( MainMenuForm->strPaidType == "ACCOUNT" )
			{


				ADOQuery9->Open();
				ADOQuery9->Insert();
				ADOQuery9->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
				ADOQuery9->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
				ADOQuery9->FieldByName("AMTPAID")->AsFloat = 0;

				if( ADOQuery6->FieldByName("BACCT")->AsString != "" )
						ADOQuery9->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("BACCT")->AsString;
				else
					ADOQuery9->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("ACCT")->AsString;



				ADOQuery9->FieldByName("NAME")->AsString = ADOQuery6->FieldByName("NAME")->AsString;
				ADOQuery9->FieldByName("TAX")->AsString = ADOQuery6->FieldByName("TAX")->AsString;
				ADOQuery9->FieldByName("AMT")->AsString = ADOQuery6->FieldByName("AMT")->AsString;
				ADOQuery9->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
				ADOQuery9->FieldByName("DUE")->AsFloat = ADOQuery6->FieldByName("AMT")->AsFloat; // - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
				ADOQuery9->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
				ADOQuery9->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
				ADOQuery9->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
				ADOQuery9->FieldByName("STATUS")->AsString =  "OPEN";
				//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

				ADOQuery9->Post();


            }

		}

		ADOQuery6->MoveBy(1);

	}
	ADOQuery6->Close();
	ADOQuery6->Open();


   //	Label19->Text =  FloatToStrF(ftotalselected  , ffCurrency, 12, 2);

    ADOQuery6->Close();
	ADOQuery5->Close();
	ADOQuery4->Close();
	ADOQuery3->Close();
	ADOQuery2->Close();
	ADOQuery1->Close();


			if( MainMenuForm->blnPrePayAllToday )
		{
		  MainMenuForm->blnPrePayAllToday = false;
		  MainMenuForm->strPrePayAccount = "";

		}


	this->Close();

	}

    CalculateTotalPickup();
    }

}
//---------------------------------------------------------------------------


void __fastcall TPickupWindow01::Button27Click(TObject *Sender)
{
		ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();
		ADOQuery6->SQL->Add("SELECT *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' And ( Status = 'I' or Status = 'R')  Order by ORDERNO");
		ADOQuery6->Active = true;

		Button30->Enabled = true;
		Button31->Enabled = true;
		Button2->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button28Click(TObject *Sender)
{
		ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();
		ADOQuery6->SQL->Add("SELECT *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"'  And Status = 'R' Order by ORDERNO");
		ADOQuery6->Active = true;
			Button30->Enabled = true;
		Button31->Enabled = true;
		Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button29Click(TObject *Sender)
{
		ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();
		ADOQuery6->SQL->Add("SELECT *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' And Status = 'I' Order by ORDERNO");
		ADOQuery6->Active = true;
		Button30->Enabled = true;
		Button31->Enabled = true;
		Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button30Click(TObject *Sender)
{
	ADOQuery6->First();

	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
		{

			ADOQuery6->Edit();
			ADOQuery6->FieldByName("IsActive")->AsBoolean = false;
			ADOQuery6->Post();
		}
		ADOQuery6->MoveBy(1);

	}
		dTotalSelected = 0;

	CalculateTotalPickup();
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button31Click(TObject *Sender)
{
	ADOQuery6->First();
	dTotalSelected = 0;

	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean == false )
		{
				dTotalSelected = dTotalSelected + (ADOQuery6->FieldByName("Amt")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat);

			ADOQuery6->Edit();
			ADOQuery6->FieldByName("IsActive")->AsBoolean = true;
			ADOQuery6->Post();
		}
		ADOQuery6->MoveBy(1);

	}

	CalculateTotalPickup();
}

void __fastcall TPickupWindow01::CalculateTotalPickup()
{

	Label19->Text =  FloatToStrF(dTotalSelected  , ffCurrency, 12, 2);



}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::FormShow(TObject *Sender)
{

//this->Fill->Color = MainMenuForm->iBackgroundColor ;
 //Edit1->Text =  MainMenuForm->strPickupAccount;
 if( Edit1->Text != "" )
 {
	// Button1Click(Sender);
 }

 if( MainMenuForm->strPrePayAccount != "" && MainMenuForm->blnPrePayAllToday )
 {

	 Edit1->Text =  MainMenuForm->strPrePayAccount;
	

     Button1Click(Sender);

 }


dTotalSelected = 0;
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Grid1DblClick(TObject *Sender)
{
   QuickTicketListBoxItemClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TPickupWindow01::Button33Click(TObject *Sender)
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

void __fastcall TPickupWindow01::Button34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button35Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button38Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button39Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button40Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button41Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button42Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button43Click(TObject *Sender)
{
 Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button44Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "-";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button45Click(TObject *Sender)
{
Edit1->Text =  "";
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Image3Click(TObject *Sender)
{
WinExec("C:\\Program Files (x86)\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button46Click(TObject *Sender)
{
					AnsiString strAddress1 = ADOQuery1->FieldByName("ADDRESS1")->AsString;
				   AnsiString strCity = ADOQuery1->FieldByName("CITY")->AsString;
				   AnsiString strState = ADOQuery1->FieldByName("STATE")->AsString;
				   AnsiString strZip = ADOQuery1->FieldByName("ZIP")->AsString ;
				   AnsiString strTemp = "http:\\\\maps.google.com?q=\""+ ADOQuery1->FieldByName("ADDRESS1")->AsString+","+ strCity +","+ strState+","+ strZip+"\"";
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
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ComboBox1Change(TObject *Sender)
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
					  ADOQuery1->Post();
				}
			}
 }

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ComboEdit1Change(TObject *Sender)
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


		   ADOQuery1->Post();
	}

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button47Click(TObject *Sender)
{
 ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";

	  MainMenuForm->strLastSearch = Edit1->Text;





	 // ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {


      	ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();

		  ADOQuery6->SQL->Add("SELECT  *,AMT - AMTPAID AS DUE from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ORDERNO = '"+Edit1->Text+"'");



		ADOQuery6->Active = true;
		ADOQuery6->First();
		if( ! ADOQuery6->Eof )
		{
		  Edit1->Text = ADOQuery6->FieldByName("ACCT")->AsString;
		}


	  ADOQuery1->Active = false;

	   ADOQuery1->SQL->Clear();

	   ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by name";

      }

	  ADOQuery1->Active = true;

	  if( ADOQuery1->Eof == false )
	  {
		 // WriteTicketListBoxItem->Enabled = true;
		  //QuickTicketListBoxItem->Enabled = true;
		 // EditCustomerListBoxItem->Enabled = true;

		  if( ADOQuery1->RecordCount == 1 )
		  {
             QuickTicketListBoxItemClick(Sender);

          }
		  Grid1->SetFocus();
	  }
	  else
	  {

		 ShowMessage("No Records Found! Try another search.");
		 Edit1->SetFocus();

		 //  QuickTicketListBoxItem->Enabled = false;
		 //  EditCustomerListBoxItem->Enabled = false;
		   return;
      }

		ADOQuery9->Active = false;
		ADOQuery9->SQL->Clear();
		ADOQuery9->SQL->Text = "Select * from AR where STORENO = '"+MainMenuForm->strStoreNo  +"' AND ID = -1";



}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::ListBox3Click(TObject *Sender)
{
	TLocateOptions SearchOptions;
	SearchOptions << loCaseInsensitive;

	ADOQuery12->Locate("COUPON",ListBox3->Selected->Text, SearchOptions  );

	MainMenuForm->dGiftCard = ADOQuery12->FieldByName("COUPONAMT")->AsFloat;

	Label59->Text = ADOQuery12->FieldByName("COUPONAMT")->AsFloat;

}
//---------------------------------------------------------------------------
  char __fastcall TPickupWindow01::hexToAscii(char first, char second)
{

	char hex[5], *stop;

	hex[0] = '0';

	hex[1] = 'x';

	hex[2] = first;

	hex[3] = second;

	hex[4] = 0;

	return strtol(hex, &stop, 16);

}

void __fastcall TPickupWindow01::Button48Click(TObject *Sender)
{
			FILE *stream;


				stream = fopen("c:\\VIVALDI8\\CCRECEIPT.TXT", "w+");


					fprintf(stream , "%c",hexToAscii('1','b') );
					fprintf(stream , "%c",hexToAscii('5','7') );
					fprintf(stream , "%c",hexToAscii('3','1') );


							fprintf(stream , "%c",hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('0','a') );

					  AnsiString s =   MainMenuForm->strStoreName;
					fprintf(stream , "%s", s);
						fprintf(stream , "%c", hexToAscii('0','a') );

					 fprintf(stream , "%c",hexToAscii('1','b') );
					fprintf(stream , "%c",hexToAscii('5','7') );
					fprintf(stream , "%c",hexToAscii('3','0') );

										fprintf(stream , "%c", hexToAscii('0','a') );
											  s =   "Rack Pick List";
					fprintf(stream , "%s", s);
						fprintf(stream , "%c", hexToAscii('0','a') );
							fprintf(stream , "%c", hexToAscii('0','a') );
							   s =   "------------------------------------";
					fprintf(stream , "%s", s);
						  fprintf(stream , "%c", hexToAscii('0','a') );
				ADOQuery6->First();
		while( ADOQuery6->Eof == false )
		 {
			if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
			{
				fprintf(stream , "%c", hexToAscii('0','a') );
								   s =   "Ticket #: "+ ADOQuery6->FieldByName("ORDERNO")->AsString+ " Loc: "+ ADOQuery6->FieldByName("LOCATION")->AsString;+ " PC: "+ ADOQuery6->FieldByName("QTY")->AsString;
						fprintf(stream , "%s", s);
			}

			ADOQuery6->MoveBy(1);

		}



								fprintf(stream , "%c", hexToAscii('0','a') );
							   s =   "------------------------------------";
					fprintf(stream , "%s", s);


							fprintf(stream , "%c", hexToAscii('0','a') );
							fprintf(stream , "%c", hexToAscii('0','a') );
							 s =   "Customer: "+ADOQuery1->FieldByName("NAME")->AsString;
					fprintf(stream , "%s", s);
						fprintf(stream , "%c", hexToAscii('0','a') );
							fprintf(stream , "%c", hexToAscii('0','a') );
							 s =   "Account #: "+ MainMenuForm->strCustomerAcct;
					fprintf(stream , "%s", s);

						fprintf(stream , "%c", hexToAscii('0','a') );

							s = DateTimeToStr(Now()) +" User:"+MainMenuForm->strUserName+" ";
						fprintf(stream , "%s", s);
						fprintf(stream , "%c", hexToAscii('0','a') );
							   s =   "------------------------------------";
					fprintf(stream , "%s", s);


							fprintf(stream , "%c", hexToAscii('0','a') );



							fprintf(stream , "%c",hexToAscii('0','a') );
							  s =   "Please Sign indicating you picked up";
					fprintf(stream , "%s", s);
						fprintf(stream , "%c",hexToAscii('0','a') );
						 s =   "the Tickets Listed here.";
					fprintf(stream , "%s", s);
						fprintf(stream , "%c",hexToAscii('0','a') );

							fprintf(stream , "%c",hexToAscii('0','a') );
								fprintf(stream , "%c", hexToAscii('0','a') );
								fprintf(stream , "%c",hexToAscii('0','a') );

									fprintf(stream , "%c", hexToAscii('0','a') );
							   s =   "____________________________";
					fprintf(stream , "%s", s);
						fprintf(stream , "%c", hexToAscii('0','a') );
							  s =   "      *******Customer Signature******";
					fprintf(stream , "%s", s);

						fprintf(stream , "%c", hexToAscii('0','a') );
								fprintf(stream , "%c", hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('0','a') );
							fprintf(stream , "%c", hexToAscii('0','a') );
								fprintf(stream , "%c", hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('0','a') );

								fprintf(stream , "%c",hexToAscii('1','b') );
							fprintf(stream , "%c",hexToAscii('6','4') );
							fprintf(stream , "%c",hexToAscii('3','0') );

				   fclose(stream);

					stream = fopen("c:\\VIVALDI8\\CCRECEIPTM.TXT", "w+");
					  fclose(stream);



					WinExec("C:\\VIVALDI8\\prtreceipt.bat", SW_MINIMIZE);

}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button49Click(TObject *Sender)
{
	ADOQuery6->Active = false;
		ADOQuery6->SQL->Clear();
		ADOQuery6->SQL->Add("SELECT *,AMT - AMTPAID AS DUE  from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' And DateIn < GETDATE() - 30  Order by ORDERNO");
		ADOQuery6->Active = true;

		Button30->Enabled = true;
		Button31->Enabled = true;
		Button2->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TPickupWindow01::Button50Click(TObject *Sender)
{
	MainMenuForm->blnPayInFull  = false;
	MainMenuForm->strPaidType = "";
	ADOQuery6->First();
	double fTotal = 0;
	MainMenuForm->fDeposit = 0;

	int iTotalTickets = 0;

	MainMenuForm->strCustomerAcct = ADOQuery1->FieldByName("ACCT")->AsString;
	 MainMenuForm->blnAccountCustomer  =   ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
		{
			fTotal = fTotal + ( ADOQuery6->FieldByName("AMT")->AsFloat - (ADOQuery6->FieldByName("AMTPAID")->AsFloat  ));
			MainMenuForm->fDeposit = MainMenuForm->fDeposit +  ADOQuery6->FieldByName("DEPOSIT")->AsFloat;
			iTotalTickets++;
		}

		ADOQuery6->MoveBy(1);

	}

	if( iTotalTickets == 0 )
	{
		ShowMessage("No Tickets Are Selected");
		return;
    }


	double fLocalTendered = 0;
	TCommonCustomForm *Form = Application->GetDeviceForm(L"CashdrawerView");
		if(Form)
		{

		   MainMenuForm->fTendered  = fTotal - MainMenuForm->dGiftCard;

		   Form->ShowModal();
		   fLocalTendered =  MainMenuForm->fTendered + MainMenuForm->dGiftCard;
		   delete Form;

		}
	 if( MainMenuForm->blnCancel == false )
	 {
		double fApplied = 0;

		 ADOQuery11->Active = false;

		 ADOQuery11->SQL->Clear();
		 ADOQuery11->SQL->Add("Select * from Store where Store = '"+MainMenuForm->strStoreNo  +"'");

		ADOQuery11->Active = true;




	if(true )
	{
	ADOQuery6->First();

	//float ftotalselected =  StrToFloat(Label19->Text);
	double famtpaid = 0;

	ADOQuery1->Edit();
	if( ADOQuery1->FieldByName("YTDTOTAL")->AsString == "" )
	{
		ADOQuery1->FieldByName("YTDTOTAL")->AsFloat = 0;

	}
	if( ADOQuery1->FieldByName("SPENT")->AsString == "" )
	{
		ADOQuery1->FieldByName("SPENT")->AsFloat = 0;

	}
    ADOQuery1->FieldByName("LASTTRAN")->AsString = DateTimeToStr(Now()).SubString(0,10);
	ADOQuery1->FieldByName("LASTTRANS")->AsString = DateTimeToStr(Now()).SubString(0,10);
	ADOQuery1->FieldByName("YTDTOTAL")->AsFloat = ADOQuery1->FieldByName("YTDTOTAL")->AsFloat + fLocalTendered;
	ADOQuery1->FieldByName("SPENT")->AsFloat = ADOQuery1->FieldByName("SPENT")->AsFloat + fLocalTendered;

	if( ADOQuery1->FieldByName("SPENT")->AsFloat < 100 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "NEW";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 2000 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "PLATIUM";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 1000 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "GOLD";
	else if( ADOQuery1->FieldByName("SPENT")->AsFloat > 500 )
	   ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString = "SILVER";



	if( ADOQuery11->FieldByName("LOYALTY")->AsBoolean && MainMenuForm->blnDefaultLoyalty )
	{

	   if( ADOQuery11->FieldByName("BYTICKETS")->AsBoolean )
	   {
			if( ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat >= ADOQuery11->FieldByName("LOYALTYLEVEL")->AsFloat )
			{

				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
				ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat =  ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat +  ADOQuery11->FieldByName("REWARD")->AsFloat;

				ShowMessage("Customer has received "+  ADOQuery11->FieldByName("REWARD")->AsString+ " Loyalty Reward Dollars. Total of "+ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsString+" on their account. These Dollars can be used on their next Ticket.");

			}
			else
			{
				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 	ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat  + iTotalTickets;
			}


	   }
	   else
	   {
			if( ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat >= ADOQuery11->FieldByName("LOYALTYLEVEL")->AsFloat )
			{

				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
				ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat =  ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsFloat +  ADOQuery11->FieldByName("REWARD")->AsFloat;
				ShowMessage("Customer has received "+  ADOQuery11->FieldByName("REWARD")->AsString+ " Loyalty Reward Dollars. Total of "+ADOQuery1->FieldByName("LOYALTYDOLLARS")->AsString+" on their account. These Dollars can be used on their next Ticket.");


			}
			else
			{
				ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 	ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat  + fLocalTendered;
            }

	   }
    }



	ADOQuery1->Post();

	ADOQuery11->Active = false;

	while( ADOQuery6->Eof == false )
	{
		if( ADOQuery6->FieldByName("IsActive")->AsBoolean )
		{



		   ADOQuery10->Open();
		   ADOQuery10->Insert();
		   ADOQuery10->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

		  if( MainMenuForm->blnPrePayAllToday )
		  {
			   ADOQuery10->FieldByName("DESCRIPTION")->AsString = "Ticket Prepaid" ;

		  }
		  else
		  {
			 ADOQuery10->FieldByName("DESCRIPTION")->AsString = "Ticket Picked Up" ;

		  }



		   ADOQuery10->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery10->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
		   ADOQuery10->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
		   ADOQuery10->FieldByName("ORDERNO")->AsString = ADOQuery6->FieldByName("ORDERNO")->AsString;
		   ADOQuery10->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("ACCT")->AsString;
		   ADOQuery10->Post();
		   ADOQuery10->Close();


		   //ShowMessage(ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat);
		   //ShowMessage( fLocalTendered );

			ADOQuery6->Edit();
			if( ADOQuery6->FieldByName("Deposit")->AsString == "" )
		         ADOQuery6->FieldByName("Deposit")->AsString = 0;


			Currency dCleanAmt = StrToCurr(FloatToStrF(  ADOQuery6->FieldByName("AMT")->AsFloat, ffGeneral , 12, 0));
			Currency dCleanAmtPaid  =  StrToCurr(FloatToStrF( ADOQuery6->FieldByName("AmtPaid")->AsFloat , ffGeneral , 12, 0));

			fLocalTendered =  StrToFloat(FloatToStrF( fLocalTendered , ffGeneral , 12, 0));

			if( MainMenuForm->fDeposit > 0 )
			{
				if( ADOQuery6->FieldByName("AMT")->AsFloat <=  ADOQuery6->FieldByName("DEPOSIT")->AsString )
				{
				   ADOQuery6->FieldByName("DEPOSIT")->AsString = ADOQuery6->FieldByName("AMT")->AsFloat;
				   MainMenuForm->fDeposit = MainMenuForm->fDeposit - ADOQuery6->FieldByName("AMT")->AsFloat;
				}
				else
				{
					ADOQuery6->FieldByName("DEPOSIT")->AsString = MainMenuForm->fDeposit;
                    MainMenuForm->fDeposit = 0;
				}


				 MainMenuForm->strPaidType = "DEPOSIT";

			}
			else if( dCleanAmt - dCleanAmtPaid <=  fLocalTendered  )
			{
				   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;
				   ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;

				 //  	if( MainMenuForm->blnPrePayAllToday == false )
				//   ADOQuery6->FieldByName("STATUS")->AsString = "P";


				 //  ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				 //  if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
				  //    ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";


			}
			else if( dCleanAmt - dCleanAmtPaid > fLocalTendered   &&  MainMenuForm->strPaidType != "ACCOUNT"  )
			{
				  fApplied = fLocalTendered;
				  ShowMessage("Customer is underpaying!  Ticket will not be marked Picked Up. Paid: "+FloatToStrF( fLocalTendered  , ffCurrency, 12, 2)+ "  Due: "+FloatToStrF( ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat  , ffCurrency, 12, 2) );
				//  ADOQuery6->FieldByName("LOCATION")->AsString = "CUSTOMER/NOT PAID";
				//  ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
			}
			else if( dCleanAmt - dCleanAmtPaid <= 0 )
			{
				   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;
				   ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;

				   //	if( MainMenuForm->blnPrePayAllToday == false )
				   //	   ADOQuery6->FieldByName("STATUS")->AsString = "P";


				 //  ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				 // if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
				 //	ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";

			}

			if( MainMenuForm->strPaidType == "ACCOUNT" )
			{

                   fApplied = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AmtPaid")->AsFloat;


		   //	if( MainMenuForm->blnPrePayAllToday == false )
			  //		   ADOQuery6->FieldByName("STATUS")->AsString = "P";



				   ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());

				 //  if(  ADOQuery6->FieldByName("LOCATION")->AsString == "CUSTOMER/NOT PAID" )
				  //		ADOQuery6->FieldByName("LOCATION")->AsString = "PICKED UP";

			}
			if(  MainMenuForm->blnPayInFull )
			{
			   //	if( MainMenuForm->blnPrePayAllToday == false )
			   //	 ADOQuery6->FieldByName("STATUS")->AsString = "P";


			   //	 ADOQuery6->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());


            }


			fLocalTendered = fLocalTendered - fApplied;

			if( ADOQuery6->FieldByName("AMTPAID")->AsString != "" )
			  famtpaid = (ADOQuery6->FieldByName("AmtPaid")->AsFloat + ADOQuery6->FieldByName("Deposit")->AsFloat);
			else
			  famtpaid = 0;

			ADOQuery6->FieldByName("PAIDDATE")->AsString =  DateTimeToStr(Now());
			ADOQuery6->FieldByName("PAIDTYPE")->AsString = MainMenuForm->strPaidType;
			ADOQuery6->FieldByName("AMTPAID")->AsFloat = famtpaid + fApplied;
			ADOQuery6->FieldByName("DEPOSIT")->AsFloat = 0;
			//ADOQuery6->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery6->Post();

			//ftotalselected =  ftotalselected - fApplied;
			ADOQuery7->Open();
			ADOQuery7->Insert();
			ADOQuery7->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery7->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery7->FieldByName("AMTPAID")->AsFloat =  fApplied;
			ADOQuery7->FieldByName("ACCT")->AsString =  	ADOQuery6->FieldByName("ACCT")->AsString;
			ADOQuery7->FieldByName("NAME")->AsString =  	ADOQuery6->FieldByName("NAME")->AsString;
			ADOQuery7->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery7->FieldByName("AMT")->AsString =  	ADOQuery6->FieldByName("AMT")->AsString;
			ADOQuery7->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery7->FieldByName("DUE")->AsFloat = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
			ADOQuery7->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
			ADOQuery7->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery7->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
			ADOQuery7->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery7->Post();

			if( Label59->Text != "" )
			{


			ADOQuery7->Insert();
			ADOQuery7->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery7->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery7->FieldByName("AMTPAID")->AsString =  Label59->Text;
			ADOQuery7->FieldByName("ACCT")->AsString =  	ADOQuery6->FieldByName("ACCT")->AsString;
			ADOQuery7->FieldByName("NAME")->AsString =  	ADOQuery6->FieldByName("NAME")->AsString;
			ADOQuery7->FieldByName("TAX")->AsString =  	0;
			ADOQuery7->FieldByName("AMT")->AsString =  	Label59->Text;
			ADOQuery7->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery7->FieldByName("DUE")->AsFloat = 0;
			ADOQuery7->FieldByName("PAYMENTTYPE")->AsString = "COUPON";
			ADOQuery7->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery7->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
			ADOQuery7->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery7->Post();


            }


			if( MainMenuForm->strPaidType == "ACCOUNT" )
			{


				ADOQuery9->Open();
				ADOQuery9->Insert();
				ADOQuery9->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
				ADOQuery9->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
				ADOQuery9->FieldByName("AMTPAID")->AsFloat = 0;

				if( ADOQuery6->FieldByName("BACCT")->AsString != "" )
						ADOQuery9->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("BACCT")->AsString;
				else
					ADOQuery9->FieldByName("ACCT")->AsString = ADOQuery6->FieldByName("ACCT")->AsString;



				ADOQuery9->FieldByName("NAME")->AsString = ADOQuery6->FieldByName("NAME")->AsString;
				ADOQuery9->FieldByName("TAX")->AsString = ADOQuery6->FieldByName("TAX")->AsString;
				ADOQuery9->FieldByName("AMT")->AsString = ADOQuery6->FieldByName("AMT")->AsString;
				ADOQuery9->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
				ADOQuery9->FieldByName("DUE")->AsFloat = ADOQuery6->FieldByName("AMT")->AsFloat; // - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
				ADOQuery9->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
				ADOQuery9->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
				ADOQuery9->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
				ADOQuery9->FieldByName("STATUS")->AsString =  "OPEN";
				//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

				ADOQuery9->Post();


            }

		}

		ADOQuery6->MoveBy(1);

	}
	ADOQuery6->Close();
	ADOQuery6->Open();


   //	Label19->Text =  FloatToStrF(ftotalselected  , ffCurrency, 12, 2);

    ADOQuery6->Close();
	ADOQuery5->Close();
	ADOQuery4->Close();
	ADOQuery3->Close();
	ADOQuery2->Close();
	ADOQuery1->Close();


			if( MainMenuForm->blnPrePayAllToday )
		{
		  MainMenuForm->blnPrePayAllToday = false;
		  MainMenuForm->strPrePayAccount = "";

		}


	this->Close();

	}

    CalculateTotalPickup();
	}
}
//---------------------------------------------------------------------------




