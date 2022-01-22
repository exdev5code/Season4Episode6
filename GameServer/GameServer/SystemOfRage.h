#include "StdAfx.h"
#include "user.h"

#ifdef _SYSTEM_OF_RAGE_

#define R_MAX_SKILL 36
#define R_MAX_LEVEL 10000

#define RAGE_DEBUG	1

#define RAGE_SYSTEM_DIR "..\\ExTeam\\RageSystem.ini"

//#define DEBUG_RAGE 0

struct RageUser
{
	int InfoLoad;
	int rLevel;
	int rPoints;
	int rExperience;
	int NextrExperience;	//HZ
	//---
	int Damage;	//
	int FreePoints;//
	int SummonPet;//
	int WingsDamagePlus;//
	int FinalMana;//
	int IgnoreDefence;//
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	//--- 2
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	//--- 3
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	//--- 4
	int ExellentDamage;//
	int CriticalDamage;//
};

enum RageSkillID
{
	eSkill1 = 1,
	eSkill2,
	eSkill3,
	eSkill4,
	eSkill5,
	eSkill6,
	eSkill7,
	eSkill8,
	eSkill9,
	eSkill10,
	eSkill11,
	eSkill12,
	eSkill13,
	eSkill14,
	eSkill15,
	eSkill16,
	eSkill17,
	eSkill18,
	eSkill19,
	eSkill20,
	eSkill21,
	eSkill22,
	eSkill23,
	eSkill24,
	eSkill25,
	eSkill26,
	eSkill27,
	eSkill28,
	eSkill29,
	eSkill30,
	eSkill31,
	eSkill32,
	eSkill33,
	eSkill34,
	eSkill35,
};

struct RageSkill
{
	char Name[50];
	int StartDamage;
	int MaxPoint;
	bool Percent;
	int PointNext;
};

// ----

struct ClickSend
{
	PBMSG_HEAD2 h;
	BYTE Click;
	WORD SkillID;
};

struct sRageUserSend
{
	PBMSG_HEAD2 h;
	int rLevel;
	int rPoints;
	int rExperience;
	//---
	int Damage;	//
	int FreePoints;//
	int SummonPet;//
	int WingsDamagePlus;//
	int FinalMana;//
	int IgnoreDefence;//
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	//--- 2
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	//--- 3
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;//
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	//--- 4
	int ExellentDamage;//
	int CriticalDamage;//
	//---
	int NextExp;
};

struct RageExpSend
{
	PBMSG_HEAD2 h;
	int Level;
	int Point;
	int Exp;
	int NextExp;
};

struct sRageTabSend
{
	PBMSG_HEAD2 h;
	int Num;
};

struct sConfigStruct
{
	PBMSG_HEAD2 h;
	BYTE SkillID;
	char Name[25];
	int Damage;
	int MaxPoint;
	int PointNext;
	BYTE Percent;
};

struct DSQuerySend
{
	PBMSG_HEAD h;

	int aIndex;
	char Name[11];
};

struct DSRageUser
{
	PBMSG_HEAD h;
	BYTE Result;
	char Name[11];
	int aIndex;
	int rLevel;
	int rPoints;
	int rExperience;
	//---
	int Damage;	//
	int FreePoints;//
	int SummonPet;//
	int WingsDamagePlus;//
	int FinalMana;//
	int IgnoreDefence;//
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	//--- 2
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	//--- 3
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	//--- 4
	int ExellentDamage;//
	int CriticalDamage;//
};


struct DSRageUserSAVE
{
	PBMSG_HEAD h;
	char Name[11];
	int rLevel;
	int rPoints;
	int rExperience;
	int Damage;	//
	int FreePoints;//
	int SummonPet;//
	int WingsDamagePlus;//
	int FinalMana;//
	int IgnoreDefence;//
	int ResetLevel;//
	int Teleport;//
	int CriticalDamageRate;//
	int AbsordDamage;//
	int PetDamageBonus;//
	int FinalLife;//
	int Strength;//
	int DefenceRate;//
	int FireDamage;//
	int Energy;//
	int Agility;//
	int DoubleDamage;//
	int FinalSD;//
	int FinalDefence;//
	int ZenDrop;//
	int GuildBonus;//
	int ReflectDamage;//
	int ExellentDamageRate;//
	int PvPBonusPlus;
	int MinDefence;//
	int Experience;//
	int StartSD;//
	int PartyBonus;//
	int IceDamage;//
	int DistanceAttack;//
	int AttackRate;//
	int WeaponBonus;//
	int ExellentDamage;//
	int CriticalDamage;//
};

class cSystemOfRage
{
private:
	bool Enable;
	int MaxLevel;
	int AddExp;

	int TeleportMap;
	int TeleportX;
	int TeleportY;

	int CreateMob;
	int rPointLvl;

	int NextExp;
	int MobExpLvL;

public:
	void Load();
	void LoadSkill(int ID, char *cName, int a1, int a2, int NextPoint, bool Percent);

	void FilterSkill(int aIndex, int SkillID);
	int ReturnPoint(int aIndex, int SkillID);
	int ReturnCalc(int aIndex, int SkillID, int Pw);
	

	void DataRecv(ClickSend *aRecv, int aIndex);
	void RecvActiveSkill(sRageTabSend *aRecv, int aIndex);

	void CalcCharacter(int aIndex);
	void CalcStats(int aIndex);

	void SummonPetSkill(int aIndex);
	void TeleportSkill(int aIndex);
	void DropZen (int aIndex, float & money);
	void ExpFunction(int aIndex, __int64 & exp);
	void AttackDefenceRate(int aIndex, int Target, float &Attack, float &Defence);
	void ExlCritDamage(int aIndex, int effect, int &AttackDamage);
	void AttackDamageRG(LPOBJ lpObj, LPOBJ lpTarget, int &dmg, bool bDamageReflect);

	void ExpFunction(LPOBJ lpObj, LPOBJ TargetObj);

	void SendUser(int aIndex);

	void ConfigSend(int aIndex);

	void SendDataServer(int aIndex,char * NAme);
	void RecvDSProtocol(DSRageUser *aRecv);

	void RageConnect(int aIndex);

	void SendSaveData(int aIndex);
	void JewelsDropRate(LPOBJ lpObj, LPOBJ lpMobObj);

	void RageClientSend();

	// ----
	RageUser rUser[OBJMAX];
	RageSkill rSkill[R_MAX_SKILL];
};
extern cSystemOfRage gSystemOfRage;

#endif