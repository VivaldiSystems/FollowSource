//---------------------------------------------------------------------------

#ifndef AccountForm2H
#define AccountForm2H
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
class TAccountForm01 : public TForm
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
	TADOQuery *ADOQuery1;
	TBindSourceDB *BindSourceDB3;
	TTabItem *TabItem5;
	TEdit *Edit10;
	TLabel *Label7;
	TEdit *Edit19;
	TLabel *Label18;
	TLabel *Label17;
	TButton *Button2;
	TLabel *Label21;
	TLabel *Label22;
	TListBox *TicketItemsListBox;
	TButton *Button3;
	TLabel *Label24;
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
	TBindSourceDB *BindSourceDB7;
	TLinkFillControlToField *LinkFillControlToField3;
	TBindSourceDB *BindSourceDB8;
	TLinkGridToDataSource *LinkGridToDataSource3;
	TLabel *Label19;
	TLinkGridToDataSource *LinkGridToDataSource1;
	TBindSourceDB *BindSourceDB9;
	TLinkFillControlToField *LinkFillControlToField4;
	TBindSourceDB *BindSourceDB10;
	TLinkGridToDataSource *LinkGridToDataSource4;
	TBindSourceDB *BindSourceDB11;
	TLinkGridToDataSource *LinkGridToDataSource5;
	TCheckBox *CheckBox1;
	TGrid *Grid1;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label2;
	TButton *Button1;
	TLinkGridToDataSource *LinkGridToDataSource6;
	TGrid *Grid2;
	TADOQuery *ADOQuery2;
	TLinkControlToField *LinkControlToField1;
	TLinkControlToField *LinkControlToField2;
	TLinkControlToField *LinkControlToField3;
	TBindSourceDB *BindSourceDB12;
	TLinkGridToDataSource *LinkGridToDataSource7;
	TButton *Button11;
	TButton *Button10;
	TButton *Button12;
	TButton *Button13;
	TButton *Button25;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TADOQuery *ADOQuery3;
	TButton *Button28;
	TLabel *Label3;
	TADOQuery *ADOQuery4;
	TButton *Button29;
	TADOQuery *ADOQuery5;
	TSQLQuery *SQLQuery1;
	TADOQuery *ADOQuery6;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8;
	TSpeedButton *SpeedButton9;
	TToolBar *ToolBar3;
	TLabel *Label1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *EditCustomerListBoxItem;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton10;
	TSpeedButton *SpeedButton11;
	TButton *Button30;
	TButton *Button31;
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
	TImage *Image36;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TImage *Image12;
	TImage *Image13;
	TImage *Image14;
	TImage *Image15;
	TImage *Image16;
	TImage *Image17;
	TImage *Image18;
	TImage *Image19;
	TImage *Image20;
	TImage *Image23;
	TImage *Image21;
	TImage *Image22;
	TImage *Image24;
	TImage *Image25;
	TImage *Image26;
	TImage *Image38;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall SelectCustomerListBoxItemClick(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall AddCustomerListBoxItemClick(TObject *Sender);
	void __fastcall SaveChangesIListBoxItemClick(TObject *Sender);
	void __fastcall Label24Click(TObject *Sender);
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
	void __fastcall MetropolisUIListBoxItem1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem2Click(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem3Click(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem4Click(TObject *Sender);
	void __fastcall Image27Click(TObject *Sender);
	void __fastcall Image28Click(TObject *Sender);
	void __fastcall Image29Click(TObject *Sender);
	void __fastcall Image30Click(TObject *Sender);
	void __fastcall Image31Click(TObject *Sender);
	void __fastcall Image32Click(TObject *Sender);
	void __fastcall Image37Click(TObject *Sender);
	void __fastcall Image33Click(TObject *Sender);
	void __fastcall Image34Click(TObject *Sender);
	void __fastcall Image35Click(TObject *Sender);
	void __fastcall Image36Click(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall Image2Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Image5Click(TObject *Sender);
	void __fastcall Image6Click(TObject *Sender);
	void __fastcall Image7Click(TObject *Sender);
	void __fastcall Image8Click(TObject *Sender);
	void __fastcall Image9Click(TObject *Sender);
	void __fastcall Image10Click(TObject *Sender);
	void __fastcall Image11Click(TObject *Sender);
	void __fastcall Image12Click(TObject *Sender);
	void __fastcall Image13Click(TObject *Sender);
	void __fastcall Image14Click(TObject *Sender);
	void __fastcall Image15Click(TObject *Sender);
	void __fastcall Image16Click(TObject *Sender);
	void __fastcall Image17Click(TObject *Sender);
	void __fastcall Image18Click(TObject *Sender);
	void __fastcall Image19Click(TObject *Sender);
	void __fastcall Image20Click(TObject *Sender);
	void __fastcall Image23Click(TObject *Sender);
	void __fastcall Image21Click(TObject *Sender);
	void __fastcall Image22Click(TObject *Sender);
	void __fastcall Image24Click(TObject *Sender);
	void __fastcall Image25Click(TObject *Sender);
	void __fastcall Image26Click(TObject *Sender);
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
	AnsiString strSelectedClass;
	float fTotalPrices;
    bool blnUpcharge;
	AnsiString strQty;
	AnsiString strClass;
	AnsiString strUpcharge;
	float fltPrice;
	bool blnSubDCItem;

public:		// User declarations
	__fastcall TAccountForm01(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TAccountForm01 *AccountForm01;
//---------------------------------------------------------------------------
#endif
