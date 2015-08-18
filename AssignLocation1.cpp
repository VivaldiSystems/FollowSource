//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
#include "MainMenu.h"

#include "AssignLocation1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TAssignLocationForm *AssignLocationForm;
//---------------------------------------------------------------------------
__fastcall TAssignLocationForm::TAssignLocationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAssignLocationForm::Button1Click(TObject *Sender)
{

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
ADOQuery1->FieldByName("LOCATION")->AsString = Edit2->Text;

if( CheckBox2->IsChecked == false )
   ADOQuery1->FieldByName("STATUS")->AsString = "R";


ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
ADOQuery1->Post();

ADOQuery3->Open();
 ADOQuery3->Insert();
	   ADOQuery3->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;

		   ADOQuery3->FieldByName("DESCRIPTION")->AsString = "Assign Loc: "+ Edit2->Text; ;
		   ADOQuery3->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
		   ADOQuery3->FieldByName("EVENTDATE")->AsString = DateTimeToStr(Now());
		   ADOQuery3->FieldByName("USERID")->AsString = MainMenuForm->strUserID;;
		   ADOQuery3->FieldByName("ORDERNO")->AsString = Edit1->Text;
		   ADOQuery3->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	   ADOQuery3->Post();
	   ADOQuery3->Close();

 

Label3->Text = "Ticket # "+ Edit1->Text + " Assign to "+Edit2->Text;

Memo1->Lines->Add(Label3->Text);


Edit2->Text = "";
Edit1->Text = "";
Edit1->SetFocus();

Button1->Default = false;
Button4->Default = true;


if( CheckBox1->IsChecked )
{

ADOQuery4->Active = false;
ADOQuery4->SQL->Clear();
ADOQuery4->SQL->Add("Select EMAIL,NAME,ROUTE from CUSTOMER where Store = '"+ MainMenuForm->strStoreNo+ "'  AND ACCT = '"+ ADOQuery1->FieldByName("ACCT")->AsString  +"'");
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

	strParam =  "-to "+ semail +"  -body \" "+"Your Ticket "+Edit1->Text+" is Ready to pickup at "+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Your Ticket is ready to be Picked up at "+MainMenuForm->strStoreName +"\" ";



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

  ADOQuery4->Active = false;




}
//---------------------------------------------------------------------------

void __fastcall TAssignLocationForm::Button2Click(TObject *Sender)
{
 ADOQuery2->Close();
   ADOQuery1->Close();
  Close();
}
//---------------------------------------------------------------------------



void __fastcall TAssignLocationForm::Button3Click(TObject *Sender)
{
if( CheckBox2->IsChecked == false )
  {
ADOQuery1->Edit();

ADOQuery1->FieldByName("STATUS")->AsString = "R";
ADOQuery1->Post();
  }


if( CheckBox1->IsChecked )
{

ADOQuery4->Active = false;
ADOQuery4->SQL->Clear();
ADOQuery4->SQL->Add("Select EMAIL,NAME from CUSTOMER where Store = '"+ MainMenuForm->strStoreNo+ "'  AND ACCT = '"+ ADOQuery1->FieldByName("ACCT")->AsString  +"'");
ADOQuery4->Active = true;

AnsiString semail =  ADOQuery4->FieldByName("EMAIL")->AsString;
AnsiString sname =  ADOQuery4->FieldByName("NAME")->AsString;
AnsiString sOrderNo =  Edit1->Text;

 if( ADOQuery4->Eof == false && semail.AnsiPos("@") != 0 && MainMenuForm->blnSendReadyEmail)
{
		 Label4->Text = "Sending Email now... Please Wait";
			SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";

   AnsiString strParam;


   strParam =  "-to "+ semail +"  -body \" "+"Your Ticket "+Edit1->Text+" is Ready to pickup at "+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Your Ticket is ready to be Picked up at "+MainMenuForm->strStoreName +"\" ";



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

  ADOQuery4->Active = false;




Edit2->Text = "";
Edit1->Text = "";
Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAssignLocationForm::FormShow(TObject *Sender)
{

if( MainMenuForm->blnSendReadyEmail)
{

 CheckBox1->IsChecked = true;
}

  Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAssignLocationForm::Button4Click(TObject *Sender)
{

if( Edit1->Text != "" )
{

 ADOQuery1->Active = false;
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("Select   ID, ORDERNO, ACCT, NAME, DATEIN,DATEOUT,ROUTE,AMT,AMTPAID,QTY, LOCATION, STATUS, STORE, INVENTORYDATE from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "'  AND ORDERNO = '"+ Edit1->Text   +"' Order by ORDERNO");
ADOQuery1->Active = true;
}
else
{
  //ShowMessage("Please Enter a Ticket Number First");
  Edit1->Text = "";
  	Edit1->SetFocus();
   return;
}

 if (ADOQuery1->Eof) {
	 //ShowMessage("Ticket Number Not Found!");
	 Edit1->Text = "";
	 Memo1->Lines->Add(Edit1->Text+" no Ticket # Found in this Store!");
		Edit1->SetFocus();
	 return;
 }


 if( ADOQuery1->FieldByName("STATUS")->AsString == "V"  )
{

   //	ShowMessage("This Ticket is currently Voided and cannot be marked Ready!");
	Edit1->Text = "";
	Memo1->Lines->Add(Edit1->Text+" Already Voided");
		Edit1->SetFocus();
	return;
}
 if( ADOQuery1->FieldByName("STATUS")->AsString == "R"  )
{

   //	ShowMessage("This Ticket is currently Ready and in Location "+ADOQuery1->FieldByName("LOCATION")->AsString+ ". You can reassign that location if you wish.");
	Memo1->Lines->Add(Edit1->Text+" Already Marked Ready");
}

if( ADOQuery1->FieldByName("STATUS")->AsString == "P"  )
{

	//ShowMessage("This Ticket is currently Picked Up and cannot be marked Ready!");
	Edit1->Text = "";
	Memo1->Lines->Add(Edit1->Text+" Already Picked Up!");
	Edit1->SetFocus();
	return;
}

if( ADOQuery1->FieldByName("STATUS")->AsString == "D"  )
{

	//ShowMessage("This Ticket is currently Delivered and cannot be marked Ready!");
	Edit1->Text = "";
	Memo1->Lines->Add(Edit1->Text+" Already Delivered");
	return;
}

  ADOQuery2->Active = false;
  ADOQuery2->SQL->Clear();
  ADOQuery2->SQL->Add("Select   ID, ORDERNO, ACCT, NAME, DATEIN,DATEOUT,ROUTE,AMT,AMTPAID,QTY, LOCATION, STATUS, STORE, INVENTORYDATE from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "'  AND ACCT = '"+ ADOQuery1->FieldByName("ACCT")->AsString  +"' AND STATUS = 'R'  Order by ORDERNO");
  ADOQuery2->Active = true;

 Label4->Text = "Enter a Location";

Button1->Default = true;
Button4->Default = false;
Edit2->SetFocus();
}
//---------------------------------------------------------------------------




void __fastcall TAssignLocationForm::Button5Click(TObject *Sender)
{

if(ADOQuery1->Active == false || ADOQuery1->FieldByName("ORDERNO")->AsString != Edit1->Text )
{
ADOQuery1->Active = false;
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("Select   ID, ORDERNO, ACCT, NAME, DATEIN,DATEOUT,ROUTE,AMT,AMTPAID,QTY, LOCATION, STATUS, STORE, INVENTORYDATE from INVOICE where Store = '"+ MainMenuForm->strStoreNo+ "'  AND ORDERNO = '"+ Edit1->Text   +"' Order by ORDERNO");
ADOQuery1->Active = true;
  }

  if( ADOQuery1->FieldByName("ORDERNO")->AsString != Edit1->Text )
  {
	  ShowMessage("Ticket Not Found");
	  return;
  }

ADOQuery1->Edit();
ADOQuery1->FieldByName("LOCATION")->AsString = "PLANT";

ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
ADOQuery1->Post();

	Memo1->Lines->Add(Edit1->Text+" Ticket Assigned to Plant");
                    Button1->Default = false;
Button4->Default = true;
Edit2->Text = "";
Edit1->Text = "";
Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAssignLocationForm::Button6Click(TObject *Sender)
{
if(ADOQuery1->Active == false || ADOQuery1->FieldByName("ORDERNO")->AsString != Edit1->Text )
{
ADOQuery1->Active = false;
ADOQuery1->SQL->Clear();
ADOQuery1->SQL->Add("Select   ID, ORDERNO, ACCT, NAME, DATEIN,DATEOUT,ROUTE,AMT,AMTPAID,QTY, LOCATION, STATUS, STORE, INVENTORYDATE from INVOICE where Store = "+ MainMenuForm->strStoreNo+ "  AND ORDERNO = '"+ Edit1->Text   +"' Order by ORDERNO");
ADOQuery1->Active = true;
  }

  if( ADOQuery1->FieldByName("ORDERNO")->AsString != Edit1->Text )
  {
	  ShowMessage("Ticket Not Found");
	  return;
  }

ADOQuery1->Edit();
ADOQuery1->FieldByName("LOCATION")->AsString = "ALTERATION";

ADOQuery1->FieldByName("INVENTORYDATE")->AsString = DateTimeToStr(Now());
ADOQuery1->Post();

	Memo1->Lines->Add(Edit1->Text+" Ticket Assigned to Alteration");
	Edit2->Text = "";

	Button1->Default = false;
Button4->Default = true;
Edit1->Text = "";
Edit1->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAssignLocationForm::SpeedButton4Click(TObject *Sender)
{
ADOQuery2->Close();
   ADOQuery1->Close();
  Close();
}
//---------------------------------------------------------------------------

