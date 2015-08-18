//---------------------------------------------------------------------------

#ifndef HotelForm2H
#define HotelForm2H
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
//---------------------------------------------------------------------------
class THotelForm : public TForm
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
	TLinkControlToField *LinkControlToField2;
	TTabControl *TabControl2;
	TTabItem *TabItem6;
	TTabItem *TabItem7;
	TTabItem *TabItem8;
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
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *Edit11;
	TEdit *Edit12;
	TEdit *Edit13;
	TEdit *Edit14;
	TEdit *Edit15;
	TEdit *Edit16;
	TLinkControlToField *LinkControlToField8;
	TLinkControlToField *LinkControlToField9;
	TLinkControlToField *LinkControlToField10;
	TLinkControlToField *LinkControlToField11;
	TLinkControlToField *LinkControlToField12;
	TLabel *Label14;
	TEdit *Edit17;
	TLinkControlToField *LinkControlToField13;
	TLabel *Label15;
	TEdit *Edit18;
	TComboBox *ComboBox1;
	TLinkControlToField *LinkControlToField14;
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
	TADOQuery *ADOQuery2;
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
	TLinkPropertyToField *LinkPropertyToField3;
	TADOQuery *ADOQuery3;
	TBindSourceDB *BindSourceDB5;
	TLinkFillControlToField *LinkFillControlToField1;
	TListBox *ListBox1;
	TADOQuery *ADOQuery4;
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
	TEdit *Edit20;
	TLabel *Label25;
	TMemo *Memo2;
	TLabel *Label27;
	TCheckBox *CheckBox1;
	TCheckBox *CheckBox2;
	TComboEdit *ComboEdit1;
	TLabel *Label28;
	TEdit *Edit22;
	TLabel *Label29;
	TEdit *Edit21;
	TLabel *Label30;
	TCheckBox *CheckBox3;
	TCheckBox *CheckBox4;
	TCheckBox *CheckBox5;
	TLabel *Label31;
	TEdit *Edit23;
	TEdit *Edit24;
	TLabel *Label32;
	TEdit *Edit25;
	TEdit *Edit26;
	TEdit *Edit27;
	TLabel *Label34;
	TLabel *Label35;
	TLabel *Label36;
	TEdit *Edit28;
	TLabel *Label39;
	TButton *Button10;
	TCheckBox *CheckBox6;
	TEdit *Edit29;
	TLabel *Label40;
	TGrid *Grid2;
	TButton *Button11;
	TButton *Button12;
	TTabItem *TabItem10;
	TButton *Button13;
	TButton *Button25;
	TButton *Button26;
	TCheckBox *CheckBox7;
	TCheckBox *CheckBox8;
	TLinkControlToField *LinkControlToField15;
	TLinkControlToField *LinkControlToField16;
	TLinkControlToField *LinkControlToField17;
	TLinkControlToField *LinkControlToField18;
	TLinkControlToField *LinkControlToField19;
	TLinkControlToField *LinkControlToField20;
	TLinkControlToField *LinkControlToField21;
	TLinkControlToField *LinkControlToField22;
	TLinkControlToField *LinkControlToField23;
	TLinkControlToField *LinkControlToField24;
	TLinkControlToField *LinkControlToField25;
	TLinkControlToField *LinkControlToField26;
	TLinkControlToField *LinkControlToField27;
	TLinkControlToField *LinkControlToField30;
	TLinkControlToField *LinkControlToField29;
	TLinkControlToField *LinkControlToField31;
	TLinkControlToField *LinkControlToField34;
	TADOQuery *ADOQuery5;
	TBindSourceDB *BindSourceDB7;
	TLinkFillControlToField *LinkFillControlToField3;
	TTabItem *TabItem11;
	TGrid *Grid3;
	TADOQuery *ADOQuery6;
	TBindSourceDB *BindSourceDB8;
	TLinkGridToDataSource *LinkGridToDataSource3;
	TADOQuery *ADOQuery7;
	TBindSourceDB *BindSourceDB9;
	TLinkGridToDataSource *LinkGridToDataSource4;
	TButton *Button27;
	TButton *Button28;
	TCornerButton *CornerButton1;
	TButton *Button29;
	TButton *Button30;
	TLinkControlToField *LinkControlToField28;
	TLabel *Label16;
	TEdit *Edit30;
	TLinkControlToField *LinkControlToField33;
	TADOQuery *ADOQuery8;
	TEdit *Edit31;
	TLabel *Label19;
	TButton *Button31;
	TADOQuery *ADOQuery9;
	TLabel *Label20;
	TLinkPropertyToField *LinkPropertyToField2;
	TEdit *Edit32;
	TLabel *Label33;
	TLinkControlToField *LinkControlToField35;
	TLinkControlToField *LinkControlToField32;
	TButton *Button32;
	TLabel *Label37;
	TButton *Button43;
	TADOQuery *ADOQuery10;
	TLabel *Label38;
	TEdit *Edit33;
	TLinkControlToField *LinkControlToField36;
	TLinkControlToField *LinkControlToField7;
	TLabel *Label41;
	TButton *Button44;
	TLabel *Label42;
	TEdit *Edit34;
	TImage *Image27;
	TImage *Image28;
	TImage *Image29;
	TImage *Image30;
	TImage *Image31;
	TImage *Image32;
	TImage *Image37;
	TImage *Image33;
	TImage *Image34;
	TImage *Image35;
	TImage *Image38;
	TToolBar *ToolBar3;
	TLabel *Label44;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton9;
	TSpeedButton *SpeedButton10;
	TSpeedButton *SpeedButton11;
	TSpeedButton *SpeedButton12;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Grid1Click(TObject *Sender);
	void __fastcall SelectCustomerListBoxItemClick(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall AddCustomerListBoxItemClick(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall SaveChangesIListBoxItemClick(TObject *Sender);
	void __fastcall TicketItemsListBoxClick(TObject *Sender);
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
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
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
	void __fastcall ListBox1Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall CornerButton1Click(TObject *Sender);
	void __fastcall CheckBox3Exit(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Edit4Change(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall ComboEdit1Change(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button33Click(TObject *Sender);
	void __fastcall Button34Click(TObject *Sender);
	void __fastcall Button35Click(TObject *Sender);
	void __fastcall Button36Click(TObject *Sender);
	void __fastcall Button37Click(TObject *Sender);
	void __fastcall Button38Click(TObject *Sender);
	void __fastcall Button39Click(TObject *Sender);
	void __fastcall Button40Click(TObject *Sender);
	void __fastcall Button41Click(TObject *Sender);
	void __fastcall Button42Click(TObject *Sender);
	void __fastcall Button43Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Grid1DblClick(TObject *Sender);
	void __fastcall Button44Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton5Click(TObject *Sender);
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
	__fastcall THotelForm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE THotelForm *HotelForm;
//---------------------------------------------------------------------------
#endif
