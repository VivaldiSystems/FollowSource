//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "DeliveryForm2.h"

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
TDeliveryForm01 *DeliveryForm01;
//---------------------------------------------------------------------------
__fastcall TDeliveryForm01::TDeliveryForm01(TComponent* Owner)
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
void __fastcall TDeliveryForm01::HeaderButtonClick(TObject *Sender)
{

 ADOQuery1->Active = false;


	Close();
}
//---------------------------------------------------------------------------

void TDeliveryForm01::ShowToolbar(bool AShow)
{

}


//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::FormActivate(TObject *Sender)
{
	//WindowState = TWindowState::wsMaximized;
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TDeliveryForm01::SelectCustomerListBoxItemClick(TObject *Sender)
{
		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;


}




void __fastcall TDeliveryForm01::EditCustomerListBoxItemClick(TObject *Sender)
{


		ADOQuery8->Active = false;
	ADOQuery8->SQL->Clear();
	ADOQuery8->SQL->Add("select max(id) AS ID from customer c1 where c1.STORE = "+MainMenuForm->strStoreNo  +" and c1.route = "+ADOQuery1->FieldByName("ROUTE")->AsString+" and 1 < (select count(id) from customer where c1.store = customer.store and c1.acct = customer.acct)");
	ADOQuery8->Active = true;

		if( ADOQuery8->Eof == false && ADOQuery8->FieldByName("ID")->AsString != "")
		{
				MainMenuForm->strQuestion = "Duplicate Customer Account Numbers have been found.  Delivery reports will not work unless we remove the duplicates.  May we do this now?";

				TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
					if (Form )
					{
						Form->ShowModal();
						delete Form;
					}


				if( MainMenuForm->blnOK == true )
				{
                    	ADOQuery8->First() ;
						while( ADOQuery8->Eof == false )
						{

                             	ADOQuery9->Active = false;
								ADOQuery9->SQL->Clear();
								ADOQuery9->SQL->Text = "DELETE FROM CUSTOMER WHERE ID = "+ADOQuery8->FieldByName("ID")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"";
								ADOQuery9->ExecSQL();
								Caption = "Removing "+ ADOQuery8->FieldByName("ID")->AsString;

							  	ADOQuery8->MoveBy(1);

						}
					  ShowMessage("Duplicate Customers have been Removed!");
				}



		}
	



		ADOQuery8->Active = false;



	 if( MainMenuForm->blnUseDeliveryVacation )
	 {

		  ADOQuery6->Active = false;
		  ADOQuery6->SQL->Clear();
		  ADOQuery6->SQL->Text = "UPDATE CUSTOMER SET ONVACATION = 0 WHERE ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +" AND GETDATE() >= VACATIONTILL  AND VACATIONTILL IS NOT NULL AND ONVACATION = 1";
		  ADOQuery6->ExecSQL();
	 }

        TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryManifest.rdl";
			MainMenuForm->strReportName = "Delivery Manifest Report";
			MainMenuForm->strReportFilter = "FILE";

			if( MainMenuForm->blnUseDeliveryVacation )
	 		{

			if( MainMenuForm->blnDeliveryByDate )
			{
				MainMenuForm->strAdditionalFilter = "STATUS = 'R' AND ROUTE <> '0' AND STORE = "+MainMenuForm->strStoreNo  +" And IsActive = '1' And And (OnVacation = 0 or Onvacation is Null)";
			}
			else
			{
				MainMenuForm->strAdditionalFilter = "STATUS = 'R' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = "+MainMenuForm->strStoreNo  +" And IsActive = '1' And And (OnVacation = 0 or Onvacation is Null)";
			}
			}
			else
			{
              if( MainMenuForm->blnDeliveryByDate )
			{
				MainMenuForm->strAdditionalFilter = "STATUS = 'R' AND ROUTE <> '0' AND STORE = "+MainMenuForm->strStoreNo  +" And IsActive = '1'";
			}
			else
			{
				MainMenuForm->strAdditionalFilter = "STATUS = 'R' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = "+MainMenuForm->strStoreNo  +" And IsActive = '1'";
			}


            }

			MainMenuForm->strDataSet = "DELIVERY";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}

}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::AddCustomerListBoxItemClick(TObject *Sender)
{

	//SaveChangesIListBoxItem->Enabled = true;

	CalendarEdit2->Text = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));

	TabControl1->TabIndex = 1;

    if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;





}
//---------------------------------------------------------------------------




void __fastcall TDeliveryForm01::SaveChangesIListBoxItemClick(TObject *Sender)
{
	MainMenuForm->strQuestion = "Are you sure you wish to Process this Route? All Tickets will be marked Delivered!";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == false )
	{

	return;
    }

	   //	SaveChangesIListBoxItem->Enabled = true;

	TabControl1->TabIndex = 1;

    if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;


	  ADOQuery4->Active = false;
	  ADOQuery4->SQL->Clear();
	  ADOQuery4->SQL->Text = "Select * from AR where STORENO = '"+MainMenuForm->strStoreNo  +"' and ID = -1";
	  ADOQuery4->Active = true;


	  	ADOQuery7->Active = false;
		ADOQuery7->SQL->Clear();
		ADOQuery7->SQL->Text = "Select * from CUSTOMER where STORE = '"+MainMenuForm->strStoreNo  +"' and ACCT = '"+ ADOQuery2->FieldByName("ACCT")->AsString+"'";
		ADOQuery7->Active = true;


	   ADOQuery2->First();

	   while( ! ADOQuery2->Eof )
	   {

			if( ADOQuery7->FieldByName("ACCOUNT")->AsBoolean )
			{


				ADOQuery4->Open();
				ADOQuery4->Insert();
				ADOQuery4->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
				ADOQuery4->FieldByName("STORENO")->AsString = MainMenuForm->strStoreNo;
				ADOQuery4->FieldByName("AMTPAID")->AsFloat = 0;

				if( ADOQuery2->FieldByName("BACCT")->AsString != "" )
					ADOQuery4->FieldByName("ACCT")->AsString = ADOQuery2->FieldByName("BACCT")->AsString;
				else
					ADOQuery4->FieldByName("ACCT")->AsString = ADOQuery2->FieldByName("ACCT")->AsString;

				ADOQuery4->FieldByName("NAME")->AsString = ADOQuery2->FieldByName("NAME")->AsString;
				ADOQuery4->FieldByName("TAX")->AsString = ADOQuery2->FieldByName("TAX")->AsString;
				ADOQuery4->FieldByName("AMT")->AsString = ADOQuery2->FieldByName("AMT")->AsString;
				ADOQuery4->FieldByName("SLAVE")->AsString = MainMenuForm->strSlave;
				ADOQuery4->FieldByName("DUE")->AsFloat = ADOQuery2->FieldByName("AMT")->AsFloat; // - ADOQuery6->FieldByName("AMTPAID")->AsFloat;
				ADOQuery4->FieldByName("PAYMENTTYPE")->AsString = MainMenuForm->strPaidType;
				ADOQuery4->FieldByName("ORDERNO")->AsString =  ADOQuery2->FieldByName("ORDERNO")->AsString;
				ADOQuery4->FieldByName("ROUTE")->AsString =  ADOQuery2->FieldByName("ROUTE")->AsString;
				ADOQuery4->FieldByName("STATUS")->AsString =  "OPEN";
				//Memo1->Lines->Add(ADOQuery4->FieldByName("ACCT")->AsString+" Ticket "+ADOQuery4->FieldByName("ORDERNO")->AsString+" Delivered - Placed on Account");
				ADOQuery4->Post();

				ADOQuery2->Edit();
				ADOQuery2->FieldByName("STATUS")->AsString = "D";

				ADOQuery2->Post();




			}
			else
			{


					AnsiString strCC =  ADOQuery7->FieldByName("CCARD")->AsString;
					AnsiString strExpDate =  ADOQuery7->FieldByName("EXPDATE")->AsString;



					if( strCC == "" )
					   ShowMessage(ADOQuery2->FieldByName("ACCT")->AsString+" CUSTOMER IS MISSING A CREDIT CARD AND IS NOT MARKED FOR ON ACCOUNT.  THIS CUSTOMER'S TICKETS WILL NOT BE PAID.");


					FILE *stream;
					 FILE *stream2;

					 AnsiString strPath = "C:\\VIVALDI8\\X-CHARGE\\";
					  if( MainMenuForm->strCreditCardPath != "" )
					  {
						  strPath = MainMenuForm->strCreditCardPath+ "\\";
					  }

					 AnsiString filename =  strPath+ TDateTime::CurrentDateTime().FormatString("MMDDYYYY")+".req" ;
					 AnsiString filename2 =  strPath+ TDateTime::CurrentDateTime().FormatString("MMDDYYYY")+".ans" ;


					 DeleteFile(filename2.c_str());
					 DeleteFile(filename.c_str());

					 Caption = filename;
					 stream2 = fopen(filename.c_str(), "w+");


					AnsiString sexp;

					AnsiString s;

					AnsiString scard = strCC;
					AnsiString svalue = FloatToStr(ADOQuery2->FieldByName("AMT")->AsFloat);
					AnsiString ssec = "";

				   AnsiString sexpdate = strExpDate.SubString(3,2)+strExpDate.SubString(1,2);

					s = "\"C1\",\"VIVALDI5\",\""+ADOQuery7->FieldByName("PHONE")->AsString+"\",\""+scard.Trim()+"\",\""+sexpdate.Trim()+"\",\""+svalue+"\",\""+ADOQuery7->FieldByName("ZIP")->AsString+"\",\""+ADOQuery7->FieldByName("ADDRESS1")->AsString+"\",\""+ssec+"\"";


					fprintf(stream2 , "%s \n", s );


					fclose(stream2);



					Caption = filename2+" - Waiting for Response ";

					if( scard.SubString(0,4) == "4111" )
					  ShowMessage("Card Swipe is: "+ scard+"  Press OK to Send the Card to Process!");




				  Caption = filename;
				   Caption = "Opening Answer File";
				 AnsiString stag = ".";
				 int i = 0;

				 while ((stream = fopen(filename2.c_str(), "r")) == NULL)
				   {
					 // sleep(50);
					 i++ ;
					 if( i == 20 )
					 {
					   stag = ".";
					   i = 0;
					 }
					 else
						 stag = stag + ".";

					  /* display an error message */
					  Caption = filename2+" - Waiting for Response "+stag;

				   }


				char msg[200];
				 AnsiString scheck2,sBuf;


				 while( sBuf.Length() == 0  )
				 {
				  Caption = "Waiting for Credit Card to Process";
				   fseek(stream, 0, SEEK_SET);
				   fgets(msg, 200, stream);  // gets the Contract
				   sBuf = msg;
				   scheck2 = sBuf.SubString(2,1);
				 }
				 fclose(stream);



				 if( scheck2 != "Y" )
				 {
					ADOQuery2->Edit();
					ADOQuery2->FieldByName("STATUS")->AsString = "N";
				   //	Memo1->Lines->Add(ADOQuery2->FieldByName("ACCT")->AsString+" Ticket "+ADOQuery2->FieldByName("ORDERNO")->AsString+" Delivered - CC Declined");
					ADOQuery2->Post();
				 }
				 else
				 {
					ADOQuery2->Edit();
					ADOQuery2->FieldByName("STATUS")->AsString = "D";
				   //	Memo1->Lines->Add(ADOQuery2->FieldByName("ACCT")->AsString+" Ticket "+ADOQuery2->FieldByName("ORDERNO")->AsString+" Delivered - CC Authorized");
					ADOQuery2->Post();

				 }



			}




			 ADOQuery2->MoveBy(1);

	   }
        	ADOQuery7->Active = false;
		ADOQuery4->Active = false;

	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;


	  ShowMessage("Route is Processed.");
}
//---------------------------------------------------------------------------





void __fastcall TDeliveryForm01::Button17Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "1";

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button15Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "2";



}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button16Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "3";


//int ival = 3;
//AnsiString sval = IntToStr(ival);


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button18Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;
 strQty = "4";


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button19Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;
 strQty = "5";


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button20Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;
 strQty = "6";


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button21Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;
 strQty = "7";


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button22Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;
 strQty = "8";


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button23Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "9";

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button14Click(TObject *Sender)
{
//TicketItemsListBox->Enabled = True;

 strQty = "0";

}
//---------------------------------------------------------------------------
void __fastcall TDeliveryForm01::UpdateTicketView()
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

		  // Memo1->Lines->Add(sQty+"  "+sItemDescription + "   " + sPrice);

	   //	if( TempListItemUpcharge->Strings[i] != "" && TempListItemUpcharge->Strings[i] != " ")
		//	  Memo1->Lines->Add("   "+ TempListItemUpcharge->Strings[i] );

	}

	//Label26->Text = "Sub Total:  "+ FloatToStrF(fTotal  , ffCurrency, 12, 2);
}
void __fastcall TDeliveryForm01::ColorButton1Click(TObject *Sender)
{
  strUpcharge = strUpcharge + " BLACK";

   TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton2Click(TObject *Sender)
{
strUpcharge = strUpcharge + " WHITE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton3Click(TObject *Sender)
{
strUpcharge = strUpcharge + " NAVY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton4Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BLUE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::Button6Click(TObject *Sender)
{
strClass = "P";
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button8Click(TObject *Sender)
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

void __fastcall TDeliveryForm01::Button7Click(TObject *Sender)
{
strClass = "A";
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button13Click(TObject *Sender)
{


  ShowMessage("Map Customer for Account # "+ADOQuery2->FieldByName("ACCT")->AsString);


   ADOQuery5->Active = false;


	  ADOQuery5->SQL->Clear();
	  ADOQuery5->SQL->Text = "Select TOP 1 ACCT,NAME, ADDRESS1, CITY, STATE, ZIP, EMAIL from CUSTOMER where ACCT = '"+ADOQuery2->FieldByName("ACCT")->AsString+"' AND STORE IN ("+MainMenuForm->strEnterprise +")";
	  ADOQuery5->Active = true;

	  if( ADOQuery5->Eof )
		 ShowMessage("Customer Not Found "+ADOQuery2->FieldByName("ACCT")->AsString);

				   AnsiString strAddress1 = ADOQuery5->FieldByName("ADDRESS1")->AsString;

				   AnsiString strCity = ADOQuery5->FieldByName("CITY")->AsString;
				   AnsiString strState = ADOQuery5->FieldByName("STATE")->AsString;
				   AnsiString strZip = ADOQuery5->FieldByName("ZIP")->AsString ;








					 strAddress1 = AnsiReplaceStr(strAddress1," ","+");


					strCity = AnsiReplaceStr(strCity," ","+");


				   strState = AnsiReplaceStr(strState," ","+");


				   AnsiString strTemp = "http://maps.google.com?q=\""+ strAddress1+","+ strCity +","+ strState+","+ strZip+"\"";
				   AnsiString strParam = "";



				   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   wchar_t *str = new wchar_t[strTemp.WideCharBufSize()];

				   execinfo.lpFile = strTemp.WideChar(str, strTemp.WideCharBufSize()); // strTemp.c_str();                                  // \L"http:\\\\maps.google.com\\";
					  // Parameters are ReportViewer.exe Store# ReportName Copies Print/Preview DataSet FilterOverride DEBUG


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

		   ADOQuery5->Active = true;


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton5Click(TObject *Sender)
{
strUpcharge = strUpcharge + " PURPLE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton6Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GREEN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton18Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CYAN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton8Click(TObject *Sender)
{
strUpcharge = strUpcharge + " RED";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton9Click(TObject *Sender)
{
strUpcharge = strUpcharge + " YELLOW";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton10Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BROWN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton11Click(TObject *Sender)
{
strUpcharge = strUpcharge + " BEIGE";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton22Click(TObject *Sender)
{
strUpcharge = strUpcharge + " KAHKI";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton21Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK BRN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton20Click(TObject *Sender)
{
strUpcharge = strUpcharge + " CRIMSON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton19Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SALMON";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton17Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GOLD";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton15Click(TObject *Sender)
{
strUpcharge = strUpcharge + " LIME";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton16Click(TObject *Sender)
{
strUpcharge = strUpcharge + " VIOLET";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton14Click(TObject *Sender)
{
strUpcharge = strUpcharge + " AQUA";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton7Click(TObject *Sender)
{
strUpcharge = strUpcharge + " GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton13Click(TObject *Sender)
{
strUpcharge = strUpcharge + " DRK GRAY";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::ColorButton12Click(TObject *Sender)
{
strUpcharge = strUpcharge + " SKIN";
 TempListItemUpcharge->Strings[TempListItemUpcharge->Count - 1] = strUpcharge;
   UpdateTicketView();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button9Click(TObject *Sender)
{
   //	Memo1->Lines->Clear();
	TempListQty->Clear();
	TempListItemCode->Clear();
	TempListItemDescription->Clear();
	TempListPrice->Clear();
	TempListTax->Clear();
	TempListItemUpcharge->Clear();

	UpdateTicketView();
}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::FormShow(TObject *Sender)
{
   // this->Fill->Color = MainMenuForm->iBackgroundColor ;
                  	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";


	  if( strNumber.AnsiPos( Edit2->Text.SubString(0,1) ) > 0 )
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from HotelRTE where Route like '%"+Edit2->Text+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by Route";

	  }
	  else
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from HotelRTE where name like '%"+Edit2->Text+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by name";


	  }

	  ADOQuery1->Active = true;
	 Edit2->SetFocus();

}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::ComboBox1Change(TObject *Sender)
{

	  // strSelectedClass =




}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::MetropolisUIListBoxItem1Click(TObject *Sender)
{

	  // if( MetropolisUIListBoxItem1->Enabled )
	 //  {
           	MainMenuForm->strQuestion = "Are you absolutely sure you wish to remove this Ticket?";

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
	 //  }


}
//---------------------------------------------------------------------------



void __fastcall TDeliveryForm01::Button1Click(TObject *Sender)
{
	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";


	  if( strNumber.AnsiPos( Edit2->Text.SubString(0,1) ) > 0 )
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from HotelRTE where Route like '%"+Edit2->Text+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by Route";

	  }
	  else
	  {
		 ADOQuery1->SQL->Clear();
		 ADOQuery1->SQL->Text = "Select * from HotelRTE where name like '%"+Edit2->Text+"%' AND STORENO = "+MainMenuForm->strStoreNo  +" order by name";


	  }

	  ADOQuery1->Active = true;


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button12Click(TObject *Sender)
{

	MainMenuForm->strQuestion = "Do you wish the Ticket to be rescheduled for the next day? (Ticket # "+ADOQuery2->FieldByName("ORDERNO")->AsString+")";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery2->Edit() ;
		ADOQuery2->FieldByName("DateOut")->AsDateTime  =  StrToDate( ADOQuery2->FieldByName("DateOut")->AsDateTime.DateString() ) + 1;
		ADOQuery2->Post();
	}

        ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";
	  ADOQuery2->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button10Click(TObject *Sender)
{
	double fLocalTendered = 0;
	TCommonCustomForm *Form = Application->GetDeviceForm(L"CashdrawerView");
		if(Form)
		{

		  MainMenuForm->fTendered  = 0; //MainMenuForm->fTicketSubTotal +  MainMenuForm->fTicketTax - MainMenuForm->fPrepayment - MainMenuForm->fCouponTotal;

		   Form->ShowModal();
		   fLocalTendered =  MainMenuForm->fTendered;
		   delete Form;

		}
	 if( MainMenuForm->blnCancel == false )
	 {

		 ADOQuery2->Insert();
			ADOQuery2->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery2->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			//ADOQuery2->FieldByName("CREDITS")->AsFloat =  MainMenuForm->fTendered;
			ADOQuery2->FieldByName("ACCT")->AsString =  	ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery2->FieldByName("NAME")->AsString =  	ADOQuery1->FieldByName("NAME")->AsString;
			//ADOQuery3->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery2->FieldByName("AMT")->AsString =  	0;
			ADOQuery2->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery2->FieldByName("AMTPAID")->AsFloat = MainMenuForm->fTendered;
			ADOQuery2->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			//ADOQuery3->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery2->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery2->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery2->Post();



		 ADOQuery3->Active = false;
		 ADOQuery3->SQL->Clear();
		 ADOQuery3->SQL->Add("Select * from CASHBOX where StoreNO = '"+ MainMenuForm->strStoreNo+ "' and id = -1");
		 ADOQuery3->Active = true;
		 ADOQuery3->Insert();
			ADOQuery3->FieldByName("DATEOUT")->AsString =  DateTimeToStr(Now());
			ADOQuery3->FieldByName("STORENO")->AsString =  MainMenuForm->strStoreNo;
			ADOQuery3->FieldByName("AMTPAID")->AsFloat =  MainMenuForm->fTendered;
			ADOQuery3->FieldByName("ACCT")->AsString =  	ADOQuery1->FieldByName("ACCT")->AsString;
			ADOQuery3->FieldByName("NAME")->AsString =  	ADOQuery1->FieldByName("NAME")->AsString;
			//ADOQuery3->FieldByName("TAX")->AsString =  	ADOQuery6->FieldByName("TAX")->AsString;
			ADOQuery3->FieldByName("AMT")->AsString =  	MainMenuForm->fTendered;
			ADOQuery3->FieldByName("SLAVE")->AsString =   MainMenuForm->strSlave;
			ADOQuery3->FieldByName("DUE")->AsFloat = MainMenuForm->fTendered;
			ADOQuery3->FieldByName("PAYMENTTYPE")->AsString = "AR PAYMENT";
			//ADOQuery3->FieldByName("ORDERNO")->AsString =  ADOQuery6->FieldByName("ORDERNO")->AsString;
			ADOQuery3->FieldByName("ROUTE")->AsString =  ADOQuery1->FieldByName("ROUTE")->AsString;
			ADOQuery3->FieldByName("STATUS")->AsString =  "OPEN";
			//ADOQuery7->FieldByName("DISCOUNT")->AsString =  ADOQuery6->FieldByName("DISCOUNT")->AsString;

			ADOQuery3->Post();
			ADOQuery3->Active = false;
	 }

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button25Click(TObject *Sender)
{


		TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "CustomerbyRoute.rdl";
			MainMenuForm->strAdditionalFilter = "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' And (RegularRoute = 1 Or OneTimePickup = 1)";
			MainMenuForm->strReportName = "Customers by Route Report";
			MainMenuForm->strReportFilter = "ALL";
			MainMenuForm->strDataSet = "CUSTOMER";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button27Click(TObject *Sender)
{
 
      ADOQuery1->MoveBy(1);

	   if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button26Click(TObject *Sender)
{

 ADOQuery1->MoveBy(-1);

    if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;






}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button28Click(TObject *Sender)
{

	MainMenuForm->strQuestion = "Mark the selected Ticket Delivery to remove from Manifest? (Ticket # "+ADOQuery2->FieldByName("ORDERNO")->AsString+")";

	TCommonCustomForm *Form = Application->GetDeviceForm(L"QuestionForm");
		if (Form )
		{
			Form->ShowModal();
			delete Form;
		}


	if( MainMenuForm->blnOK == true )
	{
		ADOQuery2->Edit() ;
		ADOQuery2->FieldByName("Status")->AsString =  "D";
		ADOQuery2->Post();

	}

     ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::CalendarEdit2Change(TObject *Sender)
{
	  ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();

	  ADOQuery2->SQL->Text = "SELECT * FROM INVOICE WHERE STATUS = 'R' AND  CAST(DATEOUT AS DATE) <= CAST('"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AS DATE) AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  ORDER BY ORDERNO";

	  ADOQuery2->Active = true;

}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::MetropolisUIListBoxItem2Click(TObject *Sender)
{

     	 if( MainMenuForm->blnUseDeliveryVacation )
	 {
	  //ADOQuery6->Active = false;
	 // ADOQuery6->SQL->Clear();
	 // ADOQuery6->SQL->Text = "UPDATE CUSTOMER SET ISACTIVE = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND VACATIONTILL < GETDATE() AND VACATIONTILL IS NOT NULL  AND ONVACATION = 1";
	 // ADOQuery6->ExecSQL();

       ADOQuery6->Active = false;
	  ADOQuery6->SQL->Clear();
	  ADOQuery6->SQL->Text = "UPDATE CUSTOMER SET ONVACATION = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND VACATIONTILL >= GETDATE() AND VACATIONTILL IS NOT NULL AND ONVACATION = 1";
	  ADOQuery6->ExecSQL();
	  }

	TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryPickup.rdl";
			MainMenuForm->strReportName = "Delivery Pickup Report";
			MainMenuForm->blnDisableDates  = true;
			MainMenuForm->strReportFilter = "ALL";

			if( MainMenuForm->blnUseDeliveryVacation )
			 {
					MainMenuForm->strAdditionalFilter = "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"'  And IsActive = '1' And (OnVacation = 0 or Onvacation is Null) And (RegularRoute = 1 Or OneTimePickup = 1)";
			  }
			  else
			  {
				MainMenuForm->strAdditionalFilter = "ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"'  And IsActive = '1' And (RegularRoute = 1 Or OneTimePickup = 1)";

			  }
			MainMenuForm->strReportName = "Route Pickup Report";

			MainMenuForm->strDataSet = "CUSTOMER";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::MetropolisUIListBoxItem3Click(TObject *Sender)
{
                   SHELLEXECUTEINFO execinfo;
				   memset(&execinfo, 0, sizeof(execinfo));
				   execinfo.cbSize = sizeof(execinfo);
				   execinfo.lpVerb = L"open";

				   execinfo.lpFile = L"http://www.iHomeValet.com";
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

void __fastcall TDeliveryForm01::Button29Click(TObject *Sender)
{
      ADOQuery6->Active = false;
	  ADOQuery6->SQL->Clear();
	  ADOQuery6->SQL->Text = "UPDATE CUSTOMER SET ONETIMEPICKUP = 0, ROUTE = 0 WHERE ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' AND ONETIMEPICKUP = 1";
	  ADOQuery6->ExecSQL();

	  ShowMessage("Update Complete");
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button30Click(TObject *Sender)
{
	ADOQuery2->Edit() ;
		ADOQuery2->FieldByName("IsActive")->AsBoolean = true;
		ADOQuery2->Post();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button31Click(TObject *Sender)
{
ADOQuery2->Edit() ;
		ADOQuery2->FieldByName("IsActive")->AsBoolean =  false;
		ADOQuery2->Post();
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button32Click(TObject *Sender)
{
 ADOQuery2->Active = false;
	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "SELECT * FROM INVOICE WHERE STATUS = 'N' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"'  order by orderno";
	  ADOQuery2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button34Click(TObject *Sender)
{
 TCommonCustomForm *Form = Application->GetDeviceForm(L"ReportView");
		if (Form)
		{
			MainMenuForm->strReportFileName = "DeliveryManifest.rdl";
			MainMenuForm->strReportName = "Delivery Manifest Report";
			MainMenuForm->strReportFilter = "FILE";

			if( MainMenuForm->blnUseDeliveryVacation )
	 {


				MainMenuForm->strAdditionalFilter = "STATUS = 'N' AND ROUTE = '"+ADOQuery1->FieldByName("ROUTE")->AsString+"' AND STORE = '"+MainMenuForm->strStoreNo  +"' And IsActive = '1'";



            }

			MainMenuForm->strDataSet = "DELIVERY";
			MainMenuForm->blnDateOut = true;
			Form->ShowModal();
			delete Form;

		}

}
//---------------------------------------------------------------------------


void __fastcall TDeliveryForm01::SpeedButton1Click(TObject *Sender)
{
   //	SaveChangesIListBoxItem->Enabled = true;

	//CalendarEdit2->Text = MainMenuForm->ConvertDate(DateTimeToStr(Now()).SubString(1,10));

	TabControl1->TabIndex = 1;

	if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
		 ADOQuery2->Post();

	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";

	 // ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";
	  ADOQuery2->Active = true;
}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button2Click(TObject *Sender)
{
 if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
 {
		 ADOQuery2->Post();
 }



	  ADOQuery1->MoveBy(-1);


	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";

	 // ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";
	  ADOQuery2->Active = true;


}
//---------------------------------------------------------------------------

void __fastcall TDeliveryForm01::Button3Click(TObject *Sender)
{
 if(  ADOQuery2->State == dsEdit  || ADOQuery2->State == dsInsert )
 {
		 ADOQuery2->Post();
 }



	  ADOQuery1->MoveBy(1);


	  ADOQuery2->Active = false;

	  ADOQuery2->SQL->Clear();
	  ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";

	 // ADOQuery2->SQL->Text = "Select * from INVOICE where STATUS = 'R' AND DATEOUT <= '"+MainMenuForm->ConvertDate(CalendarEdit2->Text)+"' AND ROUTE = "+ADOQuery1->FieldByName("ROUTE")->AsString+" AND STORE = "+MainMenuForm->strStoreNo  +"  order by orderno";
	  ADOQuery2->Active = true;
}
//---------------------------------------------------------------------------

