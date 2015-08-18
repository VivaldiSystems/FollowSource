//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "LoginForm.h"
#include "MainMenu.h"
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
TLoginForm01 *LoginForm01;
//---------------------------------------------------------------------------
__fastcall TLoginForm01::TLoginForm01(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm01::Button1Click(TObject *Sender)
{


	strStoreCode  = Edit3->Text;
    MainMenuForm->strSlave = "1";
	MainMenuForm->blnEnableTopMenu  = false;

	ADOQuery1->Active = false;
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("Select * from users where email = '"+Edit1->Text  +"' and password = '"+ Edit2->Text  +"'");
	ADOQuery1->Active = true;

	if( ADOQuery1->Eof )
	{

	   ShowMessage("Incorrect User Id and Password!");
	   Edit2->Text = "";
	   Edit2->SetFocus();
		ADOQuery1->Active = false;
	}
	else
	{
		 ModalResult = mrOk;
		 MainMenuForm->strStoreNo = ADOQuery1->FieldByName("Store")->AsString;
		 MainMenuForm->strUserName = ADOQuery1->FieldByName("Name")->AsString;
		 MainMenuForm->strUserID = ADOQuery1->FieldByName("UserID")->AsString;
		 MainMenuForm->strUserEmail = ADOQuery1->FieldByName("Email")->AsString;
		 MainMenuForm->strAccessLevel = ADOQuery1->FieldByName("AccessLevel")->AsString;

		 MainMenuForm->blnEnableTopMenu = ADOQuery1->FieldByName("ENABLEMENU")->AsBoolean;
		  MainMenuForm->blnEnableEnterprise = ADOQuery1->FieldByName("ENABLEENTERPRISE")->AsBoolean;
		  MainMenuForm->blnAllowEditAccess = ADOQuery1->FieldByName("ENABLEEDIT")->AsBoolean;
		  MainMenuForm->blnAllowCustomerAccess = ADOQuery1->FieldByName("ENABLECUSTOMER")->AsBoolean;
		  MainMenuForm->blnAllowWriteAccess = ADOQuery1->FieldByName("ENABLEWRITE")->AsBoolean;
		  MainMenuForm->blnAllowPickupAccess = ADOQuery1->FieldByName("ENABLEPICKUP")->AsBoolean;
		  MainMenuForm->blnAllowXChargeAccess = ADOQuery1->FieldByName("ENABLEXCHARGE")->AsBoolean;
		  MainMenuForm->blnAllowTimeCardAccess = ADOQuery1->FieldByName("ENABLETIMECARD")->AsBoolean;
		  MainMenuForm->blnAllowInventoryAccess = ADOQuery1->FieldByName("ENABLEINVENTORY")->AsBoolean;
		  MainMenuForm->blnAllowAccountAccess = ADOQuery1->FieldByName("ENABLEACCOUNT")->AsBoolean;
		  MainMenuForm->blnAllowCashDrawerAccess = ADOQuery1->FieldByName("ENABLECASHDRAWER")->AsBoolean;
		  MainMenuForm->blnAllowPriceListAccess = ADOQuery1->FieldByName("ENABLEPRICELIST")->AsBoolean;
		  MainMenuForm->blnAllowAssignLocationAccess = ADOQuery1->FieldByName("ENABLEMARKREADY")->AsBoolean;
		  //MainMenuForm->blnAllowMarkReadyAccess = ADOQuery1->FieldByName("ENABLEMARKREADY")->AsBoolean; //NOT USED


		  MainMenuForm->blnAllowRouteAccess = ADOQuery1->FieldByName("ENABLEROUTE")->AsBoolean;
		  MainMenuForm->blnAllowDeliveryAccess = ADOQuery1->FieldByName("ENABLEDELIVERY")->AsBoolean;
		  MainMenuForm->blnAllowHotelAccess = ADOQuery1->FieldByName("ENABLEHOTEL")->AsBoolean;
		  MainMenuForm->blnAllowStoreAccess = ADOQuery1->FieldByName("ENABLESTORE")->AsBoolean;


		 //MainMenuForm->strStoreNo =  ADOQuery1->FieldByName("Store")->AsString;

		ADOQuery1->Active = false;
						ADOQuery1->SQL->Clear();
						ADOQuery1->SQL->Text = "DELETE FROM CUSTOMER WHERE ACCT IS NULL AND STORE = "+MainMenuForm->strStoreNo;
						ADOQuery1->ExecSQL();


							ADOQuery1->Active = false;
						ADOQuery1->SQL->Clear();
						ADOQuery1->SQL->Text = "DELETE FROM INVOICE WHERE ACCT IS NULL AND STORE = "+MainMenuForm->strStoreNo;
						ADOQuery1->ExecSQL();

                       	ADOQuery1->Active = false;
						ADOQuery1->SQL->Clear();
						ADOQuery1->SQL->Text = "DELETE FROM ORDERS WHERE ITEM IS NULL AND STORE = "+MainMenuForm->strStoreNo;
						ADOQuery1->ExecSQL();

		 ADOQuery1->Active = false;

		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Add("Select * from Store where Store = "+MainMenuForm->strStoreNo );

		ADOQuery1->Active = true;

		if( ADOQuery1->FieldByName("STOREMESSAGE")->AsString != "" )
		{

			   ShowMessage( ADOQuery1->FieldByName("STOREMESSAGE")->AsString);
			   AnsiString strMessage = ADOQuery1->FieldByName("STOREMESSAGE")->AsString;
				if(strMessage.SubString(0,7) ==  "EXPIRED" )
				{
						Application->Terminate();
                }

        }

		if( ADOQuery1->Eof )
		{

		   ShowMessage("Incorrect User Id and Password!");
			ADOQuery1->Active = false;
		}
		else
		{

		if( CheckBox1->IsChecked )
		{
			FILE *stream;
			stream = fopen("c:\\VIVALDI8\\LOGINEMAIL.TXT", "w+");

			AnsiString  s;


			s = Edit1->Text;

			fprintf(stream , "%s", s);


			fclose(stream);


		}


		if( ADOQuery1->FieldByName("TOTALDUE")->AsFloat > 0 )
		{
			ShowMessage("Your current monthly bill is overdue.  To continue service please use the Pay Bill button on the Store Manager Edit Window. Due $"+ADOQuery1->FieldByName("TOTALDUE")->AsString +" Select multiple Quantities for multiple months.");
        }



		MainMenuForm->iBackgroundColor  = ADOQuery1->FieldByName("COLOR")->AsFloat;


        if( MainMenuForm->iBackgroundColor == 0 )
			 {
			   MainMenuForm->iBackgroundColor = 4278190080;
			   this->Fill->Color = 4278190080;
			 }

		MainMenuForm->dblEnvironmental = ADOQuery1->FieldByName("ENVIRONMENTAL")->AsFloat;
		MainMenuForm->strEnvironmentalClasses  = ADOQuery1->FieldByName("ENVIRONMENTALCLASSES")->AsString;

			MainMenuForm->dblActualEnvironmentalFee  = 0;
		MainMenuForm->strCustomTicket  = ADOQuery1->FieldByName("CUSTOMTICKET")->AsString;

		if( MainMenuForm->strCustomTicket  == "" )
		  MainMenuForm->strCustomTicket = "TicketView.rdl";

		if( MainMenuForm->blnEnableEnterprise )
		  MainMenuForm->strEnterprise = ADOQuery1->FieldByName("ENTERPRISE")->AsString;
		else
		  MainMenuForm->strEnterprise = ADOQuery1->FieldByName("STORE")->AsString;

		MainMenuForm->strSurchargeLabel = ADOQuery1->FieldByName("SURCHARGELABEL")->AsString;

			 TIniFile& tfile = *new TIniFile("C:\\FOLLOW\\FOLLOW.INI");

			 MainMenuForm->blnRecalcTaxAfterCoupon   = ADOQuery1->FieldByName("RECALCTAX")->AsBoolean;
			 MainMenuForm->blnPrintTwice  = ADOQuery1->FieldByName("PRINTTWICE")->AsBoolean;
			MainMenuForm->blnSmallerItems    = ADOQuery1->FieldByName("SMALLERITEMS")->AsBoolean;
			 MainMenuForm->blnWinExec   = ADOQuery1->FieldByName("WINEXEC")->AsBoolean;

			 MainMenuForm->blnLargerDTags  = ADOQuery1->FieldByName("LARGERDTAGS")->AsBoolean;

			  MainMenuForm->blnTagName  = ADOQuery1->FieldByName("TAGNAME")->AsBoolean;

				 MainMenuForm->blnTaxAllClasses   = ADOQuery1->FieldByName("TAXALLCLASSES")->AsBoolean;

				 MainMenuForm->blnLevelLoyalty  = ADOQuery1->FieldByName("LEVELLOYALTY")->AsBoolean;

				 MainMenuForm->blnEpsonU220Tag   = ADOQuery1->FieldByName("EPSONU220TAG")->AsBoolean;

			 MainMenuForm->blnDefaultNewTaxable = ADOQuery1->FieldByName("DEFAULTNEWTAXABLE")->AsBoolean;

			 MainMenuForm->blnAutoStarch = ADOQuery1->FieldByName("AUTOSTARCH")->AsBoolean;

			   MainMenuForm->blnUseMinFee  = ADOQuery1->FieldByName("USEMINFEE")->AsBoolean;

			 MainMenuForm->strCCReceiptPathPrinter = tfile.ReadString("TICKETS","RECEIPTPRINTER","");

			 MainMenuForm->strTicketPrinter = tfile.ReadString("TICKETS","TICKETPRINTER","DEFAULT");

			MainMenuForm->blnWiderTags = ADOQuery1->FieldByName("WIDERTAGS")->AsBoolean;
			MainMenuForm->blnUseDeliveryVacation = ADOQuery1->FieldByName("USEDELIVERYVACATION")->AsBoolean;

		if( MainMenuForm->strSurchargeLabel == "" )
				MainMenuForm->strSurchargeLabel = "Environmental Fee:";

		MainMenuForm->intRackTicketNumber = ADOQuery1->FieldByName("RACKTICKETNUMBER")->AsInteger;
		MainMenuForm->intMaxItems  = ADOQuery1->FieldByName("MAXITEMS")->AsInteger;

		MainMenuForm->blnDirectPrint = ADOQuery1->FieldByName("DIRECTPRINT")->AsBoolean;
		MainMenuForm->blnDontPrintTags  = ADOQuery1->FieldByName("DONTPRINTTAGSONEDIT")->AsBoolean;
		MainMenuForm->blnUseInventoryControl  = ADOQuery1->FieldByName("USEINVENTORYCONTROL")->AsBoolean;
		MainMenuForm->bln64Bit = ADOQuery1->FieldByName("64BIT")->AsBoolean;
		MainMenuForm->blnUseLotSystem  = ADOQuery1->FieldByName("USELOTSYSTEM")->AsBoolean;


		MainMenuForm->strDefaultStatus  = ADOQuery1->FieldByName("DSTATUS")->AsString;
		MainMenuForm->strPrintPause = ADOQuery1->FieldByName("PRINTPAUSE")->AsString;

		MainMenuForm->blnSeperateShirtLot = ADOQuery1->FieldByName("SEPERATESHIRTLOT")->AsBoolean;
		MainMenuForm->strCustomerARStatement  = ADOQuery1->FieldByName("CUSTOMARSTATEMENT")->AsString;
		MainMenuForm->blnUseRackTicket  = ADOQuery1->FieldByName("USERACKTICKET")->AsBoolean;
		MainMenuForm->blnAdditionalTagInfo  = ADOQuery1->FieldByName("ADDITIONALTAGINFO")->AsBoolean;
		MainMenuForm->blnDeliveryByDate  = ADOQuery1->FieldByName("DELIVERYBYDATE")->AsBoolean;
		MainMenuForm->blnUseEuropeanFormat = ADOQuery1->FieldByName("USEEUROPEANFORMAT")->AsBoolean;
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
		MainMenuForm->blnShowReadyOnly = ADOQuery1->FieldByName("SHOWREADYONLY")->AsBoolean;

		MainMenuForm->blnDefaultLoyalty  = ADOQuery1->FieldByName("DEFAULTLOYALTY")->AsBoolean;

		if(  ADOQuery1->FieldByName("EMAILSECURITY")->AsBoolean )
		{
		   MainMenuForm->strEmailSecurity = "USE-U";
		}

		if( ADOQuery1->FieldByName("WRITETICKET")->AsString != "" ) {

		   MainMenuForm->MetroListBoxItem6->Title =  ADOQuery1->FieldByName("WRITETICKET")->AsString;
			MainMenuForm->MenuItem9->Text =  ADOQuery1->FieldByName("WRITETICKET")->AsString;

		}
			if( ADOQuery1->FieldByName("PICKUPTICKET")->AsString != "" ) {

		   MainMenuForm->MetroListBoxItem1->Title =  ADOQuery1->FieldByName("PICKUPTICKET")->AsString;
		   MainMenuForm->MenuItem10->Text =  ADOQuery1->FieldByName("PICKUPTICKET")->AsString;

		}
			if( ADOQuery1->FieldByName("CUSTOMER")->AsString != "" ) {

		   MainMenuForm->MetroListBoxItem2->Title =  ADOQuery1->FieldByName("CUSTOMER")->AsString;
			MainMenuForm->MenuItem19->Text =  ADOQuery1->FieldByName("CUSTOMER")->AsString;


		}
		if( ADOQuery1->FieldByName("MARKTICKETSREADY")->AsString != "" ) {

		   MainMenuForm->MetropolisUIListBoxItem1->Title =  ADOQuery1->FieldByName("MARKTICKETSREADY")->AsString;
			MainMenuForm->MenuItem14->Text =  ADOQuery1->FieldByName("MARKTICKETSREADY")->AsString;
		}

		if( ADOQuery1->FieldByName("ASSIGNLOCATION")->AsString != "" ) {

		   MainMenuForm->MetropolisUIListBoxItem2->Title =  ADOQuery1->FieldByName("ASSIGNLOCATION")->AsString;
			MainMenuForm->MenuItem13->Text =  ADOQuery1->FieldByName("ASSIGNLOCATION")->AsString;

		}

		if( ADOQuery1->FieldByName("CASHDRAWER")->AsString != "" ) {

		   MainMenuForm->MetropolisUIListBoxItem3->Title =  ADOQuery1->FieldByName("CASHDRAWER")->AsString;
			MainMenuForm->MenuItem25->Text =  ADOQuery1->FieldByName("CASHDRAWER")->AsString;

		}

			if( ADOQuery1->FieldByName("EDITTICKET")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem4->Title =  ADOQuery1->FieldByName("EDITTICKET")->AsString;
		   MainMenuForm->MenuItem11->Text =  ADOQuery1->FieldByName("EDITTICKET")->AsString;

		}


			if( ADOQuery1->FieldByName("INVENTORY")->AsString != "" ) {

		//   MainMenuForm->MetroListBoxItem7->Title =  ADOQuery1->FieldByName("INVENTORY")->AsString;
			MainMenuForm->MenuItem39->Text =  ADOQuery1->FieldByName("INVENTORY")->AsString;

		}

			if( ADOQuery1->FieldByName("TIMECARD")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem5->Title =  ADOQuery1->FieldByName("TIMECARD")->AsString;

		}

			if( ADOQuery1->FieldByName("ACCOUNT")->AsString != "" ) {

		 //  MainMenuForm->MetropolisUIListBoxItem7->Title =  ADOQuery1->FieldByName("ACCOUNT")->AsString;
		   MainMenuForm->MenuItem28->Text =  ADOQuery1->FieldByName("ACCOUNT")->AsString;

		}

			if( ADOQuery1->FieldByName("DELIVERYMANAGER")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem8->Title =  ADOQuery1->FieldByName("DELIVERYMANAGER")->AsString;
			 MainMenuForm->MenuItem29->Text =  ADOQuery1->FieldByName("DELIVERYMANAGER")->AsString;

		}
			if( ADOQuery1->FieldByName("STOREMANAGER")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem9->Title =  ADOQuery1->FieldByName("STOREMANAGER")->AsString;
			  MainMenuForm->MenuItem18->Text =  ADOQuery1->FieldByName("STOREMANAGER")->AsString;

		}
			if( ADOQuery1->FieldByName("GARMENTTAG")->AsString != "" ) {

		 //  MainMenuForm->MetropolisUIListBoxItem10->Title =  ADOQuery1->FieldByName("GARMENTTAG")->AsString;
		   MainMenuForm->MenuItem141->Text =  ADOQuery1->FieldByName("GARMENTTAG")->AsString;

		}

			if( ADOQuery1->FieldByName("ROUTEMANAGER")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem11->Title =  ADOQuery1->FieldByName("ROUTEMANAGER")->AsString;
		   MainMenuForm->MenuItem124->Text =  ADOQuery1->FieldByName("ROUTEMANAGER")->AsString;

		}

			if( ADOQuery1->FieldByName("HOTELMANAGER")->AsString != "" ) {

		 //  MainMenuForm->MetropolisUIListBoxItem12->Title =  ADOQuery1->FieldByName("HOTELMANAGER")->AsString;
            MainMenuForm->MenuItem106->Text =  ADOQuery1->FieldByName("HOTELMANAGER")->AsString;

		}

			if( ADOQuery1->FieldByName("CUSTOMERISSUE")->AsString != "" ) {

		  // MainMenuForm->MetropolisUIListBoxItem13->Title =  ADOQuery1->FieldByName("CUSTOMERISSUE")->AsString;

		}



		 MainMenuForm->blnSendReadyEmail =   ADOQuery1->FieldByName("SENDEMAILREADY")->AsBoolean;


		 MainMenuForm->blnSendTicketEmail =   ADOQuery1->FieldByName("SENDEMAILTICKET")->AsBoolean;


			MainMenuForm->strStoreName = ADOQuery1->FieldByName("Name")->AsString;
			MainMenuForm->strStoreAddress = ADOQuery1->FieldByName("Address1")->AsString;
			MainMenuForm->strStorePhone   = ADOQuery1->FieldByName("Phone")->AsString;
			MainMenuForm->strCityState = ADOQuery1->FieldByName("City")->AsString+", "+ADOQuery1->FieldByName("State")->AsString+" "+ADOQuery1->FieldByName("Zip")->AsString;
			if( ADOQuery1->FieldByName("TaxRate")->AsString != "" )
			{
			  MainMenuForm->fTaxRate = ADOQuery1->FieldByName("TaxRate")->AsFloat;
			}
			else
			{
               MainMenuForm->fTaxRate = 0;

            }

			 MainMenuForm->strTicketCopies = ADOQuery1->FieldByName("TicketCopies")->AsString;


		 if( MainMenuForm->blnUseLotSystem  && (ADOQuery1->FieldByName("LOTDATE")->AsString == "" || ADOQuery1->FieldByName("LOTDATE")->AsString != DateTimeToStr(Now()).SubString(0,10) ) )
		 {

			  ADOQuery1->Edit();
			  ADOQuery1->FieldByName("LOTDATE")->AsString = DateTimeToStr(Now()).SubString(0,10);
			   ADOQuery1->FieldByName("LOTGROUP")->AsString = "1";
				ADOQuery1->FieldByName("SHIRTLOTCURRENT")->AsString = "100";
				 ADOQuery1->FieldByName("CURRENTLOT")->AsString = "1";

			   ADOQuery1->Post();

		 }
			 ADOQuery1->Close();

			 if( MainMenuForm->strTicketCopies == "" )
			    MainMenuForm->strTicketCopies = "2";

            //	MainMenuForm->UpdateMenu();

			this->Close();
		}
	}



}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button2Click(TObject *Sender)
{
		Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::FormShow(TObject *Sender)
{

this->Fill->Color = MainMenuForm->iBackgroundColor ;
	Edit1->SetFocus();
		try {


    	FILE *stream;
			stream = fopen("C:\\VIVALDI8\\LOGINEMAIL.TXT", "r");

			char msg[120];


			fgets(msg, 120,stream);


			fclose(stream);
			Edit1->Text = msg;
			Edit2->SetFocus();

		}
		catch(const Exception& e)
		{
		}


}
//---------------------------------------------------------------------------



void __fastcall TLoginForm01::Edit1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{

 if( Key == VK_RETURN )
   Edit2->SetFocus();

}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Edit2KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
 if( Key == VK_RETURN )
   Edit3->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button4Click(TObject *Sender)
{
   Edit2->Text =   Edit2->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button5Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button12Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button6Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button7Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button8Click(TObject *Sender)
{
      Edit2->Text =   Edit2->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button9Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button10Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button11Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm01::Button13Click(TObject *Sender)
{
Edit2->Text =   Edit2->Text + "9";
}
//---------------------------------------------------------------------------

