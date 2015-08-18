//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include <System.UITypes.hpp>

#include "System.Win.Registry.hpp"
#include <shellapi.h>
#include <inifiles.hpp>

#include <stdio.h>
#include <math.h>
#include <dos.h>
#include "MainMenu.h"
#include "ClassForm01.h"
#include "PickupForm.h"
#include "MarkForm01.h"
#include "GarmentTag.h"
#include "CustomerForm2.h"
#include "HotelForm2.h"
#include "IssuesForm2.h"
#include "StoreForm2.h"
#include "RouteForm2.h"
#include "ColorForm01.h"
#include "DeliveryForm2.h"
#include "CouponForm01.h"
#include "UserForm01.h"
#include "LoginForm.h"
#include "Dashboard1.h"
#include "AssignLocation1.h"
#include "LoginForm2.h"
#include "AccountForm2.h"
#include "WriteTicket.h"
#include "UpchargeForm2.h"
#include "InventoryForm1.h"
#include "CashDrawerForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMainMenuForm *MainMenuForm;
//---------------------------------------------------------------------------
__fastcall TMainMenuForm::TMainMenuForm(TComponent* Owner)
	: TForm(Owner)
{

strVersionNumber = "15.05.07";

}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::Panel1Click(TObject *Sender)
{


	TWriteTicketForm01* WriteTicketForm01;
				Application->CreateForm(__classid(TWriteTicketForm01), &WriteTicketForm01);
				if (WriteTicketForm01 )
				{
					WriteTicketForm01->ShowModal();
					delete WriteTicketForm01;

				}

			if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem20Click(TObject *Sender)
{
	TClassForm* ClassForm;
				Application->CreateForm(__classid(TClassForm), &ClassForm);
				if (ClassForm )
				{
					ClassForm->ShowModal();
					delete ClassForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Image5Click(TObject *Sender)
{
 TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();  UpdateMenu();
					delete LoginForm02;
				}

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";

					Label4->Text = "User: "+MainMenuForm->strUserName;


                      UpdateMenu();
			   MainMenuForm->strDateOut = DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10);

			   int ispace = MainMenuForm->strDateOut.Pos(" ");
			   if( ispace > 0 )
					 MainMenuForm->strDateOut = MainMenuForm->strDateOut.SubString(1,ispace-1);

			     CalendarEdit1->Date =  StrToDate( MainMenuForm->strDateOut );


			

}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::FormShow(TObject *Sender)
{

   blnDateOut = true;
	   blnTicketClosed = false;
	   blnEnableTopMenu = false;
	   blnUseEuropeanFormat = false;
	   blnDisableDates  = false;
	   blnReturnTendered = false;
	   blnDateIn = true;
	   strLastSearch = "";

	   WindowState = 2;

	   TIniFile& tfile = *new TIniFile("C:\\FOLLOW\\FOLLOW.INI");

		AnsiString strConnection = tfile.ReadString("DATABASE","CONNECTIONSTRING","");
		AnsiString strDatabase = tfile.ReadString("DATABASE","NAME","");
		strDataBaseType  = tfile.ReadString("DATABASE","TYPE","MSACCESS");

		strDataBaseType = strDataBaseType.UpperCase();

		blnLocalDatabase = false;

		if (strConnection != "" )
		{
			   ADOConnection1->Close();
			   ADOConnection1->ConnectionString = strConnection;
			   ADOConnection1->Open();
			   Label5->Text = "Database: "+strDataBaseType+"  - "+strDatabase;
			   blnLocalDatabase = true;
		}
		else
		{
			   ADOConnection1->Close();
			   ADOConnection1->ConnectionString = "Provider=SQLOLEDB.1;Password=foll2164;Persist Security Info=True;User ID=DB_53817_vivaldis_user;Initial Catalog=DB_53817_vivaldis;Data Source=s09.winhost.com";
			   ADOConnection1->Open();
			   Label5->Text = "Database: Follow Cloud Server";
			   blnLocalDatabase = true;
        }



	        TLoginForm01* LoginForm01;
				Application->CreateForm(__classid(TLoginForm01), &LoginForm01);
				if (LoginForm01 )
				{
					LoginForm01->ShowModal();
					delete LoginForm01;

					if( MainMenuForm->strUserName == "" )
					{
                        Application->Terminate();
                    }

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";

					Label4->Text = "User: "+MainMenuForm->strUserName;


                      UpdateMenu();
			   MainMenuForm->strDateOut = DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10);

			   int ispace = MainMenuForm->strDateOut.Pos(" ");
			   if( ispace > 0 )
				 MainMenuForm->strDateOut = MainMenuForm->strDateOut.SubString(1,ispace-1);

			   CalendarEdit1->Date =  StrToDate( MainMenuForm->strDateOut );


				}
				else
				{
					Application->Terminate();
				}

                	if(  MainMenuForm->blnTransactionLogin )
			{

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
 void __fastcall TMainMenuForm::UpdateMenu()
{

	TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";
	if( blnEnableEnterprise ) {
		Label1->Text = "Follow POS - Dry Cleaning System - (Enterprise)";

	}
	else
	{
		Label1->Text = "Follow POS - Dry Cleaning System - (Cloud)";

	}

               if(  MainMenuForm->blnEnableTopMenu )
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





		 if( MainMenuForm->blnAllowEditAccess )
		  {
				MetropolisUIListBoxItem4->Enabled = true;
				MetropolisUIListBoxItem4->Visible = true;
					Panel4->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem4->Enabled = false;
				MetropolisUIListBoxItem4->Visible = false;
				Panel4->Visible = false;
		  }

		  if(MainMenuForm->blnAllowCustomerAccess )
		   {

				MetropolisUIListBoxItem13->Visible = true;
				Panel3->Visible = true;
				MetroListBoxItem2->Enabled = true;
				MetroListBoxItem2->Visible = true;
				//CornerButton3->Enabled = true;
				MenuItem19->Enabled = true;
				Panel15->Visible = true;
		  }
		  else
		  {
			   MetropolisUIListBoxItem13->Visible = false;
				MetroListBoxItem2->Enabled = false;
				MetroListBoxItem2->Visible = false;
				//CornerButton3->Enabled = false;
				MenuItem19->Enabled = false;
				Panel3->Visible = false;
					Panel15->Visible = false;
		  }

		  if(MainMenuForm->blnAllowWriteAccess )
		   {
				MetroListBoxItem6->Enabled = true;
				MetropolisUIListBoxItem10->Visible = true;
				MetroListBoxItem6->Visible = true;
					//CornerButton1->Enabled = true;
					MenuItem9->Enabled = true;
					Panel1->Visible = true;
		  }
		  else
		  {
				MetroListBoxItem6->Enabled = false;
				MetroListBoxItem6->Visible = false;
				MetropolisUIListBoxItem10->Visible = false;
					//CornerButton1->Enabled = false;
						MenuItem9->Enabled = false;
						Panel1->Visible = false;
		  }

		 if( MainMenuForm->blnAllowPickupAccess )
		   {
				MetroListBoxItem1->Enabled = true;
				MetroListBoxItem1->Visible = true;
					//CornerButton2->Enabled = true;
						Panel2->Visible = true;
		  }
		  else
		  {
				MetroListBoxItem1->Enabled = false;
				MetroListBoxItem1->Visible = false;
					//CornerButton2->Enabled = false;
					Panel2->Visible = false;
		  }

		 if( MainMenuForm->blnAllowXChargeAccess )
		   {
				MetropolisUIListBoxItem6->Enabled = true;
				MetropolisUIListBoxItem6->Visible = true;
				Panel10->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem6->Enabled = false;
				MetropolisUIListBoxItem6->Visible = false;
				Panel10->Visible = false;
		  }

		 if( MainMenuForm->blnAllowTimeCardAccess)
		 {
				MetropolisUIListBoxItem5->Enabled = true;
					MetropolisUIListBoxItem5->Visible = true;
					Panel9->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem5->Enabled = false;
					MetropolisUIListBoxItem5->Visible = false;
					Panel9->Visible = false;
		  }

		  if(MainMenuForm->blnAllowInventoryAccess )
		  {
				MetroListBoxItem7->Enabled = true;
					MetroListBoxItem7->Visible = true;
						Panel8->Visible = true;
		  }
		  else
		  {
				MetroListBoxItem7->Enabled = false;
					MetroListBoxItem7->Visible = false;
					Panel8->Visible = false;
		  }

		  if(MainMenuForm->blnAllowAccountAccess )
		  {
				//CornerButton4->Enabled = true;
				MenuItem28->Enabled = true;
				MetropolisUIListBoxItem7->Enabled = true;
				MetropolisUIListBoxItem7->Visible = true;
				Panel11->Visible = true;
		  }
		  else
		  {
				//CornerButton4->Enabled = false;
				MenuItem28->Enabled = false;
				MetropolisUIListBoxItem7->Enabled = false;
				MetropolisUIListBoxItem7->Visible = false;
				Panel11->Visible = false;
		  }




		  if(MainMenuForm->blnAllowStoreAccess )
		  {
				MetropolisUIListBoxItem9->Enabled = true;
				MetropolisUIListBoxItem9->Visible = true;
				Panel13->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem9->Enabled = false;
				MetropolisUIListBoxItem9->Visible = false;
				Panel13->Visible = false;
		  }

		  if(MainMenuForm->blnAllowHotelAccess )
		  {
				MetropolisUIListBoxItem12->Enabled = true;
				MetropolisUIListBoxItem12->Visible = true;
				Panel19->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem12->Enabled = false;
				MetropolisUIListBoxItem12->Visible = false;
				Panel19->Visible = false;
		  }

		  if(MainMenuForm->blnAllowDeliveryAccess )
		  {
				MetropolisUIListBoxItem8->Enabled = true;
				MetropolisUIListBoxItem8->Visible = true;
					Panel12->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem8->Enabled = false;
				MetropolisUIListBoxItem8->Visible = false;
					Panel12->Visible = false;
		  }

		  if(MainMenuForm->blnAllowRouteAccess )
		  {
				MetropolisUIListBoxItem11->Enabled = true;
				MetropolisUIListBoxItem11->Visible = true;
				Panel18->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem11->Enabled = false;
				MetropolisUIListBoxItem11->Visible = false;
				Panel18->Visible = false;
		  }


		  if(MainMenuForm->blnAllowCashDrawerAccess )
		  {
				MetropolisUIListBoxItem3->Enabled = true;
				MetropolisUIListBoxItem3->Visible = true;
						Panel4->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem3->Enabled = false;
				MetropolisUIListBoxItem3->Visible = false;
				Panel4->Visible = false;
		  }




		 if( MainMenuForm->blnAllowAssignLocationAccess)
		  {
				MetropolisUIListBoxItem2->Enabled = true;
					MetropolisUIListBoxItem1->Enabled = true;
						MetropolisUIListBoxItem2->Visible = true;
					MetropolisUIListBoxItem1->Visible = true;



						Panel4->Visible = true;
					Panel5->Visible = true;

		  }
		  else
		  {
				MetropolisUIListBoxItem2->Enabled = false;
					MetropolisUIListBoxItem1->Enabled = false;
						MetropolisUIListBoxItem2->Visible = false;
					MetropolisUIListBoxItem1->Visible = false;


						Panel4->Visible = false;
					Panel5->Visible = false;
		  }

		   if(MainMenuForm->blnAllowPriceListAccess )
		  {
				MetropolisUIListBoxItem14->Enabled = true;
				MetropolisUIListBoxItem14->Visible = true;
				MenuItem21->Enabled = true;
				MenuItem46->Enabled = true;
				MenuItem20->Enabled = true;
				Panel14->Visible = true;
		  }
		  else
		  {
				MetropolisUIListBoxItem14->Enabled = false;
				MetropolisUIListBoxItem14->Visible = false;
					MenuItem21->Enabled = false;
				MenuItem46->Enabled = false;
				MenuItem20->Enabled = false;
				Panel14->Visible = false;
		  }



}

//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::Image1Click(TObject *Sender)
{
	Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::MenuItem26Click(TObject *Sender)
{
	TUserForm* UserForm;
				Application->CreateForm(__classid(TUserForm), &UserForm);
				if (UserForm)
				{
					UserForm->ShowModal();
					delete UserForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Image7Click(TObject *Sender)
{
	if( MainMenuForm->bln64Bit )
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\WinCalendar V4\\WinCalendar.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::Image3Click(TObject *Sender)
{
	if( MainMenuForm->bln64Bit )
    	WinExec("C:\\Program Files\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
	else
		WinExec("C:\\Program Files (x86)\\Microsoft Calculator Plus\\CalcPlus.exe", SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::Image4Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\Follow\\FollowBasicSystem.pdf";
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
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::Image6Click(TObject *Sender)
{
 SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http:\\\\www.FollowPOS.com";
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
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::CalendarEdit1Change(TObject *Sender)
{
 MainMenuForm->strDateOut = CalendarEdit1->Text;
}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::SpeedButton4Click(TObject *Sender)
{
   //	ProgressBar1->Value = 1;


		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( strDataBaseType == "MSACCESS" ) {
		  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'P' OR STATUS = 'D') AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY')";
	   }

		if( strDataBaseType == "SQLSERVER" )  {
		   ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'P' OR STATUS = 'D') AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
		}

		ADOQuery2->Active = true;


	  ProgressBarPickedUp->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  PickupCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		// ProgressBar1->Value = 2;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY') AND AMT = 0";
		}

		if( strDataBaseType == "SQLSERVER" )  {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101) AND AMT = 0";
	}


		ADOQuery2->Active = true;


	  ProgressBarZero->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ZeroCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		 //ProgressBar1->Value = 3;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarTicketInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ProcessedCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		// ProgressBar1->Value = 4;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarItemsInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ItemsProcessedCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		// ProgressBar1->Value = 5;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < Date()";
		}

		if( strDataBaseType == "SQLSERVER" )
		 {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < GetDate()";
		 }
			ADOQuery2->Active = true;


	  ProgressBarTicketsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  OverDueCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


	 // ProgressBar1->Value = 6;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
		if( strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < Date()";
	}

		if( strDataBaseType == "SQLSERVER" )
		 {
				ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < GetDate()";
	}



	  ADOQuery2->Active = true;


	  ProgressBarItemsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ItemsOverDueCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	 // ProgressBar1->Value = 7;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'R'";
	  ADOQuery2->Active = true;


	  ProgressBarReady->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ReadyCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  //ProgressBar1->Value = 8;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'Q'";
			ADOQuery2->Active = true;


	  ProgressBarQuick->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  QuickCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	 // ProgressBar1->Value = 9;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
		if( strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY')";
		}

		if( strDataBaseType == "SQLSERVER" )
		 {
					ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101";
		}




	  ADOQuery2->Active = true;


	  ProgressBarTransactions->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  TodayCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;
	  //ProgressBar1->Value = 10;


}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::MenuItem128Click(TObject *Sender)
{
	TColorForm* ColorForm;
				Application->CreateForm(__classid(TColorForm), &ColorForm);
				if (ColorForm )
				{
					ColorForm->ShowModal();
					delete ColorForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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


void __fastcall TMainMenuForm::Panel13Click(TObject *Sender)
{


	TStoreForm01* StoreForm01;
				Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
				if (StoreForm01 )
				{
					StoreForm01->ShowModal();
					delete StoreForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem32Click(TObject *Sender)
{
			TCouponForm* CouponForm;
				Application->CreateForm(__classid(TCouponForm), &CouponForm);
				if (CouponForm )
				{
					CouponForm->ShowModal();
					delete CouponForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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


void __fastcall TMainMenuForm::Panel4Click(TObject *Sender)
{
	TMarkForm* MarkForm;
				Application->CreateForm(__classid(TMarkForm), &MarkForm);
				if (MarkForm )
				{
					MarkForm->ShowModal();
					delete MarkForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::CornerButton6Click(TObject *Sender)
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

void __fastcall TMainMenuForm::Panel5Click(TObject *Sender)
{
	TAssignLocationForm* AssignLocationForm;
				Application->CreateForm(__classid(TAssignLocationForm), &AssignLocationForm);
				if (AssignLocationForm )
				{
					AssignLocationForm->ShowModal();
					delete AssignLocationForm;
				}


					if(  MainMenuForm->blnTransactionLogin )
			{

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
 AnsiString __fastcall TMainMenuForm::ConvertDate(AnsiString argDateString)
{
	AnsiString strReturnDate;


	if( MainMenuForm->blnUseEuropeanFormat )
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
void __fastcall TMainMenuForm::Panel11Click(TObject *Sender)
{
	TAccountForm01* AccountForm01;
		Application->CreateForm(__classid(TAccountForm01), &AccountForm01);
		if (AccountForm01 )
		{
			AccountForm01->ShowModal();
			delete AccountForm01;
		}

		if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel8Click(TObject *Sender)
{
	TInventoryForm* InventoryForm;
				Application->CreateForm(__classid(TInventoryForm), &InventoryForm);
				if (InventoryForm)
				{
					InventoryForm->ShowModal();
					delete InventoryForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem8Click(TObject *Sender)
{

			TLoginForm02* LoginForm02;
				Application->CreateForm(__classid(TLoginForm02), &LoginForm02);
				if (LoginForm02 )
				{
					LoginForm02->ShowModal();
					delete LoginForm02;

					if( MainMenuForm->strUserName == "" )
					{
                        Application->Terminate();
                    }

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";

					Label4->Text = "User: "+MainMenuForm->strUserName;


                      UpdateMenu();
			   MainMenuForm->strDateOut = DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10);

			   int ispace = MainMenuForm->strDateOut.Pos(" ");
			   if( ispace > 0 )
				 MainMenuForm->strDateOut = MainMenuForm->strDateOut.SubString(1,ispace-1);

			   CalendarEdit1->Date =  StrToDate( MainMenuForm->strDateOut );


				}
				else
				{
					Application->Terminate();
				}


}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::MenuItem6Click(TObject *Sender)
{

	        TLoginForm01* LoginForm01;
				Application->CreateForm(__classid(TLoginForm01), &LoginForm01);
				if (LoginForm01 )
				{
					LoginForm01->ShowModal();
					delete LoginForm01;

					if( MainMenuForm->strUserName == "" )
					{
                        Application->Terminate();
                    }

					TitleLabel1->Text = strStoreName+" "+strCityState+" ("+strStoreNo+")";

					Label4->Text = "User: "+MainMenuForm->strUserName;


                      UpdateMenu();
			   MainMenuForm->strDateOut = DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10);

			   int ispace = MainMenuForm->strDateOut.Pos(" ");
			   if( ispace > 0 )
				 MainMenuForm->strDateOut = MainMenuForm->strDateOut.SubString(1,ispace-1);

			   CalendarEdit1->Date =  StrToDate( MainMenuForm->strDateOut );


				}
				else
				{
					Application->Terminate();
				}


}
//---------------------------------------------------------------------------

void __fastcall TMainMenuForm::MenuItem7Click(TObject *Sender)
{
    	Application->Terminate();
}
//---------------------------------------------------------------------------


void __fastcall TMainMenuForm::MenuItem18Click(TObject *Sender)
{
	TStoreForm01* StoreForm01;
				Application->CreateForm(__classid(TStoreForm01), &StoreForm01);
				if (StoreForm01 )
				{
					StoreForm01->ShowModal();
					delete StoreForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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



void __fastcall TMainMenuForm::Panel6Click(TObject *Sender)
{
	TCashDrawerForm* CashDrawerForm;
				Application->CreateForm(__classid(TCashDrawerForm), &CashDrawerForm);
				if (CashDrawerForm )
				{
					CashDrawerForm->ShowModal();
					delete CashDrawerForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem122Click(TObject *Sender)
{
      SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"C:\\Follow\\OpenReport\\OPENRPT.EXE";
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
						ShowMessage("Could not open C:\\Follow\\OpenReport\\OPENRPT.EXE!");
						return;
				   }
}
//---------------------------------------------------------------------------


void __fastcall TMainMenuForm::CornerButton4Click(TObject *Sender)
{
	TAccountForm01* AccountForm01;
		Application->CreateForm(__classid(TAccountForm01), &AccountForm01);
		if (AccountForm01 )
		{
			AccountForm01->ShowModal();
			delete AccountForm01;
		}

		if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel12Click(TObject *Sender)
{
  TDeliveryForm01* DeliveryForm01;
				Application->CreateForm(__classid(TDeliveryForm01), &DeliveryForm01);
				if (DeliveryForm01 )
				{
					DeliveryForm01->ShowModal(); UpdateMenu();
					delete DeliveryForm01;
				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem46Click(TObject *Sender)
{
	TUpchargeForm03* UpchargeForm03;
				Application->CreateForm(__classid(TUpchargeForm03), &UpchargeForm03);
				if (UpchargeForm03 )
				{
					UpchargeForm03->ShowModal();
					delete UpchargeForm03;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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


void __fastcall TMainMenuForm::Panel15Click(TObject *Sender)
{
	TIssuesForm01* IssuesForm01;
				Application->CreateForm(__classid(TIssuesForm01), &IssuesForm01);
				if (IssuesForm01 )
				{
					IssuesForm01->ShowModal();
					delete IssuesForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel19Click(TObject *Sender)
{
	THotelForm* HotelForm;
				Application->CreateForm(__classid(THotelForm), &HotelForm);
				if (HotelForm )
				{
					HotelForm->ShowModal();
					delete HotelForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem13Click(TObject *Sender)
{
     	TAssignLocationForm* AssignLocationForm;
				Application->CreateForm(__classid(TAssignLocationForm), &AssignLocationForm);
				if (AssignLocationForm )
				{
					AssignLocationForm->ShowModal();
					delete AssignLocationForm;
				}


					if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem14Click(TObject *Sender)
{
     	TMarkForm* MarkForm;
				Application->CreateForm(__classid(TMarkForm), &MarkForm);
				if (MarkForm )
				{
					MarkForm->ShowModal();
					delete MarkForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem25Click(TObject *Sender)
{
       	TCashDrawerForm* CashDrawerForm;
				Application->CreateForm(__classid(TCashDrawerForm), &CashDrawerForm);
				if (CashDrawerForm )
				{
					CashDrawerForm->ShowModal();
					delete CashDrawerForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem125Click(TObject *Sender)
{
        TDeliveryForm01* DeliveryForm01;
				Application->CreateForm(__classid(TDeliveryForm01), &DeliveryForm01);
				if (DeliveryForm01 )
				{
					DeliveryForm01->ShowModal(); UpdateMenu();
					delete DeliveryForm01;
				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem108Click(TObject *Sender)
{
      TAccountForm01* AccountForm01;
		Application->CreateForm(__classid(TAccountForm01), &AccountForm01);
		if (AccountForm01 )
		{
			AccountForm01->ShowModal();
			delete AccountForm01;
		}

		if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem39Click(TObject *Sender)
{
       	TInventoryForm* InventoryForm;
				Application->CreateForm(__classid(TInventoryForm), &InventoryForm);
				if (InventoryForm)
				{
					InventoryForm->ShowModal();
					delete InventoryForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem105Click(TObject *Sender)
{
       	TIssuesForm01* IssuesForm01;
				Application->CreateForm(__classid(TIssuesForm01), &IssuesForm01);
				if (IssuesForm01 )
				{
					IssuesForm01->ShowModal();
					delete IssuesForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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


void __fastcall TMainMenuForm::MenuItem106Click(TObject *Sender)
{
		THotelForm* HotelForm;
				Application->CreateForm(__classid(THotelForm), &HotelForm);
				if (HotelForm )
				{
					HotelForm->ShowModal();
					delete HotelForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel17Click(TObject *Sender)
{
		TGarmentTagForm* GarmentTagForm;
				Application->CreateForm(__classid(TGarmentTagForm), &GarmentTagForm);
				if (GarmentTagForm )
				{
					GarmentTagForm->ShowModal();
					delete GarmentTagForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem141Click(TObject *Sender)
{
	TGarmentTagForm* GarmentTagForm;
				Application->CreateForm(__classid(TGarmentTagForm), &GarmentTagForm);
				if (GarmentTagForm )
				{
					GarmentTagForm->ShowModal();
					delete GarmentTagForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel3Click(TObject *Sender)
{
		TCustomerForm01* CustomerForm01;
				Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
				if (CustomerForm01 )
				{
					CustomerForm01->ShowModal();
					delete CustomerForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem19Click(TObject *Sender)
{
		TCustomerForm01* CustomerForm01;
				Application->CreateForm(__classid(TCustomerForm01), &CustomerForm01);
				if (CustomerForm01 )
				{
					CustomerForm01->ShowModal();
					delete CustomerForm01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::Panel2Click(TObject *Sender)
{
		TPickupWindow01* PickupWindow01;
				Application->CreateForm(__classid(TPickupWindow01), &PickupWindow01);
				if (PickupWindow01 )
				{
					PickupWindow01->ShowModal();
					delete PickupWindow01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::CornerButton2Click(TObject *Sender)
{
   		TPickupWindow01* PickupWindow01;
				Application->CreateForm(__classid(TPickupWindow01), &PickupWindow01);
				if (PickupWindow01 )
				{
					PickupWindow01->ShowModal();
					delete PickupWindow01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

void __fastcall TMainMenuForm::MenuItem10Click(TObject *Sender)
{
		TPickupWindow01* PickupWindow01;
				Application->CreateForm(__classid(TPickupWindow01), &PickupWindow01);
				if (PickupWindow01 )
				{
					PickupWindow01->ShowModal();
					delete PickupWindow01;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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




void __fastcall TMainMenuForm::Panel9Click(TObject *Sender)
{


SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\TimeCard Manager Basic\\TCMBasic.exe";

   AnsiString strParam = ""; //MainMenuForm->strStoreNo+ " "+ MainMenuForm->strReportFileName+" "+MainMenuForm->strReportFilter;
   MainMenuForm->strReportFilter = "";
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

void __fastcall TMainMenuForm::MetropolisUIListBoxItem6Click(TObject *Sender)
{

 SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\Program Files\\X-CHARGE\\XCHARGE.EXE";

   AnsiString strParam = ""; //MainMenuForm->strStoreNo+ " "+ MainMenuForm->strReportFileName+" "+MainMenuForm->strReportFilter;
   MainMenuForm->strReportFilter = "";
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

void __fastcall TMainMenuForm::Panel10Click(TObject *Sender)
{

 SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\Program Files\\X-CHARGE\\XCHARGE.EXE";

   AnsiString strParam = ""; //MainMenuForm->strStoreNo+ " "+ MainMenuForm->strReportFileName+" "+MainMenuForm->strReportFilter;
   MainMenuForm->strReportFilter = "";
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

void __fastcall TMainMenuForm::Panel18Click(TObject *Sender)
{
	TRouteForm1* RouteForm;
				Application->CreateForm(__classid(TRouteForm1), &RouteForm);
				if (RouteForm )
				{
					RouteForm->ShowModal();
					delete RouteForm;

				}
						if(  MainMenuForm->blnTransactionLogin )
			{

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

