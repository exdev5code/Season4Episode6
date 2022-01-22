#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_
#include "Utilits.h"
#include "Bow.h"
#include "Console.h"
#include "ToolKit.h"
#include "Items.h"

DWORD FUNCTIONC = 0x00650FF0;
DWORD RETURN = 0x00699416;
DWORD BOW = 0;

__declspec(naked) void SkillEffect()
{
	_asm
	{
		MOV EDX,DWORD PTR SS:[EBP-0x8]
		MOV DWORD PTR SS:[EBP-0x14],EDX
		MOV BOW,EDX
	}

	if(BOW >= ITEM(4,30) && BOW <= ITEM(4,255))
	{
		_asm
		{
			PUSH -1                                  ; /Arg12 = -1
			PUSH 0                                   ; |Arg11 = 0
			PUSH 0                                   ; |Arg10 = 0
			MOV DX,WORD PTR SS:[EBP+0x18]            ; |
			PUSH EDX                                 ; |Arg9
			MOV AX,WORD PTR SS:[EBP+0x14]            ; |
			PUSH EAX                                 ; |Arg8
			MOV ECX,DWORD PTR SS:[EBP+0x0C]          ; |
			MOV DX,WORD PTR DS:[ECX+0x2C]            ; |
			PUSH EDX                                 ; |Arg7
			MOV EAX,DWORD PTR SS:[EBP+0x0C]          ; |
			PUSH EAX                                 ; |Arg6
			MOV ECX,DWORD PTR SS:[EBP-0x0C]          ; |
			PUSH ECX                                 ; |Arg5
			MOV EDX,DWORD PTR SS:[EBP+0x0C]          ; |
			ADD EDX,0x9C                             ; |
			PUSH EDX                                 ; |Arg4
			MOV EAX,DWORD PTR SS:[EBP+0x0C]          ; |
			ADD EAX,0x108                            ; |
			PUSH EAX                                 ; |Arg3
			MOV ECX,DWORD PTR SS:[EBP+0x0C]          ; |
			ADD ECX,0x0FC                            ; |
			PUSH ECX                                 ; |Arg2
			PUSH 296//0x144                          ; |Arg1 = 144
			CALL FUNCTIONC                           ; \Main.00650FF0
		}
	}

	_asm{JMP RETURN}
}

DWORD IBOW = 0;
DWORD SHOWBOW = 0x0059F77C;
DWORD DEFBOW  = 0x0059F7BB;

_declspec(naked)void FixShowInventoryBow()
{
	_asm
	{
		MOV IBOW, ESI
	}

	if(IBOW == 0x0B5A)
	{
		_asm{JMP SHOWBOW}
	}
	else if(IBOW >= ITEM(4,30) && IBOW <= ITEM(4,255))
	{
		_asm{JMP SHOWBOW}
	}
	else
	{
		_asm{JMP DEFBOW}
	}
}

void initEffectSkil()
{
	SetNop(0x00699410,6);
	WriteJmp(0x00699410,(DWORD)&SkillEffect);

	SetNop(0x0059F774,6);
	WriteJmp(0x0059F774,(DWORD)&FixShowInventoryBow);
}
#endif