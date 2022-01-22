// SkillAdditionInfo.cpp: implementation of the CSkillAdditionInfo class.
//	GS	1.00.90	JPN		-	Completed
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SkillAdditionInfo.h"
#include "LogProc.h"
#include "Gamemain.h"

CSkillAdditionInfo g_SkillAdditionInfo;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkillAdditionInfo::CSkillAdditionInfo()
{
	this->Init();
}

CSkillAdditionInfo::~CSkillAdditionInfo()
{
	return;
}

void CSkillAdditionInfo::Init()
{
	this->m_iInfinityArrowSkillTime = 0; //4
	this->m_iInfinityArrowUseLevel = 0; //8

	this->m_iInfinityArrowMPConsumptionPlus0 = 0; //C
	this->m_iInfinityArrowMPConsumptionPlus1 = 0; //10
	this->m_iInfinityArrowMPConsumptionPlus2 = 0; //14
	this->m_iInfinityArrowMPConsumptionPlus3 = 0; //18 //Season4.5 add-on

	for(int i = 0; i <= 5; i++) //Master Soul Barrier Season 3
	{
		this->m_wSoulBarrierManaRateLevel[i] = 0;
	}
}

BOOL CSkillAdditionInfo::Load(LPSTR lpszFileName)
{
	if ( lpszFileName == NULL || strcmp(lpszFileName, "") == 0 )
	{
		LogAddTD("[Skill Addition Info] - File load error : File Name Error");
		return FALSE;
	}

	this->m_iInfinityArrowSkillTime = GetPrivateProfileInt("SkillInfo", "InfinityArrowSkillTime", 600, gDirPath.GetNewPath(lpszFileName)); 
	this->m_iInfinityArrowUseLevel = GetPrivateProfileInt("SkillInfo", "InfinityArrowUseLevel", 220, gDirPath.GetNewPath(lpszFileName)); 
	
	this->m_iInfinityArrowMPConsumptionPlus0 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus0", 0, gDirPath.GetNewPath(lpszFileName));
	this->m_iInfinityArrowMPConsumptionPlus1 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus1", 0, gDirPath.GetNewPath(lpszFileName));
	//this->m_iInfinityArrowMPConsumptionPlus2 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus2", 0, gDirPath.GetNewPath(lpszFileName));
	this->m_iInfinityArrowMPConsumptionPlus3 = GetPrivateProfileInt("SkillInfo", "InfinityArraowMPConsumptionPlus3", 0, gDirPath.GetNewPath(lpszFileName));

	LogAddTD("[Skill Addition Info] [Infinity Arrow] Skill Time[%d], UseLevel[%d], Arrow MP Consumption +0[%d] +1[%d] +2[%d] +3[%d]", this->m_iInfinityArrowSkillTime, this->m_iInfinityArrowUseLevel, this->m_iInfinityArrowMPConsumptionPlus0, this->m_iInfinityArrowMPConsumptionPlus1, this->m_iInfinityArrowMPConsumptionPlus2, this->m_iInfinityArrowMPConsumptionPlus3);

	this->m_bFireScreamSkill = GetPrivateProfileInt("SkillInfo", "FireScreamSkill", 1, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamExplosionAttackDistance = GetPrivateProfileInt("SkillInfo", "FireScreamExplosionAttackDistance", 1, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamExplosionRate = GetPrivateProfileInt("SkillInfo", "FireScreamExplosionRate", 300, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamMaxAttackCountSameSerial = GetPrivateProfileInt("SkillInfo", "FireScreamMaxAttackCountSameSerial", 3, gDirPath.GetNewPath(lpszFileName));
	this->m_iFireScreamSerialInitCount = GetPrivateProfileInt("SkillInfo", "FireScreamSerialInitCount", 100, gDirPath.GetNewPath(lpszFileName));
	this->m_bCheckFireScreamSerial = GetPrivateProfileInt("SkillInfo", "CheckFireScreamSerial", 1, gDirPath.GetNewPath(lpszFileName));

	LogAddTD("[Skill Addition Info] [Fire Scream] Use(%d) : Explosion Distance(%d) - Rate(%d), MaxAttack_SameSerial(%d), SerialInitCount(%d), Check Serial(%d)", this->m_bFireScreamSkill, this->m_iFireScreamExplosionAttackDistance, this->m_iFireScreamExplosionRate, this->m_iFireScreamMaxAttackCountSameSerial, this->m_iFireScreamSerialInitCount, this->m_bCheckFireScreamSerial);

	//Season3 Addition
	this->m_wSoulBarrierManaRateLevel[0] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level0", 25, gDirPath.GetNewPath(lpszFileName));

	this->m_wSoulBarrierManaRateLevel[1] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level1", 25, gDirPath.GetNewPath(lpszFileName));
	this->m_wSoulBarrierManaRateLevel[2] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level2", 30, gDirPath.GetNewPath(lpszFileName));
	this->m_wSoulBarrierManaRateLevel[3] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level3", 35, gDirPath.GetNewPath(lpszFileName));
	this->m_wSoulBarrierManaRateLevel[4] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level4", 40, gDirPath.GetNewPath(lpszFileName));
	this->m_wSoulBarrierManaRateLevel[5] = GetPrivateProfileInt("SkillInfo", "SoulBarrierManaRate_Level5", 45, gDirPath.GetNewPath(lpszFileName));

	LogAddTD("[Skill Addition Info] [SoulBarrier Strengrhen] BaseSkill(Level0):%d, Level1:%d, 2:%d, 3:%d, 4:%d, 5:%d", this->m_wSoulBarrierManaRateLevel[0], this->m_wSoulBarrierManaRateLevel[1], this->m_wSoulBarrierManaRateLevel[2], this->m_wSoulBarrierManaRateLevel[3], this->m_wSoulBarrierManaRateLevel[4], this->m_wSoulBarrierManaRateLevel[5]);

	return TRUE;
}

short CSkillAdditionInfo::GetSoulBarrierManaRateLevel(int iLevel)
{
	if(iLevel < 0 || iLevel > 5)
	{
		return 20;
	}

	return this->m_wSoulBarrierManaRateLevel[iLevel];
}