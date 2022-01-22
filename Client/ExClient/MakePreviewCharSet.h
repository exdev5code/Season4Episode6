#pragma once
#include "Stdafx.h"

//---------------------------------------------------------------------------

//namespace ASM
//{
//	enum T
//	{
//		JMP	 = 0xE9,
//		JE	 = 0x74,
//		JNE  = 0x75,
//		JGE  = 0x7D,
//		NOP	 = 0x90,
//		CALL = 0xE8,
//	};
//};
//---------------------------------------------------------------------------

//enum eItemOption
//{
//	Damage            = 80,        //-> Additional Damage +<N>
//	WizardryDamage    = 81,
//	CurseSpell        = 82,
//	Defense            = 84,        //-> Additional Defense +<N>
//	Luck            = 85,        //-> Default: 0
//	HPRecovery        = 86,
//	IncreaseDamage    = 95,        //-> Increase Damage +<N>%
//	IncreaseSpeed    = 98,        //-> Increase Attacking(Wizardry)speed +<N>
//	IgnorOpDefense    = 103,
//	ReturnAttack    = 106,        //-> Return's the enemy's attack power in <N>%
//	CompleteLife    = 107,        //-> Complete recovery of life in <N>% rate
//	CompleteMana    = 108,        //-> Complete recovery of Mana in <N>% rate
//};
////---------------------------------------------------------------------------
//
//enum ObjClass // -> Complete -> Season 5.2 JPN
//{
//	DarkWizard 		= 0,
//	SoulMaster 		= 8,
//	GrandMaster		= 24,
//	// ----
//	DarkKnight		= 1,
//	BladeKnight		= 9,
//	BladeMaster		= 25,
//	// ----
//	Elf				= 2,
//	MuseElf			= 10,
//	HightElf		= 26,
//	// ----
//	MagicGladiator	= 3,
//	DuelMaster		= 19,
//	// ----
//	DarkLord		= 4,
//	LordEmperor		= 20,
//	// ----
//	Summoner		= 5,
//	BloodySummoner	= 13,
//	DimensionMaster	= 29,
//};
//---------------------------------------------------------------------------

enum eEffectState
{
	AtDarkHorse		= 1,
	AtFenrir		= 4,
	AtGameMaster	= 5,
};
//---------------------------------------------------------------------------

//enum ObjState // -> Complete
//{
//	SelectServer	= 2,
//	SwitchCharacter = 4,
//	GameProcess		= 5,
//};
//---------------------------------------------------------------------------

enum eMauntType
{
#if CLIENT_VERSION == 0
	DarkHorse		= 226,
#else
	DarkHorse		= 225,
#endif
	Uniria			= 233,
	Dinorant		= 323,
	BlackFenrir		= 384,
	RedFenrir		= 385,
	BlueFenrir		= 386,
	GoldenFenrir	= 387,
};
//---------------------------------------------------------------------------

#define pVisible(x)						*(BYTE*)(x + 15)
#define pPlayerClass(x)					*(BYTE*)(x + 19)
#define pAncientEffect(x)				*(BYTE*)(x + 22)
#define pAtEffect(x)					*(BYTE*)(x + 23)
#define pHelmSlot(x)					*(WORD*)(x + 232)
#define pHelmSetLevel(x)				*(BYTE*)(x + 234)
#define pHelmSetExcellent(x)			*(BYTE*)(x + 235)
#define pHelmSetAncient(x)				*(BYTE*)(x + 236)
#define pArmorSlot(x)					*(WORD*)(x + 264)
#define pArmorSetLevel(x)				*(BYTE*)(x + 266)
#define pArmorSetExcellent(x)			*(BYTE*)(x + 267)
#define pArmorSetAncient(x)				*(BYTE*)(x + 268)
#define pPantsSlot(x)					*(WORD*)(x + 296)
#define pPantsSetLevel(x)				*(BYTE*)(x + 298)
#define pPantsSetExcellent(x)			*(BYTE*)(x + 299)
#define pPantsSetAncient(x)				*(BYTE*)(x + 300)
#define pGlovesSlot(x)					*(WORD*)(x + 328)
#define pGlovesSetLevel(x)				*(BYTE*)(x + 330)
#define pGlovesSetExcellent(x)			*(BYTE*)(x + 331)
#define pGlovesSetAncient(x)			*(BYTE*)(x + 332)
#define pBootsSlot(x)					*(WORD*)(x + 360)
#define pBootsSetLevel(x)				*(BYTE*)(x + 362)
#define pBootsSetExcellent(x)			*(BYTE*)(x + 363)
#define pBootsSetAncient(x)				*(BYTE*)(x + 364)
#define pWeaponFirstSlot(x)				*(WORD*)(x + 392)
#define pWeaponFirstSetLevel(x)			*(BYTE*)(x + 394)
#define pWeaponFirstSetExcellent(x)		*(BYTE*)(x + 395)
#define pWeaponFirstSetAncient(x)		*(BYTE*)(x + 396)
#define pWeaponSecondSlot(x)			*(WORD*)(x + 424)
#define pWeaponSecondSetLevel(x)		*(BYTE*)(x + 426)
#define pWeaponSecondSetExcellent(x)	*(BYTE*)(x + 427)
#define pWeaponSecondSetAncient(x)		*(BYTE*)(x + 428)
#define pWingsSlot(x)					*(WORD*)(x + 456)
#define pSetUnknown1(x)					*(BYTE*)(x + 458)
#define pSetUnknown2(x)					*(BYTE*)(x + 459)
#define pSetUnknown3(x)					*(BYTE*)(x + 460)
#define pPetSlot(x)						*(WORD*)(x + 488)
#define pSetUnknown4(x)					*(BYTE*)(x + 490)
#define pFenrirCharSet(x)				*(BYTE*)(x + 491)
#define pExpectPet(x)					*(BYTE*)(x + 492)
#define pObjAction(x)					*(BYTE*)(x + 718)
#define pObjScale(x)					*(DWORD*)(x + 796)
#define pObjSelectZone(x)				*(float*)(x + 924)
#define pGetPosition(x)					*(WORD*)(x + 952)
//---------------------------------------------------------------------------

struct Preview
{
	BYTE	Shift1[14];

	/*4*/	//BYTE	Unknown4;	// -> 100%
	/*8*/	//DWORD	Unknown8;	// -> 100%

	/*14*/	BYTE	IsSafeZone;
	/*15*/	BYTE	Visible;
	/*16*/	BYTE	Unknown16;
	/*17*/	BYTE	IsLiveObject;
	/*18*/	BYTE	Unknown18;
	/*19*/	BYTE	Class;
	/*20*/	BYTE	Unknown20;
	/*21*/	BYTE	CtrlCode;
	/*22*/	BYTE	AncientEffect;
	/*23*/	BYTE	PetStatus;
	/*24*/	BYTE	Unknown24;
	/*25*/	BYTE	Unknown25;
	/*26*/	BYTE	Unknown26;
	/*27*/	BYTE	Unknown27;
	/*28*/	BYTE	Unknown28;
	/*29*/	BYTE	Unknown29;
	/*30*/	BYTE	Unknown30;
	/*31*/	BYTE	Unknown31;
	/*32*/	BYTE	PKLevel;
	/*33*/	BYTE	Unknown33;
	/*34*/	BYTE	Unknown34;
	/*35*/	BYTE	Unknown35;
	/*36*/	BYTE	Unknown36;
	/*37*/	BYTE	Unknown37;
	/*38*/	WORD	Unknown38;
	/*40*/	BYTE	Unknown40;
	/*41*/	BYTE	Unknown41;
	/*42*/	BYTE	Unknown42;
	/*43*/	BYTE	Unknown43;
	/*44*/	BYTE	Unknown44;
	/*45*/	BYTE	MapPosX;
	/*46*/	BYTE	MapPosY;
	BYTE	Shift47[9];
	/*56*/	char	Name[25];	//-> Need check size

	/*50*/	//BYTE	Unknown50;	// -> 100%
	/*88*/	//BYTE	Unknown88;	// -> 100%
	/*90*/	//BYTE	Unknown90;	// -> 100%
	/*91*/	//BYTE	Unknown91;	// -> 100%
	/*92*/	//WORD	InGuild;	// -> 100%
	/*94*/	//WORD	ObjIndex;	// -> 100%
	/*96*/	//WORD	Unknown96;	// -> 100%
	/*98*/	//WORD	Unknown98;	// -> 100%
	/*100*/	//WORD	Unknown100;	// -> 100%
	/*106*/	//WORD	Unknown106;	// -> 100%
	/*112*/	//DWORD	Unknown112;	// -> 100%
	/*116*/	//DWORD	Unknown116;	// -> 100%
	/*124*/	//DWORD	Unknown124;	// -> 100%
	/*140*/	//DWORD MapPosX;	// -> 100%
	/*144*/	//DWORD MapPosY;	// -> 100%
	/*156*/	//DWORD	Unknown156;	// -> 100%
	/*172*/	//DWORD	Unknown172;	// -> 100%
	/*188*/	//DWORD	Unknown188;	// -> 100%
	/*192*/	//DWORD	Unknown192;	// -> 100%
	/*196*/	//DWORD	Unknown196;	// -> 100%

	BYTE	Shift2[150];

	/*232*/	WORD	HelmSlot;
	/*234*/	BYTE	HelmLevel;
	/*235*/	BYTE	HelmExcellent;
	/*236*/	BYTE	HelmAncient;
	BYTE	Shift5[27];
	/*264*/	WORD	ArmorSlot;
	/*266*/	BYTE	ArmorLevel;
	/*267*/	BYTE	ArmorExcellent;
	/*268*/	BYTE	ArmorAncient;
	BYTE	Shift6[27];
	/*296*/	WORD	PantsSlot;
	/*298*/	BYTE	PantsLevel;
	/*299*/	BYTE	PantsExcellent;
	/*300*/	BYTE	PantsAncient;
	BYTE	Shift7[27];
	/*328*/	WORD	GlovesSlot;
	/*330*/	BYTE	GlovesLevel;
	/*331*/	BYTE	GlovesExcellent;
	/*332*/	BYTE	GlovesAncient;
	BYTE	Shift8[27];
	/*360*/	WORD	BootsSlot;
	/*362*/	BYTE	BootsLevel;
	/*363*/	BYTE	BootsExcellent;
	/*364*/	BYTE	BootsAncient;
	BYTE	Shift9[27];
	/*392*/	WORD	WeaponFirstSlot;
	/*394*/	BYTE	WeaponFirstLevel;
	/*395*/	BYTE	WeaponFirstExcellent;
	/*396*/	BYTE	WeaponFirstAncient;
	/*397*/	BYTE	Unknown397;
	BYTE	Shift10[26];
	/*424*/	WORD	WeaponSecondSlot;
	/*426*/	BYTE	WeaponSecondLevel;
	/*427*/	BYTE	WeaponSecondExcellent;
	/*428*/	BYTE	WeaponSecondAncient;
	/*429*/	BYTE	Unknown429;
	BYTE	Shift11[26];
	/*456*/	WORD	WingsSlot;
	/*458*/ BYTE	Unknown458;
	/*459*/ BYTE	Unknown459;
	/*460*/ BYTE	Unknown460;
	BYTE	Shift12[27];
	/*488*/	WORD	PetSlot;
	/*490*/ BYTE	Unknown490;
	/*491*/ BYTE	FenrirCharSet;
	/*492*/ BYTE	ExpectPet;

	/*520*/	//WORD	Unknown520;	// -> 100%
	/*596*/	//DWORD	Unknown596;	// -> 100%
	/*688*/	//DWORD	Unknown688;	//
	BYTE	Shift13[207];

	/*700*/	DWORD	Unknown700;	// -> # Need check
	/*704*/	BYTE	Unknown704;

	BYTE	Shift14[2];

	/*707*/	BYTE	Unknown707;
	/*708*/	BYTE	Unknown708;
	/*709*/	BYTE	Unknown709;
	/*710*/	BYTE	Unknown710;	// -> 100%
	/*711*/	BYTE	Unknown711;
	/*712*/	BYTE	Unknown712;
	BYTE	Shift16[5];
	/*718*/	BYTE	Action;
	/*719*/	BYTE	Unknown719;
	/*720*/	BYTE	Unknown720; //-> 100%
	/*721*/	BYTE	Unknown721;	//-> 100%
	/*722*/ BYTE	ObjectType; //-> Object Type (1 = Player, 2 = Monster, 4 = NPC) 100%
	BYTE	Shift17[25];
	/*748*/	DWORD	Unknown748;
	/*752*/	DWORD	Unknown752;
	/*756*/	DWORD	Unknown756;
	/*760*/	DWORD	Unknown760;

	/*768*/	//DWORD	Unknown768;	// -> 100%

	BYTE	Shift18[32];
	/*796*/	DWORD	ModelScale;
	BYTE	Shift19[16];

	/*800*/	//DWORD	Unknown800;	// -> 100%

	/*816*/	DWORD	Unknown816;

	/*824*/	//DWORD	Unknown824;	// -> 100%

	BYTE	Shift20[103];

	/*856*/	//DWORD	Unknown856;	// -> 100%
	/*860*/	//DWORD	Unknown860;	// -> 100%
	/*864*/	//DWORD	Unknown864;	// -> 100%
	/*972*/	//DWORD	Unknown972;	// -> 100%
	/*904*/	//DWORD	Unknown904;	// -> 100%
	/*908*/	//DWORD	Unknown908;	// -> 100%
	/*912*/	//DWORD	Unknown912;	// -> 100%
	/*916*/	//DWORD	Unknown916;	// -> 100% / Maybe float
	/*920*/	//DWORD	Unknown920;	// -> 100% / Maybe float

	/*924*/	float	SelectZone;	// -> Maybe DWORD
	BYTE	Shift21[32];

	/*952*/	//float	Unknown952;	// -> 100%
	/*956*/	//float	Unknown956;	// -> 100%

	/*960*/ float	Unknown960;

	/*964*/	//DWORD	Unknown964;	// -> 100%
	/*968*/	//DWORD	Unknown968;	// -> 100%
	/*972*/	//DWORD	Unknown972;	// -> 100%
	/*1120*/	//DWORD	Unknown1120;	// -> 100%
	/*1184*/	//void?
};
//---------------------------------------------------------------------------

#define ITEM_INTER 834 //Season 4.6 JPN -> 1.03k
#define ITEM(x, y) ((x * 512) + y)
#define ITEM2(x, y) ((x * 512) + y + ITEM_INTER) 
#define oObjState				0x008D6F7C			//Main 1.03Y+ JPN: 00946F9C ; Main 1.03k JPN: 008D6F7C
#define oMapNumber				0x008C5CF8			//Main 1.03Y+ JPN: 00934540 ; Main 1.03k JPN: 008C5CF8
#define LODWORD(h)				((DWORD)(__int64(h) & __int64(0xffffffff)))
// ----
//#define CS_START				1304
#define CS_START                1236 //Main 1.03k JPN
// ----
#define CS_EMPTY_SLOT			-1
#define CS_EMPTY_ITEM			511
#define CS_EMPTY_WEAPON			4095 // ITEM(7, 511)
// ----
#define	CS_SET_1(x)				( x >> 2)
// ----
#define CS_HELM					9036 // 9089 for Season 5.2 JPN (1.03Y+ Main.exe) ; 9036 for Season 4.6 JPN (1.03k Main.exe)
#define CS_ARMOR				CS_HELM + 20
#define CS_PANTS				CS_ARMOR + 20
#define CS_GLOVES				CS_PANTS + 20
#define CS_BOOTS				CS_GLOVES + 20
// ----
#define CS_GET_STRUCT(x, y)		(CS_START * x + *(int*)y)
#define CS_GET_WEAPON(x, y)		( y | (16 * (x & 0xF0)) )
#define CS_GET_HELM(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 7) & 1) + (y >> 4) )
#define CS_GET_ARMOR(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 6) & 1) + (y & 0xF) )
#define CS_GET_PANTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 5) & 1) + (y >> 4) )
#define CS_GET_GLOVES(x, y, z)	( (32 * ((z >> 4) & 0xF)) + 16 * ((x >> 4) & 1) + (y & 0xF) )
#define CS_GET_BOOTS(x, y, z)	( (32 * (z & 0xF)) + 16 * ((x >> 3) & 1) + (y >> 4) )
//---------------------------------------------------------------------------

//bool __cdecl sub_49A450(signed int a1) -> return bool
typedef bool (__cdecl *IsChaosCastle)(int MapNumber);
extern IsChaosCastle gIsChaosCastle;
//---------------------------------------------------------------------------

//char __cdecl sub_51C4EC(BYTE a1) -> return WORD
typedef WORD (__cdecl *ItemCharSetConvert)(BYTE Pointer);
extern ItemCharSetConvert gItemCharSetConvert;
//---------------------------------------------------------------------------

//int __cdecl sub_463890(char a1) -> return BYTE or WORD
typedef BYTE (__cdecl *AmpersandConvert)(BYTE Pointer);
extern AmpersandConvert gAmpersandConvert;
//---------------------------------------------------------------------------

typedef int (__cdecl *ObjMakePreviewCharSet)(int a1, BYTE * CharSet, int a3, int a4);
extern ObjMakePreviewCharSet mObjMakePreviewCharSet;
//---------------------------------------------------------------------------

//int __cdecl sub_49A50A(int a1)
typedef int (__cdecl *Objsub_49A50A)(int Arg1);
extern Objsub_49A50A sub_49A50A;
//---------------------------------------------------------------------------

//int __cdecl sub_514A21(int a1)
typedef int (__cdecl *Objsub_514A21)(int Arg1);
extern Objsub_514A21 sub_514A21;
//---------------------------------------------------------------------------

//int __cdecl sub_4A3A7D(int a1) -> return int
typedef int (__cdecl *CheckPetStatus)(int Arg1);
extern CheckPetStatus gCheckPetStatus;
//---------------------------------------------------------------------------

//int __cdecl sub_4B6740(int a1) -> return int
typedef int (__cdecl *ReturnPetSlot)(int Arg1);
extern ReturnPetSlot gReturnPetSlot;
//---------------------------------------------------------------------------

//int __cdecl sub_4B6B54(int a1, int a2, int a3, int a4) -> return int
typedef int (__cdecl *SetObjMaunt)(int MauntCode, int Arg2, int Arg3, int Arg4, int Arg5);
extern SetObjMaunt gSetObjMaunt;
//---------------------------------------------------------------------------

//char __cdecl sub_4B680C(int a1, int a2, int a3, int a4, int a5) -> return bool
typedef bool (__cdecl *SetObjMaunt2)(int Arg1, int Arg2, int Arg3, int Arg4, int Arg5);
extern SetObjMaunt2 gSetObjMaunt2;
//---------------------------------------------------------------------------

//int __cdecl sub_8831F1() -> return THIS
typedef LPVOID (__cdecl *ObjPetGetThis)(void);
extern ObjPetGetThis gObjPetGetThis;
//---------------------------------------------------------------------------

//void __stdcall sub_88457C(int a1, int a2, char a3)
typedef void (__thiscall *SetObjPetReset)(LPVOID This, int Arg1, int Arg2, int Arg3);
extern SetObjPetReset gSetObjPetReset;
//---------------------------------------------------------------------------

//char __thiscall sub_884245(void *this, int a2, int a3, int a4, int a5, int a6, int a7) -> return bool
typedef void (__thiscall *SetObjPetOnSwitch)(LPVOID This, int Arg1, int Arg2, int Arg3, int Arg4, int Arg5, int Arg6);
extern SetObjPetOnSwitch gSetObjPetOnSwitch;
//---------------------------------------------------------------------------

//int *__cdecl sub_4ADABB(int a1) -> return int const
typedef int * (__cdecl *Objsub_4ADABB)(int Arg1);
extern Objsub_4ADABB sub_4ADABB;
//---------------------------------------------------------------------------

//int __cdecl sub_4ACDA6(int Preview * gPreview) -> return int
typedef int (__cdecl *ObjPreviewDarkRaven)(int Struct);
extern ObjPreviewDarkRaven gObjPreviewDarkRaven;
//---------------------------------------------------------------------------

typedef DWORD (*Objdword_7B65114);
extern Objdword_7B65114 dword_7B65114;
//---------------------------------------------------------------------------

typedef DWORD (*Objdword_7BA6278);
extern Objdword_7BA6278 dword_7BA6278;
//---------------------------------------------------------------------------

typedef DWORD (*Objdword_7B650F8);
extern Objdword_7B650F8 dword_7B650F8;
//---------------------------------------------------------------------------

void cMakePreviewCharSetLoad();
//---------------------------------------------------------------------------