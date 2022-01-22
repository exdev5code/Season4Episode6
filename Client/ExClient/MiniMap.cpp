#include "StdAfx.h"
#include "MiniMap.h"
#include "ToolKit.h"
#include "Configs.h"
#include "ConnectEx.h"
#include "Player.h"

void LoadImageJgpForMap(char* ImagePatch, DWORD PrintCode)
{
    _asm
    {
        Mov Edi, Main_LoadImageOzt
        Push 0x1
        Push 0x2900
        Push 0x2601
        Push 0x7B69
        Push ImagePatch
        Call Edi
        Add Esp,0x14
    }
}

int LoadMap(int Map)
{
    char FullMapName[200];
    sprintf(FullMapName,"World%d\\Map1.jpg",Map+1);
    ChangePath(FullMapName);
    LoadImageJgpForMap(FullMapName, 0x7B69);
    return Map;
}

void ChangePath(const char* Map)
{
    memset((DWORD*)0x8DC270,0,19);
    memcpy((DWORD*)0x8DC270,Map,17);
}

bool MapCheckerCore1(int Map)
{

    if( Map == 0 || Map == 1 || Map == 2 || Map == 3 || Map == 4 || Map==6 || Map == 7 || Map == 8 ||
        Map == 10 || Map == 24 || Map == 30 || Map == 33 || Map == 34 || Map == 37 || Map == 38 ||
        /* Map == 41 */ Map == 51 /*|| Map == 56*/ /*|| Map == 57 || Map == 63|| Map == 64*/)
    {
        return 1;
    }
    return 0;
}

char FullMapName[200];

void MapCheckerCore2(int Map)
{

    if( Map == 0 || Map == 1 || Map == 2 || Map == 3 || Map == 4 || Map==6 || Map == 7 || Map == 8 ||
        Map == 10 || Map == 24 || Map == 30 || Map == 33 || Map == 34 || Map == 37 || Map == 38 ||
        /* Map == 41 ||*/ Map == 51 /*|| Map == 56*/ /*|| Map == 57 || Map == 63|| Map == 64*/)
    {
        LoadMap(Map);
        _asm
        { 
            MOV EDI, 0x007747FF
            CALL EDI
            MOV ECX,EAX
            MOV EDI, 0x00774B8D
            CALL EDI
            MOV ECX,EAX
            MOV EDI, 0x006DE48E
            CALL EDI
        }
    }
    _asm
    {
        MOV EDI,0x0049029D
        PUSH Map
        CALL EDI
        POP EBP
    }
}

void InitMiniMap()
{
#if(DISABLE_MINIMAP==FALSE)
	if (Config.exMiniMap == 1)
	{
 		HookThis((DWORD)&MapCheckerCore1, 0x006DE41A);
		HookThis((DWORD)&MapCheckerCore2, 0x005E9409);
		 //Tab button press
		HookThis((DWORD)&MapCheckerCore1, 0x00730AB9);
	}
#endif
}
