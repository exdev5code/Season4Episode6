// CharDBSet.h: interface for the CCharDBSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
#define AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\Sprodef.h"
#include "..\\StdAfx.h"

typedef struct
{
	int registry;
	char AccountID[MAX_IDSTRING+1];
	char Name[MAX_IDSTRING+1];
	BYTE Class;
	int Level;
	int LevelUpPoint;
	int Experience;
	int NextExperience;
	int Money;
	short Strength;
	short Dexterity;
	short Vitality;
	short Energy;
	short Leadership;
	WORD ChatLitmitTime;
	float Life;
	float MaxLife;
	float Mana;
	float MaxMana;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE dbInventory[MAX_DBINVENTORY];
	BYTE dbMagicList[MAX_DBMAGIC];
	BYTE dbQuest[MAX_QUEST];
	BYTE MapNumber;
	BYTE MapX;
	BYTE MapY;
	BYTE Dir;
	BYTE CtlCode;
	BYTE DbVersion;
	int FruitPoint;
	int PCPoint;	//ExAdd
	int Reset;		//ExAdd
	int GReset;		//ExAdd
	int ExFreePoints;	//ExAdd
	int ExQuestNum;
	int ExQuestKill;
	int ExCred;
	int PremiumTime;
	int ChatBanTime;
	int NoobTime;
	int OffAfk;
	int VipTime;
	int CR;
	int BMQuest_num;
	int BMQuest_kill;
	int BMQuest_start;
	int BMDamageReflect;
	int BMDamage;
	int BMDefense;
	int BMCriticalDamage;
	int BMExcelentDamage;
	int BMLife;
	int ChaosBank;
	int BlessBank;
	int SoulBank;
	int LifeBank;
	DWORD MTDate;
}CharacterInfo_Struct, *LPCharacterInfo_Struct;

struct PMSG_ANS_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserID[MAX_IDSTRING+1];
	BYTE btResult;
};

struct PMSG_REQ_USERID
{
	PBMSG_HEAD2 head;
	DWORD dwKey;
	DWORD dwUserGUID;
	char chUserName[MAX_IDSTRING+1];
};

struct SDHP_CHANGE_NAME_RESULT
{
	PBMSG_HEAD h;
	int aIndex;
	char AccountId[MAX_IDSTRING];
	char OldName[MAX_IDSTRING];
	char NewName[MAX_IDSTRING];
	BYTE btResult;
};

//#ifdef _RAGE_SYSTEM_
//
//struct DSQuerySend
//{
//	PBMSG_HEAD h;
//
//	int aIndex;
//	char Name[11];
//};
//
//struct DSRageUserSAVE
//{
//	PBMSG_HEAD h;
//
//	char Name[11];
//
//	int rLevel;
//	int rPoints;
//	int rExperience;
//	//---
//	int Damage;	//
//	int FreePoints;//
//	int SummonPet;//
//	int WingsDamagePlus;//
//	int FinalMana;//
//	int IgnoreDefence;//
//	int ResetLevel;//
//	int Teleport;//
//	int CriticalDamageRate;//
//	int AbsordDamage;//
//	int PetDamageBonus;//
//	//--- 2
//	int FinalLife;//
//	int Strength;//
//	int DefenceRate;//
//	int FireDamage;//
//	int Energy;//
//	int Agility;//
//	int DoubleDamage;//
//	int FinalSD;//
//	int FinalDefence;//
//	int ZenDrop;//
//	int GuildBonus;//
//	//--- 3
//	int ReflectDamage;//
//	int ExellentDamageRate;//
//	int PvPBonusPlus;
//	int MinDefence;//
//	int Experience;//
//	int StartSD;//
//	int PartyBonus;//
//	int IceDamage;//
//	int DistanceAttack;//
//	int AttackRate;//
//	int WeaponBonus;//
//	//--- 4
//	int ExellentDamage;//
//	int CriticalDamage;//
//};
//
//struct DSRageUser
//{
//	PBMSG_HEAD h;
//
//	int aIndex;
//
//	int rLevel;
//	int rPoints;
//	int rExperience;
//	//---
//	int Damage;	//
//	int FreePoints;//
//	int SummonPet;//
//	int WingsDamagePlus;//
//	int FinalMana;//
//	int IgnoreDefence;//
//	int ResetLevel;//
//	int Teleport;//
//	int CriticalDamageRate;//
//	int AbsordDamage;//
//	int PetDamageBonus;//
//	//--- 2
//	int FinalLife;//
//	int Strength;//
//	int DefenceRate;//
//	int FireDamage;//
//	int Energy;//
//	int Agility;//
//	int DoubleDamage;//
//	int FinalSD;//
//	int FinalDefence;//
//	int ZenDrop;//
//	int GuildBonus;//
//	//--- 3
//	int ReflectDamage;//
//	int ExellentDamageRate;//
//	int PvPBonusPlus;
//	int MinDefence;//
//	int Experience;//
//	int StartSD;//
//	int PartyBonus;//
//	int IceDamage;//
//	int DistanceAttack;//
//	int AttackRate;//
//	int WeaponBonus;//
//	//--- 4
//	int ExellentDamage;//
//	int CriticalDamage;//
//};
//
//#endif

class CCharDBSet  
{
public:
	CCharDBSet();
	virtual ~CCharDBSet();

	BOOL Connect();
	int DeleteCharacter(char* AccoundID, char* CharacterID);
	int DeleteCharacter_DregInfo(char* CharacterID);
	int CreateCharacter(CString accountId, CString Name, BYTE Class);
	BOOL DefaultCharacterCreate(BYTE classskin);
	BOOL DefaultCreateCharacterInsert(LPCharacterInfo_Struct lpObj);
	BOOL DefaultCreateCharacterAllDelete();
	BYTE SaveCharacter(char* Name, LPCharacterInfo_Struct lpObj);
	BOOL GetCharacter(char* szAccountID, char* Name, LPCharacterInfo_Struct lpObj);
	BOOL GetCharacter(char* name);
	BOOL SaveItem(char* Name, BYTE* ItemBuf);
	int CharServerMove(char* Name);
	void SetSP_WZ_CreateCharacterGetVersion(int version);
	BOOL CheckSP_WZ_CreateCharacterGetVersion();
	BYTE CurCharNameSave(char* Name);
	int ChangeName(char* AccountId, char* OldName, char* NewName);
	int GetCharacterID(char* chName, char* chUserID);
	DWORD GetCharacterClass(char* chName);
//#ifdef _RAGE_SYSTEM_
//	void DefaultRageChar(char *Name, int Type, int aIndex, int pIndex);
//	void SendRageUser(DSQuerySend *Recv, int aIndex);
//	void SaveRageSkill(DSRageUserSAVE*p);
//#endif
public:
	int m_CreateCharacterVer;
	CQuery m_DBQuery;
};

#endif // !defined(AFX_CHARDBSET_H__BED5C4C4_EA0B_4126_A05F_9584C5F0E889__INCLUDED_)
