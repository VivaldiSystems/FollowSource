//---------------------------------------------------------------------------

#ifndef FM_PopupMessageH
#define FM_PopupMessageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Ani.hpp>
//---------------------------------------------------------------------------
class TFM_PopupMessage01 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TTimer *Timer1;
	TColorAnimation *ColorAnimation1;
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFM_PopupMessage01(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFM_PopupMessage01 *FM_PopupMessage01;
//---------------------------------------------------------------------------
#endif
