//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "FM_PopupMessage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TFM_PopupMessage01 *FM_PopupMessage01;
//---------------------------------------------------------------------------
__fastcall TFM_PopupMessage01::TFM_PopupMessage01(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFM_PopupMessage01::Timer1Timer(TObject *Sender)
{
 Timer1->Enabled = False;
   this->Close();

}
//---------------------------------------------------------------------------
void __fastcall TFM_PopupMessage01::FormShow(TObject *Sender)
{
   Timer1->Enabled = True;
}
//---------------------------------------------------------------------------
