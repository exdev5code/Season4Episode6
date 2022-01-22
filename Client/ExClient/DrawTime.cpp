#include "stdafx.h"
#include "Interface.h"
#include "Configs.h"

void TimeImageLoad()
{
	gInterface.LoadImages("ExTeam\\Interface\\TimeBar.tga", 0x787E, 0x2601, 0x2900, 1);
}

void TimeLoad()
{
	gInterface.BindObject(eTIME, 0x787E, 131, 70, -10, 359);
	gInterface.Data[eTIME].OnShow = true;
}

void DrawTime()
{

	if(!Config.exTime)return;

	if(!Config.Time)return;


	if( !gInterface.Data[eTIME].OnShow )
	{
		return;
	}
	// ----
	if( gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList) /*|| gObjUser.m_MapNumber == 34 || gObjUser.m_MapNumber == 30*/ )
	{
		return;
	}
	// ----
	gInterface.DrawGUI(eTIME, gInterface.Data[eTIME].X, gInterface.Data[eTIME].Y+22);
	// -----
	time_t TimeServer, TimeLocal;
	struct tm * ServerT, * LocalT;
	time(&TimeServer);
	time(&TimeLocal);
	// ----
	ServerT = localtime(&TimeServer);	//gmtime
	// ----
	char ServerTimeName[25] = "Time:";
	char ServerTime[30];
	sprintf(ServerTime, "%2d:%02d:%02d", (ServerT->tm_hour)%24, ServerT->tm_min, ServerT->tm_sec);
	// -----
	//LocalT = localtime(&TimeLocal);
	// -----
	//char LocalTimeName[25] = "Local:";
	//char LocalTime[30];
	//sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	// -----
	gInterface.DrawFormat(eGold, 5, 391+22, 50, 1, ServerTimeName);
	gInterface.DrawFormat(eWhite, 55, 391+22, 100, 1, ServerTime);
	/// ----
	//gInterface.DrawFormat(eGold, 5, 413, 50, 1, LocalTimeName);
	//gInterface.DrawFormat(eWhite, 55, 413, 100, 1, LocalTime);

	//*************************

	//// ----
	//gInterface.DrawGUI(eTIME, gInterface.Data[eTIME].X, gInterface.Data[eTIME].Y);
	//// -----
	//time_t TimeServer, TimeLocal;
	//struct tm * ServerT, * LocalT;
	//time(&TimeServer);
	//time(&TimeLocal);
	//// ----
	//ServerT = gmtime(&TimeServer);
	//// ----
	//char ServerTimeName[25] = "Server:";
	//char ServerTime[30];
	//sprintf(ServerTime, "%2d:%02d:%02d", (ServerT->tm_hour+2)%24, ServerT->tm_min, ServerT->tm_sec);
	//// -----
	//LocalT = localtime(&TimeLocal);
	//// -----
	//char LocalTimeName[25] = "Local:";
	//char LocalTime[30];
	//sprintf(LocalTime, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
	//// -----
	//gInterface.DrawFormat(eGold, 5, 391, 50, 1, ServerTimeName);
	//gInterface.DrawFormat(eWhite, 55, 391, 100, 1, ServerTime);
	//// ----
	//gInterface.DrawFormat(eGold, 5, 413, 50, 1, LocalTimeName);
	//gInterface.DrawFormat(eWhite, 55, 413, 100, 1, LocalTime);
}