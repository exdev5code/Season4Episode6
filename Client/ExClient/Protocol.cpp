#include "stdafx.h"
#include "Protocol.h"
#include "GameCharacter.h"
#include "MonsterHPBar.h"
#include "Utilits.h"
#include "ToolKit.h"
#include "Console.h"
#include "Player.h"
#include "RageSystem.h"
#include "ConnectEx.h"
#include "User.h"
#include "JewelsBank.h"
#include "AntiCheatPlus.h"

//#ifdef _SPEED_FIX_
DWORD MAGIC		= NULL;
//#endif
//#ifdef _VISUAL_FIX_
DWORD DAMAGE	= NULL;
DWORD SHIELD	= NULL;
DWORD HP		= NULL;
DWORD MAX_HP	= NULL;
DWORD SD		= NULL;
DWORD MAX_SD	= NULL;
DWORD MP		= NULL;
DWORD MAX_MP	= NULL;
DWORD AG		= NULL;
DWORD MAX_AG	= NULL;
DWORD EXP		= NULL;
DWORD UP_POINT	= NULL;
BOOL PLAYER_KILL = TRUE;
//#endif

BYTE byXorFilter[32];


void DataSend(LPBYTE Data, int Size)
{
	//Console.ConsoleOutput(GREEN," DataSend");

		//byXorFilter[0]	= 0xf2;
		//byXorFilter[1]	= 0xa5;
		//byXorFilter[2]	= 0xb4;
		//byXorFilter[3]	= 0x85;
		//byXorFilter[4]	= 0xf5;
		//byXorFilter[5]	= 0xa7;
		//byXorFilter[6]	= 0xd9;
		//byXorFilter[7]	= 0x38;
		//byXorFilter[8]	= 0x92;
		//byXorFilter[9]	= 0x01;
		//byXorFilter[10]	= 0xee;
		//byXorFilter[11]	= 0x11;
		//byXorFilter[12]	= 0xd1;
		//byXorFilter[13]	= 0x96;
		//byXorFilter[14]	= 0xfe;
		//byXorFilter[15]	= 0xfa;
		//byXorFilter[16]	= 0xa5;
		//byXorFilter[17]	= 0xda;
		//byXorFilter[18]	= 0x2f;
		//byXorFilter[19]	= 0xd1;
		//byXorFilter[20]	= 0x44;
		//byXorFilter[21]	= 0xf6;
		//byXorFilter[22]	= 0x4c;
		//byXorFilter[23]	= 0x20;
		//byXorFilter[24]	= 0x91;
		//byXorFilter[25]	= 0x74;
		//byXorFilter[26]	= 0xdc;
		//byXorFilter[27]	= 0x1d;
		//byXorFilter[28]	= 0x37;
		//byXorFilter[29]	= 0xbe;
		//byXorFilter[30]	= 0xaf;
		//byXorFilter[31]	= 0x6b;

		byXorFilter[0] = 0xE7;
		byXorFilter[1] = 0x6D;
		byXorFilter[2] = 0x3A;
		byXorFilter[3] = 0x89;
		byXorFilter[4] = 0xBC;
		byXorFilter[5] = 0xB2;
		byXorFilter[6] = 0x9F;
		byXorFilter[7] = 0x73;
		byXorFilter[8] = 0x23;
		byXorFilter[9] = 0xA8;
		byXorFilter[10] = 0xFE;
		byXorFilter[11] = 0xB6;
		byXorFilter[12] = 0x49;
		byXorFilter[13] = 0x5D;
		byXorFilter[14] = 0x39;
		byXorFilter[15] = 0x5D;
		byXorFilter[16] = 0x8A;
		byXorFilter[17] = 0xCB;
		byXorFilter[18] = 0x63;
		byXorFilter[19] = 0x8D;
		byXorFilter[20] = 0xEA;
		byXorFilter[21] = 0x7D;
		byXorFilter[22] = 0x2B;
		byXorFilter[23] = 0x5F;
		byXorFilter[24] = 0xC3;
		byXorFilter[25] = 0xB1;
		byXorFilter[26] = 0xE9;
		byXorFilter[27] = 0x83;
		byXorFilter[28] = 0x29;
		byXorFilter[29] = 0x51;
		byXorFilter[30] = 0xE8;
		byXorFilter[31] = 0x56;

	int StartPos = 0;
	// ----
	if( Data[0] == 0xC1 || Data[0] == 0xC3 )
	{
		StartPos = 3;
	}
	else if( Data[0] == 0xC2 || Data[0] == 0xC4 )
	{
		StartPos = 4;
	}
	// ----
	for( int i = StartPos; i < Size; i++ )
	{
		Data[i] ^= Data[i - 1] ^ byXorFilter[i%32];
	}
	// ----
	send(pActiveSocket, (char*)Data, Size, 0);
	//pDataSend(pActiveSocket,Data,Size);


}

void __cdecl cMU_ProtocolCore(int index, PBYTE lpMsg, int len, int flags)
{
#if(exRECONNECT)
	if( lpMsg[2] == 0xF4 && lpMsg[3] == 3)
	{
		PMSG_ANS_SERVER_INFO * lpDef = (PMSG_ANS_SERVER_INFO *)lpMsg;
		sprintf(gConnectEx.m_GSIP, "%s", lpDef->Ip);
		gConnectEx.m_GSPort = lpDef->Port;
	}
#endif

	switch (index)
	{
		case 0xF3:
			{
				switch(lpMsg[3])
				{
					case 0x03: //Character selected (join map)
						{
#ifdef exRECONNECT
							gConnectEx.RestoreGame();
#endif
#ifdef _VISUAL_FIX_
							PMSG_CHARMAPJOINRESULT * Recv = (PMSG_CHARMAPJOINRESULT*)lpMsg;
							UP_POINT = Recv->UpPoint;
							PLAYER_KILL = FALSE;
#endif
							Mob_HP_Bar.isDraw = false;//false
						}
						break;
					case 0x04: //Respawn
						{
							Mob_HP_Bar.isDraw = false;//false
#ifdef _VISUAL_FIX_
							PLAYER_KILL = FALSE;
							HP = MAX_HP;
							SD = MAX_SD;
#endif
						}
						break;
					case 0x05:
						{
#ifdef _VISUAL_FIX_
							PMSG_LEVELUP * Recv = (PMSG_LEVELUP*)lpMsg;
							UP_POINT = Recv->UpPoint;
#endif
						}
						break;
					case 0x06:
						{
#ifdef _VISUAL_FIX_
							PMSG_LVPOINTADDRESULT * Recv = (PMSG_LVPOINTADDRESULT*)lpMsg;
							if(Recv->ResultType != 0)
							{
								UP_POINT--;
							}
#endif
						}
						break;
				}	
			}
			break;
		case 0x1E:
			{
#ifdef _SPEED_FIX_
				PMSG_DURATION_MAGIC_SEND * Recv = (PMSG_DURATION_MAGIC_SEND*)lpMsg;
				MAGIC = MAKE_NUMBERW(Recv->MagicNumberH,Recv->MagicNumberL);
#endif
			}
			break;
		case MU_DAMAGE: //Damage
			{
				WORD tIndex = ((lpMsg[3] << 8) + lpMsg[4]) & 0x7FFF;
#ifdef _VISUAL_FIX_
				memcpy(&DAMAGE, &lpMsg[20], 4);
				memcpy(&SHIELD, &lpMsg[24], 4);

#if(NEW_HP_BAR)
				for(int n = 0; n < MAX_VIEWPORT;n++)
				{
					if(tIndex == gObjUser.ExViewe[n].aIndex)
					{
#ifdef exDEBUG_CODE
						//gConsole.Output(cGREEN,"SD: %d MaxSD: %d",Recv->SD,Recv->MaxSD);
#endif
			
						//gObjUser.ExViewe[n].aIndex = tIndex;
						//gObjUser.ExViewe[n].Life = this->HP;
						//gObjUser.ExViewe[n].MaxLife = this->MaxHP;
						//gObjUser.ExViewe[n].SD = Recv->SD;
						//gObjUser.ExViewe[n].MaxSD = Recv->MaxSD;

						gObjUser.ExViewe[n].aIndex = tIndex;
						gObjUser.ExViewe[n].Life -= DAMAGE;
						if(gObjUser.ExViewe[n].Life < 0)
						{
							gObjUser.ExViewe[n].Life = 0;
						}
						//gObjUser.ExViewe[n].MaxLife = this->MaxHP;
						gObjUser.ExViewe[n].SD -= SHIELD;
						if(gObjUser.ExViewe[n].SD < 0)
						{
							gObjUser.ExViewe[n].SD = 0;
						}
						//gObjUser.ExViewe[n].MaxSD = Recv->MaxSD;

						break;
					}
				}
#endif
#endif
				
				if (tIndex == *GameIndex) 
				{
#ifdef _VISUAL_FIX_
					HP -= DAMAGE;	//TEST DeBug
					SD -= SHIELD;
					if(0>HP)HP=0;				
#endif
				}
				else 
				{
					if (lpMsg[1] > 10)
					{
						int Life, MaxLife;
						memcpy(&Life, &lpMsg[12], 4);
						memcpy(&MaxLife, &lpMsg[16], 4);
//						Console.ConsoleOutput(GREEN," Life: %d | MaxLife: %d",Life,MaxLife);
						Mob_HP_Bar.SetupMob(Life, MaxLife, tIndex);	//Mob_HP_Bar.SetupMob(Life, MaxLife, tIndex);
					}
				}
			}
			break;
		case 0x14: //Destroy viewport chars
			{
				for (unsigned int i=0; i<lpMsg[3]; ++i)
				{
					WORD tIndex = (lpMsg[4 + (i*2)] << 8) + lpMsg[5 + (i*2)];
					if (tIndex == Mob_HP_Bar.aIndex)
					{
						Mob_HP_Bar.isDraw = false;	//false
						break;
					}
				}
			}
			break;
		case 0x17: //Killed object
			{
				WORD tIndex = (lpMsg[3] << 8) + lpMsg[4];

#if(NEW_HP_BAR)
				for(int n = 0; n < MAX_VIEWPORT;n++)
				{
					if(tIndex == gObjUser.ExViewe[n].aIndex)
					{
						gObjUser.ExViewe[n].aIndex = -1;
						gObjUser.ExViewe[n].Live = 0;
						break;
					}
				}
#endif
#ifdef _VISUAL_FIX_
				if(tIndex == *GameIndex)
				{
					HP = 0;
					SD = 0;
					PLAYER_KILL = TRUE;
				}
#endif
				if ((tIndex == Mob_HP_Bar.aIndex) || (tIndex == *GameIndex))
				{
					Mob_HP_Bar.isDraw = false;	//false
				}
			}
			break;
		case 0x1C: //Teleport
			{
				Mob_HP_Bar.isDraw = false;	// false
			}
			break;
		case 0x26: //Recv HP,SD
			{
#ifdef _VISUAL_FIX_
				PMSG_REFILL * Recv = (PMSG_REFILL*)lpMsg;
				if(lpMsg[3] == 0xFE)//Max Life
				{
					MAX_HP = Recv->Life;
					MAX_SD = Recv->Shield;
				}
				if(lpMsg[3] == 0xFF)//Life
				{
					HP = Recv->Life;
					SD = Recv->Shield;
				}

				if(HP > MAX_HP)
				{
					HP = MAX_HP;
				}
				if(SD > MAX_SD)
				{
					SD = MAX_SD;
				}

				if(0 > HP)
				{
					HP = MAX_HP;
				}
				if(0 > SD)
				{
					SD = MAX_SD;
				}

				if(PLAYER_KILL == TRUE)
				{
					HP=0;
					SD=0;
				}
#endif
			}
			break;
		case 0x27:
			{
#ifdef _VISUAL_FIX_
				PMSG_MANASEND * Recv = (PMSG_MANASEND*)lpMsg;
				if(lpMsg[3] == 0xFE)	//Max Mana
				{
					MAX_MP = Recv->Mana;
					MAX_AG = Recv->BP;
				}
				if(lpMsg[3] == 0xFF)	//Mana
				{
					MP = Recv->Mana;
					AG = Recv->BP;
				}

				if(MP > MAX_MP)
				{
					MP = MAX_MP;
				}
				if(AG > MAX_AG)
				{
					AG = MAX_AG;
				}

				if(0 > MP)
				{
					MP = MAX_HP;
				}
				if(0 > AG)
				{
					AG = MAX_SD;
				}
#endif
			}
			break;
		case 0x16:
			{
#ifdef _VISUAL_FIX_
				PMSG_KILLPLAYER * Recv = (PMSG_KILLPLAYER*)lpMsg;
				EXP = Recv->Exp;
#endif
			}
			break;
		case 0xFB:
			{
				PMSG_DEFAULT2 * lpDef = (PMSG_DEFAULT2 *)lpMsg;

				switch ( lpDef->subcode )
				{
#ifdef _SYSTEM_OF_RAGE_
				case 0x00:
					gRageSystem.RecvConfig((sConfigStruct *) lpMsg);
					break;
				case 0x01:
					gRageSystem.RageRecv((ClickSend*)lpMsg);
					break;
				case 0x02:
					gRageSystem.RecvStart((sRageUserSend*) lpMsg);
					break;
				case 0x03:
					gRageSystem.RecvExp((RageExpSend *) lpMsg);
					break;
#endif
#ifdef exRECONNECT
				case 0xC:
					{
						gConnectEx.m_ConnectState = ConnectExType::OnForceDisconnect;
						gConnectEx.Disconnect();
					}
					break;
#endif
#if(_JEWELS_BANK_)
				case 14:
					{
						gJewelsBank.JewelsBankRecv((EXINFO_UPDATE*)lpMsg);
					}
					break;
#endif
#if(ANTI_CHEAT_PLUS==TRUE)
				case 0xFF:
					{
						g_AntiCheatPlus.GC_Recv(lpMsg);
					}
					break;
#endif
				}
			}
			break;
	}

	if(lpMsg[0] == 0xC2)
	{
		switch(BYTE(index))
		{
		case 0xFA:
			{
				NewExVieweport((CGExUserHpBar*)lpMsg);
			}
			break;
		}
	}
	DataRecv(index, lpMsg, len, flags);
}
void NewExVieweport(CGExUserHpBar * aRecv)
{
	ZeroMemory(gObjUser.ExViewe,sizeof(gObjUser.ExViewe));
	for(int n = 0; n < MAX_VIEWPORT;n++)
	{
		//Console.ConsoleOutput(GREEN,"aIndex: %d Life: %d, MaxLife: %d",aRecv->Vp[n].aIndex,aRecv->Vp[n].Life,aRecv->Vp[n].MaxLife);
		//gConsole.Output(cGREEN,"aIndex: %d Life: %d, MaxLife: %d",aRecv->Vp[n].aIndex,aRecv->Vp[n].Life,aRecv->Vp[n].MaxLife);
		if(aRecv->Vp[n].aIndex == -1) continue;

		gObjUser.ExViewe[n].aIndex = aRecv->Vp[n].aIndex;
		gObjUser.ExViewe[n].Life = aRecv->Vp[n].Life;
		gObjUser.ExViewe[n].MaxLife = aRecv->Vp[n].MaxLife;


		gObjUser.ExViewe[n].SD = aRecv->Vp[n].SD;
		gObjUser.ExViewe[n].MaxSD = aRecv->Vp[n].MaxSD;
		gObjUser.ExViewe[n].Level = aRecv->Vp[n].Level;
		gObjUser.ExViewe[n].Reset = aRecv->Vp[n].Reset;
		gObjUser.ExViewe[n].GrandReset = aRecv->Vp[n].GrandReset;
		gObjUser.ExViewe[n].Defence = aRecv->Vp[n].Defence;

		//gObjUser.ExViewe[n].Live = aRecv->Vp[n].Live;

		memcpy(gObjUser.ExViewe[n].Name,aRecv->Vp[n].Name,sizeof(gObjUser.ExViewe[n].Name));
	}
}

#ifdef _SPEED_FIX_
//===============================================================
//		Attack Speed
//===============================================================
DWORD ATTACK_RET = 0x004D5E55;
WORD CLASS = 0;
WORD STR_SPEED = 0;
WORD MAG_SPEED = 0;
__declspec(naked) void FixAttackSpeed()
{
	_asm
	{
		MOV EAX,DWORD PTR DS:[0x7AB351C]

		MOV CX,WORD PTR DS:[EAX+0xB]
		MOV CLASS,CX

		MOV CX,WORD PTR DS:[EAX+0x54]
		MOV STR_SPEED,CX

		MOV CX,WORD PTR DS:[EAX+0x60]
		MOV MAG_SPEED,CX
	}
	
	if( CLASS == DarkWizard || CLASS == SoulMaster || CLASS == GrandMaster )
	{
		if( MAGIC == SKILL_EVIL ||
			MAGIC == 445 ||
			MAGIC == 446 ||
			MAGIC == 447 ||
			MAGIC == 448 ||
			MAGIC == 449 ||
			MAGIC == SKILL_FLAME)
		{
			if(MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if(MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if(MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if(MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if(MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		else if(MAGIC == SKILL_INFERNO)
		{
			if(MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}
	}
	else if( CLASS == DarkKnight  || CLASS == BladeKnight || CLASS == BladeMaster  )
	{

	}
	else if( CLASS == Elf || CLASS == MuseElf || CLASS == HightElf )
	{
		if(MAGIC == SKILL_CROSSBOW ||
		   MAGIC == 490 ||
		   MAGIC == 491 ||
		   MAGIC == 492 ||
		   MAGIC == 493 ||
		   MAGIC == 494 )
		{
			if(STR_SPEED > 508 && STR_SPEED < 550)
			{
				STR_SPEED = 508;
			}
			else if (STR_SPEED > 799 && STR_SPEED < 1150)
			{
				STR_SPEED = 799;
			}
		}
	}
	else if( CLASS == MagicGladiator || CLASS == DuelMaster )
	{
		if( MAGIC == SKILL_EVIL ||
			MAGIC == 530 ||
			MAGIC == 531 ||
			MAGIC == 532 ||
			MAGIC == 533 ||
			MAGIC == 534 ||
			MAGIC == SKILL_FLAME )
		{
			if(MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if(MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if(MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if(MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if(MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		else if(MAGIC == SKILL_INFERNO)
		{
			if(MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}
	}
	else if( CLASS == DarkLord || CLASS == LordEmperor)
	{
		if(MAGIC == SKILL_FIRESCREAM ||
		   MAGIC == 525 ||
		   MAGIC == 526 ||
		   MAGIC == 527 ||
		   MAGIC == 528 ||
		   MAGIC == 529)
		{
			if(STR_SPEED > 249 && STR_SPEED < 264)
			{
				STR_SPEED = 249;
			}
			else if(STR_SPEED > 324 && STR_SPEED < 367)
			{
				STR_SPEED = 324;
			}
			else if(STR_SPEED > 449 && STR_SPEED < 575)
			{
				STR_SPEED = 449;
			}
			else if(STR_SPEED > 699 && STR_SPEED < 1200)
			{
				STR_SPEED = 699;
			}
			else if(STR_SPEED > 1449)
			{
				STR_SPEED = 1449;
			}
		}
	}

	_asm
	{
		MOV EAX,DWORD PTR DS:[0x7AB351C]
		XOR ECX,ECX
		MOV CX,WORD PTR DS:[STR_SPEED]
		MOV DWORD PTR SS:[EBP-0x14],ECX
		FILD DWORD PTR SS:[EBP-0x14]
		FMUL DWORD PTR DS:[0x88B700]               ; FLOAT 0.004000000
		FSTP DWORD PTR SS:[EBP-0x8]
		MOV EDX,DWORD PTR DS:[0x7AB351C]
		XOR EAX,EAX
		MOV AX,WORD PTR DS:[MAG_SPEED]
		MOV DWORD PTR SS:[EBP-0x18],EAX
		FILD DWORD PTR SS:[EBP-0x18]
		FMUL DWORD PTR DS:[0x88B700]               ; FLOAT 0.004000000
		FSTP DWORD PTR SS:[EBP-0x0C]
		MOV ECX,DWORD PTR DS:[0x7AB351C]
		XOR EDX,EDX
		MOV DX,WORD PTR DS:[MAG_SPEED]
		MOV DWORD PTR SS:[EBP-0x1C],EDX
		FILD DWORD PTR SS:[EBP-0x1C]
		FMUL DWORD PTR DS:[0x88B494]               ; FLOAT 0.002000000
		FSTP DWORD PTR SS:[EBP-0x4]
		JMP ATTACK_RET
	}
}
#endif

#ifdef _VISUAL_FIX_
//===============================================================
//		Attack HP
//===============================================================
DWORD DMG_FUNCTION = 0x006BA450;
DWORD RETURN_DMG_JMP = 0x0061A2A3;
__declspec(naked) void FixVisualDamageHP()
{
	_asm
	{
		PUSH 1
		MOV EDX,ESP
		ADD EDX,0x28
		PUSH EBP
		AND EAX,0x0000FFFF
		PUSH EDX
		MOV ESI,EDI
		ADD ESI,0x0FC
		PUSH DAMAGE	//EAX
		PUSH ESI                                 ; |Arg1
		CALL DMG_FUNCTION                        ; \Main.006BA450
		JMP RETURN_DMG_JMP
	}
}

//===============================================================
//		Attack SD
//===============================================================
DWORD RETURN_SD_JMP = 0x0061A303;
__declspec(naked) void FixVisualDamageSD()
{
	_asm
	{
		PUSH 1                                   ; /Arg5 = 1
		MOV ECX,ESP
		ADD ECX,0x28
		MOV DWORD PTR SS:[ESP+0x44],EDX            ; |
		PUSH 0x41700000                          ; |Arg4 = 41700000
		AND EAX,0x0000FFFF                         ; |
		PUSH ECX                                 ; |Arg3 => OFFSET LOCAL.8
		FSTP DWORD PTR SS:[ESP+0x50]               ; |
		MOV EDX,ESP
		ADD EDX,0x48
		PUSH SHIELD//EAX                                 ; |Arg2
		PUSH EDX                                 ; |Arg1 => OFFSET LOCAL.2
		CALL DMG_FUNCTION                            ; \Main.006BA450
		JMP RETURN_SD_JMP
	}
}

//===============================================================
//		Visual HP Fix
//===============================================================
DWORD DRAW_PANEL_FONT = 0x006FBF97;
DWORD DRAW_TAB = 0x00402F50;
//---
DWORD VISUAL_HP_RET	= 0x0073A274;
__declspec(naked) void FixVisualHp()
{
	_asm
	{
		PUSH 0x3F800000                            ; Arg4 = 3F800000
		PUSH HP//EDX                                 ; Arg3
		PUSH 0x43E00000//43E70000                            ; Arg2 = 43E70000
		FLD DWORD PTR SS:[EBP-0x18]
		FADD DWORD PTR DS:[0x88AC8C]               ; FLOAT 25.00000
		PUSH ECX
		FSTP DWORD PTR SS:[ESP]
		CALL DRAW_PANEL_FONT
		JMP VISUAL_HP_RET
	}
}
void InitFixHpVisual()
{
	SetNop(0x0073A24E,38);
	WriteJmp(0x0073A24E, (DWORD)&FixVisualHp);
}

//===============================================================
//		Visual HP Tab Fix
//===============================================================
DWORD HP_TAB_RET = 0x0073A2D1;
__declspec(naked) void FixVisualHpTab()
{
	_asm
	{
		PUSH MAX_HP//EAX
		PUSH HP//ECX
		PUSH 0x166                                 ; /Arg1 = 166
		MOV ECX,0x07AAD828							; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP HP_TAB_RET
	}
}
void InitFixVisualHpTab()
{
	SetNop(0x0073A2AF,34);
	WriteJmp(0x0073A2AF, (DWORD)&FixVisualHpTab);
}

//===============================================================
//		Circle HP Fix
//===============================================================
DWORD CIRCL_HP_RET = 0x0073A0F9;
__declspec(naked) void FixCircleHp()
{
	_asm
	{
		MOV ECX,MAX_HP//DWORD PTR SS:[EBP-0x28]
		MOV EDX,HP//DWORD PTR SS:[EBP-0x30]
		SUB ECX,EDX
		MOV DWORD PTR SS:[EBP-0x174],ECX
		FILD DWORD PTR SS:[EBP-0x174]
		MOV EAX,MAX_HP//DWORD PTR SS:[EBP-0x28]
		MOV DWORD PTR SS:[EBP-0x178],EAX
		FIDIV DWORD PTR SS:[EBP-0x178]
		FSTP DWORD PTR SS:[EBP-0x134]
		JMP CIRCL_HP_RET
	}
}
void InitCircleHp()
{
	SetNop(0x0073A0BF,61);
	WriteJmp(0x0073A0BF, (DWORD)&FixCircleHp);
}

//===============================================================
//		Info Hp Fix Master
//===============================================================
DWORD INFO_HP_MASTER_RET = 0x006F1154;
__declspec(naked) void FixInfoHpMaster()
{
	_asm
	{
		PUSH MAX_HP//ECX
		PUSH HP//EAX
		PUSH 0x0D3                                 ; /Arg1 = 0D3
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP INFO_HP_MASTER_RET
	}
}
void InitInfoHpMaster()
{
	SetNop(0x006F1130,36);
	WriteJmp(0x006F1130, (DWORD)&FixInfoHpMaster);
}

//===============================================================
//		Info Hp Fix Normal
//===============================================================
DWORD INFO_HP_NORM_RET = 0x006F118F;
__declspec(naked) void FixInfoHpNorm()
{
	_asm
	{
		PUSH MAX_HP//EAX
		PUSH HP//EDX
		PUSH 0x0D3                                 ; /Arg1 = 0D3
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP INFO_HP_NORM_RET
	}
}
void InitInfoHpNormal()
{
	SetNop(0x006F116E,33);
	WriteJmp(0x006F116E, (DWORD)&FixInfoHpNorm);
}
//===============================================================
//		Fix Visual Mana
//===============================================================
DWORD VISUAL_MANA_RET = 0x0073A3B5;
__declspec(naked) void FixVisualMana()
{
	_asm
	{
		PUSH 0x3F800000                            ; Arg4 = 3F800000
		PUSH MP//EAX                                 ; Arg3
		PUSH 0x43E00000//43E70000                            ; Arg2 = 43E70000
		FLD DWORD PTR SS:[EBP-0x18]
		FADD DWORD PTR DS:[0x88B274]               ; FLOAT 30.00000
		PUSH ECX
		FSTP DWORD PTR SS:[ESP]                  ; Arg1
		CALL DRAW_PANEL_FONT
		JMP VISUAL_MANA_RET
	}
}
void InitFixVisualMana()
{
	SetNop(0x0073A390,36);
	WriteJmp(0x0073A390, (DWORD)&FixVisualMana);
}
//===============================================================
//		Fix Mana TAb
//===============================================================
DWORD MANA_TAB_RET = 0x0073A413;
__declspec(naked)void FixManaTab()
{
	_asm
	{
		PUSH MAX_MP//ECX
		PUSH MP//EDX
		PUSH 0x167                                 ; /Arg1 = 167
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP MANA_TAB_RET
	}
}
void InitFixTabMana()
{
	SetNop(0x0073A3F0,35);
	WriteJmp(0x0073A3F0, (DWORD)&FixManaTab);
}
//===============================================================
//		Fix Mana Circle
//===============================================================
DWORD MANA_CIRCL_RET = 0x0073A13D;
__declspec(naked)void FixManaCircle()
{
	_asm
	{
		MOV EDX,MAX_MP//DWORD PTR SS:[EBP-0x4]
		MOV EAX,MP//DWORD PTR SS:[EBP-24]
		SUB EDX,EAX
		MOV DWORD PTR SS:[EBP-0x17C],EDX
		FILD DWORD PTR SS:[EBP-0x17C]
		MOV ECX,MAX_MP//DWORD PTR SS:[EBP-4]
		MOV DWORD PTR SS:[EBP-0x180],ECX
		FIDIV DWORD PTR SS:[EBP-0x180]
		FSTP DWORD PTR SS:[EBP-0x20]
		JMP MANA_CIRCL_RET
	}
}
void InitFixManaCircle()
{
	SetNop(0x0073A106,55);
	WriteJmp(0x0073A106, (DWORD)&FixManaCircle);
}
//===============================================================
//		Fix Info Mana Master
//===============================================================
DWORD MANA_INFO_RET = 0x006F14BF;
__declspec(naked)void FixInfoManaMaster()
{
	_asm
	{
		PUSH MAX_MP//EDX
		PUSH MP//ECX
		PUSH 0x0D5                                 ; /Arg1 = 0D5
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
JMP MANA_INFO_RET
	}
}
void InitFixInfoManaMaster()
{
	SetNop(0x006F149C,34);
	WriteJmp(0x006F149C, (DWORD)&FixInfoManaMaster);
}
//===============================================================
//		Fix Info Mana Normal
//===============================================================
DWORD INFO_MANA_NORM_RET = 0x006F14F9;
__declspec(naked)void FixInfoManaNormal()
{
	_asm
	{
		PUSH MAX_MP//ECX
		PUSH MP//EAX
		PUSH 0x0D5                                 ; /Arg1 = 0D5
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP INFO_MANA_NORM_RET
	}
}
void InitFixInfoManaNormal()
{
	SetNop(0x006F14D8,33);
	WriteJmp(0x006F14D8, (DWORD)&FixInfoManaNormal);
}
//===============================================================
//		Visual SD Fix
//===============================================================
DWORD VISUAL_SD_RET = 0x0073A8FA;
__declspec(naked)void VisualSdFix()
{
	_asm
	{
		PUSH 0x3F800000                            ; Arg4 = 3F800000
		PUSH SD//EAX                                 ; Arg3
		PUSH 0x43E70000//43E70000                            ; Arg2 = 43E70000
		FLD DWORD PTR SS:[EBP-0x1C]
		FADD DWORD PTR DS:[0x88AC3C]               ; FLOAT 15.00000
		PUSH ECX
		FSTP DWORD PTR SS:[ESP]
		CALL DRAW_PANEL_FONT
		JMP VISUAL_SD_RET
	}
}
void InitFixVisualSD()
{
	SetNop(0x0073A8D5,37);
	WriteJmp(0x0073A8D5, (DWORD)&VisualSdFix);
}
//===============================================================
//		SD Tab Fix
//===============================================================
DWORD SD_TAB_FIX = 0x0073A966;
__declspec(naked)void FixTabSd()
{
	_asm
	{
		PUSH MAX_SD//ECX
		PUSH SD//EDX
		PUSH 0x7F5                                 ; /Arg1 = 7F5
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP SD_TAB_FIX
	}
}
void InitFixTabSD()
{
	SetNop(0x0073A943,35);
	WriteJmp(0x0073A943, (DWORD)&FixTabSd);
}
//===============================================================
//		Fix Circle SD
//===============================================================
DWORD CIRCLE_SD_RET = 0x0073A843;
__declspec(naked)void FixCircleSD()
{
	_asm
	{
		MOV ECX,MAX_SD//DWORD PTR SS:[EBP-8]
		MOV EDX,SD//DWORD PTR SS:[EBP-24]
		SUB ECX,EDX
		MOV DWORD PTR SS:[EBP-0x140],ECX
		FILD DWORD PTR SS:[EBP-0x140]
		MOV EAX,MAX_SD//DWORD PTR SS:[EBP-8]
		MOV DWORD PTR SS:[EBP-0x144],EAX
		FIDIV DWORD PTR SS:[EBP-0x144]
		FSTP DWORD PTR SS:[EBP-0x4]
		JMP CIRCLE_SD_RET
	}
}
void InitFixCircleSD()
{
	SetNop(0x0073A80C,55);
	WriteJmp(0x0073A80C, (DWORD)&FixCircleSD);
}
//===============================================================
//		Visual Fix AG
//===============================================================
DWORD VISUAL_AG_RET = 0x0073A656;
__declspec(naked)void VisualFixAG()
{
	_asm
	{
		PUSH 0x3F800000                            ; Arg4 = 3F800000
		PUSH AG//EAX                                 ; Arg3
		PUSH 0x43E70000                            ; Arg2 = 43E70000
		FLD DWORD PTR SS:[EBP-0x20]
		FADD DWORD PTR DS:[0x88AD00]               ; FLOAT 10.00000
		PUSH ECX
		FSTP DWORD PTR SS:[ESP]
		CALL DRAW_PANEL_FONT
		JMP VISUAL_AG_RET
	}
}
void InitVisualFixAG()
{
	SetNop(0x0073A631,37);
	WriteJmp(0x0073A631, (DWORD)&VisualFixAG);
}
//===============================================================
//		Fix Tab AG
//===============================================================
DWORD TAB_AG_RET = 0x0073A6B4;
__declspec(naked)void FixAGTab()
{
	_asm
	{
		PUSH MAX_AG//ECX
		PUSH AG//EDX
		PUSH 0x0D6                                 ; /Arg1 = 0D6
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP TAB_AG_RET
	}
}
void InitFixAgTab()
{
	SetNop(0x0073A691,35);
	WriteJmp(0x0073A691, (DWORD)&FixAGTab);
}
//===============================================================
//		Fix Circle AG
//===============================================================
DWORD CIRCLE_AG_RET = 0x0073A59F;
__declspec(naked)void FixCircleAG()
{
	_asm
	{
		MOV ECX,MAX_AG//DWORD PTR SS:[EBP-18]
		MOV EDX,AG//DWORD PTR SS:[EBP-8]
		SUB ECX,EDX
		MOV DWORD PTR SS:[EBP-0x140],ECX
		FILD DWORD PTR SS:[EBP-0x140]
		MOV EAX,MAX_AG//DWORD PTR SS:[EBP-18]
		MOV DWORD PTR SS:[EBP-0x144],EAX
		FIDIV DWORD PTR SS:[EBP-0x144]
		FSTP DWORD PTR SS:[EBP-0x4]
		JMP CIRCLE_AG_RET
	}
}
void InitFixCirclAG()
{
	SetNop(0x0073A568,55);//
	WriteJmp(0x0073A568, (DWORD)&FixCircleAG);
}
//===============================================================
//		Fix Exp
//===============================================================
DWORD EXP_RET = 0x0061F881;
__declspec(naked)void FixExp()
{
	_asm
	{
		MOV EDI,EXP
		JMP EXP_RET
	}
}
void InitFixExp()
{
	SetNop(0x0061F87C,5);//
	WriteJmp(0x0061F87C, (DWORD)&FixExp);
}
//===============================================================
//		Fix UpPoint
//===============================================================
DWORD UP_POINT_RET = 0x006EEE85;
__declspec(naked)void FixUpPoint()
{
	_asm
	{
		PUSH UP_POINT//EDX
		PUSH 0x0D9                                 ; /Arg1 = 0D9
		MOV ECX,0x07AAD828                  ; |
		CALL DRAW_TAB                            ; \Main.00402F50
		JMP UP_POINT_RET
	}
}
void InitFixUpPoint()
{
	SetNop(0x006EEE75,16);//
	WriteJmp(0x006EEE75, (DWORD)&FixUpPoint);
}
#endif

//===============================================================
void InitProtocol()
{
	HookThis((DWORD)&cMU_ProtocolCore,PROTOCOL_CALL);

#ifdef _SPEED_FIX_
	SetNop(0x004D5E05,80);
	WriteJmp(0x004D5E05, (DWORD)&FixAttackSpeed);
#endif

#ifdef _VISUAL_FIX_
	WriteJmp(0x0061A289, (DWORD)FixVisualDamageHP);
	WriteJmp(0x0061A2DF, (DWORD)FixVisualDamageSD);
	InitFixHpVisual();
	InitFixVisualHpTab();
	InitCircleHp();
	InitInfoHpMaster();
	InitInfoHpNormal();
	InitFixVisualMana();
	InitFixTabMana();
	InitFixManaCircle();
	InitFixInfoManaMaster();
	InitFixInfoManaNormal();
	InitFixVisualSD();
	InitFixTabSD();
	InitFixCircleSD();
	InitVisualFixAG();
	InitFixAgTab();
	InitFixCirclAG();
	InitFixExp();
	InitFixUpPoint();
#endif
}

