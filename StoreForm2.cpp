//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "StoreForm2.h"
#include "MainMenu.h"
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TStoreForm01 *StoreForm01;
//---------------------------------------------------------------------------
__fastcall TStoreForm01::TStoreForm01(TComponent* Owner)
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




         	Label23->Text = "Select Item";
		 Edit1->SetFocus();
          // this->Fill->Color = MainMenuForm->iBackgroundColor ;
}
//---------------------------------------------------------------------------
void __fastcall TStoreForm01::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------
void __fastcall TStoreForm01::FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
		  bool &Handled)
{
	float DX, DY;

	if (EventInfo.GestureID == igiPan) {
		if (EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin)
		  && (Sender == ToolbarPopup || EventInfo.Location.Y > (ClientHeight - 70))) {
			FGestureOrigin = EventInfo.Location;
			FGestureInProgress = true;
		}
	}

	if (FGestureInProgress && EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
		FGestureInProgress = false;
		DX = EventInfo.Location.X - FGestureOrigin.X;
		DY = EventInfo.Location.Y - FGestureOrigin.Y;
		if (fabs(DY) > fabs(DX)) {
			ShowToolbar(DY < 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	ShowToolbar(Button == TMouseButton::mbRight);
}
//---------------------------------------------------------------------------
void TStoreForm01::ShowToolbar(bool AShow)
{
 
}


//---------------------------------------------------------------------------

void __fastcall TStoreForm01::FormActivate(TObject *Sender)
{
   //	WindowState = TWindowState::wsMaximized;
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TStoreForm01::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  if( MainMenuForm->blnEnableEnterprise )
		  ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strEnterprise +") Order by STORE";
	  else
		 ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strStoreNo +") Order by STORE";

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


void __fastcall TStoreForm01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------


void __fastcall TStoreForm01::EditCustomerListBoxItemClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

	//SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
   //	SaveChangesIListBoxItem->Enabled = true;

	TIniFile& tfile = *new TIniFile("C:\\FOLLOW\\FOLLOW.INI");

			  MainMenuForm->strTicketPrinter = tfile.ReadString("TICKETS","TICKETPRINTER","DEFAULT");
			  Edit32->Text =  MainMenuForm->strTicketPrinter;


			  MainMenuForm->strTagPrinter = tfile.ReadString("TICKETS","TAGPRINTER","DEFAULT");
			  Edit33->Text = MainMenuForm->strTagPrinter;

				  MainMenuForm->strTagPrinter = tfile.ReadString("TICKETS","RECEIPTPRINTER","DEFAULT");
			  Edit52->Text = MainMenuForm->strTagPrinter;



   //WriteTicketListBoxItem->Enabled = true;

}
//---------------------------------------------------------------------------






void __fastcall TStoreForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{


	   TIniFile& tfile = *new TIniFile("C:\\FOLLOW\\FOLLOW.INI");


		tfile.WriteString("TICKETS","TICKETPRINTER", Edit32->Text);
		tfile.ReadString("TICKETS","TAGPRINTER",Edit33->Text);

		tfile.WriteString("TICKETS","RECEIPTPRINTER",Edit52->Text);


	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

		   //	MainMenuForm->iBackgroundColor  = ADOQuery1->FieldByName("COLOR")->AsFloat;
		MainMenuForm->dblEnvironmental = ADOQuery1->FieldByName("ENVIRONMENTAL")->AsFloat;
		MainMenuForm->strEnvironmentalClasses  = ADOQuery1->FieldByName("ENVIRONMENTALCLASSES")->AsString;

			MainMenuForm->dblActualEnvironmentalFee  = 0;
		MainMenuForm->strCustomTicket  = ADOQuery1->FieldByName("CUSTOMTICKET")->AsString;

		if( MainMenuForm->strCustomTicket  == "" )
		  MainMenuForm->strCustomTicket = "TicketView.rdl";

		MainMenuForm->blnAutoSelectLastCustomer     = ADOQuery1->FieldByName("SELECTLASTCUSTOMER")->AsBoolean;
		MainMenuForm->strCreditCardPath  = ADOQuery1->FieldByName("CREDITCARDPATH")->AsString;
		MainMenuForm->blnUseCreditCardProcessing   = ADOQuery1->FieldByName("USECREDITCARD")->AsBoolean;
		MainMenuForm->blnShowColorList  = ADOQuery1->FieldByName("SHOWCOLORLIST")->AsBoolean;
		MainMenuForm->blnTransactionLogin  = ADOQuery1->FieldByName("TransactionLogin")->AsBoolean;
		MainMenuForm->intDaysToPickup = ADOQuery1->FieldByName("DAYSTOPICKUP")->AsInteger;
		MainMenuForm->strSenderEmail = ADOQuery1->FieldByName("SENDEREMAIL")->AsString;
		MainMenuForm->strSenderPassword = ADOQuery1->FieldByName("SENDERPASSWORD")->AsString;
		MainMenuForm->strSendercc = ADOQuery1->FieldByName("SENDERCC")->AsString;
		MainMenuForm->strEmailPort   = ADOQuery1->FieldByName("EMAILPORT")->AsString;
		MainMenuForm->strSMTPServer = ADOQuery1->FieldByName("SMTPSERVER")->AsString;
		MainMenuForm->blnAutoPopupColor = ADOQuery1->FieldByName("AUTOPOPUPCOLOR")->AsBoolean;
		MainMenuForm->blnAutoPopUpcharges = ADOQuery1->FieldByName("AUTOPOPUPUPCHARGE")->AsBoolean;
		MainMenuForm->blnUseCashDrawer = ADOQuery1->FieldByName("USECASHDRAWER")->AsBoolean;
		MainMenuForm->blnUseTags = ADOQuery1->FieldByName("PRINTTAGS")->AsBoolean;
		MainMenuForm->strNoTagsFor = ADOQuery1->FieldByName("NOTAGSFOR")->AsString;
		MainMenuForm->blnUsePriceLevel = ADOQuery1->FieldByName("USEPRICELEVEL")->AsBoolean;

		MainMenuForm->blnDefaultLoyalty  = ADOQuery1->FieldByName("DEFAULTLOYALTY")->AsBoolean;

		if(  ADOQuery1->FieldByName("EMAILSECURITY")->AsBoolean )
		{
		   MainMenuForm->strEmailSecurity = "USE-U";
		}



		 MainMenuForm->blnSendReadyEmail =   ADOQuery1->FieldByName("SENDEMAILREADY")->AsBoolean;


		 MainMenuForm->blnSendTicketEmail =   ADOQuery1->FieldByName("SENDEMAILTICKET")->AsBoolean;


			MainMenuForm->strStoreName = ADOQuery1->FieldByName("Name")->AsString;
			MainMenuForm->strCityState = ADOQuery1->FieldByName("City")->AsString+", "+ADOQuery1->FieldByName("State")->AsString;
			if( ADOQuery1->FieldByName("TaxRate")->AsString != "" )
			{
			  MainMenuForm->fTaxRate = ADOQuery1->FieldByName("TaxRate")->AsFloat;
			}
			else
			{
               MainMenuForm->fTaxRate = 0;

            }

			 MainMenuForm->strTicketCopies = ADOQuery1->FieldByName("TicketCopies")->AsString;

			 if( MainMenuForm->strTicketCopies == "" )
				MainMenuForm->strTicketCopies = "2";




		 ShowMessage("Changes to Settings will not take affect until you exit Vivaldi 8 and log back in!");


}
//---------------------------------------------------------------------------





void __fastcall TStoreForm01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TStoreForm01::UpdateTicketView()
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
void __fastcall TStoreForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TStoreForm01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button8Click(TObject *Sender)
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

void __fastcall TStoreForm01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button13Click(TObject *Sender)
{
ADOQuery1->Active = false;


	Close();

//
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button9Click(TObject *Sender)
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


void __fastcall TStoreForm01::FormShow(TObject *Sender)
{
 //this->Fill->Color = MainMenuForm->iBackgroundColor ;

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	   if( MainMenuForm->blnEnableEnterprise )
		  ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strEnterprise +") Order by STORE";
	   else
		  ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strStoreNo +") Order by STORE";

	  ADOQuery1->Active = true;

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
//---------------------------------------------------------------------------


void __fastcall TStoreForm01::Button10Click(TObject *Sender)
{
		MainMenuForm->strQuestion = "Are you sure you want to remove this data and reimport from Vivaldi Classic?  This is a very dangerous thing, it will remove your current data!";

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


	   Label20->Text  = "Importing ... Please Wait";

				   if( CheckBox8->IsChecked )
				  {

					 Label20->Text  = "Importing Customers... Please Wait";



                  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from CUSTOMER where STORE = "+ MainMenuForm->strStoreNo;
				  ADOQuery2->Active = true;

                  if( CheckBox6->IsChecked )
				  {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
								{
												ADOQuery2->Delete();
							   }

                  }

                      ADOQuery2->Active = false;

                  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from CUSTOMER where STORE = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;

                   ADOTable1->Active = false;
				  ADOTable1->TableName = "CUSTOMER.dbf";
				  ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )
				  {



                  Label20->Text = ADOTable1->FieldByName("ACCT")->AsString;

				  try
				  {

                  ADOQuery2->Insert();

                  ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;

                  ADOQuery2->FieldByName("ACCT")->AsString  = ADOTable1->FieldByName("ACCT")->AsString;

                  ADOQuery2->FieldByName("NAME")->AsString  = ADOTable1->FieldByName("NAME")->AsString;



                  ADOQuery2->FieldByName("ROUTE")->AsFloat  = ADOTable1->FieldByName("ROUTE")->AsFloat;

                  ADOQuery2->FieldByName("ADDRESS1")->AsString  = ADOTable1->FieldByName("ADDRESS1")->AsString;

                  ADOQuery2->FieldByName("ADDRESS2")->AsString  = ADOTable1->FieldByName("ADDRESS2")->AsString;

                  ADOQuery2->FieldByName("CITY")->AsString  = ADOTable1->FieldByName("CITY")->AsString;

                  ADOQuery2->FieldByName("STATE")->AsString  = ADOTable1->FieldByName("STATE")->AsString;

                  ADOQuery2->FieldByName("ZIP")->AsString  = ADOTable1->FieldByName("ZIP")->AsString;

                  ADOQuery2->FieldByName("PHONE")->AsString  = ADOTable1->FieldByName("PHONE")->AsString;

                  ADOQuery2->FieldByName("ADDRESS1B")->AsString  = ADOTable1->FieldByName("ADDRESS1B")->AsString;

                  ADOQuery2->FieldByName("ADDRESS2B")->AsString  = ADOTable1->FieldByName("ADDRESS2B")->AsString;

                  ADOQuery2->FieldByName("CITYB")->AsString  = ADOTable1->FieldByName("CITYB")->AsString;

                  ADOQuery2->FieldByName("STATEB")->AsString  = ADOTable1->FieldByName("STATEB")->AsString;

                  ADOQuery2->FieldByName("ZIPB")->AsString  = ADOTable1->FieldByName("ZIPB")->AsString;

                  ADOQuery2->FieldByName("PHONEB")->AsString  = ADOTable1->FieldByName("PHONEB")->AsString;





                   ADOQuery2->FieldByName("CASH")->AsString  = ADOTable1->FieldByName("CASH")->AsString;

                   ADOQuery2->FieldByName("MINIMUM")->AsString  = ADOTable1->FieldByName("MINIMUM")->AsString;

                   ADOQuery2->FieldByName("STOP")->AsString  = ADOTable1->FieldByName("STOP")->AsString;

                   ADOQuery2->FieldByName("LASTTRANS")->AsString  = ADOTable1->FieldByName("LASTTRANS")->AsString;



                   ADOQuery2->FieldByName("LASTTRAN")->AsString  = ADOTable1->FieldByName("LASTTRAN")->AsString;

                   ADOQuery2->FieldByName("DISCOUNT")->AsString  = ADOTable1->FieldByName("DISCOUNT")->AsString;

                   ADOQuery2->FieldByName("ACCOUNT")->AsString  = ADOTable1->FieldByName("ACCOUNT")->AsString;



                   ADOQuery2->FieldByName("COMMENT")->AsString  = ADOTable1->FieldByName("COMMENT")->AsString;

                   ADOQuery2->FieldByName("BACCT")->AsString  = ADOTable1->FieldByName("BACCT")->AsString;

                   ADOQuery2->FieldByName("SPENT")->AsString  = ADOTable1->FieldByName("SPENT")->AsString;

                   ADOQuery2->FieldByName("TICKETS")->AsString  = ADOTable1->FieldByName("TICKETS")->AsString;

                   ADOQuery2->FieldByName("LARGEST")->AsString  = ADOTable1->FieldByName("LARGEST")->AsString;

                   ADOQuery2->FieldByName("CLHOTEL")->AsString  = ADOTable1->FieldByName("CLHOTEL")->AsString;

                   ADOQuery2->FieldByName("DCLASS")->AsString  = ADOTable1->FieldByName("DCLASS")->AsString;



                   ADOQuery2->FieldByName("TAX")->AsString  = ADOTable1->FieldByName("TAX")->AsString;

                   ADOQuery2->FieldByName("AROFF")->AsString  = ADOTable1->FieldByName("AROFF")->AsString;

                   ADOQuery2->FieldByName("DUE")->AsString  = ADOTable1->FieldByName("DUE")->AsString;

                   ADOQuery2->FieldByName("YTDTOTAL")->AsString  = ADOTable1->FieldByName("YTDTOTAL")->AsString;

                   ADOQuery2->FieldByName("YTDTICKETS")->AsString  = ADOTable1->FieldByName("YTDTICKETS")->AsString;

                   ADOQuery2->FieldByName("WHOLESALE")->AsString  = ADOTable1->FieldByName("WHOLESALE")->AsString;

                  // ADOQuery2->FieldByName("VIP")->AsString  = ADOTable1->FieldByName("VIP")->AsString;

                   //ADOQuery2->FieldByName("PRICELEVEL")->AsString  = ADOTable1->FieldByName("PRICELEVEL")->AsString;

                   //ADOQuery2->FieldByName("DEPOSIT")->AsString  = ADOTable1->FieldByName("DEPOSIT")->AsString;



                  ADOQuery2->Post();

                   }
					catch(const Exception& e)
					{
								  // Skip the Record
								  //ShowMessage(ADOTable1->FieldByName("ORDER")->AsString+ " Ticket is being Skipped.  It is corrupt");
					 }

                  ADOTable1->MoveBy(1);



				  }

	   }







                  ADOQuery2->Active = false;

                   if( CheckBox9->IsChecked )
				  {





       Label20->Text  = "Importing Tickets... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from INVOICE where STORE = "+ MainMenuForm->strStoreNo;

				  ADOQuery2->Active = true;



				if( CheckBox6->IsChecked )
				{

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
									 {

                                                ADOQuery2->Delete();

                                }

                  }

                    ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from INVOICE where STORE = "+ MainMenuForm->strStoreNo  +" AND ID = -1";

				  ADOQuery2->Active = true;


				   ADOTable1->Active = false;
				  ADOTable1->TableName = "Invoice.dbf";
				  ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )
					{



							try{




                                ADOQuery2->Insert();

                                ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;

                                ADOQuery2->FieldByName("ACCT")->AsString  = ADOTable1->FieldByName("ACCT")->AsString;

                                ADOQuery2->FieldByName("NAME")->AsString  = ADOTable1->FieldByName("NAME")->AsString;



								ADOQuery2->FieldByName("ORDERNO")->AsString  = ADOTable1->FieldByName("ORDER")->AsString;

                                ADOQuery2->FieldByName("QTY")->AsString  = ADOTable1->FieldByName("QTY")->AsString;

                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                ADOQuery2->FieldByName("STATUS")->AsString  = ADOTable1->FieldByName("STATUS")->AsString;

                                ADOQuery2->FieldByName("DATEIN")->AsString  = ADOTable1->FieldByName("DATEIN")->AsString;

                                ADOQuery2->FieldByName("DATEOUT")->AsString  = ADOTable1->FieldByName("DATEOUT")->AsString;

                                ADOQuery2->FieldByName("LOCATION")->AsString  = ADOTable1->FieldByName("LOCATION")->AsString;

                                ADOQuery2->FieldByName("AMTPAID")->AsString  = ADOTable1->FieldByName("AMTPAID")->AsString;

                                ADOQuery2->FieldByName("ACCOUNT")->AsString  = ADOTable1->FieldByName("ACCOUNT")->AsString;

                                ADOQuery2->FieldByName("GARMARK")->AsString  = ADOTable1->FieldByName("GARMARK")->AsString;

                                ADOQuery2->FieldByName("GARMARK1")->AsString  = ADOTable1->FieldByName("GARMARK1")->AsString;

                                ADOQuery2->FieldByName("TAX")->AsString  = ADOTable1->FieldByName("TAX")->AsString;

                                ADOQuery2->FieldByName("ROUTE")->AsString  = ADOTable1->FieldByName("ROUTE")->AsString;



                                ADOQuery2->FieldByName("USER")->AsString  = ADOTable1->FieldByName("USER")->AsString;

                                ADOQuery2->FieldByName("STOP")->AsString  = ADOTable1->FieldByName("STOP")->AsString;

                                ADOQuery2->FieldByName("BACCT")->AsString  = ADOTable1->FieldByName("BACCT")->AsString;



								ADOQuery2->Post();

							  }
							  catch(const Exception& e)
								{
								  // Skip the Record
								  //ShowMessage(ADOTable1->FieldByName("ORDER")->AsString+ " Ticket is being Skipped.  It is corrupt");
							  }


                         ADOTable1->MoveBy(1);



                  }

				 }
				  if( CheckBox11->IsChecked )
				  {

                  //Importing Detail

                                Label20->Text  = "Importing Ticket Detail... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from ORDERS where STORE = "+ MainMenuForm->strStoreNo;

				  ADOQuery2->Active = true;



                  if( CheckBox6->IsChecked )
					   {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
								{

												ADOQuery2->Delete();



                                }

                  }
                   				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from ORDERS where STORE = "+ MainMenuForm->strStoreNo  +" AND ID = -1";

				  ADOQuery2->Active = true;


                    ADOTable1->Active = false;
                  ADOTable1->TableName = "ORDERS.dbf";



                  ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )
					{



                                Label20->Text = ADOTable1->FieldByName("ACCT")->AsString;

								try
								{

                                ADOQuery2->Insert();

                                ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;

                                ADOQuery2->FieldByName("ACCT")->AsString  = ADOTable1->FieldByName("ACCT")->AsString;

                                ADOQuery2->FieldByName("ITEMDESC")->AsString  = ADOTable1->FieldByName("ITEMDESC")->AsString;



                                ADOQuery2->FieldByName("ORDERNO")->AsString  = ADOTable1->FieldByName("ORDER")->AsString;

                                ADOQuery2->FieldByName("QTY")->AsString  = ADOTable1->FieldByName("QTY")->AsString;

                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                ADOQuery2->FieldByName("STATUS")->AsString  = ADOTable1->FieldByName("STATUS")->AsString;

                                ADOQuery2->FieldByName("DATEIN")->AsString  = ADOTable1->FieldByName("DATEIN")->AsString;

                                ADOQuery2->FieldByName("DATEOUT")->AsString  = ADOTable1->FieldByName("DATEOUT")->AsString;

                                ADOQuery2->FieldByName("UPCHARGE")->AsString  = ADOTable1->FieldByName("UPCHARGE")->AsString;

                                ADOQuery2->FieldByName("ITEM")->AsString  = ADOTable1->FieldByName("ITEM")->AsString;

                                ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;

                                ADOQuery2->FieldByName("VALLINE")->AsString  = ADOTable1->FieldByName("VALLINE")->AsString;

                                ADOQuery2->FieldByName("DISCOUNT")->AsString  = ADOTable1->FieldByName("DISCOUNT")->AsString;

								if( ADOTable1->FieldByName("STATUS")->AsString == "T" )
								{

												ADOQuery2->FieldByName("TAX")->AsString = "0";

												ADOQuery2->FieldByName("TAXABLE")->AsBoolean  = true;

                                }
								  else
								{

												ADOQuery2->FieldByName("TAXABLE")->AsBoolean = false;

												ADOQuery2->FieldByName("TAX")->AsString  = "0" ;



								}



                                ADOQuery2->FieldByName("PRIMEKEY")->AsString  = ADOTable1->FieldByName("PRIMEKEY")->AsString;

                                ADOQuery2->Post();

                                 }
							  catch(const Exception& e)
								{
								  // Skip the Record
								  //ShowMessage(ADOTable1->FieldByName("ORDER")->AsString+ " Ticket is being Skipped.  It is corrupt");
							  }

                                ADOTable1->MoveBy(1);



                  }

				   }
				  if( CheckBox13->IsChecked )
				  {

                                //importing the dcitems



                  Label20->Text  = "Importing Items/Prices... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from DCITEM where STORENO = "+ MainMenuForm->strStoreNo ;

				  ADOQuery2->Active = true;



                  if( CheckBox6->IsChecked )
				   {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
								  {

												ADOQuery2->Delete();


                                }

                  }



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from DCITEM where STORENO = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;


					ADOTable1->Active = false;
                  ADOTable1->TableName = "DCITEM.dbf";
				  ADOTable1->Active = true;

				  ADOTable1->First();



                  while( ADOTable1->Eof == false )
				   {



				  if( ADOTable1->FieldByName("UPCHRG1")->AsString == "" )
					{

								Label20->Text = ADOTable1->FieldByName("DESC")->AsString;



                                ADOQuery2->Insert();

                                ADOQuery2->FieldByName("STORENO")->AsString  = MainMenuForm->strStoreNo ;

                                ADOQuery2->FieldByName("CODE")->AsString  = ADOTable1->FieldByName("ITEM")->AsString;

                                ADOQuery2->FieldByName("ITEM")->AsString  = ADOTable1->FieldByName("DESC")->AsString;



                                ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;

                                ADOQuery2->FieldByName("PIECES")->AsString  = ADOTable1->FieldByName("ITEMS")->AsString;

                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                ADOQuery2->FieldByName("TAX")->AsBoolean  = true;

                                ADOQuery2->FieldByName("STOCKNUMBER")->AsString  = ADOTable1->FieldByName("ITEMCODE")->AsString;

								if( ADOTable1->FieldByName("ITEM")->AsString == "#" )
								 {

                                                ADOQuery2->FieldByName("POPUPQTY")->AsBoolean = true;

                                                ADOQuery2->FieldByName("POPUPLABEL")->AsString  = "LBS";

                                }
								 else
								  {

                                                ADOQuery2->FieldByName("POPUPQTY")->AsBoolean = false;

												ADOQuery2->FieldByName("POPUPLABEL")->AsString  = "";



                                }

								ADOQuery2->Post();

						}





                                ADOTable1->MoveBy(1);



                  }



                                //importing the dcitems



                  Label20->Text  = "Importing SUBITEMS... Please Wait";



				  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from SUBDCITEM where STORENO = "+ MainMenuForm->strStoreNo ;
				  ADOQuery2->Active = true;



                  if( CheckBox6->IsChecked )
				  {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
								{

												ADOQuery2->Delete();


                                }

                  }

                 				  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from SUBDCITEM where STORENO = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";
				  ADOQuery2->Active = true;

					ADOTable1->Active = false;
                  ADOTable1->TableName = "DCITEM.dbf";
			   ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )
				  {



                  if( ADOTable1->FieldByName("UPCHRG1")->AsString != "" )
				  {

                                Label20->Text = ADOTable1->FieldByName("DESC")->AsString;



                                ADOQuery2->Insert();

                                ADOQuery2->FieldByName("STORENO")->AsString  = MainMenuForm->strStoreNo ;

                                ADOQuery2->FieldByName("ITEMCODE")->AsString  = ADOTable1->FieldByName("ITEM")->AsString;

                                ADOQuery2->FieldByName("CODE")->AsString  = ADOTable1->FieldByName("UPCHRG2")->AsString;



                                ADOQuery2->FieldByName("ITEM")->AsString  = ADOTable1->FieldByName("DESC")->AsString;



                                ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;

                                ADOQuery2->FieldByName("PIECES")->AsString  = ADOTable1->FieldByName("ITEMS")->AsString;

                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                ADOQuery2->FieldByName("TAX")->AsBoolean  = true;

                                ADOQuery2->FieldByName("STOCKNUMBER")->AsString  = ADOTable1->FieldByName("ITEMCODE")->AsString;

                                if( ADOTable1->FieldByName("UPCHRG2")->AsString == "#" )
								  {

                                                ADOQuery2->FieldByName("POPUPQTY")->AsBoolean = true;

                                                ADOQuery2->FieldByName("POPUPLABEL")->AsString  = "LBS";

                                }
								 else
								{

                                                ADOQuery2->FieldByName("POPUPQTY")->AsBoolean = false;

												ADOQuery2->FieldByName("POPUPLABEL")->AsString  = "";



                                }

								ADOQuery2->Post();

						  }





                                ADOTable1->MoveBy(1);



                  }

				   }
				  if( CheckBox10->IsChecked )
				  {

                  //importing the ar



                  Label20->Text  = "Importing UPCHARGE... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from UPCHARGE where STORENO = "+ MainMenuForm->strStoreNo;

				  ADOQuery2->Active = true;



                  if( CheckBox6->IsChecked )
				  {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )
								 {

												ADOQuery2->Delete();


                                }

                  }
                 				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from UPCHARGE where STORENO = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;


					ADOTable1->Active = false;
                  ADOTable1->TableName = "UPCHARGE.dbf";



                  ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )
				   {





                                                                Label20->Text = ADOTable1->FieldByName("DESC")->AsString;



                                                                ADOQuery2->Insert();

                                                                ADOQuery2->FieldByName("STORENO")->AsString  = MainMenuForm->strStoreNo ;

                                                                ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("UPCLASS")->AsString;

                                                                ADOQuery2->FieldByName("ITEMCODE")->AsString  = ADOTable1->FieldByName("UPITEM")->AsString;

                                                                ADOQuery2->FieldByName("CODE")->AsString  = ADOTable1->FieldByName("UPCHARGE")->AsString;

                                                ADOQuery2->FieldByName("ITEM")->AsString  = ADOTable1->FieldByName("DESC")->AsString;

                                                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                                                ADOQuery2->FieldByName("TAX")->AsBoolean  = true;





                                ADOQuery2->Post();



                                ADOTable1->MoveBy(1);



                  }

                    }
				  if( CheckBox12->IsChecked )
				  {

                   // IMPORT AR

                                  Label20->Text  = "Importing AR... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from AR where STORENO = "+ MainMenuForm->strStoreNo;

				  ADOQuery2->Active = true;



                  if( CheckBox6->IsChecked )

                  {

                                ADOQuery2->First();

                                while( ADOQuery2->Eof == false )

                                {

												ADOQuery2->Delete();



                                }

                  }

                 				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from AR where STORENO = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;

					ADOTable1->Active = false;
                  ADOTable1->TableName = "AR.dbf";
				  ADOTable1->Active = true;

                  ADOTable1->First();



                  while( ADOTable1->Eof == false )

				  {



					if( ADOTable1->FieldByName("AR")->AsBoolean == true)
                     {



                                                                                Label20->Text = ADOTable1->FieldByName("ACCT")->AsString;



                                                                                ADOQuery2->Insert();

                                                                                ADOQuery2->FieldByName("STORENO")->AsString  = MainMenuForm->strStoreNo ;

                                                                                ADOQuery2->FieldByName("ACCT")->AsString  = ADOTable1->FieldByName("ACCT")->AsString;

                                                                                ADOQuery2->FieldByName("NAME")->AsString  = ADOTable1->FieldByName("ACCT")->AsString;

                                                                                ADOQuery2->FieldByName("ROUTE")->AsString  = ADOTable1->FieldByName("ROUTE")->AsString;

                                                                                ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;

                                                                                ADOQuery2->FieldByName("ORDERNO")->AsString  = ADOTable1->FieldByName("ORDER")->AsString;

                                                                                ADOQuery2->FieldByName("DATEOUT")->AsString  = ADOTable1->FieldByName("DATEOUT")->AsString;

                                                                                ADOQuery2->FieldByName("AMT")->AsString  = ADOTable1->FieldByName("AMT")->AsString;

                                                                                ADOQuery2->FieldByName("DUE")->AsString  = ADOTable1->FieldByName("DUE")->AsString;

                                                                                ADOQuery2->FieldByName("AMTPAID")->AsString  = ADOTable1->FieldByName("CREDITS")->AsString;



                                                                                ADOQuery2->FieldByName("SLAVE")->AsString  = ADOTable1->FieldByName("SLAVE")->AsString;

                                                                                ADOQuery2->FieldByName("REFERENCE")->AsString  = ADOTable1->FieldByName("REFERENCE")->AsString;

                                                                                ADOQuery2->FieldByName("USER")->AsString  = ADOTable1->FieldByName("USER")->AsString;

                                                                                ADOQuery2->FieldByName("TIMEOUT")->AsString  = ADOTable1->FieldByName("TIMEOUT")->AsString;



                                                                                if(            ADOTable1->FieldByName("CASH")->AsBoolean )
																								ADOQuery2->FieldByName("PAYMENTTYPE")->AsString  = "CASH";
																				if(            ADOTable1->FieldByName("CHECK")->AsBoolean )
																							   ADOQuery2->FieldByName("PAYMENTTYPE")->AsString  = "CHECK";
																				if(            ADOTable1->FieldByName("CARD")->AsBoolean )
																								 ADOQuery2->FieldByName("PAYMENTTYPE")->AsString  = "CARD";



							if( ADOTable1->FieldByName("DUE")->AsFloat - ADOTable1->FieldByName("CREDITS")->AsFloat == 0 )
										 ADOQuery2->FieldByName("STATUS")->AsString  = "CLOSED";
							 else
								 ADOQuery2->FieldByName("STATUS")->AsString  = "OPEN";


							   ADOQuery2->Post();

					  }
                                ADOTable1->MoveBy(1);



				  }


				  Label20->Text  = "Importing CLASS... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from CLASS where STORE = "+ MainMenuForm->strStoreNo ;

				  ADOQuery2->Active = true;



				  if( CheckBox6->IsChecked )
				  {

								ADOQuery2->First();

								while( ADOQuery2->Eof == false )

								{

												ADOQuery2->Delete();


								}

				  }
									  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from CLASS where STORE = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;


				   ADOTable1->Active = false;
				  ADOTable1->TableName = "CLASS.dbf";



				  ADOTable1->Active = true;

				  ADOTable1->First();



				  while( ADOTable1->Eof == false )
				  {


						Label20->Text = ADOTable1->FieldByName("CODE")->AsString;

						ADOQuery2->Insert();
						ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;
						ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;
						ADOQuery2->FieldByName("CODE")->AsString  = ADOTable1->FieldByName("CODE")->AsString;
						ADOQuery2->FieldByName("TAX")->AsString  = ADOTable1->FieldByName("TAX")->AsString;
						ADOQuery2->FieldByName("MAXITEM")->AsString  = ADOTable1->FieldByName("MAXITEM")->AsString;

						ADOQuery2->Post();

						ADOTable1->MoveBy(1);

				  }

				   }
                    if( CheckBox17->IsChecked )
				   {
                    Label20->Text  = "Importing CLASS... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from CLASS where STORE = "+ MainMenuForm->strStoreNo  +"";

				  ADOQuery2->Active = true;



				  if( CheckBox6->IsChecked )
				  {

								ADOQuery2->First();

								while( ADOQuery2->Eof == false )

								{

												ADOQuery2->Delete();


								}

				  }
									  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from CLASS where STORE = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;


				   ADOTable1->Active = false;
				  ADOTable1->TableName = "CLASS.dbf";



				  ADOTable1->Active = true;

				  ADOTable1->First();



				  while( ADOTable1->Eof == false )
				  {


						Label20->Text = ADOTable1->FieldByName("CODE")->AsString;

						ADOQuery2->Insert();
						ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;
						ADOQuery2->FieldByName("CLASS")->AsString  = ADOTable1->FieldByName("CLASS")->AsString;
						ADOQuery2->FieldByName("CODE")->AsString  = ADOTable1->FieldByName("CODE")->AsString;
						ADOQuery2->FieldByName("TAX")->AsString  = ADOTable1->FieldByName("TAX")->AsString;
						ADOQuery2->FieldByName("MAXITEM")->AsString  = ADOTable1->FieldByName("MAXITEM")->AsString;

						ADOQuery2->Post();

						ADOTable1->MoveBy(1);

				  }
				  }

				   if( CheckBox14->IsChecked )
				   {
				   Label20->Text  = "Importing COUPONS... Please Wait";



				  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from COUPON where STORENO = "+ MainMenuForm->strStoreNo  +"";

				  ADOQuery2->Active = true;



				  if( CheckBox6->IsChecked )
				  {

								ADOQuery2->First();

								while( ADOQuery2->Eof == false )

								{

												ADOQuery2->Delete();


								}

				  }
									  ADOQuery2->Active = false;

				  ADOQuery2->SQL->Clear();

				  ADOQuery2->SQL->Text = "Select * from COUPON where STORENO = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";

				  ADOQuery2->Active = true;


				   ADOTable1->Active = false;
				  ADOTable1->TableName = "COUPON.dbf";



				  ADOTable1->Active = true;

				  ADOTable1->First();



				  while( ADOTable1->Eof == false )
				  {


					
						ADOQuery2->Insert();
						ADOQuery2->FieldByName("STORENO")->AsString  = MainMenuForm->strStoreNo ;
						ADOQuery2->FieldByName("COUPON")->AsString  = ADOTable1->FieldByName("COUPON")->AsString;
						ADOQuery2->FieldByName("COUPONPERCENT")->AsString  = ADOTable1->FieldByName("COUPER")->AsString;
						ADOQuery2->FieldByName("COUPONAMT")->AsString  = ADOTable1->FieldByName("COUAMT")->AsString;
						ADOQuery2->FieldByName("MAX")->AsString  = ADOTable1->FieldByName("COUMAX")->AsString;
						ADOQuery2->FieldByName("CCLASS")->AsString  = ADOTable1->FieldByName("CCLASS")->AsString;

						ADOQuery2->Post();

						ADOTable1->MoveBy(1);

				  }

		}

				  ADOQuery2->Active = false;
				ADOTable1->Active = false;


				  ShowMessage("Import Complete");

}
//---------------------------------------------------------------------------



void __fastcall TStoreForm01::CheckBox19Click(TObject *Sender)
{
if( CheckBox19->IsChecked == false )
  {

		MainMenuForm->strQuestion = "Would you like Vivaldi 8 to create a CashDrawer.bat File for you?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{

		FILE *stream;
		stream = fopen("C:\\VIVALDI8\\CashDrawer.bat", "w+");

		AnsiString  s = "Type c:\Vivaldi8\Open.txt > \\localhost\Ticket";

		fprintf(stream , "%s", s);

		fclose(stream);
	 }
  }
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button25Click(TObject *Sender)
{
	SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";
		

		   AnsiString strParam =  "-install "+  MainMenuForm->strSMTPServer  +"   "+  MainMenuForm->strSenderEmail + "  "+ MainMenuForm->strEmailPort;

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
   ShowMessage("Email Initialized: "+strParam);

}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button26Click(TObject *Sender)
{

	SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";

		   ShowMessage("Test Email will be sent to "+ MainMenuForm->strSenderEmail );

		  AnsiString pw =  "-to "+ MainMenuForm->strSenderEmail +"  -body \" "+"Test Email: "+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Test Email from POS Metro   \" ";

 int iSize = pw.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   pw.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_MINIMIZE;



    		if(! ShellExecuteEx(&execinfo))
    		{
     			ShowMessage("Could Not Run. Check that BLAT.EXE is located in c:\\VIVALDI\\REPORTS directory!");
        		return;
			}
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button27Click(TObject *Sender)
{
	WinExec("NotePad c:\\vivaldi8\\prttag.bat", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button28Click(TObject *Sender)
{
	 TIniFile& tfile = *new TIniFile("C:\\VIVALDI8\\VIVALDI8.INI");

	 tfile.WriteString("TICKETS","TICKETPRINTER",Edit32->Text);

	 tfile.WriteString("TICKETS","TAGPRINTER",Edit33->Text);

	 tfile.WriteString("TICKETS","RECEIPTPRINTER",Edit52->Text);



}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button29Click(TObject *Sender)
{

  ShowMessage("Add this to the file:  (Change localhost) Type CCRECEIPT.TXT > \\localhost\TICKET Type CCRECEIPTM.TXT > \\localhost\TICKET");
  WinExec("NotePad c:\\vivaldi8\\prttag.bat", SW_NORMAL);


}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button30Click(TObject *Sender)
{
	MainMenuForm->strQuestion = "Are you sure you want to remove this data and reimport from Access / POSCal?  This is a very dangerous thing, it will remove your current data!";

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


	if( CheckBox47->IsChecked == false )
	{

	   Label20->Text  = "Importing ... Please Wait";

				   if( CheckBox8->IsChecked )
				  {

				   Label20->Text  = "Importing Customers... Please Wait";
				   if( CheckBox6->IsChecked )
				  {
						  ADOQuery2->Active = false;

						  ADOQuery2->SQL->Clear();

						  ADOQuery2->SQL->Text = "Select * from CUSTOMER where STORE = "+ MainMenuForm->strStoreNo  +"";

						  ADOQuery2->Active = true;



								ADOQuery2->First();

								while( ADOQuery2->Eof == false )
								{
												ADOQuery2->Delete();
							   }

				  }

				  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from CUSTOMER where STORE = "+ MainMenuForm->strStoreNo  +"  AND ID = -1";
				  ADOQuery2->Active = true;

				  ADOTable2->Active = false;
				   ADOTable2->SQL->Clear();

				  ADOTable2->SQL->Text = "SELECT * FROM CUST ORDER BY PHONE";

				  ADOTable2->Active = true;

				  ADOTable2->First();



				  while( ADOTable2->Eof == false )
				  {

					AnsiString strAcct = ADOTable2->FieldByName("PHONE")->AsString;

					if ( strAcct.Trim() == "" ) {
						strAcct = ADOTable2->FieldByName("CUSTNO")->AsString;
					}
					else
					{
					   strAcct = ADOTable2->FieldByName("PHONE")->AsString;
					   strAcct = strAcct.SubString(2,3)+"-"+  strAcct.SubString(6,8);
					}

				  Label20->Text = strAcct;



                  ADOQuery2->Insert();
				  ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;
				  ADOQuery2->FieldByName("CUSTNO")->AsString  =  ADOTable2->FieldByName("CUSTNO")->AsString;
				  ADOQuery2->FieldByName("ACCT")->AsString  = strAcct;
				  ADOQuery2->FieldByName("NAME")->AsString  = ADOTable2->FieldByName("LNAME")->AsString.Trim()+ ", "+ADOTable2->FieldByName("FNAME")->AsString.Trim();

				   ADOQuery2->FieldByName("STARCH")->AsString  = ADOTable2->FieldByName("STARCH")->AsString.Trim();


				  ADOQuery2->FieldByName("ROUTE")->AsFloat  = 0;

				  ADOQuery2->FieldByName("ADDRESS1")->AsString  = ADOTable2->FieldByName("ADDRESS")->AsString.Trim();

				  //ADOQuery2->FieldByName("ADDRESS2")->AsString  = ADOTable1->FieldByName("ADDRESS2")->AsString;

				  ADOQuery2->FieldByName("CITY")->AsString  = ADOTable2->FieldByName("CITY")->AsString.Trim();

				  ADOQuery2->FieldByName("STATE")->AsString  = ADOTable2->FieldByName("ST")->AsString.Trim();

				  ADOQuery2->FieldByName("ZIP")->AsString  = ADOTable2->FieldByName("ZIP")->AsString.Trim();

				  ADOQuery2->FieldByName("PHONE")->AsString  = ADOTable2->FieldByName("PHONE")->AsString.Trim();

					 ADOQuery2->FieldByName("BDATE")->AsString  = ADOTable2->FieldByName("BIRTH")->AsString.Trim();



				   ADOQuery2->FieldByName("LASTTRANS")->AsString  = ADOTable2->FieldByName("LSDATE")->AsString.Trim();



				   ADOQuery2->FieldByName("LASTTRAN")->AsString  = ADOTable2->FieldByName("LSDATE")->AsString.Trim();




				  ADOQuery2->Post();





				  ADOTable2->MoveBy(1);



				  }
				 }
                     ADOQuery2->Active = false;

                   if( CheckBox9->IsChecked )
				  {

				 Label20->Text  = "Importing Tickets... Please Wait";
				if( CheckBox6->IsChecked )
				{
				  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from INVOICE where STORE = "+ MainMenuForm->strStoreNo  +"";

				  ADOQuery2->Active = true;

				   ADOQuery2->First();

					   while( ADOQuery2->Eof == false )
					   {

							ADOQuery2->Delete();

					   }

                  }

				  ADOQuery2->Active = false;
				  ADOQuery2->SQL->Clear();
				  ADOQuery2->SQL->Text = "Select * from INVOICE where STORE = "+ MainMenuForm->strStoreNo  +" AND ID = -1";
				  ADOQuery2->Active = true;


				  ADOTable2->Active = false;
				  ADOTable2->SQL->Clear();
				  ADOTable2->SQL->Text = "SELECT * FROM RECEIPT ORDER BY CUSTNO";
				  ADOTable2->Active = true;

				  ADOTable2->First();
				  AnsiString strPhone = "";

				  while( ADOTable2->Eof == false )
					{
							ADOQuery3->Active = false;
							ADOQuery3->SQL->Clear();
							ADOQuery3->SQL->Text = "Select * from CUSTOMER where STORE = "+ MainMenuForm->strStoreNo  +"  AND CUSTNO = '"+ADOTable2->FieldByName("CUSTNO")->AsString.Trim()  +"'";

							ADOQuery3->Active = true;


							if(  ADOQuery3->Eof == false )
							{
								strPhone  = ADOQuery3->FieldByName("ACCT")->AsString;


                                ADOQuery2->Insert();

								ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;

								ADOQuery2->FieldByName("ACCT")->AsString  = strPhone;

								ADOQuery2->FieldByName("NAME")->AsString  = ADOQuery3->FieldByName("NAME")->AsString;

								ADOQuery2->FieldByName("ORDERNO")->AsString  = ADOTable2->FieldByName("RCTNO")->AsString;

								ADOQuery2->FieldByName("QTY")->AsString  = ADOTable2->FieldByName("QTY")->AsString;

								ADOQuery2->FieldByName("AMT")->AsString  = ADOTable2->FieldByName("PRICE")->AsString;

								if(   ADOTable2->FieldByName("OUTDATE")->AsString.Trim() == "" )
								{
									ADOQuery2->FieldByName("STATUS")->AsString  = "I";
									ADOQuery2->FieldByName("AMTPAID")->AsString  = ADOTable2->FieldByName("PREPAY")->AsString;
								}
								else
								{
									ADOQuery2->FieldByName("STATUS")->AsString  = "P";
									ADOQuery2->FieldByName("AMTPAID")->AsString  = ADOTable2->FieldByName("OUTPAY")->AsString;
								}

								ADOQuery2->FieldByName("DATEIN")->AsString  =  ADOTable2->FieldByName("INDATE")->AsString.Trim();

								ADOQuery2->FieldByName("DATEOUT")->AsString  =  ADOTable2->FieldByName("OUTDATE")->AsString.Trim();

								ADOQuery2->FieldByName("LOCATION")->AsString  = ADOTable2->FieldByName("RACK")->AsString;




								ADOQuery2->Post();

							  }
							  


						 ADOTable2->MoveBy(1);



                  }

				 }

				 ADOQuery2->Active = false;
				 ADOTable2->Active = false;
				 ADOQuery3->Active = false;
		   }
		   else
		   {

                   Label20->Text  = "Importing ... Please Wait";
                   	AnsiString strAcct;
				   if( CheckBox8->IsChecked )
				  {

					  ADOTable1->Active = false;
					  ADOTable1->TableName = "CUSTOMER.dbf";
					  ADOTable1->Active = true;


					   Label20->Text  = "Importing Customers... Please Wait";
					   if( CheckBox6->IsChecked )
					   {

							  ADOTable1->First();

							  while( ADOTable1->Eof == false )
							  {
									ADOTable1->Delete();
							  }

					   }



				  ADOTable2->Active = false;
				   ADOTable2->SQL->Clear();
				  ADOTable2->SQL->Text = "SELECT * FROM CUSTOMER ORDER BY PHONE";
				  ADOTable2->Active = true;

				  ADOTable2->First();



				  while( ADOTable2->Eof == false )
				  {

					 strAcct = ADOTable2->FieldByName("PHONE")->AsString;

					if ( strAcct.Trim() == "" ) {
						strAcct = ADOTable2->FieldByName("CUSTNO")->AsString;
					}
					else
					{
					   strAcct = ADOTable2->FieldByName("PHONE")->AsString;
					   strAcct = strAcct.SubString(2,3)+"-"+  strAcct.SubString(6,8);
					}

				  Label20->Text = strAcct;



				  ADOTable1->Insert();
				  //ADOQuery2->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;
				  //ADOQuery2->FieldByName("CUSTNO")->AsString  =  ADOTable2->FieldByName("CUSTNO")->AsString;
				  ADOTable1->FieldByName("ACCT")->AsString  = strAcct;
				  ADOTable1->FieldByName("NAME")->AsString  = ADOTable2->FieldByName("LNAME")->AsString.Trim()+ ", "+ADOTable2->FieldByName("FNAME")->AsString.Trim();

				  // ADOQuery2->FieldByName("STARCH")->AsString  = ADOTable2->FieldByName("STARCH")->AsString.Trim();


				  //ADOQuery2->FieldByName("ROUTE")->AsFloat  = 0;

				  ADOTable1->FieldByName("ADDRESS1")->AsString  = ADOTable2->FieldByName("ADDRESS")->AsString.Trim();

				  //ADOQuery2->FieldByName("ADDRESS2")->AsString  = ADOTable1->FieldByName("ADDRESS2")->AsString;

				  ADOTable1->FieldByName("CITY")->AsString  = ADOTable2->FieldByName("CITY")->AsString.Trim();

				  ADOTable1->FieldByName("STATE")->AsString  = ADOTable2->FieldByName("ST")->AsString.Trim();

				  ADOTable1->FieldByName("ZIP")->AsString  = ADOTable2->FieldByName("ZIP")->AsString.Trim();

				  ADOTable1->FieldByName("PHONE")->AsString  = ADOTable2->FieldByName("PHONE")->AsString.Trim();

					 ADOTable1->FieldByName("BDATE")->AsString  = ADOTable2->FieldByName("BIRTH")->AsString.Trim();



				   //ADOTable1->FieldByName("LASTTRANS")->AsString  = ADOTable2->FieldByName("LSDATE")->AsString.Trim();



				   //ADOTable1->FieldByName("LASTTRAN")->AsString  = ADOTable2->FieldByName("LSDATE")->AsString.Trim();




				  ADOTable1->Post();





				  ADOTable2->MoveBy(1);



				  }
				 }
                     ADOQuery2->Active = false;

                   if( CheckBox9->IsChecked )
				  {

				 Label20->Text  = "Importing Tickets... Please Wait";
                   	if( CheckBox6->IsChecked )
				{
				  ADOTable1->Active = false;
				  ADOTable1->TableName = "INVOICE.dbf";
				  ADOTable1->Active = true;



								ADOTable1->First();

								while( ADOTable1->Eof == false )
									 {

												ADOTable1->Delete();

                                }

                  }




				  ADOTable2->Active = false;
				  ADOTable2->SQL->Clear();
				  ADOTable2->SQL->Text = "SELECT * FROM RECEIPT WHERE OUTDATE IS NULL OR YEAR(OUTDATE) = 2014 ORDER BY OUTDATE DESC";
				  ADOTable2->Active = true;

				  ADOTable2->First();
				  AnsiString strPhone = "";

				  ADOTable1->Active = false;
				  ADOTable1->TableName = "INVOICE.dbf";
				  ADOTable1->Active = true;


				  while( ADOTable2->Eof == false )
					{
							ADOQuery4->Active = false;
							ADOQuery4->SQL->Clear();
							ADOQuery4->SQL->Text = "Select CUSTNO,PHONE,TRIM(LNAME)+', '+TRIM(FNAME) AS NAME from CUSTOMER where CUSTNO = '"+ADOTable2->FieldByName("CUSTNO")->AsString.Trim()  +"'";

							ADOQuery4->Active = true;


							if(  ADOQuery4->Eof == false )
							{

								strAcct = ADOQuery4->FieldByName("PHONE")->AsString;

								if ( strAcct.Trim() == "" ) {
									strAcct = ADOQuery4->FieldByName("CUSTNO")->AsString;
								}
								else
								{
								   strAcct = ADOQuery4->FieldByName("PHONE")->AsString;
								   strAcct = strAcct.SubString(2,3)+"-"+  strAcct.SubString(6,8);
								}
								 strPhone = strAcct;

								ADOTable1->Insert();

								//ADOTable1->FieldByName("STORE")->AsString  = MainMenuForm->strStoreNo ;

								ADOTable1->FieldByName("ACCT")->AsString  = strPhone;

								ADOTable1->FieldByName("NAME")->AsString  = ADOQuery4->FieldByName("NAME")->AsString;

								ADOTable1->FieldByName("ORDER")->AsString  = ADOTable2->FieldByName("RCTNO")->AsString;

								ADOTable1->FieldByName("QTY")->AsString  = ADOTable2->FieldByName("QTY")->AsString;

								ADOTable1->FieldByName("AMT")->AsString  = ADOTable2->FieldByName("PRICE")->AsString;

								if(   ADOTable2->FieldByName("OUTDATE")->AsString.Trim() == "" )
								{
									ADOTable1->FieldByName("STATUS")->AsString  = "I";
									ADOTable1->FieldByName("AMTPAID")->AsString  = ADOTable2->FieldByName("PREPAY")->AsString;
								}
								else
								{
									ADOTable1->FieldByName("STATUS")->AsString  = "P";
									ADOTable1->FieldByName("AMTPAID")->AsString  = ADOTable2->FieldByName("OUTPAY")->AsString;
								}

								ADOTable1->FieldByName("DATEIN")->AsString  =  ADOTable2->FieldByName("INDATE")->AsString.SubString(1,10);

								ADOTable1->FieldByName("DATEOUT")->AsString  =  ADOTable2->FieldByName("OUTDATE")->AsString.SubString(1,10);

								ADOTable1->FieldByName("LOCATION")->AsString  = ADOTable2->FieldByName("RACK")->AsString;


								ADOTable1->Post();

							  }



						 ADOTable2->MoveBy(1);



                  }

				 }

				 ADOQuery2->Active = false;
				 ADOTable2->Active = false;
				 ADOQuery3->Active = false;
				 ADOTable1->Active = false;

		   }
				 ShowMessage("Import Complete");



}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::Button31Click(TObject *Sender)
{

if( ADOQuery1->FieldByName("BILLINGAMOUNT")->AsFloat == 9.95  )
{

  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.PointOfSaleCloud.com/995Payment.html";
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
						ShowMessage("Could Not connect to the Vivaldi Web site!");
						return;
				   }
}
else
{
                   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.PointOfSaleCloud.com/1995Payment.html";
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
						ShowMessage("Could Not connect to the Vivaldi Web site!");
						return;
				   }



}
}
//---------------------------------------------------------------------------


void __fastcall TStoreForm01::SpeedButton5Click(TObject *Sender)
{
	TabControl1->TabIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::SpeedButton6Click(TObject *Sender)
{
	TabControl1->TabIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TStoreForm01::SpeedButton4Click(TObject *Sender)
{

ADOQuery1->Active = false;
  this->Close();
}
//---------------------------------------------------------------------------

