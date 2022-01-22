//=================================
// - Name: "Main.dll"
// - Project: 1.0.0.0
// - Game Version: 1.03.11
// - MU Developer: Nemesis
//=================================

#include "Stdafx.h"
#include "Wings.h"
#include "Utilits.h"
#include "ToolKit.h"
#include "Message.h"
//#include "newjewels.h"
#include "Console.h"
#include "TMemory.h"


int UseItemLoop = GetPrivateProfileIntA("Main","IsWeapons",0,".\\Data\\Local\\Main.bmd");

//DWORD pItemType = 0;

DWORD	WingsAddExcellentStatus_Pointer;
DWORD	WingsAddExcellentStatus_Buff;
// --
DWORD	WingsAddLuckOption_Pointer;
DWORD	WingsAddLuckOption_Buff;
// --
BYTE	WingsAdd28Option_OptionNumber;
BYTE	WingsAdd28Option_OptionValue;
BYTE	WingsAdd28Option_OptionStat;
DWORD	WingsAdd28Option_Pointer;
DWORD	WingsAdd28Option_NewOption;
DWORD	WingsAdd28Option_Buff;
// --
WORD	WingsHideExcellentStatusText_Pointer;
DWORD	WingsHideExcellentStatusText_Buff;
// --
WORD	WingsShowAdditionals_Pointer;
DWORD	WingsShowAdditionals_Buff;
DWORD	WingsShowAdditionals_Percent;
// --
WORD	WingsShowDur_Pointer;
DWORD	WingsShowDur_Buff;
DWORD	WingsShowDur_Set_Buff;
// --
WORD	WingsSetGoldName_Pointer;
DWORD	WingsSetGoldName_Buff;
// --
DWORD	WingsDisableLevelShine_Pointer;
DWORD	WingsDisableLevelShine_SubPointer;
DWORD	WingsDisableLevelShine_Buff;
// --
DWORD	WingsHideExcellentGlow_Pointer;
DWORD	WingsHideExcellentGlow_Buff;
// --
BYTE	WingsAddCharSet_CharSet16;
DWORD	WingsAddCharSet_CharSet16_Buff;
BYTE	WingsAddCharSet_CharSet9;
WORD	WingsAddCharSet_CharSet9_Pointer;
DWORD	WingsAddCharSet_CharSet9_Buff;
// --
DWORD	WingsSetInvisibleEffect_Pointer;
DWORD	WingsSetInvisibleEffect_Buff;
// --
DWORD	WingsAllowJewelsInsert_Pointer;
DWORD	WingsAllowJewelsInsert_Buff;
// --
DWORD	WingsAddSpecialEffect_Pointer;
DWORD	WingsAddSpecialEffect_Buff;
DWORD	WingsAddSpecialEffect_Arg2;
DWORD	WingsAddSpecialEffect_Arg3;
DWORD	WingsAddSpecialEffect_Arg4;
DWORD	WingsAddSpecialEffect_Arg5;
DWORD	WingsAddSpecialEffect_Arg6;
DWORD	WingsAddSpecialEffect_Arg7;
DWORD	WingsAddSpecialEffect_This;
// --
DWORD	WingsAllowListMove_Pointer;
DWORD	WingsAllowListMove_Buff;

pSetEffect MU_SetEffect	= (pSetEffect)0x0069BCD9;

#define ITEM_INTER 834

#define ITEM(x, y) ((x * 512) + y)
#define ITEM2(x, y) ((x * 512) + y + ITEM_INTER)

//#define LOAD_ITEM(x,y) ((x) * 512 + (y) + ITEM_INTER)
#define GET_ITEM(x,y) (x * 512 + y) + ITEM_INTER


//void __declspec(naked) SetItemEffect()
//{
//	_asm
//	{
//		MOV pItemType, ECX
//	}
//	if (pItemType == GET_ITEM(11, 52))	//Hades Set
//	{
//		_asm
//		{
//			MOV ESI, HDK_ITEM_EFFECT_ALLOW
//			JMP ESI
//		}
//	}
//	_asm
//	{
//		MOV ESI, HDK_ITEM_EFFECT_NOT_ALLOW 
//		JMP ESI
//	}
//}
//
//void __declspec(naked) SetColorEffect()
//{
//	_asm
//	{
//		MOV pItemType, ECX
//	}
//	if (pItemType == GET_ITEM(11, 52))	//Hades Set
//	{
//		_asm
//		{
//			MOV EDX, DWORD PTR SS:[EBP+0xC]
//			MOV DWORD PTR DS:[EDX+0x9C],0	//R
//			MOV EAX, DWORD PTR SS:[EBP+0xC]
//			MOV DWORD PTR DS:[EAX+0xA0],0	//G
//			MOV ECX, DWORD PTR SS:[EBP+0xC]
//			MOV DWORD PTR DS:[ECX+0xA4],0x3F000000	//B
//		}
//	}
//	_asm
//	{
//		MOV ESI, HDK_NEXT_ITEM_COLOR
//		JMP ESI
//	}
//}

//4F0C39

void __declspec(naked) ItemsAddSpecialEffect()	//508EE8 = 1.03Y+ //4F2502 = 1.03k
{
	//7e04 - дымчатый шар
	//7e6e - огонь
	//7e22 - хрень во все стороны (норм для суммонера), от воды
	//7e2c - пузырики
	//7e72(70) - дым (как на бц, от огня)
	//7e1f - стандартная
	//7d02 - Bola Blanca
	//7d30 - маленькие шарики во все стороны[2]
	//7d36 - крутяшийся синий комок хуйни (для см крыльев норм)
	//0 - подсветка
	//1 - шар со следом
	//2 - свет
	//7d48 - шар, как 7d4d, только мигает
	//7d4d - красный шар со следом (для бк крыльев норм)
	//0 - столб
	//1 - шар со следом
	//2 - шар мегающий
	//7d54 - брызги крови
	//7d65 - дым зеленый в разные стороны
	//7d66 - коричневый след пыли
	//7D69 - дым (черный)
	//1 - след дыма
	//2 - в разные стороны
	//7d71 - звездочки
	//0 = полоска за тобой
	//1 = по меньше
	//7d77 - звездо аура (для эльф крыльев)
	//0 = толстая аура следующая за тобой
	//1 = мелкие звездочки (ели заметные)
	//2 = мегающая подцветка
	//7d83 - аура из шариков[3]
	//7dd6 - пузырики
	//7DF8 - Efecto portal
	//7DF2 - Bola negra
	//7E22 - Copo de nieve
	//7D55 - Fuego Blanco
	//7D61 - Estrellitas perseguidoras
	//7DC4 - Burbujas Ascendentes
	//7D20 - Chispitas
	//7E10 - Polvo Blanco que cae
	//7E56 - Bloom
	//7E50 - Bola Blanca parpadeante
	//7E6A - Luz Parpadeante
	// ----
	_asm
	{
		mov eax, dword ptr ss:[ebp+8]
		mov esi, dword ptr ds:[eax+0x1c8]
		mov WingsAddSpecialEffect_Pointer, esi
	}
	//int NumberTesteCode = WingsAddSpecialEffect_Pointer;
	//MessageBoxA(NULL,(LPCTSTR)WingsAddSpecialEffect_Pointer,(LPCTSTR)WingsAddSpecialEffect_Pointer,0);
	//Message_Glob(1,(char*)WingsAddSpecialEffect_Pointer);
	if( WingsAddSpecialEffect_Pointer == ITEM2(12, 180) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 180) ) // Wings of Heaven
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1D00000
			MOV DWORD PTR SS:[EBP-0x18], 0x40A00000
			MOV DWORD PTR SS:[EBP-0x14], 0x428C0000
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 0.8, 0);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 0.9, 0);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 1.0, 0);


	}
	else if( WingsAddSpecialEffect_Pointer == ITEM2(12, 181) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 181) ) // Wings of Demonic
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1D00000	//-24.000000 -> Coords Atras - Adelante (si sumas es atras si restas es adelante)
			MOV DWORD PTR SS:[EBP-0x18], 0x40A00000	//5.000000 -> Coords Derecha - Izquierda (si sumas es derecha si restas es izquierda)
			MOV DWORD PTR SS:[EBP-0x14], 0x428C0000	//70.000000 -> Coords Arriba - Abajo (si sumas es arriba si restas es abajo)
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7d37, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 1.0, 1);

	}
	else if( WingsAddSpecialEffect_Pointer == ITEM2(12, 183) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 183) ) // Wings of Demonic
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1D00000
			MOV DWORD PTR SS:[EBP-0x18], 0
			MOV DWORD PTR SS:[EBP-0x14], 0x428C0000
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 0.25, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 0.15, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 0.35, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 0.45, 1);
		MU_SetEffect(0x7d03, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 0.55, 1);
	}
	else if( WingsAddSpecialEffect_Pointer == ITEM2(12, 182) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 182) ) // Wings of Blossom
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1A00000
			MOV DWORD PTR SS:[EBP-0x18], 0x40000000//41200000
			MOV DWORD PTR SS:[EBP-0x14], 0x41F00000//41F00000
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d20, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
	}
	else if( WingsAddSpecialEffect_Pointer == ITEM2(12, 185) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 185) ) // Wings of Blossom
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1D00000
			MOV DWORD PTR SS:[EBP-0x18], 0x40A00000
			MOV DWORD PTR SS:[EBP-0x14], 0x428C0000
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7E6A, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
	}
#ifdef _WINGS_5LVL_
	else if( WingsAddSpecialEffect_Pointer == ITEM2(12, 189) || WingsAddSpecialEffect_Pointer == ITEM2(12 * 161, 189) ) // Complete
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x1C], 0xC1D00000
			MOV DWORD PTR SS:[EBP-0x18], 0x40A00000
			MOV DWORD PTR SS:[EBP-0x14], 0x428C0000
			// ----
			PUSH 1
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg7, eax
			PUSH EAX
			LEA ECX,[EBP-0x1C]
			mov WingsAddSpecialEffect_Arg6, ecx
			PUSH ECX
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			MOV EAX,DWORD PTR DS:[EDX+0x1A4]
			mov WingsAddSpecialEffect_Arg5, eax
			PUSH EAX
			MOV ECX,DWORD PTR SS:[EBP-0x34]
			mov WingsAddSpecialEffect_This, ecx
			mov WingsAddSpecialEffect_Buff, 0x004CC40E
			CALL WingsAddSpecialEffect_Buff
			// ----
			MOV ECX,DWORD PTR SS:[EBP+0x0C]
			ADD ECX, 0x9C
			mov WingsAddSpecialEffect_Arg4, ecx
			MOV EDX,DWORD PTR SS:[EBP+0x0C]
			ADD EDX, 0x1C8
			mov WingsAddSpecialEffect_Arg3, edx
			LEA EAX,[EBP-0x44]
			mov WingsAddSpecialEffect_Arg2, eax
		}
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 3.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 4.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 2.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 1, 1.0, 1);
		MU_SetEffect(0x7d67, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 2, 2.0, 1);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 0.8, 0);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 0.9, 0);
		MU_SetEffect(0x7dF3, WingsAddSpecialEffect_Arg2, WingsAddSpecialEffect_Arg3, WingsAddSpecialEffect_Arg4, 3, 1.0, 0);
	}
#endif
	_asm
	{
		mov eax, dword ptr ss:[ebp+0x0c]
		mov esi, dword ptr ds:[eax+0x30]
		mov WingsAddSpecialEffect_Pointer, esi
	}
	// ----
	
	if( WingsAddSpecialEffect_Pointer != 0x288 )
	{
		_asm
		{
			mov WingsAddSpecialEffect_Buff, 0x004F3348
			jmp WingsAddSpecialEffect_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsAddSpecialEffect_Buff, 0x004F2C4B
			jmp WingsAddSpecialEffect_Buff
		}
	}

}

void __declspec(naked) WingsAddCharSet () // -> 57 -> 004FE263  |> 8B4D 0C        MOV ECX,DWORD PTR SS:[EBP+C]
{
    _asm
    {
        mov ecx, dword ptr ss:[ebp+0x0c]
        xor edx, edx
        mov dl, byte ptr ds:[ecx+0x08]
        and edx, 0x00000007
        mov byte ptr ss:[ebp-4], dl
        mov eax, dword ptr ss:[ebp-4]
        and eax, 0x000000FF
        mov WingsAddCharSet_CharSet9_Buff, eax
    }
    // ----
    if( WingsAddCharSet_CharSet9_Buff > 0 )
    {
        _asm
        {
            mov cl, byte ptr ss:[ebp-4]
            mov byte ptr ss:[ebp-0x3c], cl
            mov WingsAddCharSet_CharSet9, cl
        }
    }
    else
    {
        goto CHARSET16;
    }

    if( WingsAddCharSet_CharSet9 == 1 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 180);
    }
    else if( WingsAddCharSet_CharSet9 == 2 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 181);
    }
    else if( WingsAddCharSet_CharSet9 == 3 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 182);
    }
    else if( WingsAddCharSet_CharSet9 == 4 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 183);
    }
    else if( WingsAddCharSet_CharSet9 == 5 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 184);
    }
    else if( WingsAddCharSet_CharSet9 == 6 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 185);
    }
	//Custom Wings2.5
	else if( WingsAddCharSet_CharSet9 == 7 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 186);
    }
	else if( WingsAddCharSet_CharSet9 == 8 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 187);
    }
	else if( WingsAddCharSet_CharSet9 == 9 )
    {
        WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 188);
    }
#ifdef _WINGS_5LVL_
	else if( WingsAddCharSet_CharSet9 == 10 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 189);
	}
	else if( WingsAddCharSet_CharSet9 == 11 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 190);
	}
	else if( WingsAddCharSet_CharSet9 == 12 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 191);
	}
	else if( WingsAddCharSet_CharSet9 == 13 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 192);
	}
	else if( WingsAddCharSet_CharSet9 == 14 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 193);
	}
	else if( WingsAddCharSet_CharSet9 == 15 )
	{
		WingsAddCharSet_CharSet9_Pointer = ITEM2(12, 194);
	}
#endif
    // ----
    _asm
    {
        mov edx, dword ptr ss:[ebp-8]
        mov ax, WingsAddCharSet_CharSet9_Pointer
        mov word ptr ds:[edx+0x1c8], ax
    }
    // ----
CHARSET16:
    // ----
    _asm
    {
        mov ecx, dword ptr ss:[ebp+0x0c]
        xor edx, edx
        mov dl, byte ptr ds:[ecx+0x0f]
        sar edx, 2
        and edx, 0x00000007
        mov byte ptr ss:[ebp-4], dl
        mov eax, dword ptr ss:[ebp-4]
        and eax, 0x000000FF
        mov WingsAddCharSet_CharSet16_Buff, eax
    }
    // ----
    if( WingsAddCharSet_CharSet16_Buff > 0 )
    {
        _asm
        {
            mov cl, byte ptr ss:[ebp-4]
            mov byte ptr ss:[ebp-0x3c], cl
            mov WingsAddCharSet_CharSet16, cl
        }
    }
    else
    {
        _asm
        {
            mov WingsAddCharSet_CharSet16_Buff, 0x004FE2B3    // 1.03K JPN
            jmp WingsAddCharSet_CharSet16_Buff
        }
    }
    if( WingsAddCharSet_CharSet16 == 6 )
    {
        _asm
        {
            mov edx, dword ptr ss:[ebp-8]
            mov word ptr ds:[edx+0x1c8], 0x1B6D                // FIX 1.03K (1.03.25 1BA2)


            mov WingsAddCharSet_CharSet16_Buff, 0x004FE2B3    // 1.03K JPN
            jmp WingsAddCharSet_CharSet16_Buff
        }
    }
    else
    {
        _asm
        {
            mov WingsAddCharSet_CharSet16_Buff, 0x004FE29C    // 1.03K
            jmp WingsAddCharSet_CharSet16_Buff
        }
	}
}

void __declspec(naked) WingsSetInvisiableEffect()
{
	_asm
	{
		mov WingsSetInvisibleEffect_Buff, esi
		// ----
		mov ecx, dword ptr ss:[ebp+8]
		mov esi, dword ptr ds:[ecx+0x30]
		mov WingsSetInvisibleEffect_Pointer, esi
		// ----
		mov esi, WingsSetInvisibleEffect_Buff
	}
	// ----
	if( WingsSetInvisibleEffect_Pointer == 0x1D54	//Cloak of Invisibility 
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 185)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 188)
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 182) 
		|| WingsSetInvisibleEffect_Pointer == ITEM2(12, 183) )
	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x005CEE41
			jmp WingsSetInvisibleEffect_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsSetInvisibleEffect_Buff, 0x005CEEB7
			jmp WingsSetInvisibleEffect_Buff
		}
	}
}

void __declspec(naked) WingsAdd28Option() // -> 199 -> 0050C453
{
	_asm
	{
		mov edx, dword ptr ss:[ebp+8]
		// ----
		movsx eax, word ptr ds:[edx]
		mov WingsAdd28Option_Pointer, eax
		// ----
		mov edx, dword ptr ss:[ebp-0x14]
		mov WingsAdd28Option_NewOption, edx
		// ----
		mov cl, byte ptr ss:[ebp-0x10]
		mov WingsAdd28Option_OptionValue, cl
	}

	switch(WingsAdd28Option_Pointer)
	{
	case ITEM(12, 43):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::CurseSpell;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	//Custom Wings4
	case ITEM(12, 180):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	case ITEM(12, 181):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::Damage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	case ITEM(12, 182):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::Damage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	case ITEM(12, 183):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::Damage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	case ITEM(12, 184):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::Damage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
	case ITEM(12, 185):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::CurseSpell;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
		//Custom Wings2.5
		case ITEM(12, 186):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
		case ITEM(12, 187):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
		// --
		case ITEM(12, 188):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::Defense;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
#ifdef _WINGS_5LVL_
	case ITEM(12, 189):
	case ITEM(12, 190):
	case ITEM(12, 191):
	case ITEM(12, 192):
	case ITEM(12, 193):
	case ITEM(12, 194):
		{
			if( (WingsAdd28Option_NewOption >> 4) & 1 )
			{
				WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
				WingsAdd28Option_OptionNumber	= eItemOption::WizardryDamage;
			}
			else
			{
				if( (WingsAdd28Option_NewOption >> 5) & 1 )
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue * 4;
					WingsAdd28Option_OptionNumber	= eItemOption::CurseSpell;
				}
				else
				{
					WingsAdd28Option_OptionStat		= WingsAdd28Option_OptionValue;
					WingsAdd28Option_OptionNumber	= eItemOption::HPRecovery;
				}
			}
		}
		break;
#endif
		// --
	default:
		{
			_asm
			{
				mov WingsAdd28Option_Buff, 0x0050C51A
				jmp WingsAdd28Option_Buff
			}
		}
		break;
	}
	_asm
	{
		mov edx, dword ptr ss:[ebp-0x10]
		shl edx, 2
		// ----
		mov eax, dword ptr ss:[ebp+8]
		xor ecx, ecx
		// ----
		mov cl, byte ptr ds:[eax+0x25]
		mov eax, dword ptr ss:[ebp+8]
		mov dl, WingsAdd28Option_OptionStat
		mov byte ptr ds:[ecx+eax+0x2e], dl
		// ----
		xor edx, edx
		mov dl, byte ptr ds:[eax+0x25]
		mov cl, WingsAdd28Option_OptionNumber
		mov byte ptr ds:[edx+eax+0x26], cl
		// ----
		add dl, 1
		mov byte ptr ds:[eax+0x25], dl
		// ----
		mov WingsAdd28Option_Buff, 0x0050C51A
		jmp WingsAdd28Option_Buff
	}
}

void __declspec(naked) WingsShowAdditionals() // -> 29 -> 005AED3E
{
	_asm
	{
		cmp cx, ITEM(12, 36)
		jl EXIT
		cmp cx, ITEM(12, 40)
		jle SET_ADD

		cmp cx, ITEM(12, 43)
		je SET_ADD

		cmp cx, ITEM(12, 180)
		jl EXIT
		cmp cx, ITEM(12, 185)
		jle SET_ADD_NEW

		cmp cx, ITEM(12, 186)
		jl EXIT
		cmp cx, ITEM(12, 188)
		jle SET_ADD_2_5

#ifdef _WINGS_5LVL_
		cmp cx, ITEM(12, 189)
		jl EXIT
		cmp cx, ITEM(12, 194)
		jle SET_ADD_5
#endif

		JMP EXIT

		SET_ADD:
		lea esi, [ebp+ebp+39] // WingsShowAdditionals_Percent = 39;
		mov WingsShowAdditionals_Buff, 0x00595282
		jmp WingsShowAdditionals_Buff
		// ----
		SET_ADD_NEW:
		lea esi, [ebp+ebp+45] // WingsShowAdditionals_Percent = 45;
		mov WingsShowAdditionals_Buff, 0x00595282
		jmp WingsShowAdditionals_Buff
		// ----
		SET_ADD_2_5:
		lea esi, [ebp+ebp+35] // WingsShowAdditionals_Percent = 35;
		mov WingsShowAdditionals_Buff, 0x00595282
		jmp WingsShowAdditionals_Buff
		// ----
#ifdef _WINGS_5LVL_
		SET_ADD_5:
		lea esi, [ebp+ebp+50] // WingsShowAdditionals_Percent = 50;
		mov WingsShowAdditionals_Buff, 0x00595282
		jmp WingsShowAdditionals_Buff
#endif
		// ----
		EXIT:
		mov WingsShowAdditionals_Buff, 0x005952FF
		jmp WingsShowAdditionals_Buff
	}
}

void __declspec(naked) WingsAddLuckOption() // -> 8 -> 0050B8CD
{
	_asm
	{
		mov WingsAddLuckOption_Pointer, edx
	}
	//Console.ConsoleOutput(RED,"[WingsAddLuckOption]  %d",(int)WingsAddLuckOption_Pointer);
	// ----
	if( WingsAddLuckOption_Pointer == ITEM(12, 43) || WingsAddLuckOption_Pointer >= ITEM(12, 180) && WingsAddLuckOption_Pointer <= ITEM(12, END_NEW_WING) )
	{
		_asm
		{
			mov WingsAddLuckOption_Buff, 0x0050B8D5
			jmp WingsAddLuckOption_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsAddLuckOption_Buff, 0x0050B8F3
			jmp WingsAddLuckOption_Buff
		}
	}
}
//--------------------------------------------------------------------------

void __declspec(naked) WingsAddExcellentStatus() // -> 12 -> 0050B688
{
	_asm
	{
		mov WingsAddExcellentStatus_Pointer, edx
	}
	// ----
	if( WingsAddExcellentStatus_Pointer == ITEM(12, 43) || 
		( WingsAddExcellentStatus_Pointer >= ITEM(12, 180) && WingsAddExcellentStatus_Pointer <= ITEM(12, END_NEW_WING) ) )
	{
		_asm
		{
			mov WingsAddExcellentStatus_Buff, 0x0050B694
			jmp WingsAddExcellentStatus_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsAddExcellentStatus_Buff, 0x0050B77F
			jmp WingsAddExcellentStatus_Buff
		}
	}
}

#define SetItemSpecialStat        ((int(*)(short ItemID, int Arg2, BYTE SpecialOption, BYTE SpecialValue, int Arg5)) 0x5A6360) //5C0DC0 1.03Y+
#define oSetItemSpecialStat        0x005AF065	//005CA0B0 1.03Y+

int __cdecl gSetItemSpecialStat(short ItemID, int Arg2, BYTE SpecialOption, BYTE SpecialValue, int Arg5)
{
    switch(ItemID)
    {
        case ITEM(12, 180):
        case ITEM(12, 181):
        case ITEM(12, 182):
        case ITEM(12, 183):
        case ITEM(12, 184):
        case ITEM(12, 185):
		case ITEM(12, 186):
		case ITEM(12, 187):
		case ITEM(12, 188):
#ifdef _WINGS_5LVL_
        case ITEM(12, 189):
        case ITEM(12, 190):
        case ITEM(12, 191):
        case ITEM(12, 192):
        case ITEM(12, 193):
		case ITEM(12, 194):
#endif
        {
            switch(SpecialOption)
            {
            case eItemOption::IgnorOpDefense:
                {
                    SpecialValue = 8;
                }
                break;
                // --
            case eItemOption::ReturnAttack:
                {
                    SpecialValue = 10;
                }
                break;
                // --
            case eItemOption::CompleteLife:
                {
                    SpecialValue = 7;
                }
                break;
                // --
            case eItemOption::CompleteMana:
                {
                    SpecialValue = 7;
                }
                break;
				// --
			case eItemOption::CurseSpell:
				{
					SpecialValue = 10;
				}
				break;
				// --
			case eItemOption::Defense:
				{
					SpecialValue = 4;
				}
				break;
            }
        }
        break;
    }
    // ----
    return SetItemSpecialStat(ItemID, Arg2, SpecialOption, SpecialValue, Arg5);
}

void __declspec(naked) WingsHideExcellentGlow() // -> 28 -> 005D22A3
{
	//If you use my variation of asm all without bug's :)
	//If you use variation of c++ all items lost excellent glow :(
	//FUCK!!!!
	/*
	_asm
	{
		mov ecx, dword ptr ss:[ebp+8]
		mov edx, dword ptr ds:[ecx+0x30]
		mov WingsHideExcellentGlow_Pointer, eax
	}
	// ----
	if( WingsHideExcellentGlow_Pointer >= ITEM2(12, 36) && WingsHideExcellentGlow_Pointer <= ITEM2(12, 43) 
		|| WingsHideExcellentGlow_Pointer >= ITEM2(12, 180) && WingsHideExcellentGlow_Pointer <= ITEM2(12, 185) )
	{
		_asm
		{
			mov WingsHideExcellentGlow_Buff, 0x005D23EE
			jmp WingsHideExcellentGlow_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsHideExcellentGlow_Buff, 0x005D22B3
			jmp WingsHideExcellentGlow_Buff
		}
	}
	*/
	_asm
	{
		CMP DWORD PTR DS:[ECX+0x30],0x1B6D
		JE HideExcellentGlowOri
		JE HideExcellentGlow1
		JE HideExcellentGlow2
		JE HideExcellentGlow3
		JE HideExcellentGlow4
		JE HideExcellentGlow5
		JE HideExcellentGlow6
		//Custom Wings2.5
		JE HideExcellentGlow7
		JE HideExcellentGlow8
		JE HideExcellentGlow9
HideExcellentGlowOri:
		CMP DWORD PTR DS:[ECX+0x30],0x1B6D	//Item Original
		JE NotExcellentGlow
HideExcellentGlow1:
		CMP DWORD PTR DS:[ECX+0x30],0x18B4	//Wings of Demonic
		JE NotExcellentGlow
HideExcellentGlow2:
		CMP DWORD PTR DS:[ECX+0x30],0x18B5	//Wings of Heaven
		JE NotExcellentGlow
HideExcellentGlow3:
		CMP DWORD PTR DS:[ECX+0x30],0x18B6	//Wings of Blossom
		JE NotExcellentGlow
HideExcellentGlow4:
		CMP DWORD PTR DS:[ECX+0x30],0x18B7	//Wings of Sparks
		JE NotExcellentGlow
HideExcellentGlow5:
		CMP DWORD PTR DS:[ECX+0x30],0x18B8	//Wings of Raven
		JE NotExcellentGlow
HideExcellentGlow6:
		CMP DWORD PTR DS:[ECX+0x30],0x18B9	//Wings of Eternal
		JE NotExcellentGlow
		//Custom Wings2.5
HideExcellentGlow7:
		CMP DWORD PTR DS:[ECX+0x30],0x18BA	//Wings of Eternal
		JE NotExcellentGlow
HideExcellentGlow8:
		CMP DWORD PTR DS:[ECX+0x30],0x18BB	//Wings of Eternal
		JE NotExcellentGlow
HideExcellentGlow9:
		CMP DWORD PTR DS:[ECX+0x30],0x18BC	//Wings of Eternal
		JE NotExcellentGlow
		//---------------
		JE ReturnNormalLoad
NotExcellentGlow:
		MOV ESI,0x005D23EE
		JMP ESI
ReturnNormalLoad:
		MOV ESI,0x005D22AD
		JMP ESI
	}
}
//--------------------------------------------------------------------------

void __declspec(naked) WingsDisableLevelShine() // 19 -> 005CDCC8
{
	_asm
	{
		mov WingsDisableLevelShine_Pointer, edx
		sub edx, ITEM2(12, 15)
		mov WingsDisableLevelShine_SubPointer, edx
		mov dword ptr ss:[ebp-0x4cc], edx
	}
	// ----
	if( WingsDisableLevelShine_Pointer >= ITEM2(12, 180) && WingsDisableLevelShine_Pointer <= ITEM2(12, END_NEW_WING) )
	{
		_asm
		{
			mov dword ptr ss:[ebp-8], 0
		}
	}
	// ----
	if( WingsDisableLevelShine_SubPointer > 32 )
	{
		_asm
		{
			mov WingsDisableLevelShine_Buff, 0x005CE14E
			jmp WingsDisableLevelShine_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsDisableLevelShine_Buff, 0x005CDCE1
			jmp WingsDisableLevelShine_Buff
		}
	}
}
//--------------------------------------------------------------------------

void __declspec(naked) WingsSetGoldName() // -> 42 -> 00590628
{
	
	_asm
	{
		mov ax, word ptr ss:[ebp]
		mov WingsSetGoldName_Pointer, ax
	}
	// ----
	if(  WingsSetGoldName_Pointer >= ITEM(12, 3) && WingsSetGoldName_Pointer <= ITEM(12, 6) 
		|| WingsSetGoldName_Pointer == ITEM(13, 30) 
		|| WingsSetGoldName_Pointer >= ITEM(12, 36) && WingsSetGoldName_Pointer <= ITEM(12, 40) 
		|| WingsSetGoldName_Pointer >= ITEM(12, 42) && WingsSetGoldName_Pointer == ITEM(12, 43) 
		|| WingsSetGoldName_Pointer >= ITEM(12, 180) && WingsSetGoldName_Pointer <= ITEM(12, END_NEW_WING) )
	{
		_asm
		{
			mov WingsSetGoldName_Buff, 0x00590652
			jmp WingsSetGoldName_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsSetGoldName_Buff, 0x0059066D
			jmp WingsSetGoldName_Buff
		}
	}
	
	_asm
	{
		CMP AX,0x182B	//Alas level 3 de Summoner
		JE SetGoldNameOri
		JE SetGoldName1
		JE SetGoldName2
		JE SetGoldName3
		JE SetGoldName4
		JE SetGoldName5
		JE SetGoldName6
		//Custom Wings2.5
		JE SetGoldName7
		JE SetGoldName8
		JE SetGoldName9

SetGoldNameOri:
		CMP AX,0x182B
		JE GoldColorAllow
SetGoldName1:
		CMP AX,0x18B4	//Wings of Demonic
		JE GoldColorAllow
SetGoldName2:
		CMP AX,0x18B5	//Wings of Heaven
		JE GoldColorAllow
SetGoldName3:
		CMP AX,0x18B6	//Wings of Blossom
		JE GoldColorAllow
SetGoldName4:
		CMP AX,0x18B7	//Wings of Sparks
		JE GoldColorAllow
SetGoldName5:
		CMP AX,0x18B8	//Wings of Raven
		JE GoldColorAllow
SetGoldName6:
		CMP AX,0x18B9	//Wings of Heaven
		JE GoldColorAllow
//Custom Wings2.5
SetGoldName7:
		CMP AX,0x18BA	//Wings of chaos	2.5
		JE GoldColorAllow
SetGoldName8:
		CMP AX,0x18BB	//Wings of chaos	2.5
		JE GoldColorAllow
SetGoldName9:
		CMP AX,0x18BC	//Wings of chaos	2.5
		JE GoldColorAllow
		JE ReturnGoldNormalLoad
//--------------
GoldColorAllow:
		MOV ESI,0x00590652
		JMP ESI
ReturnGoldNormalLoad:
		MOV ESI,0x00590650
		JMP ESI
	}
}

//--------------------------------------------------------------------------

void __declspec(naked) WingsShowDur() // -> 18 -> 00595DBE
{
	_asm
	{
		mov WingsShowDur_Pointer, ax 
	}
	// ----
	if( WingsShowDur_Pointer < ITEM(12, 0)
		|| (WingsShowDur_Pointer >= ITEM(12, 180) && WingsShowDur_Pointer <= ITEM(12, END_NEW_WING))
		|| (WingsShowDur_Pointer >= ITEM(13, 0) && WingsShowDur_Pointer < ITEM(14, 0)) )
	{
		_asm
		{
			mov WingsShowDur_Buff, 0x00595DF4
			jmp WingsShowDur_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsShowDur_Buff, 0x00595DD0
			jmp WingsShowDur_Buff
		}
	}
}
//--------------------------------------------------------------------------

void __declspec(naked) WingsHideExcellentStatusText() // -> 6 -> 00591594
{
	_asm
	{
		mov WingsHideExcellentStatusText_Pointer, ax
	}
	// ----
	if( WingsHideExcellentStatusText_Pointer == ITEM(13, 30) 
		|| (WingsHideExcellentStatusText_Pointer >= ITEM(12, 180) && WingsHideExcellentStatusText_Pointer <= ITEM(12, END_NEW_WING)) )
	{
		_asm
		{
			mov WingsHideExcellentStatusText_Buff, 0x0059159A
			jmp WingsHideExcellentStatusText_Buff
		}
	}
	else
	{
		_asm
		{
			mov WingsHideExcellentStatusText_Buff, 0x005915D4
			jmp WingsHideExcellentStatusText_Buff
		}
	}
}

void __declspec(naked) BowEffect()
{
	DWORD eItem;
	_asm
	{
		MOV EAX, DWORD PTR SS:[EBP-0x3AC]
		MOV eItem, EAX

		CMP eItem, 0x0B5A	//Original Item: Air Lyn Bow
		JE AddEffect
		JE AddEffect2
		JE AddEffect3
		JE AddEffect4
		JE AddEffect5
		CMP eItem, 0x0B59	//Dark Stinger Bow
		JE AddEffect
		JE AddEffect2
		JE AddEffect3
		JE AddEffect4
		JE AddEffect5
		CMP eItem, 0x356
		JE AddEffect2
		JE AddEffect3

		JMP Continue1
		JMP Continue2
Continue1:
		MOV ESI, 0x004E9FF0
		JMP ESI
Continue2:
		MOV ESI, 0x004E9FE4
		JMP ESI
AddEffect:
		MOV ESI, 0x004F07A3
		JMP ESI
AddEffect2:
		MOV ESI, 0x004F07A5
		JMP ESI
AddEffect3:
		MOV ESI, 0x004F0830
		JMP ESI
AddEffect4:
		MOV ESI, 0x004F0832
		JMP ESI
AddEffect5:
		MOV ESI, 0x004F0663
		JMP ESI
	}
}

void InitBowEffect()
{
	//Hook Bow Effect
	memset((int*)0x004E9FE6,0x90,9);
	WriteJmp(0x004E9FE6,(DWORD)&BowEffect);
	memset((int*)0x004E9FDA,0x90,9);
	WriteJmp(0x004E9FDA,(DWORD)&BowEffect);
}

void InitSetItemSpecialStat()
{
	SetHook((LPVOID)gSetItemSpecialStat, (LPVOID)oSetItemSpecialStat, ASM::CALL);
}

void InitWingsAddLuckOption()
{
	SetNop(0x0050B8CD, 8);
	WriteJmp(0x0050B8CD, (DWORD)&WingsAddLuckOption);
}

void InitWingsAddExcellentStatus()
{
	SetNop(0x0050B688, 12);
	WriteJmp(0x0050B688, (DWORD)&WingsAddExcellentStatus);
}

void InitWingsShowAdditionals()
{
	SetNop(0x00595265, 29);
	WriteJmp(0x00595265, (DWORD)&WingsShowAdditionals);
}

//void InitSmokeEffect()
//{
//	SetNop(HDK_SET_ITEM_EFFECT, 12);
//	WriteJmp(HDK_SET_ITEM_EFFECT, (DWORD)&SetItemEffect);
//
//	SetNop(HDK_SET_COLOR_EFFECT, 46);
//	WriteJmp(HDK_SET_COLOR_EFFECT, (DWORD)&SetColorEffect);
//}


void WingsAddCharSetLoad()
{
	SetNop(0x004FE263, 57);
	WriteJmp(0x004FE263, (DWORD)&WingsAddCharSet);
}


void ItemsEffectsLoad()
{
	SetNop(0x004F2C3B, 16);
	WriteJmp(0x004F2C3B, (DWORD)&ItemsAddSpecialEffect);
}

void InitInvEffect()
{
	SetNop(0x005CEE35, 12);
	WriteJmp(0x005CEE35, (DWORD)&WingsSetInvisiableEffect);
}


void InitWings28Option()
{
	SetNop(0x0050C453, 199);
	WriteJmp(0x0050C453, (DWORD)&WingsAdd28Option);
}


void InitWingsProps()
{
	SetNop(0x005D22A3, 1);
	WriteJmp(0x005D22A3, (DWORD)&WingsHideExcellentGlow);

	SetNop(0x005CDCC8, 19);
	WriteJmp(0x005CDCC8, (DWORD)&WingsDisableLevelShine);

	SetNop(0x0059064C, 1);
	WriteJmp(0x0059064C, (DWORD)&WingsSetGoldName);

	SetNop(0x00595DBE, 18);
	WriteJmp(0x00595DBE, (DWORD)&WingsShowDur);

	SetNop(0x00591594, 6);
	WriteJmp(0x00591594, (DWORD)&WingsHideExcellentStatusText);

	//006CEDFA -> kanturu wings

	SetByte((0x006CEE44),0xEB);
	//SetByte((0x006CEE3E+3),0x18);
	//006CEE3E

	
}

void NewWingsStart()
{
		WingsAddCharSetLoad();
		//InitSmokeEffect();
		ItemsEffectsLoad();
		InitInvEffect();
		InitWings28Option();
		InitWingsShowAdditionals();
		InitWingsAddExcellentStatus();
		InitWingsAddLuckOption();
		InitSetItemSpecialStat();
		InitWingsProps();
		InitBowEffect();
}
