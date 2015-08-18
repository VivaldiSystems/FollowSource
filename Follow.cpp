//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("LoginForm2.cpp", LoginForm02);
USEFORM("MainMenu.cpp", MainMenuForm);
USEFORM("MarkForm01.cpp", MarkForm);
USEFORM("InventoryForm1.cpp", InventoryForm);
USEFORM("IssuesForm2.cpp", IssuesForm01);
USEFORM("LoginForm.cpp", LoginForm01);
USEFORM("PickupForm.cpp", PickupWindow01);
USEFORM("StoreForm2.cpp", StoreForm01);
USEFORM("UserForm01.cpp", UserForm);
USEFORM("QuantityForm1.cpp", QuantityForm);
USEFORM("QuestionForm1.cpp", QuestionForm);
USEFORM("RouteForm2.cpp", RouteForm1);
USEFORM("HotelForm2.cpp", HotelForm);
USEFORM("ClassForm01.cpp", ClassForm);
USEFORM("ColorForm01.cpp", ColorForm);
USEFORM("CouponForm01.cpp", CouponForm);
USEFORM("AccountForm2.cpp", AccountForm01);
USEFORM("AssignLocation1.cpp", AssignLocationForm);
USEFORM("CashDrawerForm1.cpp", CashDrawerForm);
USEFORM("CustomerForm2.cpp", CustomerForm01);
USEFORM("GarmentTag.cpp", GarmentTagForm);
USEFORM("Dashboard1.cpp", DashboardForm);
USEFORM("DeliveryForm2.cpp", DeliveryForm01);
USEFORM("FM_DATEPICKER01.CPP", FM_DATEPICKER);
USEFORM("WriteTicket.cpp", WriteTicketForm01);
USEFORM("FM_PopupMessage.cpp", FM_PopupMessage01);
//---------------------------------------------------------------------------
extern "C" int FMXmain()
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TMainMenuForm), &MainMenuForm);
		Application->CreateForm(__classid(TQuestionForm), &QuestionForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
