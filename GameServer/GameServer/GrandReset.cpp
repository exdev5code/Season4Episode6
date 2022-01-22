#include "StdAfx.h"
#include "user.h"
#include "Message.h"
#include "Reset.h"
#include "Functions.h"
#include "LogProc.h"
#include "Configs.h"
#include "DSProtocol.h"
//int EnableGrandResetSystem = GetPrivateProfileInt("GrandReset","Enable",0,"..\\ExTeam\\GrandReset.ini");	
//int MaxGrandRes = GetPrivateProfileInt("GrandReset","Max.GrandRes",100,"..\\ExTeam\\GrandReset.ini");
//int ZenForm = GetPrivateProfileInt("GrandReset","ZenForm",0,"..\\ExTeam\\GrandReset.ini");
//int NeedZen = GetPrivateProfileInt("GrandReset","Need.Zen",0,"..\\ExTeam\\GrandReset.ini");
//int NeedRes = GetPrivateProfileInt("GrandReset","Need.Res",0,"..\\ExTeam\\GrandReset.ini");
//int NeedLevel = GetPrivateProfileInt("GrandReset","Need.Level",0,"..\\ExTeam\\GrandReset.ini");
//int AddForm = GetPrivateProfileInt("GrandReset","Add.Form",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsDW = GetPrivateProfileInt("GrandReset","Add.PointsDW",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsDK = GetPrivateProfileInt("GrandReset","Add.PointsDK",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsELF = GetPrivateProfileInt("GrandReset","Add.PointsELF",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsSUM = GetPrivateProfileInt("GrandReset","Add.PointsSUM",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsMG = GetPrivateProfileInt("GrandReset","Add.PointsMG",0,"..\\ExTeam\\GrandReset.ini");
//int AddPointsDL = GetPrivateProfileInt("GrandReset","Add.PointsDL",0,"..\\ExTeam\\GrandReset.ini");
//int AddPcPoint = GetPrivateProfileInt("GrandReset","Add.PcPoint",0,"..\\ExTeam\\GrandReset.ini");
//int NeedEmptyInv = GetPrivateProfileInt("GrandReset","Need.EmptyInv",1,"..\\ExTeam\\GrandReset.ini");

void ExGrandResetSystemFunciton(int aIndex)
{
	if(!ExConfig.GrandReset.EnableGrandResetSystem)
		return;
	//Проверка на максимальное количество ресетов
	if(ExUser[aIndex].GReset >= ExConfig.GrandReset.MaxGrandRes)
	{
		MsgNormal(aIndex,"[GReset]: Max Grand Reset %d",ExUser[aIndex].GReset);
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
		MsgNormal(aIndex,"[GReset]: Interface Off to Grand Reset");
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
		MsgNormal(aIndex,"[GReset]: Started In Lorencia");
		return;
	}
//#endif
	//Проверка на Ресет
	if(ExConfig.GrandReset.NeedRes > ExUser[aIndex].Reset)
	{
		MsgNormal(aIndex,"[GReset]: You need above %d Reset to GReset",ExConfig.GrandReset.NeedRes);
		return;
	}
	//Проверка на уровень
	if(ExConfig.GrandReset.NeedLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[GReset]: You need above %d Level to GReset",ExConfig.GrandReset.NeedLevel);
		return;
	}
	int ZenMoney = 0;
	//Проверка на зен
	switch(ExConfig.GrandReset.ZenForm)
	{
		case 1: ZenMoney = ExConfig.GrandReset.NeedZen * ( ExUser[aIndex].GReset + 1 ); break;
		case 2: ZenMoney = ExConfig.GrandReset.NeedZen; break;
	}
	
	if(ExConfig.GrandReset.ZenForm != 0)
	{
		if(lpObj->Money < ZenMoney)
		{
			MsgNormal(aIndex,"[GReset]: You need above %d Zen to GReset",ZenMoney);
			return;
		}
	}
	//Проверка на пустой инвентарь
	if(ExConfig.GrandReset.NeedEmptyInv)
	{
		if(lpObj->pInventory[0].m_Type != -1 || lpObj->pInventory[1].m_Type != -1 || lpObj->pInventory[2].m_Type != -1 ||
		   lpObj->pInventory[3].m_Type != -1 || lpObj->pInventory[4].m_Type != -1 || lpObj->pInventory[5].m_Type != -1 ||
		   lpObj->pInventory[6].m_Type != -1 || lpObj->pInventory[7].m_Type != -1 || lpObj->pInventory[8].m_Type != -1 ||
		   lpObj->pInventory[9].m_Type != -1 || lpObj->pInventory[10].m_Type != -1|| lpObj->pInventory[11].m_Type != -1)
		{
			MsgNormal(aIndex,"[GReset]: You need Empty Inventory to GReset");
			return;
		}
	}
	/////////////////////
	//Выполнение Гранд ресета//
	/////////////////////
	lpObj->Money -= ZenMoney;
	lpObj->Level = 1;
	lpObj->Experience = 0;
	lpObj->NextExp = 100;
	ExUser[aIndex].PCPoint += ExConfig.GrandReset.AddPcPoint;
	if(ExConfig.GrandReset.AddForm == 2 || ExConfig.GrandReset.AddForm == 3)
	{
		lpObj->Strength = 25;
		lpObj->Dexterity = 25;
		lpObj->Vitality = 25;
		lpObj->Energy = 25;
		if(lpObj->Class == 4)
			lpObj->Leadership = 25;
	}
	//Поинта за ресет
	if(ExConfig.GrandReset.AddForm == 1 || ExConfig.GrandReset.AddForm == 2)
	{
		switch (lpObj->Class)
		{
			case 0: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsDW ;  break;
			case 1: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsDK ;  break;
			case 2: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsELF ; break;
			case 3: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsMG ;  break;
			case 4: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsDL ;  break;
			case 5: lpObj->LevelUpPoint = ( ExUser[aIndex].GReset + 1 ) * ExConfig.GrandReset.AddPointsSUM ; break;
		}
	}

	lpObj->LevelUpPoint += ExUser[aIndex].ExFreePoints;

	if(ExConfig.GrandReset.AddForm == 3)
	{
		lpObj->LevelUpPoint = 0;
	}

	ExUser[aIndex].Reset = 0;
	ExUser[aIndex].GReset++;
#ifdef _GRAND_RESET_WCOIN_
	if(ExConfig.GrandReset.AddWcoin > 0)
	{
#ifdef _h3yShOk_
		int dwCost = ExConfig.GrandReset.AddWcoin;
#else
		int dwCost = ExConfig.GrandReset.AddWcoin * (ExUser[aIndex].GReset);
#endif
		GDRequestWcoinInfoLoad (lpObj,dwCost,1);
	}
#endif
	
	ExFireCracker(aIndex, lpObj->X, lpObj->Y);
	gObjCloseSet(aIndex, 1);
	LogAddTD("[GrandResetSystem] Accaunt: %s , Name: %s , GrandReset: %d",lpObj->AccountID, lpObj->Name,ExUser[aIndex].GReset);
}