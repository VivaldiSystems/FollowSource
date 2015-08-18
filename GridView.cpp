//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include <System.UITypes.hpp>

#include "System.Win.Registry.hpp"
#include "GridView.h"

#include "LoginForm.h"
#include "SplitPaneView.h"
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "AccountForm2.h"
#include "Dashboard1.h"
#include "DeliveryForm2.h"
#include "WriteTicket.h"
#include "PickupForm.h"
#include "CustomerForm2.h"
#include "HotelForm2.h"
#include "AssignLocation1.h"
#include "MarkReady1.h"
#include "CashDrawerForm1.h"
#include "EditTicket3.h"
#include "InventoryForm1.h"
#include "ColorsForm2.h"
#include "StoreForm2.h"
#include "DCItemForm2.h"
#include "UpchargeForm2.h"
#include "ClassForm2.h"
#include "UserForm2.h"
#include "RouteForm2.h"
#include "CouponForm2.h"
#include "LoginForm2.h"
#include "GarmentTag.h"
#include "IssuesForm2.h"
#include "WholesaleForm2.h"
#include "GiftCardForm2.h"
#include "FM_CustomerSearch1.h"
#include "SendEmailReminderForm1.h"
#include "NewCustomerEmailForm1.h"

#include <shellapi.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TGridViewForm *GridViewForm;
//---------------------------------------------------------------------------
__fastcall TGridViewForm::TGridViewForm(TComponent* Owner)
	: TForm(Owner)
{

	   strVersionNumber = "4.08";
	   Label1->Text = "Vivaldi Systems - POS Metro "+strVersionNumber+"  - (Cloud) User: ";
	   blnDateOut = true;
	   blnTicketClosed = false;
	   blnEnableTopMenu = false;
	   blnUseEuropeanFormat = false;
	   blnDisableDates  = false;
	   blnReturnTendered = false;
	   blnDateIn = true;
	   strLastSearch = "";


        TIniFile& tfile = *new TIniFile("C:\\VIVALDI8\\VIVALDI8.INI");

		AnsiString strConnection = tfile.ReadString("DATABASE","CONNECTIONSTRING","");

		blnLocalDatabase = false;

		if (strConnection != "" ) {
			   ADOConnection1->Close();
			   ADOConnection1->ConnectionString = strConnection;
				ADOConnection1->Open();
				 Label1->Text = "Vivaldi Systems - POS Metro "+strVersionNumber+"  - (Local SQL) User: ";
				blnLocalDatabase = true;
		}
		else
		{
		   //ADOConnection1->ConnectionString = "Provider=SQLOLEDB.1;Password=foll2164;Persist Security Info=True;User ID=DB_53817_vivaldis_user;Initial Catalog=DB_53817_vivaldis;Data Source=s09.winhost.com";

		}
        ADOQuery1->Active = true;

	   //= "StyleBook2";

	   //SetStyleFromFile

	   //Provider=Microsoft.ACE.OLEDB.15.0;Data Source=C:\VIVALDI8\STORES.ACCDB;Persist Security Info=False

	   //Provider=SQLOLEDB.1;Password=foll2164;Persist Security Info=True;User ID=DB_53817_vivaldis_user;Initial Catalog=DB_53817_vivaldis;Data Source=s09.winhost.com

}
//---------------------------------------------------------------------------
void __fastcall TGridViewForm::ItemClick(TObject *Sender)
{
	   //	TCommonCustomForm *Form = Application->GetDeviceForm(L"DetailView");
	   //	if (Form)
	   //		Form->Show();
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
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

void __fastcall TGridViewForm::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	ShowToolbar(Button == TMouseButton::mbRight);
}
//---------------------------------------------------------------------------
void TGridViewForm::ShowToolbar(bool AShow)
{
  ToolbarPopup->Width = ClientWidth;
  ToolbarPopup->PlacementRectangle->Rect = TRect(0, ClientHeight-ToolbarPopup->Height, ClientWidth-1, ClientHeight-1);
  ToolbarPopupAnimation->StartValue = ToolbarPopup->Height;
  ToolbarPopupAnimation->StopValue = 0;

  ToolbarPopup->IsOpen = AShow;
}

AnsiString __fastcall TGridViewForm::ConvertDate(AnsiString argDateString)
{
	AnsiString strReturnDate;


	if( GridViewForm->blnUseEuropeanFormat )
		strReturnDate = argDateString.SubString(4,2)+"/"+argDateString.SubString(1,2)+"/"+argDateString.SubString(7,4);
	else
	{

			   int ispace = argDateString.Pos(" ");
			   if( ispace > 0 )
			      argDateString = argDateString.SubString(1,ispace-1);



	   strReturnDate = argDateString;



	}



	 return strReturnDate;

 }
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::ToolbarCloseButtonClick(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
		  TShiftState Shift)
{
  if (Key == vkEscape) {
	  ShowToolbar(!ToolbarPopup->IsOpen);
  }
}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MetroListBoxItem7Click(TObject *Sender)
{

if(  MetroListBoxItem7->Enabled == false )
		  return;



//	Application->CreateForm(__classid(TInventoryForm), &InventoryForm);
//Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
		TInventoryForm* InventoryForm;
				Application->CreateForm(__classid(TInventoryForm), &InventoryForm);
				if (InventoryForm )
				{
					InventoryForm->ShowModal();
					delete InventoryForm;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();
					UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem8Click(TObject *Sender)
{
//Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
		 //	Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
		TLoginForm01* LoginForm01;
				Application->CreateForm(__classid(TLoginForm01), &LoginForm01);
				if (LoginForm01 )
				{
					LoginForm01->ShowModal();
					delete LoginForm01;

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
					if( blnEnableEnterprise ) {
					   Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

					}
					else
					{
                        Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

                    }
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetroListBoxItem2Click(TObject *Sender)
{


 if(  MetroListBoxItem2->Enabled == false )
		  return;

	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	TCustomerForm01* CustomerForm01;
				Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
				if (CustomerForm01 )
				{
					CustomerForm01->ShowModal();
					delete CustomerForm01;
				}

              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetroListBoxItem6Click(TObject *Sender)
{


	  if(  MetroListBoxItem6->Enabled == false )
		  return;

	   GridViewForm->blnPrePayAllToday = false;
	   GridViewForm->blnRepeat  = false;

	  //	TCommonCustomForm *FormWriteTicket = Application->GetDeviceForm(L"WriteTicket");
		if ( blnTicketClosed == false )
		{


           	GridViewForm->blnAccountCustomer = false;

			GridViewForm->strPickupAccount = "";

				TWriteTicketForm01* WriteTicketForm01;
				Application->CreateForm(__classid(TWriteTicketForm01), &WriteTicketForm01);
				if (WriteTicketForm01 )
				{
					WriteTicketForm01->ShowModal();
					delete WriteTicketForm01;



				}

			blnTicketClosed = true;

            	if( GridViewForm->strPickupAccount != "" )
						{

                             MetroListBoxItem1Click(Sender);

						}
						else
						{

			if(  GridViewForm->blnTransactionLogin  )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

                 }


	   }
	   else
		  blnTicketClosed = false;

		    GridViewForm->strCustomerAcct = "";
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetroListBoxItem1Click(TObject *Sender)
{



 if(  MetroListBoxItem1->Enabled == false )
		  return;



	GridViewForm->strPickupAccount = "";
	GridViewForm->blnAccountCustomer = false;

   // Application->CreateForm(__classid(TPickupWindow01), &PickupWindow01);

   TPickupWindow01* PickupWindow01;
				Application->CreateForm(__classid(TPickupWindow01), &PickupWindow01);
				if (PickupWindow01 )
				{
					PickupWindow01->ShowModal();
					delete PickupWindow01;
				}
                GridViewForm->strCustomerAcct = "";


              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::FormShow(TObject *Sender)
{
        GridViewForm->strAdditionalFilter = "";
		this->WindowState = 2;

		TLoginForm01* LoginForm01;
				Application->CreateForm(__classid(TLoginForm01), &LoginForm01);
				if (LoginForm01 )
				{
					LoginForm01->ShowModal();
					delete LoginForm01;

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
					Label1->Text = "";
					if( blnEnableEnterprise ) {
					   Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

					}
					else
					{
						Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

					}


				}


			   UpdateMenu();
			   GridViewForm->strDateOut = DateTimeToStr(Now()+GridViewForm->intDaysToPickup).SubString(1,10);

			   int ispace = GridViewForm->strDateOut.Pos(" ");
			   if( ispace > 0 )
				 GridViewForm->strDateOut = GridViewForm->strDateOut.SubString(1,ispace-1);



			  CalendarEdit1->Date =  StrToDate( GridViewForm->strDateOut );

			 //SpeedButton1Click(Sender) ;

			 if( GridViewForm->iBackgroundColor == 0 )
			 {
			   GridViewForm->iBackgroundColor = 4278190080;
			   ColorComboBox1->Color = 4278190080;
			   this->Fill->Color = 4278190080;
			 }
			 else
			   ColorComboBox1->Color =  GridViewForm->iBackgroundColor;
}
//---------------------------------------------------------------------------
 void __fastcall TGridViewForm::UpdateMenu()
{

	TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
	if( blnEnableEnterprise ) {
		Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

	}
	else
	{
		Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

	}

               if(  GridViewForm->blnEnableTopMenu )
			   {

						MenuItem1->Enabled = true;

						MenuItem2->Enabled = true;

						MenuItem3->Enabled = true;

						MenuItem4->Enabled = true;

						MenuItem5->Enabled = true;



			   }
			   else
			   {

						MenuItem1->Enabled = false;

						MenuItem2->Enabled = false;

						MenuItem3->Enabled = false;

						MenuItem4->Enabled = false;

						MenuItem5->Enabled = false;



			   }





		 if( GridViewForm->blnAllowEditAccess )
		  {
				MetropolisUIListBoxItem4->Enabled = true;
				MetropolisUIListBoxItem4->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem4->Enabled = false;
				MetropolisUIListBoxItem4->Visible = false;
		  }

		  if(GridViewForm->blnAllowCustomerAccess )
		   {

				MetropolisUIListBoxItem13->Visible = true;

				MetroListBoxItem2->Enabled = true;
				MetroListBoxItem2->Visible = true;
				CornerButton3->Enabled = true;
				MenuItem19->Enabled = true;
		  }
		  else
		  {
			   MetropolisUIListBoxItem13->Visible = false;
				MetroListBoxItem2->Enabled = false;
				MetroListBoxItem2->Visible = false;
				CornerButton3->Enabled = false;
				MenuItem19->Enabled = false;
		  }

		  if(GridViewForm->blnAllowWriteAccess )
		   {
				MetroListBoxItem6->Enabled = true;
				MetropolisUIListBoxItem10->Visible = true;
				MetroListBoxItem6->Visible = true;
					CornerButton1->Enabled = true;
		  }
		  else
		  {
				MetroListBoxItem6->Enabled = false;
				MetroListBoxItem6->Visible = false;
				MetropolisUIListBoxItem10->Visible = false;
					CornerButton1->Enabled = false;
		  }

		 if( GridViewForm->blnAllowPickupAccess )
		   {
				MetroListBoxItem1->Enabled = true;
				MetroListBoxItem1->Visible = true;
					CornerButton2->Enabled = true;
		  }
		  else
		  {
				MetroListBoxItem1->Enabled = false;
				MetroListBoxItem1->Visible = false;
					CornerButton2->Enabled = false;
		  }

		 if( GridViewForm->blnAllowXChargeAccess )
		   {
				MetropolisUIListBoxItem6->Enabled = true;
				MetropolisUIListBoxItem6->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem6->Enabled = false;
				MetropolisUIListBoxItem6->Visible = false;
		  }

		 if( GridViewForm->blnAllowTimeCardAccess)
		 {
				MetropolisUIListBoxItem5->Enabled = true;
					MetropolisUIListBoxItem5->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem5->Enabled = false;
					MetropolisUIListBoxItem5->Visible = false;
		  }

		  if(GridViewForm->blnAllowInventoryAccess )
		  {
				MetroListBoxItem7->Enabled = true;
					MetroListBoxItem7->Visible = true;
		  }
		  else
		  {
				MetroListBoxItem7->Enabled = false;
					MetroListBoxItem7->Visible = false;
		  }

		  if(GridViewForm->blnAllowAccountAccess )
		  {
				CornerButton4->Enabled = true;
				MenuItem28->Enabled = true;
				MetropolisUIListBoxItem7->Enabled = true;
				MetropolisUIListBoxItem7->Visible = true;
		  }
		  else
		  {
				CornerButton4->Enabled = false;
				MenuItem28->Enabled = false;
				MetropolisUIListBoxItem7->Enabled = false;
				MetropolisUIListBoxItem7->Visible = false;
		  }




		  if(GridViewForm->blnAllowStoreAccess )
		  {
				MetropolisUIListBoxItem9->Enabled = true;
				MetropolisUIListBoxItem9->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem9->Enabled = false;
				MetropolisUIListBoxItem9->Visible = false;
		  }

		  if(GridViewForm->blnAllowHotelAccess )
		  {
				MetropolisUIListBoxItem12->Enabled = true;
				MetropolisUIListBoxItem12->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem12->Enabled = false;
				MetropolisUIListBoxItem12->Visible = false;
		  }

		  if(GridViewForm->blnAllowDeliveryAccess )
		  {
				MetropolisUIListBoxItem8->Enabled = true;
				MetropolisUIListBoxItem8->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem8->Enabled = false;
				MetropolisUIListBoxItem8->Visible = false;
		  }

		  if(GridViewForm->blnAllowRouteAccess )
		  {
				MetropolisUIListBoxItem11->Enabled = true;
				MetropolisUIListBoxItem11->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem11->Enabled = false;
				MetropolisUIListBoxItem11->Visible = false;
		  }


		  if(GridViewForm->blnAllowCashDrawerAccess )
		  {
				MetropolisUIListBoxItem3->Enabled = true;
				MetropolisUIListBoxItem3->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem3->Enabled = false;
				MetropolisUIListBoxItem3->Visible = false;
		  }




		 if( GridViewForm->blnAllowAssignLocationAccess)
		  {
				MetropolisUIListBoxItem2->Enabled = true;
					MetropolisUIListBoxItem1->Enabled = true;
						MetropolisUIListBoxItem2->Visible = true;
					MetropolisUIListBoxItem1->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem2->Enabled = false;
					MetropolisUIListBoxItem1->Enabled = false;
						MetropolisUIListBoxItem2->Visible = false;
					MetropolisUIListBoxItem1->Visible = false;
		  }

		   if(GridViewForm->blnAllowPriceListAccess )
		  {
				MetropolisUIListBoxItem14->Enabled = true;
				MetropolisUIListBoxItem14->Visible = true;
				MenuItem21->Enabled = true;
				MenuItem46->Enabled = true;
				MenuItem20->Enabled = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem14->Enabled = false;
				MetropolisUIListBoxItem14->Visible = false;
					MenuItem21->Enabled = false;
				MenuItem46->Enabled = false;
				MenuItem20->Enabled = false;
		  }



}


void __fastcall TGridViewForm::MenuItem16Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerReport.rdl";
			strReportName = "Customer Listing Report";
			strReportFilter = " ISACTIVE = 1  ";      //3304776517
			GridViewForm->strDataSet = "CUSTOMER" ;
			//Form->Label3->Text = "Customer Listing Report";
			Form->ShowModal();
			delete Form;

		}

}


//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MenuItem17Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerAccounts.rdl";
			strReportName = "Account Customers Report";
			GridViewForm->strDataSet = "CUSTOMER" ;
			strReportFilter = " Account=1";

			//Form->Label3->Text = "Customer Listing Report";
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem7Click(TObject *Sender)
{
      Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem6Click(TObject *Sender)
{
			//Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
		 //	Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
		TLoginForm01* LoginForm01;
				Application->CreateForm(__classid(TLoginForm01), &LoginForm01);
				if (LoginForm01 )
				{
					LoginForm01->ShowModal();
					delete LoginForm01;

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
					if( blnEnableEnterprise ) {
					   Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

					}
					else
					{
                        Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

                    }
				}
}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MenuItem18Click(TObject *Sender)
{


   //	Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
			TStoreForm01* StoreForm01;
				Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
				if (StoreForm01 )
				{
					StoreForm01->ShowModal();
					delete StoreForm01;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem19Click(TObject *Sender)
{

	MetroListBoxItem2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem21Click(TObject *Sender)
{

		 //	Application->CreateForm(__classid(TDCItemForm01), &DCItemForm01);
		TDCItemForm01* DCItemForm01;
				Application->CreateForm(__classid(TDCItemForm01), &DCItemForm01);
				if (DCItemForm01 )
				{
					DCItemForm01->ShowModal();
					delete DCItemForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem20Click(TObject *Sender)
{


			 //	Application->CreateForm(__classid(TClassForm01), &ClassForm01);
		TClassForm01* ClassForm01;
				Application->CreateForm(__classid(TClassForm01), &ClassForm01);
				if (ClassForm01 )
				{
					ClassForm01->ShowModal();
					delete ClassForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------






void __fastcall TGridViewForm::MetropolisUIListBoxItem4Click(TObject *Sender)
{
GridViewForm->strDefaultEditTicketNumber = "";

if(  MetropolisUIListBoxItem4->Enabled == false )
		  return;


		GridViewForm->blnAccountCustomer = false;

		//	Application->CreateForm(__classid(TEditTicketForm03), &EditTicketForm03);
		TEditTicketForm03* EditTicketForm03;
				Application->CreateForm(__classid(TEditTicketForm03), &EditTicketForm03);
				if (EditTicketForm03 )
				{
					EditTicketForm03->ShowModal();
					delete EditTicketForm03;
				}
				  GridViewForm->strCustomerAcct = "";


              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem2Click(TObject *Sender)
{


if(  MetropolisUIListBoxItem2->Enabled == false )
		  return;




	   //Application->CreateForm(__classid(TAssignLocationForm), &AssignLocationForm);
		TAssignLocationForm* AssignLocationForm;
				Application->CreateForm(__classid(TAssignLocationForm), &AssignLocationForm);
				if (AssignLocationForm )
				{
					AssignLocationForm->ShowModal();
					delete AssignLocationForm;
				}


              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem1Click(TObject *Sender)
{

if(  MetropolisUIListBoxItem1->Enabled == false )
		  return;

		//Application->CreateForm(__classid(TMarkReadyForm), &MarkReadyForm);
		TMarkReadyForm* CustomerForm01;
				Application->CreateForm(__classid(TMarkReadyForm), &CustomerForm01);
				if (CustomerForm01 )
				{
					CustomerForm01->ShowModal();
					delete CustomerForm01;
				}


              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem13Click(TObject *Sender)
{
	MetropolisUIListBoxItem2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem14Click(TObject *Sender)
{
	MetropolisUIListBoxItem1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem6Click(TObject *Sender)
{


if(  MetropolisUIListBoxItem6->Enabled == false )
		  return;


 SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\Program Files\\X-CHARGE\\XCHARGE.EXE";

   AnsiString strParam = ""; //GridViewForm->strStoreNo+ " "+ GridViewForm->strReportFileName+" "+GridViewForm->strReportFilter;
   GridViewForm->strReportFilter = "";
   int iSize = strParam.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   strParam.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_SHOWDEFAULT;


  	if(! ShellExecuteEx(&execinfo))
	{
		ShowMessage("Could Not Run X-Charge. Check that c:\\Program Files\\X-charge\\X-CHARGE.exe has not been Installed!");
		return;
	}



}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem5Click(TObject *Sender)
{
if(  MetropolisUIListBoxItem5->Enabled == false )
		  return;

SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\TimeCard Manager Basic\\TCMBasic.exe";

   AnsiString strParam = ""; //GridViewForm->strStoreNo+ " "+ GridViewForm->strReportFileName+" "+GridViewForm->strReportFilter;
   GridViewForm->strReportFilter = "";
   int iSize = strParam.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   strParam.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_SHOWDEFAULT;

	if(! ShellExecuteEx(&execinfo))
	{
		ShowMessage("You need to Install the TimeCard Manager (TCM.exe) Goto www.econsoft.com. The installer link is also found on the Help Menu of Vivaldi ");
		return;
	}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem3Click(TObject *Sender)
{



if(  MetropolisUIListBoxItem3->Enabled == false )
		  return;
		   //	Application->CreateForm(__classid(TCashDrawerForm), &CashDrawerForm);
			TCashDrawerForm* CashDrawerForm;
				Application->CreateForm(__classid(TCashDrawerForm), &CashDrawerForm);
				if (CashDrawerForm )
				{
					CashDrawerForm->ShowModal();
					delete CashDrawerForm;
				}


              	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem23Click(TObject *Sender)
{


SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\TCMBasicInstaller.exe";

   AnsiString strParam = ""; //GridViewForm->strStoreNo+ " "+ GridViewForm->strReportFileName+" "+GridViewForm->strReportFilter;
   GridViewForm->strReportFilter = "";
   int iSize = strParam.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   strParam.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_SHOWDEFAULT;

	if(! ShellExecuteEx(&execinfo))
	{
		ShowMessage("You need to Install the TimeCard Manager Installer (TCMBasicInstaller.exe) Goto www.econsoft.com. The installer link is also found on the Help Menu of Vivaldi ");
		return;
	}


}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem25Click(TObject *Sender)
{
    MetropolisUIListBoxItem3Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem26Click(TObject *Sender)
{


	   //Application->CreateForm(__classid(TUserForm01), &UserForm01);
		TUserForm01* UserForm01;
		Application->CreateForm(__classid(TUserForm01), &UserForm01);
		if (UserForm01 )
		{
			UserForm01->ShowModal();
			delete UserForm01;
		}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}


}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MenuItem31Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketListingSummary.rdl";
			strReportName = "Ticket Listing Summary";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";

			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem32Click(TObject *Sender)
{

		 //	Application->CreateForm(__classid(TCouponForm01), &CouponForm01);
		TCouponForm01* CouponForm01;
				Application->CreateForm(__classid(TCouponForm01), &CouponForm01);
				if (CouponForm01 )
				{
					CouponForm01->ShowModal();
					delete CouponForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem33Click(TObject *Sender)
{
 TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketDetailReport.rdl";
			strReportName = "Ticket Detail";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";
			strDataSet = "TicketView";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image1Click(TObject *Sender)
{
   Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem9Click(TObject *Sender)
{
	MetroListBoxItem6Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem10Click(TObject *Sender)
{
    MetroListBoxItem1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem11Click(TObject *Sender)
{
     MetropolisUIListBoxItem4Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem34Click(TObject *Sender)
{

  Caption = "Updating Email Accounts... Please Wait";

			 ADOCommand1->CommandText  = "UPDATE CUSTOMER SET PRIMEKEY = EMAIL where Store = "+ GridViewForm->strStoreNo;
	 ADOCommand1->Execute() ;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{




			strReportFileName = "CustomerEmailReport.rdl";
			strReportName = "Customer Email Report";
			GridViewForm->strDataSet = "CUSTOMER" ;
			strReportFilter = "PRIMEKEY IS NOT NULL AND ISACTIVE = 1 ";

			Form->ShowModal();
			delete Form;

			 Caption = "Vivaldi 8 Metro";

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem35Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketByStatus.rdl";
			strReportName = "Ticket by Status";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem37Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CashboxHistoryReport.rdl";
			strReportName = "Payment Type Summary";
			strReportFilter = "FILE";
			strDataSet = "CASHBOX";
			GridViewForm->blnDateOut = true;

			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem38Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CashboxbyPaymentTypeReport.rdl";
			strReportName = "Cashbox by Payment Type Report";
			strReportFilter = "FILE";
			strDataSet = "CASHBOX";
			GridViewForm->blnDateOut = true;

			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem39Click(TObject *Sender)
{
    MetroListBoxItem7Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem40Click(TObject *Sender)
{
   MetroListBoxItem6Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem41Click(TObject *Sender)
{
	MetroListBoxItem1Click(Sender) ;
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem42Click(TObject *Sender)
{
	  MetropolisUIListBoxItem4Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem43Click(TObject *Sender)
{
	 MetroListBoxItem2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem44Click(TObject *Sender)
{
   MetropolisUIListBoxItem2Click(Sender) ;
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem45Click(TObject *Sender)
{

  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.vivaldi2000.com/TCMBasicInstaller.exe";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not connect to the Microsoft Web site!");
						return;
				   }

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem46Click(TObject *Sender)
{


		 //	Application->CreateForm(__classid(TCouponForm01), &CouponForm01);
		TUpchargeForm03* UpchargeForm03;
				Application->CreateForm(__classid(TUpchargeForm03), &UpchargeForm03);
				if (UpchargeForm03 )
				{
					UpchargeForm03->ShowModal();
					delete UpchargeForm03;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem108Click(TObject *Sender)
{

		TAccountForm01* AccountForm01;
		Application->CreateForm(__classid(TAccountForm01), &AccountForm01);
		if (AccountForm01 )
		{
			AccountForm01->ShowModal();
			delete AccountForm01;
		}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}


}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem122Click(TObject *Sender)
{




SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";
   //"C:\Program Files\Microsoft SQL Server\Report Builder 2.0\MSReportBuilder.exe"
   execinfo.lpFile = L"C:\\Program Files (x86)\\Microsoft SQL Server\\Report Builder 2.0\\MSReportBuilder.exe";

   AnsiString strParam = ""; //GridViewForm->strStoreNo+ " "+ GridViewForm->strReportFileName+" "+GridViewForm->strReportFilter;
   GridViewForm->strReportFilter = "";
   int iSize = strParam.WideCharBufSize();
   wchar_t *wTemp = new wchar_t[iSize];
   strParam.WideChar(wTemp, iSize);

   execinfo.lpParameters =  wTemp;

   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
   execinfo.nShow = SW_SHOWDEFAULT;

	if(! ShellExecuteEx(&execinfo))
	{
		ShowMessage("You need to Install the Report Builder 2.0 (Report Builder 2.0) Goto www.microsoft.com.");
		return;
	}


}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton1Click(TObject *Sender)
{
    MetroListBoxItem6Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton2Click(TObject *Sender)
{
  MetroListBoxItem1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton3Click(TObject *Sender)
{
    MetroListBoxItem2Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem65Click(TObject *Sender)
{
	TFM_CustomerSearch01* FM_CustomerSearch01;
	Application->CreateForm(__classid(TFM_CustomerSearch01), &FM_CustomerSearch01);
	if (FM_CustomerSearch01 )
	{
					FM_CustomerSearch01->ShowModal();
					delete FM_CustomerSearch01;
	}


	if( GridViewForm->strCustomerAcct != "" )
	{

		TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
			if (Form)
			{
				strReportFileName = "CustomerTicketReport.rdl";
				strReportName = "Customer Ticket Report";
				strReportFilter = "FILE";
				GridViewForm->strDataSet = "INVOICE" ;
				//Form->Label3->Text = "Customer Listing Report";
				Form->ShowModal();
				delete Form;

			}
	}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem66Click(TObject *Sender)
{

  	TFM_CustomerSearch01* FM_CustomerSearch01;
	Application->CreateForm(__classid(TFM_CustomerSearch01), &FM_CustomerSearch01);
	if (FM_CustomerSearch01 )
	{
					FM_CustomerSearch01->ShowModal();
					delete FM_CustomerSearch01;
	}


	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerLocationReport.rdl";
			strReportName = "Customer Location Report";
			strReportFilter = "FILE";
			GridViewForm->strDataSet = "INVOICE" ;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem48Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketByUser.rdl";
			strReportName = "Ticket by User Report";
			strReportFilter = "FILE";
			strAdditionalFilter = "USER IS NOT NULL AND STATUS != 'V'";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem47Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketByRoute.rdl";
			strReportName = "Ticket by Route Summary";
			strReportFilter = "FILE";
				strAdditionalFilter = "ROUTE > 0 AND STATUS != 'V'";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem50Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			GridViewForm->strReportFileName = "ProductionReport.rdl";
			GridViewForm->strReportName = "Production Report";
			GridViewForm->strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";
			GridViewForm->strDataSet = "CASHBOXSALESSUMMARY";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem51Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TaxReport.rdl";
			strReportName = "TaxReport";
			strAdditionalFilter = "TAX <> 0 AND AMTPAID <> 0 AND STATUS != 'V'";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem53Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketProfit.rdl";
			strReportName = "Ticket Profit Report";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";
			GridViewForm->strDataSet = "INVOICE" ;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem64Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			GridViewForm->strReportFileName = "EndofDayReport.rdl";
			GridViewForm->strReportName = "End of Day Report";
			GridViewForm->strReportFilter = "FILE";
			GridViewForm->strDataSet = "CASHBOXSALESSUMMARY";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem62Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			GridViewForm->strReportFileName = "SalesSummaryReport.rdl";
			GridViewForm->strReportName = "Sales Summary Report";
			GridViewForm->strReportFilter = "FILE";
			GridViewForm->strDataSet = "INVOICESALESBYCLASS";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem63Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			GridViewForm->strReportFileName = "EndofDayReport.rdl";
			GridViewForm->strReportName = "End of Day Report";
			GridViewForm->strReportFilter = "FILE";
			GridViewForm->strDataSet = "CASHBOXSALESSUMMARYRANGE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem67Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SalesSummarybyDay.rdl";
			strReportName = "Sales Summary by Day";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem68Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CurrentInventory.rdl";
			strReportName = "Current Inventory";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->strAdditionalFilter = "STATUS = 'R' AND LOCATION IS NOT NULL";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem70Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "InventorybyDay.rdl";
			strReportName = "Inventory By Day";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS = 'R' AND LOCATION IS NOT NULL";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton4Click(TObject *Sender)
{

if(  CornerButton4->Enabled == false )
		  return;

	MenuItem108Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem71Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SalesSummarybyItem.rdl";
			strReportName = "Sales Summary by item Report";
			strReportFilter = "FILE";
			strDataSet = "SALESBYITEMVIEW";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem102Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SlotBySlotReport.rdl";
			strReportName = "Slot by Slot Report";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->strAdditionalFilter = "STATUS = 'R' AND LOCATION IS NOT NULL";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem103Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SlotbyNameReport.rdl";
			strReportName = "Slot by Name Report";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS = 'R' AND LOCATION IS NOT NULL";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem104Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SlotbySlottedReport.rdl";
			strReportName = "Slot by Date Slotted Report";
			GridViewForm->strAdditionalFilter = "STATUS = 'R' AND LOCATION IS NOT NULL";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem72Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerRankedbySales.rdl";
			strReportName = "Customer Ranked by Sales Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = "CAST(CAST(spent AS float) AS INT) > 500 AND ISACTIVE = 1 ";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem73Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerRankedTickets.rdl";
			strReportName = "Customer Ranked by Tickets Report";
			strReportFilter = "ALL";
				 GridViewForm->strAdditionalFilter = "CAST(CAST(TICKETS AS float) AS INT) > 100 AND ISACTIVE = 1 ";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem74Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "LoyaltyCustomers.rdl";
			strReportName = "Loyalty Customers Report";
			strReportFilter = "ALL";
			 GridViewForm->strAdditionalFilter = " Loyalty = '1' AND ISACTIVE = 1 ";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem75Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "AbsentCustomers.rdl";
			strReportName = "Absent Customers Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = "LASTTRANS < GETDATE() - 60 AND ISACTIVE = 1 ";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem76Click(TObject *Sender)
{

		 ADOCommand1->CommandText  = "UPDATE CUSTOMER SET PRIMEKEY = EMAIL where Store = "+ GridViewForm->strStoreNo;
	 ADOCommand1->Execute() ;



TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerEmailReport.rdl";
			strReportName = "Customer Email Report";

				GridViewForm->strAdditionalFilter = "PRIMEKEY IS NOT NULL AND ISACTIVE = 1 ";

			strReportFilter = "ALL";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem77Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerbyRoute.rdl";
			GridViewForm->strAdditionalFilter = "ROUTE IS NOT NULL AND ROUTE <> '0'";
			strReportName = "Customers by Route Report";
			strReportFilter = "ALL";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem78Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "DeliveryPickup.rdl";
			strReportName = "Delivery Pickup Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter =  "ROUTE IS NOT NULL AND ROUTE <> '0' And (ReqularRoute = 1 Or OneTimePickup = 1)";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem79Click(TObject *Sender)
{
			if(  GridViewForm->blnTransactionLogin )
			{

			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

			TNewCustomerEmailForm* NewCustomerEmailForm;
				Application->CreateForm(__classid(TNewCustomerEmailForm), &NewCustomerEmailForm);
				if (NewCustomerEmailForm )
				{
					NewCustomerEmailForm->ShowModal();
					delete NewCustomerEmailForm;
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem80Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "RouteDeliverySchedule.rdl";
			strReportName = "Route Delivery Schedule Report";
			strReportFilter = "FILE";
			strDataSet = "ROUTES";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem81Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "HotelListing.rdl";
			strReportName = "Hotel Listing Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = " CLHOTEL = '1'";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem82Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "HotelDelivery.rdl";
			strReportName = "Hotel Delivery Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = "ROUTE IS NOT NULL AND ROUTE <> '0' AND CLHOTEL = '1'";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem83Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "HotelListing.rdl";
			strReportName = "Hotel Listing Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = " CLHOTEL = '1'";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem84Click(TObject *Sender)
{
  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.pointofsalecloud.com\\packages.html";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem85Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.vivaldi2000.com/barcode.exe";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not connect to the Microsoft Web site!");
						return;
				   }



}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem69Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SalesSummarybyItem.rdl";
			strReportName = "Sales Summary by item Report";
			strReportFilter = "FILE";
			strDataSet = "SALESBYITEMVIEW";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem86Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SalesSummarybyUpcharge.rdl";
			strReportName = "Sales Summary by Upcharge Report";
			strReportFilter = "FILE";
			strDataSet = "ORDERS";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem87Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "DCItemReport.rdl";
			strReportName = "Price List Report";
			strReportFilter = "FILE";
			strDataSet = "DCITEM";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem88Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "UpCharge.rdl";
			strReportName = "Upcharge Report";
			strReportFilter = "FILE";
			strDataSet = "PRICELIST";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem89Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "PriceLevelList.rdl";
			strReportName = "Price Level List Report";
			strReportFilter = "FILE";
			strDataSet = "PRICELEVEL";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem91Click(TObject *Sender)
{

	GridViewForm->strQuestion = "Are you sure you wish to Run all AR Statements?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( GridViewForm->blnOK == true )
	{




	GridViewForm->strReportFileName = "ARStatementAll.rdl";
			GridViewForm->strReportName = "AR Statement Report";
			GridViewForm->strReportFilter = "";
			GridViewForm->strDataSet = "ARSTATEMENT" ;




		 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   if( GridViewForm->blnLocalDatabase == false) {

						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

				   } else {
					 	execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

				   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = GridViewForm->strStoreNo+ "  "+GridViewForm->strReportFileName+" 1 PREVIEW ARSTATEMENT ALL FALSE";

					if( GridViewForm->blnWinExec  )
					{
						if( GridViewForm->blnLocalDatabase  == false) {
							AnsiString strCommand =  "C:\\VIVALDI8\\ReportViewer.exe "+GridViewForm->strStoreNo  +" ARSTATEMENTALL.RDL 1 PREVIEW ARSTATEMENT ALL FALSE" ;
							WinExec(strCommand.c_str(), SW_NORMAL);
						}
						else
						{
							AnsiString strCommand = "C:\\VIVALDI8\\ReportViewerLocal.exe "+GridViewForm->strStoreNo  +" ARSTATEMENTALL.RDL 1 PREVIEW ARSTATEMENT ALL FALSE";
							WinExec( strCommand.c_str(), SW_NORMAL);
                        }
				   }
				   else
				   {
					   GridViewForm->strReportFilter = "";
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
	   }
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem92Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "ARInvoiceListing.rdl";
			strReportName = "AR Invoice Listing";
			strReportFilter = "FILE";
			strDataSet = "ARSTATEMENT";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem93Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerAccounts.rdl";
			strReportName = "Account Customers Report";
			GridViewForm->strDataSet = "CUSTOMER" ;
			strReportFilter = " Account=1";

			//Form->Label3->Text = "Customer Listing Report";
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem94Click(TObject *Sender)
{
		TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "QuickTicketReport.rdl";
			strReportName = "Quick Ticket Report";
			strReportFilter = "FILE";
			strAdditionalFilter = "STATUS = 'Q'";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem95Click(TObject *Sender)
{

				GridViewForm->strQuestion = "Are you absolutely sure you wish to reset all the YTD Customer Totals?";

				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
				if (Form )
				{
					Form->ShowModal();
					delete Form;
				}


				if( GridViewForm->blnOK == true )
				{


						ADOQuery2->Active = false;
						ADOQuery2->SQL->Clear();
						ADOQuery2->SQL->Text = "UPDATE CUSTOMER SET YTDTOTALS = '0', YTDTICKETS = '0' WHERE STORE = '"+GridViewForm->strStoreNo  +"'";
						ADOQuery2->ExecSQL();
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem96Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "BoxItemsLabels.rdl";
			strReportName = "Box Item Labels";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem97Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerLabels.rdl";
			strReportName = "Customer Labels";
			strReportFilter = "FILE";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem98Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "AbsentCustomerLabels.rdl";
			strReportName = "Absent Customer Labels";
			strReportFilter = "FILE";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem99Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "NewCustomerLabels.rdl";
			strReportName = "New Customer Labels";
			strReportFilter = "FILE";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem100Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "Top100CustomerLabels.rdl";
			strReportName = "Top 100 Customer Labels";
			strReportFilter = "FILE";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem61Click(TObject *Sender)
{
  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\Vivaldi8\\Vivaldi8BasicSystem.pdf";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::CornerButton5Click(TObject *Sender)
{



TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "PriceList.rdl";
			strReportName = "PriceList Report";
			strReportFilter = "FILE";
			strDataSet = "PRICELIST";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton6Click(TObject *Sender)
{
	TDashboardForm* DashboardForm;
				Application->CreateForm(__classid(TDashboardForm), &DashboardForm);
				if (DashboardForm )
				{
					DashboardForm->ShowModal();
					delete DashboardForm;

				

				}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem52Click(TObject *Sender)
{

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "PickedTicketReport.rdl";
			strReportName = "Picked Ticket Report";
			strReportFilter = "FILE";
			strAdditionalFilter = "(STATUS = 'P' OR STATUS = 'D')";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}



}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem123Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "VoidedTicketReport.rdl";
			strReportName = "Voided Ticket Report";
			strReportFilter = "FILE";
			strAdditionalFilter = "STATUS = 'V'";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem124Click(TObject *Sender)
{


   if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

	TRouteForm1* RouteForm1;
				Application->CreateForm(__classid(TRouteForm1), &RouteForm1);
				if (RouteForm1 )
				{
					RouteForm1->ShowModal();
					delete RouteForm1;
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem127Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "SubDCItemReport.rdl";
			strReportName = "Sub Item Report";
			strReportFilter = "FILE";
			strDataSet = "SUBDCITEM";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem126Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerbyRoute.rdl";
			GridViewForm->strAdditionalFilter = "ROUTE IS NOT NULL AND ROUTE <> '0'";
			strReportName = "Customers by Route Report";
			strReportFilter = "ALL";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem128Click(TObject *Sender)
{
				TColorsForm03* ColorsForm2;
				Application->CreateForm(__classid(TColorsForm03), &ColorsForm2);
				if (ColorsForm2 )
				{
					ColorsForm2->ShowModal();
					delete ColorsForm2;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MenuItem129Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketLocationReport.rdl";
			GridViewForm->strAdditionalFilter = "LOCATION IS NOT NULL AND STATUS != 'P' AND STATUS != 'V' AND STATUS != 'D' AND STATUS != 'N'";
			strReportName = "Ticket Location Report";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem120Click(TObject *Sender)
{

if( MetropolisUIListBoxItem13->Enabled == false )
		  return;
	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	TIssuesForm01* IssuesForm01;
				Application->CreateForm(__classid(TIssuesForm01), &IssuesForm01);
				if (IssuesForm01 )
				{
					IssuesForm01->ShowModal();
					delete IssuesForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem130Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.vivaldi2000.com/FreeVK.exe";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not download FreeVK.exe from Vivaldi. Search Google for this file!");
						return;
				   }
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem117Click(TObject *Sender)
{
   ShowMessage("About Vivaldi - Point of Sales System by Vivaldi Systems. Sales 760.524.2473  online support and sales at www.vivaldi2000.com");
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CornerButton7Click(TObject *Sender)
{
	if( GridViewForm->bln64Bit )
		WinExec("C:\\Program Files\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);


}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem125Click(TObject *Sender)
{
	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}
		TDeliveryForm01* DeliveryForm01;
		Application->CreateForm(__classid(TDeliveryForm01), &DeliveryForm01);
		if (DeliveryForm01 )
		{
			DeliveryForm01->ShowModal();
			delete DeliveryForm01;
		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem131Click(TObject *Sender)
{
			   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.microsoft.com/en-us/download/details.aspx?id=24085";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not Run ReportBuilder.msi . Install the Report Builder 2.0 under Help!");
						return;
				   }
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem109Click(TObject *Sender)
{

	GridViewForm->strQuestion = "Are you sure you wish to Run all AR Statements? (Next select the cut off date for your Statements)";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( GridViewForm->blnOK == true )
	{

			GridViewForm->strDateOut = GridViewForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));



	TCommonCustomForm *FM_DATEPICKERFORM = Application->GetDeviceForm(L"FM_DATEPICKER");
		if (FM_DATEPICKERFORM)
		{


			if( FM_DATEPICKERFORM->ShowModal() == mrOk )
			{

			}

			delete FM_DATEPICKERFORM;

		}

              	ADOQuery5->Active = false;
				ADOQuery5->SQL->Clear();
				ADOQuery5->SQL->Add("UPDATE STORE SET DATEOUTPARAM = '"+GridViewForm->strDateOut +"' where Store = '"+ GridViewForm->strStoreNo+ "'");
					ADOQuery5->ExecSQL();

			if( GridViewForm->strCustomerARStatement == "" )
			{
					GridViewForm->strReportFileName = "ARStatementAll.rdl";
			}
			else
			{
				 GridViewForm->strReportFileName = GridViewForm->strCustomerARStatement;
            }


			GridViewForm->strReportName = "AR Statement Report";
			GridViewForm->strReportFilter = "";
			GridViewForm->strDataSet = "ARSTATEMENT" ;



			SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   if( GridViewForm->blnLocalDatabase  == false) {

						execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewer.exe";

				   } else {
					 	execinfo.lpFile = L"C:\\VIVALDI8\\ReportViewerLocal.exe";

				   }
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = GridViewForm->strStoreNo+ "  "+GridViewForm->strReportFileName+" 1 PREVIEW ARSTATEMENT ALL FALSE";

					if( GridViewForm->blnWinExec  )
					{
						if( GridViewForm->blnLocalDatabase  == false) {
							AnsiString strCommand =  "C:\\VIVALDI8\\ReportViewer.exe "+GridViewForm->strStoreNo  +" "+GridViewForm->strReportFileName+" 1 PREVIEW ARSTATEMENT ALL FALSE" ;
							WinExec(strCommand.c_str(), SW_NORMAL);
						}
						else
						{
							AnsiString strCommand = "C:\\VIVALDI8\\ReportViewerLocal.exe "+GridViewForm->strStoreNo  +" "+GridViewForm->strReportFileName+" 1 PREVIEW ARSTATEMENT ALL FALSE";
							WinExec( strCommand.c_str(), SW_NORMAL);
						}
				   }
				   else
				   {
					   GridViewForm->strReportFilter = "";
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
	   }
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::SpeedButton1Click(TObject *Sender)
{
		ProgressBar1->Value = 1;


		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'P' OR STATUS = 'D') AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
		ADOQuery2->Active = true;


	  ProgressBarOverDue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label12->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		 ProgressBar1->Value = 2;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND CONVERT(VARCHAR(10),DATEIN,101) = CONVERT(VARCHAR(10),GETDATE(),101) AND AMT = 0";
		ADOQuery2->Active = true;


	  ProgressBarZero->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label13->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		 ProgressBar1->Value = 3;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarTicketInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label14->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		 ProgressBar1->Value = 4;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarItemsInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label15->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		 ProgressBar1->Value = 5;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
	ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'I' AND DATEOUT < GetDate()";
			ADOQuery2->Active = true;


	  ProgressBarTicketsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label16->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


	  ProgressBar1->Value = 6;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'I' AND DATEOUT < GetDate()";
	  ADOQuery2->Active = true;


	  ProgressBarItemsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label17->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 7;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'R'";
	  ADOQuery2->Active = true;


	  ProgressBarReady->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label18->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 8;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'Q'";
			ADOQuery2->Active = true;


	  ProgressBarQuick->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label19->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 9;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND CONVERT(VARCHAR(10),DATEIN,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
	  ADOQuery2->Active = true;


	  ProgressBarTransactions->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  Label20->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;
	  ProgressBar1->Value = 10;

      Label21->Text = "Updated: "+ DateTimeToStr(Now());

}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::Button1Click(TObject *Sender)
{
	ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'P' OR STATUS = 'D') AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
		ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button2Click(TObject *Sender)
{
			ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND CONVERT(VARCHAR(10),DATEIN,101) = CONVERT(VARCHAR(10),GETDATE(),101) AND AMT = 0";
		ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button3Click(TObject *Sender)
{
         	ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE  FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'I' OR STATUS = 'Q')";
			ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button4Click(TObject *Sender)
{
				ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button5Click(TObject *Sender)
{
			ADOQuery3->Active = false;
		ADOQuery3->SQL->Clear();
	ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'I' AND DATEOUT < GetDate()";
			ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button6Click(TObject *Sender)
{
			  ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'I' AND DATEOUT < GetDate()";
	  ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button7Click(TObject *Sender)
{
		  ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'R'";
	  ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button8Click(TObject *Sender)
{
	 ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
		ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND STATUS = 'Q'";
			ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Button9Click(TObject *Sender)
{
			 ADOQuery3->Active = false;
	  ADOQuery3->SQL->Clear();
	  ADOQuery3->SQL->Text = "SELECT ORDERNO,NAME,DATEIN,STATUS,AMT,STORE FROM INVOICE WHERE STORE = '"+GridViewForm->strStoreNo  +"' AND CONVERT(VARCHAR(10),DATEIN,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
	  ADOQuery3->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem116Click(TObject *Sender)
{
	  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"https://www.youtube.com/playlist?list=PLX1GlmodKukT5uXzcLu0mn2i4WZ1oEq98";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem136Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.vivaldi2000.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem137Click(TObject *Sender)
{
SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.x-charge.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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



void __fastcall TGridViewForm::Button10Click(TObject *Sender)
{
  GridViewForm->strDefaultEditTicketNumber = ADOQuery3->FieldByName("ORDERNO")->AsString;

  if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}
		GridViewForm->blnAccountCustomer = false;

		//	Application->CreateForm(__classid(TEditTicketForm03), &EditTicketForm03);
		TEditTicketForm03* EditTicketForm03;
				Application->CreateForm(__classid(TEditTicketForm03), &EditTicketForm03);
				if (EditTicketForm03 )
				{
					EditTicketForm03->ShowModal();
					delete EditTicketForm03;
				}


}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem138Click(TObject *Sender)
{
	//system( "cashdrawer.bat");
	WinExec("c:\\vivaldi8\\cashdrawer.bat", SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem139Click(TObject *Sender)
{
   system( "Copy c:\vivaldi8\tag.txt c:\vivaldi8\new.txt");
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem140Click(TObject *Sender)
{
	//system( "Copy c:\\vivaldi8\\TAG.TXT c:\\vivaldi8\\new.txt");
	//system( "c:\\vivaldi8\\CTEST.BAT");

   //	WinExec("http://www.microsoft.com/en-us/download/details.aspx?id=21622", SW_NORMAL);
		  //C:\Program Files (x86)\Notepad++

		   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.microsoft.com/en-us/download/details.aspx?id=21622";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
				   int iSize = strParam.WideCharBufSize();
				   wchar_t *wTemp = new wchar_t[iSize];
				   strParam.WideChar(wTemp, iSize);

				   execinfo.lpParameters =  wTemp;

				   execinfo.fMask = SEE_MASK_NOCLOSEPROCESS ;
				   execinfo.nShow = SW_NORMAL;


				   if(! ShellExecuteEx(&execinfo))
				   {
						ShowMessage("Could Not connect to the Microsoft Web site!");
						return;
				   }



}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem141Click(TObject *Sender)
{

	GridViewForm->blnAccountCustomer = false;


		TGarmentTagForm* GarmentTagForm;
				Application->CreateForm(__classid(TGarmentTagForm), &GarmentTagForm);
				if (GarmentTagForm )
				{
					GarmentTagForm->ShowModal();
					delete GarmentTagForm;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image2Click(TObject *Sender)
{
	TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();
					delete LoginForm02;

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
						if( blnEnableEnterprise ) {
					   Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

					}
					else
					{
						Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

					}
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem142Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "VIPCustomers.rdl";
			strReportName = "VIP Customers Report";
			strReportFilter = "ALL";
			 GridViewForm->strAdditionalFilter = " VIP = '1' AND ISACTIVE = 1 ";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem143Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "NewCustomers.rdl";
			strReportName = "New Customers Report";
			strReportFilter = "ALL";

			 GridViewForm->strAdditionalFilter = "CONVERT(VARCHAR(10),OPENDATE,101) =CONVERT(VARCHAR(10),GetDate(),101) AND ISACTIVE = 1 ";
			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image5Click(TObject *Sender)
{
TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();
					delete LoginForm02;

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
						if( blnEnableEnterprise ) {
					   Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Enterprise) User: "+ GridViewForm->strUserName;

					}
					else
					{
						Label1->Text = "Vivaldi Metro "+strVersionNumber+" - Dry Cleaning System - (Cloud) User: "+ GridViewForm->strUserName;

					}
				}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image3Click(TObject *Sender)
{
	if( GridViewForm->bln64Bit )
    	WinExec("C:\\Program Files\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image6Click(TObject *Sender)
{
	 // WinExec("http:\\PointOfSaleCloud.com", SW_NORMAL);
	  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.PointOfSaleCloud.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem144Click(TObject *Sender)
{
 //WinExec("http:\\PointOfSaleCloud.com", SW_NORMAL);
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.PointOfSaleCloud.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem145Click(TObject *Sender)
{
 //WinExec("http:\\PointOfSaleCloud.com", SW_NORMAL);
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.Cleanersupply.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem146Click(TObject *Sender)
{



      SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.wincalendar.com//calendar.html";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::ColorComboBox1Change(TObject *Sender)
{

if(   ColorComboBox1->Color != 0 )
{
	this->Fill->Color = ColorComboBox1->Color;
	iBackgroundColor  = ColorComboBox1->Color;


	//ADOQuery4->Active = false;
//ADOQuery4->SQL->Clear();
//ADOQuery4->SQL->Add("UPDATE STORE SET COLOR = '"+ FloatToStr(ColorComboBox1->Color) +"' where Store = '"+ GridViewForm->strStoreNo+ "'; Select Top 1 Store from store");
//ADOQuery4->Active = true;

	if( GridViewForm->strStoreNo != NULL && GridViewForm->strStoreNo != "" )
	{

	 ADOCommand1->CommandText  = "UPDATE STORE SET COLOR = '"+ FloatToStr(ColorComboBox1->Color) +"' where Store = "+ GridViewForm->strStoreNo;
	 ADOCommand1->Execute() ;

     }
 }


}
//---------------------------------------------------------------------------


void __fastcall TGridViewForm::MetropolisUIListBoxItem8Click(TObject *Sender)
{

if(  MetropolisUIListBoxItem8->Enabled == false )
		  return;


		TDeliveryForm01* DeliveryForm01;
		Application->CreateForm(__classid(TDeliveryForm01), &DeliveryForm01);
		if (DeliveryForm01 )
		{
			DeliveryForm01->ShowModal();
			delete DeliveryForm01;
		}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem7Click(TObject *Sender)
{

if(  MetropolisUIListBoxItem7->Enabled == false )
		  return;


		TAccountForm01* AccountForm01;
		Application->CreateForm(__classid(TAccountForm01), &AccountForm01);
		if (AccountForm01 )
		{
			AccountForm01->ShowModal();
			delete AccountForm01;
		}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem9Click(TObject *Sender)
{



if(  MetropolisUIListBoxItem9->Enabled == false )
		  return;

   //	Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
			TStoreForm01* StoreForm01;
				Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
				if (StoreForm01 )
				{
					StoreForm01->ShowModal();
					delete StoreForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem10Click(TObject *Sender)
{

if(  MetropolisUIListBoxItem10->Enabled == false )
		  return;
		GridViewForm->blnAccountCustomer = false;


		TGarmentTagForm* GarmentTagForm;
				Application->CreateForm(__classid(TGarmentTagForm), &GarmentTagForm);
				if (GarmentTagForm )
				{
					GarmentTagForm->ShowModal();
					delete GarmentTagForm;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem11Click(TObject *Sender)
{

if(  MetropolisUIListBoxItem11->Enabled == false )
		  return;




	TRouteForm1* RouteForm1;
				Application->CreateForm(__classid(TRouteForm1), &RouteForm1);
				if (RouteForm1 )
				{
					RouteForm1->ShowModal();
					delete RouteForm1;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem14Click(TObject *Sender)
{


  if(  MetropolisUIListBoxItem14->Enabled == false )
		  return;
		 //	Application->CreateForm(__classid(TDCItemForm01), &DCItemForm01);
		TDCItemForm01* DCItemForm01;
				Application->CreateForm(__classid(TDCItemForm01), &DCItemForm01);
				if (DCItemForm01 )
				{
					DCItemForm01->ShowModal();
					delete DCItemForm01;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem12Click(TObject *Sender)
{
 if(  MetropolisUIListBoxItem12->Enabled == false )
		  return;
	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	THotelForm* HotelForm;
				Application->CreateForm(__classid(THotelForm), &HotelForm);
				if (HotelForm )
				{
					HotelForm->ShowModal();
					delete HotelForm;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MetropolisUIListBoxItem13Click(TObject *Sender)
{

if( MetropolisUIListBoxItem13->Enabled == false )
		  return;

	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	TIssuesForm01* IssuesForm01;
				Application->CreateForm(__classid(TIssuesForm01), &IssuesForm01);
				if (IssuesForm01 )
				{
					IssuesForm01->ShowModal();
					delete IssuesForm01;
				}


	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem106Click(TObject *Sender)
{
if(  MetropolisUIListBoxItem12->Enabled == false )
		  return;
	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	THotelForm* HotelForm;
				Application->CreateForm(__classid(THotelForm), &HotelForm);
				if (HotelForm )
				{
					HotelForm->ShowModal();
					delete HotelForm;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem105Click(TObject *Sender)
{

if( MetropolisUIListBoxItem13->Enabled == false )
		  return;


	 //Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
	TIssuesForm01* IssuesForm01;
				Application->CreateForm(__classid(TIssuesForm01), &IssuesForm01);
				if (IssuesForm01 )
				{
					IssuesForm01->ShowModal();
					delete IssuesForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem107Click(TObject *Sender)
{
if(  MetropolisUIListBoxItem12->Enabled == false )
		  return;

	TWholesaleForm* WholesaleForm;
				Application->CreateForm(__classid(TWholesaleForm), &WholesaleForm);
				if (WholesaleForm )
				{
					WholesaleForm->ShowModal();
					delete WholesaleForm;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem134Click(TObject *Sender)
{


	TGiftCardForm01* GiftCardForm01;
				Application->CreateForm(__classid(TGiftCardForm01), &GiftCardForm01);
				if (GiftCardForm01 )
				{
					GiftCardForm01->ShowModal();
					delete GiftCardForm01;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem147Click(TObject *Sender)
{


	TSendEmailReminderForm* SendEmailReminderForm;
				Application->CreateForm(__classid(TSendEmailReminderForm), &SendEmailReminderForm);
				if (SendEmailReminderForm )
				{
					SendEmailReminderForm->ShowModal();
					delete SendEmailReminderForm;
				}

	if(  GridViewForm->blnTransactionLogin )
			{
			  //Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}
			}

}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem113Click(TObject *Sender)
{


 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://notepad-plus-plus.org/download/v6.4.5.html";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem115Click(TObject *Sender)
{
	  SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\Vivaldi8\\Vivaldi8System.pdf";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::Image4Click(TObject *Sender)
{

        SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\Vivaldi8\\Vivaldi8BasicSystem.pdf";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem132Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "DeclinedReport.rdl";
			GridViewForm->strAdditionalFilter = " STATUS = 'N'";
			strReportName = "Ticket Location Report";
			strReportFilter = "FILE";
			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem135Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "TicketSummary.rdl";
			strReportName = "Ticket Summary";
			strReportFilter = "FILE";
			GridViewForm->strAdditionalFilter = "STATUS != 'V'";

			strDataSet = "INVOICE";
			GridViewForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem150Click(TObject *Sender)
{
SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.MailChimp.com";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG
				   AnsiString strParam = "";
				   GridViewForm->strReportFilter = "";
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

void __fastcall TGridViewForm::MenuItem151Click(TObject *Sender)
{
	if(  GridViewForm->blnTransactionLogin )
			{

			   TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal(); UpdateMenu();
					delete LoginForm02;
				}
			}

			TNewCustomerEmailForm* NewCustomerEmailForm;
				Application->CreateForm(__classid(TNewCustomerEmailForm), &NewCustomerEmailForm);
				if (NewCustomerEmailForm )
				{
					NewCustomerEmailForm->ShowModal();
					delete NewCustomerEmailForm;
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::GroupLayout1Click(TObject *Sender)
{
  TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();
					UpdateMenu();
					delete LoginForm02;
				}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::Image7Click(TObject *Sender)
{
	if( GridViewForm->bln64Bit )
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem152Click(TObject *Sender)
{
	if( GridViewForm->bln64Bit )
		WinExec("SetupWinCalendarV4.exe", SW_NORMAL);
	else
		WinExec("SetupWinCalendarV4.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::CalendarEdit1Change(TObject *Sender)
{
 GridViewForm->strDateOut = CalendarEdit1->Text;
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem153Click(TObject *Sender)
{
TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerRankedbySales.rdl";
			strReportName = "Customer YTD Sales Report over $500";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = "CAST(CAST(YTDTOTAL AS float) AS INT) > 500 AND ISACTIVE = 1 ";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem154Click(TObject *Sender)
{
		 TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "AllCustomerRankedbySales.rdl";
			strReportName = "All Customer Ranked by Sales Report";
			strReportFilter = "ALL";
			GridViewForm->strAdditionalFilter = "CAST(CAST(YTDTOTAL AS float) AS INT) > 0 AND ISACTIVE = 1 ";

			strDataSet = "CUSTOMER";
			GridViewForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem155Click(TObject *Sender)
{
	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			strReportFileName = "CustomerReport.rdl";
			strReportName = "Customer Listing Report";
			strReportFilter = " ISACTIVE = 0 or ISACTIVE IS NULL ";      //3304776517
			GridViewForm->strDataSet = "CUSTOMER" ;
			//Form->Label3->Text = "Customer Listing Report";
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TGridViewForm::MenuItem156Click(TObject *Sender)
{

ShowMessage("This utility will check the store customer database for duplicat customer account numbers and delete them.  Certain reports can not print with duplicate accounts in the same store.  Please be patient while checking");

		ADOQuery6->Active = false;
	ADOQuery6->SQL->Clear();
	ADOQuery6->SQL->Add("select max(id) AS ID from customer c1 where c1.STORE = '"+GridViewForm->strStoreNo  +"'  and 1 < (select count(id) from customer where c1.store = customer.store and c1.acct = customer.acct)");
	ADOQuery6->Active = true;

		if( ADOQuery6->Eof == false  && ADOQuery6->FieldByName("ID")->AsString != "")
		{
				GridViewForm->strQuestion = "Duplicate Customer Account Numbers have been found.  Delivery reports will not work unless we remove the duplicates.  May we do this now?";

				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
					if (Form )
					{
						Form->ShowModal();
						delete Form;
					}


				if( GridViewForm->blnOK == true )
				{
						ADOQuery6->First() ;
						while( ADOQuery6->Eof == false )
						{

								ADOQuery7->Active = false;
								ADOQuery7->SQL->Clear();
								ADOQuery7->SQL->Text = "DELETE FROM CUSTOMER WHERE ID = '"+ADOQuery6->FieldByName("ID")->AsString+"' AND STORE = '"+GridViewForm->strStoreNo  +"'";
								ADOQuery7->ExecSQL();
								Caption = "Removing "+ ADOQuery6->FieldByName("ID")->AsString;

								ADOQuery6->MoveBy(1);

						}
						ShowMessage("Duplicate Customers have been Removed!");

				}


		}
		else
		  ShowMessage("No Duplicate Customer were found!");


		ADOQuery6->Active = false;
}
//---------------------------------------------------------------------------

