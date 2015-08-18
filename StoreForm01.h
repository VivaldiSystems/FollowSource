//---------------------------------------------------------------------------

#ifndef StoreForm01H
#define StoreForm01H
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
#include <FMX.TabControl.hpp>
//---------------------------------------------------------------------------
class TStoreForm : public TForm
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
	TLinkGridToDataSource *LinkGridToDataSource1;
	TTabControl *TabControl2;
	TTabItem *TabItem6;
	TLabel *Label8;
	TEdit *Edit11;
	TLabel *Label10;
	TEdit *Edit13;
	TLabel *Label9;
	TEdit *Edit12;
	TCheckBox *CheckBox15;
	TLabel *Label30;
	TEdit *Edit24;
	TCheckBox *CheckBox24;
	TLabel *Label35;
	TEdit *Edit28;
	TCheckBox *CheckBox25;
	TEdit *Edit56;
	TLabel *Label64;
	TCheckBox *CheckBox39;
	TCheckBox *CheckBox40;
	TCheckBox *CheckBox41;
	TCheckBox *CheckBox49;
	TEdit *Edit57;
	TLabel *Label71;
	TLabel *Label73;
	TEdit *Edit59;
	TTabItem *TabItem9;
	TGrid *Grid2;
	TButton *Button11;
	TButton *Button12;
	TTabItem *TabItem7;
	TCheckBox *CheckBox4;
	TLabel *Label15;
	TEdit *Edit18;
	TCheckBox *CheckBox5;
	TLabel *Label25;
	TEdit *Edit20;
	TCheckBox *CheckBox16;
	TEdit *Edit21;
	TEdit *Edit22;
	TLabel *Label28;
	TLabel *Label27;
	TLabel *Label29;
	TEdit *Edit23;
	TCheckBox *CheckBox18;
	TCheckBox *CheckBox19;
	TLabel *Label34;
	TEdit *Edit27;
	TCheckBox *CheckBox23;
	TCheckBox *CheckBox26;
	TLabel *Label38;
	TEdit *Edit31;
	TCheckBox *CheckBox29;
	TCheckBox *CheckBox31;
	TCheckBox *CheckBox34;
	TCheckBox *CheckBox38;
	TTabItem *TabItem8;
	TCheckBox *CheckBoxLoyalty;
	TLabel *Label31;
	TCheckBox *CheckBox20;
	TCheckBox *CheckBox21;
	TLabel *Label32;
	TEdit *Edit25;
	TLabel *Label33;
	TEdit *Edit26;
	TCheckBox *CheckBox22;
	TCheckBox *CheckBox46;
	TTabItem *TabItem10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TCheckBox *CheckBox1;
	TEdit *Edit14;
	TEdit *Edit15;
	TEdit *Edit16;
	TEdit *Edit17;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TLabel *Label36;
	TEdit *Edit29;
	TButton *Button25;
	TButton *Button26;
	TTabItem *TabItem11;
	TButton *Button10;
	TCheckBox *CheckBox6;
	TLabel *Label20;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox13;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox17;
	TButton *Button30;
	TCheckBox *CheckBox47;
	TTabItem *TabItem12;
	TEdit *Edit30;
	TLabel *Label37;
	TCheckBox *CheckBox36;
	TCheckBox *CheckBox37;
	TTabItem *TabItem13;
	TLabel *Label39;
	TLabel *Label40;
	TEdit *Edit32;
	TEdit *Edit33;
	TButton *Button27;
	TLabel *Label41;
	TLabel *Label42;
	TEdit *Edit34;
	TCheckBox *CheckBox30;
	TEdit *Edit52;
	TLabel *Label60;
	TButton *Button28;
	TCheckBox *CheckBox35;
	TButton *Button29;
	TCheckBox *CheckBox42;
	TCheckBox *CheckBox43;
	TCheckBox *CheckBox44;
	TCheckBox *CheckBox45;
	TCheckBox *CheckBox48;
	TCheckBox *CheckBox50;
	TLabel *Label72;
	TEdit *Edit58;
	TCheckBox *CheckBox51;
	TCheckBox *CheckBox52;
	TLabel *Label74;
	TTabItem *TabItem14;
	TLabel *Label44;
	TLabel *Label45;
	TLabel *Label46;
	TLabel *Label47;
	TLabel *Label48;
	TLabel *Label49;
	TLabel *Label50;
	TLabel *Label51;
	TLabel *Label52;
	TLabel *Label53;
	TLabel *Label54;
	TLabel *Label55;
	TLabel *Label56;
	TLabel *Label57;
	TLabel *Label58;
	TLabel *Label59;
	TEdit *Edit36;
	TEdit *Edit37;
	TEdit *Edit38;
	TEdit *Edit39;
	TEdit *Edit40;
	TEdit *Edit41;
	TEdit *Edit42;
	TEdit *Edit43;
	TEdit *Edit44;
	TEdit *Edit45;
	TEdit *Edit46;
	TEdit *Edit47;
	TEdit *Edit48;
	TEdit *Edit49;
	TEdit *Edit50;
	TEdit *Edit51;
	TTabItem *TabItem15;
	TLabel *Label61;
	TLabel *Label62;
	TLabel *Label63;
	TEdit *Edit53;
	TEdit *Edit54;
	TEdit *Edit55;
	TLabel *ItemTitle2;
	TLabel *ItemSubTitle2;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label16;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit10;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TLabel *Label17;
	TCheckBox *CheckBox32;
	TCheckBox *CheckBox27;
	TCheckBox *CheckBox28;
	TCheckBox *CheckBox33;
	TLabel *Label43;
	TLabel *Label67;
	TButton *Button31;
	TLabel *Label65;
	TLabel *Label66;
	TLabel *Label69;
	TLabel *Label70;
	TLabel *Label68;
	TLabel *Label18;
	TLabel *Label19;
	TLabel *Label21;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TLinkControlToField *LinkControlToField4;
	TLinkControlToField *LinkControlToField5;
	TLinkControlToField *LinkControlToField6;
	TLinkControlToField *LinkControlToField7;
	TLinkControlToField *LinkControlToField8;
	TLinkPropertyToField *LinkPropertyToField1;
	TLinkPropertyToField *LinkPropertyToField2;
	TLinkPropertyToField *LinkPropertyToField3;
	TLinkControlToField *LinkControlToField9;
	TLinkControlToField *LinkControlToField10;
	TLinkControlToField *LinkControlToField11;
	TLinkControlToField *LinkControlToField12;
	TLinkControlToField *LinkControlToField13;
	TLinkControlToField *LinkControlToField14;
	TLinkControlToField *LinkControlToField15;
	TLinkControlToField *LinkControlToField16;
	TLinkControlToField *LinkControlToField17;
	TLinkControlToField *LinkControlToField18;
	TLinkControlToField *LinkControlToField19;
	TLinkControlToField *LinkControlToField20;
	TLinkControlToField *LinkControlToField21;
	TLinkControlToField *LinkControlToField22;
	TLinkControlToField *LinkControlToField23;
	TLinkControlToField *LinkControlToField25;
	TLinkControlToField *LinkControlToField26;
	TLinkControlToField *LinkControlToField27;
	TLinkControlToField *LinkControlToField24;
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TStoreForm(TComponent* Owner);
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
extern PACKAGE TStoreForm *StoreForm;
//---------------------------------------------------------------------------
#endif