#include "StdAfx.h"
#include "3DCamera.h"
#include "ChatWnd.h"
#include "Connect.h"
#include "ToolKit.h"
#include "MiniMap.h"
#include "Security.h"
#include "Interface.h"
#include "Protocol.h"
#include "Header.h"
#include "Fix.h"
#include "Configs.h"
#include "Control.h"
#include "Items.h"
#include "Wings.h"
#include "MakePreviewCharSet.h"
#ifdef CONSOLE
#include "Console.h"
#endif
#include "Player.h"
#ifdef _GRAND_SYSTEM_
#include "Maps.h"
#include "Monster.h"
#include "Glow.h"
#include "Bow.h"
#include "SocketItem.h"
#endif
#if ANTI_HACK
#include "AntiHack.h"
#endif
#include "Pets.h"
#include "RageSystem.h"
#include "LoadItem.h"
#include "ConnectEx.h"
#include "LoadGlow.h"
#include "Effect.h"
#include "TMemory.h"
#include "NewHpBar.h"
#include "Graphics.h"
#include "AntiCheatPlus.h"

BOOL KeyboardSetHook(BOOL set_or_remove)
{
	if(set_or_remove == TRUE) 
	{
		if(KeyboardHook == NULL) 
		{
			KeyboardHook = SetWindowsHookExA(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hInstance, GetCurrentThreadId());
			
			if(!KeyboardHook) 
			{ 
				//MessageBox(0,"ERROR","KeyboardHook",0); 
				return FALSE; 
			}
		}
	} 
	else
	{
		//MessageBox(0,"ERROR","KeyboardHook 2",0); 
		KeyboardHook = NULL;
		return UnhookWindowsHookEx(KeyboardHook);
	}
	return TRUE;
}

BOOL MouseSetHook(BOOL set_or_remove) 
{
	if(set_or_remove == TRUE) 
	{
		if(MouseHook == NULL) 
		{
			MouseHook = SetWindowsHookExA(WH_MOUSE, MouseProc, hInstance, GetCurrentThreadId());
			if(!MouseHook) 
			{ 
				//MessageBox(0,"ERROR","Mause",0);
				return FALSE;
			}
		}
	} 
	else
	{ 
		//MessageBox(0,"ERROR","Mause 2",0);
		MouseHook = NULL;
		return UnhookWindowsHookEx(MouseHook); 
	}
	return TRUE;
}


BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			{
				hInstance = hModule;
#if ANTI_HACK
				SystemProcessesScan();
				CheckFilesDir(0);
#endif
#ifdef CONSOLE
				Console.InitCore();
#endif
#if __MuRain__||__ExGames__
#ifndef NO_DLL_CLICKER
				LoadLibraryA("Clicker.dll");
#endif
#endif
				//LoadLibraryA("Glow.dll");
#ifdef _zigzagmu_ru_
				LoadLibraryA("Clicker.dll");
#endif
#ifdef _MegaMu_
				LoadLibraryA("Clicker.dll");
#endif
#if(_CONFIG_SAVE_)
				LoadGame();
#endif

#ifdef _h3yShOk_
				LoadLibraryA("GameGuard.dll");
#endif
#if(CLICKER_DLL)
				LoadLibraryA("Clicker.dll");
#endif
			}
		break;
		case DLL_THREAD_ATTACH:break;
		case DLL_THREAD_DETACH:break;
		case DLL_PROCESS_DETACH:
			{
				//keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // TEST
				KeyboardSetHook(false); MouseSetHook(false);
#if(_CONFIG_SAVE_)
				SaveGame();
#endif
			}
			break;
	}
	return TRUE;
}

DWORD WINAPI Timer(LPVOID lpParam)
{
	Sleep(5000);
	while(true)
	{
		//if(Config.Ctrl == true)
		//{
		//	HWND MuWnd = FindWindow("MU", NULL);
		//	if(GetForegroundWindow() == MuWnd)
		//		keybd_event(VK_CONTROL, 0, 0, 0); // вот тут какой-то флаг
		//	else
		//		keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0); // TEST
		//}
		Sleep(1000);
	}
	return 1;
} 

DWORD WINAPI UpdateTimer(LPVOID lpParam)
{
	Sleep(5000);
	while(true)
	{
#if ANTI_HACK
		SystemProcessesScan();
		CheckFilesDir(1);
#endif
		Sleep(5000);	//5 sek perekur
	}
	return 1;
}

//============================================================================================
//#define EX_AH	FALSE
extern "C" __declspec(dllexport) void DllExp() 
{
	DWORD dwOldProtect;
	if (VirtualProtect(LPVOID(0x00401000), 0x00875FFF, PAGE_EXECUTE_READWRITE, &dwOldProtect))
	{
//#if EX_AH == TRUE
//		LoadLibrary("ExAntiCheat");
//#endif
#if EX_AH == TRUE
		if(!LoadLibrary("ex.dll"))
		{
			MessageBox(0, "Load Error ex.dll", "Start Error", ERROR);
			ExitProcess(0);
		}
#endif

#ifdef _LAUNCHER_
		char **	Command	= 0;
		CommandLineToArg(GetCommandLine(), &Command);
		if( strcmp(_LAUNCHER_, Command[1]) )
		{
			MessageBox(0, "Please start game from Launcher", "Start Error", ERROR);
			ExitProcess(0);
		}
#endif
#if(ANTI_CHEAT_PLUS==TRUE)
		g_AntiCheatPlus.Load();
#endif
		Config.Start();
		Security.ConfigStart();
		KeyboardSetHook(true); 
		MouseSetHook(true);
#if(_ITEM_LOAD_)
		gLoadItem.Load();
#endif
		//InitInterface();	//Delete
		gInterface.Load();
		gRageSystem.Load();
		InitProtocol();
		BugFix();		
		ChatWndHooks(); 

	#ifndef __MuRain__
			Ip();
			Version();
			SerialNumber();
	#else
		#if(DEBUG)
			Ip();
			Version();
			SerialNumber();
		#endif
	#endif
#ifdef _IP_NEW_
		Ip();
#endif
#ifdef _SERIAL_NEW_
		SerialNumber();
		Version();
#endif

	
		InitMiniMap();
		NewItemsInit();
		NewWingsStart();
		cMakePreviewCharSetLoad();
#ifdef _GRAND_SYSTEM_
		InitMaps();
		Init_Monsters();
		InitGlowFunc();
		initEffectSkil();
		InitSocketItem();
#endif
#ifdef _PET_CUSTOM_
		StartNewCustomPet();
#endif
#if(exRECONNECT)
		gConnectEx.Load();
#endif
#if(_LOAD_GLOW_)
		gLoadGlow.Load();
#endif
#ifdef ITEM_EFFECT
		AttachNewEffect();
#endif
#if( NEW_HP_BAR )
		gViewePortInfo.InitNewHpBar();
#endif
#if(NEW_GLOW_EFFECT)
	gGraphics.Load();
#endif
		CloseHandle(CreateThread(NULL,0,Timer,NULL,0,NULL));	
		CloseHandle(CreateThread(NULL,0,UpdateTimer,NULL,0,NULL));
	}
	else
	{
		MessageBoxA(NULL, "Don't use cheat programs!", "Error", MB_ICONERROR); 
		::ExitProcess(0);
	}
}

