#pragma once

#include "Sprodef.h"

#include ".\\DbSet\\DBConBase.h"

struct DSQuerySend
{
	PBMSG_HEAD h;

	int aIndex;
	char Name[11];
};

struct DSRageUserSAVE
{
	PBMSG_HEAD h;

	char Name[11];

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


class cRageSystem
{
public:
	cRageSystem();
	virtual ~cRageSystem();

	bool Connect();

	void DefaultRageChar(char *Name, int Type, int aIndex, int pIndex);
	void SendRageUser(DSQuerySend *Recv, int aIndex);
	void SaveRageSkill(DSRageUserSAVE*p);

	CQuery m_DBQuery;
};
