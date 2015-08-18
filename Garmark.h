//---------------------------------------------------------------------------

#ifndef GarmarkH
#define GarmarkH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TGarmarkForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button2;
	TButton *Button4;
	TLabel *Label3;
	TLabel *Label4;
	TCheckBox *CheckBox2;
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TGarmarkForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGarmarkForm *GarmarkForm;
//---------------------------------------------------------------------------
#endif