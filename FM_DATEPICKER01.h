//---------------------------------------------------------------------------

#ifndef FM_DATEPICKER01H
#define FM_DATEPICKER01H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TFM_DATEPICKER : public TForm
{
__published:	// IDE-managed Components
	TCalendar *Calendar1;
	TLabel *Label1;
	TButton *Button1;
	void __fastcall Calendar1DateSelected(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFM_DATEPICKER(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFM_DATEPICKER *FM_DATEPICKER;
//---------------------------------------------------------------------------
#endif
