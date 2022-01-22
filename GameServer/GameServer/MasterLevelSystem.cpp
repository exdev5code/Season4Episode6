// MasterLevelSystem.cpp: implementation of the CMasterLevelSystem class.
//	GS-N	1.00.90	JPN	0xXXXXXXXX	- Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MasterLevelSystem.h"
#include "..\include\readscript.h"
#include "GameMain.h"
#include "LogProc.h"
#include "ObjCalCharacter.h"
#include "protocol.h"
#include "DSProtocol.h"
#include "user.h"
#include "DBSockMng.h"
#include "..\common\winutil.h"

CMasterLevelSystem g_MasterLevelSystem;

CMasterLevelSystem::CMasterLevelSystem()
{

}

CMasterLevelSystem::~CMasterLevelSystem() 
{

}

void CMasterLevelSystem::ReadCommonServerInfo()
{
	this->m_iML_MinMonsterKillLevel = GetPrivateProfileInt("GameServerInfo","ML_MinMonsterKillLevel",110, gDirPath.GetNewPath("commonserver.cfg"));

	char szTemp[10] = {0};//Season 4.5 addon

	GetPrivateProfileString("GameServerInfo", "ML_AddExperience", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));//Season 4.5 addon
	this->m_fML_AddExpericence = atof(szTemp);	//Season 4.5 addon
	LogAddTD("MasterLevel Info Set MinMonsterKillLevel:%d, AddExpRate:%d", this->m_iML_MinMonsterKillLevel, this->m_fML_AddExpericence);
}

void CMasterLevelSystem::SetExperienceTable()
{
	this->m_i64ML_ExperienceTable[0] = 0;

	__int64 local3 = 0;
	__int64 local5 = 0;
	__int64 local7 = 0;

	for(int local8 = 1;local8 < MAX_MASTER_LEVEL;local8++)
	{
		local3 = local8+400;
		local7 = (local3+9)*local3*local3*10;
		local5 = local3-255;
		local7 += (local5+9)*local5*local5*1000;
		local7 = (local7-3892250000)/2;

		this->m_i64ML_ExperienceTable[local8] = local7;
	}

	LogAddTD("Master level system exp table setting is complete");
}

void CMasterLevelSystem::CalculateNexExp(LPOBJ lpObj)
{
	int MasterLevel = lpObj->MLevel + 1;
	lpObj->MLNextExp = this->m_i64ML_ExperienceTable[MasterLevel];
}

int CMasterLevelSystem::MasterLevelUp(LPOBJ lpObj, __int64 Experience)
{
	if(this->CheckIsMasterLevelCharacter(lpObj) == FALSE)
	{
		return FALSE;
	}

	if(lpObj->MLevel >= 200)
	{
		GCServerMsgStringSend(lMsg.Get(1136), lpObj->m_Index, 1); //You have reached maximum level?
		return FALSE;
	}

	Experience = (__int64)(Experience * this->m_fML_AddExpericence);

	if(lpObj->m_MLPassiveSkill.m_iML_IncreaseExpRate > 0) //Master Skill to increase EXP
	{
		Experience += Experience * lpObj->m_MLPassiveSkill.m_iML_IncreaseExpRate / 100;
	}

	if(Experience > 0)
	{
		gObjSetExpPetItem(lpObj->m_Index, Experience);
		LogAddTD("ML Experience : Map[%d]-(%d,%d) [%s][%s](%d) %I64d %I64d", lpObj->MapNumber, lpObj->X, lpObj->Y, lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLExp, Experience);

		if(lpObj->MLExp + Experience < lpObj->MLNextExp)
		{
			lpObj->MLExp += Experience;
		}
		else
		{
			Experience = 0;
			lpObj->MLExp = lpObj->MLNextExp;
			lpObj->MLevel++;
			lpObj->MLPoint++;
			gObjCalCharacter(lpObj->m_Index);
			lpObj->MaxLife += DCInfo.DefClass[ lpObj->Class ].LevelLife;
			lpObj->MaxMana += DCInfo.DefClass[ lpObj->Class ].LevelMana;
			lpObj->Life = lpObj->AddLife + lpObj->MaxLife;
			lpObj->Mana = lpObj->AddMana + lpObj->MaxMana;
			gObjCalcShieldPoint(lpObj);
			lpObj->iShield = lpObj->iMaxShield + lpObj->iAddShield;
			this->CalculateNexExp(lpObj);
			gObjCalcMaxLifePower(lpObj->m_Index);
			gObjSetBP(lpObj->m_Index);
			//GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);	//Disable Master LEvel Up
			this->GCSendMasterLevelUpEffect(lpObj);
			GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield);
			GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		}

		GCKillPlayerExtSend(lpObj->m_Index, (WORD)-1, Experience, 0, 0);
	}

	return 1;
}

int CMasterLevelSystem::CheckIsMasterLevelCharacter(LPOBJ lpObj)
{
	if(lpObj == NULL)
	{
		return 0;
	}

	if(lpObj->MLInfoLoad == 0)
	{
		return 0;
	}

	if(lpObj->Level >= 400 && lpObj->ChangeUP3rd == 1)
	{
		return 1;
	}

	return 0;
}

int CMasterLevelSystem::CheckMinMonsterLevel(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(this->CheckIsMasterLevelCharacter(lpObj) != FALSE)
	{
		if(lpTargetObj->Level < this->m_iML_MinMonsterKillLevel)
		{
			return 0;
		}
	}
	return 1;
}

__int64 CMasterLevelSystem::GetLevelExperienceTable(int Level)
{
	return m_i64ML_ExperienceTable[Level];
}

int CMasterLevelSystem::CheckMasterLevelCharacterPkLevel(LPOBJ lpObj)
{
	if(CheckIsMasterLevelCharacter(lpObj) == FALSE)
	{
		return -1;
	}

	int loc2 = 0;

	if(lpObj->m_PK_Level <= 3)
	{
		loc2 = 7;
	}
	else if(lpObj->m_PK_Level == 4)
	{
		loc2 = 20;
	}
	else if(lpObj->m_PK_Level == 5)
	{
		loc2 = 30;
	}
	else if(lpObj->m_PK_Level >= 6)
	{
		loc2 = 40;
	}

	return loc2;
}

int CMasterLevelSystem::CheckMasterLevelCharacterMoneyLevel(LPOBJ lpObj)
{
	if(CheckIsMasterLevelCharacter(lpObj) == FALSE)
	{
		return -1;
	}

	return 4;
}

struct PMSG_REQ_ML_INFO_LOAD
{
	PBMSG_HEAD h;
	int iUserIndex;
	char chCharacterName[11];
};

void CMasterLevelSystem::GDRequestMasterLevelInfoLoad(LPOBJ lpObj)
{
	if(lpObj->MLInfoLoad == 1)
	{
		return;
	}

	PMSG_REQ_ML_INFO_LOAD pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x30, sizeof(pMsg));

	pMsg.iUserIndex = lpObj->m_Index;
	memcpy(pMsg.chCharacterName, lpObj->Name, 10);
	pMsg.chCharacterName[10] = '\0';

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	LogAddTD("[%s][%s] Request master level info to DB", lpObj->AccountID, lpObj->Name);
}

struct PMSG_ANS_ML_INFO_LOAD
{
	PBMSG_HEAD h;
	BYTE Result; //3
	int Index; //4
	char szName[11];
	short MLevel; //14
	__int64 MLExp; //
	__int64 MLNextExp; //
	short MLPoint; //28 Should be int not short
};

void CMasterLevelSystem::DGRequestMasterLevelInfoLoad(LPBYTE aRecv)
{
	if(aRecv == NULL)
	{
		return;
	}

	PMSG_ANS_ML_INFO_LOAD * pRecv = (PMSG_ANS_ML_INFO_LOAD *)aRecv;

	if(!gObjIsConnectedGP(pRecv->Index))
	{
		return;
	}

	int aIndex = pRecv->Index;

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->MLInfoLoad == 1)
	{
		return;
	}

	if(pRecv->Result == 0)
	{
		LogAddTD("[%s][%s] MasterLevel Info Load Fail", lpObj->AccountID, lpObj->Name);
		return;
	}

	if(pRecv->Result == 1)
	{
		lpObj->MLInfoLoad = 1;

		if(pRecv->MLevel == NULL && pRecv->MLNextExp == NULL) //Zero
		{
			lpObj->MLevel = pRecv->MLevel;
			lpObj->MLExp = pRecv->MLExp;
			lpObj->MLNextExp = this->m_i64ML_ExperienceTable[1]; //:>D
			lpObj->MLPoint = pRecv->MLPoint;

			LogAddTD("[%s][%s] MasterLevel Info First Set [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]", lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLExp, lpObj->MLNextExp, lpObj->MLPoint);

			this->GDRequestMasterLevelInfoSave(lpObj);
		}
		else
		{
			lpObj->MLevel = pRecv->MLevel;
			lpObj->MLExp = pRecv->MLExp;
			lpObj->MLNextExp = pRecv->MLNextExp;
			lpObj->MLPoint = pRecv->MLPoint;

			LogAddTD("[%s][%s] Recv MasterLevel Info [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]", lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLExp, lpObj->MLNextExp, lpObj->MLPoint);
		}

		lpObj->MaxLife = DCInfo.DefClass[lpObj->Class].Life + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelLife  + ((lpObj->Vitality - DCInfo.DefClass[lpObj->Class].Vitality ) * DCInfo.DefClass[lpObj->Class].VitalityToLife);

		if(lpObj->Life > lpObj->MaxLife + lpObj->AddLife)//Season 4.5 changed
		{
			lpObj->Life = lpObj->MaxLife;
		}

		lpObj->MaxMana = DCInfo.DefClass[lpObj->Class].Mana + (lpObj->Level + lpObj->MLevel - 1) * DCInfo.DefClass[lpObj->Class].LevelMana  + ((lpObj->Energy - DCInfo.DefClass[lpObj->Class].Energy ) * DCInfo.DefClass[lpObj->Class].EnergyToMana);

		if(lpObj->Mana > lpObj->MaxMana + lpObj->AddMana)//Season 4.5 changed
		{
			lpObj->Mana = lpObj->MaxMana;
		}

		gObjCalcMaxLifePower(lpObj->m_Index);
		gObjSetBP(lpObj->m_Index);
		gObjCalcShieldPoint(lpObj);

		lpObj->iShield = lpObj->iMaxShield + lpObj->iAddShield; //wtf?

		LogAddTD("[%s][%s] Reset Max Value For MasterLevel [MaxLife:%d][MaxMana:%d][MaxSD:%d]", lpObj->AccountID, lpObj->Name, lpObj->MaxLife, lpObj->MaxMana, lpObj->iShield);

		this->GCSendMasterLevelWindowStatus(lpObj);

		GCReFillSend(lpObj->m_Index, (int)lpObj->Life, -1, 0, (int)lpObj->iShield);
		GCManaSend(lpObj->m_Index, (int)lpObj->Mana, -1, 0, (int)lpObj->BP);
		gObjCalCharacter(lpObj->m_Index);//Season 4.5 addon
	}
}

struct PMSG_REQ_ML_INFO_SAVE
{
	PBMSG_HEAD h;
	char chCharacterName[11];
	short MLevel;
	__int64 MLExp;
	__int64 MLNextExp;
	short MLPoint; //Should be int not short
};

void CMasterLevelSystem::GDRequestMasterLevelInfoSave(LPOBJ lpObj)
{
	if(lpObj->MLInfoLoad == 0)
	{
		return;
	}

	PMSG_REQ_ML_INFO_SAVE pMsg;

	pMsg.h.set((LPBYTE)&pMsg, 0x31, sizeof(pMsg));

	memcpy(pMsg.chCharacterName, lpObj->Name, 10);
	pMsg.chCharacterName[10] = '\0';

	pMsg.MLevel = lpObj->MLevel;
	pMsg.MLExp = lpObj->MLExp;
	pMsg.MLNextExp = lpObj->MLNextExp;
	pMsg.MLPoint = lpObj->MLPoint;

	cDBSMng.Send((char*)&pMsg, pMsg.h.size);

	LogAddTD("[%s][%s] MasterLevel Info Save [MLevel:%d][MLExp:%I64d][MLNextExp:%I64d][MLPoint:%d]", lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLExp, lpObj->MLNextExp, lpObj->MLPoint);
}

struct PMSG_ML_WINDOW_STATUS
{
	PBMSG_HEAD2 h; //0x00

	short MLevel; //0x04

	BYTE MLExpHHH; //0x06
	BYTE MLExpHHL; //0x07
	BYTE MLExpHLH; //0x08
	BYTE MLExpHLL; //0x09
	BYTE MLExpLHH; //0x0A
	BYTE MLExpLHL; //0x0B
	BYTE MLExpLLH; //0x0C
	BYTE MLExpLLL; //0x0D

	BYTE MLNextExpHHH; //0x0E
	BYTE MLNextExpHHL; //0x0F
	BYTE MLNextExpHLH; //0x10
	BYTE MLNextExpHLL; //0x11
	BYTE MLNextExpLHH; //0x12
	BYTE MLNextExpLHL; //0x13
	BYTE MLNextExpLLH; //0x14
	BYTE MLNextExpLLL; //0x15

	WORD MLPoint; // 0x16
	WORD MaxLife; // 0x18
	WORD MaxMana; // 0x1A
	WORD MaxShield; // 0x1C
	WORD MaxBP; // 0x1E
};

void CMasterLevelSystem::GCSendMasterLevelWindowStatus(LPOBJ lpObj)
{
	if(lpObj->MLInfoLoad == 0)
	{
		this->GDRequestMasterLevelInfoLoad(lpObj);
		return;
	}

	PMSG_ML_WINDOW_STATUS pMsg;
	
	PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x50, sizeof(pMsg));

	pMsg.MLevel = lpObj->MLevel;

	pMsg.MLExpHHH = SET_NUMBERH(SET_NUMBERHW(HIDWORD(lpObj->MLExp)));
	pMsg.MLExpHHL = SET_NUMBERL(SET_NUMBERHW(HIDWORD(lpObj->MLExp)));
	pMsg.MLExpHLH = SET_NUMBERH(SET_NUMBERLW(HIDWORD(lpObj->MLExp)));
	pMsg.MLExpHLL = SET_NUMBERL(SET_NUMBERLW(HIDWORD(lpObj->MLExp)));
	pMsg.MLExpLHH = SET_NUMBERH(SET_NUMBERHW(LODWORD(lpObj->MLExp)));
	pMsg.MLExpLHL = SET_NUMBERL(SET_NUMBERHW(LODWORD(lpObj->MLExp)));
	pMsg.MLExpLLH = SET_NUMBERH(SET_NUMBERLW(LODWORD(lpObj->MLExp)));
	pMsg.MLExpLLL = SET_NUMBERL(SET_NUMBERLW(LODWORD(lpObj->MLExp)));

	pMsg.MLNextExpHHH = SET_NUMBERH(SET_NUMBERHW(HIDWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpHHL = SET_NUMBERL(SET_NUMBERHW(HIDWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpHLH = SET_NUMBERH(SET_NUMBERLW(HIDWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpHLL = SET_NUMBERL(SET_NUMBERLW(HIDWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpLHH = SET_NUMBERH(SET_NUMBERHW(LODWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpLHL = SET_NUMBERL(SET_NUMBERHW(LODWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpLLH = SET_NUMBERH(SET_NUMBERLW(LODWORD(lpObj->MLNextExp)));
	pMsg.MLNextExpLLL = SET_NUMBERL(SET_NUMBERLW(LODWORD(lpObj->MLNextExp)));

	pMsg.MLPoint = lpObj->MLPoint;
	pMsg.MaxLife = (WORD)(lpObj->MaxLife+lpObj->AddLife);
	pMsg.MaxMana = (WORD)(lpObj->MaxMana+lpObj->AddMana);
	pMsg.MaxShield = lpObj->iMaxShield+lpObj->iAddShield;
	pMsg.MaxBP = lpObj->MaxBP+lpObj->AddBP;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
}

struct PMSG_ML_LEVEL_UP
{
    PBMSG_HEAD2 h;
	WORD MasterLevel;
	WORD GainPoint;
	WORD MLPoint;
	WORD MaxPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxShield;
    WORD MaxBP;
};

void CMasterLevelSystem::GCSendMasterLevelUpEffect(LPOBJ lpObj)
{
	PMSG_ML_LEVEL_UP pMsg;

	PHeadSubSetB((LPBYTE)&pMsg, 0xF3, 0x51, 32); //webzen mistake for fixed size (should have the szName included)

	pMsg.MasterLevel = lpObj->MLevel;
	pMsg.GainPoint = 1;
	pMsg.MLPoint = lpObj->MLPoint;
	pMsg.MaxPoint = 200;
	pMsg.MaxLife = (WORD)(lpObj->AddLife + lpObj->MaxLife);
	pMsg.MaxMana = (WORD)(lpObj->AddMana + lpObj->MaxMana);
	pMsg.MaxShield = lpObj->iMaxShield + lpObj->iAddShield;
	pMsg.MaxBP = lpObj->MaxBP + lpObj->AddBP;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	GCSendEffectInfo(lpObj->m_Index, 0x10);

	LogAddTD("[%s][%s] Master Level Up :%d, MLPoint:%d/%d", lpObj->AccountID, lpObj->Name, lpObj->MLevel, lpObj->MLPoint, 200);
}