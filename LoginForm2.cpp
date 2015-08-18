//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "LoginForm2.h"
#include "MainMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TLoginForm02 *LoginForm02;
//---------------------------------------------------------------------------
__fastcall TLoginForm02::TLoginForm02(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TLoginForm02::Button1Click(TObject *Sender)
{
	//strStoreCode  = Edit3->Text;


	ADOQuery1->Active = false;
	ADOQuery1->SQL->Clear();
	ADOQuery1->SQL->Add("Select * from users where password = '"+ Edit2->Text  +"' and store = "+ MainMenuForm->strStoreNo);
	ADOQuery1->Active = true;

	if( ADOQuery1->Eof )
	{

		ShowMessage("Incorrect Password!");
		Edit2->Text = "";
	    Edit2->SetFocus();
		ADOQuery1->Active = false;
	}
	else
	{
		 ModalResult = mrOk;
		 //MainMenuForm->strStoreNo = Edit3->Text;
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

		  //MainMenuForm->blnAllowMarkReadyAccess = ADOQuery1->FieldByName("ENABLEMARKREADY")->AsBoolean; //NOT USED


		 //MainMenuForm->strUserEmail = ADOQuery1->FieldByName("Email")->AsString;
		 //MainMenuForm->strStoreNo =  ADOQuery1->FieldByName("Store")->AsString;
		 ADOQuery1->Active = false;

		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Add("Select * from Store where Store = "+MainMenuForm->strStoreNo );

		ADOQuery1->Active = true;

		if( ADOQuery1->Eof )
		{

		   ShowMessage("Incorrect User Id and Password!");
			ADOQuery1->Active = false;
		}
		else
		{

			MainMenuForm->UpdateMenu();
			 //MainMenuForm->strTicketCopies = ADOQuery1->FieldByName("TicketCopies")->AsString;

			 //if( MainMenuForm->strTicketCopies == "" )
			 //   MainMenuForm->strTicketCopies = "2";

			this->Close();
		}
	}



}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button2Click(TObject *Sender)
{
		Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::FormShow(TObject *Sender)
{
	Edit2->SetFocus();
	//this->Fill->Color = MainMenuForm->iBackgroundColor ;
}
//---------------------------------------------------------------------------



void __fastcall TLoginForm02::Edit1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{

 if( Key == VK_RETURN )
   Edit2->SetFocus();

}
//---------------------------------------------------------------------------


void __fastcall TLoginForm02::Button3Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "0";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button4Click(TObject *Sender)
{
 Edit2->Text =   Edit2->Text + "1";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button5Click(TObject *Sender)
{
 Edit2->Text =   Edit2->Text + "3";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button12Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "2";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button6Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "4";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button7Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "5";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button8Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "6";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button9Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "7";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button10Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "8";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm02::Button11Click(TObject *Sender)
{
  Edit2->Text =   Edit2->Text + "9";
}
//---------------------------------------------------------------------------

