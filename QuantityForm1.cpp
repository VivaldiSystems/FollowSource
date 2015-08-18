//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "MainMenu.h"
#include "QuantityForm1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TQuantityForm *QuantityForm;
//---------------------------------------------------------------------------
__fastcall TQuantityForm::TQuantityForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TQuantityForm::Button1Click(TObject *Sender)
{
	MainMenuForm->strEnterQuantity  = Edit1->Text;

		if( MainMenuForm->strEnterQuantity == "" )
					{
						MainMenuForm->strEnterQuantity = "0";
                    }
	this->Close();

}
//---------------------------------------------------------------------------

void __fastcall TQuantityForm::FormShow(TObject *Sender)
{
   Edit1->SetFocus();
   Label1->Text = MainMenuForm->strQuantityType;
}
//---------------------------------------------------------------------------

