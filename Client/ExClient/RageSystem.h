#include "stdafx.h"
#include "Protocol.h"


#define R_MAX_SKILL 36

#define RAGE_SYSTEM_DIR ".\\Data\\ExTeam\\RageSystem.ini"

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

struct RageUser
{
	int rLevel;
	int rPoints;
	int rExperience;
	//---
	int Damage;
	int FreePoints;
	int SummonPet;
	int WingsDamagePlus;
	int FinalMana;
	int IgnoreDefence;
	int ResetLevel;
	int Teleport;
	int CriticalDamageRate;
	int AbsordDamage;
	int PetDamageBonus;
	//--- 2
	int FinalLife;
	int Strength;
	int DefenceRate;
	int FireDamage;
	int Energy;
	int Agility;
	int DoubleDamage;
	int FinalSD;
	int FinalDefence;
	int ZenDrop;
	int GuildBonus;
	//--- 3
	int ReflectDamage;
	int ExellentDamageRate;
	int PvPBonusPlus;
	int MinDefence;
	int Experience;
	int StartSD;
	int PartyBonus;
	int IceDamage;
	int DistanceAttack;
	int AttackRate;
	int WeaponBonus;
	//--- 4
	int ExellentDamage;
	int CriticalDamage;
};

struct RageSkill
{
	char Name[50];
	int StartDamage;
	int MaxPoint;
	bool Percent;
	int PointNext;
};

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


class RageSystem
{
public:
	RageSystem();
	void Load();
	void LoadImages();
	void LoadSkill(int ID, char *cName, int a1, int a2, int NextPoint, bool Percent);
	void rDrawInterface();
	void rDrawInfoText(int ID, int SkillID, int Point);
	void DrawDirection(int X, int Y, int Width, int Height);
	void DrawButtonActive(int ID, char * Text, int Poin, int SkID);

	void DrawIcon(int ID1, int SkillID, int &ClickCount, int Tree,int NextShow);

	void FilterSkill(int SkillID);

	void RageSend(short Skill);
	void RageRecv(ClickSend * Recv);
	void RecvStart(sRageUserSend * Recv);
	void RecvExp(RageExpSend * Recv);
	void RageTabSend(short index);

	void RecvConfig(sConfigStruct * Recv);
private:

	bool Enable;

	int NextExp;
	RageUser rUser;
	RageSkill rSkill[R_MAX_SKILL];

};
extern RageSystem gRageSystem;