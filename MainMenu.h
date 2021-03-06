//---------------------------------------------------------------------------

#ifndef MainMenuH
#define MainMenuH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <MetropolisUI.Tile.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.ListBox.hpp>
#include <Data.DB.hpp>
#include <Data.Win.ADODB.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Procs.hpp>
#include <FMX.Grid.hpp>
//---------------------------------------------------------------------------
class TMainMenuForm : public TForm
{
__published:	// IDE-managed Components
	TToolBar *ToolBar1;
	TMainMenu *MainMenu1;
	TMenuItem *MenuItem1;
	TMenuItem *MenuItem6;
	TMenuItem *MenuItem8;
	TMenuItem *MenuItem24;
	TMenuItem *MenuItem7;
	TMenuItem *MenuItem2;
	TMenuItem *MenuItem9;
	TMenuItem *MenuItem10;
	TMenuItem *MenuItem11;
	TMenuItem *MenuItem12;
	TMenuItem *MenuItem13;
	TMenuItem *MenuItem14;
	TMenuItem *MenuItem25;
	TMenuItem *MenuItem39;
	TMenuItem *MenuItem105;
	TMenuItem *MenuItem141;
	TMenuItem *MenuItem3;
	TMenuItem *MenuItem18;
	TMenuItem *MenuItem19;
	TMenuItem *MenuItem27;
	TMenuItem *MenuItem28;
	TMenuItem *MenuItem108;
	TMenuItem *MenuItem109;
	TMenuItem *MenuItem110;
	TMenuItem *MenuItem111;
	TMenuItem *MenuItem112;
	TMenuItem *MenuItem29;
	TMenuItem *MenuItem125;
	TMenuItem *MenuItem126;
	TMenuItem *MenuItem133;
	TMenuItem *MenuItem124;
	TMenuItem *MenuItem132;
	TMenuItem *MenuItem106;
	TMenuItem *MenuItem107;
	TMenuItem *MenuItem120;
	TMenuItem *MenuItem134;
	TMenuItem *MenuItem147;
	TMenuItem *MenuItem148;
	TMenuItem *MenuItem79;
	TMenuItem *MenuItem149;
	TMenuItem *MenuItem150;
	TMenuItem *MenuItem151;
	TMenuItem *MenuItem4;
	TMenuItem *MenuItem15;
	TMenuItem *MenuItem16;
	TMenuItem *MenuItem17;
	TMenuItem *MenuItem34;
	TMenuItem *MenuItem65;
	TMenuItem *MenuItem66;
	TMenuItem *MenuItem155;
	TMenuItem *MenuItem30;
	TMenuItem *MenuItem31;
	TMenuItem *MenuItem135;
	TMenuItem *MenuItem33;
	TMenuItem *MenuItem35;
	TMenuItem *MenuItem48;
	TMenuItem *MenuItem47;
	TMenuItem *MenuItem50;
	TMenuItem *MenuItem51;
	TMenuItem *MenuItem53;
	TMenuItem *MenuItem123;
	TMenuItem *MenuItem129;
	TMenuItem *MenuItem94;
	TMenuItem *MenuItem52;
	TMenuItem *MenuItem36;
	TMenuItem *MenuItem37;
	TMenuItem *MenuItem38;
	TMenuItem *MenuItem64;
	TMenuItem *MenuItem49;
	TMenuItem *MenuItem62;
	TMenuItem *MenuItem63;
	TMenuItem *MenuItem67;
	TMenuItem *MenuItem71;
	TMenuItem *MenuItem54;
	TMenuItem *MenuItem68;
	TMenuItem *MenuItem70;
	TMenuItem *MenuItem101;
	TMenuItem *MenuItem102;
	TMenuItem *MenuItem103;
	TMenuItem *MenuItem104;
	TMenuItem *MenuItem55;
	TMenuItem *MenuItem72;
	TMenuItem *MenuItem153;
	TMenuItem *MenuItem73;
	TMenuItem *MenuItem74;
	TMenuItem *MenuItem75;
	TMenuItem *MenuItem76;
	TMenuItem *MenuItem142;
	TMenuItem *MenuItem143;
	TMenuItem *MenuItem154;
	TMenuItem *MenuItem56;
	TMenuItem *MenuItem77;
	TMenuItem *MenuItem78;
	TMenuItem *MenuItem80;
	TMenuItem *MenuItem57;
	TMenuItem *MenuItem81;
	TMenuItem *MenuItem82;
	TMenuItem *MenuItem83;
	TMenuItem *MenuItem58;
	TMenuItem *MenuItem69;
	TMenuItem *MenuItem86;
	TMenuItem *MenuItem87;
	TMenuItem *MenuItem127;
	TMenuItem *MenuItem88;
	TMenuItem *MenuItem89;
	TMenuItem *MenuItem90;
	TMenuItem *MenuItem59;
	TMenuItem *MenuItem92;
	TMenuItem *MenuItem93;
	TMenuItem *MenuItem91;
	TMenuItem *MenuItem60;
	TMenuItem *MenuItem96;
	TMenuItem *MenuItem97;
	TMenuItem *MenuItem98;
	TMenuItem *MenuItem99;
	TMenuItem *MenuItem100;
	TMenuItem *MenuItem5;
	TMenuItem *MenuItem84;
	TMenuItem *MenuItem20;
	TMenuItem *MenuItem21;
	TMenuItem *MenuItem46;
	TMenuItem *MenuItem128;
	TMenuItem *MenuItem26;
	TMenuItem *MenuItem32;
	TMenuItem *MenuItem22;
	TMenuItem *MenuItem122;
	TMenuItem *MenuItem95;
	TMenuItem *MenuItem23;
	TMenuItem *MenuItem156;
	TMenuItem *MenuItem114;
	TMenuItem *MenuItem115;
	TMenuItem *MenuItem61;
	TMenuItem *MenuItem116;
	TMenuItem *MenuItem117;
	TMenuItem *MenuItem118;
	TMenuItem *MenuItem119;
	TMenuItem *MenuItem121;
	TMenuItem *MenuItem130;
	TMenuItem *MenuItem131;
	TMenuItem *MenuItem136;
	TMenuItem *MenuItem137;
	TMenuItem *MenuItem144;
	TMenuItem *MenuItem145;
	TMenuItem *MenuItem146;
	TMenuItem *MenuItem113;
	TMenuItem *MenuItem45;
	TMenuItem *MenuItem85;
	TMenuItem *MenuItem152;
	TMenuItem *MenuItem140;
	TImage *Image1;
	TImage *Image5;
	TImage *Image6;
	TImage *Image4;
	TImage *Image3;
	TImage *Image7;
	TLabel *Label23;
	TCalendarEdit *CalendarEdit1;
	TImage *Image2;
	TLabel *Label1;
	TLabel *Label2;
	TMetropolisUIListBoxItem *MetroListBoxItem1;
	TMetropolisUIListBoxItem *MetroListBoxItem6;
	TMetropolisUIListBoxItem *MetroListBoxItem2;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem1;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem2;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem3;
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TADOConnection *ADOConnection1;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel15;
	TPanel *Panel17;
	TPanel *Panel18;
	TPanel *Panel19;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem4;
	TMetropolisUIListBoxItem *MetroListBoxItem7;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem5;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem6;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem7;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem8;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem9;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem10;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem11;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem12;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem13;
	TMetropolisUIListBoxItem *MetropolisUIListBoxItem14;
	TLabel *TitleLabel1;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TButton *Button1;
	TProgressBar *ProgressBarPickedUp;
	TLabel *PickupCount;
	TLabel *Label7;
	TButton *Button2;
	TProgressBar *ProgressBarZero;
	TLabel *ZeroCount;
	TLabel *ProcessedCount;
	TProgressBar *ProgressBarTicketInprocess;
	TButton *Button3;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label15;
	TLabel *Label16;
	TLabel *Label17;
	TButton *Button9;
	TButton *Button8;
	TButton *Button7;
	TButton *Button6;
	TButton *Button5;
	TButton *Button4;
	TProgressBar *ProgressBarItemsInprocess;
	TProgressBar *ProgressBarTicketsOverdue;
	TProgressBar *ProgressBarItemsOverdue;
	TProgressBar *ProgressBarReady;
	TProgressBar *ProgressBarQuick;
	TProgressBar *ProgressBarTransactions;
	TLabel *ItemsProcessedCount;
	TLabel *OverDueCount;
	TLabel *ItemsOverDueCount;
	TLabel *ReadyCount;
	TLabel *QuickCount;
	TLabel *TodayCount;
	TSpeedButton *SpeedButton4;
	TADOQuery *ADOQuery2;
	TCornerButton *CornerButton6;
	TPopupMenu *PopupMenu1;
	TMenuItem *MenuItem40;
	TMenuItem *MenuItem41;
	TMenuItem *MenuItem42;
	TMenuItem *MenuItem43;
	TMenuItem *MenuItem44;
	TStyleBook *StyleBook2;
	TRectangle *Rectangle1;
	TRectangle *Rectangle2;
	void __fastcall UpdateMenu();
	void __fastcall Panel1Click(TObject *Sender);
	void __fastcall MenuItem20Click(TObject *Sender);
	void __fastcall Image5Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Image1Click(TObject *Sender);
	void __fastcall MenuItem26Click(TObject *Sender);
	void __fastcall Image7Click(TObject *Sender);
	void __fastcall Image3Click(TObject *Sender);
	void __fastcall Image4Click(TObject *Sender);
	void __fastcall Image6Click(TObject *Sender);
	void __fastcall CalendarEdit1Change(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall MenuItem128Click(TObject *Sender);
	void __fastcall Panel13Click(TObject *Sender);
	void __fastcall MenuItem32Click(TObject *Sender);
	void __fastcall Panel4Click(TObject *Sender);
	void __fastcall CornerButton6Click(TObject *Sender);
	void __fastcall Panel5Click(TObject *Sender);
	void __fastcall Panel11Click(TObject *Sender);
	AnsiString __fastcall ConvertDate(AnsiString argDateString);
	void __fastcall Panel8Click(TObject *Sender);
	void __fastcall MenuItem8Click(TObject *Sender);
	void __fastcall MenuItem6Click(TObject *Sender);
	void __fastcall MenuItem7Click(TObject *Sender);
	void __fastcall MenuItem18Click(TObject *Sender);
	void __fastcall Panel6Click(TObject *Sender);
	void __fastcall MenuItem122Click(TObject *Sender);
	void __fastcall CornerButton4Click(TObject *Sender);
	void __fastcall Panel12Click(TObject *Sender);
	void __fastcall MenuItem46Click(TObject *Sender);
	void __fastcall Panel15Click(TObject *Sender);
	void __fastcall Panel19Click(TObject *Sender);
	void __fastcall MenuItem13Click(TObject *Sender);
	void __fastcall MenuItem14Click(TObject *Sender);
	void __fastcall MenuItem25Click(TObject *Sender);
	void __fastcall MenuItem125Click(TObject *Sender);
	void __fastcall MenuItem108Click(TObject *Sender);
	void __fastcall MenuItem39Click(TObject *Sender);
	void __fastcall MenuItem105Click(TObject *Sender);
	void __fastcall MenuItem106Click(TObject *Sender);
	void __fastcall Panel17Click(TObject *Sender);
	void __fastcall MenuItem141Click(TObject *Sender);
	void __fastcall Panel3Click(TObject *Sender);
	void __fastcall MenuItem19Click(TObject *Sender);
	void __fastcall Panel2Click(TObject *Sender);
	void __fastcall CornerButton2Click(TObject *Sender);
	void __fastcall MenuItem10Click(TObject *Sender);
	void __fastcall Panel9Click(TObject *Sender);
	void __fastcall MetropolisUIListBoxItem6Click(TObject *Sender);
	void __fastcall Panel10Click(TObject *Sender);
	void __fastcall Panel18Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainMenuForm(TComponent* Owner);
		AnsiString strStoreNo;
	AnsiString strReportName;
	AnsiString strReportFileName;
	AnsiString strStoreName;
	AnsiString strStoreAddress;
	AnsiString strStoreCity;
	AnsiString strStoreState;
	AnsiString strStoreZip;
	AnsiString strStorePhone;
	AnsiString strUserName;
	AnsiString strUserID;
	AnsiString strUserEmail;
	AnsiString strCityState;
	AnsiString strPaidType;
	AnsiString strReportFilter;
	AnsiString strStockNumber;
	AnsiString strVersionNumber;
	AnsiString strPickupAccount;
	AnsiString strPickupZip;
	AnsiString strPickupAddress;
	AnsiString strDescription;
	AnsiString strDataSet;
	AnsiString strCustomerAcct;
	AnsiString strDefaultEditTicketNumber;
	AnsiString strTicketNumber;
	AnsiString strQuestion;
    AnsiString strEnterQuantity;
	AnsiString strSenderEmail;
	AnsiString strSenderPassword;
	AnsiString strSendercc;
	AnsiString strSMTPServer;
	AnsiString strEmailSecurity;
	bool blnSendTicketEmail;
	bool blnIsQuickTicket;
	bool blnSendReadyEmail;
	AnsiString strEmailPort;
	bool blnItemTagEntered;
	bool blnUseItemTags;
	double dblRushFee;
	bool blnOK;
	bool blnRecalcTaxAfterCoupon;
	AnsiString strQuantityType;
	bool blnUseTags;
	AnsiString strNoTagsFor;
	AnsiString strSlave;
	double dDescriptionPrice;
	bool blnTicketClosed;
	bool blnUseMinFee;
	double fTendered;
	double iCouponPercent;
	double dCouponAmount;
	double fTaxRate;
	double fDeposit;
	bool blnPrePayAllToday;
	AnsiString strPrePayAccount;
	bool blnRepeat;
	bool blnWiderTags;
	bool blnPreview;
	bool blnAccountCustomer;
	AnsiString strDateOut;
	bool blnEnableTopMenu;
	double fPrepayment;
	bool blnDirectPrint;
	double fCouponTotal;
	double blnDirectPayment;
	double fTicketTax;
	bool blnDateOut;
	bool blnDateIn;
	AnsiString strDefaultStatus;
	AnsiString strCCard;
	AnsiString strExpDate;
    bool blnDefaultNewTaxable;
	bool blnAllowEditAccess;
		bool blnAllowCustomerAccess;
			bool blnAllowWriteAccess;
				bool blnAllowPickupAccess;
					bool blnAllowXChargeAccess;
						bool blnAllowTimeCardAccess;
							bool blnAllowInventoryAccess;
								bool blnAllowAccountAccess;
									bool blnAllowCashDrawerAccess;
										bool blnAllowPriceListAccess;
											bool blnAllowAssignLocationAccess;
												bool blnAllowMarkReadyAccess;


													bool blnAllowDeliveryAccess;
														bool blnAllowStoreAccess;
															bool blnAllowHotelAccess;
																bool blnAllowRouteAccess;




	bool blnTransactionLogin;
	bool blnWinExec;
	double fTicketSubTotal;
	double fLoyaltyDollars;
	bool blnAutoPopUpcharges;
	AnsiString strTicketPieceCount;
	AnsiString strTicketCopies;
	AnsiString strLastTicketNo;
	bool blnAutoPopupColor;
	AnsiString strTag1;
	AnsiString strTag2;
	AnsiString strTag3;
	bool blnDeposit;
	AnsiString strTag4;
	AnsiString strPC;
	AnsiString strTag5;
	AnsiString strTag6;
	AnsiString strTag7;
	bool blnSeperateShirtLot;
	bool blnUseEuropeanFormat;
	bool blnUseInventoryControl;
	bool blnLocalDatabase;
	bool blnCancel;
	bool blnAutoStarch;
	bool blnDefaultLoyalty;
	bool blnUsePriceLevel;
	bool blnPayInFull;
	bool blnReturnTendered;
	bool blnBackButton;
	bool bln64Bit;
	bool blnUseCashDrawer;
	bool blnShowColorList;
	bool blnEnableEnterprise;
	bool blnDeliveryByDate;
	AnsiString strTicketPrinter;
	AnsiString strTagPrinter;
	bool blnEpsonU220Tag;
	bool blnDontPrintTags;
	bool blnNoTags;
	bool blnLargerDTags;
	bool blnTaxAllClasses;
	bool blnUseDeliveryVacation;
    double dTotalTicketValue;
	AnsiString strEnterprise;
	AnsiString strCustomerDiscount;
	AnsiString strLastSearch;
	bool blnLevelLoyalty;
	bool blnAutoSelectLastCustomer;
	bool blnUseCreditCardProcessing;
	AnsiString strCustomTicket;
	AnsiString strStarch;
	AnsiString strAdditionalFilter;
	AnsiString strCreditCardPath;
	AnsiString strSelectedClass;
	AnsiString strAccessLevel;
	AnsiString strPickupDate;
	AnsiString strStarchPreference;
	int intDaysToPickup;
	bool blnDisableDates;
	double dGiftCard;
	bool blnPrintTwice;
	AnsiString strPrintPause;
	bool blnPrint;
	AnsiString strCCReceiptPathPrinter;
	bool blnEmailOnly;
	AnsiString strSurchargeLabel;
	int iBackgroundColor;
	bool blnCustomerTaxable;
	bool blnShowReadyOnly;
	bool blnUseLotSystem;
	int intRackTicketNumber;
	int intCurrentLot;
	int intMaxItems;
	AnsiString strTicketComment;
	AnsiString strEnvironmentalClasses;
	double dblEnvironmental;
	double dblActualEnvironmentalFee;
	double dblTotalEnvironmental;
	bool blnSmallerItems;
	bool blnTagName;
	bool blnUseRackTicket;
	bool blnAdditionalTagInfo;
	AnsiString strDataBaseType;
	AnsiString strCustomerARStatement;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainMenuForm *MainMenuForm;
//---------------------------------------------------------------------------
#endif
