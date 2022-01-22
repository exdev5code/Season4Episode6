#include "stdafx.h"
//#include "Object.h"
#include "TMemory.h"
#include "ConnectEx.h"
#include "NewHpBar.h"
#include "User.h"
#include "Interface.h"
#include "Console.h"
//#include "ChatExpanded.h"
//#include "Import.h"
#include "GameCharacter.h"
#include "MonsterHPBar.h"
#include "Configs.h"

#ifdef NEW_HP_BAR

ViewePortInfo gViewePortInfo;

void ViewePortInfo::NewHpBarLoad()
{
	//this->HPAllMonster = 1;
	//this->HPTargetMonster = 1;
	//this->HPPartyBar = 1;
	//this->HPTargetUser = 1;
}

WORD IndexModel(int a1)
{
  int v2; // [sp+0h] [bp-Ch]@3
  signed int v3; // [sp+4h] [bp-8h]@1
  signed int i; // [sp+8h] [bp-4h]@1

  //for ( i = 0; i < 400; ++i )
  //{
	 // if(a1==i)
	 // {
		return *(WORD *)(1236 * a1 + *(DWORD*)0x7A7239C + 94);
	//  }
 // }
  //return -1;

 // v3 = 400;
 // for ( i = 0; i < 400; ++i )
 // {
 //   v2 = 1236 * i + *(DWORD*)0x7A7239C;
	////v2 = *(DWORD*)0x7A7239C + 1236 * i;
 //   if ( *(BYTE *)(1236 * i + *(DWORD*)0x7A7239C + 704) )
 //   {
 //     if ( *(WORD *)(v2 + 94) == a1 )
 //       v3 = i;
	//  break;
 //   }
 //   *(BYTE *)(v2 + 23) = 0;
 // }
 // return v3;
}


int HpResMode()
{
	if(pWinWidth == 800 & pWinHeight == 600)
	{
		return 5;
	}
	else if (pWinWidth == 1024 & pWinHeight == 768)
	{
		return 10;
	}
	else if (pWinWidth == 1280 & pWinHeight == 720)
	{
		return 10;
	}
	else if (pWinWidth == 1280 & pWinHeight == 800)
	{
		return 10;
	}
	else if (pWinWidth == 1366 & pWinHeight == 768)
	{
		return 10;
	}
	else if (pWinWidth == 1440 & pWinHeight == 900)
	{
		return 13;
	}
	else if (pWinWidth == 1280 & pWinHeight == 1024)
	{
		return 14;
	}
	else if (pWinWidth == 1600 & pWinHeight == 1200)
	{
		return 16;
	}
	else if (pWinWidth == 1680 & pWinHeight == 1050)
	{
		return 13;
	}
	else if (pWinWidth == 1920 & pWinHeight == 1080)
	{
		return 13;
	}
	else if (pWinWidth == 1920 & pWinHeight == 1200)
	{
		return 16;
	}
	else
	{
		return 5;
	}
}

void ViewePortInfo::TargetMonsterHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	//lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);

	if( pViewAttackTargetID < 0 ) return;

	//if(lpViewTarget->m_Model.ObjectType == emMonster)

	int Life, MaxLife, Level, Def;

	//BYTE Live = 0;

	if(IndexModel(pViewAttackTargetID)  < 10000)
	{
		bool Draw = false;
		char NewName[20];

		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			//if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex)
			if(IndexModel(pViewAttackTargetID) == gObjUser.ExViewe[n].aIndex)
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Draw = true;
				memcpy(NewName,gObjUser.ExViewe[n].Name,sizeof(NewName));
				//Live = gObjUser.ExViewe[n].Live;
				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			return;
		}

		int DevX = 20;
		int Wind = 70;

		//Angle.X = lpViewTarget->m_Model.VecPosX;
		//Angle.Y = lpViewTarget->m_Model.VecPosY;
		//Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

		Angle.X = *(float *)(*(DWORD*)0x7A7239C + 1236 * pViewAttackTargetID + 952);
		Angle.Y = *(float *)(*(DWORD*)0x7A7239C + 1236 * pViewAttackTargetID + 956);
		Angle.Z = *(float *)(*(DWORD*)0x7A7239C + 1236 * pViewAttackTargetID + 960) + *(float *)(*(DWORD*)0x7A7239C + 1236 * pViewAttackTargetID + 924) + 100.0;


		pGetPosFromAngle(&Angle, &PosX, &PosY);
		//PosX -= (int)floor(LifeBarWidth / (double)2.0);
		PosX -= (int)floor((double)Wind / (double)4.0);

		sprintf(LifeDisplay, "L:%d HP:%d",Level, Life);
		pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
		pDrawText(pTextThis(), PosX-DevX, PosY - 19, LifeDisplay, Wind, 10, (LPINT)3, 0);		
		
		sprintf(LifeDisplay, "%s", NewName);
		pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
		pDrawText(pTextThis(), PosX - DevX, PosY - 8, LifeDisplay, Wind, 14, (LPINT)3, 0);

		pSetBlend(true);
		pGLSwitchBlend();

		int pHP = (Life * 100) / MaxLife;
		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		//pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}
}

void ViewePortInfo::AllMonsterHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	for(int i = 0; i < 400; i++)
	{
		//lpViewObj lpObj    = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), i);

		//if( !lpObj || !lpObj->m_Model.Unknown4 )
		//{
		//	continue;
		//}

			if( i < 0/* || !lpViewTarget->m_Model.Unknown4*/ )
			{
				//Console.ConsoleOutput(GREEN,"gObjUser.VieweTargetID < 0");
				return;
			}

			int Life, MaxLife, Level, Shield, MaxShield, Reset, GRand;

			//BYTE Live = 0;

		//if(lpObj->m_Model.ObjectType == emMonster)
		if(IndexModel(i)  < 10000)
		{
			

			bool Draw = false;

			char NewName[20];

			for(int n = 0; n < MAX_VIEWPORT;n++)
			{
				//if(lpObj->aIndex == gObjUser.ExViewe[n].aIndex)
				if(IndexModel(i) == gObjUser.ExViewe[n].aIndex && gObjUser.ExViewe[n].aIndex != -1)
				{
				
					Life = gObjUser.ExViewe[n].Life;
					MaxLife = gObjUser.ExViewe[n].MaxLife;
					Level = gObjUser.ExViewe[n].Level;
					Draw = true;
					memcpy(NewName,gObjUser.ExViewe[n].Name,sizeof(NewName));
					//Live = gObjUser.ExViewe[n].Live;
					if(Life > MaxLife)
					{
						gObjUser.ExViewe[n].Life = MaxLife;
						Life = MaxLife;
					}
					break;
				}
			}

			if(Draw == false || Life <= 0 )
			{
				continue;
			}

			int DevX = 20;
			int Wind = 70;

			//Angle.X = lpObj->m_Model.VecPosX;
			//Angle.Y = lpObj->m_Model.VecPosY;
			//Angle.Z = lpObj->m_Model.VecPosZ + lpObj->m_Model.Unknown216.Z + 100.0;

		Angle.X = *(float *)(*(DWORD*)0x7A7239C + 1236 * i + 952);
		Angle.Y = *(float *)(*(DWORD*)0x7A7239C + 1236 * i + 956);
		Angle.Z = *(float *)(*(DWORD*)0x7A7239C + 1236 * i + 960) + *(float *)(*(DWORD*)0x7A7239C + 1236 * i + 924) + 100.0;


			// ----
			pGetPosFromAngle(&Angle, &PosX, &PosY);
			//PosX -= (int)floor(LifeBarWidth / (double)2.0);
			PosX -= (int)floor((double)Wind / (double)4.0);

			if(pViewAttackTargetID == i)
			{
				sprintf(LifeDisplay, "L:%d HP:%d",Level, Life);
				pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX-DevX, PosY - 19, LifeDisplay, Wind, 10, (LPINT)3, 0);		
			}

			//lpViewObj lpObj    = &*(ObjectPreview*)*(DWORD*)(0x7A7239C + 1236 * i);

			sprintf(LifeDisplay, "%s",NewName);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX - DevX, PosY - 8, LifeDisplay, Wind, 14, (LPINT)3, 0);

			pSetBlend(true);
			pGLSwitchBlend();

			int pHP = (Life * 100) / MaxLife;
			pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2), (Wind * pHP/*100*/) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

			//pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}
	}
}


void ViewePortInfo::TargetUserHpBar()
{
	char LifeDisplay[30];
	VAngle Angle;
	int PosX, PosY, LifeProgress;

	float LifeBarWidth	= 38.0f;

	//lpViewObj lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), gObjUser.VieweTargetID);




	if( gObjUser.VieweTargetID < 0/* || !lpViewTarget->m_Model.Unknown4*/ )
	{
		//Console.ConsoleOutput(GREEN,"gObjUser.VieweTargetID < 0");
		return;
	}

	if(IndexModel(gObjUser.VieweTargetID)  >= 10000)
	{
		bool Result = false;
		if( pPartyMemberCount > 0 )
		{
			for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
			{
				PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);
				if(gObjUser.VieweTargetID == PartyMember.ViewportID)
				{
					//Console.ConsoleOutput(GREEN,"if(gObjUser.VieweTargetID == PartyMember.ViewportID)");
					return;
				}
			}
		}

		int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset;

		//BYTE Live = 0;

		bool Draw = false;

		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			//if(lpViewTarget->aIndex == gObjUser.ExViewe[n].aIndex)
			if(IndexModel(gObjUser.VieweTargetID) == gObjUser.ExViewe[n].aIndex)
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Shield = gObjUser.ExViewe[n].SD;
				MaxShield = gObjUser.ExViewe[n].MaxSD;
				Reset = gObjUser.ExViewe[n].Reset;
				GrandReset = gObjUser.ExViewe[n].GrandReset;
				//Live = gObjUser.ExViewe[n].Live;
				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
				Draw = true;
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			//Console.ConsoleOutput(GREEN,"Draw == false || Life <= 0");
			return;
		}

		int DevX = 20;
		int Wind = 70;
		int DevY = 0;

		//Angle.X = lpViewTarget->m_Model.VecPosX;
		//Angle.Y = lpViewTarget->m_Model.VecPosY;
		//Angle.Z = lpViewTarget->m_Model.VecPosZ + lpViewTarget->m_Model.Unknown216.Z + 100.0;

		Angle.X = *(float *)(*(DWORD*)0x7A7239C + 1236 * gObjUser.VieweTargetID + 952);
		Angle.Y = *(float *)(*(DWORD*)0x7A7239C + 1236 * gObjUser.VieweTargetID + 956);
		Angle.Z = *(float *)(*(DWORD*)0x7A7239C + 1236 * gObjUser.VieweTargetID + 960) + *(float *)(*(DWORD*)0x7A7239C + 1236 * gObjUser.VieweTargetID + 924) + 100.0;


		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor((double)Wind / (double)4.0);

		PosY -= 10 - HpResMode();

		if(gObjUser.BattleCursor == true)
		{
			sprintf(LifeDisplay, "HP: %d",Life);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}
		else
		{
			sprintf(LifeDisplay, "L:%d R:%d G:%d",Level, Reset,GrandReset);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}

		pSetBlend(true);
		pGLSwitchBlend();

		int pSD = (Shield * 100) / MaxShield;
		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, (int)Color4f(255, 255, 0, 130));

		int pHP = (Life * 100) / MaxLife;
		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 4 - DevY + 9), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		//pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}
}

void ViewePortInfo::AllUserHpBar()
{

}

void ViewePortInfo::PartyHPBar()
{
    if( pPartyMemberCount <= 0 )
    {
        return;
    }
    // ----
    float LifeBarWidth = 38.0f;
    char LifeDisplay[30];
    VAngle Angle;
    int PosX, PosY, LifeProgress;

    // ----
		for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
		{
			PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);

			//Console.ConsoleOutput(GREEN,"PartyMember.ViewportID: %d",PartyMember.ViewportID);
			if( 0 > PartyMember.ViewportID  )
			{
				//Console.ConsoleOutput(GREEN,"0 > PartyMember.ViewportID: %d",PartyMember.ViewportID);
				continue;
			}

		int Life, MaxLife, Shield, MaxShield, Def, Reset, Level, GrandReset;

		bool Draw = false;

		//Console.ConsoleOutput(GREEN,"%d Index: %d",PartyMember.ViewportID,IndexModel(PartyMember.ViewportID));

		for(int n = 0; n < MAX_VIEWPORT;n++)
		{
			//if(IndexModel(gObjUser.ExViewe[n].aIndex) != -1 )
			if(gObjUser.ExViewe[n].aIndex == -1) continue;
			//if(*(WORD *)(1236 * PartyMember.ViewportID + *(DWORD*)0x7A7239C + 94)  = gObjUser.ExViewe[n].aIndex )
			if(IndexModel(PartyMember.ViewportID) == gObjUser.ExViewe[n].aIndex)
			{
				Life = gObjUser.ExViewe[n].Life;
				MaxLife = gObjUser.ExViewe[n].MaxLife;
				Level = gObjUser.ExViewe[n].Level;
				Def = gObjUser.ExViewe[n].Defence;
				Shield = gObjUser.ExViewe[n].SD;
				MaxShield = gObjUser.ExViewe[n].MaxSD;
				Reset = gObjUser.ExViewe[n].Reset;
				GrandReset = gObjUser.ExViewe[n].GrandReset;
				if(Life > MaxLife)
				{
					gObjUser.ExViewe[n].Life = MaxLife;
					Life = MaxLife;
				}
				Draw = true;
				break;
			}
		}

		if(Draw == false || Life <= 0)
		{
			return;
		}

		int DevX = 20;
		int Wind = 70;
		int DevY = 0;//-5;	//Code

		//Angle.X = lpPartyObj->m_Model.VecPosX;
		//Angle.Y = lpPartyObj->m_Model.VecPosY;
		//Angle.Z = lpPartyObj->m_Model.VecPosZ + lpPartyObj->m_Model.Unknown216.Z + 100.0;

		Angle.X = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 952);
		Angle.Y = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 956);
		Angle.Z = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 960) + *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 924) + 100.0;


		// ----
		pGetPosFromAngle(&Angle, &PosX, &PosY);
		PosX -= (int)floor((double)Wind / (double)4.0);

		PosY -= 10 - HpResMode();

		if(gObjUser.VieweTargetID == PartyMember.ViewportID && gObjUser.BattleCursor == false)
		{
			
			sprintf(LifeDisplay, "L:%d R:%d G:%d",Level, Reset,GrandReset);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}
		else
		{
			sprintf(LifeDisplay, "HP: %d",Life);
			pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
			pDrawText(pTextThis(), PosX-DevX, PosY - DevY, LifeDisplay, Wind, 16, (LPINT)3, 0);	
		}

		pSetBlend(true);
		pGLSwitchBlend();

		int pSD = (Shield * 100) / MaxShield;
		//Console.ConsoleOutput(GREEN,"Shield: %d MaxShield: %d",Shield,MaxShield);
		pDrawColorButton(0x7880, /*(MAX_WIDTH / 2) - 75*/ (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, (int)Color4f(255, 255, 0, 130));

		//MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) - 75, 5, (150 * 100) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));

		//MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) - 75, 5, (150 * pSD) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));

		//pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 2 - DevY + 7), (Wind * pSD) / 100, 2, 0, 0, (int)Color4f(255, 255, 0, 130));

		int pHP = (Life * 100) / MaxLife;
		//Console.ConsoleOutput(GREEN,"pHP: %d",pHP);
		pDrawColorButton(0x7880, (PosX - DevX) , (PosY + 4 - DevY + 9), (Wind * pHP) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));

		//pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
    }
}

void ViewePortInfo::DrawPartyHP(int a1, int a2, int a3)
{
	
	//pPartyDraw2();
	//return;
	//Config.iMonsterHPBar = 2;
	if(Config.iMonsterHPBar == 1)
	{
		gViewePortInfo.AllMonsterHpBar();
	}
	else if(Config.iMonsterHPBar == 2)
	{
		gViewePortInfo.TargetMonsterHpBar();
	}

	//.iUserHpBar	= 1;
	if(Config.iUserHpBar)
	{
		gViewePortInfo.TargetUserHpBar();
	}

	//gViewePortInfo.iPartyHpBar = 1;

	if(Config.iPartyHpBar)
	{
		gViewePortInfo.PartyHPBar();
	}
	else
	{
		if( pPartyMemberCount <= 0 )
		{
			return;
		}

		float LifeBarWidth = 38.0f;
		char LifeDisplay[30];
		VAngle Angle;
		int PosX, PosY, LifeProgress;

		for( int PartySlot = 0; PartySlot < pPartyMemberCount; PartySlot++ )
		{
			PartyList PartyMember    = *(PartyList*)((char*)&pPartyListStruct + sizeof(PartyList) * PartySlot);

			//Console.ConsoleOutput(GREEN,"PartyMember.ViewportID: %d",PartyMember.ViewportID);
			if( 0 > PartyMember.ViewportID  )
			{
				//Console.ConsoleOutput(GREEN,"0 > PartyMember.ViewportID: %d",PartyMember.ViewportID);
				continue;
			}

			//lpViewObj lpPartyObj    = &*(ObjectPreview *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID);
			//Angle.X = lpPartyObj->m_Model.VecPosX;
			//Angle.Y = lpPartyObj->m_Model.VecPosY;
			//Angle.Z = lpPartyObj->m_Model.VecPosZ + lpPartyObj->m_Model.Unknown216.Z + 100.0;

			Angle.X = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 952);
			Angle.Y = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 956);
			Angle.Z = *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 960) + *(float *)(*(DWORD*)0x7A7239C + 1236 * PartyMember.ViewportID + 924) + 100.0;


			//Console.ConsoleOutput(RED,"%d %d",PartyMember.ViewportID,sub_4FC0001111(PartyMember.ViewportID));

			pGetPosFromAngle(&Angle, &PosX, &PosY);

			//Console.ConsoleOutput(GREEN,"PosX: %d | PosY: %d",PosX,PosY);



			PosX -= (int)floor(LifeBarWidth / (double)2.0);
			//MU_DrawColorButton(NEWUI_BAR_SWITCH02, (MAX_WIDTH / 2) - 75, 5, (150 * pHP) / 100, 8, 0, 0, MU_CreateColor(255, 0, 0, 130));
			//pDrawColorButton(0x00007A5C, (PosX) , (PosY), (80 * 100) / 100, 2, 0, 0, (int)Color4f(255, 0, 0, 130));
 
			if(        pCursorX >= PosX
				&&    (float)pCursorX <= (float)PosX + LifeBarWidth
				&&    pCursorY >= PosY - 2
				&&    pCursorY < PosY + 6 )
			{
				sprintf(LifeDisplay, "HP : %d0%%", 100 /*PartyMember.LifePercent*/);
				pSetTextColor(pTextThis(), 0xFF, 0xE6, 0xD2, 0xFF));
				pDrawText(pTextThis(), PosX, PosY - 6, LifeDisplay, 0, 0, (LPINT)1, 0);
			}

			pSetBlend(true);

			glColor4f(0.0, 0.0, 0.0, 0.5);
			pDrawBarForm((float)(PosX + 1), (float)(PosY + 1), LifeBarWidth + 4.0, 5.0, 0.0, 0);
			pGLSwitchBlend();

			glColor3f(0.2, 0.0, 0.0);
			pDrawBarForm((float)PosX, (float)PosY, LifeBarWidth + 4.0, 5.0, 0.0, 0);

			glColor3f(0.19607843, 0.039215688, 0.0);
			pDrawBarForm((float)(PosX + 2), (float)(PosY + 2), LifeBarWidth, 1.0, 0.0, 0);

			if( PartyMember.LifePercent > 10 )    
			{
				LifeProgress = 10;
			}
			else
			{
				LifeProgress = PartyMember.LifePercent;
			}

			glColor3f(0.98039216, 0.039215688, 0.0);

			for( int i = 0; i < LifeProgress; i++ )
			{
				pDrawBarForm((float)(i * 4 + PosX + 2), (float)(PosY + 2), 3.0, 2.0, 0.0, 0);
			}

			//pGLSwitch();
		}
		//pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
	}
}

void ViewePortInfo::InitNewHpBar()
{
	//Console.ConsoleOutput(GREEN,"InitNewHpBar");
	//0057FF65	|	580E50	
	//SetRange((LPVOID)0x0057FF65, 5, ASM::NOP);
	SetOp((LPVOID)0x0057FF65, this->DrawPartyHP, ASM::CALL);
	//SetOp((LPVOID)0x005B96E8, this->DrawPartyHP, ASM::CALL);
}

#endif