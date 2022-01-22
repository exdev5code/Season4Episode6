#include "StdAfx.h"
#include "user.h"
#include "Message.h"
#include "Reset.h"
#include "Functions.h"
#include "LogProc.h"
#include "Configs.h"
#include "PCPointSystem.h"
#include "SystemOfRage.h"
#include "DSProtocol.h"

cReset gReset;

void cReset::Load()
{
#ifdef _Eugene_
	this->NPC_Num = GetPrivateProfileInt("Reset","NPC_Num",0,Reset_DIR);
	this->NPC_Map = GetPrivateProfileInt("Reset","NPC_Map",0,Reset_DIR);
	this->NPC_X = GetPrivateProfileInt("Reset","NPC_X",0,Reset_DIR);
	this->NPC_Y = GetPrivateProfileInt("Reset","NPC_Y",0,Reset_DIR);
	this->NeedItemEnable = GetPrivateProfileInt("Reset","NeedItemEnable",0,Reset_DIR);
	this->NeedItemType = GetPrivateProfileInt("Reset","NeedItemType",0,Reset_DIR);
	this->NeedItemIndex = GetPrivateProfileInt("Reset","NeedItemIndex",0,Reset_DIR);
	this->NeedItemLevel = GetPrivateProfileInt("Reset","NeedItemLevel",0,Reset_DIR);
#endif
}

#if __MuRain__

void cReset::Init()
{
	for(int i(0);i<100;i++)
	{
		this->rTab[i].Reset = 0;
		this->rTab[i].Level = 0;
	}

	FILE * file = fopen(Reset_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\Reset.ini Load Error","CRITICAL ERROR",0);
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->rTab[this->Count].Reset = n[0];
			this->rTab[this->Count].Level = n[1];
			this->Count++;
		}
	}
	fclose(file);
}

#endif

void cReset::ExResetSystemFunciton(int aIndex)
{
	int ZenMoney = 0;

	if(!ExConfig.Reset.EnableResetSystem)
		return;
	//Проверка на максимальное количество ресетов
	if(ExUser[aIndex].Reset >= ExConfig.Reset.Maxres)
	{
		MsgNormal(aIndex,"[Reset]: Max Reset %d",ExConfig.Reset.Maxres);
		return;
	}
	LPOBJ lpObj = &gObj[aIndex];

	if ( (GetTickCount() - lpObj->MySelfDefenseTime ) < 60000)
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4, 109)), lpObj->m_Index, 1);
		GCCloseMsgSend(aIndex,-1); //Season 2.5 add-on
		return;
	}

	if ( (lpObj->m_IfState.use) > 0 ) 
	{
		MsgNormal(aIndex,"[Reset]: Interface Off to Reset");
		return;
	}
//#ifdef _pravednik_
//	if(lpObj->MapNumber != 2)
//	{
//		MsgNormal(aIndex,"[Reset]: Started In Arkania");
//		return;
//	}
//#else
	if(lpObj->MapNumber != 0)
	{
		MsgNormal(aIndex,"[Reset]: Started In Lorencia");
		return;
	}
//#endif
	//Проверка на уровень
#if __MuRain__
	int NeedLevel = 400;
	for(int i=0;i<this->Count;i++)
	{
		if(this->rTab[i].Reset == ExUser[aIndex].Reset + 1)
		{
			NeedLevel = this->rTab[i].Level;
			break;
		}
	}
	if(NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",NeedLevel);
		return;
	}
#else
	if(ExConfig.Reset.NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",ExConfig.Reset.NeedLevel);
		return;
	}
	//Проверка на уровень
#ifdef _SYSTEM_OF_RAGE_
	if((ExConfig.Reset.NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0) > lpObj->Level))
	{
		MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",ExConfig.Reset.NeedLevel - gSystemOfRage.ReturnCalc(aIndex,eSkill7,0));
		return;
	}
#else
	if(ExConfig.Reset.NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[Reset]: You need above %d Level to Reset",ExConfig.Reset.NeedLevel);
		return;
	}
#endif
#endif

	//Проверка на зен
	switch(ExConfig.Reset.ZenForm)
	{
		case 1: ZenMoney = ExConfig.Reset.NeedZen * ( ExUser[aIndex].Reset + 1 ); break;
		case 2: ZenMoney = ExConfig.Reset.NeedZen; break;
	}
	
	if(ExConfig.Reset.ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			MsgNormal(aIndex,"[Reset]: You need above %d Zen to Reset",ZenMoney);
			return;
		}
	}
	//Проверка на пустой инвентарь
	if(ExConfig.Reset.NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[Reset]: You need Empty Inventory to Reset");
			return;
		}
	}

#ifdef _Eugene_
	if(this->NeedItemEnable)
	{
		if(gObjGetItemCountInInventory(aIndex,ITEMGET(this->NeedItemType,this->NeedItemIndex),this->NeedItemLevel) < 1)
		{
			MsgNormal(aIndex,"[Reset] Need Item");
			return;
		}
		gObjDeleteItemsCount(aIndex,ITEMGET(this->NeedItemType,this->NeedItemIndex),this->NeedItemLevel,1);
	}
#endif

	/////////////////////
	//Выполнение ресета//
	/////////////////////
	lpObj->Money -= ZenMoney;
	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	//ExUser[aIndex].PCPoint += ExConfig.Reset.AddPcPoint;
	if(ExConfig.Reset.AddForm == 2)
	{
		lpObj->Strength = 25;
		lpObj->Dexterity = 25;
		lpObj->Vitality = 25;
		lpObj->Energy = 25;
		if(lpObj->Class == 4)
			lpObj->Leadership = 25;
	}
	//Поинта за ресет
	if(ExConfig.Reset.AddForm == 1 || ExConfig.Reset.AddForm == 2)
	{
		switch (lpObj->Class)
		{
			case 0: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsDW ;  break;
			case 1: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsDK ;  break;
			case 2: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsELF ; break;
			case 3: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsMG ;  break;
			case 4: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsDL ;  break;
			case 5: lpObj->LevelUpPoint = ( ExUser[aIndex].Reset + 1 ) * ExConfig.Reset.AddPointsSUM ; break;
		}
	}
	//Поинта от гранд ресета
	
	if(ExConfig.GrandReset.EnableGrandResetSystem)
	{
		if(ExUser[aIndex].GReset > 0)
		{
			if(ExConfig.GrandReset.AddForm == 1 || ExConfig.GrandReset.AddForm == 2)
			{
				switch (lpObj->Class)
				{
					case 0: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDW ;  break;
					case 1: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDK ;  break;
					case 2: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsELF ; break;
					case 3: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsMG ;  break;
					case 4: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDL ;  break;
					case 5: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsSUM ; break;
				}
			}
#ifdef NEW_RESET_GRANDRESET
			if(ExConfig.GrandReset.AddForm == 3)
			{
				switch (lpObj->Class)
				{
					case 0: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDW  * ( ExUser[aIndex].Reset+1 ); break;
					case 1: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDK  * ( ExUser[aIndex].Reset+1 ); break;
					case 2: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsELF * ( ExUser[aIndex].Reset+1 ); break;
					case 3: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsMG  * ( ExUser[aIndex].Reset+1 ); break;
					case 4: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsDL  * ( ExUser[aIndex].Reset+1 ); break;
					case 5: lpObj->LevelUpPoint += ExUser[aIndex].GReset * ExConfig.GrandReset.AddPointsSUM * ( ExUser[aIndex].Reset+1 ); break;
				}
			}
#endif
		}
	}

	lpObj->LevelUpPoint += ExUser[aIndex].ExFreePoints;
	ExUser[aIndex].Reset++;
	ExUser[aIndex].PCPoint += ExConfig.Reset.AddExPoint;
	ExPCPointSystem.InitPCPointForPlayer(lpObj, ExUser[aIndex].PCPoint ,lpObj->ExCred);



	MsgNormal(aIndex,"[PCPoint] +%d For Reset",ExConfig.Reset.AddExPoint);

	if(ExConfig.Reset.AddWcoin)
	{
		int dwCost = ExConfig.Reset.AddWcoin * (ExUser[aIndex].GReset+1);
		GDRequestWcoinInfoLoad (lpObj,dwCost,1);
	}

	

	ExFireCracker(aIndex, lpObj->X, lpObj->Y);
	gObjCloseSet(aIndex, 1);
	LogAddTD("[ResetSystem] Accaunt: %s , Name: %s , Reset: %d",lpObj->AccountID, lpObj->Name,ExUser[aIndex].Reset);
}

#ifdef _Eugene_
void cReset::NPCReset(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(lpNpc->Class == this->NPC_Num && lpNpc->MapNumber == this->NPC_Map && lpNpc->X == this->NPC_X && lpNpc->Y == this->NPC_Y)
	{
		ExResetSystemFunciton(lpObj->m_Index);
	}
	
}
#endif