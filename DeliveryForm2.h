//---------------------------------------------------------------------------

#ifndef DeliveryForm2H
#define DeliveryForm2H
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
class TDeliveryForm01 : public TForm
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
	TEdit *Edit10;
	TLabel *Label7;
	TDataSource *DataSource2;
	TBindSourceDB *BindSourceDB4;
	TLinkGridToDataSource *LinkGridToDataSource2;
	TBindSourceDB *BindSourceDB5;
	TLinkFillControlToField *LinkFillControlToField1;
	TBindSourceDB *BindSourceDB6;
	TLinkFillControlToField *LinkFillControlToField2;
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
	TGrid *Grid1;
	TEdit *Edit1;
	TEdit *Edit2;
	TLabel *Label2;
	TButton *Button1;
	TLinkGridToDataSource *LinkGridToDataSource6;
	TGrid *Grid2;
	TADOQuery *ADOQuery2;
	TLinkControlToField *LinkControlToField2;
	TBindSourceDB *BindSourceDB12;
	TLinkGridToDataSource *LinkGridToDataSource7;
	TButton *Button11;
	TButton *Button12;
	TButton *Button25;
	TADOQuery *ADOQuery3;
	TButton *Button26;
	TButton *Button27;
	TButton *Button28;
	TLinkControlToField *LinkControlToField1;
	TCalendarEdit *CalendarEdit2;
	TLabel *Label3;
	TADOQuery *ADOQuery4;
	TButton *Button10;
	TButton *Button13;
	TADOQuery *ADOQuery5;
	TADOQuery *ADOQuery6;
	TButton *Button29;
	TButton *Button30;
	TButton *Button31;
	TADOQuery *ADOQuery7;
	TButton *Button32;
	TMemo *Memo2;
	TButton *Button33;
	TButton *Button34;
	TCheckBox *CheckBox1;
	TADOQuery *ADOQuery8;
	TADOQuery *ADOQuery9;
	TToolBar *ToolBar3;
	TLabel *Label4;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton10;
	TButton *Button35;
	TButton *Button4;
	TButton *Button5;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Grid1Click(TObject *Sender);
	void __fastcall SelectCustomerListBoxItemClick(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall AddCustomerListBoxItemClick(TObject *Sender);
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
	void __fastcall ComboBox1Change(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem1Click(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button25Click(TObject *Sender);
	void __fastcall Button27Click(TObject *Sender);
	void __fastcall Button26Click(TObject *Sender);
	void __fastcall Button28Click(TObject *Sender);
	void __fastcall CalendarEdit2Change(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem2Click(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem3Click(TObject *Sender);
	void __fastcall Button29Click(TObject *Sender);
	void __fastcall Button30Click(TObject *Sender);
	void __fastcall Button31Click(TObject *Sender);
	void __fastcall Button32Click(TObject *Sender);
	void __fastcall Button34Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
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
	__fastcall TDeliveryForm01(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TDeliveryForm01 *DeliveryForm01;
//---------------------------------------------------------------------------
#endif
