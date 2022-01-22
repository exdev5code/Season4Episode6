// MasterLevelSystem.h: interface for the CMasterLevelSystem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MASTERLEVELSYSTEM_H
#define MASTERLEVELSYSTEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "user.h"

#define MAX_MASTER_LEVEL	201 //Should be 200

class CMasterLevelSystem  
{
public:
	CMasterLevelSystem();
	virtual ~CMasterLevelSystem();

	void ReadCommonServerInfo();
	void SetExperienceTable();
	void CalculateNexExp(LPOBJ lpObj);
	int MasterLevelUp(LPOBJ lpObj, __int64 Experience);
	int CheckMinMonsterLevel(LPOBJ lpObj, LPOBJ lpTargetObj);
	__int64 GetLevelExperienceTable(int Level);
	int CheckMasterLevelCharacterPkLevel(LPOBJ lpObj);
	int CheckMasterLevelCharacterMoneyLevel(LPOBJ lpObj);
	void GDRequestMasterLevelInfoLoad(LPOBJ lpObj);
	void DGRequestMasterLevelInfoLoad(LPBYTE aRecv);
	void GDRequestMasterLevelInfoSave(LPOBJ lpObj);
	int CheckIsMasterLevelCharacter(LPOBJ lpObj);
	void GCSendMasterLevelWindowStatus(LPOBJ lpObj);
	void GCSendMasterLevelUpEffect(LPOBJ lpObj);

	__int64 m_i64ML_ExperienceTable[MAX_MASTER_LEVEL];

private:
	int m_iML_MinMonsterKillLevel; //0x650
	float m_fML_AddExpericence; //0x654
};

extern CMasterLevelSystem g_MasterLevelSystem;

#endif