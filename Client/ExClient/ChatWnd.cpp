#include "StdAfx.h"
#include "ChatWnd.h"
#include "ToolKit.h"
#include "TMemory.h"
#include "NewHpBar.h"

DWORD dwMsgType;
DWORD dwYpos;
DWORD dwHeight;
DWORD dwMsgCnt;
DWORD dwScrollPos;

int SystChatSepar = 190;

__declspec(naked) void ShowSysMsgs()
{
	__asm 
	{
		call GetDisplayMsgType
		mov dwMsgType, eax
		MOV ECX, DWORD PTR SS:[EBP-4]
		MOV EAX, DWORD PTR DS:[ECX+0xB4]
		MOV dwYpos, EAX
		MOV EAX, DWORD PTR DS:[ECX+0xC4]
		MOV dwHeight, EAX
		// ----
		MOV EDX, [SystChatSepar]
		MOV DWORD PTR DS:[ECX+0xB4], EDX
		MOV DWORD PTR DS:[ECX+0xC4], 0x64
		MOV EAX, DWORD PTR DS:[ECX+0xC8]
		MOV dwMsgCnt, EAX
		MOV DWORD PTR DS:[ECX+0xC8], 4		//string Log
		MOV EAX, DWORD PTR DS:[ECX+0xD4]
		MOV dwScrollPos, EAX
		PUSH 3
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL SetDisplayMsgType
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL ShowChatMsgs
		MOV ECX, DWORD PTR SS:[EBP-4]
		PUSH dwMsgType
		CALL SetDisplayMsgType
		MOV ECX, DWORD PTR SS:[EBP-4]
		MOV EAX, dwYpos
		MOV DWORD PTR DS:[ECX+0xB4], EAX
		MOV EAX, dwHeight
		MOV DWORD PTR DS:[ECX+0xC4], EAX
		MOV EAX, dwMsgCnt
		MOV DWORD PTR DS:[ECX+0xC8], EAX
		MOV EAX, dwScrollPos
		MOV DWORD PTR DS:[ECX+0xD4], EAX
		MOV ECX, DWORD PTR SS:[EBP-4]
		CALL ShowChatMsgs
		retn
	}
}

__declspec(naked) void FixSysMsg1()
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg1_FALSE
		_true:
		pop eax
		jmp FixSysMsg1_TRUE
	}
}

__declspec(naked) void FixSysMsg2()
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg2_FALSE
		_true:
		pop eax
		jmp FixSysMsg2_TRUE
	}
}

__declspec(naked) void FixSysMsg3()
{
	__asm 
	{
		cmp dword ptr ss:[ebp+0x10], 3
		je _true
		call NewCall
		jmp FixSysMsg3_FALSE
		_true:
		pop eax
		jmp FixSysMsg3_TRUE
	}
}

//006F5AE1

//	pDrawText

#define pDrawTextLog  ((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int Arg4, int Arg5, LPINT Arg6, int Arg7)) 0x41EE57)

#if(ANTI_ELITE==TRUE)
AntiElite g_AntiElite;

void AntiElite::Check(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)
{
	char tt[] = " > meet player ";
	if(!strncmp(Text, tt, strlen(tt)))
	{
		//g_AntiCheat.Write("Hack Elite Clicker");
		ExitProcess(0);
	}
	pDrawTextLog(This, PosX, PosY, Text, nCount, nTabPositions, lpnTabStopPositions,  nTabOrigin);
	//return true;
}
//---------------------------------------------------------------------------
#endif
void ChatWndHooks()
{
	HookThis((DWORD)ShowSysMsgs, ShowChatMsgsCall_Hook);
	WriteJmp(FixSysMsg1_Hook, (DWORD)FixSysMsg1);
	WriteJmp(FixSysMsg2_Hook, (DWORD)FixSysMsg2);
	WriteJmp(FixSysMsg3_Hook, (DWORD)FixSysMsg3);
#if(ANTI_ELITE==TRUE)
	SetRange((LPVOID)0x006F5AE1, 5, ASM::NOP);
	SetOp((LPVOID)0x006F5AE1,  (LPVOID)g_AntiElite.Check, ASM::CALL);
#endif
}  