#include "StdAfx.h"
#include "Fix.h"
#include "ToolKit.h"
#include "Configs.h"
#include "Interface.h"
#include "TMemory.h"
#include "3DCamera.h"

#if(FULL_HD == 1)

#define oGameLoad				0x005FA4D0						
#define pGameLoad				((int(__cdecl*)()) 0x005F921D)	
#define pGameResolutionMode		*(int*)0x809F460				
#define pWinWidth				*(int*)0x8D65C8					
#define pWinHeight				*(int*)0x8D65CC					
#define pWinFontHeight			*(int*)0x7AB3538				
#define pWinWidthReal			*(float*)0x8F5C8C				
#define pWinHeightReal			*(float*)0x8F5C90				

#define oMoveListInit1			0x007512CC						
#define oMoveListInit2			0x0075316C						
#define pMoveListInit			((void(__thiscall*)(LPVOID This, int Arg1, int Arg2)) 0x00751320)

int GameLoad()
{
	pGameLoad();

	switch(pGameResolutionMode)
	{
	case 5:
		pWinWidth		= 1280;
		pWinHeight		= 720;
		break;
	case 6:
		pWinWidth		= 1280;
		pWinHeight		= 800;
		break;
	case 7:
		pWinWidth		= 1366;
		pWinHeight		= 768;
		break;
	case 8:
		pWinWidth		= 1440;
		pWinHeight		= 900;
		break;
	case 9:
		pWinWidth		= 1680;
		pWinHeight		= 1050;
		break;
	case 10:
		pWinWidth		= 1920;
		pWinHeight		= 1080;
		break;
	case 11:
		pWinWidth		= 1920;
		pWinHeight		= 1200;
		break;

	}

	pWinFontHeight	= 15;
	pWinWidthReal	= (float)pWinWidth / MAX_WIN_WIDTH;
	pWinHeightReal	= (float)pWinHeight / MAX_WIN_HEIGHT;

	if(pGameResolutionMode >= 5)
	{
		float Aux = abs(GetMemBuffer((DWORD*)CAMERA_POSZ) - 150) * 3;
		UnProtect((DWORD*)(float*)0x0088BB18, 1190.0f + Aux + 3000.0f);
		UnProtect((DWORD*)(float*)0x0088BB18, 2400.0f + Aux + 3000.0f);
		UnProtect((DWORD*)(float*)0x0088BB4C, 3000.0f + Aux + 1500.0f);
	}

	return 1;
}

static void __fastcall MoveListInit(LPVOID This, LPVOID EDX, int Arg1, int Arg2)
{
	int TempWidth = pWinWidth;
	pWinWidth = 1280;
	pMoveListInit(This, Arg1, Arg2);
	pWinWidth = TempWidth;
}

#endif

void BugFix() 
{
#if(FULL_HD == 1 )
	SetOp((LPVOID)oGameLoad, (LPVOID)GameLoad, ASM::CALL);
	SetOp((LPVOID)oMoveListInit1, (LPVOID)MoveListInit, ASM::CALL);
	SetOp((LPVOID)oMoveListInit2, (LPVOID)MoveListInit, ASM::CALL);	
#endif

	if(Config.exCastleSkills)
	{
		//Castle siege skills
		*(BYTE*)(0x0057F0A7+1)  = 0x2B;
		*(BYTE*)(0x0057F0AC+1)  = 0x26;
		*(BYTE*)(0x0057F0B1+1)  = 0x21;
		*(BYTE*)(0x0057F0B6+1)  = 0x1C;
		*(BYTE*)(0x0057F0BB+1)  = 0x17;
		*(BYTE*)(0x0059A9B5+2)  = 0x00;
		*(BYTE*)(0x0059A9BB+2)  = 0x00;
		*(BYTE*)(0x0059A9C1+2)  = 0x00;
		*(BYTE*)(0x0059A9C7+2)  = 0x00;
		*(BYTE*)(0x0059A9CD+2)  = 0x00;
		*(BYTE*)(0x0059A9D3+2)  = 0x00;
		*(BYTE*)(0x00579D0F+1)  = 0x33;
		*(BYTE*)(0x00579D14+1)  = 0x2E;
		*(BYTE*)(0x00579D19+1)  = 0x29;
		*(BYTE*)(0x00579D1E+1)  = 0x24;
		*(BYTE*)(0x00579D23+1)  = 0x1F;
		*(BYTE*)(0x00579D71+1)  = 0x33;
		*(BYTE*)(0x00579D76+1)  = 0x2E;
		*(BYTE*)(0x00579D7B+1)  = 0x29;
		*(BYTE*)(0x00579D80+1)  = 0x24;
		*(BYTE*)(0x00579D85+1)  = 0x1F;
		*(BYTE*)(0x00492A98+3)  = 0x01;
		*(BYTE*)(0x00579D28)    = 0xEB;
		*(BYTE*)(0x0057F0C0)    = 0xEB;
		*(BYTE*)(0x00579D8A)    = 0xEB; 
	}
	
	// 1.03k
	BYTE Font[3] = { 0x01, 0x00, 0x00 }; 
	memcpy((int*)0x008C2ECC, Font, sizeof(Font));

	BYTE DecryptLog[5] = { 0x90, 0x90, 0x90, 0x90, 0x90 };
	memcpy((int*)0x006BD88D, DecryptLog, sizeof(DecryptLog)); memcpy((int*)0x006BDAA0, DecryptLog, sizeof(DecryptLog));

	BYTE WarpMenu[2] = { 0xEB, 0x27 };	 
	memcpy((int*)0x0075104B, WarpMenu, sizeof(WarpMenu));

	/* Draw frame Fix */
	// Jmp to Sleep
	*(BYTE*)(0x006020C4)     = 0xE9;
	*(BYTE*)(0x006020C4 + 1) = 0xFA;
	*(BYTE*)(0x006020C4 + 2) = 0x6E;
	*(BYTE*)(0x006020C4 + 3) = 0x28;
	*(BYTE*)(0x006020C4 + 4) = 0x00;
	*(BYTE*)(0x006020C4 + 5) = 0x90;
	*(BYTE*)(0x006020C4 + 6) = 0x90;

	// Sleep and jmp to Call Ebx
	*(BYTE*)(0x00888FC3)      = 0x6A;
	*(BYTE*)(0x00888FC3 + 1)  = 0x01;
	*(BYTE*)(0x00888FC3 + 2)  = 0xFF;
	*(BYTE*)(0x00888FC3 + 3)  = 0x15;
	*(BYTE*)(0x00888FC3 + 4)  = 0x78;
	*(BYTE*)(0x00888FC3 + 5)  = 0x91;
	*(BYTE*)(0x00888FC3 + 6)  = 0x88;
	*(BYTE*)(0x00888FC3 + 7)  = 0x00;
	*(BYTE*)(0x00888FC3 + 8)  = 0xE9;
	*(BYTE*)(0x00888FC3 + 9)  = 0xE7;
	*(BYTE*)(0x00888FC3 + 10) = 0x90;
	*(BYTE*)(0x00888FC3 + 11) = 0xD7;
	*(BYTE*)(0x00888FC3 + 12) = 0xFF;
	*(BYTE*)(0x00888FC3 + 13) = 0x90; 

	// Redirect to MU.exe
	//005FA1DF   . /EB 55         JMP SHORT mainClea.005FA236
	//*(BYTE*)(0x005FA1DF) = 0x75;
	//*(BYTE*)(0x005FA1E0) = 0x55;

	// Multi Window
	//005FA130   . /75 3C         JNZ SHORT MuGroza.005FA16E 
	//*(BYTE*)(0x005FA130) = 0x75; // EB
 
	// Sword slot limit
	//*(BYTE*)(0x005D81DD+3) = 0x7F; 
	//// Axe slot limit
	//*(BYTE*)(0x005D82B0+3) = 0x7F; 
	//// Mace slot limit
	//*(BYTE*)(0x005D82ED+3) = 0x7F; 
	//// Mace slot limit
	//*(BYTE*)(0x005D8343+3) = 0x7F; 
	//// Spear slot limit
	//*(BYTE*)(0x005D8399+3) = 0x7F; 
	//// Shield slot limit
	//*(BYTE*)(0x005D83EF+3) = 0x7F; 
	//// Staff slot limit
	//*(BYTE*)(0x005D845E+3) = 0x7F; 
	//// Staff slot limit
	//*(BYTE*)(0x005D84E6+3) = 0x7F; 
	//// Bow slot limit
	//*(BYTE*)(0x005D8523+3) = 0x7F; 
	//// Crossbow slot limit
	//*(BYTE*)(0x005D8560+3) = 0x7F;
	//// Helm slot limit
	//*(BYTE*)(0x005D6C8C+3) = 0x7F; 
	//// Armor, Pant, Glove, Boot slot limit
	//*(BYTE*)(0x005D6CD6+3) = 0x7F; 

	//// Heml, Armor, Pant, Glove, Boot slot limit
	//*(BYTE*)(0x005D626C+3) = 0x7F; 
	//// 005D626C |> 837D F0 0A      CMP DWORD PTR SS:[EBP-10],0A

	//// Shield
	//*(BYTE*)(0x005D83EF+3) = 0x7F;
	////005D83EF  |> 837D E4 0F      CMP DWORD PTR SS:[EBP-1C],0F

	//*(BYTE*)(0x005F7DDA+4) = 0x26; // Max tex limit
	//*(BYTE*)(0x005D80BE+3) = 0x7F; // Helm tex limit
	//*(BYTE*)(0x005D8109+3) = 0x7F; // Armor, Pant, Glove, Boot tex limit 	
	
	//005DA10A  |> \837D FC 04     CMP [LOCAL.1],4
	//005DA10E  |.  7D 50         |JGE SHORT main.005DA160
	//005DA110  |.  837D FC 03    |CMP [LOCAL.1],3 
	
	//*(BYTE*)(0x005DA10A+3) = 0x09;
	//*(BYTE*)(0x005DA110+3) = 0x7F;

	//// 005DA1EA  |> \837D FC 04     CMP [LOCAL.1],4
	//*(BYTE*)(0x005DA1EA+3) = 0x35;
	//// 005DA227  |> \837D FC 04     CMP [LOCAL.1],4
	//*(BYTE*)(0x005DA227+3) = 0x15;
	//// 005DA29F  |> \837D FC 2B     CMP [LOCAL.1],2B
	//*(BYTE*)(0x005DA29F+3) = 0x39;
	//// 005DA2DC  |> \837D FC 17     CMP [LOCAL.1],17
	////*(BYTE*)(0x005DA2DC+3) = 0x35;
	//// 005DA319  |> \837D FC 09     CMP [LOCAL.1],9
	//*(BYTE*)(0x005DA319+3) = 0x35;
	//// 005DA4BD  |> \837D FC 02     CMP [LOCAL.1],2
	//*(BYTE*)(0x005DA4BD+3) = 0x09;
	//// 005DA590  |> \837D FC 04     CMP [LOCAL.1],4
	//*(BYTE*)(0x005DA590+3) = 0x09;
	//// 005DA5EB  |> \837D FC 02     CMP [LOCAL.1],2
	//*(BYTE*)(0x005DA5EB+3) = 0x09;
	//// 005DA753  |> \837D FC 11     CMP [LOCAL.1],11
	////*(BYTE*)(0x005DA753+3) = 0x27;
	//// 005DA8F1  |> \837D FC 14     CMP [LOCAL.1],14
	//*(BYTE*)(0x005DA8F1+3) = 0x25;
	//// 005DA92E  |> \837D FC 1C     CMP [LOCAL.1],1C
	//*(BYTE*)(0x005DA92E+3) = 0x25;
	//// 005DA96B  |> \837D FC 05     CMP [LOCAL.1],5
	//*(BYTE*)(0x005DA96B+3) = 0x09;
	//// 005DA9A7  |> \837D FC 02     CMP [LOCAL.1],2
	//*(BYTE*)(0x005DA9A7+3) = 0x09;
	//// 005DAA02  |> \837D FC 15     CMP [LOCAL.1],15
	//*(BYTE*)(0x005DAA02+3) = 0x25;
	//// 005DAA3F  |> \837D FC 04     CMP [LOCAL.1],4
	//*(BYTE*)(0x005DAA3F+3) = 0x09;
	//// 005DAB6B  |> \837D FC 13     CMP [LOCAL.1],13
	//*(BYTE*)(0x005DAB6B+3) = 0x25;
	//// 005DACD4  |> \837D FC 03     CMP [LOCAL.1],3
	//*(BYTE*)(0x005DACD4+3) = 0x09;
	//// 005DAD11  |> \837D FC 02     CMP [LOCAL.1],2
	//*(BYTE*)(0x005DAD11+3) = 0x09;
	//// 005DAD4D  |> \837D FC 06     CMP [LOCAL.1],6
	//*(BYTE*)(0x005DAD4D+3) = 0x09;
	//// 005DAD8A  |> \837D FC 02     CMP [LOCAL.1],2
	//*(BYTE*)(0x005DAD8A+3) = 0x09;
	//// 005DB32B  |> \837D FC 05     CMP [LOCAL.1],5
	//*(BYTE*)(0x005DA8F1+3) = 0x09; 

	//Multi Client
//#if __LOCAL__||__ExGames__||__DoubleDamage__||__MuRain__
//	*(BYTE*)(0x005FA14C) = 0xEB; 
//#endif
	*(BYTE*)(0x005FA14C) = 0xEB; 
	//Font Fix
#if __DoubleDamage__
	*(BYTE*)(0x008C2ECC) = 0x01;
#endif
} 


