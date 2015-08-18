//---------------------------------------------------------------------------

#ifndef InventoryForm1H
#define InventoryForm1H
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
#include <FMX.Memo.hpp>
//---------------------------------------------------------------------------
class TInventoryForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TADOQuery *ADOQuery1;
	TGrid *Grid1;
	TButton *Button3;
	TADOQuery *ADOQuery2;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TButton *Button4;
	TLabel *Label3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TButton *Button5;
	TButton *Button6;
	TADOQuery *ADOQuery3;
	TMemo *Memo1;
	TToolBar *ToolBar1;
	TLabel *Label4;
	TSpeedButton *SpeedButton4;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TInventoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInventoryForm *InventoryForm;
//---------------------------------------------------------------------------
#endif
