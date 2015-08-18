//---------------------------------------------------------------------------

#ifndef ClassForm01H
#define ClassForm01H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Grid.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
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
class TClassForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TLabel *ItemTitle2;
	TEdit *Edit6;
	TCheckBox *CheckBox1;
	TEdit *Edit10;
	TEdit *Edit1;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox3;
	TGrid *Grid1;
	TDataSource *DataSource2;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	TLabel *Label3;
	TLabel *Label4;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TLinkControlToField *LinkControlToField4;
	TLinkControlToField *LinkControlToField5;
	TLinkControlToField *LinkControlToField6;
	TLinkControlToField *LinkControlToField7;
	TLinkControlToField *LinkControlToField8;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TLabel *Label2;
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TClassForm(TComponent* Owner);
		TStringList *TempListQty;
	TStringList *TempListItemCode;
	TStringList *TempListItemDescription;
	TStringList *TempListItemUpcharge;
	TStringList *TempListPrice;
	TStringList *TempListTax;
	float* aPrices;
	float* aLinePrices;
	AnsiString strSelectedClass;
	float fTotalPrices;
    bool blnUpcharge;
	AnsiString strQty;
	AnsiString strClass;
	AnsiString strUpcharge;
	float fltPrice;
	bool blnSubDCItem;
};
//---------------------------------------------------------------------------
extern PACKAGE TClassForm *ClassForm;
//---------------------------------------------------------------------------
#endif