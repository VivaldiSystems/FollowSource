//---------------------------------------------------------------------------

#ifndef SplitPaneViewH
#define SplitPaneViewH
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
//---------------------------------------------------------------------------
class TSplitPaneForm : public TForm
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
	TImageControl *Illustration3;
	TLayout *Layout6;
	TLabel *ItemTitle3;
	TLabel *ItemSubTitle3;
	TLabel *Text3;
	TTabItem *TabItem4;
	TVertScrollBox *Article4;
	TLayout *ArticleHeaderLayout4;
	TImageControl *Illustration4;
	TLayout *Layout8;
	TLabel *ItemTitle4;
	TLabel *ItemSubTitle4;
	TLabel *Text4;
	TListBox *ListBoxItems;
	TMetropolisUIListBoxItem *AddCustomerListBoxItem;
	TMetropolisUIListBoxItem *EditCustomerListBoxItem;
	TMetropolisUIListBoxItem *RemoveCustomerListBoxItem;
	TMetropolisUIListBoxItem *AdvancedSearchListBoxItem;
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
	TLabel *Label8;
	TLinkControlToField *LinkControlToField7;
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
	TMetropolisUIListBoxItem *SaveChangesIListBoxItem;
	TLinkControlToField *LinkControlToField14;
	TLabel *Label16;
	TLinkPropertyToField *LinkPropertyToField2;
	void __fastcall HeaderButtonClick(TObject *Sender);
	void __fastcall FormGesture(TObject *Sender, const TGestureEventInfo &EventInfo,
          bool &Handled);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall RemoveCustomerListBoxItemClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ToolbarCloseButtonClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, System::WideChar &KeyChar,
          TShiftState Shift);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Grid1Click(TObject *Sender);
	void __fastcall SelectCustomerListBoxItemClick(TObject *Sender);
	void __fastcall EditCustomerListBoxItemClick(TObject *Sender);
	void __fastcall AdvancedSearchListBoxItemClick(TObject *Sender);
	void __fastcall AddCustomerListBoxItemClick(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall SaveChangesIListBoxItemClick(TObject *Sender);
private:	// User declarations
	TPointF FGestureOrigin;
	bool FGestureInProgress;
	void ShowToolbar(bool AShow);
public:		// User declarations
	__fastcall TSplitPaneForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplitPaneForm *SplitPaneForm;
//---------------------------------------------------------------------------
#endif
