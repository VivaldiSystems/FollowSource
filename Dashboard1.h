//---------------------------------------------------------------------------

#ifndef Dashboard1H
#define Dashboard1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.ListBox.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <Fmx.Bind.DBEngExt.hpp>
#include <Fmx.Bind.Editors.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
//---------------------------------------------------------------------------
class TDashboardForm : public TForm
{
__published:	// IDE-managed Components
	TButton *Button10;
	TADOQuery *ADOQuery2;
	TADOQuery *ADOQuery1;
	TListBox *ListBox1;
	TBindSourceDB *BindSourceDB1;
	TBindingsList *BindingsList1;
	TProgressBar *ProgressBar1;
	TCheckBox *CheckBox1;
	TLinkFillControlToField *LinkFillControlToField1;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	TLabel *Label7;
	TLabel *Label6;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TProgressBar *ProgressBarPickedUp;
	TProgressBar *ProgressBarZero;
	TProgressBar *ProgressBarTicketInprocess;
	TProgressBar *ProgressBarItemsInprocess;
	TProgressBar *ProgressBarTicketsOverdue;
	TProgressBar *ProgressBarItemsOverdue;
	TProgressBar *ProgressBarReady;
	TProgressBar *ProgressBarQuick;
	TProgressBar *ProgressBarTransactions;
	TLabel *TodayCount;
	TLabel *QuickCount;
	TLabel *ReadyCount;
	TLabel *ItemsOverDueCount;
	TLabel *OverDueCount;
	TLabel *ItemsProcessedCount;
	TLabel *ProcessedCount;
	TLabel *ZeroCount;
	TLabel *PickupCount;
	TToolBar *ToolBar1;
	TLabel *Label1;
	TSpeedButton *SpeedButton4;
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ListBox1Change(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDashboardForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDashboardForm *DashboardForm;
//---------------------------------------------------------------------------
#endif
