// MasterSkillSystem.h: interface for the CMasterSkillSystem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MASTERSKILLSYSTEM_H
#define MASTERSKILLSYSTEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "user.h"

#define MAX_CHAR_SKILL_TREE	5
#define MAX_SKILL_TREE_INFO	9
#define MAX_TYPES	21

struct SkillRowsData
{
	BYTE Type;
	BYTE Index;
	BYTE Unknown;
	int Unk[MAX_SKILL_TREE_INFO-1][MAX_CHAR_SKILL_TREE-1];
};

struct PMSG_ML_SKILL_RECV_INFO
{
    PBMSG_HEAD2 h;
	int  MLSkill;
};

class CMasterSkillSystem  
{
public:
	CMasterSkillSystem();
	virtual ~CMasterSkillSystem();

	void Clear();
	void Load(LPSTR lpszFileName);
	void ClearPassiveSkill(LPOBJ lpObj);
	void AddPassiveSkill(LPOBJ lpObj, int Skill, int Point);
	int CheckMagicAdd(LPOBJ lpObj, int skill, int arg3);
	int FindPrimarySkill(LPOBJ lpObj, int skill);
	int CheckRequireStatus(int skill);
	int CheckPrimarySkill(LPOBJ lpObj, int skill);
	int GetSkillID(int skill);
	int MagicAdd(LPOBJ lpObj, int skill, int level);
	void CGMasterSkillSend(PMSG_ML_SKILL_RECV_INFO * lpMsg, int aIndex);
	BOOL RunningSkill(LPOBJ lpObj, int aTargetIndex, CMagicInf *lpMagic, BOOL bCombo, BYTE x, BYTE y, BYTE TargetPos);
	void WizardMagicDefense(LPOBJ lpObj, int aTargetIndex, CMagicInf * lpMagic);
	void SkillHealing(LPOBJ lpObj, int aTargetIndex, CMagicInf * lpMagic);
	void SkillWheel(LPOBJ lpObj, CMagicInf * lpMagic, int aTargetIndex, BOOL isCombo);
	void KnightSkillAddLife(LPOBJ lpObj, CMagicInf * lpMagic);
	BOOL SkillDarkHorseAttack(LPOBJ lpObj, int aTargetIndex, CMagicInf * lpMagic);
	BOOL SkillFireBurst(LPOBJ lpObj, int aTargetIndex, CMagicInf * lpMagic);

	//Season4 Addition
	BOOL TestSkill(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, int aTargetIndex, int dis, BOOL bVpAttack, int random, int delay);
	BOOL SkillSuddenIce(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, int aTargetIndex);
	int CalDistance(int x, int y, int x1, int y1);
	int GetAngle(int x, int y, int tx, int ty);
	void SkillFrustrum(int aIndex, float fangle, float tx, float ty);
	BOOL SkillKnightBlow(int aIndex, int aTargetIndex, CMagicInf * lpMagic, BOOL isCombo);
	void SkillBlowOfFury(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, int aTargetIndex, BOOL isCombo);
	void SkillDefense(int aIndex, int aTargetIndex, CMagicInf *lpMagic);
	void SkillAttack(int aIndex, int aTargetIndex, CMagicInf *lpMagic);
	void MaGumSkillDefenseDown(int aIndex, int aTargetIndex);
	void SkillPowerSlash(int aIndex, CMagicInf * lpMagic, BYTE x, BYTE y, BYTE TargetPos, int aTargetIndex);
	BOOL SkillFireScream(int aIndex, int aTargetIndex, CMagicInf * lpMagic);
	BOOL WeaponMagicDel(LPOBJ lpObj, BYTE aSkill, BYTE Level);
	BOOL WeaponMagicAdd(LPOBJ lpObj, BYTE aSkill, BYTE Level);
	BOOL GetWeaponMagicSearch(LPOBJ lpObj, int pos);

private:
	int m_iClassSkillData[MAX_SKILL_TREE_INFO][MAX_CHAR_SKILL_TREE]; //0xB4
	int m_iClassSkillCount[MAX_SKILL_TREE_INFO]; //0xD8
	SkillRowsData	m_SkillData[MAX_TYPES]; //
};

extern CMasterSkillSystem g_MasterSkillSystem;

#endif