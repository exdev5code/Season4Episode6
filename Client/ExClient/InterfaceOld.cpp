//#include "stdafx.h"
//#include "Interface.h"
//#include "MonsterHPBar.h"
//#include "Protocol.h"
//#include "Configs.h"
//#include "Time.h"
//#include "BattleMode.h"
//#include "ToolKit.h"
//
//	//0x00007A58 - �������� �������
//	//0x00007A57 - �����
//	//0x00007A56 - �������������
//	//0x00007A55 - �������
//	//0x00007A54 - ���� �������������
//	//0x00007A53 - Clouse
//	//0x00007A52 - Cancel
//	//0x00007A51 - ok
//	//0x00007A50 - �����
//	//0x00007A4B - ����� ��� �����
//	//0x00007A26- ������� ����������
//	//0x00007A25 - ������� ���������
//	//0x00007A08 - ����� ������������ ��� ������� ������ ������
//	//0x000079E0 - ������� ����� ����� �����������
//	//0x00007AED - ������ �� ������ � �����
//	//7AEE		 - ������� �� �� ������
//	//0x00007B8F - ����� �������� ��� ����
//
//pMU_DrawGUI MU_DrawGUI = (pMU_DrawGUI)MU_DRAWGUI;
//pMU_CreateColor MU_CreateColor = (pMU_CreateColor)MU_CREATE_COLOR;
//pMU_DrawButton MU_DrawButton = (pMU_DrawButton)MU_DRAW_BUTTON;
//pMU_DrawColoredButton MU_DrawColorButton = (pMU_DrawColoredButton)MU_DRAW_COLORED_BUTTON;
//pCDC_This CDC_This = (pCDC_This)MU_CDC_GET_THIS_POINTER;
//
//pCDCSetTextColor MU_SetTextColor = (pCDCSetTextColor)MU_CDC_SETTEXTCOLOR;
//pCDCTabbedTextOut MU_TabbedTextOut = (pCDCTabbedTextOut)MU_CDC_TABBEDTEXTOUT;
//
//#ifdef DEBUG_INTERFACE
//#define MU_SetTextColorTEST		((DWORD(__thiscall*)(LPVOID, BYTE , BYTE , BYTE , BYTE )) 0x0041EDCA)
//#endif
//
////
//
//void MU_SetColor(BYTE r, BYTE g, BYTE b, BYTE h)
//{
//	MU_SetTextColor(CDC_This(), r, g, b, h);
//#ifdef DEBUG_INTERFACE
//	MU_SetTextColorTEST(CDC_This(), r, g, b, h);
//#endif
//}
//
//void MU_OutText(int x, int y, LPCTSTR lpszString)
//{
//	MU_TabbedTextOut(CDC_This(), x, y, lpszString, 1, 1, (LPINT)0, 0);
//}
//
//void MU_SetTextColorEx(BYTE red, BYTE blue, BYTE green, BYTE Header)
//{
//	MU_SetTextColor(CDC_This(), red, blue, green, Header);
//}
//
//void __cdecl cDrawInterface()
//{
//	if (Mob_HP_Bar.isDraw && Config.HPBar)
//	{
//		Mob_HP_Bar.Draw();
//		Mob_HP_Bar.ShowHp();
//	}
//	if(Config.Time) 
//	{
//		MyShowTime();
//	}
//	if(Config.Ctrl)
//	{	
//		ShowBattleMode();
//	}
//	DrawInterface();	//������ ����������
//}
//
//void InitInterface()
//{
//	HookThis((DWORD)&cDrawInterface,0x00739C02);
//}