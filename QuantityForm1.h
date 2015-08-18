//---------------------------------------------------------------------------

#ifndef QuantityForm1H
#define QuantityForm1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Types.hpp>
//---------------------------------------------------------------------------
class TQuantityForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TQuantityForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuantityForm *QuantityForm;
//---------------------------------------------------------------------------
#endif
