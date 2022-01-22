#include "stdafx.h"

enum eSkillType
{
	SKILL_POISON = 0x1,
	SKILL_METEO = 0x2,
	SKILL_THUNDER = 0x3,
	SKILL_FIREBALL = 0x4,
	SKILL_FLAME = 0x5,
	SKILL_TELEPORT = 0x6,
	SKILL_SLOW = 0x7,
	SKILL_STORM = 0x8,
	SKILL_EVIL = 0x9,
	SKILL_HELL = 0xa,
	SKILL_POWERWAVE = 0xb,
	SKILL_FLASH = 0xc,
	SKILL_BLAST = 0xd,
	SKILL_INFERNO = 0xe,
	SKILL_TARGET_TELEPORT = 0xf,
	SKILL_MAGICDEFENSE = 0x10,
	SKILL_ENERGYBALL = 0x11,
	SKILL_BLOCKING = 0x12,
	SKILL_SWORD1 = 0x13,
	SKILL_SWORD2 = 0x14,
	SKILL_SWORD3 = 0x15,
	SKILL_SWORD4 = 0x16,
	SKILL_SWORD5 = 0x17,
	SKILL_CROSSBOW = 0x18,
	SKILL_BOW = 0x19,
	SKILL_HEALING = 0x1a,
	SKILL_DEFENSE = 0x1b,
	SKILL_ATTACK = 0x1c,
	SKILL_CALLMON1 = 0x1e,
	SKILL_CALLMON2 = 0x1f,
	SKILL_CALLMON3 = 0x20,
	SKILL_CALLMON4 = 0x21,
	SKILL_CALLMON5 = 0x22,
	SKILL_CALLMON6 = 0x23,
	SKILL_CALLMON7 = 0x24,
	SKILL_WHEEL = 0x29,
	SKILL_BLOWOFFURY = 0x2a,
	SKILL_STRIKE = 0x2b,
	SKILL_KNIGHTSPEAR = 0x2f,
	SKILL_KNIGHTADDLIFE = 0x30,
	SKILL_KNIGHTDINORANT = 0x31,
	SKILL_ELFHARDEN = 0x33,
	SKILL_PENETRATION = 0x34,
	SKILL_DEFENSEDOWN = 0x37,
	SKILL_SWORD6 = 0x38,
	SKILL_5CROSSBOW = 0x36,
	SKILL_EXPPOISON = 0x26,
	SKILL_EXPICE = 0x27,
	SKILL_EXPHELL = 0x28,
	SKILL_EXPHELL_START = 0x3a,
	SKILL_IMPROVE_AG_REFILL = 0x35,
	SKILL_DEVILFIRE = 0x32,
	SKILL_COMBO = 0x3b,
	SKILL_SPEAR = 0x3c,
	SKILL_FIREBURST = 0x3d,
	SKILL_DARKHORSE_ATTACK = 0x3e,
	SKILL_RECALL_PARTY = 0x3f,
	SKILL_ADD_CRITICALDAMAGE = 0x40,
	SKILL_ELECTRICSPARK = 0x41,
	SKILL_LONGSPEAR = 0x42,
	SKILL_RUSH = 0x2c,
	SKILL_JAVALIN = 0x2d,
	SKILL_DEEPIMPACT = 0x2e,
	SKILL_ONE_FLASH = 0x39,
	SKILL_DEATH_CANNON = 0x49,
	SKILL_SPACE_SPLIT = 0x4a,
	SKILL_BRAND_OF_SKILL = 0x4b,
	SKILL_STUN = 0x43,
	SKILL_REMOVAL_STUN = 0x44,
	SKILL_ADD_MANA = 0x45,
	SKILL_INVISIBLE = 0x46,
	SKILL_REMOVAL_INVISIBLE = 0x47,
	SKILL_REMOVAL_MAGIC = 0x48,
	SKILL_FENRIR_ATTACK = 0x4c,
	SKILL_INFINITY_ARROW = 0x4d,
	SKILL_FIRESCREAM = 0x4e,
	SKILL_EXPLOSION = 0x4f,
	SKILL_SUMMON = 0xc8,
	SKILL_IMMUNE_TO_MAGIC = 0xc9,
	SKILL_IMMUNE_TO_HARM = 0xca,
};

enum ObjClass // -> Complete for JPN protocol
{
	DarkWizard 		= 0,
	SoulMaster 		= 8,
	GrandMaster		= 24,
	// ----
	DarkKnight		= 1,
	BladeKnight		= 9,
	BladeMaster		= 25,
	// ----
	Elf				= 2,
	MuseElf			= 10,
	HightElf		= 26,
	// ----
	MagicGladiator	= 3,
	DuelMaster		= 19,
	// ----
	DarkLord		= 4,
	LordEmperor		= 20,
	// ----
	Summoner		= 5,
	BloodySummoner	= 13,
	DimensionMaster	= 29,
};
//---------------------------------------------------------------------------

enum ObjState // -> Complete
{
	SelectServer	= 2,
	SwitchCharacter = 4,
	GameProcess		= 5,
};
//---------------------------------------------------------------------------

#pragma pack(push, 1)
struct ObjectItem	//-> Complete (size: 107)
{
/*+0*/		short	ItemID;
/*+2*/		int		Level;
/*+6*/		char	Unknown6;
/*+7*/		char	Unknown7;
/*+8*/		char	Unknown8;
/*+9*/		short	DamageMin;
/*+11*/		short	DamageMax;
/*+13*/		char	Unknown13;
/*+14*/		short	Unknown14;
/*+16*/		short	Unknown16;
/*+18*/		char	Unknown18;
/*+19*/		char	Unknown19;
/*+20*/		short	Unknown20;
/*+22*/		char	Durability;
/*+23*/		char	ExcellentOption;
/*+24*/		char	AncientOption;
/*+25*/		short	ReqStrenght;
/*+27*/		short	ReqDextirity;
/*+29*/		short	ReqEnergy;
/*+31*/		short	ReqVitality;
/*+33*/		short	ReqCommand;
/*+35*/		short	ReqLevel;
/*+37*/		char    SpecialCount;
/*+38*/		WORD	SpecialType[8];
/*+54*/		BYTE	SpecialValue[8];
/*+62*/		int		UniqueID;
/*+66*/		char	Unknown66;
/*+67*/		char 	PosX;
/*+68*/		char 	PosY;
/*+69*/		WORD 	HarmonyType;
/*+71*/		short	HarmonyValue;
/*+73*/		char 	Is380Item;
/*+74*/		char	SocketOption[5];
/*+79*/		char	Unknown79;
/*+80*/		char	SocketSeedIndex[5];
/*+85*/		char	SocketSphereLevel[5];
/*+90*/		char	SocketSet;
BYTE gap01[5];
/*+96*/		char	DurabilityState;
/*+97*/		char 	PeriodItem;
/*+98*/		char 	ExpiredItem;
/*+99*/		int		ExpireDateConvert;
/*+103*/	int		Unknown103;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct UnknownStruct0
{
	/*+0*/	WORD	Unknown0;//?
	/*+2*/	WORD	Unknown2;//?
	/*+4*/	WORD	Unknown4;//?
	/*+6*/	WORD	Unknown6;
	/*+8*/	WORD	Unknown8;
	/*+10*/	WORD	Unknown10;
	/*+12*/	WORD	Unknown12;//?
	/*+14*/	WORD	Unknown14;
	/*+16*/	WORD	Unknown16;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------
//ObjectCharacter * pPlayer = &*(ObjectCharacter*)*(DWORD*)0x7AB351C;	//1.03K
#pragma pack(push, 1)
struct ObjectCharacter	//-> ~InDev (size: 6012) [8128AC4 | 8128AC8]
{
/*+0*/		char	Name[11];
/*+11*/		char	Class;
/*+12*/		BYTE	Unknown12;
/*+13*/		BYTE	Unknown13;
/*+14*/		short	Level;
/*+16*/		DWORD	Experience;
/*+20*/		DWORD	NextExperience;
/*+24*/		short	Strength;
/*+26*/		short	Dexterity;
/*+28*/		short	Vitality;
/*+30*/		short	Energy;
/*+32*/		short	Leadership;
/*+34*/		WORD	Life;	//22
/*+36*/		WORD	Mana;	//24
/*+38*/		WORD	MaxLife;	//26
/*+40*/		WORD	MaxMana;	//28
/*+42*/		WORD	Shield;		//2A
/*+44*/		WORD	MaxShield;	//2C
/*+46*/		WORD	AttackRate;	//2E
/*+48*/		WORD	DefenseRate;
/*+50*/		short	AddStrength;
/*+52*/		short	AddDexterity;
/*+54*/		short	AddVitality;
/*+56*/		short	AddEnergy;
BYTE gap01[4];
/*+62*/		WORD	AddLeadership;	//GS use unsigned value...
/*+64*/		WORD	Stamina;
/*+66*/		WORD	MaxStamina;
/*+68*/		BYTE	ItemSpecialUseFlag;		//Bit decomposit (1, 2, 8)
BYTE UnknownGap;
/*+70*/		WORD	ItemSpecialUseTime[3];	//[ ]
/*+76*/		WORD	AddPoint;	//FruitStat start
/*+78*/		WORD	MaxAddPoint;
/*+80*/		WORD	MinusPoint;
/*+82*/		WORD	MaxMinusPoint;	//FruitStat end
/*+84*/		WORD	AttackSpeed;
/*+86*/		WORD	DamageRate;
/*+88*/		WORD	DamageMin;
/*+90*/		WORD	DamageMax;
/*+92*/		WORD	Unknown92;
/*+94*/		WORD	Unknown94;
/*+96*/		WORD	MagicSpeed;	//Test
BYTE gap02[10];
/*+108*/	WORD	Unknown108;
/*+110*/	WORD	Unknown110;
BYTE gap03[4];
/*+116*/	WORD	LevelPoint;
/*+118*/	BYTE	MagicCount;
/*+119*/	BYTE	Unknown119;
/*+120*/	WORD	pMagicList[650];	//maybe 150?	//Original 650
/*1420*/
BYTE gap04[3252];
/*+4672*/	ObjectItem pEquipment[12];
/*+5956*/	DWORD	MoneyInventory;	//(C4)
/*+5960*/	DWORD	MoneyWarehouse;	//(C4)
BYTE gap05[8];
/*+5972*/	UnknownStruct0 Unknown5972;
BYTE gap06[2];
/*+5992*/	WORD	Unknown5992;
/*+5994*/	WORD	Unknown5994;
BYTE gap07[2];
/*+5998*/	WORD	Unknown5998;
/*+6000*/	WORD	Unknown6000;
/*+6002*/	WORD	Unknown6002;
/*+6004*/	WORD	Unknown6004;
/*+6006*/	WORD	Unknown6006;
/*+6008*/	BYTE	Unknown6008;
/*+6009*/	BYTE	Unknown6009;
/*+6010*/	BYTE	Unknown6010;
/*+6011*/	BYTE	Unknown6011;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------


