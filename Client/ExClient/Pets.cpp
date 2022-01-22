#include "StdAfx.h"

#ifdef _PET_CUSTOM_
#include "Utilits.h"
#include "Items.h"
#include "ToolKit.h"

bool bLoot;
DWORD dwPointer;

__declspec(naked) void RudolphFuck()
{
	bLoot = false;
// ----
	_asm
	{
		MOV EDX,DWORD PTR SS:[EBP-0x8]
		IMUL EDX,EDX,0x278
		MOVSX EAX,WORD PTR DS:[EDX+0x7B46D7A]
		MOV dwPointer,EAX
	}
// ----

	if ( dwPointer == ITEMGET(14,15) ||	//Zen
		 dwPointer == ITEMGET(12,15) ||	//Chaos
		 dwPointer == ITEMGET(14,13) || //Bless
		 dwPointer == ITEMGET(14,14) || //Soul
		 dwPointer == ITEMGET(14,22) || //Creation
		 dwPointer == ITEMGET(14,31) || //Guardian
		 dwPointer == ITEMGET(14,11) || //Box
		 dwPointer == ITEMGET(14,41) || //Gem
		 dwPointer == ITEMGET(14,16) )  //Life
	{
		bLoot = true;
	}
	else
	{
		bLoot = false;
	}
// ----
	if ( bLoot ) // Подбираем предмет если та самая
	{
		_asm
		{
			mov esi, 0x00812601
			jmp esi
		}
	}
	else // Уходим обратно если на полу не та вещь
	{
		_asm
		{
			mov esi, 0x00812541 // Автоподбор
			jmp esi
		}
	}
}


void StartNewCustomPet()
{
	SetNop(0x008125E5,17);
	WriteJmp(0x008125E5, (DWORD)&RudolphFuck);
}
#endif