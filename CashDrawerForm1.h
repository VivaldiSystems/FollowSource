//---------------------------------------------------------------------------

#ifndef CashDrawerForm1H
#define CashDrawerForm1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
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
#include <FMX.Edit.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Menus.hpp>
//---------------------------------------------------------------------------
class TCashDrawerForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TGrid *Grid1;
	TADOQuery *ADOQuery1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TLabel *Label1;
	TComboEdit *ComboEdit1;
	TButton *Button6;
	TEdit *Edit1;
	TLabel *Label2;
	TComboEdit *ComboEdit2;
	TLabel *Label3;
	TLabel *Label4;
	TCalendarEdit *CalendarEdit1;
	TButton *Button7;
	TPopupMenu *PopupMenu1;
	TMenuItem *MenuItem1;
	TCheckBox *CheckBox1;
	TButton *Button8;
	TToolBar *ToolBar1;
	TLabel *Label5;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ComboEdit1Change(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall ComboEdit2Change(TObject *Sender);
	void __fastcall CalendarEdit1Change(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall CheckBox1Change(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCashDrawerForm(TComponent* Owner);
	AnsiString strType;
};
//---------------------------------------------------------------------------
extern PACKAGE TCashDrawerForm *CashDrawerForm;
//---------------------------------------------------------------------------
#endif
