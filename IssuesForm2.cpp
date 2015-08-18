//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "IssuesForm2.h"
#include "MainMenu.h"
#include <shellapi.h>
#include <inifiles.hpp>
#include <stdio.h>
#include <math.h>
#include <io.h>
#include <dos.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TIssuesForm01 *IssuesForm01;
//---------------------------------------------------------------------------
__fastcall TIssuesForm01::TIssuesForm01(TComponent* Owner)
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

         	Label23->Text = "Select Item";


}
//---------------------------------------------------------------------------
void __fastcall TIssuesForm01::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void TIssuesForm01::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------


void __fastcall TIssuesForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TIssuesForm01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TIssuesForm01::SelectCustomerListBoxItemClick(TObject *Sender)
{
		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

			//SaveChangesIListBoxItem->Visible = false;
		   //	SavePrintListBoxItem->Visible = false;
		   //	QuickTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Enabled = true;
}




void __fastcall TIssuesForm01::EditCustomerListBoxItemClick(TObject *Sender)
{

	  TabControl1->TabIndex = 1;



	  ADOQuery2->Active = false;


	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from ISSUES where acct like '%"+ADOQuery1->FieldByName("ACCT")->AsString+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by issuedate";
	  ADOQuery2->Active = true;




}
//---------------------------------------------------------------------------


void __fastcall TIssuesForm01::AddCustomerListBoxItemClick(TObject *Sender)
{
	//SavePrintListBoxItem->Visible = false;



	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery2->Insert() ;
	ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	ADOQuery2->FieldByName("ISSUEDATE")->AsString =   DateTimeToStr(Now());




}
//---------------------------------------------------------------------------




void __fastcall TIssuesForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{
	   if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();


	  ShowMessage("Changes Saved");
}
//---------------------------------------------------------------------------





void __fastcall TIssuesForm01::Button17Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button15Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button16Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "3";



}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button18Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button19Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button20Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button21Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button22Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button23Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button14Click(TObject *Sender)
{
TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TIssuesForm01::UpdateTicketView()
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
void __fastcall TIssuesForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TIssuesForm01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button8Click(TObject *Sender)
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

void __fastcall TIssuesForm01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button13Click(TObject *Sender)
{

if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

   ADOQuery2->Active = false;


	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from AR where acct like '%"+ADOQuery1->FieldByName("ACCT")->AsString+"%' AND STORENO = "+MainMenuForm->strStoreNo  +"  order by orderno";
	  ADOQuery2->Active = true;



}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button9Click(TObject *Sender)
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


void __fastcall TIssuesForm01::FormShow(TObject *Sender)
{
	//this->Fill->Color = MainMenuForm->iBackgroundColor ;

	 Edit2->SetFocus();

}
//---------------------------------------------------------------------------




void __fastcall TIssuesForm01::MetropolisUIListBoxItem1Click(TObject *Sender)
{

		MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Issue?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{

		ADOQuery2->Delete();
	}
}
//---------------------------------------------------------------------------



void __fastcall TIssuesForm01::Button1Click(TObject *Sender)
{
	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";


	  if( strNumber.AnsiPos( Edit2->Text.SubString(0,1) ) > 0 )
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where  acct like '%"+Edit2->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by acct";

	  }
	  else
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from customer where  name like '%"+Edit2->Text+"%' AND STORE IN ("+MainMenuForm->strEnterprise +") order by name";


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
		//   EditCustomerListBoxItem->Enabled = false;
	  }
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button12Click(TObject *Sender)
{
	ADOQuery2->Insert() ;
	ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	ADOQuery2->FieldByName("ISSUEDATE")->AsString = DateTimeToStr(Now());

   Memo2->SetFocus();
}
//---------------------------------------------------------------------------





void __fastcall TIssuesForm01::Button28Click(TObject *Sender)
{

	MainMenuForm->strQuestion = "Are you sure you wish to Delete this Issue?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery2->Delete();

	}


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::Button10Click(TObject *Sender)
{

  if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

		 AnsiString strMessage = "Customer "+ ADOQuery1->FieldByName("NAME")->AsString   +  "  " + ADOQuery2->FieldByName("ACCT")->AsString  + " \n\r Issue:  "+ ADOQuery2->FieldByName("ISSUE")->AsString + " \n\r Issue:  "+ ADOQuery2->FieldByName("RESOLUTION")->AsString;


			SHELLEXECUTEINFO execinfo;
   memset(&execinfo, 0, sizeof(execinfo));
   execinfo.cbSize = sizeof(execinfo);
   execinfo.lpVerb = L"open";

   execinfo.lpFile = L"C:\\VIVALDI8\\BLAT.EXE";

   AnsiString strParam;


   strParam =  "-to "+ MainMenuForm->strSenderEmail +"  -body \" "+strMessage+  MainMenuForm->strStoreName  +"\" -serverSMTP  "+   MainMenuForm->strSMTPServer +" -sender "+  MainMenuForm->strSenderEmail +"  -u "+  MainMenuForm->strSenderEmail +"  -pw "+  MainMenuForm->strSenderPassword +" -subject \"Customer Issues for Store "+MainMenuForm->strStoreName+"  "+ ADOQuery1->FieldByName("NAME")->AsString +"\" ";


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


   ShowMessage("Email Sent: "+ strMessage);
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton4Click(TObject *Sender)
{

if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();


 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton3Click(TObject *Sender)
{
if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

          ShowMessage("Changes Saved");

}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton5Click(TObject *Sender)
{

	  TabControl1->TabIndex = 1;

	 // AddCustomerListBoxItem->Enabled = true;
	 // MetropolisUIListBoxItem1->Enabled = true;
	 // SaveChangesIListBoxItem->Enabled = true;

	  ADOQuery2->Active = false;


	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from ISSUES where acct like '%"+ADOQuery1->FieldByName("ACCT")->AsString+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by issuedate";
	  ADOQuery2->Active = true;




}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton1Click(TObject *Sender)
{
  //	SaveChangesIListBoxItem->Enabled = true;


	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery2->Insert() ;
	ADOQuery2->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
	ADOQuery2->FieldByName("ACCT")->AsString = ADOQuery1->FieldByName("ACCT")->AsString;
	ADOQuery2->FieldByName("ISSUEDATE")->AsString =   DateTimeToStr(Now());


}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton2Click(TObject *Sender)
{
		MainMenuForm->strQuestion = "Are you absolutely sure you wish to DELETE this Issue?";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{

		ADOQuery2->Delete();
	}
}
//---------------------------------------------------------------------------

void __fastcall TIssuesForm01::SpeedButton6Click(TObject *Sender)
{
 TabControl1->TabIndex = 0;
}
//---------------------------------------------------------------------------

