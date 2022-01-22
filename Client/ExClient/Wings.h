//=================================
// - Name: "Main.dll"
// - Project: 1.0.0.0
// - Game Version: 1.03.11
// - MU Developer: Nemesis
//=================================

#include "Stdafx.h"

#ifdef _WINGS_5LVL_
#define END_NEW_WING 194
#else
#define END_NEW_WING 188
#endif

//char Item[15];
//int i;

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

enum eItemOption
{
	Damage            = 80,        //-> Additional Damage +<N>
	WizardryDamage    = 81,
	CurseSpell        = 82,
	Defense            = 84,        //-> Additional Defense +<N>
	Luck            = 85,        //-> Default: 0
	HPRecovery        = 86,
	IncreaseDamage    = 95,        //-> Increase Damage +<N>%
	IncreaseSpeed    = 98,        //-> Increase Attacking(Wizardry)speed +<N>
	IgnorOpDefense    = 103,
	ReturnAttack    = 106,        //-> Return's the enemy's attack power in <N>%
	CompleteLife    = 107,        //-> Complete recovery of life in <N>% rate
	CompleteMana    = 108,        //-> Complete recovery of Mana in <N>% rate
};

//====================HDK 380 Sets Effect==============================
//#define HDK_SET_ITEM_EFFECT		0x004F9F76//1.03.28 ENG: 52B0DB
//#define HDK_SET_COLOR_EFFECT		0x004F9FDA//1.03.28 ENG: 52B122
//#define HDK_ITEM_EFFECT_ALLOW		0x004F9F9F//1.03.28 ENG: 52B0E7
//#define HDK_ITEM_EFFECT_NOT_ALLOW	0x004FA63E//1.03.28 ENG: 52B9E0
//#define HDK_NEXT_ITEM_COLOR		0x004FA013//1.03.28 ENG: 52B150
//=====================================================================

//void InitItem (int ItemID, char* ModelName, char* Folder, char* Form);
//void NewItemLoop();

//void SetItemEffect();
//void SetColorEffect();

void InitItemLoop();
void InitSmokeEffect();
void WingsSetInvisiableEffect();
void InitInvEffect();
void WingsAdd28Option();
void InitWings28Option();
void WingsShowAdditionals();
void InitWingsShowAdditionals();
void WingsAddExcellentStatus();
void WingsAddLuckOption();
void InitWingsAddExcellentStatus();
void InitWingsAddLuckOption();

void InitSetItemSpecialStat();

typedef int (__cdecl *pSetEffect)(DWORD a1, DWORD a2, DWORD a3, DWORD a4, DWORD a5, float a6, DWORD a7);
extern pSetEffect MU_SetEffect;

void WingsAddCharSet();
void WingsAddCharSetLoad();
void ItemsEffectsLoad();

void InitWingsProps();


//void BowEffect();
//void InitBowEffect();

void NewWingsStart();