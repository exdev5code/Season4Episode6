//#include "StdAfx.h"
//#include "Interface.h"
//#include "Time.h"
//void MyShowTime()
//{
//	SYSTEMTIME time;
//	GetLocalTime(&time);
//	char buffer[100];
//	time.wHour;
//	sprintf(buffer,"%02d:%02d:%02d",time.wHour,time.wMinute,time.wSecond);
//	LPCTSTR var = (LPCTSTR)buffer;
//	MU_DrawGUI(0x00007B8F, 70, 0, 57, 17);	//Рамка
//	MU_DrawColorButton(NEWUI_BAR_SWITCH02, 72, 2,52, 12, 0, 0, MU_CreateColor(100, 100,100, 255)); //Фон и цвет
//	MU_SetTextColorEx(255, 255, 255, 255);	//Text Color
//	MU_OutText(82,3,var);
//}