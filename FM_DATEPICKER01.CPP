//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FM_DATEPICKER01.h"
#include "MainMenu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFM_DATEPICKER *FM_DATEPICKER;
//---------------------------------------------------------------------------
__fastcall TFM_DATEPICKER::TFM_DATEPICKER(TComponent* Owner)
	: TForm(Owner)
{

Calendar1->Date = Now()+MainMenuForm->intDaysToPickup;
   //Calendar1->Date = MainMenuForm->ConvertDate(DateTimeToStr(Now()+MainMenuForm->intDaysToPickup).SubString(1,10));

}
//---------------------------------------------------------------------------
void __fastcall TFM_DATEPICKER::Calendar1DateSelected(TObject *Sender)
{
  MainMenuForm->strPickupDate = DateTimeToStr(Calendar1->Date);

	MainMenuForm->strDateOut =   DateTimeToStr(Calendar1->Date);
		this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFM_DATEPICKER::Button1Click(TObject *Sender)
{
        MainMenuForm->strPickupDate = DateTimeToStr(Calendar1->Date);

	MainMenuForm->strDateOut =   DateTimeToStr(Calendar1->Date);

	this->Close();
}
//---------------------------------------------------------------------------
