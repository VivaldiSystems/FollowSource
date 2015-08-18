//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "WriteTicket.h"
#include "MainMenu.h"
#include "FM_PopupMessage.h"
#include "FM_DATEPICKER01.h"
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
#include "syscurr.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TWriteTicketForm01 *WriteTicketForm01;
//---------------------------------------------------------------------------
__fastcall TWriteTicketForm01::TWriteTicketForm01(TComponent* Owner)
	: TForm(Owner)
{
		 TabControl1->TabIndex = 0;
		 SaveChangesIListBoxItem->Visible = false;
		 strUpcharge = "";
		 MainMenuForm->strTicketNumber = "";
		 strClass = "D";
		 MainMenuForm->blnItemTagEntered = false;
		  strQty = "1";
		   Label48->Text = strQty;
		  blnSubDCItem = false;
		  aPrices = new double[200];
		  aPieces = new int[200];
		  aLinePrices = new double[200];
		  fTotalPrices = 0.00;
		  blnUpcharge = false;
		  blnClassTaxable = true;
		  Edit1->Text = MainMenuForm->strLastSearch;

		 if(    MainMenuForm->blnSmallerItems )
		 {
		   TicketItemsListBox->ItemHeight = 44;

         }

		 TempListQty = new TStringList; // declare the list
		  TempListItemCode = new TStringList; // declare the list
		   TempListItemDescription = new TStringList; // declare the list


			 TempListTax = new TStringList; // declare the list
			 TempListItemUpcharge = new TStringList; // declare the list
			 TempListClass   = new TStringList;

			  ADOQuery4->Active = false;
			ADOQuery4->SQL->Clear();
			ADOQuery4->SQL->Add("Select * from CLASS where Store = '"+ MainMenuForm->strStoreNo+ "' Order by Code");

			 if( MainMenuForm->blnUseItemTags )
			 {
				  Button48->Enabled = true;

			 }
			 else
			 {
                  Button48->Enabled = false;
             }

			 ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
		   //	ADOQuery3->Active = true;
			Label26->Text = "$0.00";


			  ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' Order by ROUTE");
		   //	ADOQuery5->Active = true;

			Label26->Text = " $0.00";
			Label16->Text = "0";
			Label23->Text = "Select Item";
			Edit1->SetFocus();

			if( MainMenuForm->strLastSearch != "" && MainMenuForm->blnAutoSelectLastCustomer)
				Button1Click(Owner);

}
//---------------------------------------------------------------------------
void __fastcall TWriteTicketForm01::HeaderButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void TWriteTicketForm01::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::FormActivate(TObject *Sender)
{
	//WindowState = TWindowState::wsMaximized;
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TWriteTicketForm01::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";
	  MainMenuForm->strLastSearch = Edit1->Text;
	  //ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	   if( Edit31->Text != "" )
	  {

          ADOQuery1->SQL->Clear();

	     ADOQuery1->SQL->Text = "Select * from customer where accountnumber like '%"+Edit31->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by accountnumber";



	  }
	  else
	  {

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {
	   ADOQuery1->SQL->Clear();

	  ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND (ISACTIVE = 1 OR ISACTIVE IS NULL) order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
	   ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND (ISACTIVE = 1 OR ISACTIVE IS NULL) order by name";


      }
      }
	  ADOQuery1->Active = true;

	  if( ADOQuery1->Eof == false )
	  {
		  WriteTicketListBoxItem->Enabled = true;
		  QuickTicketListBoxItem->Enabled = true;
		  EditCustomerListBoxItem->Enabled = true;

		  

		  Grid1->SetFocus();



	  }
	  else
	  {
		  WriteTicketListBoxItem->Enabled = false;
		  QuickTicketListBoxItem->Enabled = false;
		   EditCustomerListBoxItem->Enabled = false;



		 ShowMessage("No Records Found! Try another search.");
		 Edit1->SetFocus();




      }

}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TWriteTicketForm01::SelectCustomerListBoxItemClick(TObject *Sender)
{




	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();



		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

			SaveChangesIListBoxItem->Visible = false;
			SavePrintListBoxItem->Visible = false;
			QuickTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Enabled = true;

			Edit1->SetFocus();
}



void __fastcall TWriteTicketForm01::WriteTicketListBoxItemClick(TObject *Sender)
{

   if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }

	MainMenuForm->blnIsQuickTicket = false;

     if(   ADOQuery1->State == dsInsert )
	  {
		   AnsiString strAcct = ADOQuery1->FieldByName("ACCT")->AsString;

			ADOQuery19->Active = false;
			ADOQuery19->SQL->Clear();
			ADOQuery19->SQL->Add("select max(id) AS ID from customer c1 where c1.Acct = '"+ ADOQuery1->FieldByName("ACCT")->AsString +"' and c1.STORE = '"+MainMenuForm->strStoreNo  +"'  and c1.ID != '"+ ADOQuery1->FieldByName("ID")->AsString+"'");
			ADOQuery19->Active = true;

		if( ADOQuery19->Eof == false && ADOQuery19->FieldByName("ID")->AsString != "")
		{
			ShowMessage("This customer Account is already in your Store!  Try searching by Account Number and you will find it.  You should eithor change the Account number under Tools using the Global account change or remove this customer.  Some reports will not work with duplicate account numbers.  If this customer has the same phone number as another customer then put an A,B,C at the end of the account number. This customer will be deleted.  Use Select Customer and search for the existing customer!");
			ADOQuery1->Delete();
			 ADOQuery1->Active = false;
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add("Select * from CUSTOMER where Store = '"+ MainMenuForm->strStoreNo+ "' and ACCT = '"+strAcct+"'");
			ADOQuery1->Active = true;

				ADOQuery19->Active = false;

		   return;
		}
			ADOQuery19->Active = false;
	   }



	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


	if( WriteTicketListBoxItem->Enabled )
	{



        	ListBox2->Items->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();
	MainMenuForm->fTicketSubTotal = 0;
	TempListTax->Clear();
	TempListItemUpcharge->Clear();
	TempListClass->Clear();
	Button5->Enabled = false;
 	Button28->Enabled = false;
	Button6->Enabled = false;
	Button7->Enabled = false;
	Button8->Enabled = false;
	Button9->Enabled = false;
	Button4->Enabled = false;
	Button27->Enabled = false;
    Button32->Enabled = false;
	fTotalPrices = 0.00;
	memset(aPieces, 0, 200);
	memset(aPrices, 0, 200);
	memset(aLinePrices, 0, 200);
     blnUpcharge = false;
     blnSubDCItem = false;
		 MainMenuForm->fTicketTax = 0;
		TabControl1->TabIndex = 3;
		SaveChangesIListBoxItem->Visible = true;
		SaveChangesIListBoxItem->Enabled = true;
		SavePrintListBoxItem->Visible = true;
		QuickTicketListBoxItem->Visible = true;
		WriteTicketListBoxItem->Enabled = false;
		LeftLayout->Visible = false;

		if(   ADOQuery1->FieldByName("ALERT")->AsBoolean )
		{
			  ShowMessage( ADOQuery1->FieldByName("Comment")->AsString );

        }


			MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
			strClass = "D";
			if( ADOQuery1->FieldByName("DCLASS")->AsString != "" )
			{
				strClass  = ADOQuery1->FieldByName("DCLASS")->AsString;
			}

			 if( ADOQuery1->FieldByName("VIP")->AsBoolean )
			{

				Label8->Text = "VIP";
				Label8->Visible = true;


			}
			else
			{
                Label8->Visible = false;
            }


		   if( ADOQuery1->FieldByName("CLHOTEL")->AsBoolean )
			{
				RoomEdit->Visible = true;
				RoomLabel->Visible = true;
				RoomEdit->SetFocus();
			}
			else
			{
				RoomEdit->Visible = false;
				RoomLabel->Visible = false;

            }

		  ADOQuery4->Active = false;
			ADOQuery4->SQL->Clear();
			ADOQuery4->SQL->Add("Select * from CLASS where Store = '"+ MainMenuForm->strStoreNo+ "' Order by Code");
			 ADOQuery4->Active = true;


			 ADOQuery4->First();
			TLocateOptions SearchOptions;
			SearchOptions << loCaseInsensitive;

			 ADOQuery4->Locate("CODE",strClass, SearchOptions  );
			 if(  ADOQuery4->FieldByName("Tax")->AsBoolean )
			 {
				blnClassTaxable = true;
			 }
			 else
			 {
                	blnClassTaxable = false;
             }

             	strClassDescription =  ADOQuery4->FieldByName("CLASS")->AsString;

				Label23->Text = "Select Item for: "+strClassDescription;


			 ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
			ADOQuery3->Active = true;
			Label26->Text = "$0.00";



	 }
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::EditCustomerListBoxItemClick(TObject *Sender)
{
	if( EditCustomerListBoxItem->Enabled )
	{
	TabControl1->TabIndex = 1;
	Edit4->Enabled = false;
	SaveChangesIListBoxItem->Visible = true;
	SavePrintListBoxItem->Visible = false;
	SaveChangesIListBoxItem->Enabled = true;
	WriteTicketListBoxItem->Enabled = true;

	  ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' Order by ROUTE");
			ADOQuery5->Active = true;


	}
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::QuickTicketListBoxItemClick(TObject *Sender)
{

 if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }
       	MainMenuForm->blnIsQuickTicket = true;


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();



	if( QuickTicketListBoxItem->Enabled )
	{
       	MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
         MainMenuForm->fPrepayment = 0;
		TabControl1->TabIndex = 2;

        	ListBox2->Items->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();

	TempListTax->Clear();
	TempListItemUpcharge->Clear();
	TempListClass->Clear();

      aPrices = new double[200];
		  aPieces = new int[200];
		  aLinePrices = new double[200];
		  fTotalPrices = 0.00;
        MainMenuForm->fTicketSubTotal = 0;

       	memset(aPieces, 0, 200);
	memset(aPrices, 0, 200);
	memset(aLinePrices, 0, 200);

    	ListBox2->Items->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();

	TempListTax->Clear();
	TempListItemUpcharge->Clear();
	TempListClass->Clear();
	Button5->Enabled = false;
 	Button28->Enabled = false;
	Button6->Enabled = false;
	Button7->Enabled = false;
	Button8->Enabled = false;
	Button9->Enabled = false;
	Button4->Enabled = false;
	Button27->Enabled = false;
    Button32->Enabled = false;
	fTotalPrices = 0.00;
	memset(aPieces, 0, 200);
	memset(aPrices, 0, 200);
	memset(aLinePrices, 0, 200);
	//MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10));

		 MainMenuForm->fTicketTax = 0;

	UpdateTicketView();


		Edit19->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::AddCustomerListBoxItemClick(TObject *Sender)
{






	if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();



	SavePrintListBoxItem->Visible = false;
	SaveChangesIListBoxItem->Enabled = true;
	SaveChangesIListBoxItem->Visible = true;
	Edit4->Enabled = true;

	if(  ADOQuery1->Active == false )
	{
	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from customer where id = -1 AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";
	  ADOQuery1->Active = true;
	}

		MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;

          ADOQuery5->Active = false;
			ADOQuery5->SQL->Clear();
			ADOQuery5->SQL->Add("Select * from HOTELRTE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' Order by ROUTE");
			ADOQuery5->Active = true;


	ADOQuery7->Active = false;
	ADOQuery7->SQL->Clear();
	ADOQuery7->SQL->Add("Select NAME,ADDRESS1,ADDRESS2, CITY,STATE,ZIP,LOYALTY,PHONE,LOGIN from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
	ADOQuery7->Active = true;







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


		ADOQuery1->FieldByName("CITY")->AsString = ADOQuery7->FieldByName("CITY")->AsString;
	ADOQuery1->FieldByName("STATE")->AsString =  ADOQuery7->FieldByName("STATE")->AsString;
	ADOQuery1->FieldByName("ZIP")->AsString =   ADOQuery7->FieldByName("ZIP")->AsString;

	if( MainMenuForm->blnDefaultLoyalty )
		ADOQuery1->FieldByName("LOYALTY")->AsBoolean = true;


		ADOQuery7->Active = false;

    Edit3->SetFocus();

}
//---------------------------------------------------------------------------



void __fastcall TWriteTicketForm01::Button5Click(TObject *Sender)
{

   MainMenuForm->strSelectedClass  =  strClass;
   ListBox1->Enabled = false;
    ListBox2->Enabled = false;
		Button6->Enabled = false;
			Button4->Enabled = false;
				Button5->Enabled = false;
					Button27->Enabled = false;
						Button28->Enabled = false;
							Button7->Enabled = false;
								Button8->Enabled = false;
									Button9->Enabled = false;
                                    Button32->Enabled = false;




    ADOQuery3->Active = false;
	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("Select * from UPCHARGE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class like '%"+strClass+"%' Order by Code");
	ADOQuery3->Active = true;
	blnUpcharge = true;
	Button29->Visible = true;
	Button29->Text = "Exit Upcharges";
	Label23->Text = "Select Upcharge";

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{

	if(  ADOQuery1->FieldByName("ACCT")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Phone number for the Account before trying to Save a Customer Record.  If you don't have a phone number then press the Assign button to Assign a Sequential number for the account.");
		   return;
		}

		if(  ADOQuery1->FieldByName("NAME")->AsString == "")
		{
		   ShowMessage("Error:  You need to Enter a Customer Name for the Customer before trying to Save a Customer Record.");
		   return;
		}

	  if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }
	 if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	  {
		   AnsiString strAcct = ADOQuery1->FieldByName("ACCT")->AsString;

			ADOQuery19->Active = false;
			ADOQuery19->SQL->Clear();
			ADOQuery19->SQL->Add("select max(id) AS ID from customer c1 where c1.Acct = '"+ ADOQuery1->FieldByName("ACCT")->AsString +"' and c1.STORE = '"+MainMenuForm->strStoreNo  +"'  and c1.ID != '"+ ADOQuery1->FieldByName("ID")->AsString+"'");
			ADOQuery19->Active = true;

		if( ADOQuery19->Eof == false && ADOQuery19->FieldByName("ID")->AsString != "")
		{
			ShowMessage("This customer Account is already in your Store!  Try searching by Account Number and you will find it.  You should eithor change the Account number under Tools using the Global account change or remove this customer.  Some reports will not work with duplicate account numbers.  If this customer has the same phone number as another customer then put an A,B,C at the end of the account number. This customer will be deleted.  Use Select Customer and search for the existing customer!");
			ADOQuery1->Delete();
			 ADOQuery1->Active = false;
			ADOQuery1->SQL->Clear();
			ADOQuery1->SQL->Add("Select * from CUSTOMER where Store = '"+ MainMenuForm->strStoreNo+ "' and ACCT = '"+strAcct+"'");
			ADOQuery1->Active = true;

				ADOQuery19->Active = false;

		   return;
		}
			ADOQuery19->Active = false;
	   }

		Edit4->Enabled = false;

	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {
		 ADOQuery1->Post();
		}

	 WriteTicketListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::Button3Click(TObject *Sender)
{
   if( LeftLayout->Visible == true )
   {
		Label24->Text = "View Menu";
		LeftLayout->Visible = false;
   }
   else
   {
       Label24->Text = "Close Menu";
	   LeftLayout->Visible = true;
	    if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

        // Close();

		TabControl1->TabIndex = 0;

			SaveChangesIListBoxItem->Visible = false;
			SavePrintListBoxItem->Visible = false;
			QuickTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Enabled = true;

			Edit1->SetFocus();

   }



}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Label24Click(TObject *Sender)
{
		LeftLayout->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::TicketItemsListBoxClick(TObject *Sender)
{
 blnAlterationItem = false;
 strAlteration = "";

if( blnUpcharge == false )
{

	if( MainMenuForm->blnAutoPopUpcharges == false )
	{

		ADOQuery18->Active = false;
		ADOQuery18->SQL->Clear();
		ADOQuery18->SQL->Add("Select * from UPCHARGE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class like '%"+ADOQuery3->FieldByName("CLASS")->AsString+"%' Order by Code");
		ADOQuery18->Active = true;

		ListBox3->Visible = true;
	}



 if(  ADOQuery3->FieldByName("Alteration")->AsBoolean || strClass == "A" )
 {

	MainMenuForm->strQuestion = "Is this Alteration Attached to the Item Above?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
	if (Form )
	{

		
			Form->ShowModal();

			delete Form;
	}


	if( MainMenuForm->blnOK == true )
	{

	  blnAlterationItem = true;
	  strAlteration = "(Item Above)";
	}
	else
	{
		 blnAlterationItem = false;
		 strAlteration = "";
    }

   }

  }

	int iLBI = TicketItemsListBox->ItemIndex;
	ADOQuery3->First();
	ADOQuery3->MoveBy(iLBI);

	if( ADOQuery3->FieldByName("CODE")->AsString == "0" )
	{
	   Button6Click(Sender);
	}
	else
	{

	if( ! ADOQuery3->Eof )
	{
		if( blnUpcharge )
		{


			double ftempqty = StrToFloat( strQty );
			strUpcharge = ADOQuery3->FieldByName("Item")->AsString+"("+strQty+")";
			fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;

			aPrices[TempListQty->Count - 1] = aPrices[TempListQty->Count - 1] + fltPrice;
			aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice * ftempqty );

			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " " +strUpcharge;

			UpdateTicketView();
			strQty = "1";
		}
		else
		{
		if( blnSubDCItem == false )
		{
			AnsiString strItem = ADOQuery3->FieldByName("Item")->AsString ;
			AnsiString strItemCode = ADOQuery3->FieldByName("Code")->AsString;
			AnsiString newClass = "("+strClass+") " ;

			if( MainMenuForm->blnUsePriceLevel && ADOQuery1->FieldByName("PRICELEVEL")->AsString != "" )
			{


				ADOQuery11->Active = false;
				ADOQuery11->SQL->Clear();
				ADOQuery11->SQL->Text = "Select * from DCPRICE where Storeno = '"+ MainMenuForm->strStoreNo+ "' AND DCITEMID = '"+ADOQuery3->FieldByName("ID")->AsString+"' AND LEVEL = '"+ADOQuery1->FieldByName("PRICELEVEL")->AsString+"'";
				ADOQuery11->Active = true;

				if( ADOQuery11->Eof )
					fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;
				else
					fltPrice = ADOQuery11->FieldByName("Amt")->AsFloat;


				ADOQuery11->Active = false;

			}
			else
			{


				fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;


			}
			 if( MainMenuForm->blnUseItemTags && ADOQuery3->FieldByName("CODE")->AsString != "0" )
			 {

					ADOQuery20->Active = false;
					ADOQuery20->SQL->Clear();
					ADOQuery20->SQL->Add("Select ID from SUBDCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' and ItemCode = '"+ strItemCode+"'");
					ADOQuery20->Active = true;
				  if( ADOQuery20->Eof )
				  {

					MainMenuForm->blnItemTagEntered = false;

					TCommonCustomForm *FormSearch = Application->GetDeviceForm(L"SearchItemView");
					if (FormSearch )
					{
					FormSearch->ShowModal();

					ADOQuery20->Active = false;
					ADOQuery20->SQL->Clear();
					ADOQuery20->SQL->Add("SELECT ID from CUSTTAG where StoreNO = '"+ MainMenuForm->strStoreNo+ "' And TAGCODE = '"+	MainMenuForm->strStockNumber +"'");
					ADOQuery20->Active = true;

					 if( ADOQuery20->Eof == false )
					 {
						 ShowMessage("That Item Tag Code is already being Used");
						 return;
                     }

					if( MainMenuForm->strStockNumber != "" )
					{
						AnsiString strDescTemp = ADOQuery3->FieldByName("Item")->AsString;
						strDescTemp = AnsiReplaceStr(strDescTemp,"'","''");

						AnsiString strPriceFix = FloatToStr(aLinePrices[TempListQty->Count - 1]);
						//strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));
						if( strPriceFix.AnsiPos(".") > 0 )
						{
						  strPriceFix = strPriceFix.SubString(0,strPriceFix.AnsiPos(".")+2);
						}
						ADOQuery21->Active = false;
						ADOQuery21->SQL->Clear();
						ADOQuery21->SQL->Text = "INSERT INTO CUSTTAG (ACCT,TAGCODE,STORENO,CLASS,ITEMCODE,SUBCODE,[DESC],AMT,VALLINE,ORDERNO,LASTIN) VALUES ('"+ADOQuery1->FieldByName("ACCT")->AsString+"','"+MainMenuForm->strStockNumber+"',"+MainMenuForm->strStoreNo  +",'"+ADOQuery3->FieldByName("CLASS")->AsString+"','"+ADOQuery3->FieldByName("CODE")->AsString+"','','"+strDescTemp +"','"+  strPriceFix  +"',1,'"+MainMenuForm->strTicketNumber+"',GetDate())";
						ADOQuery21->ExecSQL();

							TempListItemUpcharge->Add("("+MainMenuForm->strStockNumber+") ");


					}

					delete FormSearch;
				}

				}
			    else
				{
				  TempListItemUpcharge->Add("");

				}
			 }
			 else
			 {
			   TempListItemUpcharge->Add("");

             }
			 MainMenuForm->blnItemTagEntered = false;



			TempListQty->Add(strQty.Trim());

			MainMenuForm->strQuantityType = ADOQuery3->FieldByName("POPUPLABEL")->AsString;

			if( ADOQuery3->FieldByName("POPUPQTY")->AsBoolean )
			{
				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuantityForm");
				if (Form )
				{
					Form->ShowModal();
					delete Form;

				   //	TempListItemUpcharge->Add(MainMenuForm->strQuantityType+" "+MainMenuForm->strEnterQuantity);

				   TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1]+" "+ MainMenuForm->strQuantityType+" "+MainMenuForm->strEnterQuantity;

					fltPrice = fltPrice * StrToFloat(MainMenuForm->strEnterQuantity);

				}

			}


			AnsiString newString = strItem + newClass;



			TempListItemCode->Add(ADOQuery3->FieldByName("Code")->AsString) ;
			TempListClass->Add(strClass);


			if( blnClassTaxable )
			   TempListTax->Add("True");
			else
			   TempListTax->Add("False");



			MainMenuForm->dDescriptionPrice = 0;
			if( ADOQuery3->FieldByName("POPUPDESCRIPTION")->AsBoolean )
			{
				MainMenuForm->strDescription = "";

				TCommonCustomForm *Form = Application->GetDeviceForm(L"DescribeForm");
				if(Form)
				{

				   Form->ShowModal();

				   delete Form;
				   if( MainMenuForm->strDescription != "" )
				   {
						TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1]+" "+ MainMenuForm->strDescription;
						//MainMenuForm->dDescriptionPrice = 0;
				   }

				}

			}
			strUpcharge = "";
			if( strClass == "L" && MainMenuForm->blnAutoStarch )
			{
			    TCommonCustomForm *Form = Application->GetDeviceForm(L"StarchForm");
				 if (Form )
				{

				   MainMenuForm->strStarchPreference = ADOQuery1->FieldByName("STARCH")->AsString;

					Form->ShowModal();
					delete Form;
					//TempListItemUpcharge->Add(MainMenuForm->strStarch);
					TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1]+" "+ MainMenuForm->strStarch;
					ADOQuery1->Edit();
					ADOQuery1->FieldByName("STARCH")->AsString = MainMenuForm->strStarch;
					ADOQuery1->Post();
				}


			 }
			 


			fltPrice = fltPrice + MainMenuForm->dDescriptionPrice;
			aPrices[TempListQty->Count - 1] = fltPrice;

			if( strQty == "0" )
			{
				aLinePrices[TempListQty->Count - 1] = fltPrice;
			}
			else
			{
			   aLinePrices[TempListQty->Count - 1] = fltPrice * StrToFloat(strQty);

			}

			//aLinePrices[TempListQty->Count - 1] = fltPrice * StrToFloat(strQty);
			if( blnAlterationItem == false )
			   aPieces[TempListQty->Count - 1] = aPieces[TempListQty->Count - 1] + ( ADOQuery3->FieldByName("Pieces")->AsInteger * StrToFloat(strQty));

			TempListItemDescription->Add(newString+" "+strAlteration);

			UpdateTicketView();

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from SUBDCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' and ItemCode = '"+ strItemCode+"' Order by Code");
			ADOQuery3->Active = true;

			if( ! ADOQuery3->Eof )
			{
				  Label23->Text = "Select Sub Item for: "+ newString;
				  blnSubDCItem = true;
				  ListBox1->Enabled = false;

					Button4->Enabled = false;
					Button5->Enabled = false;
					Button6->Enabled = false;
					Button28->Enabled = false;
				   	Button7->Enabled = false;
					Button8->Enabled = false;
					Button9->Enabled = false;
					Button4->Enabled = false;
					Button27->Enabled = false;
					Button32->Enabled = false;
			}
			else
			{

				blnSubDCItem = false;

				if( MainMenuForm->blnAutoPopUpcharges )
				{
					 Button5Click(Sender);
					 return;
			    }



				ADOQuery3->Active = false;
				ADOQuery3->SQL->Clear();
				ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
				ADOQuery3->Active = true;
					Label23->Text = "Select Item for: "+strClassDescription;
				ListBox1->Enabled = true;
				Button8->Enabled = true;
					Button4->Enabled = true;
			Button5->Enabled = true;
					Button28->Enabled = true;
			Button6->Enabled = true;
			Button7->Enabled = true;
			Button8->Enabled = true;
			Button9->Enabled = true;
			Button4->Enabled = true;
			Button27->Enabled = true;
			Button32->Enabled = true;
				strQty = "1";
                Label48->Text = strQty;
			 }


		}
		else
		{

			double ftempqty = StrToFloat( strQty );
			Label23->Text = "Select Item for: "+strClassDescription;

			strUpcharge = ADOQuery3->FieldByName("Item")->AsString;


			if( MainMenuForm->blnUsePriceLevel && ADOQuery1->FieldByName("PRICELEVEL")->AsString != "" )
			{


				ADOQuery11->Active = false;
				ADOQuery11->SQL->Clear();
				ADOQuery11->SQL->Text = "Select * from DCPRICE where Storeno = '"+ MainMenuForm->strStoreNo+ "' AND DCITEMID = '"+ADOQuery3->FieldByName("ID")->AsString+"' AND LEVEL = '"+ADOQuery1->FieldByName("PRICELEVEL")->AsString+"'";
				ADOQuery11->Active = true;

				if( ADOQuery11->Eof )
					fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;
				else
					fltPrice = ADOQuery11->FieldByName("Amt")->AsFloat;


				ADOQuery11->Active = false;

			}
			else
			{


				fltPrice = ADOQuery3->FieldByName("Amt")->AsFloat;


            }
			aPrices[TempListQty->Count - 1] = aPrices[TempListQty->Count - 1] + fltPrice;

			if( strQty == "0" )
			{
				aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice);

			}
			else
			{
				aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice * ftempqty );

			}

             if( MainMenuForm->blnUseItemTags && ADOQuery3->FieldByName("CODE")->AsString != "0" && MainMenuForm->blnItemTagEntered == false)
			 {
				 MainMenuForm->blnItemTagEntered = false;

				TCommonCustomForm *FormSearch2 = Application->GetDeviceForm(L"SearchItemView");
				if (FormSearch2 )
				{
				FormSearch2->ShowModal();

				ADOQuery20->Active = false;
				ADOQuery20->SQL->Clear();
				ADOQuery20->SQL->Add("SELECT ID from CUSTTAG where StoreNO = '"+ MainMenuForm->strStoreNo+ "' And TAGCODE = '"+	MainMenuForm->strStockNumber +"'");
				ADOQuery20->Active = true;
					 if( ADOQuery20->Eof == false )
					 {
						 ShowMessage("That Item Tag Code is already being Used");
						 return;
                     }

					if( MainMenuForm->strStockNumber != "" )
					{

                    	AnsiString strPriceFix = FloatToStr(aLinePrices[TempListQty->Count - 1]);
						//strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));
						if( strPriceFix.AnsiPos(".") > 0 )
						{
						  strPriceFix = strPriceFix.SubString(0,strPriceFix.AnsiPos(".")+2);
						}
						AnsiString strDescTemp = TempListItemDescription->Strings[TempListQty->Count - 1];
						strDescTemp = AnsiReplaceStr(strDescTemp,"'","''");

						AnsiString strUpchargeTemp = ADOQuery3->FieldByName("ITEM")->AsString;
						strUpchargeTemp = AnsiReplaceStr(strUpchargeTemp,"'","''");

						ADOQuery21->Active = false;
						ADOQuery21->SQL->Clear();
						ADOQuery21->SQL->Text = "INSERT INTO CUSTTAG (ACCT,TAGCODE,STORENO,CLASS,ITEMCODE,SUBCODE,[DESC],AMT,VALLINE,UPCHARGE,ORDERNO,LASTIN) VALUES ('"+ADOQuery1->FieldByName("ACCT")->AsString+"','"+MainMenuForm->strStockNumber+"','"+MainMenuForm->strStoreNo  +"','"+ADOQuery3->FieldByName("CLASS")->AsString+"','"+ADOQuery3->FieldByName("ITEMCODE")->AsString+"','"+ADOQuery3->FieldByName("CODE")->AsString+"','"+strDescTemp +"','"+  strPriceFix  +"','1','"+strUpchargeTemp+"','"+MainMenuForm->strTicketNumber+"',GetDate())";
						ADOQuery21->ExecSQL();

					   strUpcharge = "("+ MainMenuForm->strStockNumber +") "+strUpcharge;
					   TempListItemUpcharge->Strings[TempListQty->Count - 1] = strUpcharge;

					}

					delete FormSearch2;
				}


			 }
			 MainMenuForm->blnItemTagEntered = false;

			if( ADOQuery3->FieldByName("Pieces")->AsString != "" && blnAlterationItem == false )
			   aPieces[TempListQty->Count - 1] = aPieces[TempListQty->Count - 1] + ( ADOQuery3->FieldByName("Pieces")->AsInteger * ftempqty);

			   	if( MainMenuForm->strStockNumber == "" )
					{
                	TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " " +strUpcharge;
				  }

			UpdateTicketView();


			blnSubDCItem = false;

			if( MainMenuForm->blnAutoPopUpcharges )
			{
					 Button5Click(Sender);
					 return;
			}


			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;
			Button8->Enabled = true;
				Button4->Enabled = true;
			Button5->Enabled = true;
				Button28->Enabled = true;
			Button6->Enabled = true;
			Button7->Enabled = true;
			Button8->Enabled = true;
			Button9->Enabled = true;
			Button4->Enabled = true;
			Button27->Enabled = true;
			Button32->Enabled = true;
			ListBox1->Enabled = true;
             	strQty = "1";
			 Label48->Text = strQty;
		}
		}

    }

	}
	TicketItemsListBox->ItemIndex = 0;
	TicketItemsListBox->Selected->IsSelected = false;


     Label48->Text = strQty;


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";
   Label48->Text = strQty;
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";
  Label48->Text = strQty;


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";
  Label48->Text = strQty;

//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";
  Label48->Text = strQty;

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";
  Label48->Text = strQty;

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";
   Label48->Text = strQty;

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";
   Label48->Text = strQty;

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";
  Label48->Text = strQty;

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";
  Label48->Text = strQty;
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";
   Label48->Text = strQty;
}
//---------------------------------------------------------------------------
void __fastcall TWriteTicketForm01::UpdateTicketView()
{
ListBox2->Items->Clear();

AnsiString sQty;
AnsiString sItemDescription;
AnsiString sUpcharge;
AnsiString sPrice;
double fTotal = 0;

double fTotalQuantity = 0;

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
			fTotalQuantity = fTotalQuantity + aPieces[i];
		}


		// sItemDescription = sItemDescription +  sItemDescription.StringOfChar(' ', 30 - sItemDescription.Length() );



		ListBox2->Items->Add(sQty+"  "+sItemDescription + " (" + sPrice+")");

		if( i < TempListItemUpcharge->Count && TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
			  ListBox2->Items->Add("   "+ TempListItemUpcharge->Strings[i] );

	}

	Label16->Text = FloatToStrF( fTotalQuantity  , ffGeneral , 12, 0);
	Label26->Text = FloatToStrF(fTotal  , ffCurrency, 12, 2);

}
void __fastcall TWriteTicketForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button4Click(TObject *Sender)
{


	int iLBI = ListBox2->ItemIndex;
	if( iLBI == -1 )
	{
		ShowMessage("Please Select a line to Remove on the Right First!");
		return;
	}

	int	intSelectedLine = -1;

	for( int i = 0; i < ListBox2->Items->Count; i++ )
	{

		  // ShowMessage( ListBox2->ItemByIndex(i)->Text);
		  if(  ListBox2->ItemByIndex(i)->Text != "" && ListBox2->ItemByIndex(i)->Text.SubString(0,1) != " " )
		  {
			intSelectedLine = intSelectedLine + 1;
		  }
		  if( i == iLBI )
			  break;


	}


	 MainMenuForm->blnOK = false;
   MainMenuForm->strQuestion = "Would you like to remove the selected Record? ("+ TempListItemDescription->Strings[intSelectedLine]+")";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == false )
	{
	   return;

	}



	int iLast = intSelectedLine; // TempListQty->Count - 1;





	if( iLast > -1 )
	{
		TempListQty->Delete(iLast);
		TempListItemCode->Delete(iLast);
		TempListItemDescription->Delete(iLast);

	    if( iLast < TempListTax->Count ) {
		   TempListTax->Delete(iLast);
		}

		TempListItemUpcharge->Delete(iLast);
		TempListClass->Delete(iLast);





		for( int i = iLast; i < TempListQty->Count + 1; i++ )
		{
		  aPrices[i] = aPrices[i + 1];
		  aLinePrices[i] = aLinePrices[i + 1];
		  aPieces[i] = aPieces[i + 1];


          //This need to adjust inventory


		}

	}

	ListBox2->Items->Clear();
	UpdateTicketView();

}
//---------------------------------------------------------------- -----------
 char __fastcall TWriteTicketForm01::hexToAscii(char first, char second)
{

	char hex[5], *stop;

	hex[0] = '0';

	hex[1] = 'x';

	hex[2] = first;

	hex[3] = second;

	hex[4] = 0;

	return strtol(hex, &stop, 16);

}

void __fastcall TWriteTicketForm01::Button8Click(TObject *Sender)
{

 int intTotShirt = 0;

	AnsiString strCurrentLot = "";
	AnsiString strGroupLot = "";
	AnsiString strShirtLotCurrent = "";

	MainMenuForm->blnPreview  = false;
	Currency fTotal = 0;
	int iQty = 0;
	//double fTax = 0;
	double fTotalMin = 0;
	double RouteMin = 0;
	Currency fTax = 0;
	Currency fTotalTax = 0;
	Currency fSubTotal = 0;
	MainMenuForm->fTicketTax = 0;
	MainMenuForm->fDeposit = 0;
	MainMenuForm->blnCustomerTaxable = ADOQuery1->FieldByName("Tax")->AsBoolean;
	//MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10));
	MainMenuForm->strCustomerDiscount   = ADOQuery1->FieldByName("Discount")->AsString;
	MainMenuForm->strCustomerAcct  = ADOQuery1->FieldByName("Acct")->AsString;
	MainMenuForm->fTendered = 0;
	MainMenuForm->strPrePayAccount = ADOQuery1->FieldByName("Acct")->AsString;

	MainMenuForm->iCouponPercent = 0;
	MainMenuForm->dCouponAmount =0;
	MainMenuForm->blnDirectPayment = false;
	MainMenuForm->fCouponTotal = 0;


 if( MainMenuForm->blnLevelLoyalty  &&  MainMenuForm->strCustomerDiscount == "" )
 {

	 if( ADOQuery1->FieldByName("YTDTOTAL")->AsFloat >= 10000 )
	 {
		 MainMenuForm->strCustomerDiscount = "30";
	 }
	 else if( ADOQuery1->FieldByName("YTDTOTAL")->AsFloat >= 7500 )
	 {
		 MainMenuForm->strCustomerDiscount = "25";
	 }
	  else if( ADOQuery1->FieldByName("YTDTOTAL")->AsFloat >= 5000 )
	 {
		 MainMenuForm->strCustomerDiscount = "20";
	 }
	  else if( ADOQuery1->FieldByName("YTDTOTAL")->AsFloat >= 2500 )
	 {
		 MainMenuForm->strCustomerDiscount = "15";
	 }
	  else if( ADOQuery1->FieldByName("YTDTOTAL")->AsFloat >= 1000 )
	 {
		 MainMenuForm->strCustomerDiscount = "10";
	 }


 }

  if( ADOQuery1->FieldByName("OPENDATE")->AsString != "" )
  {

	 AnsiString strTempDate = ADOQuery1->FieldByName("OPENDATE")->AsString;
                         // 7/2014           9/2014
	  if( StrToDate( strTempDate ) + 362 < Now() )
	  {

			 ADOQuery1->Edit();
			 ADOQuery1->FieldByName("YTDTOTAL")->AsString = "0.00";
			 ADOQuery1->Post();

	  }

  }
  else
  {

	   ADOQuery1->Edit();
	   ADOQuery1->FieldByName("OPENDATE")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));
       ADOQuery1->Post();


  }




  MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10));



	TCommonCustomForm *FM_DATEPICKERFORM = Application->GetDeviceForm(L"FM_DATEPICKER");
		if (FM_DATEPICKERFORM)
		{


			if( FM_DATEPICKERFORM->ShowModal() == mrOk )
			{
			   //MainMenuForm->blnPrint  = true;
			}

			delete FM_DATEPICKERFORM;

		}


ListBox2->Items->Clear();

AnsiString sQty;
AnsiString sItemDescription;
AnsiString sUpcharge;
AnsiString sPrice;

//check if dup
ADOQuery13->Active = false;
ADOQuery13->SQL->Clear();
ADOQuery13->SQL->Add("SELECT ID FROM INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString+"' AND AMT = '"+ Label16->Text +"' AND CONVERT(VARCHAR(10),DATEIN,101) <> CONVERT(VARCHAR(10),GETDATE(),101)");
ADOQuery13->Active = true;
AnsiString strOrderNo;

if( MainMenuForm->blnUseItemTags == false )
{

	ADOQuery7->Active = false;
	ADOQuery7->SQL->Clear();
	ADOQuery7->SQL->Add("UPDATE STORE SET ORDERNO = ORDERNO + 1 where Store = '"+ MainMenuForm->strStoreNo+ "';Select OrderNo, NAME, ADDRESS1, CITY, STATE, ZIP , PHONE, LOGIN, LOYALTY from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
	ADOQuery7->Active = true;


	strOrderNo = ADOQuery7->FieldByName("OrderNo")->AsString;
	MainMenuForm->strTicketNumber = strOrderNo;
 }
 else
 {

	 strOrderNo  = MainMenuForm->strTicketNumber;
 }
	MainMenuForm->dCouponAmount = 0;

ADOQuery6->Active = false;
ADOQuery6->SQL->Clear();
ADOQuery6->SQL->Text = "Select * from Invoice where STORE = '"+MainMenuForm->strStoreNo  +"' AND ORDERNO = '"+strOrderNo+"'";
ADOQuery6->Active = false;

if( ADOQuery6->Eof == false )
{

		   ShowMessage("Error:  You're store Ticket number is set too low, you have tickets in this Range.  Go to Store Manager and raise the Ticket number or call the Vivaldi Support Center");
		   return;

}

   //	ShowMessage("Ticket Scheduled for "+ MainMenuForm->strPickupDate );1234
  // ShowMessage("Preparing Tags");
FILE *stream;
if( MainMenuForm->blnUseTags )
{
		// ShowMessage("Opening Tags");
		stream = fopen("c:\\VIVALDI8\\TAG.TXT", "w+");
}



for( int i = 0; i < TempListQty->Count; i++ )
{

		if( i < TempListQty->Count )
			sQty = TempListQty->Strings[i];

		fTotalMin = fTotalMin + aLinePrices[i];

		iQty = iQty + aPieces[i];

}
 int intLotGroup = 1;

MainMenuForm->blnNoTags = false;

if(  MainMenuForm->intMaxItems < iQty  && 	MainMenuForm->intMaxItems != 0  )
  {

		MainMenuForm->strQuestion = "You have exceeded the Max # of items allowed on a Ticket?";

		TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{

	 ShowMessage("You have exceeded the Max # of items allowed on a Ticket");
	 return;
    }

  }

	 //UPDATE STORE SET CURRENTLOT = CURRENTLOT + "+ IntToStr(iQty)  +" where Store = '"+ MainMenuForm->strStoreNo+ "'
 //ShowMessage("Checked Max #");
	 int iTotShirts = 0;

if( MainMenuForm->blnUseLotSystem  )
{
  // ShowMessage("Setting Lot System up");
if( MainMenuForm->blnSeperateShirtLot  )
{
 for( int i = 0; i < TempListQty->Count; i++ )
 {
	  if( TempListClass->Strings[i] == "L" &&  TempListItemCode->Strings[i] == "S" )
	  {
		  iTotShirts = iTotShirts + StrToInt(TempListQty->Strings[i]);

	  }
  }
 }

	ADOQuery16->Active = false;
	ADOQuery16->SQL->Clear();
	ADOQuery16->SQL->Add("Select CURRENTLOT, LOTGROUP,SHIRTLOTCURRENT from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
	ADOQuery16->Active = true;
	MainMenuForm->dCouponAmount = 0;

	MainMenuForm->intCurrentLot = ADOQuery16->FieldByName("CURRENTLOT")->AsInteger;
	strCurrentLot = IntToStr(MainMenuForm->intCurrentLot);
	intLotGroup = ADOQuery16->FieldByName("LOTGROUP")->AsInteger;
	strGroupLot = IntToStr(intLotGroup);

	intTotShirt =  ADOQuery16->FieldByName("SHIRTLOTCURRENT")->AsInteger;
	strShirtLotCurrent = ADOQuery16->FieldByName("SHIRTLOTCURRENT")->AsString;

	if(intLotGroup == 0 )
	  intLotGroup = 1;

	ADOQuery16->Active = false;
	ADOQuery16->SQL->Clear();

	if( MainMenuForm->intCurrentLot + iQty > 99 )
	{

		if( intLotGroup >= 99 )
		{
		  ADOQuery16->SQL->Add("UPDATE STORE SET CURRENTLOT = "+IntToStr((MainMenuForm->intCurrentLot + (iQty - iTotShirts) ) - 99) +", LOTGROUP = 1, SHIRTLOTCURRENT = SHIRTLOTCURRENT + "+ IntToStr(iTotShirts) +" where Store = '"+ MainMenuForm->strStoreNo+ "'");

		}
		else
		{
			ADOQuery16->SQL->Add("UPDATE STORE SET CURRENTLOT = "+IntToStr((MainMenuForm->intCurrentLot + (iQty - iTotShirts)) - 99) +", LOTGROUP = LOTGROUP + 1, SHIRTLOTCURRENT = SHIRTLOTCURRENT +"+ IntToStr(iTotShirts) +" where Store = '"+ MainMenuForm->strStoreNo+ "'");

		}
	}
	else
	{


		   ADOQuery16->SQL->Add("UPDATE STORE SET CURRENTLOT = "+IntToStr(MainMenuForm->intCurrentLot + (iQty - iTotShirts)) +", SHIRTLOTCURRENT = SHIRTLOTCURRENT + "+ IntToStr(iTotShirts) +" where Store = '"+ MainMenuForm->strStoreNo+ "'");

	}

	ADOQuery16->ExecSQL();
	ADOQuery16->Active = false;
}

if(  ADOQuery1->FieldByName("ROUTE")->AsString != "" &&  ADOQuery1->FieldByName("ROUTE")->AsString != "0" )
{
	  // ShowMessage("Setting up Route Customer");
	ADOQuery15->Active = false;
	ADOQuery15->SQL->Clear();
	ADOQuery15->SQL->Text = "Select MINCHARGE from HotelRTE where STORENO = '"+MainMenuForm->strStoreNo  +"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"'";
	ADOQuery15->Active = true;

	if( ADOQuery15->Eof == false )
	{
		RouteMin = ADOQuery15->FieldByName("MINCHARGE")->AsFloat;
		if( fTotalMin < RouteMin &&  MainMenuForm->blnUseMinFee )
		{

			 RouteMin = RouteMin - fTotalMin;


			 if( RouteMin != 0 )
			 {

				AnsiString strItem = "Min Delivery Charge";
				AnsiString strItemCode = "0";
				AnsiString newClass = "("+strClass+")";

				TempListItemDescription->Add(strItem);
				TempListQty->Add(0);
				TempListItemCode->Add("0") ;
				TempListClass->Add(strClass);
				TempListItemUpcharge->Add("");

				TempListTax->Add("False");

				fltPrice = MainMenuForm->dDescriptionPrice;
				aPrices[TempListQty->Count - 1] = RouteMin;
				aLinePrices[TempListQty->Count - 1] = RouteMin;
				aPieces[TempListQty->Count - 1] = 0;

				strUpcharge = "";

				//UpdateTicketView();

		   }


		}

	}
	ADOQuery15->Active = false;
}
   //	 ShowMessage("Preparing Email");
	MainMenuForm->strTicketPieceCount = IntToStr(iQty);

    	ADOQuery7->Active = false;
	ADOQuery7->SQL->Clear();
	ADOQuery7->SQL->Add("Select NAME,ADDRESS1,ADDRESS2, CITY,STATE,ZIP,LOYALTY,PHONE,LOGIN from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
	ADOQuery7->Active = true;


	AnsiString sBody = "Ticket "+ MainMenuForm->strTicketNumber+"\n\r";
	AnsiString sStore = ADOQuery7->FieldByName("NAME")->AsString;

	sBody = sBody + ADOQuery7->FieldByName("NAME")->AsString +"\n\r";
	sBody = sBody + ADOQuery7->FieldByName("ADDRESS1")->AsString +"\n\r";
	sBody = sBody + ADOQuery7->FieldByName("CITY")->AsString +", "+ ADOQuery7->FieldByName("STATE")->AsString +", "+ ADOQuery7->FieldByName("ZIP")->AsString+"\n\r";
	sBody = sBody + ADOQuery7->FieldByName("PHONE")->AsString +"\n\r";
	sBody = sBody + ADOQuery7->FieldByName("LOGIN")->AsString +"\n\r";
	sBody = sBody + "\n\r";
	sBody = sBody + "\n\r";

    ADOQuery7->Active = false;

	sBody = sBody + "Account: "+ADOQuery1->FieldByName("ACCT")->AsString +"\n\r";
	sBody = sBody + "Name:    "+ADOQuery1->FieldByName("NAME")->AsString +"\n\r";
		sBody = sBody + "Pickup on:    "+MainMenuForm->strDateOut +"\n\r";
	 sBody = sBody + "\n\r";
	 sBody = sBody + "\n\r";

    	   //MainMenuForm->blnUseLotSystem
			int iLotGroup = intLotGroup;
			int iCurrentLot = MainMenuForm->intCurrentLot;

	int iTotalItems = 0;

	bool blndontprinttags = false;
	AnsiString strDClass;




	for( int i = 0; i < TempListQty->Count; i++ )
	{

		sQty = "0";
		sItemDescription = "";
		sUpcharge = "";
		sPrice = "$0.00";

		if( i < TempListQty->Count )
			sQty = TempListQty->Strings[i];


			if( sQty == "" )
			  sQty = "0";

		//iQty = iQty + (StrToInt(sQty) * StrToInt(aPieces[i]) );

		if( i < TempListItemDescription->Count   )
		{

			sItemDescription = TempListItemDescription->Strings[i];
			sPrice = FloatToStrF(aLinePrices[i]  , ffCurrency, 12, 2);
			fTotal = fTotal + aLinePrices[i];
			if( i < TempListTax->Count  && MainMenuForm->blnCustomerTaxable )
			{
				if( TempListTax->Strings[i] == "True" && MainMenuForm->fTaxRate != 0 )
				   fTax = fTax + ( aLinePrices[i] * ( MainMenuForm->fTaxRate / 100) );
				else
				   fTax = 0;
			}
			else
			{
			  fTax = 0;

			}

			fTotalTax = fTotalTax + fTax;

		}
		 sBody = sBody + sQty+"  "+sItemDescription + " (" + sPrice +")\n\r";

		 ListBox2->Items->Add(sQty+"  "+sItemDescription + " (" + sPrice+")");

		if( TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
		   ListBox2->Items->Add("   "+ TempListItemUpcharge->Strings[i] );

		   MainMenuForm->strCustomerAcct = ADOQuery1->FieldByName("ACCT")->AsString;
		   if( ADOQuery1->FieldByName("DISCOUNT")->AsString != "" )
			  MainMenuForm->iCouponPercent =   ADOQuery1->FieldByName("DISCOUNT")->AsInteger;
		   else
              MainMenuForm->iCouponPercent = 0;

		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = aLinePrices[i];

		   if( TempListTax->Strings[i] == "True" )   //   ADOQuery1->FieldByName("TAX")->AsBoolean )
			  ADOQuery2->FieldByName("TAX")->AsFloat =  fTax;
		   else
			  ADOQuery2->FieldByName("TAX")->AsFloat = 0;


		   ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = false;
		   ADOQuery2->FieldByName("QTY")->AsInteger =  StrToInt(sQty);


		   ADOQuery2->FieldByName("VALLINE")->AsInteger = aPieces[i];
		   ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());

		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  sItemDescription;
		   ADOQuery2->FieldByName("CLASS")->AsString =  TempListClass->Strings[i];
		   ADOQuery2->FieldByName("UPCHARGE")->AsString =  TempListItemUpcharge->Strings[i];
		   ADOQuery2->FieldByName("ITEM")->AsString =  TempListItemCode->Strings[i];

		   strDClass =  ADOQuery2->FieldByName("CLASS")->AsString;


		   ADOQuery2->Post();
		   //	 ShowMessage("Ticket Updated");
		   if( MainMenuForm->blnUseInventoryControl )
		   {

				ADOQuery17->Active = false;
						ADOQuery17->SQL->Clear();
						ADOQuery17->SQL->Text = "UPDATE DCITEM SET CURRENTSTOCK = CURRENTSTOCK - "+IntToStr(aPieces[i])+" WHERE STORENO = '"+MainMenuForm->strStoreNo  +"' AND CLASS = '"+TempListClass->Strings[i]+"' AND CODE = '"+TempListItemCode->Strings[i]+"' AND INVENTORYITEM = 1";
						ADOQuery17->ExecSQL();


			}




		   if( MainMenuForm->blnUseTags )
		   {
			   iTotalItems =  aPieces[i];

			   //CHECK TAG CLASSES
			   ADOQuery4->First();
			   TLocateOptions SearchOptions;
			   SearchOptions << loCaseInsensitive;



			 ADOQuery4->Locate("CODE",TempListClass->Strings[i], SearchOptions  );
			 if(  ADOQuery4->FieldByName("NOTAGS")->AsBoolean )
			 {
				blndontprinttags = true;
			 }
			 else
			 {
				blndontprinttags = false;
			 }


				if(  blndontprinttags == false )
				{
				  //Begin

				  if( MainMenuForm->blnEpsonU220Tag == false )
				  {
						  fprintf(stream , "%c",hexToAscii('1','b') );
						  fprintf(stream , "%c",hexToAscii('4','5') );


						  if( MainMenuForm->blnWiderTags )
							{

								//CHANGE FONT
								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",'W' );
								fprintf(stream , "%c",'1' );

							}
							else
							{
                               	fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",'W' );
								fprintf(stream , "%c",'0' );

                            }

							for( int iTags = 0; iTags < iTotalItems; iTags++ )
							{

							 AnsiString  s = "#"+strOrderNo;

							AnsiString strDay = DayOfWeek(StrToDate( MainMenuForm->strDateOut ));
							if (strDay == "2") {
								  strDay = "MON";
							}
							else if (strDay == "3") {
								  strDay = "TUE";
							}
							else if (strDay == "4") {
								  strDay = "WED";
							}
							else if (strDay == "5") {
								  strDay = "THR";
							}
							else if (strDay == "6") {
								  strDay = "FRI";
							}
							else if (strDay == "7") {
								  strDay = "SAT";
							}
							else if (strDay == "1") {
								  strDay = "SUN";
							}


							s = s+" "+strDay+" "+ MainMenuForm->strDateOut.SubString(0,5) +"("+IntToStr(iQty)+")";
							fprintf(stream , "%s", s);



						   fprintf(stream , "%c",hexToAscii('0','a') );

						   if(  MainMenuForm->blnTagName   )
						   {

									s =  " "+ADOQuery1->FieldByName("NAME")->AsString.SubString(0,18)+" #"+strOrderNo;
									fprintf(stream , "%s", s);
									fprintf(stream , "%c",hexToAscii('0','a') );


						   }

								if(  MainMenuForm->blnAdditionalTagInfo )
							   {
									s = "  PC: "+IntToStr(iQty)+" "+ADOQuery1->FieldByName("NAME")->AsString.SubString(0,18);
									fprintf(stream , "%s", s);
										fprintf(stream , "%c",hexToAscii('0','a') );
										fprintf(stream , "%c",hexToAscii('0','a') );

							   }


                              if( MainMenuForm->blnWiderTags || (MainMenuForm->blnLargerDTags && strDClass == "D" ))
							   {
									fprintf(stream , "%c",hexToAscii('0','a') );

								}


							//fprintf(stream , "%c",hexToAscii('0','a') );
						   //cut
						   fprintf(stream , "%c",hexToAscii('1','b') );
						   fprintf(stream , "%c",hexToAscii('6','4') );
						   fprintf(stream , "%c",hexToAscii('3','0') );




						}

				  //end
				  }
				  else
				  {



								//CHANGE FONT
					  fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('2','1') );
								fprintf(stream , "%c",hexToAscii('2','8') );



					  for( int iTags = 0; iTags < iTotalItems; iTags++ )
					  {

							//57:31  ESC W 1 set large
							//57:30   0 set small


							AnsiString  s =   strOrderNo+" "+ADOQuery1->FieldByName("NAME")->AsString.SubString(0,7);
							fprintf(stream , "%s", s);

							fprintf(stream , "%c",hexToAscii('0','a') );

							AnsiString strDay = DayOfWeek(StrToDate( MainMenuForm->strDateOut ));

							if (strDay == "2") {
								  strDay = "MON";
							}
							else if (strDay == "3") {
								  strDay = "TUE";
							}
							else if (strDay == "4") {
								  strDay = "WED";
							}
							else if (strDay == "5") {
								  strDay = "THR";
							}
							else if (strDay == "6") {
								  strDay = "FRI";
							}
							else if (strDay == "7") {
								  strDay = "SAT";
							}
							else if (strDay == "1") {
								  strDay = "SUN";
							}


							s = strDay+" "+ MainMenuForm->strDateOut.SubString(0,5) +" PC:"+IntToStr(iQty);
							fprintf(stream , "%s", s);

							if( MainMenuForm->blnWiderTags || (MainMenuForm->blnLargerDTags && strDClass == "D" ) )
								{
									fprintf(stream , "%c",hexToAscii('0','a') );
									AnsiString  s =   strOrderNo+" "+ADOQuery1->FieldByName("ACCT")->AsString.SubString(0,7);
									fprintf(stream , "%s", s);
									fprintf(stream , "%c",hexToAscii('0','a') );
								}

							fprintf(stream , "%c",hexToAscii('0','a') );
							fprintf(stream , "%c",hexToAscii('1','b') );
						   fprintf(stream , "%c",hexToAscii('6','9') );



						}



				  }


				}

		   }



	}
	 // ShowMessage("Checking Tags 1");
	if(  blndontprinttags == false )
	{

		if( MainMenuForm->blnUseTags && iTotalItems > 0)
		{

				fprintf(stream , "%c",hexToAscii('0','a') ); //1


				if(  MainMenuForm->blnTagName   )
				{
						fprintf(stream , "%c",hexToAscii('0','a') );
				}



				if( MainMenuForm->blnEpsonU220Tag == false )
				{
                                	if(  MainMenuForm->blnAdditionalTagInfo )
								{
									fprintf(stream , "%c",hexToAscii('0','a') );  //2
									fprintf(stream , "%c",hexToAscii('0','a') );


								 }
                               	if( MainMenuForm->blnWiderTags  || (MainMenuForm->blnLargerDTags && strDClass == "D" ) )
								{
									fprintf(stream , "%c",hexToAscii('0','a') );   //3

								 }
								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','4') );
								fprintf(stream , "%c",hexToAscii('3','0') );


				}
				else
				{

                                	if( MainMenuForm->blnWiderTags  || (MainMenuForm->blnLargerDTags && strDClass == "D" ) )
								{
										fprintf(stream , "%c",hexToAscii('0','a') );

								}
								 fprintf(stream , "%c",hexToAscii('0','a') );
								if(  MainMenuForm->blnAdditionalTagInfo )
								{
									fprintf(stream , "%c",hexToAscii('0','a') );


								 }

								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','9') );

				}



			  fprintf(stream , "%c",hexToAscii('0','a') ); //1

			 if(  MainMenuForm->blnTagName   )
			{
				fprintf(stream , "%c",hexToAscii('0','a') );
			}




					   if( MainMenuForm->blnEpsonU220Tag == false )
							{
							   if( MainMenuForm->blnWiderTags  || (MainMenuForm->blnLargerDTags && strDClass == "D" ) )
								{
										fprintf(stream , "%c",hexToAscii('0','a') );  //2

								}
                                	if(  MainMenuForm->blnAdditionalTagInfo )
							   {
									fprintf(stream , "%c",hexToAscii('0','a') );   //3
									fprintf(stream , "%c",hexToAscii('0','a') );

							   }

								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','4') );
								fprintf(stream , "%c",hexToAscii('3','0') );


					}
					else
					{

							 fprintf(stream , "%c",hexToAscii('0','a') );
								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','9') );

					}

		// Third cut
		if( MainMenuForm->blnUseLotSystem == false )
		{

			fprintf(stream , "%c",hexToAscii('0','a') );   //1




			if(  MainMenuForm->blnTagName   )
			{
				fprintf(stream , "%c",hexToAscii('0','a') );
			}


				if( MainMenuForm->blnEpsonU220Tag == false )
				{
                                     if(  MainMenuForm->blnAdditionalTagInfo )
								{
									fprintf(stream , "%c",hexToAscii('0','a') );  //2
									fprintf(stream , "%c",hexToAscii('0','a') );
								 }
                                	if( MainMenuForm->blnWiderTags  || (MainMenuForm->blnLargerDTags && strDClass == "D" ) )
									 {
										fprintf(stream , "%c",hexToAscii('0','a') );   //3

									}
								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','4') );
								fprintf(stream , "%c",hexToAscii('3','0') );


				}
				else
				{

								fprintf(stream , "%c",hexToAscii('1','b') );
								fprintf(stream , "%c",hexToAscii('6','9') );

				}

		}
		fclose(stream);

	}

   }
		//  ShowMessage("Tags Created");
	MainMenuForm->strPC  = IntToStr(iQty);


				MainMenuForm->iCouponPercent =	0;
	MainMenuForm->dCouponAmount = 0;
	MainMenuForm->fTicketTax  = fTotalTax;
	MainMenuForm->fTicketSubTotal = fTotal;
	MainMenuForm->fPrepayment = 0;
	MainMenuForm->blnAccountCustomer  =   ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;

	 MainMenuForm->strTag1 = "";
  MainMenuForm->strTag2 = "";
	MainMenuForm->strTag3 = "";
	 MainMenuForm->strTag4 = "";
	  MainMenuForm->strTag5 = "";
	   MainMenuForm->strTag6 = "";
	   //MainMenuForm->strDateOut = MainMenuForm->ConvertDate(DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10));


	   //	ShowMessage("Loading Ticket Window");
	TCommonCustomForm *FormWriteTicketReport = Application->GetDeviceForm(L"ReportTicketView");
		if (FormWriteTicketReport)
		{
			MainMenuForm->strReportFileName = MainMenuForm->strCustomTicket ;
			MainMenuForm->strReportFilter = strOrderNo;



			if( FormWriteTicketReport->ShowModal() == mrOk )
			{
			   MainMenuForm->blnPrint  = true;
			}

			delete FormWriteTicketReport;

			}




			if( MainMenuForm->strPickupAccount == "True")
				   MainMenuForm->strPickupAccount = ADOQuery1->FieldByName("ACCT")->AsString;
			else
				   MainMenuForm->strPickupAccount = "";


			 if( MainMenuForm->fCouponTotal != 0 )
			 {

			   ADOQuery2->Open();
			   ADOQuery2->Insert();
			   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
			   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
			   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
			   ADOQuery2->FieldByName("AMT")->AsFloat = MainMenuForm->fCouponTotal * -1;
			   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
               ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
			   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
			   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
			   if( MainMenuForm->iCouponPercent != 0 )
			   {
					 ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Coupon %"+FloatToStrF( MainMenuForm->iCouponPercent  , ffGeneral, 3, 0);


			   }
			   else
			   {
                      ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Coupon "+FloatToStrF( MainMenuForm->fCouponTotal  , ffCurrency, 12, 2);

               }

					ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
			   ADOQuery2->FieldByName("CLASS")->AsString =  "COUPON";

			   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

			   ADOQuery2->Post();


			 }




			 if( MainMenuForm->dblActualEnvironmentalFee  != 0 )
			 {

			   ADOQuery2->Open();
			   ADOQuery2->Insert();
			   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
			   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
			   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
			   ADOQuery2->FieldByName("AMT")->AsFloat = MainMenuForm->dblActualEnvironmentalFee;
			   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
               ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
			   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
			   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
			   ADOQuery2->FieldByName("ITEMDESC")->AsString =   MainMenuForm->strSurchargeLabel + FloatToStrF(MainMenuForm->dblActualEnvironmentalFee , ffCurrency, 12, 2);
			   ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
			   ADOQuery2->FieldByName("CLASS")->AsString =  "COUPON";

			   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

			   ADOQuery2->Post();

		   }


		   if( MainMenuForm->fDeposit != 0 )
		   {

		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = 0;
		   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
           ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
		   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Deposit: "+FloatToStrF( MainMenuForm->fDeposit , ffCurrency, 12, 2);
			ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
		   ADOQuery2->FieldByName("CLASS")->AsString =  "COUPON";

		   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

		   ADOQuery2->Post();


		}


   //loyalty



	TFM_PopupMessage01* FM_PopupMessage01;
	Application->CreateForm(__classid(TFM_PopupMessage01), &FM_PopupMessage01);
	if (FM_PopupMessage01 )
	{
		FM_PopupMessage01->Show();
		//delete FM_PopupMessage01;
	}



   ADOQuery6->Open();
   ADOQuery6->Insert();
   ADOQuery6->FieldByName("ORDERNO")->AsString = strOrderNo;
   ADOQuery6->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
   ADOQuery6->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;

    if( ADOQuery1->FieldByName("CLHOTEL")->AsBoolean )
	{
		ADOQuery6->FieldByName("NAME")->AsString = RoomEdit->Text+" ("+ADOQuery1->FieldByName("NAME")->AsString+")";

	}
	else
		   ADOQuery6->FieldByName("NAME")->AsString = ADOQuery1->FieldByName("NAME")->AsString;




   ADOQuery6->FieldByName("ROUTE")->AsString = ADOQuery1->FieldByName("ROUTE")->AsString;
   ADOQuery6->FieldByName("STOP")->AsString = ADOQuery1->FieldByName("STOP")->AsString;

	ADOQuery6->FieldByName("COUPONPERCENT")->AsFloat =	MainMenuForm->iCouponPercent;
	ADOQuery6->FieldByName("COUPONAMOUNT")->AsFloat = MainMenuForm->dCouponAmount;

   if( ADOQuery1->FieldByName("TAX")->AsBoolean )
	 ADOQuery6->FieldByName("TAX")->AsFloat = MainMenuForm->fTicketTax;
   else
   {
	 ADOQuery6->FieldByName("TAX")->AsFloat = 0;
	  MainMenuForm->fTicketTax = 0;
   }

   ADOQuery6->FieldByName("USER")->AsString = MainMenuForm->strUserID;
   ADOQuery6->FieldByName("AMTPAID")->AsFloat =	MainMenuForm->fPrepayment;
   ADOQuery6->FieldByName("DEPOSIT")->AsFloat =	MainMenuForm->fDeposit;
   ADOQuery6->FieldByName("LOYALTY")->AsString = ADOQuery1->FieldByName("LOYALTY")->AsString;
   ADOQuery6->FieldByName("ACCOUNT")->AsString = ADOQuery1->FieldByName("ACCOUNT")->AsString;
   ADOQuery6->FieldByName("BACCT")->AsString = ADOQuery1->FieldByName("BACCT")->AsString;
   ADOQuery6->FieldByName("CLASS")->AsString = strClass;

	if( MainMenuForm->blnDirectPayment )
	{
		ADOQuery6->FieldByName("STATUS")->AsString =  "P";
	}
	else if (MainMenuForm->strDefaultStatus != "" )
	{
	    ADOQuery6->FieldByName("STATUS")->AsString =  MainMenuForm->strDefaultStatus;
	}
	else
	{
		ADOQuery6->FieldByName("STATUS")->AsString =  "I";
	}

  if( MainMenuForm->blnUseLotSystem  ) {
	   if(   MainMenuForm->intCurrentLot <= 100 )
	   {
			MainMenuForm->strTag1 = IntToStr(intLotGroup)+":"+IntToStr(MainMenuForm->intCurrentLot)+"-"+IntToStr(MainMenuForm->intCurrentLot + (iQty - 1));
	   }
	   else
	   {
			MainMenuForm->strTag1 = IntToStr(intLotGroup)+":"+IntToStr(MainMenuForm->intCurrentLot)+"-99";
			MainMenuForm->strTag2 = IntToStr(intLotGroup+1)+":"+" 1-"+IntToStr(MainMenuForm->intCurrentLot - 99);
	   }


  }


	ADOQuery6->FieldByName("QTY")->AsString = MainMenuForm->strPC;

  ADOQuery6->FieldByName("GARMARK")->AsString = MainMenuForm->strTag1;
  ADOQuery6->FieldByName("GARMARK1")->AsString = MainMenuForm->strTag2;
	ADOQuery6->FieldByName("GARMARK2")->AsString = MainMenuForm->strTag3;
	  ADOQuery6->FieldByName("GARMARK3")->AsString = MainMenuForm->strTag4;
		ADOQuery6->FieldByName("GARMARK4")->AsString = MainMenuForm->strTag5;
		  ADOQuery6->FieldByName("GARMARK5")->AsString = MainMenuForm->strTag6;
	ADOQuery6->FieldByName("CURRENTLOT")->AsString = strCurrentLot ;
			ADOQuery6->FieldByName("LOTGROUP")->AsString = strGroupLot ;
				ADOQuery6->FieldByName("SHIRTLOTCURRENT")->AsString = strShirtLotCurrent;

   ADOQuery6->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
   ADOQuery6->FieldByName("DATEOUT")->AsString =  MainMenuForm->strDateOut;


   MainMenuForm->dTotalTicketValue = (fTotal + MainMenuForm->fTicketTax  +  MainMenuForm->dblActualEnvironmentalFee) - MainMenuForm->fCouponTotal;

       const double factor = pow(10, 2);
				   double tmp = MainMenuForm->dTotalTicketValue * factor + 0.5;

				   MainMenuForm->dTotalTicketValue = (int)tmp / factor;


   ADOQuery6->FieldByName("AMT")->AsFloat = MainMenuForm->dTotalTicketValue; //  MainMenuForm->fTendered = (fTotal + MainMenuForm->fTicketTax  +  MainMenuForm->dblActualEnvironmentalFee) - MainMenuForm->fCouponTotal;
   //ADOQuery6->FieldByName("QTY")->AsInteger = iQty;
   ADOQuery6->FieldByName("ISACTIVE")->AsBoolean =  true;

   ADOQuery6->Post();

   ADOQuery1->Edit();

   if( ADOQuery1->FieldByName("ITEMS")->AsString == "" )
	{
		ADOQuery1->FieldByName("ITEMS")->AsFloat = 0;

	}
	ADOQuery1->FieldByName("ITEMS")->AsFloat = ADOQuery1->FieldByName("ITEMS")->AsFloat + iQty;
	if( ADOQuery1->FieldByName("TICKETS")->AsString == "" )
	{
		ADOQuery1->FieldByName("TICKETS")->AsFloat = 0;

	}
	ADOQuery1->FieldByName("TICKETS")->AsFloat = ADOQuery1->FieldByName("TICKETS")->AsFloat + 1;
	ADOQuery1->FieldByName("LASTTRAN")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(0,10));
	ADOQuery1->FieldByName("LASTTRANS")->AsString = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(0,10));
	ADOQuery1->Post();


	//Write to invoicehistory
	   ADOQuery9->Open();
	   ADOQuery9->Insert();
	   ADOQuery9->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

	   ADOQuery9->FieldByName("DESCRIPTION")->AsString = "Ticket Created" ;
	   ADOQuery9->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	   ADOQuery9->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
	   ADOQuery9->FieldByName("USERID")->AsString = MainMenuForm->strUserID;
	   ADOQuery9->FieldByName("ORDERNO")->AsString = strOrderNo;
	   ADOQuery9->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	   ADOQuery9->Post();
	   ADOQuery9->Close();


       	AnsiString semail = ADOQuery1->FieldByName("EMAIL")->AsString;

		if( semail.AnsiPos("@") != 0 && MainMenuForm->blnSendTicketEmail )
		{


		   sBody = sBody + "------------------------------\n\r";

			sBody = sBody + "Total:                     "+ FloatToStr((fTotal + MainMenuForm->fTicketTax  +  MainMenuForm->dblActualEnvironmentalFee) - MainMenuForm->fCouponTotal) +"\n\r";
		   sBody = sBody +  "Paid:                      "+ ADOQuery6->FieldByName("AMTPAID")->AsString;
		   sBody = sBody + "\n\r------------------------------\n\r";
		   sBody = sBody +  "Pickup/Delivery on: "+ MainMenuForm->strDateOut;
		   sBody = sBody + "\n\r";
		ADOQuery7->Open();
		if( ADOQuery7->FieldByName("LOYALTY")->AsBoolean )
		{

					 sBody = sBody + "Loyalty Level "+ ADOQuery1->FieldByName("CUSTOMERLEVEL")->AsString +"\n\r";
					 sBody = sBody + "Spent "+ ADOQuery1->FieldByName("SPENT")->AsString +"\n\r";
                      sBody = sBody + "\n\r";
		}
		   // ADOQuery5->FieldByName("CUSTOMERLEVEL")->AsString
        ADOQuery7->Close();

			SHELLEXECUTEINFO execinfo;
			memset(&execinfo, 0, sizeof(execinfo));
			execinfo.cbSize = sizeof(execinfo);
			execinfo.lpVerb = L"open";

			execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";


			AnsiString   strParam;


			strParam =  "-to "+ semail +"  -body \" "+sBody  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Ticket from "+MainMenuForm->strStoreName +"\" ";

		   //	ShowMessage(strParam);

			int iSize = strParam.WideCharBufSize();
			wchar_t *wTemp = new wchar_t[iSize];
			strParam.WideChar(wTemp, iSize);

			execinfo.lpParameters =  wTemp;

			execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
			execinfo.nShow = SW_MINIMIZE;



    		if(! ShellExecuteEx(&execinfo))
    		{
     			ShowMessage("Could Not Run. Check that BLAT.EXE is located in c:\\VIVALDI\\REPORTS directory!");
        		return;
			}



       }


   if( MainMenuForm->fPrepayment > 0 )
   {
			ADOQuery8->Open();
			ADOQuery8->Insert();
			ADOQuery8->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery8->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery8->FieldByName("AMTPAID")->AsString =  ADOQuery6->FieldByName("AMTPAID")->AsString;
			ADOQuery8->FieldByName("ACCT")->AsString =  	ADOQuery6->FieldByName("ACCT")->AsString;
			ADOQuery8->FieldByName("NAME")->AsString =  	ADOQuery6->FieldByName("NAME")->AsString;
			ADOQuery8->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery8->FieldByName("AMT")->AsString =  	ADOQuery6->FieldByName("AMT")->AsString;
			ADOQuery8->FieldByName("DUE")->AsFloat = ADOQuery6->FieldByName("AMT")->AsFloat - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
			ADOQuery8->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
			ADOQuery8->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery8->FieldByName("ROUTE")->AsString =  ADOQuery6->FieldByName("ROUTE")->AsString;
			ADOQuery8->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery8->FieldByName("STATUS")->AsString =   "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery8->Post();
	   ADOQuery8->Close();
   }

	ListBox2->Items->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();
	fTotal = 0;
	TempListTax->Clear();
	TempListItemUpcharge->Clear();
	TempListClass->Clear();


	fTotalPrices = 0.00;
	memset(aPieces, 0, 200);
	memset(aPrices, 0, 200);
	memset(aLinePrices, 0, 200);

	AnsiString strPrintText = "PRINT";

	if( MainMenuForm->blnDirectPrint )
			strPrintText = "DIRECTPRINT";

	//print rack tags
	if( MainMenuForm->blnUseRackTicket && MainMenuForm->intRackTicketNumber > 0 && 	MainMenuForm->blnPrint )
	{

				   int iRackCopies = 0;
				   iRackCopies = iQty / MainMenuForm->intRackTicketNumber;

				   if( MainMenuForm->intRackTicketNumber * iRackCopies < iQty )
					   iRackCopies = iRackCopies + 1;



				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";


					if( MainMenuForm->blnLocalDatabase == false ) {

					   if( MainMenuForm->blnDirectPrint )
						   execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerDirect.exe";
					   else
						  execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

					} else {

							execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

					}

					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = MainMenuForm->strStoreNo+ " RackTicket.RDL "+ IntToStr(iRackCopies) +" "+strPrintText+" TICKETVIEW "+MainMenuForm->strReportFilter+" FALSE ";

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




	strPrintText = "PRINT";

	if( MainMenuForm->blnDirectPrint )
			strPrintText = "DIRECTPRINT";



	if(  MainMenuForm->strPickupAccount == "")
	{
			UpdateTicketView();
			TabControl1->TabIndex = 0;

             if(  MainMenuForm->blnPrint && MainMenuForm->blnEmailOnly == false  )
			   {


					//howMessage("Click OK after the First Ticket Prints!");

				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";



				  if( MainMenuForm->blnLocalDatabase == false) {

					if( MainMenuForm->blnDirectPrint )
						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerDirect.exe";
					else
						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

				   } else {
	                    execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

				   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   //AnsiString strParam = MainMenuForm->strStoreNo+ " "+MainMenuForm->strCustomTicket+" "+MainMenuForm->strTicketCopies+" "+strPrintText+" TICKETVIEW "+MainMenuForm->strReportFilter+" FALSE ";
                   AnsiString strParam = MainMenuForm->strStoreNo+ " "+MainMenuForm->strCustomTicket+" "+MainMenuForm->strTicketCopies+" "+strPrintText+" TICKETVIEW "+MainMenuForm->strReportFilter+" FALSE";

				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;

				   //ShowMessage(strParam);

				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
						return;
				   }


				   if( MainMenuForm->blnPrintTwice )
				   {
                             if( MainMenuForm->strPrintPause != "" )
							  {
								Sleep(StrToInt(MainMenuForm->strPrintPause));

							  }
							  else
							  {
								Sleep(500);
							  }

							  if(! ShellExecuteEx(&execinfo))
							  {
									ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
									return;
							  }

				   }
			}

			Label24->Text = "Close Menu";
			LeftLayout->Visible = true;

			SaveChangesIListBoxItem->Visible = false;
			SavePrintListBoxItem->Visible = false;
			QuickTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Enabled = true;

			Edit1->SetFocus();



	}
	else
	{

				ADOQuery1->Close();
				ADOQuery2->Close();
				ADOQuery3->Close();
				ADOQuery4->Close();
				ADOQuery5->Close();
				ADOQuery6->Close();


			   if(  MainMenuForm->blnPrint && MainMenuForm->blnEmailOnly == false )
			   {
				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";


					   if( MainMenuForm->blnLocalDatabase == false ) {

	if( MainMenuForm->blnDirectPrint )
				   execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerDirect.exe";
				   else
					  execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

   } else {
	
					  execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

   }

				   //AnsiString strParam = MainMenuForm->strStoreNo+ " "+ MainMenuForm->strReportFileName+" "+MainMenuForm->strReportFilter+" "+MainMenuForm->strTicketCopies+" "+strPrintText;
				   AnsiString strParam = MainMenuForm->strStoreNo+ " "+MainMenuForm->strCustomTicket+" "+MainMenuForm->strTicketCopies+" "+strPrintText+" TICKETVIEW "+MainMenuForm->strReportFilter+" FALSE";


				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL ;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
						return;
				   }
			   }


           	if( MainMenuForm->strPickupAccount != "" )
			  this->Close();
  }



		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

			SaveChangesIListBoxItem->Visible = false;
			SavePrintListBoxItem->Visible = false;
			QuickTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Enabled = true;

			Edit1->SetFocus();

		   if( MainMenuForm->blnRepeat )
		       WriteTicketListBoxItemClick(Sender);

			   if( MainMenuForm->blnPrePayAllToday )
				   this->Close();


}
//---------------------------------------------------------------------------



void __fastcall TWriteTicketForm01::Button7Click(TObject *Sender)
{
		TCommonCustomForm *FormSearch = Application->GetDeviceForm(L"SearchItemView");
		if (FormSearch )
		{
			FormSearch->ShowModal();

				ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' And StockNumber = '"+	MainMenuForm->strStockNumber +"' Order by Code");
		ADOQuery3->Active = true;

		if( MainMenuForm->strStockNumber == "" )
		{
		   delete FormSearch;
		   return;

		}
		if( ADOQuery3->Eof )
		{

			bool blnPopupScanCode =    ADOQuery4->FieldByName("AUTOPOPUPSCANCODE")->AsBoolean;
			strClass = ADOQuery4->FieldByName("Code")->AsString;
			blnClassTaxable = true; //ADOQuery4->FieldByName("Tax")->AsBoolean;
			strClassDescription =  ADOQuery4->FieldByName("Class")->AsString;
			Label23->Text = "Select Item for: "+strClassDescription;

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
			ADOQuery3->Active = true;


		   ShowMessage("Stock Item "+ 	MainMenuForm->strStockNumber + " is not Found!");
		   return;

		}

		 TicketItemsListBox->ItemIndex = 0;
		  TicketItemsListBoxClick(Sender);

		   delete FormSearch;
		}
}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ListBox1Click(TObject *Sender)
{
	int iLBI = ListBox1->ItemIndex;


	ADOQuery4->First();
	ADOQuery4->MoveBy(iLBI);


	if( ! ADOQuery4->Eof )
	{
		bool blnPopupScanCode =    ADOQuery4->FieldByName("AUTOPOPUPSCANCODE")->AsBoolean;
		strClass = ADOQuery4->FieldByName("Code")->AsString;
		blnClassTaxable = ADOQuery4->FieldByName("Tax")->AsBoolean;
		strClassDescription =  ADOQuery4->FieldByName("Class")->AsString;
		Label23->Text = "Select Item for: "+strClassDescription;

		ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
		ADOQuery3->Active = true;


        	blnUpcharge = false;

			blnSubDCItem = false;


			Button4->Enabled = true;
			Button5->Enabled = true;
			Button28->Enabled = true;
			Button6->Enabled = true;
			Button7->Enabled = true;
			Button8->Enabled = true;
			Button9->Enabled = true;
			Button4->Enabled = true;
			 Button27->Enabled = true;
			 Button32->Enabled = true;
			ListBox1->Enabled = true;
			 Button29->Visible = false;
			Label23->Text = "Select Item for: "+strClassDescription;



	   TicketItemsListBox->SetFocus();


	   if( blnPopupScanCode )
	   {
            Button7Click(Sender);

       }


   }
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button9Click(TObject *Sender)
{
	ListBox2->Items->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();

	TempListTax->Clear();
	TempListItemUpcharge->Clear();
	TempListClass->Clear();

      aPrices = new double[200];
		  aPieces = new int[200];
		  aLinePrices = new double[200];
		  fTotalPrices = 0.00;


       	memset(aPieces, 0, 200);
	memset(aPrices, 0, 200);
	memset(aLinePrices, 0, 200);

	UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::Button2Click(TObject *Sender)
{



if( Edit19->Text == "" )
{

  Edit19->Text = "0";
  ShowMessage("You Need to Enter a Quantity for Quick Ticket!");
  return;

}

  	TFM_PopupMessage01* FM_PopupMessage01;
	Application->CreateForm(__classid(TFM_PopupMessage01), &FM_PopupMessage01);
	if (FM_PopupMessage01 )
	{
		FM_PopupMessage01->Show();

	}


double fTotal = 0;
int iQty = 0;
double fTax = 0;

 ListBox2->Items->Clear();

AnsiString sQty;
AnsiString sItemDescription;
AnsiString sUpcharge;
AnsiString sPrice;

ADOQuery7->Active = false;
ADOQuery7->SQL->Clear();
ADOQuery7->SQL->Add("UPDATE STORE SET ORDERNO = ORDERNO + 1 where Store = '"+ MainMenuForm->strStoreNo+ "';Select OrderNo , ADDRESS1, CITY,STATE,ZIP,LOYALTY from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
ADOQuery7->Active = true;


AnsiString strOrderNo = ADOQuery7->FieldByName("OrderNo")->AsString;
ADOQuery7->Active = false;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportTicketView");
		if (Form)
		{
			MainMenuForm->strReportFileName = MainMenuForm->strCustomTicket ;
			 MainMenuForm->strTicketNumber = strOrderNo;
			MainMenuForm->strReportFilter = strOrderNo;
			MainMenuForm->strTicketPieceCount = Edit19->Text;
			MainMenuForm->strPC  = Edit19->Text;

			Form->ShowModal();
			delete Form;

		}
          if( MainMenuForm->fCouponTotal != 0 )
			 {

		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = 0;
		   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
           ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
		   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Coupon "+FloatToStrF( MainMenuForm->fCouponTotal  , ffCurrency, 12, 2);
			ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
		   ADOQuery2->FieldByName("CLASS")->AsString =  "C";

		   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

		   ADOQuery2->Post();


			 }


		ADOQuery6->Active = false;
	   ADOQuery6->SQL->Clear();
	   ADOQuery6->SQL->Text = "Select * from Invoice where STORE = '"+MainMenuForm->strStoreNo  +"' AND ORDERNO = '"+strOrderNo+"'";
		ADOQuery6->Active = false;

		if( ADOQuery6->Eof == false )
		{

		   ShowMessage("Error:  You're store Ticket number is set too low, you have tickets in this Range.  Go to Store Manager and raise the Ticket number or call the Vivaldi Support Center");
		   return;
        }


		TabControl1->TabIndex = 0;
			MainMenuForm->strCustomerAcct = ADOQuery1->FieldByName("ACCT")->AsString;

		   ADOQuery6->Open();
		   ADOQuery6->Insert();
		   ADOQuery6->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery6->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery6->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery6->FieldByName("NAME")->AsString = ADOQuery1->FieldByName("NAME")->AsString;
		   ADOQuery6->FieldByName("ROUTE")->AsString = ADOQuery1->FieldByName("ROUTE")->AsString;
		   ADOQuery6->FieldByName("STOP")->AsString = ADOQuery1->FieldByName("STOP")->AsString;
		   ADOQuery6->FieldByName("TAX")->AsString = fTax;
		   ADOQuery6->FieldByName("LOYALTY")->AsString = ADOQuery1->FieldByName("LOYALTY")->AsString;
		   ADOQuery6->FieldByName("BACCT")->AsString = ADOQuery1->FieldByName("BACCT")->AsString;
		   ADOQuery6->FieldByName("CLASS")->AsString = strClass;
		   ADOQuery6->FieldByName("STATUS")->AsString =  "Q";
		   ADOQuery6->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery6->FieldByName("DATEOUT")->AsString =  MainMenuForm->strDateOut;
		   ADOQuery6->FieldByName("AMT")->AsFloat = 0;
		   ADOQuery6->FieldByName("AMTPAID")->AsFloat =	MainMenuForm->fPrepayment;
		   ADOQuery6->FieldByName("DEPOSIT")->AsFloat =	MainMenuForm->fDeposit;
		   ADOQuery6->FieldByName("QTY")->AsString = Edit19->Text;
		   ADOQuery6->FieldByName("ISACTIVE")->AsBoolean =  true;

		   ADOQuery6->Post();

		    if( MainMenuForm->fCouponTotal != 0 )
			 {

		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = 0;
		   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
           ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
		   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Coupon "+FloatToStrF( MainMenuForm->fCouponTotal  , ffCurrency, 12, 2);
			ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
		   ADOQuery2->FieldByName("CLASS")->AsString =  "COUPON";

		   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

		   ADOQuery2->Post();


			 }



				if( MainMenuForm->fDeposit != 0 )
			 {

		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = 0;
		   //ADOQuery2->FieldByName("DATEOUT")->AsString = MainMenuForm->strDateOut;
           ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery2->FieldByName("QTY")->AsInteger =  0;
		   ADOQuery2->FieldByName("VALLINE")->AsInteger =  0;
		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  "Deposit: "+FloatToStrF( MainMenuForm->fDeposit , ffCurrency, 12, 2);
			ADOQuery2->FieldByName("COUPONLINE")->AsBoolean = true;
		   ADOQuery2->FieldByName("CLASS")->AsString =  "COUPON";

		   ADOQuery2->FieldByName("ITEM")->AsString =  "C";

		   ADOQuery2->Post();


			 }


		   ADOQuery2->Open();
		   ADOQuery2->Insert();
		   ADOQuery2->FieldByName("ORDERNO")->AsString = strOrderNo;
		   ADOQuery2->FieldByName("STORE")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
		   ADOQuery2->FieldByName("AMT")->AsFloat = 0;
		   ADOQuery2->FieldByName("QTY")->AsString = Edit19->Text;
		   ADOQuery2->FieldByName("VALLINE")->AsString = "0";
		   ADOQuery2->FieldByName("ITEMDESC")->AsString =  "QUICK TICKET";
		   ADOQuery2->FieldByName("CLASS")->AsString =  "D";
		   ADOQuery2->FieldByName("ITEM")->AsString =  "0";
		   ADOQuery2->FieldByName("DATEIN")->AsString = DateTimeToStr(Now());
		   ADOQuery2->Post();

               	ADOQuery1->Close();
				ADOQuery2->Close();
				ADOQuery3->Close();
				ADOQuery4->Close();
				ADOQuery5->Close();
				ADOQuery6->Close();

			AnsiString strPrintText = "PRINT";

		   if( MainMenuForm->blnDirectPrint )
			  strPrintText = "DIRECTPRINT";



	MainMenuForm->strReportFilter = strOrderNo;

	if( CheckBox9->IsChecked )
		   strPrintText = "PREVIEW";

			UpdateTicketView();
			TabControl1->TabIndex = 0;

             if(  MainMenuForm->blnPrint )
			   {
				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

					if( MainMenuForm->blnLocalDatabase ) {
						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

					   } else {

						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

					}
				   AnsiString strParam = MainMenuForm->strStoreNo+ " QuickTicketView.rdl "+MainMenuForm->strTicketCopies+" "+strPrintText+" TICKETVIEW "+MainMenuForm->strReportFilter+" FALSE";
				   MainMenuForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL ;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run Report Writer. Check that ReportViewer is Installed!");
						return;
				   }
			   }

			Label24->Text = "Close Menu";
			LeftLayout->Visible = true;

			SaveChangesIListBoxItem->Visible = false;
			SavePrintListBoxItem->Visible = false;
			QuickTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Visible = true;
			WriteTicketListBoxItem->Enabled = true;

			Edit1->SetFocus();




		this->Close();


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::SavePrintListBoxItemClick(TObject *Sender)
{
   Button8Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button6Click(TObject *Sender)
{
	MainMenuForm->strDescription = "";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"DescribeForm");
		if(Form)
		{


		   Form->ShowModal();

		   delete Form;
		   if( MainMenuForm->strDescription != "" )
		   {
			AnsiString strItem = MainMenuForm->strDescription ;
			AnsiString strItemCode = ADOQuery3->FieldByName("Code")->AsString;
			AnsiString newClass = "("+strClass+")";

			AnsiString newString = strItem + newClass;

			//TempListItemDescription->Add(newString);
			TempListQty->Add(strQty.Trim());
			TempListItemCode->Add(ADOQuery3->FieldByName("Code")->AsString) ;
			TempListClass->Add(strClass);
			TempListItemUpcharge->Add(strAlteration);

			if( blnClassTaxable )
			   TempListTax->Add("True");
			else
			   TempListTax->Add("False");

			fltPrice = MainMenuForm->dDescriptionPrice;
			aPrices[TempListQty->Count - 1] = fltPrice;
			aLinePrices[TempListQty->Count - 1] = fltPrice * StrToFloat(strQty);

			if( blnAlterationItem == false )
			  aPieces[TempListQty->Count - 1] = aPieces[TempListQty->Count - 1] + StrToFloat(strQty);

            TempListItemDescription->Add(newString+" "+strAlteration);


			if( strUpcharge.IsEmpty() || strUpcharge == NULL ||  strUpcharge != ""  )
				 strUpcharge = " ";

			strUpcharge = "";

			UpdateTicketView();
			}


		}

		 ListBox1->Enabled = true;
			 ListBox2->Enabled = true;
				Button6->Enabled = true;

					Button4->Enabled = true;
				Button5->Enabled = true;
					Button27->Enabled = true;
				Button32->Enabled = true;
						Button28->Enabled = true;
							Button7->Enabled = true;
								Button8->Enabled = true;
									Button9->Enabled = true;



}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Grid1DblClick(TObject *Sender)
{
   if( ADOQuery1->Eof == false )
   {

	MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
	WriteTicketListBoxItemClick(Sender);
   }
   else
      ShowMessage("Please search for a customer before trying to select nobody!");
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::FormShow(TObject *Sender)
{

this->Fill->Color = MainMenuForm->iBackgroundColor ;
	Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::MenuItem1Click(TObject *Sender)
{
 MainMenuForm->blnOK = false;
   MainMenuForm->strQuestion = "Would you like to remove the selected Record? ("+IntToStr(intSelectedLine)+")";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK )
	{


    }
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ListBox2Click(TObject *Sender)
{
	//int iLBI = ListBox2->ItemIndex;
   //		intSelectedLine = iLBI;

	//while( ListBox2-> )
	//{



   //	}


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button27Click(TObject *Sender)
{
int iLBI = ListBox2->ItemIndex;
	if( iLBI == -1 )
	{
		ShowMessage("Please Select a line to Remove on the Right First!");
		return;
	}

	int	intSelectedLine = -1;

	for( int i = 0; i < ListBox2->Items->Count; i++ )
	{

		  // ShowMessage( ListBox2->ItemByIndex(i)->Text);
		  if(  ListBox2->ItemByIndex(i)->Text != "" && ListBox2->ItemByIndex(i)->Text.SubString(0,1) != " " )
		  {
			intSelectedLine = intSelectedLine + 1;
		  }
		  if( i == iLBI )
			  break;


	}


	 MainMenuForm->blnOK = false;
  // MainMenuForm->strQuestion = "Would you like to remove the selected Record? ("+ TempListItemDescription->Strings[intSelectedLine]+")";

   double dNewPrice = 0;
   MainMenuForm->strDescription = TempListItemDescription->Strings[intSelectedLine];
	TCommonCustomForm *Form = Application->GetDeviceForm(L"DescribeForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;

			 MainMenuForm->strDescription = "";

			 dNewPrice = StrToFloat(MainMenuForm->dDescriptionPrice);


		}



	int iLast = intSelectedLine; // TempListQty->Count - 1;

	if( iLast > -1 )
	{


			aPrices[iLast] = dNewPrice;

			if(  TempListQty->Strings[iLast] == "" ||  TempListQty->Strings[iLast] == "0" )
			{
               aLinePrices[iLast] = dNewPrice;

			}
			else
				aLinePrices[iLast] = dNewPrice * TempListQty->Strings[iLast].ToInt();




	}


	ListBox2->Items->Clear();



	UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::MenuItem3Click(TObject *Sender)
{
	   Button8Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::MenuItem4Click(TObject *Sender)
{
		ListBox1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::MenuItem5Click(TObject *Sender)
{
	MainMenuForm->strSelectedClass = strClass;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"UpchargePopup");
	if(Form)
	{
		   Form->ShowModal();
	}

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button24Click(TObject *Sender)
{

				MainMenuForm->strQuantityType = "Quantity:";
				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuantityForm");
				if (Form )
				{
					Form->ShowModal();
					delete Form;

					TicketItemsListBox->Enabled = True;

					strQty = MainMenuForm->strEnterQuantity;
				}


}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button28Click(TObject *Sender)
{
 ListBox1->Enabled = false;
  ListBox2->Enabled = false;
	Button6->Enabled = false;

    	Button4->Enabled = false;
				Button5->Enabled = false;
					Button27->Enabled = false;
						Button28->Enabled = false;
						Button32->Enabled = false;
							Button7->Enabled = false;
								Button8->Enabled = false;
									Button9->Enabled = false;

   MainMenuForm->strSelectedClass  =  strClass;
	Button29->Visible = true;
	Button29->Text = "Exit Colors";
    ADOQuery3->Active = false;
	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("Select * from COLORS where StoreNO = '"+ MainMenuForm->strStoreNo+ "' Order by Code");
	ADOQuery3->Active = true;
	blnUpcharge = true;

	Label23->Text = "Select Colors";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button29Click(TObject *Sender)
{

	if( MainMenuForm->blnAutoPopupColor && Button29->Text != "Exit Colors")
			{
			 Button28Click(Sender);
			 return;
			}

			 ListBox1->Enabled = true;
			 ListBox2->Enabled = true;
				Button6->Enabled = true;

					Button4->Enabled = true;
				Button5->Enabled = true;
					Button27->Enabled = true;
				Button32->Enabled = true;
						Button28->Enabled = true;
							Button7->Enabled = true;
								Button8->Enabled = true;
									Button9->Enabled = true;


	        blnUpcharge = false;
            Button29->Text = "Exit Upcharges";
			blnSubDCItem = false;

			ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by SortOrder,Code");
			ADOQuery3->Active = true;
			Button4->Enabled = true;
			Button5->Enabled = true;
			Button28->Enabled = true;
			Button6->Enabled = true;
			Button7->Enabled = true;
			Button8->Enabled = true;
			Button9->Enabled = true;
			Button4->Enabled = true;
			 Button27->Enabled = true;
			 Button32->Enabled = true;
			ListBox1->Enabled = true;
			 Button29->Visible = false;
			Label23->Text = "Select Item for: "+strClassDescription;

            	strQty = "1";


}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::CheckBox3Click(TObject *Sender)
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

void __fastcall TWriteTicketForm01::Button30Click(TObject *Sender)
{
  if(  Edit3->Text == "" ||  Edit4->Text == "" )
  {
	 //ShowMessage("Customer Name and Account (Phone) are required to Save");
	 Edit3->SetFocus();
	 return;

  }



	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
	   {

		

		 ADOQuery1->Post();
	   }
	   ADOQuery1->MoveBy(1);
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button31Click(TObject *Sender)
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

void __fastcall TWriteTicketForm01::Button32Click(TObject *Sender)
{
int iLBI = ListBox2->ItemIndex;
	if( iLBI == -1 )
	{
		ShowMessage("Please Select a line to Change on the Right First!");
		return;
	}

	int	intSelectedLine = -1;

	for( int i = 0; i < ListBox2->Items->Count; i++ )
	{

		  // ShowMessage( ListBox2->ItemByIndex(i)->Text);
		  if(  ListBox2->ItemByIndex(i)->Text != "" && ListBox2->ItemByIndex(i)->Text.SubString(0,1) != " " )
		  {
			intSelectedLine = intSelectedLine + 1;
		  }
		  if( i == iLBI )
			  break;


	}


	MainMenuForm->blnOK = false;

	double dNewPrice = 0;
	MainMenuForm->strDescription = TempListItemDescription->Strings[intSelectedLine];

	MainMenuForm->strQuantityType = "Quantity:";
	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuantityForm");
	if (Form )
	{
					Form->ShowModal();
					delete Form;

					TicketItemsListBox->Enabled = True;

					if( MainMenuForm->strEnterQuantity == "" )
					{
						MainMenuForm->strEnterQuantity = "0";
                    }

					strQty = MainMenuForm->strEnterQuantity;
	}


	int iLast = intSelectedLine; // TempListQty->Count - 1;

    if( iLast > -1 )
	{


			double dValLine = 0;
			if (TempListQty->Strings[iLast].ToInt() != 0 )
			{
					dValLine = aPieces[iLast]  / TempListQty->Strings[iLast].ToInt();
					TempListQty->Strings[iLast] = strQty;
					aPieces[iLast] = dValLine *  TempListQty->Strings[iLast].ToInt();
			}
			else
			{
					dValLine = 0;
					TempListQty->Strings[iLast] = strQty;
					aPieces[iLast] = 0;

            }



			if( TempListQty->Strings[iLast].ToInt() == 0 )
			{
			   aLinePrices[iLast] = aPrices[iLast];
			}
			else
			   aLinePrices[iLast] = aPrices[iLast]  * TempListQty->Strings[iLast].ToInt();



	}


	ListBox2->Items->Clear();

	strQty = "1";

	UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button33Click(TObject *Sender)
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


void __fastcall TWriteTicketForm01::Grid1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{


   //if( ADOQuery1->Eof == false )
   //{

  //	MainMenuForm->blnAccountCustomer = ADOQuery1->FieldByName("ACCOUNT")->AsBoolean;
  //	WriteTicketListBoxItemClick(Sender);
  // }
  // else
  //	  ShowMessage("Please search for a customer before trying to select nobody!");



}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::Edit4Change(TObject *Sender)
{
	 if( ADOQuery1->FieldByName("ID")->AsString == "" )
	 {
	  ADOQuery14->Active = false;
	  ADOQuery14->SQL->Clear();
	  ADOQuery14->SQL->Text = "Select * from customer where STORE IN ("+MainMenuForm->strEnterprise +") And ACCT = '"+ Edit4->Text +"'";
	  ADOQuery14->Active = true;



	   ADOQuery14->Active = false;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Image4Click(TObject *Sender)
{
   Button8Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Image1Click(TObject *Sender)
{

   	if( MainMenuForm->bln64Bit )
		WinExec("C:\\Program Files\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);



}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button35Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button38Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button39Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button40Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button41Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button42Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button43Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button44Click(TObject *Sender)
{
Edit1->Text =  "";
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Image3Click(TObject *Sender)
{
	if( MainMenuForm->bln64Bit )
	  WinExec("C:\\Program Files\\Notepad++\\Notepad++.exe", SW_NORMAL);
	else
	  WinExec("C:\\Program Files (x86)\\Notepad++\\Notepad++.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Image2Click(TObject *Sender)
{
		if( MainMenuForm->bln64Bit )
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);

}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox1Click(TObject *Sender)
{
			if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}

			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " BLACK";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox2Click(TObject *Sender)
{
           	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " WHITE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox3Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " GRAY";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox4Click(TObject *Sender)
{
           	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " LT BLUE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox5Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " BLUE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox6Click(TObject *Sender)
{
           	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " NAVY";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox7Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " PURPLE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox8Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " PINK";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox9Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " YELLOW";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox10Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " ORANGE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox11Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " LIME";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox12Click(TObject *Sender)
{
				if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
			   return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " GREEN";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox13Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " OLIVE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox14Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " TAN";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox15Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " SLATE";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox16Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " LT BRN";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox17Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " RED";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox18Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " BROWN";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox19Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " SALMON";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox20Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " HT PNK";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox21Click(TObject *Sender)
{
             	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " AQUA";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox22Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " ALMOND";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox23Click(TObject *Sender)
{
            	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}
			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " DRK GRY";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ColorBox24Click(TObject *Sender)
{           	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}

			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " PEACH";

			UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::ListBox3Click(TObject *Sender)
{
	if( TempListQty->Count == 0 )
			{
			   ShowMessage("You must select an Item First");
               return;
			}

				int iLBI = ListBox3->ItemIndex;
	ADOQuery18->First();
	ADOQuery18->MoveBy(iLBI);

	if( ! ADOQuery18->Eof )
	{


			double ftempqty = StrToFloat( strQty );
			strUpcharge = ADOQuery18->FieldByName("Item")->AsString+"("+strQty+")";
			fltPrice = ADOQuery18->FieldByName("Amt")->AsFloat;

			aPrices[TempListQty->Count - 1] = aPrices[TempListQty->Count - 1] + fltPrice;
			aLinePrices[TempListQty->Count - 1] = aLinePrices[TempListQty->Count - 1] + (fltPrice * ftempqty );

			TempListItemUpcharge->Strings[TempListQty->Count - 1] = TempListItemUpcharge->Strings[TempListQty->Count - 1] + " " +strUpcharge;


			UpdateTicketView();
	}
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button13Click(TObject *Sender)
{
MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Customer? This will remove this customer completely!  Are you sure?";

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

void __fastcall TWriteTicketForm01::Button25Click(TObject *Sender)
{
 Label19->Visible = true;
	 Edit31->Visible = true;
	 Button31->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TWriteTicketForm01::Button46Click(TObject *Sender)
{
int iLBI = ListBox2->ItemIndex;
	if( iLBI == -1 )
	{
		ShowMessage("Please Select a line to Remove on the Right First!");
		return;
	}

	int	intSelectedLine = -1;

	for( int i = 0; i < ListBox2->Items->Count; i++ )
	{

		  // ShowMessage( ListBox2->ItemByIndex(i)->Text);
		  if(  ListBox2->ItemByIndex(i)->Text != "" && ListBox2->ItemByIndex(i)->Text.SubString(0,1) != " " )
		  {
			intSelectedLine = intSelectedLine + 1;
		  }
		  if( i == iLBI )
			  break;


	}


	 MainMenuForm->blnOK = false;
  // MainMenuForm->strQuestion = "Would you like to remove the selected Record? ("+ TempListItemDescription->Strings[intSelectedLine]+")";

   double dNewPrice = 0;
   MainMenuForm->strDescription = TempListItemDescription->Strings[intSelectedLine];

   TempListItemDescription->Strings[intSelectedLine] = TempListItemDescription->Strings[intSelectedLine]+" (REDO)";


	int iLast = intSelectedLine; // TempListQty->Count - 1;

	if( iLast > -1 )
	{


			aPrices[iLast] = 0;

			if(  TempListQty->Strings[iLast] == "" ||  TempListQty->Strings[iLast] == "0" )
			{
               aLinePrices[iLast] = 0;

			}
			else
				aLinePrices[iLast] = dNewPrice * TempListQty->Strings[iLast].ToInt();




	}


	ListBox2->Items->Clear();



	UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button47Click(TObject *Sender)
{

	ADOQuery7->Active = false;
ADOQuery7->SQL->Clear();
ADOQuery7->SQL->Add("UPDATE STORE SET CUSTNUM = CUSTNUM + 1 where Store = '"+ MainMenuForm->strStoreNo+ "';Select CUSTNUM from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
ADOQuery7->Active = true;


 ADOQuery1->FieldByName("ACCT")->AsString = ADOQuery7->FieldByName("CUSTNUM")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button48Click(TObject *Sender)
{

			ListBox1->Enabled = true;
				Button8->Enabled = true;
					Button4->Enabled = true;
			Button5->Enabled = true;
					Button28->Enabled = true;
			Button6->Enabled = true;
			Button7->Enabled = true;
			Button8->Enabled = true;
			Button9->Enabled = true;
			Button4->Enabled = true;
			Button27->Enabled = true;
			Button32->Enabled = true;
				strQty = "1";


	   TCommonCustomForm *FormSearch = Application->GetDeviceForm(L"SearchItemView");
		if (FormSearch )
		{
			FormSearch->ShowModal();

				ADOQuery20->Active = false;
		ADOQuery20->SQL->Clear();
		ADOQuery20->SQL->Add("Select * from CUSTTAG where StoreNO = '"+ MainMenuForm->strStoreNo+ "' And TAGCODE = '"+	MainMenuForm->strStockNumber +"'");
		ADOQuery20->Active = true;

		if( MainMenuForm->strStockNumber == "" )
		{
		   delete FormSearch;
		   return;

		}
		if(  ADOQuery20->Eof == false )
		{
		   //	TempListItemDescription->Add(ADOQuery20->FieldByName("DESC")->AsString);


		   MainMenuForm->strDescription =   ADOQuery20->FieldByName("DESC")->AsString;

			strClass = ADOQuery20->FieldByName("Class")->AsString;
			blnClassTaxable = true;  //ADOQuery3->FieldByName("Tax")->AsBoolean;
			AnsiString strCode =  ADOQuery20->FieldByName("ItemCode")->AsString;
			AnsiString strSubCode =  ADOQuery20->FieldByName("SubCode")->AsString;
			Label23->Text = "Select Item for: "+ADOQuery20->FieldByName("Desc")->AsString;

				ADOQuery3->Active = false;
			ADOQuery3->SQL->Clear();
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' And Code = '"+strCode+"'");
			ADOQuery3->Active = true;
            if(  ADOQuery3->Eof  )
			{
							 ShowMessage("This Tag Item has been removed from the item file.  Please add the Class and Code back");
                             delete FormSearch;
							 return;
			}

			if( strSubCode != "" )
			{
                	ADOQuery3->Active = false;
					ADOQuery3->SQL->Clear();
					ADOQuery3->SQL->Add("Select * from SUBDCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' And Code = '"+strSubCode+"' And ItemCode = '"+strCode +"'");
					ADOQuery3->Active = true;
					 if(  ADOQuery3->Eof  )
					{
							 ShowMessage("This Tag Item has been removed from the item file.  Please add the Class and Code back");
                             delete FormSearch;
							 return;
					}
					else
					{
							blnSubDCItem = true;
						
					 }

			}



		  if( MainMenuForm->strTicketNumber == "" )
		  {
                ADOQuery7->Active = false;
				ADOQuery7->SQL->Clear();
				ADOQuery7->SQL->Add("UPDATE STORE SET ORDERNO = ORDERNO + 1 where Store = '"+ MainMenuForm->strStoreNo+ "';Select OrderNo, NAME, ADDRESS1, CITY, STATE, ZIP , PHONE, LOGIN, LOYALTY from Store where Store = '"+ MainMenuForm->strStoreNo+ "'");
				ADOQuery7->Active = true;

				AnsiString strOrderNo = ADOQuery7->FieldByName("OrderNo")->AsString;
				MainMenuForm->strTicketNumber = strOrderNo;
		  }

			 //MainMenuForm->strTicketNumber


             MainMenuForm->blnItemTagEntered = true;
		   	AnsiString strItem = MainMenuForm->strDescription ;
			AnsiString strItemCode = ADOQuery20->FieldByName("ITEMCODE")->AsString;
			AnsiString newClass = "("+ADOQuery20->FieldByName("CLASS")->AsString+")";

			AnsiString newString = strItem + newClass;

			//TempListItemDescription->Add(newString);
			TempListQty->Add(strQty.Trim());
			TempListItemCode->Add(ADOQuery20->FieldByName("ITEMCODE")->AsString) ;
			TempListClass->Add(strClass);
			TempListItemUpcharge->Add("("+MainMenuForm->strStockNumber+") "+ADOQuery20->FieldByName("UPCHARGE")->AsString);

			//if( ADOQuery3->FieldByName("TAX")->AsBoolean )
			   TempListTax->Add("True");
			//else
			//   TempListTax->Add("False");

			fltPrice = ADOQuery3->FieldByName("AMT")->AsFloat;
			aPrices[TempListQty->Count - 1] = fltPrice;
			aLinePrices[TempListQty->Count - 1] = fltPrice;


			aPieces[TempListQty->Count - 1] = aPieces[TempListQty->Count - 1] + 1;

            TempListItemDescription->Add(ADOQuery20->FieldByName("DESC")->AsString);

             	ADOQuery20->Active = false;
						ADOQuery20->SQL->Clear();
						ADOQuery20->SQL->Text = "UPDATE CUSTTAG SET ORDERNO = '"+MainMenuForm->strTicketNumber +"', LASTIN = GETDATE() WHERE StoreNO = '"+ MainMenuForm->strStoreNo+ "' And TAGCODE = '"+	MainMenuForm->strStockNumber +"'";
						ADOQuery20->ExecSQL();


			 ADOQuery20->Active = false;

			UpdateTicketView();


		}
		else
		{
           ADOQuery20->Active = false;
			ShowMessage("Tag Code "+ 	MainMenuForm->strStockNumber + " is not Found!");


        }



		   delete FormSearch;


		   Button48Click(Sender);

		}
}
//---------------------------------------------------------------------------

void __fastcall TWriteTicketForm01::Button49Click(TObject *Sender)
{

	 if (MainMenuForm->dblRushFee == 0 ) {
        	ShowMessage("You need to enter a Rush % Fee in Store Manager!");
		return;
	 }

	int iLBI = ListBox2->ItemIndex;

	if( iLBI == -1 )
	{
		ShowMessage("Please Select a line to RUSH First!");
		return;
	}

	int	intSelectedLine = -1;

	for( int i = 0; i < ListBox2->Items->Count; i++ )
	{


		  if(  ListBox2->ItemByIndex(i)->Text != "" && ListBox2->ItemByIndex(i)->Text.SubString(0,1) != " " )
		  {
			intSelectedLine = intSelectedLine + 1;
		  }
		  if( i == iLBI )
			  break;


	}




	int iLast = intSelectedLine; // TempListQty->Count - 1;

	if( iLast > -1 )
	{



			TempListItemUpcharge->Strings[iLast] = + " **RUSH**" + TempListItemUpcharge->Strings[iLast] ;


			//if(  TempListQty->Strings[iLast] == "" ||  TempListQty->Strings[iLast] == "0" )
			//{
			   aLinePrices[iLast] = aLinePrices[iLast] + (aLinePrices[iLast] * (MainMenuForm->dblRushFee/100));

			//}




	}


	ListBox2->Items->Clear();

	UpdateTicketView();

}
//---------------------------------------------------------------------------

