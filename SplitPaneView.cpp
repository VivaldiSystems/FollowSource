//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SplitPaneView.h"
#include "GridView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TSplitPaneForm *SplitPaneForm;
//---------------------------------------------------------------------------
__fastcall TSplitPaneForm::TSplitPaneForm(TComponent* Owner)
	: TForm(Owner)
{
		 TabControl1->TabIndex = 0;
			 RemoveCustomerListBoxItem->Enabled = false;
		 	 SaveChangesIListBoxItem->Visible = false;
			 RemoveCustomerListBoxItem->Visible = false;
		 Edit1->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSplitPaneForm::HeaderButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSplitPaneForm::FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
		  bool &Handled)
{
	float DX, DY;

	if (EventInfo.GestureID == igiPan) {
		if (EventInfo.Flags.Contains(TInteractiveGestureFlag::gfBegin)
		  && (Sender == ToolbarPopup || EventInfo.Location.Y > (ClientHeight - 70))) {
			FGestureOrigin = EventInfo.Location;
			FGestureInProgress = true;
		}
	}

	if (FGestureInProgress && EventInfo.Flags.Contains(TInteractiveGestureFlag::gfEnd)) {
		FGestureInProgress = false;
		DX = EventInfo.Location.X - FGestureOrigin.X;
		DY = EventInfo.Location.Y - FGestureOrigin.Y;
		if (fabs(DY) > fabs(DX)) {
			ShowToolbar(DY < 0);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  float X, float Y)
{
	ShowToolbar(Button == TMouseButton::mbRight);
}
//---------------------------------------------------------------------------
void TSplitPaneForm::ShowToolbar(bool AShow)
{
  ToolbarPopup->Width = ClientWidth;
  ToolbarPopup->PlacementRectangle->Rect = TRect(0, ClientHeight-ToolbarPopup->Height, ClientWidth-1, ClientHeight-1);
  ToolbarPopupAnimation->StartValue = ToolbarPopup->Height;
  ToolbarPopupAnimation->StopValue = 0;

  ToolbarPopup->IsOpen = AShow;
}


//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::FormActivate(TObject *Sender)
{
	WindowState = TWindowState::wsMaximized;
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::ToolbarCloseButtonClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift)
{
	if (Key == vkEscape) {
		Close();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSplitPaneForm::Button1Click(TObject *Sender)
{

	  ADOQuery1->Active = false;

	  AnsiString strNumber = "1234567890";

	  //ShowMessage(strNumber.AnsiPos( Edit1->Text.SubString(0,1) ));

	  if( strNumber.AnsiPos( Edit1->Text.SubString(0,1) ) > 0 )
	  {


	  ADOQuery1->SQL->Text = "Select name,acct,address1,address2,city,state,zip,phone,address1b,address2b,cityb,stateb,zipb,phoneb,primekey from customer where acct like '%"+Edit1->Text+"%' order by acct";

	  }
	  else
	  {

	   ADOQuery1->SQL->Text = "Select name,acct,address1,address2,city,state,zip,phone,address1b,address2b,cityb,stateb,zipb,phoneb,primekey from customer where name like '%"+Edit1->Text+"%' order by name";


      }

	  ADOQuery1->Active = true;

}
//---------------------------------------------------------------------------


void __fastcall TSplitPaneForm::Grid1Click(TObject *Sender)
{
      //ShowMessage("Customer Selected");
}
//---------------------------------------------------------------------------



void __fastcall TSplitPaneForm::SelectCustomerListBoxItemClick(TObject *Sender)
{
		TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;
		RemoveCustomerListBoxItem->Enabled = false;
			SaveChangesIListBoxItem->Visible = false;
	RemoveCustomerListBoxItem->Visible = false;
}



void __fastcall TSplitPaneForm::RemoveCustomerListBoxItemClick(TObject *Sender)
{

   //	MessageDlg("Are you sure you sould like to Remove this Record?", mtConfirmation, TMsgDlgButtons() << mbOK, 0);


   if( 	RemoveCustomerListBoxItem->Enabled == true )
   {
	 ADOQuery1->Delete();
	 ADOQuery1->Post();
	 ShowMessage("Record was Removed!");
	 TabControl1->TabIndex = 0;
	}
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::EditCustomerListBoxItemClick(TObject *Sender)
{
	TabControl1->TabIndex = 1;
	RemoveCustomerListBoxItem->Enabled = true;
	SaveChangesIListBoxItem->Visible = true;
	RemoveCustomerListBoxItem->Visible = true;

}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::AdvancedSearchListBoxItemClick(TObject *Sender)
{
	TabControl1->TabIndex = ((TFmxObject *)Sender)->Tag;
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::AddCustomerListBoxItemClick(TObject *Sender)
{
	TabControl1->TabIndex = 1;
	ADOQuery1->Append();
}
//---------------------------------------------------------------------------



void __fastcall TSplitPaneForm::Button5Click(TObject *Sender)
{
	ADOQuery1->Post();
}
//---------------------------------------------------------------------------

void __fastcall TSplitPaneForm::SaveChangesIListBoxItemClick(TObject *Sender)
{

		 ADOQuery1->Post();

}
//---------------------------------------------------------------------------


