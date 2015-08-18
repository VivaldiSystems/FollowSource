//---------------------------------------------------------------------------

#ifndef WriteTicketH
#define WriteTicketH
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
#include <FMX.Menus.hpp>
#include <FMX.Effects.hpp>
//---------------------------------------------------------------------------
class TWriteTicketForm01 : public TForm
{
__published:	// IDE-managed Components
	TLayout *MainLayout;
	TLayout *LeftLayout;
	TLayout *HeaderLayout;
	TLabel *TitleLabel1;
	TLayout *Layout2;
	TButton *HeaderButton;
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
	TListBox *ListBoxItems;
	TMetropolisUIListBoxItem *AddCustomerListBoxItem;
	TMetropolisUIListBoxItem *EditCustomerListBoxItem;
	TMetropolisUIListBoxItem *WriteTicketListBoxItem;
	TMetropolisUIListBoxItem *QuickTicketListBoxItem;
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
	TMetropolisUIListBoxItem *SelectCustomerListBoxItem;
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
	TMetropolisUIListBoxItem *SaveChangesIListBoxItem;
	TLinkControlToField *LinkControlToField14;
	TEdit *Edit19;
	TLabel *Label18;
	TButton *Button2;
	TLabel *Label21;
	TLabel *Label22;
	TListBox *TicketItemsListBox;
	TMetropolisUIListBoxItem *SavePrintListBoxItem;
	TButton *Button3;
	TLabel *Label24;
	TLinkPropertyToField *LinkPropertyToField1;
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
	TLinkPropertyToField *LinkPropertyToField3;
	TADOQuery *ADOQuery3;
	TBindSourceDB *BindSourceDB5;
	TLinkFillControlToField *LinkFillControlToField1;
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
	TLinkControlToField *LinkControlToField32;
	TLinkControlToField *LinkControlToField34;
	TADOQuery *ADOQuery5;
	TBindSourceDB *BindSourceDB7;
	TLinkFillControlToField *LinkFillControlToField3;
	TADOQuery *ADOQuery6;
	TADOQuery *ADOQuery7;
	TADOCommand *ADOCommand1;
	TADODataSet *ADODataSet1;
	TListBox *ListBox2;
	TADOQuery *ADOQuery8;
	TADOQuery *ADOQuery9;
	TLabel *Label17;
	TEdit *Edit30;
	TLinkControlToField *LinkControlToField28;
	TLabel *Label19;
	TPopupMenu *PopupMenu1;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem2;
	TButton *Button27;
	TMenuItem *MenuItem3;
	TMenuItem *MenuItem4;
	TMenuItem *MenuItem5;
	TButton *Button28;
	TButton *Button29;
	TLabel *Label16;
	TButton *Button30;
	TButton *Button31;
	TListBox *ListBox1;
	TLinkFillControlToField *LinkFillControlToField4;
	TButton *Button32;
	TButton *Button33;
	TADOQuery *ADOQuery10;
	TADOQuery *ADOQuery11;
	TEdit *RoomEdit;
	TLabel *RoomLabel;
	TLabel *Label8;
	TADOQuery *ADOQuery12;
	TADOQuery *ADOQuery13;
	TListBoxItem *ListBoxItem1;
	TLabel *Label20;
	TLabel *Label33;
	TLabel *Label37;
	TLabel *Label38;
	TLabel *Label41;
	TLabel *Label42;
	TLabel *Label43;
	TLabel *Label44;
	TLabel *Label45;
	TLinkPropertyToField *LinkPropertyToField2;
	TLinkPropertyToField *LinkPropertyToField4;
	TLinkPropertyToField *LinkPropertyToField5;
	TLinkPropertyToField *LinkPropertyToField6;
	TLinkPropertyToField *LinkPropertyToField7;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TButton *Button34;
	TButton *Button35;
	TButton *Button36;
	TButton *Button37;
	TButton *Button38;
	TButton *Button39;
	TButton *Button40;
	TButton *Button41;
	TButton *Button42;
	TButton *Button43;
	TButton *Button44;
	TImage *Image5;
	TLine *Line1;
	TLine *Line2;
	TImage *Image9;
	TLinkControlToField *LinkControlToField7;
	TADOQuery *ADOQuery14;
	TADOQuery *ADOQuery15;
	TADOQuery *ADOQuery16;
	TCheckBox *CheckBox9;
	TADOQuery *ADOQuery17;
	TLabel *Label46;
	TEdit *Edit31;
	TColorBox *ColorBox1;
	TColorBox *ColorBox2;
	TColorBox *ColorBox3;
	TColorBox *ColorBox4;
	TColorBox *ColorBox5;
	TColorBox *ColorBox6;
	TColorBox *ColorBox7;
	TColorBox *ColorBox8;
	TColorBox *ColorBox9;
	TColorBox *ColorBox10;
	TColorBox *ColorBox11;
	TColorBox *ColorBox12;
	TColorBox *ColorBox13;
	TColorBox *ColorBox14;
	TColorBox *ColorBox15;
	TColorBox *ColorBox16;
	TColorBox *ColorBox17;
	TColorBox *ColorBox18;
	TColorBox *ColorBox19;
	TColorBox *ColorBox20;
	TColorBox *ColorBox21;
	TColorBox *ColorBox22;
	TColorBox *ColorBox23;
	TColorBox *ColorBox24;
	TListBox *ListBox3;
	TADOQuery *ADOQuery18;
	TBindSourceDB *BindSourceDB8;
	TLinkFillControlToField *LinkFillControlToField5;
	TLabel *Label47;
	TEdit *Edit32;
	TButton *Button45;
	TLabel *Label48;
	TButton *Button46;
	TButton *Button47;
	TADOQuery *ADOQuery19;
	TButton *Button48;
	TShadowEffect *ShadowEffect1;
	TADOQuery *ADOQuery20;
	TADOQuery *ADOQuery21;
	TButton *Button49;
	TLabel *Label49;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall WriteTicketListBoxItemClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Grid1Click(TObject *Sender);
	void __fastcall SelectCustomerListBoxItemClick(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall QuickTicketListBoxItemClick(TObject *Sender);
	void __fastcall AddCustomerListBoxItemClick(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall SaveChangesIListBoxItemClick(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Label24Click(TObject *Sender);
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
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall SavePrintListBoxItemClick(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Grid1DblClick(TObject *Sender);
	char __fastcall hexToAscii(char first, char second);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall MenuItem1Click(TObject *Sender);
	void __fastcall ListBox2Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall MenuItem3Click(TObject *Sender);
	void __fastcall MenuItem4Click(TObject *Sender);
	void __fastcall MenuItem5Click(TObject *Sender);
	void __fastcall Button24Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall CheckBox3Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button33Click(TObject *Sender);
	void __fastcall Grid1KeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Edit4Change(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
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
	void __fastcall Button44Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall ColorBox1Click(TObject *Sender);
	void __fastcall ColorBox2Click(TObject *Sender);
	void __fastcall ColorBox3Click(TObject *Sender);
	void __fastcall ColorBox4Click(TObject *Sender);
	void __fastcall ColorBox5Click(TObject *Sender);
	void __fastcall ColorBox6Click(TObject *Sender);
	void __fastcall ColorBox7Click(TObject *Sender);
	void __fastcall ColorBox8Click(TObject *Sender);
	void __fastcall ColorBox9Click(TObject *Sender);
	void __fastcall ColorBox10Click(TObject *Sender);
	void __fastcall ColorBox11Click(TObject *Sender);
	void __fastcall ColorBox12Click(TObject *Sender);
	void __fastcall ColorBox13Click(TObject *Sender);
	void __fastcall ColorBox14Click(TObject *Sender);
	void __fastcall ColorBox15Click(TObject *Sender);
	void __fastcall ColorBox16Click(TObject *Sender);
	void __fastcall ColorBox17Click(TObject *Sender);
	void __fastcall ColorBox18Click(TObject *Sender);
	void __fastcall ColorBox19Click(TObject *Sender);
	void __fastcall ColorBox20Click(TObject *Sender);
	void __fastcall ColorBox21Click(TObject *Sender);
	void __fastcall ColorBox22Click(TObject *Sender);
	void __fastcall ColorBox23Click(TObject *Sender);
	void __fastcall ColorBox24Click(TObject *Sender);
	void __fastcall ListBox3Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button46Click(TObject *Sender);
	void __fastcall Button47Click(TObject *Sender);
	void __fastcall Button48Click(TObject *Sender);
	void __fastcall Button49Click(TObject *Sender);
private:	// User declarations
	TPointF FGestureOrigin;
	bool FGestureInProgress;
	void ShowToolbar(bool AShow);
	AnsiString strAlteration;
	 bool blnAlterationItem;
	TStringList *TempListQty;
	TStringList *TempListItemCode;
	TStringList *TempListItemDescription;
	TStringList *TempListItemUpcharge;
	TStringList *TempListPrice;
	TStringList *TempListClass;
	TStringList *TempListTax;
	double* aPrices;
	int* aPieces;
	int intSelectedLine;
	double* aLinePrices;
	double fTotalPrices;
    bool blnUpcharge;
	AnsiString strQty;
	AnsiString strClass;
	AnsiString strClassDescription;
	bool blnClassTaxable;
	AnsiString strUpcharge;
	double fltPrice;
	bool blnSubDCItem;

public:		// User declarations
	__fastcall TWriteTicketForm01(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TWriteTicketForm01 *WriteTicketForm01;
//---------------------------------------------------------------------------
#endif
