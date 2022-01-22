#include "StdAfx.h"
#include "Configs.h"
#include "Message.h"
#include "3DCamera.h"
#include "Control.h"
#include "Player.h"
#include "ConnectEx.h"
#include "Console.h"
#include "NewHpBar.h"
#include "Interface.h"
#include "JewelsBank.h"
#include "Graphics.h"

WPARAM mParam;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{	
	if (((lParam >> 31) & 1) && (nCode == HC_ACTION)) 
	{
		//====================
		if (wParam == VK_END)			//3D Camera on/off
		{
			if (Function3DVK_IsPressed() == false && Config.CAM_IsActive == true)	
			{
				Function3DOff();
			}
			else	
			{
				Function3DOn();
			}
		}
		//====================
		if (wParam == VK_HOME)			//Default 3D
		{
			_beginthread(CAMDefault, 0, NULL); 
		}
		//====================
		if(wParam == VK_DELETE)			//Time On/Off
		{
			if(Config.Time == true) 
				Config.Time = false;
			else 
				Config.Time = true;
			//Config.Time++;
			//	if(Config.Time==2)
			//		Config.Time = 0;
			//char InfoDate[512];
			//sprintf(InfoDate, "%d %d %d",(int)0, VK_MINIMAP,Config.Time);
			//Console.ConsoleOutput(GREEN,InfoDate);
		}
		//====================
		if(wParam == VK_PRIOR)		//Hp Bar On/Off
		{
			if(Config.HPBar == true) 
				Config.HPBar = false;
			else 
				Config.HPBar = true;
		}
		if(wParam == VK_NEXT)
		{
			HWND MuWnd = FindWindow("MU", NULL);
			if(GetForegroundWindow() == MuWnd)
			{
				//Emulator Battle Mode
				if(Config.Ctrl == true) 
				{
					Config.Ctrl = false;
					keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // вот тут какой-то флаг
				}
				else 
					Config.Ctrl = true;
			}
		}
#if(_CONFIG_SAVE_)
		if(wParam == VK_TAB && pPlayerState == GameProcess )
		{
			//VK_MINIMAP++;
			//	if(VK_MINIMAP==2)
			//		VK_MINIMAP = 0;
			//if(VK_MINIMAP == false)
			//{
			//	VK_MINIMAP = true;
			//}
			//else
			//{
			//	VK_MINIMAP == false;
			//}

		}
#endif
#if(NEW_HP_BAR)
		if(wParam == VK_F9)
			{
				if(Config.iMonsterHPBar == 0)
				{
					Config.iMonsterHPBar++;
				}
				else if(Config.iMonsterHPBar == 1)
				{
					Config.iMonsterHPBar++;
				}
				else
				{
					Config.iMonsterHPBar = 0;
				}
#ifdef exDEBUG_CODE
				gConsole.Output(2,"%d",gViewePortInfo.iMonsterHPBar);
#endif
			}

		if(wParam == VK_F10)
			{

				if(Config.iUserHpBar == 0)
				{
					Config.iUserHpBar = 1;
				}
				else
				{
					Config.iUserHpBar = 0;
				}
#ifdef exDEBUG_CODE
				gConsole.Output(2,"%d",gViewePortInfo.iUserHpBar);
#endif
			}
			
		if(wParam == VK_F11)
			{
				if(Config.iPartyHpBar == 0)
				{
					Config.iPartyHpBar = 1;
				}
				else
				{
					Config.iPartyHpBar = 0;
				}
#ifdef exDEBUG_CODE
				gConsole.Output(2,"%d",gViewePortInfo.iPartyHpBar);
#endif
			}
#endif
#if(_JEWELS_BANK_)
		if(wParam == 0x59)	//Y
		{
			if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				if(gJewelsBank.Active)
				{
					gJewelsBank.Active = false;
				}
				else
				{
					gJewelsBank.Active = true;
				}
			}
		}
#endif
		if(wParam == 0x4F)	//O
		{
			if(!gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				if(g_bGlowGraphic)
					g_bGlowGraphic = false;
				else
					g_bGlowGraphic = true;
			}
		}

	}	
	return CallNextHookEx(KeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int code, WPARAM wParam, LPARAM lParam)
{
#ifdef CONSOLE
	//Console.ConsoleOutput(2,"MOUSE");
#endif
	MOUSEHOOKSTRUCTEX* mhs = (MOUSEHOOKSTRUCTEX*)lParam;
	HWND MuWnd = FindWindow("MU", NULL);

	mParam = wParam;

	if(!Config.exCAM_IsActive)
	{
		return CallNextHookEx(MouseHook, code, wParam, lParam);
	}

	Function3DNotAvaibleFalse();

	Function3DStart();

	if (Config.CAM_IsActive) 
	{
		if (GetForegroundWindow() == MuWnd) 
		{
			if (Function3DInitCameraReturn()) 
			{		
				Function3DInitCamera();
			}
			else if (wParam == WM_MOUSEWHEEL && Function3DNotAvaible() == FALSE) 
			{ 
				Function3DZoom((int)mhs->mouseData);
			}
			else if (wParam == WM_MBUTTONDOWN)
			{
				Function3DRoom1((int)mhs->pt.x,(int)mhs->pt.y);
			}
			else if (wParam == WM_MBUTTONUP)
			{
				Function3DRoom2();
			}
			else if (wParam == WM_MOUSEMOVE)
			{
				if (Function3DReturn()) 
				{
					Function3DMove((int)mhs->pt.x,(int)mhs->pt.y);
				}
			}
		}
	}
	else
	{
		Function3DInitCamera();
	}

	return CallNextHookEx(MouseHook, code, wParam, lParam);
}