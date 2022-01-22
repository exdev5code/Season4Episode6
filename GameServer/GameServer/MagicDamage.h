#ifndef MAGICDAMAGE_H
#define MAGICDAMAGE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_SKILL			600
#define MAX_REQ_SKILL_STATUS	3

#include "..\common\classdef.h"


enum eSkillType
{
	AT_SKILL_POISON = 0x1,
	AT_SKILL_METEO = 0x2,
	AT_SKILL_THUNDER = 0x3,
	AT_SKILL_FIREBALL = 0x4,
	AT_SKILL_FLAME = 0x5,
	AT_SKILL_TELEPORT = 0x6,
	AT_SKILL_SLOW = 0x7,
	AT_SKILL_STORM = 0x8,
	AT_SKILL_EVIL = 0x9,
	AT_SKILL_HELL = 0xa,
	AT_SKILL_POWERWAVE = 0xb,
	AT_SKILL_FLASH = 0xc,
	AT_SKILL_BLAST = 0xd,
	AT_SKILL_INFERNO = 0xe,
	AT_SKILL_TARGET_TELEPORT = 0xf,
	AT_SKILL_MAGICDEFENSE = 0x10,
	AT_SKILL_ENERGYBALL = 0x11,
	AT_SKILL_BLOCKING = 0x12,
	AT_SKILL_SWORD1 = 0x13,
	AT_SKILL_SWORD2 = 0x14,
	AT_SKILL_SWORD3 = 0x15,
	AT_SKILL_SWORD4 = 0x16,
	AT_SKILL_SWORD5 = 0x17,
	AT_SKILL_CROSSBOW = 0x18,
	AT_SKILL_BOW = 0x19,
	AT_SKILL_HEALING = 0x1a,
	AT_SKILL_DEFENSE = 0x1b,
	AT_SKILL_ATTACK = 0x1c,
	AT_SKILL_CALLMON1 = 0x1e,
	AT_SKILL_CALLMON2 = 0x1f,
	AT_SKILL_CALLMON3 = 0x20,
	AT_SKILL_CALLMON4 = 0x21,
	AT_SKILL_CALLMON5 = 0x22,
	AT_SKILL_CALLMON6 = 0x23,
	AT_SKILL_CALLMON7 = 0x24,
	AT_SKILL_WHEEL = 0x29,
	AT_SKILL_BLOWOFFURY = 0x2a,
	AT_SKILL_STRIKE = 0x2b,
	AT_SKILL_KNIGHTSPEAR = 0x2f,
	AT_SKILL_KNIGHTADDLIFE = 0x30,
	AT_SKILL_KNIGHTDINORANT = 0x31,
	AT_SKILL_ELFHARDEN = 0x33,
	AT_SKILL_PENETRATION = 0x34,
	AT_SKILL_DEFENSEDOWN = 0x37,
	AT_SKILL_SWORD6 = 0x38,
	AT_SKILL_5CROSSBOW = 0x36,
	AT_SKILL_EXPPOISON = 0x26,
	AT_SKILL_EXPICE = 0x27,
	AT_SKILL_EXPHELL = 0x28,
	AT_SKILL_EXPHELL_START = 0x3a,
	AT_SKILL_IMPROVE_AG_REFILL = 0x35,
	AT_SKILL_DEVILFIRE = 0x32,
	AT_SKILL_COMBO = 0x3b,
	AT_SKILL_SPEAR = 0x3c,
	AT_SKILL_FIREBURST = 0x3d,
	AT_SKILL_DARKHORSE_ATTACK = 0x3e,
	AT_SKILL_RECALL_PARTY = 0x3f,
	AT_SKILL_ADD_CRITICALDAMAGE = 0x40,
	AT_SKILL_ELECTRICSPARK = 0x41,
	AT_SKILL_LONGSPEAR = 0x42,
	AT_SKILL_RUSH = 0x2c,
	AT_SKILL_JAVALIN = 0x2d,
	AT_SKILL_DEEPIMPACT = 0x2e,
	AT_SKILL_ONE_FLASH = 0x39,
	AT_SKILL_DEATH_CANNON = 0x49,
	AT_SKILL_SPACE_SPLIT = 0x4a,
	AT_SKILL_BRAND_OF_SKILL = 0x4b,
	AT_SKILL_STUN = 0x43,
	AT_SKILL_REMOVAL_STUN = 0x44,
	AT_SKILL_ADD_MANA = 0x45,
	AT_SKILL_INVISIBLE = 0x46,
	AT_SKILL_REMOVAL_INVISIBLE = 0x47,
	AT_SKILL_REMOVAL_MAGIC = 0x48,
	AT_SKILL_FENRIR_ATTACK = 0x4c,
	AT_SKILL_INFINITY_ARROW = 0x4d,
	AT_SKILL_FIRESCREAM = 0x4e,
	AT_SKILL_EXPLOSION = 0x4f,
	AT_SKILL_SUMMON = 0xc8,
	AT_SKILL_IMMUNE_TO_MAGIC = 0xc9,
	AT_SKILL_IMMUNE_TO_HARM = 0xca,
};


class CMagicDamage
{

private:

	int Get(int skill);
	void SetML(int iSkill, int SkillRank, int SkillGroup, int rMLPoint, int rAG, int rShield, short Duration, int rStrength, int rDexterity);
	void SetEx(int iSkill, int iSkillUseType, int iSkillBrand, int iKillCount, int* pReqStatus);
	void Set(char* name, int skill, int damage,  int rlevel,  int mana,  int bp,  int dis, int Attr,  int iSkillType, BYTE* ReqClass, int rEnergy, int rLeadership, int rdelay);
	int CheckSkillAttr(int skill, int attr);

public:

	CMagicDamage();
	virtual ~CMagicDamage();

	void Init();
	void LogSkillList(char* Buffer, int iSize);
	void LogSkillList(char* filename);
	void LogSkillNameList(char* Buffer, int iSize);
	void LogSkillNameList(char* filename);
	int SkillGet(int skill);
	int SkillGetMana(int skill);
	int SkillGetRequireEnergy(int skill);
	int SkillGetRequireLevel(int skill);
	int SkillGetRequireClass(int Cclass, int ChangeUP, int ChangeUP3rd, int skill);
	int SkillGetBP(int skill);
	int GetSkillAttr(int skill);
	int GetskillRequireLeadership(int skill);
	int GetDelayTime(int skill);
	int GetSkillType(int iSkill);
	int CheckStatus(int iSkill, int iGuildStatus);
	int CheckBrandOfSkill(int iSkill);
	int CheckKillCount(int iSkill, int iKillCount);
	int GetSkillDistance(int skill);
	int GetSkillReqMLPoint(int skill);
	int GetSkillReqStrength(int skill);
	int GetSkillReqDexterity(int skill);
	int GetSkillReqBrandOfSkill(int skill);
	int GetSkillUseType(int skill);
	int GetSkillReqLevel(int skill);
	int GetSkillGroup(int skill);
	int GetSkillRank(int skill);

private:

	int m_Damage[MAX_SKILL];	// 4
	char m_Name[MAX_SKILL][50];	// 960
	BYTE m_rLevel[MAX_SKILL];	// 7E94
	WORD m_Mana[MAX_SKILL];	// 8344
	BYTE m_Distance[MAX_SKILL];	// 859C
	int m_RequireEnergy[MAX_SKILL];	// 87F4
	BYTE m_RequireClass[MAX_SKILL][MAX_TYPE_PLAYER];	// 0x9604
	int m_RequireLevel[MAX_SKILL];	// 0x9F64
	int m_RequireLeadership[MAX_SKILL];	// 0xA8C4
	int m_Delay[MAX_SKILL];	// 0xB224
	WORD m_BrainPower[MAX_SKILL];	//0xB6D4
	int m_Attr[MAX_SKILL];	//0xC034
	int m_iSkillType[MAX_SKILL];	//0xC994
	int m_iSkillUseType[MAX_SKILL];	//0xD2F4
	int m_iSkillBrand[MAX_SKILL];	//0xDC54
	int m_iKillCount[MAX_SKILL];	//0xE5B4
	int m_iRequireStatus[MAX_SKILL][MAX_REQ_SKILL_STATUS];	//0xEF14

    short m_sSkillRank[MAX_SKILL]; //0x10B34
    short m_sSkillGroup[MAX_SKILL]; //0x10FE4
    short m_sReqMLPoint[MAX_SKILL]; //0x11494

	//Unused o.O
    short m_sReqAG[MAX_SKILL]; //0x11944
    short m_sReqShield[MAX_SKILL]; //0x11DF4
    short m_sDuration[MAX_SKILL]; //0x122A4

    short m_sReqStrength[MAX_SKILL]; //0x12754
    short m_sReqDexterity[MAX_SKILL]; //0x12C04

	enum 
	{
		SKILL_TYPE_NONE = -1,
		SKILL_TYPE_PHYSICS = 0,
		SKILL_TYPE_MAGIC = 1,
	};

};

extern CMagicDamage MagicDamageC; //0x03AFFAC8

#endif