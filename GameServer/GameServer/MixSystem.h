#ifndef CHAOSBOX_H
#define CHAOSBOX_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "protocol.h"
#include "..\common\zzzitem.h"


#define CHAOS_BOX_SIZE 32
#define MIN_CHAOS_ITEM_LEVEL 4

#define CHAOS_BOX_RANGE(x) (((x)<0)?FALSE:((x)>CHAOS_BOX_SIZE-1)?FALSE:TRUE )

enum CHAOS_TYPE
{
	CHAOS_TYPE_DEFAULT = 0x1,
	CHAOS_TYPE_DEVILSQUARE = 0x2,
	CHAOS_TYPE_UPGRADE_10 = 0x3,
	CHAOS_TYPE_UPGRADE_11 = 0x4,
	CHAOS_TYPE_UPGRADE_12 = 0x16,
	CHAOS_TYPE_UPGRADE_13 = 0x17,
	CHAOS_TYPE_DINORANT = 0x5,
	CHAOS_TYPE_FRUIT = 0x6,
	CHAOS_TYPE_SECOND_WING = 0x7,
	CHAOS_TYPE_BLOODCATLE = 0x8,
	CHAOS_TYPE_FIRST_WING = 0xb,
	CHAOS_TYPE_SETITEM = 0xc,
	CHAOS_TYPE_DARKHORSE = 0xd,
	CHAOS_TYPE_DARKSPIRIT = 0xe,
	CHAOS_TYPE_CLOAK = 0x18,
	CHAOS_TYPE_BLESS_POTION = 0xf,
	CHAOS_TYPE_SOUL_POTION = 0x10,
	CHAOS_TYPE_LIFE_STONE = 0x11,

	CHAOS_TYPE_CASTLE_ITEM = 0x12,

	CHAOS_TYPE_HT_BOX = 0x14,
	CHAOS_TYPE_FENRIR_01 = 0x19,
	CHAOS_TYPE_FENRIR_02 = 0x1a,
	CHAOS_TYPE_FENRIR_03 = 0x1b,
	CHAOS_TYPE_FENRIR_04 = 0x1c,
	CHAOS_TYPE_COMPOUNDPOTION_LV1 = 0x1e,
	CHAOS_TYPE_COMPOUNTPOTION_LV2 = 0x1f,
	CHAOS_TYPE_COMPOUNTPOTION_LV3 = 0x20,
	CHAOS_TYPE_JEWELOFHARMONY_PURITY = 0x21,
	CHAOS_TYPE_JEWELOFHARMONY_MIX_SMELTINGITEM = 0x22,
	CHAOS_TYPE_JEWELOFHARMONY_RESTORE_ITEM = 0x23,
	CHAOS_TYPE_380_OPTIONITEM = 0x24,
	CHAOS_TYPE_BLOOD_SCROLL_MIX = 0x25,
	CHAOS_TYPE_CONDOR_FEATHER_MIX = 0x26,
	CHAOS_TYPE_THIRD_WING_MIX = 0x27,
	CHAOS_TYPE_LOTTERY_MIX = 0x28, //season 2.5 changed
	CHAOS_TYPE_CHERRYBLOSSOM_MIX = 0x29, //season 3.0 add-on
	CHAOS_TYPE_SOCKET_SEED_EXTRACT_MIX = 0x2A, //season 4.0 add-on
	CHAOS_TYPE_SOCKET_SPHERE_COMPOSITE_MIX = 0x2B, //season 4.0 add-on
	CHAOS_TYPE_SOCKET_SPHERE_SET_MIX = 0x2C, //season 4.0 add-on
	CHAOS_TYPE_SOCKET_SPHERE_REMOVE_MIX = 0x2D, //season 4.0 add-on
};


struct PMSG_CHAOSMIXRESULT
{
	PBMSG_HEAD h;	// C1:86
	BYTE Result;	// 3
	BYTE ItemInfo[MAX_ITEM_INFO];	// 4
};





struct CB_PMSG_REQ_PRESENT_RESULT
{
	PBMSG_HEAD h;
	char AccountId[10];	// 3
	char GameId[10];	// D
	int Sequence;	// 18
	char present;	// 1C
	char presentname[50];	// 1D
	int Seq_present;	// 50
};



#define CB_ERROR					0
#define CB_SUCCESS					1
#define CB_NOT_ENOUGH_ZEN			2
#define CB_TOO_MANY_ITEMS			3
#define CB_LOW_LEVEL_USER			4
#define CB_LACKING_MIX_ITEMS		6
#define CB_INCORRECT_MIX_ITEMS		7
#define CB_INVALID_ITEM_LEVEL		8
#define CB_USER_CLASS_LOW_LEVEL		9
#define CB_NO_BC_CORRECT_ITEMS		10
#define CB_BC_NOT_ENOUGH_ZEN		11



class CMixSystem
{

public:

	CMixSystem();
	virtual ~CMixSystem();

	BOOL ChaosBoxCheck(LPOBJ lpObj);
	BOOL ChaosBoxInit(LPOBJ lpObj);
	BOOL ChaosBoxItemDown(LPOBJ lpObj);
	int ChaosBoxMix(LPOBJ lpObj, int & Result2, int & Result3);

	void DefaultChaosMix(LPOBJ lpObj);

	void LogDQChaosItem(LPOBJ lpObj);


	int  CheckDevilSquareItem(LPOBJ lpObj, int & eventitemcount, int & itemlevel);

	BOOL DevilSquareEventChaosMix(LPOBJ lpObj, BOOL bCheckType, int iItemLevel);

	void DevilSquareItemChaosMix(LPOBJ lpObj);

	void LogPlusItemLevelChaosItem(LPOBJ lpObj, int iPlusMixLevel);
	void LogChaosItem(LPOBJ lpObj, LPSTR sLogType);
	BOOL PlusItemLevelChaosMix(LPOBJ lpObj, int mixType);

	void BreakItemOption(LPOBJ lpObj); //season3 add-on
	BOOL IsMixPossibleItem(int iItemCode); //season3 add-on

	BOOL PegasiaChaosMix(LPOBJ lpObj);
	BOOL CircleChaosMix(LPOBJ lpObj);
	BOOL WingChaosMix(LPOBJ lpObj);
	

	void BloodCastleItemChaosMix(LPOBJ lpObj);
	
	void DarkHorseChaosMix(LPOBJ lpObj);
	void DarkSpiritChaosMix(LPOBJ lpObj);
	void BlessPotionChaosMix(LPOBJ lpObj);
	void SoulPotionChaosMix(LPOBJ lpObj);
	void LifeStoneChaosMix(LPOBJ lpObj);

	void CastleSpecialItemMix(LPOBJ lpObj);

	void HiddenTreasureBoxItemMix(LPOBJ lpObj);
	void Fenrir_01Level_Mix(LPOBJ lpObj);
	void Fenrir_02Level_Mix(LPOBJ lpObj);
	void Fenrir_03Level_Mix(LPOBJ lpObj);
	void Fenrir_04Upgrade_Mix(LPOBJ lpObj);
	void ShieldPotionLv1_Mix(LPOBJ lpObj);
	void ShieldPotionLv2_Mix(LPOBJ lpObj);
	void ShieldPotionLv3_Mix(LPOBJ lpObj);

	BOOL IsCondorItemCheck(int iItemCode); //Season 2.5 add-on
	BOOL CheckLevel1WingItem(int iItemCode); //Season 2.5 add-on
	BOOL CheckLevel2WingItem(int iItemCode); //Season 2.5 add-on
	BOOL CheckLevel3WingItem(int iItemCode); //Season 2.5 add-on
	BOOL CheckItemCondition(CItem * lpItem, short Level, BYTE Op1, BYTE Op2, BYTE Op3, BYTE SetOption, BYTE NewOption); //Season 2.5 add-on
	void ThirdWingMix1(LPOBJ lpObj); //Season 2.5 add-on
	void ThirdWingMix2(LPOBJ lpObj); //Season 2.5 add-on
	void ThirdWingMixItemDown(LPOBJ lpObj); //Season 2.5 add-on
	void ThirdWingMixItemDown2(CItem * lpItem); //Season 2.5 add-on

	void SetItemChaosMix(LPOBJ lpObj);
	void CBUPS_ItemRequest(int aIndex, char* AccountId, char* Name);
	void LotteryItemMix(LPOBJ lpObj);

	void CherryBlossomMix(LPOBJ lpObj);

	void SocketSeedExtract(LPOBJ lpObj);
	void SocketSeedSphereComposite(LPOBJ lpObj);
	void SocketSetSeedSphere(LPOBJ lpObj, BYTE SocketSlot);
	void SocketRemoveSeedSphere(LPOBJ lpObj, BYTE SocketSlot);
		
	void MixWings2_5(LPOBJ lpObj);	//Custom Wings2.5
	void MixWings4rd(LPOBJ lpObj);	//Custom Wings4

#ifdef _WINGS_5LVL_
	void MixWings5rd(LPOBJ lpObj);
#endif

private:
	//Season 2.5 add-on
	int iJewelofChaos; //4
	int iJewelofBless; //8
	int iJewelofSoul; //C
	int iJewelofCreation; //10
	int iBundleofBless; //14
	int iBundleofSoul; //18
	int iCondorFeather; //1C
	int iCondorFlame; //20
	int iWingofStorm; //24
	int iWingofEternal; //28
	int iWingofIllusion; //2C
	int iWingofRuin; //30
	int iCapeofLord; //34
	int iWingofDimension; //38 -> Season3 add-on (Summoner 3rd Wing)
	int i3rdWingLuckRate; //3C
};

void ChaosEventProtocolCore(BYTE protoNum, unsigned char* aRecv, int aLen);

extern CMixSystem g_MixSystem;

#endif