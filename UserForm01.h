//---------------------------------------------------------------------------

#ifndef UserForm01H
#define UserForm01H
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
class TUserForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TLabel *Label1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TGrid *Grid1;
	TDataSource *DataSource2;
	TDataSource *DataSource1;
	TADOQuery *ADOQuery1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TADOQuery *ADOQuery2;
	TDataSource *DataSource3;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox17;
	TLabel *Label2;
	TEdit *Edit2;
	TEdit *Edit6;
	TEdit *Edit10;
	TEdit *Edit1;
	TLabel *Label9;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label7;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TCheckBox *CheckBox6;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox13;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox15;
	TCheckBox *CheckBox16;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TLinkControlToField *LinkControlToField9;
	TLinkControlToField *LinkControlToField10;
	TLinkControlToField *LinkControlToField11;
	TLinkControlToField *LinkControlToField12;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TLinkControlToField *LinkControlToField4;
	TLinkControlToField *LinkControlToField5;
	TLinkControlToField *LinkControlToField6;
	TLinkControlToField *LinkControlToField7;
	TLinkControlToField *LinkControlToField8;
	TLinkControlToField *LinkControlToField13;
	TLinkControlToField *LinkControlToField14;
	TLinkControlToField *LinkControlToField15;
	TLinkControlToField *LinkControlToField16;
	TLinkControlToField *LinkControlToField17;
	TLinkControlToField *LinkControlToField18;
	TLinkControlToField *LinkControlToField19;
	TLinkControlToField *LinkControlToField20;
	TLinkControlToField *LinkControlToField21;
	TLabel *Label5;
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TUserForm(TComponent* Owner);
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
extern PACKAGE TUserForm *UserForm;
//---------------------------------------------------------------------------
#endif
