//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "UpchargeForm2.h"
#include "MainMenu.h"
#include "QuestionForm1.h"
#include <shellapi.h>
#include <inifiles.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TUpchargeForm03 *UpchargeForm03;
//---------------------------------------------------------------------------
__fastcall TUpchargeForm03::TUpchargeForm03(TComponent* Owner)
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




		   //	Label23->Text = "Select Item";


}
//---------------------------------------------------------------------------
void __fastcall TUpchargeForm03::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void TUpchargeForm03::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::FormActivate(TObject *Sender)
{
   //	WindowState = TWindowState::wsMaximized;
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TUpchargeForm03::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TUpchargeForm03::SelectCustomerListBoxItemClick(TObject *Sender)
{

  if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();


		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;

			//SaveChangesIListBoxItem->Visible = false;
		   //	SavePrintListBoxItem->Visible = false;
		   //	QuickTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Visible = true;
		   //	WriteTicketListBoxItem->Enabled = true;
}




void __fastcall TUpchargeForm03::EditCustomerListBoxItemClick(TObject *Sender)
{

	TabControl1->TabIndex = 1;

	//SaveChangesIListBoxItem->Visible = true;
   //	SavePrintListBoxItem->Visible = false;
	//SaveChangesIListBoxItem->Enabled = true;






}
//---------------------------------------------------------------------------


void __fastcall TUpchargeForm03::AddCustomerListBoxItemClick(TObject *Sender)
{
	//SavePrintListBoxItem->Visible = false;
	//SaveChangesIListBoxItem->Enabled = true;

     if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();




	TabControl1->TabIndex = 1;
	//ADOQuery1->Append();
	ADOQuery2->Insert() ;
	ADOQuery2->FieldByName("StoreNo")->AsString = MainMenuForm->strStoreNo;





}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::SaveChangesIListBoxItemClick(TObject *Sender)
{
	   if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

      ShowMessage("Changes Saved");

}
//---------------------------------------------------------------------------





void __fastcall TUpchargeForm03::Button17Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::Button15Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::Button16Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------







void __fastcall TUpchargeForm03::UpdateTicketView()
{
//Memo1->Lines->Clear();

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

		//   Memo1->Lines->Add(sQty+"  "+sItemDescription + "   " + sPrice);

	   //	if( TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
		 //	  Memo1->Lines->Add("   "+ TempListItemUpcharge->Strings[i] );

	}

   //	Label26->Text = "Sub Total:  "+ FloatToStrF(fTotal  , ffCurrency, 12, 2);
}
void __fastcall TUpchargeForm03::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TUpchargeForm03::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::Button8Click(TObject *Sender)
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



void __fastcall TUpchargeForm03::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TUpchargeForm03::FormShow(TObject *Sender)
{

	  ADOQuery1->Active = false;
	  ADOQuery1->SQL->Clear();
	  ADOQuery1->SQL->Text = "Select * from Class where Store = "+ MainMenuForm->strStoreNo+ "  Order by CODE";
	  ADOQuery1->Active = true;


	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from UPCHARGE where Storeno = "+ MainMenuForm->strStoreNo+ " Order by CODE";
	  ADOQuery2->Active = true;

        if( ADOQuery2->Eof == false )
	  {
			//SaveChangesIListBoxItem->Enabled = true;
		   //	EditCustomerListBoxItem->Enabled = true;
			// MetropolisUIListBoxItem1->Enabled = true;



	  }
	  else
	  {
		  // SaveChangesIListBoxItem->Enabled = false;
		  // EditCustomerListBoxItem->Enabled = false;
		  //	MetropolisUIListBoxItem1->Enabled = false;
	  }

	

}
//---------------------------------------------------------------------------


void __fastcall TUpchargeForm03::ComboBox1Change(TObject *Sender)
{

	  // strSelectedClass =
	

}
//---------------------------------------------------------------------------





void __fastcall TUpchargeForm03::SpeedButton5Click(TObject *Sender)
{
    	TabControl1->TabIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::SpeedButton6Click(TObject *Sender)
{
	TabControl1->TabIndex = 1;
}
//---------------------------------------------------------------------------

void __fastcall TUpchargeForm03::SpeedButton2Click(TObject *Sender)
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
		ADOQuery2->Delete();

	}
}
//---------------------------------------------------------------------------

