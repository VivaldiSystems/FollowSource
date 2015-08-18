//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <shellapi.h>
#include <inifiles.hpp>
#include "MainMenu.h"
#include "CashDrawerForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TCashDrawerForm *CashDrawerForm;
//---------------------------------------------------------------------------
__fastcall TCashDrawerForm::TCashDrawerForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCashDrawerForm::Button3Click(TObject *Sender)
{

   MainMenuForm->blnOK = false;
   MainMenuForm->strQuestion = "Would you like to Z out the Drawer for the Selected Client!";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK )
	{
	  if( MainMenuForm->blnUseCashDrawer )
	  {

        WinExec("c:\\vivaldi8\\cashdrawer.bat", SW_HIDE);
   }


		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
		   ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = '"+ComboEdit1->Text+"'  AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"','MM/DD/YYYY') Order by DATEOUT");
		}
		else
		{
		   ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = '"+ComboEdit1->Text+"'  AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date) Order by DATEOUT");
		}


		ADOQuery1->Active = true;

		ADOQuery1->First();

		while( ADOQuery1->Eof == false )
		{
			if( ADOQuery1->FieldByName("STATUS")->AsString != "CLOSED" )
			{
					ADOQuery1->Edit();
					ADOQuery1->FieldByName("STATUS")->AsString = "CLOSED";
					ADOQuery1->Post();

			}
			ADOQuery1->MoveBy(1);

		}
	}

	if( CheckBox1->IsChecked )
{

if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' ,'MM/DD/YYYY')  Order by DATEOUT");
		}
		else
		{
         		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");
		}
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"','MM/DD/YYYY')  Order by DATEOUT");
		 }
		 else
		 {
          	ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");
		 }


		ADOQuery1->Active = true;


   }
}
else
{

   if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"','MM/DD/YYYY')  AND STATUS = 'OPEN' Order by DATEOUT");
		}
		else
		{
			ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  AND STATUS = 'OPEN' Order by DATEOUT");
		}
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND FORMAT(DATEOUT,'MM/DD/YYYY') = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"','MM/DD/YYYY')   AND STATUS = 'OPEN' Order by DATEOUT");
		}
		else
		{
			ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)   AND STATUS = 'OPEN' Order by DATEOUT");
		}
		ADOQuery1->Active = true;


   }


}

}
//---------------------------------------------------------------------------
void __fastcall TCashDrawerForm::Button5Click(TObject *Sender)
{


	if( Edit1->Enabled )
	{

	   ADOQuery1->Insert();
	   ADOQuery1->FieldByName("SLAVE")->AsString = "1";
	   if (strType == "ADJUSTMENT" )
	   {

			ADOQuery1->FieldByName("AMTPAID")->AsString = Edit1->Text;
		   ADOQuery1->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery1->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
		   ADOQuery1->FieldByName("PAYMENTTYPE")->AsString = strType;
		   ADOQuery1->FieldByName("SLAVE")->AsString = ComboEdit1->Text;
	   }
	   else
	   {
		   ADOQuery1->FieldByName("STARTINGCASH")->AsString = Edit1->Text;
			ADOQuery1->FieldByName("AMTPAID")->AsString = Edit1->Text;
		   ADOQuery1->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery1->FieldByName("DATEOUT")->AsString = DateTimeToStr(Now());
		   ADOQuery1->FieldByName("PAYMENTTYPE")->AsString = strType;
		   ADOQuery1->FieldByName("SLAVE")->AsString = ComboEdit1->Text;
	   }
	   ADOQuery1->Post();

	   Edit1->Enabled = false;

	}
     Edit1->Text = "";
   //Button5->Enabled = false;
   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
   {
		 ADOQuery1->Post();
		 ADOQuery1->Close();
		 ADOQuery1->Open();
   }

}
//---------------------------------------------------------------------------
void __fastcall TCashDrawerForm::Button2Click(TObject *Sender)
{
	TCommonCustomForm *FormLogin = Application->GetDeviceForm(L"LoginUserView");
		if (FormLogin)
		{
			FormLogin->ShowModal();
		
			delete FormLogin;

		}


           Grid1->ReadOnly = false;
		   //Button5->Enabled = true;
		   Button8->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TCashDrawerForm::Button1Click(TObject *Sender)
{
   this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::FormShow(TObject *Sender)
{

	CalendarEdit1->Text = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		AnsiString strDate ;
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
		  strDate = "Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = 1 AND FORMAT(DATEOUT,'MM/DD/YYYY') = FORMAT('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"','MM/DD/YYYY') AND STATUS <> 'CLOSED' Order by DATEOUT";
		}
		else
		{
             strDate = "Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '1' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date) AND STATUS != 'CLOSED' Order by DATEOUT";

        }
		ADOQuery1->SQL->Add(strDate);
			ADOQuery1->Active = true;
		//this->Fill->Color = MainMenuForm->iBackgroundColor ;

}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::ComboEdit1Change(TObject *Sender)
{

    // ComboEdit2->Text = "All";

   if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND convert(varchar(10),dateout,101) = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' Order by DATEOUT");
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND convert(varchar(10),dateout,101) = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' Order by DATEOUT");
		ADOQuery1->Active = true;


   }

}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::Button6Click(TObject *Sender)
{
 if( MainMenuForm->blnUseCashDrawer )
	  {
 WinExec("c:\\vivaldi8\\cashdrawer.bat", SW_HIDE);

     }
		Edit1->Enabled = true;
		ShowMessage("Enter Starting Cash then press Save");
		Edit1->SetFocus();
		Label2->Text = "Starting: ";
		strType =  "STARTINGCASH";
	   //	Button5->Enabled = true;

}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::ComboEdit2Change(TObject *Sender)
{
   if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND convert(varchar(10),dateout,101) = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' Order by DATEOUT");
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND convert(varchar(10),dateout,101) = '"+MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' Order by DATEOUT");
		ADOQuery1->Active = true;


   }
}
//---------------------------------------------------------------------------


void __fastcall TCashDrawerForm::CalendarEdit1Change(TObject *Sender)
{
if( CheckBox1->IsChecked )
{

if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			 ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"'  Order by DATEOUT");
		}
		else
		{
         	ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");
		}
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
		ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"'  Order by DATEOUT");
		}
		else
		{
          	ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");

        }
		ADOQuery1->Active = true;


   }
}
else
{

   if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
			ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"'  AND STATUS = 'OPEN' Order by DATEOUT");
		}
		else
		{
          	ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  AND STATUS = 'OPEN' Order by DATEOUT");
		}
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		if( MainMenuForm->strDataBaseType == "MSACCESS" ) {
		   ADOQuery1->SQL->Add("Select *,FORMAT(DATEOUT,'HH:MM:SS') AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = "+ MainMenuForm->strStoreNo+ " AND SLAVE = "+ComboEdit1->Text+" AND FORMAT(DATEOUT,'MM/DD/YYYY') = '"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"'   AND STATUS = 'OPEN' Order by DATEOUT");
		}
		else
		{
		   ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)   AND STATUS = 'OPEN' Order by DATEOUT");

        }
		ADOQuery1->Active = true;


   }


}

}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::Button7Click(TObject *Sender)
{

  if( MainMenuForm->blnUseCashDrawer )
	  {
 WinExec("c:\\vivaldi8\\cashdrawer.bat", SW_HIDE);
   }
	Edit1->Enabled = true;
		ShowMessage("Enter Adjustment in the Adjustment field then press Save");
		Edit1->SetFocus();
		Label2->Text = "Adjustment: ";
		strType =  "ADJUSTMENT";
	   //	Button5->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::Button4Click(TObject *Sender)
{
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
}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::MenuItem1Click(TObject *Sender)
{


	WinExec("c:\\vivaldi8\\cashdrawer.bat", SW_HIDE);
}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::CheckBox1Change(TObject *Sender)
{
if( CheckBox1->IsChecked )
{

if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  Order by DATEOUT");
		ADOQuery1->Active = true;


   }
}
else
{

   if( ComboEdit2->Text == "ALL" )
   {

		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)  AND STATUS = 'OPEN' Order by DATEOUT");
		ADOQuery1->Active = true;
   }
   else
   {
		ADOQuery1->Active = false;
		ADOQuery1->SQL->Clear();
		ADOQuery1->SQL->Add("Select *,CONVERT(TIME(0),Dateout) AS HourMinuteSecond from CASHBOX where PAYMENTTYPE = '"+ ComboEdit2->Text +"' AND StoreNO = '"+ MainMenuForm->strStoreNo+ "' AND SLAVE = '"+ComboEdit1->Text+"' AND cast(dateout as date) = cast('"+ MainMenuForm->ConvertDate(CalendarEdit1->Text)+"' as date)   AND STATUS = 'OPEN' Order by DATEOUT");
		ADOQuery1->Active = true;


   }


}
}
//---------------------------------------------------------------------------

void __fastcall TCashDrawerForm::Button8Click(TObject *Sender)
{


 if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
   {
		 ADOQuery1->Post();
		 ADOQuery1->Close();
		 ADOQuery1->Open();
   }

    	MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Record?";

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

