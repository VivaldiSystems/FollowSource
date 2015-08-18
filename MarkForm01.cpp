//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "MarkForm01.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TMarkForm *MarkForm;
//---------------------------------------------------------------------------
__fastcall TMarkForm::TMarkForm(TComponent* Owner)
	: TForm(Owner)
{






}
//---------------------------------------------------------------------------
void __fastcall TMarkForm::SpeedButton4Click(TObject *Sender)
{
 ADOQuery2->Close();
   ADOQuery1->Close();
   ADOQuery3->Close();
   ADOQuery4->Close();
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TMarkForm::SpeedButton1Click(TObject *Sender)
{
   //	SaveChangesIListBoxItem->Enabled = true;

      if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();


	ADOQuery1->Insert() ;
	ADOQuery1->FieldByName("Store")->AsString = MainMenuForm->strStoreNo;


}
//---------------------------------------------------------------------------

void __fastcall TMarkForm::SpeedButton3Click(TObject *Sender)
{
	   if(  ADOQuery1->State == dsEdit  || ADOQuery1->State == dsInsert )
		 ADOQuery1->Post();

     ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------

void __fastcall TMarkForm::SpeedButton2Click(TObject *Sender)
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
		ADOQuery1->Delete();

	}
}
//---------------------------------------------------------------------------

void __fastcall TMarkForm::Button3Click(TObject *Sender)
{

 Label4->Text = "Searching for Ticket : "+Edit1->Text;

if( Edit1->Text != "" )
{

 ADOQuery1->Active = false;
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("Select  ID, ORDERNO, ACCT, NAME, DATEIN, LOCATION, STATUS, STORE, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND ORDERNO = "+ Edit1->Text   +" Order by ORDERNO");
ADOQuery1->Active = true;
}
else
{
  ShowMessage("Please Enter a Ticket Number First");
  Edit2->Text = "";
  Edit1->Text = "";

  Edit1->SetFocus();
   return;
}

 if (ADOQuery1->Eof)
 {
	   //	ShowMessage("Ticket Number Not Found!");
		Edit2->Text = "";
		Memo1->Lines->Add(Edit1->Text+" Ticket # Not Found");
		Edit1->Text = "";
		Edit1->SetFocus();
		return;
 }

  Edit1->Text = "";

if( ADOQuery1->FieldByName("STATUS")->AsString == "V"  )
{

	//ShowMessage("This Ticket is currently Voided and cannot be marked Ready!");
		Memo1->Lines->Add(Edit1->Text+" Already Voided");

	return;
}


if( ADOQuery1->FieldByName("STATUS")->AsString == "P"  )
{

   //	ShowMessage("This Ticket currently Picked Up and cannot be marked Ready!");
	   Memo1->Lines->Add(Edit1->Text+" Already Picked Up");
	return;
}

if( ADOQuery1->FieldByName("STATUS")->AsString == "D"  )
{

   //	ShowMessage("This Ticket currently Delivered and cannot be marked Ready!");
	   Memo1->Lines->Add(Edit1->Text+" Already Delivered");
	return;
}




ADOQuery1->Edit();

if( CheckBox4->IsChecked == false && CheckBox5->IsChecked == false )
{
          ADOQuery1->FieldByName("STATUS")->AsString = "R";
}

if( CheckBox4->IsChecked == true  )
{
		   ADOQuery1->FieldByName("LOCATION")->AsString = "PLANT";
}
else if( CheckBox5->IsChecked == true  )
{
		   ADOQuery1->FieldByName("LOCATION")->AsString = "ALTERATION";
}


ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
ADOQuery1->Post();

ADOQuery3->Open();
 ADOQuery3->Insert();
	   ADOQuery3->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
if( CheckBox4->IsChecked == true  )
{
		   ADOQuery3->FieldByName("DESCRIPTION")->AsString = "Assigned to Plant ";
}
else if( CheckBox5->IsChecked == true  )
{
		   ADOQuery3->FieldByName("DESCRIPTION")->AsString = "Assigned to Alteration ";
}
else
{
   ADOQuery3->FieldByName("DESCRIPTION")->AsString = "Marked Ready ";
}
		   ADOQuery3->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery3->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
		   ADOQuery3->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
		   ADOQuery3->FieldByName("ORDERNO")->AsString = Edit1->Text;
		   ADOQuery3->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	   ADOQuery3->Post();
	   ADOQuery3->Close();


Label3->Text = "Ticket # "+ Edit1->Text+" Marked Ready";
 Memo1->Lines->Add(Label3->Text);

if( CheckBox1->IsChecked && CheckBox4->IsChecked == false && CheckBox5->IsChecked == false)
{

ADOQuery4->Active = false;
ADOQuery4->SQL->Clear();
ADOQuery4->SQL->Add("Select EMAIL,NAME,ROUTE from CUSTOMER where Store = "+ MainMenuForm->strStoreNo+ "  AND ACCT = '"+ ADOQuery1->FieldByName("ACCT")->AsString  +"'");
ADOQuery4->Active = true;

AnsiString semail =  ADOQuery4->FieldByName("EMAIL")->AsString;
AnsiString sname =  ADOQuery4->FieldByName("NAME")->AsString;
AnsiString sroute =  ADOQuery4->FieldByName("ROUTE")->AsString;
AnsiString sOrderNo =  Edit1->Text;

 if( ADOQuery4->Eof == false && semail.AnsiPos("@") != 0 && MainMenuForm->blnSendReadyEmail && (sroute == "" || sroute == "0" ))
{
		 Label4->Text = "Sending Email now... Please Wait";
			SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";

   AnsiString strParam;

	 if( CheckBox2->IsChecked )
	 {
   strParam =  "-to "+ semail +"  -body \" "+"Your Ticket "+Edit1->Text+" is Ready and will be delivery from "+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Your Ticket is ready to be Picked up at "+MainMenuForm->strStoreName +"\" ";
	  }
	  else
	  {
    strParam =  "-to "+ semail +"  -body \" "+"Your Ticket "+Edit1->Text+" is Ready to pickup at "+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Your Ticket is ready to be Picked up at "+MainMenuForm->strStoreName +"\" ";

      }

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
	 Label4->Text = "Email Sent to: "+semail;
}

}
ADOQuery1->Active = true;
ADOQuery4->Active = false;
Edit2->Text = "";
Edit1->Text = "";

  Button3->Default = true;
//Button4->Default = true;
Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMarkForm::FormShow(TObject *Sender)
{
  Button3->Default = true;

  Edit1->SetFocus();
}
//---------------------------------------------------------------------------

