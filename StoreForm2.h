//---------------------------------------------------------------------------

#ifndef StoreForm2H
#define StoreForm2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Types.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Ani.hpp>
#include <FMX.TabControl.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
#include <Fmx.Bind.Navigator.hpp>
#include <FMX.Grid.hpp>
#include <Data.Bind.Grid.hpp>
#include <Fmx.Bind.Grid.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Colors.hpp>
#include <FMX.Memo.hpp>
#include <Data.FMTBcd.hpp>
#include <Data.SqlExpr.hpp>
//---------------------------------------------------------------------------
class TStoreForm01 : public TForm
{
__published:	// IDE-managed Components
	TLayout *MainLayout;
	TLayout *RightLayout;
	TLayout *ToolbarHolder;
	TPopup *ToolbarPopup;
	TFloatAnimation *ToolbarPopupAnimation;
	TTabControl *TabControl1;
	TTabItem *TabItem1;
	TVertScrollBox *Article1;
	TLayout *ArticleHeaderLayout1;
	TLayout *Layout1;
	TTabItem *TabItem2;
	TVertScrollBox *Article2;
	TLayout *ArticleHeaderLayout2;
	TLayout *Layout4;
	TLabel *ItemTitle2;
	TLabel *ItemSubTitle2;
	TTabItem *TabItem3;
	TVertScrollBox *Article3;
	TLayout *ArticleHeaderLayout3;
	TLayout *Layout6;
	TLabel *ItemTitle3;
	TLabel *ItemSubTitle3;
	TTabItem *TabItem4;
	TVertScrollBox *Article4;
	TLayout *ArticleHeaderLayout4;
	TLayout *Layout8;
	TToolBar *ToolBar1;
	TButton *ToolbarApplyButton;
	TButton *ToolbarCloseButton;
	TButton *ToolbarAddButton;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TDataSource *DataSource1;
	TBindSourceDB *BindSourceDB2;
	TGrid *Grid1;
	TEdit *Edit1;
	TLabel *Label1;
	TButton *Button1;
	TADOQuery *ADOQuery1;
	TBindSourceDB *BindSourceDB3;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TTabItem *TabItem5;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TLinkControlToField *LinkControlToField1;
	TTabControl *TabControl2;
	TTabItem *TabItem6;
	TTabItem *TabItem9;
	TEdit *Edit5;
	TEdit *Edit6;
	TEdit *Edit7;
	TEdit *Edit8;
	TEdit *Edit9;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TLinkControlToField *LinkControlToField3;
	TLinkControlToField *LinkControlToField4;
	TLinkControlToField *LinkControlToField5;
	TLinkControlToField *LinkControlToField6;
	TEdit *Edit10;
	TLabel *Label7;
	TLinkControlToField *LinkControlToField14;
	TLabel *Label16;
	TLinkPropertyToField *LinkPropertyToField2;
	TEdit *Edit19;
	TLabel *Label18;
	TLabel *Label17;
	TButton *Button2;
	TLabel *Label21;
	TLabel *Label22;
	TListBox *TicketItemsListBox;
	TButton *Button3;
	TLabel *Label24;
	TLinkPropertyToField *LinkPropertyToField1;
	TPanel *Panel1;
	TDataSource *DataSource2;
	TBindSourceDB *BindSourceDB4;
	TButton *Button14;
	TButton *Button15;
	TButton *Button16;
	TButton *Button17;
	TButton *Button18;
	TButton *Button19;
	TButton *Button20;
	TButton *Button21;
	TButton *Button22;
	TButton *Button23;
	TButton *Button24;
	TLinkGridToDataSource *LinkGridToDataSource2;
	TColorButton *ColorButton1;
	TColorButton *ColorButton2;
	TColorButton *ColorButton3;
	TColorButton *ColorButton4;
	TColorButton *ColorButton5;
	TColorButton *ColorButton6;
	TColorButton *ColorButton7;
	TColorButton *ColorButton8;
	TColorButton *ColorButton9;
	TColorButton *ColorButton10;
	TColorButton *ColorButton11;
	TColorButton *ColorButton12;
	TColorButton *ColorButton13;
	TColorButton *ColorButton14;
	TColorButton *ColorButton15;
	TColorButton *ColorButton16;
	TColorButton *ColorButton17;
	TColorButton *ColorButton18;
	TColorButton *ColorButton19;
	TColorButton *ColorButton20;
	TColorButton *ColorButton21;
	TColorButton *ColorButton22;
	TMemo *Memo1;
	TBindSourceDB *BindSourceDB5;
	TLinkFillControlToField *LinkFillControlToField1;
	TListBox *ListBox1;
	TBindSourceDB *BindSourceDB6;
	TLinkFillControlToField *LinkFillControlToField2;
	TButton *Button4;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TLabel *Label23;
	TLabel *Label26;
	TCalendarEdit *CalendarEdit1;
	TGrid *Grid2;
	TButton *Button11;
	TButton *Button12;
	TBindSourceDB *BindSourceDB7;
	TLinkFillControlToField *LinkFillControlToField3;
	TBindSourceDB *BindSourceDB8;
	TLinkGridToDataSource *LinkGridToDataSource3;
	TLabel *Label19;
	TLabel *Label8;
	TEdit *Edit11;
	TLinkPropertyToField *LinkPropertyToField4;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField7;
	TLabel *Label10;
	TEdit *Edit13;
	TLinkControlToField *LinkControlToField8;
	TLinkControlToField *LinkControlToField9;
	TLabel *Label9;
	TEdit *Edit12;
	TLinkControlToField *LinkControlToField10;
	TTabItem *TabItem7;
	TTabItem *TabItem8;
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
	TLinkControlToField *LinkControlToField11;
	TLinkControlToField *LinkControlToField12;
	TLinkControlToField *LinkControlToField13;
	TLinkControlToField *LinkControlToField15;
	TLinkControlToField *LinkControlToField16;
	TCheckBox *CheckBox2;
	TCheckBox *CheckBox3;
	TLinkControlToField *LinkControlToField17;
	TLinkControlToField *LinkControlToField18;
	TCheckBox *CheckBox4;
	TLabel *Label15;
	TEdit *Edit18;
	TLinkControlToField *LinkControlToField19;
	TLinkControlToField *LinkControlToField20;
	TCheckBox *CheckBox5;
	TLinkControlToField *LinkControlToField21;
	TTabItem *TabItem11;
	TButton *Button10;
	TADOTable *ADOTable1;
	TADOQuery *ADOQuery2;
	TCheckBox *CheckBox6;
	TLabel *Label20;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TCheckBox *CheckBox9;
	TCheckBox *CheckBox10;
	TCheckBox *CheckBox11;
	TCheckBox *CheckBox13;
	TCheckBox *CheckBox12;
	TCheckBox *CheckBox14;
	TCheckBox *CheckBox15;
	TLinkControlToField *LinkControlToField22;
	TLabel *Label25;
	TEdit *Edit20;
	TLinkControlToField *LinkControlToField23;
	TCheckBox *CheckBox16;
	TLinkControlToField *LinkControlToField24;
	TCheckBox *CheckBox17;
	TEdit *Edit21;
	TEdit *Edit22;
	TLabel *Label28;
	TLinkControlToField *LinkControlToField25;
	TLinkControlToField *LinkControlToField26;
	TLabel *Label27;
	TLabel *Label29;
	TEdit *Edit23;
	TLinkControlToField *LinkControlToField27;
	TCheckBox *CheckBox18;
	TLinkControlToField *LinkControlToField28;
	TLabel *Label30;
	TEdit *Edit24;
	TLinkControlToField *LinkControlToField29;
	TCheckBox *CheckBox19;
	TLinkControlToField *LinkControlToField30;
	TCheckBox *CheckBoxLoyalty;
	TLabel *Label31;
	TCheckBox *CheckBox20;
	TCheckBox *CheckBox21;
	TLabel *Label32;
	TEdit *Edit25;
	TLabel *Label33;
	TEdit *Edit26;
	TLinkControlToField *LinkControlToField31;
	TLinkControlToField *LinkControlToField32;
	TLinkControlToField *LinkControlToField33;
	TLinkControlToField *LinkControlToField34;
	TLinkControlToField *LinkControlToField35;
	TCheckBox *CheckBox22;
	TLinkControlToField *LinkControlToField36;
	TLabel *Label34;
	TEdit *Edit27;
	TLinkControlToField *LinkControlToField37;
	TCheckBox *CheckBox23;
	TLinkControlToField *LinkControlToField38;
	TCheckBox *CheckBox24;
	TLinkControlToField *LinkControlToField39;
	TLabel *Label35;
	TEdit *Edit28;
	TLinkControlToField *LinkControlToField40;
	TCheckBox *CheckBox25;
	TLinkControlToField *LinkControlToField41;
	TLabel *Label36;
	TEdit *Edit29;
	TLinkControlToField *LinkControlToField42;
	TTabItem *TabItem12;
	TEdit *Edit30;
	TLabel *Label37;
	TLinkControlToField *LinkControlToField43;
	TButton *Button25;
	TButton *Button26;
	TCheckBox *CheckBox26;
	TLinkControlToField *LinkControlToField44;
	TLabel *Label38;
	TEdit *Edit31;
	TLinkControlToField *LinkControlToField45;
	TCheckBox *CheckBox27;
	TLinkControlToField *LinkControlToField46;
	TCheckBox *CheckBox28;
	TLinkControlToField *LinkControlToField47;
	TTabItem *TabItem13;
	TLabel *Label39;
	TLabel *Label40;
	TEdit *Edit32;
	TEdit *Edit33;
	TButton *Button27;
	TLabel *Label41;
	TCheckBox *CheckBox29;
	TLinkControlToField *LinkControlToField48;
	TLabel *Label42;
	TEdit *Edit34;
	TLinkControlToField *LinkControlToField49;
	TEdit *Edit35;
	TLabel *Label43;
	TLinkControlToField *LinkControlToField50;
	TCheckBox *CheckBox30;
	TLinkControlToField *LinkControlToField51;
	TCheckBox *CheckBox31;
	TLinkControlToField *LinkControlToField52;
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
	TLinkControlToField *LinkControlToField53;
	TLinkControlToField *LinkControlToField54;
	TLinkControlToField *LinkControlToField55;
	TLinkControlToField *LinkControlToField56;
	TLinkControlToField *LinkControlToField57;
	TLinkControlToField *LinkControlToField58;
	TLinkControlToField *LinkControlToField59;
	TLinkControlToField *LinkControlToField60;
	TLinkControlToField *LinkControlToField61;
	TLinkControlToField *LinkControlToField62;
	TLinkControlToField *LinkControlToField63;
	TLinkControlToField *LinkControlToField64;
	TLinkControlToField *LinkControlToField65;
	TLinkControlToField *LinkControlToField66;
	TLinkControlToField *LinkControlToField67;
	TLinkControlToField *LinkControlToField68;
	TCheckBox *CheckBox32;
	TLinkControlToField *LinkControlToField69;
	TCheckBox *CheckBox33;
	TLinkControlToField *LinkControlToField70;
	TEdit *Edit52;
	TLabel *Label60;
	TButton *Button28;
	TCheckBox *CheckBox34;
	TLinkControlToField *LinkControlToField71;
	TTabItem *TabItem15;
	TLabel *Label61;
	TLabel *Label62;
	TLabel *Label63;
	TEdit *Edit53;
	TEdit *Edit54;
	TEdit *Edit55;
	TLinkControlToField *LinkControlToField72;
	TLinkControlToField *LinkControlToField73;
	TLinkControlToField *LinkControlToField74;
	TCheckBox *CheckBox35;
	TLinkControlToField *LinkControlToField75;
	TEdit *Edit56;
	TLabel *Label64;
	TLinkControlToField *LinkControlToField76;
	TCheckBox *CheckBox36;
	TLinkControlToField *LinkControlToField77;
	TButton *Button29;
	TCheckBox *CheckBox37;
	TLinkControlToField *LinkControlToField78;
	TButton *Button30;
	TADOQuery *ADOTable2;
	TADOQuery *ADOQuery3;
	TCheckBox *CheckBox38;
	TLinkControlToField *LinkControlToField79;
	TLabel *Label65;
	TLabel *Label66;
	TButton *Button31;
	TLabel *Label67;
	TLabel *Label68;
	TLinkPropertyToField *LinkPropertyToField3;
	TLinkPropertyToField *LinkPropertyToField5;
	TLabel *Label69;
	TLabel *Label70;
	TLinkPropertyToField *LinkPropertyToField6;
	TCheckBox *CheckBox39;
	TLinkControlToField *LinkControlToField80;
	TCheckBox *CheckBox40;
	TLinkControlToField *LinkControlToField81;
	TCheckBox *CheckBox41;
	TLinkControlToField *LinkControlToField82;
	TCheckBox *CheckBox42;
	TLinkControlToField *LinkControlToField83;
	TCheckBox *CheckBox43;
	TLinkControlToField *LinkControlToField84;
	TCheckBox *CheckBox44;
	TLinkControlToField *LinkControlToField85;
	TCheckBox *CheckBox45;
	TLinkControlToField *LinkControlToField86;
	TCheckBox *CheckBox46;
	TLinkControlToField *LinkControlToField87;
	TCheckBox *CheckBox47;
	TSQLTable *SQLTable1;
	TADOQuery *ADOQuery4;
	TCheckBox *CheckBox48;
	TLinkControlToField *LinkControlToField88;
	TCheckBox *CheckBox49;
	TLinkControlToField *LinkControlToField89;
	TEdit *Edit57;
	TLabel *Label71;
	TLinkControlToField *LinkControlToField90;
	TCheckBox *CheckBox50;
	TLabel *Label72;
	TEdit *Edit58;
	TLinkControlToField *LinkControlToField91;
	TLabel *Label73;
	TEdit *Edit59;
	TLinkControlToField *LinkControlToField92;
	TCheckBox *CheckBox51;
	TCheckBox *CheckBox52;
	TLinkControlToField *LinkControlToField93;
	TLinkControlToField *LinkControlToField94;
	TLabel *Label74;
	TToolBar *ToolBar2;
	TLabel *Label75;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Grid1Click(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall SaveChangesIListBoxItemClick(TObject *Sender);
	void __fastcall Button17Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall Button16Click(TObject *Sender);
	void __fastcall Button18Click(TObject *Sender);
	void __fastcall Button19Click(TObject *Sender);
	void __fastcall Button20Click(TObject *Sender);
	void __fastcall Button21Click(TObject *Sender);
	void __fastcall Button22Click(TObject *Sender);
	void __fastcall Button23Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall UpdateTicketView();
	void __fastcall ColorButton1Click(TObject *Sender);
	void __fastcall ColorButton2Click(TObject *Sender);
	void __fastcall ColorButton3Click(TObject *Sender);
	void __fastcall ColorButton4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall ColorButton5Click(TObject *Sender);
	void __fastcall ColorButton6Click(TObject *Sender);
	void __fastcall ColorButton18Click(TObject *Sender);
	void __fastcall ColorButton8Click(TObject *Sender);
	void __fastcall ColorButton9Click(TObject *Sender);
	void __fastcall ColorButton10Click(TObject *Sender);
	void __fastcall ColorButton11Click(TObject *Sender);
	void __fastcall ColorButton22Click(TObject *Sender);
	void __fastcall ColorButton21Click(TObject *Sender);
	void __fastcall ColorButton20Click(TObject *Sender);
	void __fastcall ColorButton19Click(TObject *Sender);
	void __fastcall ColorButton17Click(TObject *Sender);
	void __fastcall ColorButton15Click(TObject *Sender);
	void __fastcall ColorButton16Click(TObject *Sender);
	void __fastcall ColorButton14Click(TObject *Sender);
	void __fastcall ColorButton7Click(TObject *Sender);
	void __fastcall ColorButton13Click(TObject *Sender);
	void __fastcall ColorButton12Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall CheckBox19Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
private:	// User declarations
	TPointF FGestureOrigin;
	bool FGestureInProgress;
	void ShowToolbar(bool AShow);

	TStringList *TempListQty;
	TStringList *TempListItemCode;
	TStringList *TempListItemDescription;
	TStringList *TempListItemUpcharge;
	TStringList *TempListPrice;
	TStringList *TempListTax;
	float* aPrices;
	float* aLinePrices;
	float fTotalPrices;
    bool blnUpcharge;
	AnsiString strQty;
	AnsiString strClass;
	AnsiString strUpcharge;
	float fltPrice;
	bool blnSubDCItem;

public:		// User declarations
	__fastcall TStoreForm01(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TStoreForm01 *StoreForm01;
//---------------------------------------------------------------------------
#endif