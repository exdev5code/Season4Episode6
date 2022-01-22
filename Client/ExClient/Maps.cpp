#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_
#include "Utilits.h"
#include "ToolKit.h"

//===============================================================
//		Load New Map no Wellcome
//===============================================================
DWORD MAPNUMBER	= 0;
DWORD NEWMAP_JMP = 0x0045F722;
DWORD OLDMAP_JMP = 0x0045F731;

__declspec(naked)void NewMapLoader()
{
	_asm
	{
		MOV EAX, DWORD PTR DS:[0x8C5CF8]
		MOV MAPNUMBER, EAX
	}
	if(MAPNUMBER == 40)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 80)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 81)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 82)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 83)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 84)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 85)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 86)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 87)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 88)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 89)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else if(MAPNUMBER == 90)	//Original
	{
		_asm{JMP NEWMAP_JMP}
	}
	else
	{
		_asm{JMP OLDMAP_JMP}
	}
}

//===============================================================
//		Load Wellcome Map Name
//===============================================================
char * LorenMarket = "ExTeam/MapName/MapName_MarketRolen.tga";
char * BalgasBarrack = "ExTeam/MapName/BalgasBarrack.tga";

DWORD RET_WELLNAME	= 0x0045F6A1;
DWORD WELL_CALL1	= 0x0045FAD0;
DWORD WELL_CALL2	= 0x00409F10;

__declspec(naked)void NewWellcomeLoader()
{
	_asm
	{
		MOV DWORD PTR SS:[EBP-0x0D8],0x40
		PUSH 0x008C1BE0                     ; ASCII "Interface\duelarena.tga"
		LEA EDX,[EBP-0x0D8]
		PUSH EDX
		MOV ECX,DWORD PTR SS:[EBP-0x0DC]
		ADD ECX,4
		CALL WELL_CALL1
		MOV ECX,EAX
		CALL WELL_CALL2
		//----
		MOV DWORD PTR SS:[EBP-0x0D8],0x4F
		PUSH LorenMarket                    
		LEA EDX,[EBP-0x0D8]
		PUSH EDX
		MOV ECX,DWORD PTR SS:[EBP-0x0DC]
		ADD ECX,4
		CALL WELL_CALL1
		MOV ECX,EAX
		CALL WELL_CALL2
		//----
		MOV DWORD PTR SS:[EBP-0x0D8],0x50
		PUSH BalgasBarrack                    
		LEA EDX,[EBP-0x0D8]
		PUSH EDX
		MOV ECX,DWORD PTR SS:[EBP-0x0DC]
		ADD ECX,4
		CALL WELL_CALL1
		MOV ECX,EAX
		CALL WELL_CALL2

		MOV ESP,EBP
		POP EBP
		RETN
	}
}

//===============================================================
//		Fix Effect Cub
//===============================================================
DWORD MAP = 0;
DWORD CUB_FIX_ON	 = 0x007BEF63;
DWORD CUB_FIX_ST     = 0x007BEF3D;// 0x007BF0B6;
//DWORD CALL_MAP_CUBE	 = 0x007BEEBF;

_declspec(naked) void FixEffectCub()
{
	_asm
	{
		MOV EAX, DWORD PTR DS:[0x8C5CF8]
		MOV MAP, EAX
	}

	switch(MAP)
	{
	case 79:
	case 41:
	//case 62:
	case 80:
	case 81:
		_asm
		{
			//CALL CALL_MAP_CUBE
			JMP CUB_FIX_ON
		}
	}

	//if(MAP == 79)
	//{
	//	_asm{JMP CUB_FIX_ON}
	//}
	//else if(MAP == 41)
	//{
	//	_asm{JMP CUB_FIX_ON}
	//}	
	//else if(MAP == 62)
	//{
	//	_asm{JMP CUB_FIX_ON}
	//}
	//else if(MAP == 80)
	//{
	//	_asm{JMP CUB_FIX_ON}
	//}	
	//else
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x14],ECX
			MOV ECX,DWORD PTR SS:[EBP-0x14]
			JMP CUB_FIX_ST
		}
	}
}

//===============================================================
//		Added Effect to Map
//===============================================================
DWORD MAP_EFFECT = 0;
DWORD EFFECT_ON  = 0x007BF166;
DWORD EFFECT_OFF = 0x007BF140;

_declspec(naked) void AddedEffect()
{
	_asm
	{
		MOV EAX, DWORD PTR DS:[0x8C5CF8]
		MOV MAP_EFFECT, EAX
	}

	if(MAP_EFFECT == 41)
	{
		_asm{JMP EFFECT_ON}
	}	
	else if(MAP_EFFECT == 62)
	{
		_asm{JMP EFFECT_ON}
	}	
	else if(MAP_EFFECT == 80)
	{
		_asm{JMP EFFECT_ON}
	}	
	else if(MAP_EFFECT == 81)
	{
		_asm{JMP EFFECT_ON}
	}	
	else
	{
		_asm
		{
			MOV DWORD PTR SS:[EBP-0x28],ECX
			MOV ECX,DWORD PTR SS:[EBP-0x28]

			JMP EFFECT_OFF
		}
	}
}

//===============================================================
//		Added Effect fakel
//===============================================================
DWORD MAP_FACEL = 0;
DWORD FACEL_ON  = 0x007ECDFB;
DWORD FACEL_OFF = 0x007ECDEB;
DWORD FACEL_MAP_FUN = 0x007ECA76;

_declspec(naked)void MapEffectFacel()
{
	_asm
	{
		MOV EAX, DWORD PTR DS:[0x8C5CF8]
		MOV MAP_FACEL, EAX
	}

	if(MAP_FACEL == 79)
	{
		_asm{JMP FACEL_ON}
	}
	else
	{
		_asm
		{
			CALL FACEL_MAP_FUN
			JMP FACEL_OFF
		}
	}
}

//===============================================================
//		Party Map Name
//===============================================================
DWORD PMAP = 0;
DWORD TEXTLINE = 0;
DWORD PFUNCTION = 0x00402FF0;
DWORD PRET = 0x005A4BDC;
DWORD ELSEJMP = 0x005A49C7;

_declspec(naked)void PartyMapName()
{
	_asm
	{
		MOV PMAP,ESI
	}

	if(PMAP == 0x3A)
	{
		TEXTLINE = 740;
	}
	else if(PMAP == 79)
	{
		TEXTLINE = 2750;
	}
	else if(PMAP == 80)
	{
		TEXTLINE = 2751;
	}
	else
	{
		_asm{JMP ELSEJMP}
	}

	_asm
	{
		PUSH TEXTLINE                                 ; /Arg1 = 740
		MOV ECX,0x07AAD828                  ; |
		CALL PFUNCTION                            ; \Main.00402FF0
		JMP PRET
	}
}

void InitMaps()
{
	//SetNop(0x0045F719,16);
	WriteJmp(0x0045F719, (DWORD)&NewMapLoader);

	//SetNop(0x0045F719,16);
	WriteJmp(0x0045F676, (DWORD)&NewWellcomeLoader);

	//SetNop(0x007BEF37,6);
	WriteJmp(0x007BEF37, (DWORD)&FixEffectCub);//0x007BEF3D

	////SetNop(0x007BF13A,6);
	WriteJmp(0x007BF13A, (DWORD)&AddedEffect);

	//SetNop(0x007ECDE6,5);
	WriteJmp(0x007ECDE6, (DWORD)&MapEffectFacel);

	WriteJmp(0x005A49AE,(DWORD)&PartyMapName);
}

#endif