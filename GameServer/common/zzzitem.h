#ifndef ZZZITEM_H
#define ZZZITEM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_TYPE_PLAYER 6
#define MAX_ITEM_LEVEL	15
#define MAX_TYPE_ITEMS 16
#define MAX_SUBTYPE_ITEMS 512
#define MAX_EXOPTION_SIZE 8
#define ITEMGET(x,y) ( (x)*MAX_SUBTYPE_ITEMS + (y))
#define MAX_PET_LEVEL 50
#define MAX_ITEM_DURABILITY	255
#define MAX_ITEMS (MAX_TYPE_ITEMS*MAX_SUBTYPE_ITEMS)
#define MAX_ITEM_SPECIAL_ATTRIBUTE 7

#define DBI_GET_TYPE(x) ( ((x)&((MAX_TYPE_ITEMS-1)<<8))>>4 )
#define DBI_GET_INDEX(x) ( (x) & 0xFF )
#define DBI_GET_LEVEL(x)  ( ((x)>>3)& MAX_ITEM_LEVEL )
#define DBI_GET_SKILL(x)  ( (x) >> 7 )
#define DBI_GET_LUCK(x)  ( ((x) >> 2) & 0x01)
#define DBI_GET_OPTION(x)  ( ( (x) ) & 0x03 )
#define DBI_GET_OPTION16(x) ( (x) & 0x40  )
#define DBI_GET_DINO_OPTION(x)  ( DBI_GET_OPTION16((x)) >> 4 )
#define DBI_GET_NOPTION(x)  ( (x) & 0x3F  )
#define DBI_GET_380OPTION(x) ( ((x) & 0x08) << 4  )
#define ITEM_GET_TYPE(x)  ( (x)/MAX_SUBTYPE_ITEMS  )
#define ITEM_GET_INDEX(x) ( (x)%MAX_SUBTYPE_ITEMS  )

/*#define DBI_TYPE			0
#define DBI_OPTION_DATA		1
#define DBI_DUR				2
#define DBI_SERIAL1			3
#define DBI_SERIAL2			4
#define DBI_SERIAL3			5
#define DBI_SERIAL4			6
#define DBI_NOPTION_DATA	7
#define DBI_SOPTION_DATA	8
#define DBI_OPTION380_DATA	9
#define DBI_JOH_DATA		10
*/

#define MAX_ITEM_INFO	7+5 //7 Common + 5 Socket

/*#define I_TYPE		0
#define I_OPTION	1
#define I_DUR		2
#define I_NOPTION	3
#define I_SOPTION	4
#define I_380OPTION	5
#define I_JOHOPTION	6
*/
#define ITEM_DUR_RANGE(x) (((x)<0)?FALSE:((x)>MAX_ITEM_DURABILITY-1)?FALSE:TRUE )

typedef struct
{
	char Name[32]; // 0
	BYTE HaveItemInfo; // 20  {A8}
	BYTE TwoHand;	// 21 {A9}
	BYTE Level; // 22
	BYTE Width;	// 23
	BYTE Height;	// 24
	char Serial; // 25
	BYTE OptionFlag; // 26
	BYTE MondownFlag; // 27 {AF}
	BYTE AttackSpeed; // 28 {B0}
	BYTE WalkSpeed; // 29 {B1}
	BYTE DamageMin; // 2A
	BYTE DamageMax; // 2B
	BYTE SuccessfulBlocking; // 2C
	BYTE Defense; // 2D
	BYTE MagicDefense; // 2E
	BYTE Speed;	// 2F
	BYTE Durability; // 30
	BYTE MagicDurability; // 31 {B9}
	BYTE AttackDur;	// 32 {BA}
	BYTE DefenceDur; // 33 {BC}
	WORD RequireStrength; // 34 {BD}
	WORD RequireDexterity; // 36 {BF}
	WORD RequireEnergy; // 38 {C1}
	WORD RequireLevel; // 3A {C3}
	WORD Value; // 3C {C5}
	BYTE RequireClass[MAX_TYPE_PLAYER]; // 3E {C7}
	BYTE Resistance[MAX_ITEM_SPECIAL_ATTRIBUTE]; // 44 {CD}
	WORD RequireVitality;	// 4C {D5}
	int BuyMoney; // 50  {D8}
	int MagicPW; // 54
	float RepaireMoneyRate;	// 58
	float AllRepaireMoneyRate; // 5C
	bool QuestItem;	// 60
	BYTE SetAttr; // 61
	BYTE ResistanceType;	// 62
	int ItemSlot; // 64
	int SkillType; // 68
	int RequireLeadership;	// 6C

}  ITEM_ATTRIBUTE, * LPITEM_ATTRIBUTE;

extern  ITEM_ATTRIBUTE ItemAttribute[MAX_ITEMS];



class CItem
{

public:

	CItem();

	void Convert(int type, BYTE Option1, BYTE Option2, BYTE Option3,BYTE Attribute2, BYTE SetOption, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex, BYTE DbVersion);
	void Value();
	void OldValue();
	int GetSize(int& w, int& h);
	void Clear();
	int IsItem();
	int IsSetItem();
	int GetAddStatType();
	void SetPetItemInfo(int petlevel, int petexp);
	int AddPetItemExp(int petexp);
	int DecPetItemExp(int percent);
	void PetValue();
	int PetItemLevelDown(int exp);
	int ItemDamageMin();
	int ItemDefense();
	int BookSpellDmg();
	int IsClass(char aClass, int ChangeUP, int ChangeUP3rd);
	LPSTR GetName();
	int GetLevel();
	void PlusSpecial(int* Value, int Special);
	void PlusSpecialPercent(int* Value, int Special, WORD Percent);
	void PlusSpecialPercentEx(int* Value, int SourceValue, int Special);
	void SetItemPlusSpecialStat(short* Value, int Special);
	int GetWeaponType();
	void PlusSpecialSetRing(BYTE* Value);
	DWORD GetNumber();
	int IsExtItem();
	int IsExtLifeAdd();
	int IsExtManaAdd();
	int IsExtDamageMinus();
	int IsExtDamageReflect();
	int IsExtDefenseSuccessfull();
	int IsExtMonsterMoney();
	int IsExtExcellentDamage();
	int IsExtAttackRate();
	int IsExtAttackRate2();
	int IsExtAttackSpeed();
	int IsExtMonsterDieLife();
	int IsExtMonsterDieMana();
	int IsWingOpGetOnePercentDamage();
	int IsWingOpGetManaToMoster();
	int IsDinorantReduceAttackDamaege();
	int IsFenrirIncLastAttackDamage();
	int IsFenrirDecLastAttackDamage();
	int IsFenrirSpecial();
	int IsThirdWingOpGetOnePercentDamage();
	int SimpleDurabilityDown(int iDur);
	int DurabilityDown(int dur, int aIndex);
	int DurabilityDown2(int dur, int aIndex);
	int NormalWeaponDurabilityDown(int defence, int aIndex);
	int BowWeaponDurabilityDown(int defence, int aIndex);
	int StaffWeaponDurabilityDown(int defence, int aIndex);
	int ArmorDurabilityDown(int damagemin, int aIndex);
	int CheckDurabilityState();
	BYTE SearchEmptySocketSlot();
	BYTE SetSocketOptionSlot(BYTE SocketSlot, BYTE arg2, BYTE arg3);
	BYTE DeleteSocketOptionSlot(BYTE SocketSlot);
	void ClearSocketOption(BYTE btSocketSlotCount);

	DWORD m_Number; // 0
	char m_serial;	// 4
	short m_Type; // 6
	short m_Level; // 8
	BYTE m_Part;	// A
	BYTE m_Class;	// B
	BYTE m_TwoHand;	// C
	BYTE m_AttackSpeed;	// D
	BYTE m_WalkSpeed;	// E
	WORD m_DamageMin;	// 10
	WORD m_DamageMax;	// 12
	BYTE m_SuccessfulBlocking;	// 14
	WORD m_Defense;	// 16
	WORD m_MagicDefense;	// 18
	BYTE m_Speed;	// 1A
	WORD m_DamageMinOrigin;	// 1C
	WORD m_DefenseOrigin;	// 1E
	WORD m_Magic;	// 20
	WORD m_BookSpell;	// 22
	float m_Durability; // 24
	WORD m_DurabilitySmall; // 28
	float m_BaseDurability;	// 2C
	BYTE m_SpecialNum;	// 30
	BYTE m_Special[8];	// 31
	BYTE m_SpecialValue[8];	// 39
	WORD m_RequireStrength;	// 42
	WORD m_RequireDexterity;	// 44
	WORD m_RequireEnergy;	// 46
	WORD m_RequireLevel;	// 48
	WORD m_RequireVitality;	// 4A
	WORD m_RequireLeaderShip;	// 4C
	WORD m_Leadership;	// 4E
	BYTE m_RequireClass[MAX_TYPE_PLAYER];	// 50
	BYTE m_Resistance[MAX_ITEM_SPECIAL_ATTRIBUTE];	// 56
	int m_Value;	// 60
	DWORD m_SellMoney;	// 64
	DWORD m_BuyMoney;	// 68
	int m_iPShopValue;	// 6C
	bool m_bItemExist;	// 70
	int m_OldSellMoney;	// 74
	int m_OldBuyMoney;	// 78
	BYTE m_Option1;	// 7C  Skill
	BYTE m_Option2;	// 7D  Luck
	BYTE m_Option3;	// 7E  Option
	BYTE m_NewOption;	// 7F ExcellentOption
	float m_DurabilityState[4];	// 80
	float m_CurrentDurabilityState;	// 90
	bool m_SkillChange;	// 94
	bool m_QuestItem;	// 95
	BYTE m_SetOption;	// 96
	BYTE m_SetAddStat;	// 97
	bool m_IsValidItem;	// 98
	BYTE m_SkillResistance[MAX_ITEM_SPECIAL_ATTRIBUTE];	// 99
	BOOL m_IsLoadPetItemInfo;	// A0
	int  m_PetItem_Level;	// A4
	int  m_PetItem_Exp; // A8
	BYTE m_JewelOfHarmonyOption;	// AC
	WORD m_HJOpStrength;	// AE
	WORD m_HJOpDexterity;	// B0
	BYTE m_ItemOptionEx;	// B2
	//Season4 Add-on
	BYTE m_SocketOptionIndex; //B3
	BYTE m_SocketOption[5]; // B4
	BYTE m_SocketBonus; //B9
};

class CPetItemExp
{

public:

	int m_DarkSpiritExpTable[MAX_PET_LEVEL+2];
	int m_DarkHorseExpTable[MAX_PET_LEVEL+2];

public:

	CPetItemExp();
};


extern int g_MaxItemIndexOfEachItemType[MAX_TYPE_ITEMS];

void BufferItemtoConvert3(LPBYTE buf, int& type, BYTE& level, BYTE& op1, BYTE& op2, BYTE& op3, BYTE& dur);
void ItemByteConvert7(LPBYTE buf, CItem * const item , int maxitem);
void ItemByteConvert10(LPBYTE buf, CItem * const item , int maxitem);
void ItemByteConvert16(LPBYTE buf, CItem * const item , int maxitem);
void ItemByteConvert(LPBYTE buf, CItem item);
void ItemByteConvert(LPBYTE buf, int type, BYTE Option1, BYTE Option2, BYTE Option3, BYTE level, BYTE dur, BYTE Noption, BYTE SetOption, BYTE JewelOfHarmonyOption, BYTE ItemEffectEx, BYTE SocketOption[5], BYTE SocketIndex);
int ItemGetNumberMake(int type, int index);
void ItemGetSize(int index, int & width, int & height);
BOOL HasItemDurability(int index);
int ItemGetDurability(int index, int itemLevel, int ExcellentItem, int SetItem);
int ItemGetAttackDurability(int index);
int ItemGetDefenseDurability(int index);
float GetRepairItemRate(int index);
float GetAllRepairItemRate(int index);
void CalRepairRate( int itemtype, int itemsubtype, LPITEM_ATTRIBUTE p);
BOOL OpenItemScript(char* FileName);
BOOL OpenItemNameScript(char* FileName);
BOOL OpenItemScript(char* Buffer, int iSize);
BOOL OpenItemNameScript(char* Buffer, int iSize);
int zzzItemLevel(int type, int index, int level);
int GetLevelItem(int type, int index, int level);
int GetSerialItem(int type);
int IsItem(int item_num);
LPITEM_ATTRIBUTE GetItemAttr(int item_num);

#endif