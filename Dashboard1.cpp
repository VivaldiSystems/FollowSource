//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MainMenu.h"
#include "Dashboard1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TDashboardForm *DashboardForm;
//---------------------------------------------------------------------------
__fastcall TDashboardForm::TDashboardForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDashboardForm::Button10Click(TObject *Sender)
{
	ProgressBar1->Value = 1;

	AnsiString strCurrentStore = "0";

	if( CheckBox1->IsChecked)
	{
		strCurrentStore = MainMenuForm->strEnterprise;
	 }  else {

		strCurrentStore = ADOQuery1->FieldByName("STORE")->AsString;
     }
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
		  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'P' OR STATUS = 'D') AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY')";
	   }

		if( MainMenuForm->strDataBaseType == "SQLSERVER" )  {
		   ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'P' OR STATUS = 'D') AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101)";
		}

		ADOQuery2->Active = true;


	  ProgressBarPickedUp->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  PickupCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		 ProgressBar1->Value = 2;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY') AND AMT = 0";
		}

		if( MainMenuForm->strDataBaseType == "SQLSERVER" )  {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101) AND AMT = 0";
	}


		ADOQuery2->Active = true;


	  ProgressBarZero->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ZeroCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		 ProgressBar1->Value = 3;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarTicketInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ProcessedCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

		 ProgressBar1->Value = 4;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND (STATUS = 'I' OR STATUS = 'Q')";
		ADOQuery2->Active = true;


	  ProgressBarItemsInprocess->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ItemsProcessedCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


		 ProgressBar1->Value = 5;
		ADOQuery2->Active = false;
		ADOQuery2->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < Date()";
		}

		if( MainMenuForm->strDataBaseType == "SQLSERVER" )
		 {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < GetDate()";
		 }
			ADOQuery2->Active = true;


	  ProgressBarTicketsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  OverDueCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;


	  ProgressBar1->Value = 6;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < Date()";
	}

		if( MainMenuForm->strDataBaseType == "SQLSERVER" )
		 {
				ADOQuery2->SQL->Text = "SELECT SUM(QTY) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'I' AND DATEOUT < GetDate()";
	}



	  ADOQuery2->Active = true;


	  ProgressBarItemsOverdue->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ItemsOverDueCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 7;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'R'";
	  ADOQuery2->Active = true;


	  ProgressBarReady->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  ReadyCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 8;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND STATUS = 'Q'";
			ADOQuery2->Active = true;


	  ProgressBarQuick->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  QuickCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;

	  ProgressBar1->Value = 9;
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT(DATE(),'MM/DD/YYYY')";
		}

		if( MainMenuForm->strDataBaseType == "SQLSERVER" )
		 {
					ADOQuery2->SQL->Text = "SELECT COUNT(ID) AS COUNTID FROM INVOICE WHERE STORE = "+MainMenuForm->strStoreNo  +" AND CONVERT(VARCHAR(10),DATEOUT,101) = CONVERT(VARCHAR(10),GETDATE(),101";
		}




	  ADOQuery2->Active = true;


	  ProgressBarTransactions->Value =  ADOQuery2->FieldByName("COUNTID")->AsFloat;
	  TodayCount->Text = ADOQuery2->FieldByName("COUNTID")->AsString;

	  ADOQuery2->Active = false;
	  ProgressBar1->Value = 10;



}
//---------------------------------------------------------------------------
void __fastcall TDashboardForm::FormShow(TObject *Sender)
{
	 ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  if( MainMenuForm->blnEnableEnterprise )
		  ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strEnterprise +") Order by STORE";
	  else
		 ADOQuery1->SQL->Text = "Select * from STORE where STORE IN ("+MainMenuForm->strStoreNo +") Order by STORE";

	  ADOQuery1->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TDashboardForm::ListBox1Change(TObject *Sender)
{
	int iLBI = ListBox1->ItemIndex;


	ADOQuery1->First();
	ADOQuery1->MoveBy(iLBI);


	if( ! ADOQuery1->Eof )
	{

	   Button10Click(Sender);
    }
}
//---------------------------------------------------------------------------
void __fastcall TDashboardForm::Button11Click(TObject *Sender)
{

ADOQuery1->Close();
ADOQuery2->Close();

this->Close();

}
//---------------------------------------------------------------------------
void __fastcall TDashboardForm::Button12Click(TObject *Sender)
{
   AnsiString strOldStoreNo = MainMenuForm->strStoreNo ;
   MainMenuForm->strStoreNo = ADOQuery1->FieldByName("Store")->AsString;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "TicketListingSummary.rdl";
			MainMenuForm->strReportName = "Ticket Listing Summary";
			MainMenuForm->strReportFilter = "FILE";
			MainMenuForm->strAdditionalFilter = "STATUS != 'V'";

			MainMenuForm->strDataSet = "INVOICE";
			MainMenuForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}


		MainMenuForm->strStoreNo =  strOldStoreNo;

}
//---------------------------------------------------------------------------

void __fastcall TDashboardForm::Button13Click(TObject *Sender)
{

   AnsiString strOldStoreNo = MainMenuForm->strStoreNo ;
   MainMenuForm->strStoreNo = ADOQuery1->FieldByName("Store")->AsString;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "SalesSummaryReport.rdl";
			MainMenuForm->strReportName = "Sales Summary Report";
			MainMenuForm->strReportFilter = "FILE";
			MainMenuForm->strDataSet = "INVOICESALESBYCLASS";
			MainMenuForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}

			MainMenuForm->strStoreNo =  strOldStoreNo;
}
//---------------------------------------------------------------------------

void __fastcall TDashboardForm::Button14Click(TObject *Sender)
{
	AnsiString strOldStoreNo = MainMenuForm->strStoreNo ;
   MainMenuForm->strStoreNo = ADOQuery1->FieldByName("Store")->AsString;

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "EndofDayReport.rdl";
			MainMenuForm->strReportName = "End of Day Report";
			MainMenuForm->strReportFilter = "FILE";
			MainMenuForm->strDataSet = "CASHBOXSALESSUMMARY";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}

			MainMenuForm->strStoreNo =  strOldStoreNo;
}
//---------------------------------------------------------------------------

void __fastcall TDashboardForm::Button15Click(TObject *Sender)
{
    AnsiString strOldStoreNo = MainMenuForm->strStoreNo ;
   MainMenuForm->strStoreNo = ADOQuery1->FieldByName("Store")->AsString;


	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "TicketSummary.rdl";
			MainMenuForm->strReportName = "Ticket Summary";
			MainMenuForm->strReportFilter = "FILE";
			MainMenuForm->strAdditionalFilter = "STATUS != 'V'";

			MainMenuForm->strDataSet = "INVOICE";
			MainMenuForm->blnDateOut = false;
			Form->ShowModal();
			delete Form;

		}

		MainMenuForm->strStoreNo =  strOldStoreNo;
}
//---------------------------------------------------------------------------

void __fastcall TDashboardForm::SpeedButton4Click(TObject *Sender)
{
  ADOQuery1->Close();
  ADOQuery2->Close();

  this->Close();
}
//---------------------------------------------------------------------------

