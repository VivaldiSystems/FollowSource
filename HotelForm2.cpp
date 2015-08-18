//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "HotelForm2.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
#include <shellapi.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
THotelForm *HotelForm;
//---------------------------------------------------------------------------
__fastcall THotelForm::THotelForm(TComponent* Owner)
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

			// ADOQuery3->Active = false;
		   //	ADOQuery3->SQL->Clear();
		   //	ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
		   //	ADOQuery3->Active = true;
		   //	Label26->Text = "Sub Total:   $0.00";
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
void __fastcall THotelForm::HeaderButtonClick(TObject *Sender)
{


 if( ! ADOQuery1->Eof && (Edit3->Text == "" ||  Edit4->Text == "" ) )
  {
	 ShowMessage("Customer Name and Account (Phone) are required to Save");
	// Edit3->SetFocus();
	 return;

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
//---------------------------------------------------------------------------

void THotelForm::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------


void __fastcall THotelForm::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall THotelForm::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";
      MainMenuForm->strLastSearch = Edit1->Text;
	  //ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	  if( Edit34->Text == "" )
	  {

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {
	   ADOQuery1->SQL->Clear();

	  ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND CLHOTEL = 1 order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
	   ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND CLHOTEL = 1 order by name";


	  }
	  }
	  else
	  {

           if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {
	    ADOQuery1->SQL->Clear();

		ADOQuery1->SQL->Text = "Select * from customer where acct like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") AND ROUTE = '"+Edit34->Text +"' AND CLHOTEL = 1 order by acct";

	  }
	  else
	  {
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Text = "Select * from customer where name like '%"+Edit1->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +")  AND ROUTE = '"+Edit34->Text +"'  AND CLHOTEL = 1 order by name";


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
		 //  EditCustomerListBoxItem->Enabled = false;
      }

}
//---------------------------------------------------------------------------


void __fastcall THotelForm::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall THotelForm::SelectCustomerListBoxItemClick(TObject *Sender)
{
 //SaveChangesIListBoxItem->SubTitle = "";


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
		 // EditCustomerListBoxItem->Enabled = true;
	  }
	  else
	  {
		 // WriteTicketListBoxItem->Enabled = false;
		 // QuickTicketListBoxItem->Enabled = false;
		  // EditCustomerListBoxItem->Enabled = false;
	  }


}




void __fastcall THotelForm::EditCustomerListBoxItemClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

	//SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;

	Edit4->Enabled = false;
   //	 SaveChangesIListBoxItem->SubTitle = "";
	ComboEdit1->Text = ADOQuery1->FieldByName("STARCH")->AsString;

	 Label41->Visible = false;


}
//---------------------------------------------------------------------------


void __fastcall THotelForm::AddCustomerListBoxItemClick(TObject *Sender)
{


     if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();




	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery2->Insert() ;
	ADOQuery2->FieldByName("StoreNo")->AsString = MainMenuForm->strStoreNo;

}
//---------------------------------------------------------------------------



void __fastcall THotelForm::Button5Click(TObject *Sender)
{


    ADOQuery3->Active = false;
	ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Add("Select * from UPCHARGE where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
	ADOQuery3->Active = true;
	blnUpcharge = true;

	Label23->Text = "Select Upcharge";

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::SaveChangesIListBoxItemClick(TObject *Sender)
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
            Edit4->Enabled = false;
		 ADOQuery1->Post();

		 Label41->Visible = true;
		// SaveChangesIListBoxItem->SubTitle = "Saved";
          ShowMessage("Changes Saved");

	   }

	

}
//---------------------------------------------------------------------------




void __fastcall THotelForm::TicketItemsListBoxClick(TObject *Sender)
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
			ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
			ADOQuery3->Active = true;

			ListBox1->Enabled = true;
			strQty = "1";
		}
		}

    }



}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall THotelForm::UpdateTicketView()
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
void __fastcall THotelForm::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button4Click(TObject *Sender)
{

ADOQuery3->Active = false;
ADOQuery3->SQL->Clear();
ADOQuery3->SQL->Add("Select * from DCITEM where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and Class = '"+strClass+"' Order by Code");
ADOQuery3->Active = true;


}
//---------------------------------------------------------------- -----------

void __fastcall THotelForm::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button8Click(TObject *Sender)
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

void __fastcall THotelForm::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------


void __fastcall THotelForm::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::ListBox1Click(TObject *Sender)
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

void __fastcall THotelForm::Button9Click(TObject *Sender)
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


void __fastcall THotelForm::Button12Click(TObject *Sender)
{
	 ADOQuery7->Active = false;
			ADOQuery7->SQL->Clear();
			ADOQuery7->SQL->Add("Select * from INVOICEHISTORY where Storeno = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' Order by ORDERNO");
			ADOQuery7->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button11Click(TObject *Sender)
{
	 ADOQuery7->Active = false;
			ADOQuery7->SQL->Clear();
			ADOQuery7->SQL->Add("Select * from INVOICEHISTORY where Storeno = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' and EventDate > GetDate() - 30 Order by ORDERNO");
			ADOQuery7->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button27Click(TObject *Sender)
{
  ADOQuery6->Active = false;
			ADOQuery6->SQL->Clear();
			ADOQuery6->SQL->Add("Select ORDERNO,ACCT,NAME,DATEIN,DATEOUT,QTY,AMT,STATUS,AMTPAID from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' AND DATEIN > GetDate() - 30 Order by ORDERNO");
			ADOQuery6->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button28Click(TObject *Sender)
{
  ADOQuery6->Active = false;
			ADOQuery6->SQL->Clear();
			ADOQuery6->SQL->Add("Select ORDERNO,ACCT,NAME,DATEIN,DATEOUT,QTY,AMT,STATUS,AMTPAID from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "' AND ACCT = '"+ADOQuery1->FieldByName("ACCT")->AsString.Trim()+"' Order by ORDERNO");
			ADOQuery6->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::CornerButton1Click(TObject *Sender)
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


void __fastcall THotelForm::CheckBox3Exit(TObject *Sender)
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

void __fastcall THotelForm::Button29Click(TObject *Sender)
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

void __fastcall THotelForm::Button30Click(TObject *Sender)
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

void __fastcall THotelForm::Button13Click(TObject *Sender)
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
	   //	ADOQuery1->Delete();

	}
}
//---------------------------------------------------------------------------



void __fastcall THotelForm::Edit4Change(TObject *Sender)
{
 if( ADOQuery1->FieldByName("ID")->AsString == "" )
	 {
	  ADOQuery8->Active = false;
	  ADOQuery8->SQL->Clear();
	  ADOQuery8->SQL->Text = "Select * from customer where STORE IN ("+MainMenuForm->strEnterprise +") And ACCT = '"+ Edit4->Text +"'";
	  ADOQuery8->Active = true;

	  if(  ADOQuery8->Eof == false )
		 ShowMessage("Customer with this Account number already exists!");


	   ADOQuery8->Active = false;
	 }
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button25Click(TObject *Sender)
{
	 Label19->Visible = true;
	 Edit31->Visible = true;
	 Button31->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button31Click(TObject *Sender)
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
						ADOQuery9->SQL->Text = "UPDATE INVOICE SET ACCT = '"+Edit31->Text+"' WHERE STORE = "+MainMenuForm->strStoreNo  +" AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();


						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE ORDERS SET ACCT = '"+Edit31->Text+"' WHERE STORE = "+MainMenuForm->strStoreNo  +" AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();

						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE AR SET ACCT = '"+Edit31->Text+"' WHERE STORENO = "+MainMenuForm->strStoreNo  +" AND ACCT = '"+Edit4->Text+"'";
						ADOQuery9->ExecSQL();

						ADOQuery9->Active = false;
						ADOQuery9->SQL->Clear();
						ADOQuery9->SQL->Text = "UPDATE CASHBOX SET ACCT = '"+Edit31->Text+"' WHERE STORENO = "+MainMenuForm->strStoreNo  +" AND ACCT = '"+Edit4->Text+"'";
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

void __fastcall THotelForm::ComboEdit1Change(TObject *Sender)
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
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button10Click(TObject *Sender)
{
	  ADOQuery1->Edit();
	  ADOQuery1->FieldByName("LOYALTYLEVEL")->AsFloat = 0;
	  ADOQuery1->Post();
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button32Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\VIVALDI8\\FreeVK.exe";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
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

void __fastcall THotelForm::Button33Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button34Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button35Click(TObject *Sender)
{
  Edit1->Text =  Edit1->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button36Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button37Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button38Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button39Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button40Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button41Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button42Click(TObject *Sender)
{
Edit1->Text =  Edit1->Text + "9";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button43Click(TObject *Sender)
{
Edit1->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::FormShow(TObject *Sender)
{
  //this->Fill->Color = MainMenuForm->iBackgroundColor ;
}
//---------------------------------------------------------------------------



void __fastcall THotelForm::Grid1DblClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

   //	SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
  //	SaveChangesIListBoxItem->Enabled = true;

	Edit4->Enabled = false;
   //	 SaveChangesIListBoxItem->SubTitle = "";
	ComboEdit1->Text = ADOQuery1->FieldByName("STARCH")->AsString;

     Label41->Visible = false;

   //WriteTicketListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall THotelForm::Button44Click(TObject *Sender)
{
	 //https://maps.google.com/?q=9412+sapphire+ave,hesperia,ca,92344


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
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG


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

void __fastcall THotelForm::SpeedButton2Click(TObject *Sender)
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
		ADOQuery2->Delete();

	}
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::SpeedButton6Click(TObject *Sender)
{
TabControl1->TabIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall THotelForm::SpeedButton5Click(TObject *Sender)
{
//SaveChangesIListBoxItem->SubTitle = "";


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
		  //EditCustomerListBoxItem->Enabled = true;
	  }
	  else
	  {
		 // WriteTicketListBoxItem->Enabled = false;
		 // QuickTicketListBoxItem->Enabled = false;
		 //  EditCustomerListBoxItem->Enabled = false;
	  }

}
//---------------------------------------------------------------------------

