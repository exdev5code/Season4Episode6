//GS-N 1.00.90 - 0xXXXXXXXX  - complete
//GS-CS 1.00.90 - 0xXXXXXXXX  - complete
#include "stdafx.h"
#include "AcceptIp.h"
#include "gamemain.h"
#include "..\common\winutil.h"
#include "GameServer.h"
#include "DirPath.h"
#include "logproc.h"
#include "gameserverauth.h"
#include "wsJoinServerCli.h"
#include "DirPath.h"
#include "DSProtocol.h"
#include "CLoginCount.h"
#include "MapClass.h"
#include "..\common\classdef.h"
#include "..\include\prodef.h"
#include "wsGameServer.h"
#include "EledoradoEvent.h"
#include "WhisperCash.h"
#include "SProtocol.h"
#include "ChaosCastle.h"
#include "DevilSquare.h"
#include "Gate.h"
#include "user.h"
#include "Event.h"
#include "PacketCheckSum.h"
#include "DragonEvent.h"
#include "AttackEvent.h"
#include "SendHackLog.h"
#include "SimpleModulus.h"
#include "MapServerManager.h"
#include "..\ggsvr\ggsvr.h"
#include "QuestInfo.h"
#include "SkillHitBox.h"
#include "EventManagement.h"
#include "..\common\SetItemOption.h"
#include "EDSProtocol.h"
#include "MonsterItemMng.h"
#include "ConMember.h"
#include "GMMng.h"
#include "BattleSoccerManager.h"
#include "GuildClass.h"
#include "MoveCommand.h"
#include "MixSystem.h"
#include "BloodCastle.h"
#include "Shop.h"
#include "ItemAddOption.h"
#include "CrywolfSync.h"
#include "Kanturu.h"
#include "KanturuMonsterMng.h"
#include "SkillAdditionInfo.h"
#include "TMonsterSkillElement.h"
#include "TMonsterSkillUnit.h"
#include "TMonsterSkillManager.h"
#include "TMonsterAIElement.h"
#include "TMonsterAIAutomata.h"
#include "TMonsterAIUnit.h"
#include "TMonsterAIRule.h"
#include "TMonsterAIGroup.h"
#include "CashShop.h"
#include "CashItemPeriodSystem.h"
#include "CashLotterySystem.h"
#include "ProbabilityItemBag.h"
#include "IllusionTempleEvent.h"
#include "BuffEffect.h"
#include "MasterLevelSystem.h"
#include "MasterSkillSystem.h"
#include "ChaosCard.h"
#include "Raklion.h"
#include "PCBangPointSystem.h"
#include "XmasAttackEvent.h"
#include "CrywolfAltar.h"
#include "ItemDropManager.h"
//#include "MossMerchant.h"
//#include "GoldenArcher.h"
//#include "PCPointSystem.h"
//#include "ExQuestSystem.h"
#include "AntiCheatPlus.h"

BOOL JoinServerConnected;
BOOL DataServerConnected;
BOOL GameServerCreated;
BOOL DevilSquareEventConnect;
BOOL IsDevilSquareEventConnected;
BOOL EventChipServerConnect;
BOOL IsEventChipServerConnected;
CDragonEvent * DragonEvent;
CAttackEvent * AttackEvent;
CItemBag * LuckboxItemBag;
CItemBag * Mon55;
CItemBag * Mon53;
CItemBagEx * StarOfXMasItemBag;
CItemBag * FireCrackerItemBag;
CItemBag * HeartOfLoveItemBag;
CItemBag * GoldMedalItemBag;
CItemBag * SilverMedalItemBag;
CItemBag * EventChipItemBag;
CProbabilityItemBag * GoldGoblenItemBag;
CProbabilityItemBag * TitanItemBag;
CProbabilityItemBag * GoldDerconItemBag;
CProbabilityItemBag * DevilLizardKingItemBag;
CProbabilityItemBag * KanturItemBag;
CItemBag * RingEventItemBag;
CItemBag * FriendShipItemBag;
CItemBag * DarkLordHeartItemBag;
CItemBagEx * KundunEventItemBag;
CItemBagEx * HiddenTreasureBoxItemBag;
CItemBagEx * RedRibbonBoxEventItemBag;
CItemBagEx * GreenRibbonBoxEventItemBag;
CItemBagEx * BlueRibbonBoxEventItemBag;
CItemBagEx * PinkChocolateBoxEventItemBag;
CItemBagEx * RedChocolateBoxEventItemBag;
CItemBagEx * BlueChocolateBoxEventItemBag;
CItemBagEx * LightPurpleCandyBoxEventItemBag;
CItemBagEx * VermilionCandyBoxEventItemBag;
CItemBagEx * DeepBlueCandyBoxEventItemBag;
CItemBagEx * CrywolfDarkElfItemBag;
CItemBagEx * CrywolfBossMonsterItemBag;

CItemBagEx * KanturuMayaHandItemBag;
CItemBagEx * KanturuNightmareItemBag;

CItemBagEx * HallowinDayEventItemBag;

CItemBag * RingOfHeroBoxItemBag;

CProbabilityItemBag * NewYearLuckyPouchItemBag; //test
CProbabilityItemBag * GMPresentBoxItemBag; //test
CProbabilityItemBag * IllusionTemple1ItemBag; //test
CProbabilityItemBag * IllusionTemple2ItemBag; //test
CProbabilityItemBag * IllusionTemple3ItemBag; //test
CProbabilityItemBag * MoonHarvestItemBag; //test
CProbabilityItemBag * MoonHarvestItemBag2; //test

CProbabilityItemBag * CherryBlossom1; //test
CProbabilityItemBag * CherryBlossom2; //test
CProbabilityItemBag * CherryBlossom3; //test
CProbabilityItemBag * CherryBlossom4; //test

CProbabilityItemBag * PCBangGageGreenBox; //test
CProbabilityItemBag * PCBangGageRedBox; //test
CProbabilityItemBag * PCBangGagePurpleBox; //test

CProbabilityItemBag * ReservedBox; //test

CProbabilityItemBag * RaklionSelupanItemBag; //test

CProbabilityItemBag * XMasEventA; //test
CProbabilityItemBag * XMasEventB; //test
CProbabilityItemBag * XMasEventC; //test

CProbabilityItemBag * LuckyCoin10; //test
CProbabilityItemBag * LuckyCoin20; //test
CProbabilityItemBag * LuckyCoin30; //test

BOOL SpeedHackPlayerBlock;
BOOL bCanConnectMember;
BOOL bCanChangeCharacterName;
int  gServerType;
int  gPartition;
BOOL gApplyHeroSystem;
int  gSpeedHackPenalty;
BOOL gEnableEventNPCTalk;
BOOL gEnableServerDivision;
BOOL gEvent1;
int  gMonsterHp;
BOOL gMerryXMasNpcEvent;
BOOL gHappyNewYearNpcEvent;
int  gEvent1ItemDropTodayCount;
int  gLanguage;
BOOL gChaosEvent;
char gChaosEventServerIp[20];
char gDevilSquareEventServerIp[20];
char gHackLogServerIp[20];
char gEventChipServerIp[20];
char gStalkProtocolId[11];
BOOL gNonPK;
BOOL gPkLimitFree;
BOOL gXMasEvent;
BOOL gFireCrackerEvent;
BOOL gHeartOfLoveEvent;
BOOL gMedalEvent;
BOOL gEventChipEvent;
BOOL gDevilSquareEvent;
BOOL gWriteSkillLog;
BOOL g_bStoneItemDrop;
BOOL g_bDoXMasAttackEvent;
BOOL g_bDoRingEvent;
BOOL g_bEventManagerOn;
int  g_iKundunMarkDropRate;
int  g_iMarkOfTheLord;

#ifdef INTERNATIONAL_JAPAN
int g_iJapan1StAnivItemDropRate;
#endif

int  g_iDarkLordHeartDropRate;
int  g_iDarkLordHeartOffEventRate;
int g_iMysteriousBeadDropRate1;
int g_iMysteriousBeadDropRate2;
int g_iHiddenTreasureBoxOfflineRate;
BOOL bIsIgnorePacketSpeedHackDetect;
BOOL gIsKickDetecHackCountLimit;
BOOL gTamaJJangEvent;
int gAppearTamaJJang;
int gTamaJJangTime;
BOOL gIsItemDropRingOfTransform;
BOOL gIsEledoradoEvent;
BOOL gDoPShopOpen;
BOOL gWriteChatLog;
BOOL gDisconnectHackUser;
int g_iBlockKanturuMapEnter;
int g_iBlockCastleSiegeMapEnter;
int g_iBlockRaklionMapEnter;
BOOL GSInfoSendFlag;

int  GameServerPort;
int  JoinServerPort;
int  DataServerPort;
int  DataServerPort2;
int  ExDbPort;

BOOL gNewServer;
BOOL gEventOff;


CwsGameServer wsGServer;	// line : 213GameServer

wsJoinServerCli wsJServerCli;	// line : 214 Join Server
wsJoinServerCli wsDataCli;	// line : 215 DataServer
wsJoinServerCli wsExDbCli;	// line : 239 Extra DataBase Server
wsJoinServerCli wsRServerCli;	// line : 244 Ranking Server
wsJoinServerCli wsEvenChipServerCli; // line : 246 EVENT_MU2003

CDirPath gDirPath;	// line : 248 Directory Path

MapClass MapC[MAX_NUMBER_MAP];	// line 249	// Map Manager

CMonsterAttr gMAttr;	// line 250

CMonsterSetBase gMSetBase;	// line 251

classdef DCInfo;	// line 252:

CWhisperCash WhisperCash;	// line 253

PartyClass gParty;	// line 254

CDbSave gDbSave;	// line 255

WzUdp gUdpSoc;	// line 256
WzUdp gUdpSocCE;	// line 258
WzUdp gUdpSocCER;	// line 259
WzUdp gUdpSocCRank;	// line 261
WzUdp gUdpSocCRankR;	//line 262

CGuildClass Guild;	// line 265

CMsg lMsg;	// line 324

NSerialCheck gNSerialCheck[OBJMAX];	// line 326

CLoginCount gLCount[3];	// line 329

DWORD  gLevelExperience[MAX_CHAR_LEVEL+1];

char szGameServerExeSerial[24];
char szServerName[50];
char szKorItemTextFileName[256];
char szKorSkillTextFileName[256];
char szItemTextFileName[256];
char szSkillTextFileName[256];
char szQuestTextFileName[256];
char szMoveReqFileName[256];
char szCommonlocIniFileName[256];
char szAuthKey[20];

BOOL gIsDropDarkLordItem;
int  gSleeveOfLordDropRate;
int  gSleeveOfLordDropLevel;
int  gSoulOfDarkHorseDropRate;
int  gSoulOfDarkHorseropLevel;
int  gSoulOfDarkSpiritDropRate;
int  gSoulOfDarkSpiritDropLevel;
float gDarkSpiritAddExperience;
BOOL gIsDropGemOfDefend;
int  gGemOfDefendDropRate;
int  gGemOfDefendDropLevel;
int  g_iUseCharacterAutoRecuperationSystem;
int  g_iCharacterRecuperationMaxLevel;
int g_iServerGroupGuildChatting;
int g_iServerGroupUnionChatting;

BOOL g_bRibbonBoxEvent;
int g_iRedRibbonBoxDropLevelMin;
int g_iRedRibbonBoxDropLevelMax;
int g_iRedRibbonBoxDropRate;
int g_iRedRibbonBoxDropZenRate;
int g_iRedRibbonBoxDropZen;
int g_iGreenRibbonBoxDropLevelMin;
int g_iGreenRibbonBoxDropLevelMax;
int g_iGreenRibbonBoxDropRate;
int g_iGreenRibbonBoxDropZenRate;
int g_iGreenRibbonBoxDropZen;
int g_iBlueRibbonBoxDropLevelMin;
int g_iBlueRibbonBoxDropLevelMax;
int g_iBlueRibbonBoxDropRate;
int g_iBlueRibbonBoxDropZenRate;
int g_iBlueRibbonBoxDropZen;

BOOL g_bNewYearLuckyBagMonsterEventOn;

BOOL g_bChocolateBoxEvent;
int g_iPinkChocolateBoxDropLevelMin;
int g_iPinkChocolateBoxDropLevelMax;
int g_iPinkChocolateBoxDropRate;
int g_iPinkChocolateBoxDropZenRate;
int g_iPinkChocolateBoxDropZen;
int g_iRedChocolateBoxDropLevelMin;
int g_iRedChocolateBoxDropLevelMax;
int g_iRedChocolateBoxDropRate;
int g_iRedChocolateBoxDropZenRate;
int g_iRedChocolateBoxDropZen;
int g_iBlueChocolateBoxDropLevelMin;
int g_iBlueChocolateBoxDropLevelMax;
int g_iBlueChocolateBoxDropRate;
int g_iBlueChocolateBoxDropZenRate;
int g_iBlueChocolateBoxDropZen;

BOOL g_bCandyBoxEvent;
int g_iLightPurpleCandyBoxDropLevelMin;
int g_iLightPurpleCandyBoxDropLevelMax;
int g_iLightPurpleCandyBoxDropRate;
int g_iLightPurpleCandyBoxDropZenRate;
int g_iLightPurpleCandyBoxDropZen;
int g_iVermilionCandyBoxDropLevelMin;
int g_iVermilionCandyBoxDropLevelMax;
int g_iVermilionCandyBoxDropRate;
int g_iVermilionCandyBoxDropZenRate;
int g_iVermilionCandyBoxDropZen;
int g_iDeepBlueCandyBoxDropLevelMin;
int g_iDeepBlueCandyBoxDropLevelMax;
int g_iDeepBlueCandyBoxDropRate;
int g_iDeepBlueCandyBoxDropZenRate;
int g_iDeepBlueCandyBoxDropZen;

BOOL g_bFenrirStuffItemDrop;
int g_iFenrirStuff_01_DropLv_Min;
int g_iFenrirStuff_01_DropLv_Max;
int g_iFenrirStuff_01_DropMap;
int g_iFenrirStuff_01_DropRate;
int g_iFenrirStuff_02_DropLv_Min;
int g_iFenrirStuff_02_DropLv_Max;
int g_iFenrirStuff_02_DropMap;
int g_iFenrirStuff_02_DropRate;
int g_iFenrirStuff_03_DropLv_Min;
int g_iFenrirStuff_03_DropLv_Max;
int g_iFenrirStuff_03_DropMap;
int g_iFenrirStuff_03_DropRate;
int g_iFenrirRepairRate;
int g_iFenrirDefaultMaxDurSmall;
int g_iFenrirElfMaxDurSmall;
int g_iFenrir_01Level_MixRate;
int g_iFenrir_02Level_MixRate;
int g_iFenrir_03Level_MixRate;

BOOL g_bCrywolfMonsterDarkElfItemDrop;
int g_iCrywolfMonsterDarkElfItemDropRate;
int g_iCrywolfMonsterDarkElfDropZenRate;
int g_iCrywolfMonsterDarkElfDropZen;

BOOL g_bCrywolfBossMonsterItemDrop;
int g_iCrywolfBossMonsterItemDropRate;
int g_iCrywolfBossMonsterDropZenRate;
int g_iCrywolfBossMonsterDropZen;
int g_iCrywolfApplyMvpBenefit;
int g_iCrywolfApplyMvpPenalty;
int g_iSkillDistanceCheck;
int g_iSkillDistanceCheckTemp;
int g_iSkillDistanceKick;
int g_iSkillDistanceKickCount;
int g_iSkillDiatanceKickCheckTime;

BOOL g_bKanturuMayaHandItemDrop;
int g_iKanturuMayaHandItemDropRate;
int g_iKanturuMayaHandDropZenRate;
int g_iKanturuMayaHandDropZen;
BOOL g_bKanturuNightmareItemDrop;
int g_iKanturuNightmareItemDropRate;
int g_iKanturuNightmareDropZenRate;
int g_iKanturuNightmareDropZen;
BOOL g_bKanturuSpecialItemDropOn;
int g_iKanturuMoonStoneDropRate;
int g_iKanturuJewelOfHarmonyDropRate;

BOOL	g_bRaklionSelupanItemDrop;
int	g_iRaklionSelupanItemDropRate;
int	g_iRaklionSelupanDropZenRate;
BOOL	g_bRaklionSelupanDropZen;

BOOL	g_bLuckyCoinEventOn;
int	g_iLuckyCoinDropRate;

BOOL g_bHallowinDayEventOn;
int g_iHallowinDayEventItemDropRate;
int g_iHallowinDayEventJOLBlessDropRate;
int g_iHallowinDayEventJOLAngerDropRaTe;
int g_iHallowinDayEventJOLScreamDropRate;
int g_iHallowinDayEventJOLFoodDropRate;
int g_iHallowinDayEventJOLDrinkDropRate;
int g_iHallowinDayEventJOLPolymorphRingDropRate;

//Season2.5 add-on
int g_iSantaPolymorphRingDropOn;
int g_iSantaPolymorphRingDropRate;
int g_iCondorFlameDropRate;

//Season3 add-on
BOOL g_bCherryBlossomEventOn;
int g_iCherryBlossomEventItemDropRate;
int g_iML_OldScrollDropRate = 10;
int g_iML_CovenantOfIllusionDropRate = 10;
int g_iML_AngelKingsPaperDropRate = 10;
int g_iML_BloodBoneDropRate = 10;
int g_iML_EyesOfDevilSquareDropRate = 10;
int g_iML_KeysOfDevilSquareDropRate = 10;
int g_iShadowPhantomMaxLevel = 220;

int g_bAbilityDebug; //For GMMNG

//Season 4.5 addon
int g_iXMasVisitCount = 0;
int g_iXMasEvent_LuckNumber1st = 100;
int g_iXMasEvent_LuckNumber2nd = 200;

DWORD dwgCheckSum[MAX_CHECKSUM_KEY];
char connectserverip[20];
int  connectserverport;
short gGameServerCode;
int  gPkTime;
BOOL g_bCastleGuildDestoyLimit;
DWORD  gItemNumberCount;
BOOL gStalkProtocol;
DWORD  gAttackEventRegenTime;
int  gYear;
BOOL gOnlyFireCrackerEffectUse;
int  g_iRingOrcKillGiftRate;
int  g_iRingDropGiftRate;
int  g_iXMasAttackEventDropRate;
int  g_iXMasAttackEventDropZen;

CSimpleModulus g_SimpleModulusCS;
CSimpleModulus g_SimpleModulusSC;

int  gEledoradoGoldGoblenItemDropRate;
int  gEledoradoTitanItemDropRate;
int  gEledoradoGoldDerconItemDropRate;
int  gEledoradoDevilLizardKingItemDropRate;
int  gEledoradoDevilTantarosItemDropRate;
int  gEledoradoGoldGoblenExItemDropRate;
int  gEledoradoTitanExItemDropRate;
int  gEledoradoGoldDerconExItemDropRate;
int  gEledoradoDevilLizardKingExItemDropRate;
int  gEledoradoDevilTantarosExItemDropRate;
int  gEledoradoGoldenRabbitRegenTime = 60;
int  gEledoradoGoldenDarkKnightRegenTime = 60;
int  gEledoradoGoldenDevilRegenTime = 60;
int  gEledoradoGoldenMonsterRegenTime = 60;
int  gEledoradoGoldenCrustRegenTime = 60;
int  gEledoradoGoldenSatirosRegenTime = 60;
int  gEledoradoGoldenTwintailRegenTime = 60;
int  gEledoradoGoldenIronKnightRegenTime = 60;
int  gEledoradoGoldenNeipinRegenTime = 60;
int gEledoradoGoldenGreatDragonRegenTime = 60;
int  giKundunRefillHPSec;
int  giKundunRefillHP;
int  giKundunRefillHPTime;
int  giKundunHPLogSaveTime;
BOOL gUseNPGGChecksum;
int g_ShieldSystemOn;
int g_iDamageDevideToSDRate;
int g_iDamageDevideToHPRate;
float g_fSuccessAttackRateOption;
int g_iSDChargingOption;
int g_iConstNumberOfShieldPoint;
int g_ShieldAutoRefillOn;
int g_ShieldAutoRefillOnSafeZone;
int g_PKLevelIncreaseOff;
int g_CompoundPotionDropOn;
int g_iCompoundPotionLv1DropRate;
int g_iCompoundPotionLv2DropRate;
int g_iCompoundPotionLv3DropRate;
int g_iCompoundPotionLv1DropLevel;
int g_iCompoundPotionLv2DropLevel;
int g_iCompoundPotionLv3DropLevel;
BOOL g_bShieldComboMissOptionOn;
int g_iShieldPotionLv1MixSuccessRate;
int g_iShieldPotionLv1MixMoney;
int g_iShieldPotionLv2MixSuccessRate;
int g_iShieldPotionLv2MixMoney;
int g_iShieldPotionLv3MixSuccessRate;
int g_iShieldPotionLv3MixMoney;
int g_iShieldGageConstA;
int g_iShieldGageConstB;
BOOL g_bCheckSpeedHack = TRUE;

char gMapName[MAX_NUMBER_MAP][255];

char g_szMapName[MAX_NUMBER_MAP][32]={"Lorencia", "Dungeon", "Devias", "Noria", "LostTower", "Exile", "Arena", "Atlans", "Tarkan", "Icarus", "BloodCastle1", "BloodCastle2", "BloodCastle3", "BloodCastle4", "BloodCastle5", "BloodCastle6", "BloodCastle7"};
char szGameServerVersion[12]=GAMESERVER_VERSION;
char szClientVersion[8]="000000";
BOOL bCanTrade=1;
BOOL bCanChaosBox=1;
BOOL bCanWarehouseLock=1;
int  MapMinUserLevel[MAX_NUMBER_MAP] = { 0, 20, 15, 10, 80, 0, 0, 60, 130, 0, 160, 10, 36, 80, 130, 170, 210, 310, 15, 30, 100, 160, 220, 280, 15, 50, 120, 180, 240, 300, 10, 10, 0, 0, 0};
BOOL gEnableBattleSoccer=1;
int  gLootingTime=3;
int  gPkItemDrop=1;
int  gItemDropPer=10;
int  gEvent1ItemDropTodayMax=1;
int  gEvent1ItemDropTodayPercent=80;
char gCountryName[20]="Kor";
int  gCharacterDeleteMinLevel=40;
BOOL gCreateCharacter=1;
BOOL gGuildCreate=1;
BOOL gGuildDestroy=1;
int  gGuildCreateLevel=100;
BOOL gItemSerialCheck=1;
float  gAddExperience=1.0f;
float  gAddZen=1.0f;
int  g_XMasEvent_StarOfXMasDropRate=80;
int  g_XMasEvent_ItemDropRateForStarOfXMas=2;
int  gFireCrackerDropRate=80;
int  g_ItemDropRateForgFireCracker=2;
int  gHeartOfLoveDropRate=80;
int  g_ItemDropRateForgHeartOfLove=2;
int  gGoldMedalDropRate=2;
int  gSilverMedalDropRate=2;
int  g_ItemDropRateForGoldMedal=2;
int  g_ItemDropRateForSilverMedal=2;
int  gBoxOfGoldDropRate=2;
int  g_ItemDropRateForBoxOfGold=2;
int  g_EventChipDropRateForBoxOfGold=2;
int  gEyesOfDevilSquareDropRate=2;
int  gKeyOfDevilSquareDropRate=2;
int  gDQChaosSuccessRateLevel1=75;
int  gDQChaosSuccessRateLevel2=70;
int  gDQChaosSuccessRateLevel3=65;
int  gDQChaosSuccessRateLevel4=60;
int  gDQChaosSuccessRateLevel5=55;
int  gDQChaosSuccessRateLevel6=50;
int  gDQChaosSuccessRateLevel7=45;
BOOL g_bBloodCastle=1;
int  g_iBloodCastle_StartHour=1;
int  g_iStoneDropRate=60;
int  g_iBloodCastle_OddEvenHour=0;
int  g_iAngelKingsPaperDropRate=10;
int  g_iBloodBoneDropRate=20;
BOOL g_bChaosCastle=1;
DWORD  gAttackSpeedTimeLimit=130;
DWORD  gHackCheckCount=5;
float gDecTimePerAttackSpeed=5.33f;
int  gMinimumAttackSpeedTime=8;
int  gDetectedHackKickCount=10;
int gTamaJJangKeepTime = 100;
int gTamaJJangDisappearTime = 1800;
int gTamaJJangDisappearTimeRandomRange = 1000;
BOOL gItemDropRingOfTransform=1;
int  gQuestNPCTeleportTime=60;
DWORD  gEledoradoGoldGoblenRegenTime=60;
DWORD  gEledoradoTitanRegenTime=60;
DWORD  gEledoradoGoldDerconRegenTime=60;
DWORD  gEledoradoDevilLizardKingRegenTime=60;
DWORD  gEledoradoDevilTantarosRegenTime=60;
int  gZenDurationTime=30;
int gMonsterHPAdjust = 100;
BOOL gEnableCheckPenetrationSkill=TRUE;

BOOL g_bDoCastleDeepEvent;
int gIsDropSetItemInCastleHuntZone;
int gSetItemInCastleHuntZoneDropRate;
int gSetItemInCastleHuntZoneDropLevel;
int g_iCastleItemMixLimit = 1;
CItemBagEx * CastleItemMixItemBag;
CItemBagEx * CastleHuntZoneBossItemBag;

bool MSSQL2008;

void CheckSumFileLoad(char* szCheckSum);

//identical
void gSetDate()
{
	tm *today;
	time_t ltime;

	time(&ltime);
	today=localtime(&ltime);
	
	today->tm_year=today->tm_year+1900;
	gYear=today->tm_year;
}

//identical
BOOL gJoomin15Check(char* szJN)
{
	int tyear=1900;
	char szTyear[3]="";
	
	if ( szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear)-1);

	tyear=tyear+atoi(&szTyear[0]);
	if ( (gYear-15 ) < tyear )
	{
		return 0;
	}
	return 1;
}

//identical	
BOOL gJoominCheck(char* szJN, int iLimitAge)
{

	if ( iLimitAge <0 )
	{
		return 1;
	}

	int tyear=1900;
	char szTyear[3]="";

	if ( szJN[6] == 51 || szJN[6] == 52)
	{
		tyear = 2000;
	}

	memcpy(&szTyear[0], szJN, sizeof(szTyear)-1);

	tyear=tyear+atoi(&szTyear[0]);
	if ( (gYear-iLimitAge ) < tyear )
	{
		return 0;
	}
	
	return 1;
}	


void GameMainInit(HWND hWnd)
{

	int n;
	int DataBufferSize;
	char* DataBuffer;
	int LevelOver_N;
	
	srand(time(NULL));
	ReadServerInfo();
	LogInit(TRUE);
	gSetDate();

	gDirPath.SetFirstPath(FIRST_PATH);
	gDirPath.SetFirstPath(FINAL_PATH);
	
	gServerType=GetPrivateProfileInt("GameServerInfo","ServerType",0, gDirPath.GetNewPath("commonserver.cfg") );
	gPartition=GetPrivateProfileInt("GameServerInfo","Partition",0, gDirPath.GetNewPath("commonserver.cfg") );
	gLanguage=GetPrivateProfileInt("GameServerInfo","Language",0, gDirPath.GetNewPath("commonserver.cfg") );
	
	gGameServerAuth.Init();
	gGameServerAuth.SetInfo(gLanguage, gPartition,0, szGameServerVersion, szServerName, gServerType, GameServerAuthCallBackFunc);
	gGameServerAuth.GetKey(&szAuthKey[0], 0, 5);

	DragonEvent = new CDragonEvent;
	
	if ( DragonEvent == 0 )
	{
		MsgBox("CDragonEvent %s", lMsg.Get( MSGGET(0,110)) );	// Memory allocation error
		return;
	}

	AttackEvent = new CAttackEvent;
	
	if ( AttackEvent == 0 )
	{
		MsgBox("AttackEvent %s", lMsg.Get(MSGGET(0,110)) );	// Memory allocation error
		return;
	}

	ReadCommonServerInfo();

	g_MapServerManager.LoadData( gDirPath.GetNewPath("MapServerInfo.dat"));

	if( g_CastleSiege.Ready(g_MapServerManager.GetMapSvrGroup()) == TRUE )
	{
		if( g_CastleSiege.LoadData(gDirPath.GetNewPath(".\\Events\\MuCastleData.dat")) )
		{
			g_CastleSiege.LoadPreFixData(gDirPath.GetNewPath("commonserver.cfg"));
			g_CastleSiege.SetDataLoadState(CASTLESIEGE_DATALOAD_2);
		}
	}

	gGameServerAuth.GetKey(szAuthKey, 10, 5);

	if ( gEnableServerDivision != 0 )
	{
		MessageBox(NULL, "서버분할이 가능한 서버입니다.", "Warning", MB_OK);
	}

	if ( gUdpSoc.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}

	if ( gUdpSocCER.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}
	int UDPPort = GetPrivateProfileInt("Connect","UDP-Port",60006,".\\Connect.ini");
	gUdpSocCER.RecvSet( UDPPort ); // Same as MuManager to JS ?

	gUdpSocCER.Run();

	if ( gUdpSocCE.CreateSocket() == 0)
	{
		MsgBox("UDP Socket create error");
		return;
	}

	gUdpSocCER.SetProtocolCore(ChaosEventProtocolCore); 
	gUdpSocCE.SetProtocolCore(ChaosEventProtocolCore);

	if ( false )
	{
		MsgBox(lMsg.Get(MSGGET(0, 210)) );	// No check on speed hack.
	}
	if ( false )
	{
		MsgBox("주의!! 캐릭터 데이터를 저장하지 않습니다.");
	}

	gObjInit();
	InitBattleSoccer();

	gGameServerAuth.RequestData(7);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();

	gMAttr.LoadAttr( DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(9);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();

	gMSetBase.LoadSetBase(DataBuffer, DataBufferSize);

	g_MonsterItemMng.Init();

	gLevelExperience[0]=0;
	LevelOver_N=1;

	for ( n=1;n<MAX_CHAR_LEVEL+1;n++)
	{
		gLevelExperience[n] = (((n+9)*n)*n)*10;

		if ( n > 255 )
		{
			gLevelExperience[n] += ((((LevelOver_N+9)*LevelOver_N)*LevelOver_N)*1000);
			LevelOver_N++;
		}
	}

	g_MasterLevelSystem.SetExperienceTable(); //season3 add-on

	char MapAttrName[MAX_NUMBER_MAP][36] =
	{
		".\\Terrains\\terrain1.att",		//
		".\\Terrains\\terrain2.att",		//
		".\\Terrains\\terrain3.att",		//
		".\\Terrains\\terrain4.att",		//
		".\\Terrains\\terrain5.att",		//
		".\\Terrains\\terrain6.att",		//
		".\\Terrains\\terrain7.att",		//
		".\\Terrains\\terrain8.att",		//
		".\\Terrains\\terrain9.att",		//
		".\\Terrains\\terrain10.att",	//

		".\\Terrains\\terrain11.att",	//

		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//
		".\\Terrains\\terrain12.att",	//

		".\\Terrains\\terrain19.att",	//
		".\\Terrains\\terrain19.att",	//
		".\\Terrains\\terrain19.att",	//
		".\\Terrains\\terrain19.att",	//
		".\\Terrains\\terrain19.att",	//
		".\\Terrains\\terrain19.att",	//

		".\\Terrains\\terrain25.att",	//
		".\\Terrains\\terrain25.att",	//
		".\\Terrains\\terrain25.att",	//
		".\\Terrains\\terrain25.att",	//
		".\\Terrains\\terrain25.att",	//
		".\\Terrains\\terrain25.att",	//

		".\\Terrains\\terrain31.att",	//
		".\\Terrains\\terrain32.att",	//
		".\\Terrains\\terrain33.att",	//
		".\\Terrains\\terrain34.att",	//
		".\\Terrains\\terrain35.att",	//
		".\\Terrains\\terrain36.att",	//
		".\\Terrains\\terrain37.att",	//
		".\\Terrains\\terrain38.att",	//
		".\\Terrains\\terrain39.att",	//
		".\\Terrains\\terrain40.att",	//

		".\\Terrains\\terrain41.att",	// GM Summon Zone
		".\\Terrains\\terrain42.att",	// Balgass Barracks
		".\\Terrains\\terrain43.att",	// Balgass Refugee

		".\\Terrains\\terrain46.att",	// reserved loading
		".\\Terrains\\terrain46.att",	// reserved loading

		".\\Terrains\\terrain46.att",	// Illusion Temple 1 = 45
		".\\Terrains\\terrain46.att",	// Illusion Temple 2
		".\\Terrains\\terrain46.att",	// Illusion Temple 3
		".\\Terrains\\terrain46.att",	// Illusion Temple 4
		".\\Terrains\\terrain46.att",	// Illusion Temple 5
		".\\Terrains\\terrain46.att",	// Illusion Temple 6 = 50

		//Season 3.0
		".\\Terrains\\terrain52.att",	// Elbeland

		".\\Terrains\\terrain12.att",	// Blood Castle 8
		".\\Terrains\\terrain19.att",	// ChaosCastle 7
		".\\Terrains\\terrain57.att",	// DevilSquare 7

		".\\Terrains\\terrain57.att",	// reserved loading

		".\\Terrains\\terrain57.att",	// Swamp of Calmness = 56

		//Season 4.0
		".\\Terrains\\terrain58.att",	// Raklion
		".\\Terrains\\terrain59.att",	// Hatchery
		".\\Terrains\\terrain62.att",	// Santa Village

		".\\Terrains\\terrain62.att",	// reserved loading
		".\\Terrains\\terrain62.att",	// reserved loading
		".\\Terrains\\terrain62.att",	// reserved loading
		//Season 4.6
		".\\Terrains\\terrain64.att",	// Vulcanus
		".\\Terrains\\terrain65.att",	// Duel Room
		//Season 5
#ifdef _GRAND_HERO_SYSTEM_
		".\\Terrains\\Terrain66.att", //66 Doppel Ganger-A
		".\\Terrains\\Terrain67.att", //67 Doppel Ganger-B
		".\\Terrains\\Terrain68.att", //68 Doppel Ganger-C
		".\\Terrains\\Terrain69.att", //69 Doppel Ganger-D
		".\\Terrains\\Terrain70.att", //70 Imperial Guardian-A
		".\\Terrains\\Terrain71.att", //71 Imperial Guardian-B
		".\\Terrains\\Terrain72.att", //72 Imperial Guardian-C 
		".\\Terrains\\Terrain73.att", //73 Imperial Guardian-D	//Season 5 ImperialFort
		".\\Terrains\\Terrain80.att", //74 Roren Market
		".\\Terrains\\Terrain80.att", //75 Roren Market
		".\\Terrains\\Terrain80.att", //76 Roren Market
		".\\Terrains\\Terrain80.att", //77 Roren Market
		".\\Terrains\\Terrain80.att", //78 Roren Market
		".\\Terrains\\Terrain80.att", //79 Roren Market
		".\\Terrains\\Terrain80.att", //80 Roren Market
		".\\Terrains\\Terrain81.att", //81 Karutan 1
		".\\Terrains\\Terrain82.att", //82 Karutan 2
		".\\Terrains\\Terrain83.att", //83 New Map
		".\\Terrains\\Terrain84.att", //84 New Map
		".\\Terrains\\Terrain85.att", //85 New Map
		".\\Terrains\\Terrain86.att", //86 New Map
		".\\Terrains\\Terrain87.att", //87 New Map
		".\\Terrains\\Terrain88.att", //88 New Map
		".\\Terrains\\Terrain89.att", //89 New Map
		".\\Terrains\\Terrain90.att", //90 New Map
#endif
	};

	for ( n=0;n<MAX_NUMBER_MAP;n++)
	{
		MapC[n].ItemInit();
		MapC[n].LoadMapAttr(gDirPath.GetNewPath(MapAttrName[n]), n);
	}

	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath(".\\Terrains\\terrain35_PEACE.att"),0);
	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath(".\\Terrains\\terrain35_OCCUPIED.att"),1);
	g_Crywolf.LoadCrywolfMapAttr(gDirPath.GetNewPath(".\\Terrains\\terrain35_WAR.att"),2);

	g_Kanturu.LoadKanturuMapAttr(gDirPath.GetNewPath(".\\Terrains\\terrain40_CLOSE.att"), 0);
	g_Kanturu.LoadKanturuMapAttr(gDirPath.GetNewPath(".\\Terrains\\terrain40_OPEN.att"), 1);


	DCInfo.Init();
	ShopDataLoad();
	wsGServer.CreateSocket(hWnd);
	wsJServerCli.CreateSocket(hWnd);
	wsDataCli.CreateSocket(hWnd);

	gGameServerAuth.GetKey(szAuthKey, 5,5 );

	wsRServerCli.CreateSocket(hWnd);
	wsEvenChipServerCli.CreateSocket(hWnd);
	GameServerInfoSend();
	GameMonsterAllAdd();

	acceptIP.Load(gDirPath.GetNewPath("Iplist.dat"));
	ConMember.Load(gDirPath.GetNewPath("ConnectMember.txt"));
	GCTeleportSend(gObj, 1, 1, 1, 2, 3);
	
	gGameServerAuth.GetKey(szAuthKey, 15,5 );

	g_Raklion.SetState(RAKLION_STATE_END);

	//gItemDropManager.Init();
}


int GetWarehouseUsedHowMuch(int UserLevel, int MasterLevel, BOOL IsLock)
{
	int rZen=0;

	int iBaseLevel = UserLevel+MasterLevel;

	rZen = (int)((iBaseLevel * iBaseLevel)* 0.1 * 0.4);

	if (bCanWarehouseLock == TRUE)
	{
		if ( IsLock != 0)
		{
			rZen = rZen + ( UserLevel * 2 );
		}
	}
	if ( rZen < 1 )
	{
		rZen=1;
	}

	if ( rZen >= 1000 )
	{
		rZen = (rZen/100)*100;
	}
	
	else if ( rZen >= 100 )
	{
		rZen = (rZen/10)*10;
	}
	
	if ( rZen == 0 )
	{
		rZen=1;
	}
	
	return rZen;
}


void GraphPaint(HWND hWnd)
{
	HDC hdc;
	RECT rect;
	int val[10];
	HBRUSH colBrush[4];
	int n;

	hdc = GetDC(hWnd);

	colBrush[0]=CreateSolidBrush( RGB(100, 100, 100));
	colBrush[1]=CreateSolidBrush( RGB(200, 100, 100));
	colBrush[2]=CreateSolidBrush( RGB(200, 200, 200));
	colBrush[3]=CreateSolidBrush( RGB(200, 200, 100));

	for ( n=0; n<4;n++)
	{
		val[0] = DCInfo.DefClass[n].Strength;
		val[1] = DCInfo.DefClass[n].Dexterity ;
		val[2] = DCInfo.DefClass[n].Vitality;
		val[3] = DCInfo.DefClass[n].Energy;
		val[4] = (int)DCInfo.DefClass[n].Life ;
		val[5] = (int)DCInfo.DefClass[n].Mana ;
		val[6] = (int)(DCInfo.DefClass[n].LevelLife * 10.0f);
		val[7] = (int)(DCInfo.DefClass[n].LevelMana * 10.0f);
		val[8] = (int)(DCInfo.DefClass[n].VitalityToLife * 10.0f);
		val[9] = (int)(DCInfo.DefClass[n].EnergyToMana * 10.0f);

		for (int k=0; k<10;k++)
		{
			rect.left = (k * 45) + (n * 10);
			rect.right = ((k * 45) + (n * 10))+10;
			rect.top = 0;
			rect.bottom = val[k];
			FillRect(hdc, &rect, colBrush[n]);
		}
	}
	
	ReleaseDC(hWnd, hdc);
	DeleteObject( (HGDIOBJ)colBrush[0]);
	DeleteObject( (HGDIOBJ)colBrush[1]);
	DeleteObject( (HGDIOBJ)colBrush[2]);
	DeleteObject( (HGDIOBJ)colBrush[3]);
	DeleteObject( (HGDIOBJ)val[0]);
}


void GameMonsterAllAdd()
{
	gCurPaintPlayer = 0;

	int result;

	for ( int n=0;n< gMSetBase.m_Count ;n++)
	{
		if ( DS_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			continue;
		}

		if ( BC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			if ( gMSetBase.m_Mp[n].m_Type != 232 )
			{
				continue;
			}
		}

		if ( CC_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE )
		{
			continue;
		}

		if ( IT_MAP_RANGE(gMSetBase.m_Mp[n].m_MapNumber) != FALSE && gMSetBase.m_Mp[n].m_Type != 381 && gMSetBase.m_Mp[n].m_Type != 382)
		{
			if( gMSetBase.m_Mp[n].m_Type == 380 || gMSetBase.m_Mp[n].m_Type == 383 || gMSetBase.m_Mp[n].m_Type == 384 )
			{
				g_IllusionTempleEvent.CreateNPCPosition(gMSetBase.m_Mp[n].m_MapNumber,gMSetBase.m_Mp[n].m_Type, n);
			}
			else if(gMSetBase.m_Mp[n].m_Type >= 386 || gMSetBase.m_Mp[n].m_Type <= 403)
			{
				g_IllusionTempleEvent.CreateMonsterPosition(gMSetBase.m_Mp[n].m_MapNumber,gMSetBase.m_Mp[n].m_Type, n);
			}

			continue;
		}
			
		result = gObjAddMonster(gMSetBase.m_Mp[n].m_MapNumber);

		if ( result >= 0 )
		{
			gObjSetPosMonster(result, n);
			gObjSetMonster(result, gMSetBase.m_Mp[n].m_Type);
			gCurPaintPlayer++;

			if ( BC_MAP_RANGE(gObj[result].MapNumber) )
			{
				if ( gObj[result].Class == 232 )
				{
					gObj[result].m_cBloodCastleIndex = g_BloodCastle.GetBridgeIndex(gObj[result].MapNumber);
				}
			}

				if ( gObj[result].Class == 216 )
				{
					g_CastleSiege.SetCrownIndex(result);
				}
				if( CRYWOLF_MAP_RANGE(gObj[result].MapNumber) )
				{
					if(gObj[result].Type == OBJ_NPC)
					{
						if(gObj[result].Class == 406 || gObj[result].Class == 407)
						{
							
						}
						else if ( CRYWOLF_ALTAR_CLASS_RANGE(gObj[result].Class) ) //Altar?
						{
							g_Crywolf.m_ObjSpecialNPC.AddObj(result);
						}
						else
						{
							g_Crywolf.m_ObjCommonNPC.AddObj(result);
						}
					}
				}
				if( CRYWOLF_MAP_RANGE(gObj[result].MapNumber) )
				{
					if(gObj[result].Type == OBJ_MONSTER)
					{
						g_Crywolf.m_ObjCommonMonster.AddObj(result);
					}
				}
		}
	}

	//gDevilSquareEvent = FALSE;
	//g_bChaosCastle = FALSE;
	//g_iUseRaklionEvent = FALSE;

	g_DevilSquare.Init();
	g_BloodCastle.LoadItemDropRate();

	if ( g_bBloodCastle != FALSE )
	{
		g_BloodCastle.Init(TRUE);
	}
	else
	{
		g_BloodCastle.Init(FALSE);
	}

	if ( g_bChaosCastle != FALSE )
	{
		g_ChaosCastle.Init(TRUE);
	}
	else
	{
		g_ChaosCastle.Init(FALSE);
	}
	if ( g_iIllusionTempleEvent != FALSE )
	{
		g_IllusionTempleEvent.Init();
	}
}

void GameMonsterAllCloseAndReLoad()
{
	for ( int n=0;n<OBJ_MAXMONSTER;n++)
	{
		if ( gObj[n].Type == OBJ_MONSTER || gObj[n].Type == OBJ_NPC )
		{
			

			if ( gObj[n].MapNumber == MAP_INDEX_KANTURU_BOSS )
			{
				continue;
			}
			if ( gObj[n].m_btCsNpcType )

			{
				continue;
			}

			if ( gObj[n].m_iCurrentAI )
			{
				gObj[n].Live = FALSE;
				gObjViewportListProtocolDestroy(&gObj[n]);
				gObjViewportClose(&gObj[n]);
			}
			
			gObjDel(n);
		}
	}

	g_Crywolf.m_ObjCommonNPC.Reset();
	g_Crywolf.m_ObjSpecialNPC.Reset();
	g_Crywolf.m_ObjCommonMonster.Reset();
	g_Crywolf.m_ObjSpecialMonster.Reset();

	gGameServerAuth.RequestData(7);
	int DataBufferSize = gGameServerAuth.GetDataBufferSize();
	char * DataBuffer = gGameServerAuth.GetDataBuffer();
	gMAttr.LoadAttr(DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(9);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gMSetBase.LoadSetBase(DataBuffer, DataBufferSize);

	g_IllusionTempleEvent.AllObjReset();

	g_MonsterItemMng.Init();
	gObjMonCount = 0;
	GameMonsterAllAdd();

	g_Raklion.SetState(RAKLION_STATE_END);
}

void GameMainFree()
{
	gDbSave.End();
	GDGameServerInfoSave();
	gObjEnd();
	ClearBattleSoccer();
	LogClose();
	CleanupGameguardAuth();
}

BOOL GMJoinServerConnect(LPSTR ConnectServer, DWORD wMsg)
{
	wsJServerCli.SetProtocolCore(SProtocolCore);
	int result = wsJServerCli.Connect(ConnectServer, JoinServerPort, wMsg);

	if ( result == 0 )
	{
		return FALSE;
	}

	GJServerLogin();

	LogAdd( lMsg.Get( MSGGET(1, 145)), ConnectServer);
	return TRUE;

}

BOOL GMRankingServerConnect(char* RankingServer, DWORD wMsg)
{
	wsRServerCli.SetProtocolCore(DevilSquareProtocolCore);
	int result = wsRServerCli.Connect(RankingServer, RANKING_SERVER_PORT, wMsg);
	if ( result == 0 )
	{
		return FALSE;
	}
	LogAdd("RankingServer Connect IP [ %s ]", RankingServer);
	return TRUE;
}

BOOL GMEventChipServerConnect(char* ServerIP, DWORD wMsg)
{
	wsEvenChipServerCli.SetProtocolCore(EventChipEventProtocolCore);
	int result = wsEvenChipServerCli.Connect(ServerIP, EVENT_CHIP_SERVER_PORT, wMsg);
	if ( result == 0 )
	{
		return FALSE;
	}

	LogAdd("EventChip Connect IP [ %s ]", ServerIP);
	return TRUE;
}

BOOL GMDataServerConnect(char* ConnectServer, WPARAM wMsg)
{
	wsDataCli.SetProtocolCore(DataServerProtocolCore);
	int result = wsDataCli.Connect(ConnectServer, DataServerPort, wMsg);
	if ( result == 0 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 147)), ConnectServer, DataServerPort);
		return FALSE;
	}
	DataServerLogin(0);
	LogAdd(lMsg.Get(MSGGET(1, 146)), ConnectServer, DataServerPort);
	return TRUE;
}

BOOL ExDataServerConnect(char* ConnectServer, DWORD wMsg)
{
	wsExDbCli.SetProtocolCore(ExDataServerProtocolCore);
	int result = wsExDbCli.Connect(ConnectServer, ExDbPort, wMsg);
	if ( result == 0 )
	{
		LogAdd(lMsg.Get(MSGGET(1, 147)), ConnectServer, ExDbPort);
		return FALSE;
	}

	ExDataServerLogin();
	LogAddC(2, "ExDB Server Online");
	return TRUE;
}

BOOL GameMainServerCreate(DWORD sMsg, DWORD cMsg)
{
	gDbSave.Begin();
	LogAdd( lMsg.Get( MSGGET(1, 148)), GameServerPort);
	return TRUE;
}


void GMServerMsgProc(WPARAM wParam, LPARAM lParam)
{
	
	switch ( lParam & 0xFFFF & 0xFFFF)
	{
	case FD_ACCEPT :
		/*SOCKET cSocket;
		IN_ADDR cInAddr;
		int ClientIndex;
		//LogAdd("SFD_ACCEPT MESSAGE");
		if( wsGServer.AcceptSocket(cSocket, cInAddr) == TRUE )
		{
			ClientIndex = gObjAddSearch(cSocket, inet_ntoa(cInAddr) );

			int addnumber = gObjAdd(cSocket, inet_ntoa(cInAddr), ClientIndex);
			if( addnumber >= 0 ) 
			{
				SCPJoinResultSend( addnumber, 0x01);
			}
			else 
			{// �??????� ?㈅??? �?..
				wsGServer.Close(cSocket);
			}
		}
		else {
			return;
		}*/
		break;
	}
}

void GMClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	int wp = wParam;
	int lp = lParam;

	switch ( lParam & 0xFFFF & 0xFFFF)
	{
		SOCKET socket;

		case 1:
			wsGServer.DataRecv(wParam);
			break;
		case 2:
			wsGServer.FDWRITE_MsgDataSend(wParam);
			break;
		case 32:
			socket = gObjGetSocket(wParam);
			break;

	}
}

void GMJoinClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch ( lParam & 0xFFFF & 0xFFFF )
	{
		case 1:
			wsJServerCli.DataRecv();
			break;
		case 2:
			wsJServerCli.FDWRITE_MsgDataSend();
			break;
		case 32:
			LogAddC(2, lMsg.Get(MSGGET(1, 149)));
			SendMessage(ghWnd, WM_CLOSE, 0, 0);
	}
}

void GMRankingClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch ( lParam & 0xFFFF & 0xFFFF )
	{
		case 1:
			wsRServerCli.DataRecv();
			break;
		case 2:
			wsRServerCli.FDWRITE_MsgDataSend();
			break;
		case 32:
			IsDevilSquareEventConnected = FALSE;
	}
}

void GMEventChipClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch ( lParam & 0xFFFF & 0xFFFF )
	{
		case 1:
			wsEvenChipServerCli.DataRecv();
			break;
		case 2:
			wsEvenChipServerCli.FDWRITE_MsgDataSend();
			break;
		case 32:
			IsEventChipServerConnected = FALSE;
	}
}

void ExDataClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch ( lParam & 0xFFFF & 0xFFFF )
	{
		case 1:
			wsExDbCli.DataRecv();
			break;
		case 2:
			wsExDbCli.FDWRITE_MsgDataSend();
			break;
		case 32:
			LogAddC(2, lMsg.Get(MSGGET(1, 150)));
			wsExDbCli.Close();

			for ( int i =0;i<OBJMAX;i++)
			{
				if ( gObjIsConnectedGP(i) == TRUE )
				{
					PMSG_FRIEND_STATE pMsg;
					
					pMsg.h.set((LPBYTE)&pMsg, 0xC4 , sizeof(pMsg) );
					pMsg.State = -4;

					DataSend(i, (LPBYTE)&pMsg, sizeof(pMsg) );

					gObj[i].m_FriendServerOnline = FRIEND_SERVER_STATE_OFFLINE;
				}
			}

			LogAddTD("Error-L1 : Friend Server Down (State Send Ok)");
			LogAddC(2, "Error-L1 : Friend Server Down (State Send Ok)");
			break;
	}
}

void GMDataClientMsgProc(WPARAM wParam, LPARAM lParam)
{
	switch ( lParam & 0xFFFF & 0xFFFF )
	{
		case 1:
			wsDataCli.DataRecv();
			break;
		case 2:
			wsDataCli.FDWRITE_MsgDataSend();
			break;
		case 32:
			LogAddC(2, lMsg.Get(MSGGET(1, 150)));
	}
}

void ReadServerInfo()
{
	if (!IsFile(SERVER_INFO_PATH))
	{
		MsgBox("ServerInfo.dat file not found");
	}
	GetPrivateProfileString("GameServerInfo","ServerName","",szServerName,50,SERVER_INFO_PATH);
	gGameServerCode=GetPrivateProfileInt("GameServerInfo","ServerCode",0,SERVER_INFO_PATH);
	bCanConnectMember=GetPrivateProfileInt("GameServerInfo","ConnectMemberLoad",0,SERVER_INFO_PATH);
	bCanChangeCharacterName=GetPrivateProfileInt("GameServerInfo","ChangeCharacterName",0,SERVER_INFO_PATH);
}

bool RESETSTART = false;

void ReadCommonServerInfo()
{
	char szTemp[256];
	char szCheckSum[256];
	char* cvstr;
	int DataBufferSize;
	char* DataBuffer;
	char szlMsgName[256];

	ReadServerInfo();

	gGameServerAuth.RequestData(8);

	DataBufferSize = gGameServerAuth.GetDataBufferSize();

	DataBuffer = gGameServerAuth.GetDataBuffer();

	gGateC.Load(DataBuffer, DataBufferSize);

	if(!IsFile(gDirPath.GetNewPath("commonserver.cfg")))
	{
		MsgBox("[commonserver.cfg] file not found");
	}

	GetPrivateProfileString("GameServerInfo", "Language", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gLanguage = atoi(szTemp);
	gStalkProtocol	= GetPrivateProfileInt("GameServerInfo","StalkProtocol",0,gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "StalkProtocolId", "0", gStalkProtocolId, 10, gDirPath.GetNewPath("commonserver.cfg"));

	if(gStalkProtocol != 0)
	{
		LogAdd("Stalk Protocol ID = '%s' ", gStalkProtocolId);
	}

	if(g_SimpleModulusCS.LoadDecryptionKey(gDirPath.GetNewPath("Dec1.dat")) == FALSE)
	{
		MsgBox("Dec1.dat file not found");
	}

	if(g_SimpleModulusSC.LoadEncryptionKey(gDirPath.GetNewPath("Enc2.dat")) == FALSE)
	{
		MsgBox("Enc2.dat file not found");
	}

	strcpy(szKorItemTextFileName, gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
	strcpy(szKorSkillTextFileName, gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));

	switch(gLanguage)
	{
		case 0: // Korea
			strcpy(szlMsgName, gDirPath.GetNewPath("message_kor.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\kor\\item(kor).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\kor\\skill(kor).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\kor\\Quest(Kor).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\kor\\CheckSum.dat"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\kor\\movereq(Kor).txt"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\kor\\commonloc.cfg"));
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
		case 1: // English
			strcpy(szlMsgName, gDirPath.GetNewPath("message_eng.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\eng\\item(eng).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\eng\\skill(eng).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\eng\\Quest(eng).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\eng\\movereq(Eng).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\eng\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\eng\\commonloc.cfg"));
			strcpy(gCountryName, "Eng");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
		case 2: // Japan
			strcpy(szlMsgName, gDirPath.GetNewPath("message_jpn.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\jpn\\item(jpn).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\jpn\\skill(jpn).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\jpn\\Quest(jpn).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\jpn\\movereq(jpn).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\jpn\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\jpn\\commonloc.cfg"));
			strcpy(gCountryName, "Jpn");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
		case 3: // China
			strcpy(szlMsgName, gDirPath.GetNewPath("message_chs.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\chs\\item(chs).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\chs\\skill(chs).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\chs\\Quest(chs).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\chs\\movereq(chs).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\chs\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\chs\\commonloc.cfg"));
			strcpy(gCountryName, "Chs");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
		case 4: // Taiwan
			strcpy(szlMsgName, gDirPath.GetNewPath("message_tai.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tai\\item(tai).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tai\\skill(tai).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\tai\\Quest(tai).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\tai\\movereq(tai).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\tai\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\tai\\commonloc.cfg"));
			strcpy(gCountryName, "Tai");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
		case 5: // Thailand
			strcpy(szlMsgName, gDirPath.GetNewPath("message_tha.wtf"));
			strcpy(szItemTextFileName, gDirPath.GetNewPath("lang\\tha\\item(tha).txt"));
			strcpy(szSkillTextFileName, gDirPath.GetNewPath("lang\\tha\\skill(tha).txt"));
			strcpy(szQuestTextFileName, gDirPath.GetNewPath("lang\\tha\\Quest(tha).txt"));
			strcpy(szMoveReqFileName, gDirPath.GetNewPath("lang\\tha\\movereq(tha).txt"));
			strcpy(szCheckSum, gDirPath.GetNewPath("lang\\tha\\CheckSum.dat"));
			strcpy(szCommonlocIniFileName, gDirPath.GetNewPath("lang\\tha\\commonloc.cfg"));
			strcpy(gCountryName, "Tha");
			gNonPK = GetPrivateProfileInt("GameServerInfo","NonPK",0, SERVER_INFO_PATH);
			if(gNonPK != 0)
			{
				LogAdd("NON-PK Server");
			}
			gPkLimitFree = GetPrivateProfileInt("GameServerInfo","PkLimitFree",0, SERVER_INFO_PATH);
			if(gPkLimitFree != 0)
			{
				LogAdd("PK Limit Free Server");
			}
			gNewServer = GetPrivateProfileInt("GameServerInfo","NewServer",0, SERVER_INFO_PATH);
			if(gNewServer != 0)
			{
				LogAdd("New Server");
			}
			gEventOff = GetPrivateProfileInt("GameServerInfo","EventOff",0, SERVER_INFO_PATH);
			if(gEventOff != 0)
			{
				LogAdd("EventOff");
			}
			break;
	}

	CheckSumFileLoad(szCheckSum);

	DWORD dwGGErrCode = InitGameguardAuth("", OBJMAXUSER);

	if ( dwGGErrCode != 0 )
	{
		MsgBox("Failed initialization of GameGaurd !!! , Error: %d", dwGGErrCode);
		return;
	}

	lMsg.LoadWTF(szlMsgName);
	SetMapName();

	gGameServerAuth.RequestData(0);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	OpenItemScript( DataBuffer, DataBufferSize);

	if(gLanguage != 0)
	{
		gGameServerAuth.RequestData(1);
		DataBufferSize = gGameServerAuth.GetDataBufferSize();
		DataBuffer = gGameServerAuth.GetDataBuffer();
		OpenItemNameScript( DataBuffer, DataBufferSize);
	}

	gGameServerAuth.RequestData(2);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	MagicDamageC.LogSkillList(DataBuffer, DataBufferSize);

	if(gLanguage != 0)
	{
		gGameServerAuth.RequestData(3);
		DataBufferSize = gGameServerAuth.GetDataBufferSize();
		DataBuffer = gGameServerAuth.GetDataBuffer();
		MagicDamageC.LogSkillNameList(DataBuffer, DataBufferSize);
	}

	SkillSpearHitBox.Load(gDirPath.GetNewPath("skillSpear.hit"));
	SkillElectricSparkHitBox.Load(gDirPath.GetNewPath("skillElect.hit"));
	//SkillDrainLifeHitBox.Load(gDirPath.GetNewPath("SkillDrainLife.hit"));
	//SkillLightingOrbHitBox.Load(gDirPath.GetNewPath("SkillLightingOrb.hit"));

	gGameServerAuth.RequestData(26);

	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();


	gSetItemOption.LoadOptionInfo(DataBuffer, DataBufferSize);

	gGameServerAuth.RequestData(28);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gSetItemOption.LoadTypeInfo(DataBuffer, DataBufferSize);

	g_kJewelOfHarmonySystem.LoadScript(gDirPath.GetNewPath("JewelOfHarmonyOption.txt"));
	g_kJewelOfHarmonySystem.LoadScriptOfSmelt(gDirPath.GetNewPath("JewelOfHarmonySmelt.txt"));
	g_kItemSystemFor380.Load380ItemOptionInfo(gDirPath.GetNewPath("ItemAddOption.txt"));
	g_ItemAddOption.Load(gDirPath.GetNewPath("ItemAddOption.txt"));
	g_MasterSkillSystem.Load(gDirPath.GetNewPath("MasterSkillTree.txt"));
	g_SocketOption.LoadScript(gDirPath.GetNewPath("socketitem.txt"));

	gGameServerAuth.RequestData(24);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	gMoveCommand.Load(DataBuffer, DataBufferSize);
	gMoveCommand.LoadMoveLevel(gDirPath.GetNewPath("MoveLevel.txt"));

	ConMember.Load(gDirPath.GetNewPath("ConnectMember.txt"));

	gGameServerAuth.RequestData(4);
	DataBufferSize = gGameServerAuth.GetDataBufferSize();
	DataBuffer = gGameServerAuth.GetDataBuffer();
	g_QuestInfo.LoadQuestInfo(DataBuffer, DataBufferSize);	
	gGameServerAuth.GetClientVersion(szTemp, szGameServerExeSerial);

	cvstr = strtok(szTemp, ".");
	szClientVersion[0] = cvstr[0];
	cvstr = strtok(NULL, ".");
	szClientVersion[1] = cvstr[0];
	szClientVersion[2] = cvstr[1];
	cvstr = strtok(NULL, ".");
	szClientVersion[3] = cvstr[0];
	szClientVersion[4] = cvstr[1];	


	TMonsterSkillElement::LoadData(gDirPath.GetNewPath("MonsterSkillElement.txt"));
	TMonsterSkillUnit::LoadData(gDirPath.GetNewPath("MonsterSkillUnit.txt"));
	TMonsterSkillManager::LoadData(gDirPath.GetNewPath("MonsterSkill.txt"));
	TMonsterAIElement::LoadData(gDirPath.GetNewPath("MonsterAIElement.txt"));
	TMonsterAIAutomata::LoadData(gDirPath.GetNewPath("MonsterAutomata.txt"));
	TMonsterAIUnit::LoadData(gDirPath.GetNewPath("MonsterAIUnit.txt"));
	TMonsterAIRule::LoadData(gDirPath.GetNewPath("MonsterAIRule.txt"));
	TMonsterAIGroup::LoadData(gDirPath.GetNewPath("MonsterAIGroup.txt"));


	g_Crywolf.LoadData(gDirPath.GetNewPath(".\\Events\\Crywolf.dat"));


	g_SkillAdditionInfo.Load("SkillAdditionInfo.dat");


	g_Kanturu.LoadData(gDirPath.GetNewPath(".\\Events\\Kanturu.dat"));
	g_KanturuMonsterMng.LoadData(gDirPath.GetNewPath("KanturuMonsterSetBase.txt"));


	g_PCBangPointSystem.Load(gDirPath.GetNewPath("PCBangPointItemOpt.txt"));

	g_Raklion.LoadData(gDirPath.GetNewPath(".\\Events\\Raklion.dat"));

	GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gCreateCharacter = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "CharacterDeleteMinLevel", "40", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gCharacterDeleteMinLevel = atoi(szTemp);


	int iMaxUser = GetPrivateProfileInt("GameServerInfo","NumberOfMaxUser",500, gDirPath.GetNewPath("commonserver.cfg"));

	if(iMaxUser >= 0 && iMaxUser <= OBJMAXUSER)
	{
		gServerMaxUser = iMaxUser;
		LogAddTD("[Option Reload] ★★★ MaxUser ☆☆☆  : %d", gServerMaxUser);
	}


	g_iServerGroupGuildChatting = GetPrivateProfileInt("GameServerInfo","ServerGroupGuildChatting",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iServerGroupUnionChatting = GetPrivateProfileInt("GameServerInfo","ServerGroupUnionChatting",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gGuildCreate = atoi(szTemp);

	LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
	GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));

	gGuildDestroy = atoi(szTemp);
	LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
	GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gGuildCreateLevel = atoi(szTemp);

	LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);

	g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("GameServerInfo", "SpeedHackPlayerBlock", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	SpeedHackPlayerBlock = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "ItemSerialCheck", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gItemSerialCheck = atoi(szTemp);
	GetPrivateProfileString("GameServerInfo", "AddExperience", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gAddExperience = atof(szTemp);	
	GetPrivateProfileString("GameServerInfo", "AddZen", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gAddZen = atof(szTemp);	
	GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	bCanTrade = atoi(szTemp);

	if(bCanTrade != 0)
	{
		LogAddTD(lMsg.Get(407));
	}
	else
	{
		LogAddTD(lMsg.Get(408));
	}

	bCanChaosBox = GetPrivateProfileInt("GameServerInfo","ChaosBox",0, gDirPath.GetNewPath("commonserver.cfg"));
	gChaosEvent = GetPrivateProfileInt("GameServerInfo","ChaosEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "ChaosEventServer", "210.181.89.241", gChaosEventServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));
	LogAdd("[Option] ChaosBox = %d", bCanChaosBox);
	LogAdd("[Option] ChaosEvent = %d", gChaosEvent);
	LogAdd("[Option] ChaosEventServer = %s", gChaosEventServerIp);
	LogAdd("[Option] AttackEventRegenTime = %d", gAttackEventRegenTime);
	GetPrivateProfileString("GameServerInfo", "PKTIME", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gPkTime = atoi(szTemp);

	if(gPkTime != 0)
	{
		LogAddTD(lMsg.Get(409), gPkTime);
	}

	GetPrivateProfileString("GameServerInfo", "MonsterHp", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gMonsterHp = atoi(szTemp);

	if(gMonsterHp != 0)
	{
		LogAddTD(lMsg.Get(410), gMonsterHp);
	}

	GetPrivateProfileString("GameServerInfo", "LootingTime", "3", szTemp, 5, szCommonlocIniFileName);
	gLootingTime = atoi(szTemp);

	if(gLootingTime != 0)
	{
		LogAddTD("[Option] Auto Looting Time Set : %d", gLootingTime);
	}

	GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gPkItemDrop = atoi(szTemp);

	if(gPkItemDrop != 0)
	{
		LogAddTD(lMsg.Get(MSGGET(1, 155)));
	}
	else
	{
		LogAddTD(lMsg.Get(MSGGET(1, 156)));
	}

	GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gItemDropPer = atoi(szTemp);
	LogAddTD(lMsg.Get(413), gItemDropPer);
	gZenDurationTime = GetPrivateProfileInt("GameServerInfo","ZenDurationTime",30, gDirPath.GetNewPath("commonserver.cfg"));
	gEventChipEvent = GetPrivateProfileInt("GameServerInfo","EventChipEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	gBoxOfGoldDropRate = GetPrivateProfileInt("GameServerInfo","BoxOfGoldDropRate",2, gDirPath.GetNewPath("commonserver.cfg"));
	g_ItemDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo","ItemDropRateForBoxOfGold",2, gDirPath.GetNewPath("commonserver.cfg"));
	g_EventChipDropRateForBoxOfGold = GetPrivateProfileInt("GameServerInfo","EventChipDropRateForBoxOfGold",2, gDirPath.GetNewPath("commonserver.cfg"));

	if ( gDevilSquareEvent == FALSE )
	{
		g_DevilSquare.SetClose();
	}

	gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo","AttackSpeedTimeLimit",800, gDirPath.GetNewPath("commonserver.cfg"));
	bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo","IsIgnorePacketHackDetect",0, gDirPath.GetNewPath("commonserver.cfg"));
	gHackCheckCount = GetPrivateProfileInt("GameServerInfo","HackCheckCount",5, gDirPath.GetNewPath("commonserver.cfg"));
	gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo","MinimumAttackSpeedTime",200, gDirPath.GetNewPath("commonserver.cfg"));
	gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo","DetectedHackKickCount",10, gDirPath.GetNewPath("commonserver.cfg"));
	gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo","IsKickDetecHackCountLimit",0, gDirPath.GetNewPath("commonserver.cfg"));

	gTamaJJangEvent = GetPrivateProfileInt("GameServerInfo", "TamaJJangEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangKeepTime = GetPrivateProfileInt("GameServerInfo", "TamaJJangKeepTime", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangDisappearTime = GetPrivateProfileInt("GameServerInfo", "TamaJJangDisappearTime", 1800, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangDisappearTimeRandomRange = GetPrivateProfileInt("GameServerInfo", "TamaJJangDisappearTimeRandomRange", 1800, gDirPath.GetNewPath("commonserver.cfg"));
	gTamaJJangTime = 10;

	gIsItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo","IsItemDropRingOfTransform",0, gDirPath.GetNewPath("commonserver.cfg"));
	gItemDropRingOfTransform = GetPrivateProfileInt("GameServerInfo","ItemDropRingOfTransform",1, gDirPath.GetNewPath("commonserver.cfg"));

	gWriteChatLog = GetPrivateProfileInt("GameServerInfo","WriteChatLog",0, gDirPath.GetNewPath("commonserver.cfg"));

	gDisconnectHackUser = GetPrivateProfileInt("GameServerInfo","DisconnectHackUser",0, gDirPath.GetNewPath("commonserver.cfg"));
	gUseNPGGChecksum = GetPrivateProfileInt("GameServerInfo","UseNPGGChecksum",0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "DecTimePerAttackSpeed", "5.33", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
	gDecTimePerAttackSpeed = atof(szTemp);
	gSpeedHackPenalty = GetPrivateProfileInt("GameServerInfo","SpeedHackPenalty",0, gDirPath.GetNewPath("commonserver.cfg"));

	gDQChaosSuccessRateLevel1 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel1",75, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel2 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel2",70, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel3 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel3",65, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel4 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel4",60, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel5 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel5",55, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel6 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel6",50, gDirPath.GetNewPath("commonserver.cfg"));
	gDQChaosSuccessRateLevel7 = GetPrivateProfileInt("GameServerInfo","DQChaosSuccessRateLevel7",45, gDirPath.GetNewPath("commonserver.cfg"));

	gWriteSkillLog = GetPrivateProfileInt("GameServerInfo","WriteSkillLog",0, gDirPath.GetNewPath("commonserver.cfg"));

	gQuestNPCTeleportTime = GetPrivateProfileInt("GameServerInfo","QuestNPCTeleportTime",900, gDirPath.GetNewPath("commonserver.cfg"));

#ifdef INTERNATIONAL_JAPAN
	g_iJapan1StAnivItemDropRate = GetPrivateProfileInt("GameServerInfo","Japan1StAnivItemDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
#endif

	g_iMarkOfTheLord = GetPrivateProfileInt("GameServerInfo","MarkOfTheLord",0, gDirPath.GetNewPath("commonserver.cfg"));


	g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
	
	giKundunRefillHPSec = GetPrivateProfileInt("GameServerInfo","KundunRefillHPSec",500, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunRefillHP = GetPrivateProfileInt("GameServerInfo","KundunRefillHP",10000, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunRefillHPTime = GetPrivateProfileInt("GameServerInfo","KundunRefillHPTime",600, gDirPath.GetNewPath("commonserver.cfg"));
	giKundunHPLogSaveTime = GetPrivateProfileInt("GameServerInfo","KundunHPLogSaveTime",120, gDirPath.GetNewPath("commonserver.cfg"));

	g_bFenrirStuffItemDrop = GetPrivateProfileInt("GameServerInfo","FenrirStuffItemDrop", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iFenrirStuff_01_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_01_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_01_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_01_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_01_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iFenrirStuff_02_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_02_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_02_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_02_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_02_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iFenrirStuff_03_DropLv_Min = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropLv_Min", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_03_DropLv_Max = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropLv_Max", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_03_DropMap = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropMap", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirStuff_03_DropRate = GetPrivateProfileInt("GameServerInfo","FenrirStuff_03_DropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iFenrirRepairRate = GetPrivateProfileInt("GameServerInfo","FenrirRepairRate", 4000, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirDefaultMaxDurSmall = GetPrivateProfileInt("GameServerInfo","FenrirDefaultMaxDurSmall", 200, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrirElfMaxDurSmall = GetPrivateProfileInt("GameServerInfo","FenrirElfMaxDurSmall", 160, gDirPath.GetNewPath("commonserver.cfg"));

	g_iFenrir_01Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_01Level_MixRate", 70, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrir_02Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_02Level_MixRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
	g_iFenrir_03Level_MixRate = GetPrivateProfileInt("GameServerInfo","Fenrir_03Level_MixRate", 30, gDirPath.GetNewPath("commonserver.cfg"));

	g_bCrywolfMonsterDarkElfItemDrop = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iCrywolfMonsterDarkElfItemDropRate = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCrywolfMonsterDarkElfDropZenRate = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCrywolfMonsterDarkElfDropZen = GetPrivateProfileInt("GameServerInfo","CrywolfMonsterDarkElfDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bCrywolfBossMonsterItemDrop = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iCrywolfBossMonsterItemDropRate = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCrywolfBossMonsterDropZenRate = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCrywolfBossMonsterDropZen = GetPrivateProfileInt("GameServerInfo","CrywolfBossMonsterDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
		
	g_iCrywolfApplyMvpBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfApplyMvpBenefit",0, gDirPath.GetNewPath("commonserver.cfg"));

	int iCrywolfPlusChaosRateBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfPlusChaosRateBenefit",0, gDirPath.GetNewPath("commonserver.cfg"));
	int iCrywolfMonHPRateBenefit = GetPrivateProfileInt("GameServerInfo","CrywolfMonHPRateBenefit", 100, gDirPath.GetNewPath("commonserver.cfg"));
	int iCrywolfKundunHPRefillState = GetPrivateProfileInt("GameServerInfo","CrywolfKundunHPRefillBenefit", 1, gDirPath.GetNewPath("commonserver.cfg"));

	g_CrywolfSync.SetKundunHPRefillState(iCrywolfKundunHPRefillState);
	g_CrywolfSync.SetPlusChaosRate(iCrywolfPlusChaosRateBenefit);
	g_CrywolfSync.SetMonHPBenefitRate(iCrywolfMonHPRateBenefit);

	g_iCrywolfApplyMvpPenalty = GetPrivateProfileInt("GameServerInfo","CrywolfApplyMvpPenalty",0, gDirPath.GetNewPath("commonserver.cfg"));

	int iCrywolfGemDropPenaltyRate = GetPrivateProfileInt("GameServerInfo","CrwyolfGemDropPenaltyRate",100, gDirPath.GetNewPath("commonserver.cfg"));
	int iCrywolfGettingExpPenaltyRate = GetPrivateProfileInt("GameServerInfo","CrwyolfGettingExpPenaltyRate",100, gDirPath.GetNewPath("commonserver.cfg"));

	g_CrywolfSync.SetGemDropPenaltiyRate(iCrywolfGemDropPenaltyRate);
	g_CrywolfSync.SetGettingExpPenaltyRate(iCrywolfGettingExpPenaltyRate);

	int iKanturuEnableValue = GetPrivateProfileInt("GameServerInfo","KanturuEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_Kanturu.SetKanturuEnable(iKanturuEnableValue);
	
	g_iBlockKanturuMapEnter = GetPrivateProfileInt("GameServerInfo","BlockKanturuMapEnter",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlockCastleSiegeMapEnter = GetPrivateProfileInt("GameServerInfo","BlockCastleSiegeMapEnter",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bKanturuMayaHandItemDrop = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuMayaHandItemDropRate = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuMayaHandDropZenRate = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuMayaHandDropZen = GetPrivateProfileInt("GameServerInfo","KanturuMayaHandDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bKanturuNightmareItemDrop = GetPrivateProfileInt("GameServerInfo","KanturuNightmareItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuNightmareItemDropRate = GetPrivateProfileInt("GameServerInfo","KanturuNightmareItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuNightmareDropZenRate = GetPrivateProfileInt("GameServerInfo","KanturuNightmareDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuNightmareDropZen = GetPrivateProfileInt("GameServerInfo","KanturuNightmareDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bKanturuSpecialItemDropOn = GetPrivateProfileInt("GameServerInfo","KanturuSpecialItemDropOn",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iKanturuMoonStoneDropRate = GetPrivateProfileInt("GameServerInfo","KanturuMoonStoneDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iKanturuJewelOfHarmonyDropRate = GetPrivateProfileInt("GameServerInfo","KanturuJewelOfHarmonyDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));

	//CHECK GS-N POSITION
	int iRaklionEnableValue = GetPrivateProfileInt("GameServerInfo","RaklionEvent",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_Raklion.SetRaklionEnable(iRaklionEnableValue);

	g_bRaklionSelupanItemDrop = GetPrivateProfileInt("GameServerInfo","RaklionSelupanItemDrop",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRaklionSelupanItemDropRate = GetPrivateProfileInt("GameServerInfo","RaklionSelupanItemDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iRaklionSelupanDropZenRate = GetPrivateProfileInt("GameServerInfo","RaklionSelupanDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_bRaklionSelupanDropZen = GetPrivateProfileInt("GameServerInfo","RaklionSelupanDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iBlockRaklionMapEnter = GetPrivateProfileInt("GameServerInfo","BlockRaklionMapEnter",0, gDirPath.GetNewPath("commonserver.cfg"));

	g_bHallowinDayEventOn = GetPrivateProfileInt("GameServerInfo","HallowinEventOn",0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventItemDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventPumpkinOfLuckDropRate",100, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLBlessDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLBlessDropRate",10, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLAngerDropRaTe = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLAngerDropRate",15, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLScreamDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLScreamDropRate",15, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLFoodDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLFoodDropRate",30, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLDrinkDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLDrinkDropRate",25, gDirPath.GetNewPath("commonserver.cfg"));
	g_iHallowinDayEventJOLPolymorphRingDropRate = GetPrivateProfileInt("GameServerInfo","HallowinEventJOLPolymorphRingDropRate", 5, gDirPath.GetNewPath("commonserver.cfg"));

	//Season 2.5 addon
	g_iSantaPolymorphRingDropOn = GetPrivateProfileInt("GameServerInfo","SantaPolymorphRingDropOn", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSantaPolymorphRingDropRate = GetPrivateProfileInt("GameServerInfo","SantaPolymorphRingDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));

	g_bNewYearLuckyBagMonsterEventOn = GetPrivateProfileInt("GameServerInfo","NewYearLuckyBagMonsterEventOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_IllusionTempleEvent.ReadCommonServerInfo();

	g_iCondorFlameDropRate = GetPrivateProfileInt("GameServerInfo","CondorFlameDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));

	//Season 3 add-on
	g_bCherryBlossomEventOn = GetPrivateProfileInt("GameServerInfo","CherryBlossomEventOn", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCherryBlossomEventItemDropRate = GetPrivateProfileInt("GameServerInfo","CherryBlossomEventItemDropRate", 8000, gDirPath.GetNewPath("commonserver.cfg"));

	//Season4.5 add-on
	g_bLuckyCoinEventOn = GetPrivateProfileInt("GameServerInfo","LuckyCoinEventOn", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iLuckyCoinDropRate = GetPrivateProfileInt("GameServerInfo","LuckyCoinDropRate", 1000, gDirPath.GetNewPath("commonserver.cfg"));

	g_MasterLevelSystem.ReadCommonServerInfo();

	g_iML_OldScrollDropRate = GetPrivateProfileInt("GameServerInfo","ML_OldScrollDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iML_CovenantOfIllusionDropRate = GetPrivateProfileInt("GameServerInfo","ML_CovenantOfIllusionDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iML_AngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","ML_AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iML_BloodBoneDropRate = GetPrivateProfileInt("GameServerInfo","ML_BloodBoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iML_EyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","ML_EyesOfDevilSquareDropRate ", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iML_KeysOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","ML_KeyOfDevilSquareDropRate ", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iShadowPhantomMaxLevel = GetPrivateProfileInt("GameServerInfo","ShadowPhantomMaxLevel", 220, gDirPath.GetNewPath("commonserver.cfg"));

	GetPrivateProfileString("ConnectServerInfo", "IP", "", connectserverip, 20, szCommonlocIniFileName);
	GetPrivateProfileString("ConnectServerInfo", "PORT", "", szTemp, 10, szCommonlocIniFileName);
	connectserverport = atoi(szTemp);
	LogAddTD(lMsg.Get(MSGGET(1, 158)), connectserverip, connectserverport);

	gUdpSoc.SendSet(connectserverip, connectserverport);
	gUdpSocCE.SendSet(gChaosEventServerIp, 60005);

	DevilSquareEventConnect = GetPrivateProfileInt("GameServerInfo","DevilSquareEventConnect", 1, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "DevilSquareEventServer", "210.181.89.241", gDevilSquareEventServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));
	EventChipServerConnect = GetPrivateProfileInt("GameServerInfo","EventChipServerConnect", 0, gDirPath.GetNewPath("commonserver.cfg"));
	GetPrivateProfileString("GameServerInfo", "EventChipServerIp", "192.168.10.150", gEventChipServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));

	gApplyHeroSystem = GetPrivateProfileInt("GameServerInfo","ApplyHeroSystem", 0, gDirPath.GetNewPath("commonserver.cfg"));

	gEnableBattleSoccer = GetPrivateProfileInt("GameServerInfo","EnableBattleSoccer", 1, gDirPath.GetNewPath("commonserver.cfg"));
	gEnableEventNPCTalk = GetPrivateProfileInt("GameServerInfo","EnableEventNPCTalk", 0, gDirPath.GetNewPath("commonserver.cfg"));
	gEnableServerDivision = GetPrivateProfileInt("GameServerInfo","EnableServerDivision", 0, gDirPath.GetNewPath("commonserver.cfg"));

	gMonsterHPAdjust = GetPrivateProfileInt("GameServerInfo","MonsterHPAdjust", 100, gDirPath.GetNewPath("commonserver.cfg"));

	cManager.Init();

	GetPrivateProfileString("GameServerInfo", "HackLogServer", "10.1.2.69", gHackLogServerIp, 20, gDirPath.GetNewPath("commonserver.cfg"));
	gSendHackLog.SendSet(gHackLogServerIp, 60005);

	gEnableCheckPenetrationSkill = GetPrivateProfileInt("GameServerInfo","EnableCheckPenetrationSkill", 1, gDirPath.GetNewPath("commonserver.cfg"));

	g_ShieldSystemOn = GetPrivateProfileInt("GameServerInfo","ShieldSystemOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iDamageDevideToSDRate = GetPrivateProfileInt("GameServerInfo","DamageDevideToSD", 90, gDirPath.GetNewPath("commonserver.cfg"));
	g_iDamageDevideToHPRate = GetPrivateProfileInt("GameServerInfo","DamageDevideToHP", 10, gDirPath.GetNewPath("commonserver.cfg"));
	g_fSuccessAttackRateOption = (double)(GetPrivateProfileInt("GameServerInfo","SuccessAttackRateOption", 20000, gDirPath.GetNewPath("commonserver.cfg")) / 10000 );
	g_iSDChargingOption = GetPrivateProfileInt("GameServerInfo","SDChargingOption", 1, gDirPath.GetNewPath("commonserver.cfg"));
	g_iConstNumberOfShieldPoint = GetPrivateProfileInt("GameServerInfo","ConstNumberOfShieldPoint", 20, gDirPath.GetNewPath("commonserver.cfg"));
	g_ShieldAutoRefillOn = GetPrivateProfileInt("GameServerInfo","ShieldAutoRefillOn", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_ShieldAutoRefillOnSafeZone = GetPrivateProfileInt("GameServerInfo","ShieldAutoRefilOnSafeZone", 1, gDirPath.GetNewPath("commonserver.cfg"));

	g_PKLevelIncreaseOff = GetPrivateProfileInt("GameServerInfo","PKLevelIncreaseOff", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_CompoundPotionDropOn = GetPrivateProfileInt("GameServerInfo","CompoundPotionDropOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iCompoundPotionLv1DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv1DropRate", 100, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCompoundPotionLv2DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv2DropRate", 80, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCompoundPotionLv3DropRate = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv3DropRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCompoundPotionLv1DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv1DropLevel", 68, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCompoundPotionLv2DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv2DropLevel", 96, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCompoundPotionLv3DropLevel = GetPrivateProfileInt("GameServerInfo","CompoundPotionLv3DropLevel", 118, gDirPath.GetNewPath("commonserver.cfg"));

	g_bShieldComboMissOptionOn = GetPrivateProfileInt("GameServerInfo","ShieldComboMissOptionOn", 0, gDirPath.GetNewPath("commonserver.cfg"));

	g_iShieldPotionLv1MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv1MixSuccessRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv1MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv1MixMoney", 100000, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv2MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv2MixSuccessRate", 30, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv2MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv2MixMoney", 500000, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv3MixSuccessRate = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv3MixSuccessRate", 30, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldPotionLv3MixMoney = GetPrivateProfileInt("GameServerInfo","ShieldPotionLv3MixMoney", 1000000, gDirPath.GetNewPath("commonserver.cfg"));
	
	g_iShieldGageConstA = GetPrivateProfileInt("GameServerInfo","ShieldGageConstA", 12, gDirPath.GetNewPath("commonserver.cfg"));
	g_iShieldGageConstB = GetPrivateProfileInt("GameServerInfo","ShieldGageConstB", 30, gDirPath.GetNewPath("commonserver.cfg"));

	g_bCheckSpeedHack = GetPrivateProfileInt("GameServerInfo","CheckSpeedHack", TRUE, gDirPath.GetNewPath("commonserver.cfg"));

	char cGsVersion[16];
	int iServerType = 0;
	iServerType = gServerType;
	wsprintf(cGsVersion, "%s_%d", szGameServerVersion, iServerType);

	wsprintf(szTemp, lMsg.Get(MSGGET(1, 160)), cGsVersion, szServerName, szClientVersion[0], szClientVersion[1], szClientVersion[2], szClientVersion[3], szClientVersion[4], szGameServerExeSerial, gCountryName);
	LogAdd("User Object Size = %d", sizeof(OBJECTSTRUCT));


	strcat(szTemp, "[CastleSiege]");


	char szDiplayGSInfo[512] = {0};
	wsprintfA(szDiplayGSInfo, "%s [%d][%d][%d]", szTemp, dwgCheckSum[1]%1000, dwgCheckSum[17]%1000, dwgCheckSum[1004]%1000);
	SetWindowText(ghWnd, szDiplayGSInfo);

	LoadItemBag();

	gPacketCheckSum.Init();

	gDoPShopOpen = GetPrivateProfileInt("GameServerInfo","PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));

	ReadEventInfo(MU_EVENT_ALL );

	g_iUseCharacterAutoRecuperationSystem = GetPrivateProfileInt("GameServerInfo","UseCharacterAutoRecuperationSystem", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iCharacterRecuperationMaxLevel = GetPrivateProfileInt("GameServerInfo","CharacterRecuperationMaxLevel", 100, gDirPath.GetNewPath("commonserver.cfg"));

	g_iSkillDistanceCheck = GetPrivateProfileInt("GameServerInfo","SkillDistanceCheck", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceCheckTemp = GetPrivateProfileInt("GameServerInfo","SkillDistanceCheckTemp", 2, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceKick = GetPrivateProfileInt("GameServerInfo","SkillDistanceKick", 0, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDistanceKickCount = GetPrivateProfileInt("GameServerInfo","SkillDistanceKickCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
	g_iSkillDiatanceKickCheckTime = GetPrivateProfileInt("GameServerInfo","SkillDistanceKickCheckTime", 10, gDirPath.GetNewPath("commonserver.cfg"));

	g_CashShop.CashShopOptioNReload();
	if (!RESETSTART)
	{
		g_CashItemPeriodSystem.Initialize();
	}


	//Season 3.0 add-on
	g_ChaosCard.Load("ChaosCard", gDirPath.GetNewPath("ChaosCardProbability.txt"));
	g_ChaosCard.Load("ChaosCardMini", gDirPath.GetNewPath("ChaosCardProbability1.txt"));
	g_ChaosCard.Load("ChaosCardGold", gDirPath.GetNewPath("ChaosCardProbability2.txt"));
	g_ChaosCard.Load("ChaosCardRare", gDirPath.GetNewPath("ChaosCardProbability3.txt"));
	
	g_BuffEffect.Load(gDirPath.GetNewPath("BuffEffect.txt"));
	
	g_EventItemList.Load(gDirPath.GetNewPath(".\\EventItemBags\\EventItemList.txt"));

#if(ANTI_CHEAT_PLUS==TRUE)
	g_AntiCheatPlus.Load();
#endif

	SetEventOff(); //
	RESETSTART = true;
}

void GameServerInfoSendStop()
{
	GSInfoSendFlag = 0;
}

void GameServerInfoSendStart()
{
	GSInfoSendFlag = 1;
}

struct PMSG_SERVERINFO
{
	PBMSG_HEAD h;	// C1:01
	short ServerCode;	// 4
	BYTE Percent;	// 6
	short UserCount;	// 8
	short AccountCount;	// A
	short PCbangCount;	// C
	short MaxUserCount;	// E
};

void GameServerInfoSend()
{
	PMSG_SERVERINFO pMsg;

	if ( gDisconnect == TRUE )
	{
		return;
	}

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x01;
	pMsg.h.size = sizeof( pMsg );

	if ( gObjTotalUser == 0 )
	{
		pMsg.Percent = 0;
	}
	else
	{
		pMsg.Percent = (gObjTotalUser * 100)/gServerMaxUser;
	}

	pMsg.ServerCode = gGameServerCode;
	pMsg.UserCount = gObjTotalUser;
	pMsg.AccountCount = gLCount[0].Get();
	pMsg.PCbangCount = gLCount[1].Get();
	pMsg.MaxUserCount = gServerMaxUser;

	gUdpSoc.SendData((LPBYTE)&pMsg, pMsg.h.size);
}

void CheckSumFileLoad(char * szCheckSum)
{
	int DataBufferSize;
	char* DataBuffer;

	gGameServerAuth.RequestData(6);
	DataBufferSize=gGameServerAuth.GetDataBufferSize();
	DataBuffer=gGameServerAuth.GetDataBuffer();
	memcpy(dwgCheckSum, DataBuffer, DataBufferSize);
}

void LoadItemBag() //0053E2F0
{
	if ( LuckboxItemBag != FALSE )
	{
		delete LuckboxItemBag;
	}

	LuckboxItemBag = new CItemBag;

	if ( LuckboxItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	LuckboxItemBag->Init(".\\EventItemBags\\eventitembag.txt");

	if ( Mon55 != FALSE )
	{
		delete Mon55;
	}

	Mon55 = new CItemBag;

	if ( Mon55 == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	Mon55->Init(".\\EventItemBags\\eventitembag2.txt");

	if ( Mon53 != FALSE )
	{
		delete Mon53;
	}

	Mon53 = new CItemBag;

	if ( Mon53 == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	Mon53->Init(".\\EventItemBags\\eventitembag3.txt");

	if ( StarOfXMasItemBag != FALSE )	
	{
		delete StarOfXMasItemBag;
	}

	StarOfXMasItemBag = new CItemBagEx;

	if ( StarOfXMasItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	StarOfXMasItemBag->Init(".\\EventItemBags\\eventitembag4.txt");

	if ( FireCrackerItemBag != FALSE )	
	{
		delete FireCrackerItemBag;
	}

	FireCrackerItemBag = new CItemBag;

	if ( FireCrackerItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	FireCrackerItemBag->Init(".\\EventItemBags\\eventitembag5.txt");

	if ( HeartOfLoveItemBag != FALSE )	
	{
		delete HeartOfLoveItemBag;
	}

	HeartOfLoveItemBag = new CItemBag;

	if ( HeartOfLoveItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	HeartOfLoveItemBag->Init(".\\EventItemBags\\eventitembag5.txt");

	if ( GoldMedalItemBag != FALSE )	
	{
		delete GoldMedalItemBag;
	}

	GoldMedalItemBag = new CItemBag;

	if ( GoldMedalItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	GoldMedalItemBag->Init(".\\EventItemBags\\eventitembag6.txt");

	if ( SilverMedalItemBag != FALSE )	
	{
		delete SilverMedalItemBag;
	}

	SilverMedalItemBag = new CItemBag;

	if ( SilverMedalItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	SilverMedalItemBag->Init(".\\EventItemBags\\eventitembag7.txt");

	if ( GoldGoblenItemBag != FALSE )	
	{
		delete GoldGoblenItemBag;
	}

	GoldGoblenItemBag = new CProbabilityItemBag;

	if ( GoldGoblenItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	GoldGoblenItemBag->Init(".\\EventItemBags\\eventitembag8.txt");

	if ( TitanItemBag != FALSE )	
	{
		delete TitanItemBag;
	}

	TitanItemBag = new CProbabilityItemBag;

	if ( TitanItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	TitanItemBag->Init(".\\EventItemBags\\eventitembag9.txt");

	if ( GoldDerconItemBag != FALSE )	
	{
		delete GoldDerconItemBag;
	}

	GoldDerconItemBag = new CProbabilityItemBag;

	if ( GoldDerconItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	GoldDerconItemBag->Init(".\\EventItemBags\\eventitembag10.txt");

	if ( DevilLizardKingItemBag != FALSE )	
	{
		delete DevilLizardKingItemBag;
	}

	DevilLizardKingItemBag = new CProbabilityItemBag;

	if ( DevilLizardKingItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	DevilLizardKingItemBag->Init(".\\EventItemBags\\eventitembag11.txt");

	if ( KanturItemBag != FALSE )	
	{
		delete KanturItemBag;
	}

	KanturItemBag = new CProbabilityItemBag;

	if ( KanturItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	KanturItemBag->Init(".\\EventItemBags\\eventitembag12.txt");

	if ( RingEventItemBag != FALSE )	
	{
		delete RingEventItemBag;
	}

	RingEventItemBag = new CItemBag;

	if ( RingEventItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	RingEventItemBag->Init(".\\EventItemBags\\eventitembag13.txt");

	if ( FriendShipItemBag != FALSE )	
	{
		delete FriendShipItemBag;
	}

	FriendShipItemBag = new CItemBag;

	if ( FriendShipItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	FriendShipItemBag->Init(".\\EventItemBags\\eventitembag14.txt");

	if ( DarkLordHeartItemBag != FALSE )	
	{
		delete DarkLordHeartItemBag;
	}

	DarkLordHeartItemBag = new CItemBag;

	if ( DarkLordHeartItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	DarkLordHeartItemBag->Init(".\\EventItemBags\\eventitembag15.txt");

	if ( KundunEventItemBag != FALSE )	
	{
		delete KundunEventItemBag;
	}

	KundunEventItemBag = new CItemBagEx;

	if ( KundunEventItemBag == NULL )
	{
		MsgBox( "CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	KundunEventItemBag->Init(".\\EventItemBags\\eventitembag17.txt");


	if ( CastleHuntZoneBossItemBag != FALSE )
	{
		delete CastleHuntZoneBossItemBag;
	}

	CastleHuntZoneBossItemBag = new CItemBagEx; 

	if ( CastleHuntZoneBossItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CastleHuntZoneBossItemBag->Init(".\\EventItemBags\\eventitembag18.txt");

	// EventItemBag for Special Mix
	if ( CastleItemMixItemBag != FALSE )
	{
		delete CastleItemMixItemBag;
	}

	CastleItemMixItemBag = new CItemBagEx;

	if ( CastleItemMixItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CastleItemMixItemBag->Init(".\\EventItemBags\\eventitembag19.txt");


	if ( HiddenTreasureBoxItemBag != NULL )
		delete HiddenTreasureBoxItemBag;

	HiddenTreasureBoxItemBag = new CItemBagEx; 
	if ( HiddenTreasureBoxItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	HiddenTreasureBoxItemBag->Init(".\\EventItemBags\\eventitembag20.txt");

	if ( RedRibbonBoxEventItemBag != NULL )
		delete RedRibbonBoxEventItemBag;

	RedRibbonBoxEventItemBag = new CItemBagEx; 
	if ( RedRibbonBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	RedRibbonBoxEventItemBag->Init(".\\EventItemBags\\eventitembag21.txt");

	if ( GreenRibbonBoxEventItemBag != NULL )
		delete GreenRibbonBoxEventItemBag;

	GreenRibbonBoxEventItemBag = new CItemBagEx; 
	if ( GreenRibbonBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	GreenRibbonBoxEventItemBag->Init(".\\EventItemBags\\eventitembag22.txt");

	if ( BlueRibbonBoxEventItemBag != NULL )
		delete BlueRibbonBoxEventItemBag;

	BlueRibbonBoxEventItemBag = new CItemBagEx; 
	if ( BlueRibbonBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	BlueRibbonBoxEventItemBag->Init(".\\EventItemBags\\eventitembag23.txt");

	if ( PinkChocolateBoxEventItemBag != NULL )
		delete PinkChocolateBoxEventItemBag;

	PinkChocolateBoxEventItemBag = new CItemBagEx; 
	if ( PinkChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	PinkChocolateBoxEventItemBag->Init(".\\EventItemBags\\eventitembag24.txt");

	if ( RedChocolateBoxEventItemBag != NULL )
		delete RedChocolateBoxEventItemBag;

	RedChocolateBoxEventItemBag = new CItemBagEx; 
	if ( RedChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	RedChocolateBoxEventItemBag->Init(".\\EventItemBags\\eventitembag25.txt");

	if ( BlueChocolateBoxEventItemBag != NULL )
		delete BlueChocolateBoxEventItemBag;

	BlueChocolateBoxEventItemBag = new CItemBagEx; 
	if ( BlueChocolateBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	BlueChocolateBoxEventItemBag->Init(".\\EventItemBags\\eventitembag26.txt");

	if ( LightPurpleCandyBoxEventItemBag != NULL )
		delete LightPurpleCandyBoxEventItemBag;

	LightPurpleCandyBoxEventItemBag = new CItemBagEx; 
	if ( LightPurpleCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	LightPurpleCandyBoxEventItemBag->Init(".\\EventItemBags\\eventitembag27.txt");

	if ( VermilionCandyBoxEventItemBag != NULL )
		delete VermilionCandyBoxEventItemBag;

	VermilionCandyBoxEventItemBag = new CItemBagEx; 
	if ( VermilionCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	VermilionCandyBoxEventItemBag->Init(".\\EventItemBags\\eventitembag28.txt");

	if ( DeepBlueCandyBoxEventItemBag != NULL )
		delete DeepBlueCandyBoxEventItemBag;

	DeepBlueCandyBoxEventItemBag = new CItemBagEx; 
	if ( DeepBlueCandyBoxEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	DeepBlueCandyBoxEventItemBag->Init(".\\EventItemBags\\eventitembag29.txt");

	if ( CrywolfDarkElfItemBag != NULL )
		delete CrywolfDarkElfItemBag;

	CrywolfDarkElfItemBag = new CItemBagEx; 
	if ( CrywolfDarkElfItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CrywolfDarkElfItemBag->Init(".\\EventItemBags\\eventitembag30.txt");

	if ( CrywolfBossMonsterItemBag != NULL )
		delete CrywolfBossMonsterItemBag;

	CrywolfBossMonsterItemBag = new CItemBagEx; 
	if ( CrywolfBossMonsterItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CrywolfBossMonsterItemBag->Init(".\\EventItemBags\\eventitembag31.txt");


	if ( KanturuMayaHandItemBag != NULL )
		delete KanturuMayaHandItemBag;

	KanturuMayaHandItemBag = new CItemBagEx; 
	if ( KanturuMayaHandItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	KanturuMayaHandItemBag->Init(".\\EventItemBags\\eventitembag32.txt");

	if ( KanturuNightmareItemBag != NULL )
		delete KanturuNightmareItemBag;

	KanturuNightmareItemBag = new CItemBagEx; 
	if ( KanturuNightmareItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	KanturuNightmareItemBag->Init(".\\EventItemBags\\eventitembag33.txt");


	if ( HallowinDayEventItemBag != NULL )
		delete HallowinDayEventItemBag;

	HallowinDayEventItemBag = new CItemBagEx; 
	if ( HallowinDayEventItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	HallowinDayEventItemBag->Init(".\\EventItemBags\\eventitembag34.txt");

	//////////////////////////////////////////////

	if ( RingOfHeroBoxItemBag != NULL )
		delete RingOfHeroBoxItemBag;

	RingOfHeroBoxItemBag = new CItemBag; 
	if ( RingOfHeroBoxItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	RingOfHeroBoxItemBag->Init(".\\EventItemBags\\eventitembag35.txt");

	if ( NewYearLuckyPouchItemBag != NULL )
		delete NewYearLuckyPouchItemBag;

	NewYearLuckyPouchItemBag = new CProbabilityItemBag; 
	if ( NewYearLuckyPouchItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	NewYearLuckyPouchItemBag->Init(".\\EventItemBags\\eventitembag37.txt");

	if ( GMPresentBoxItemBag != NULL )
		delete GMPresentBoxItemBag;

	GMPresentBoxItemBag = new CProbabilityItemBag; 
	if ( GMPresentBoxItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	GMPresentBoxItemBag->Init(".\\EventItemBags\\eventitembag41.txt");

	//PCBangGageGreenBox
	if ( PCBangGageGreenBox != NULL )
		delete PCBangGageGreenBox;

	PCBangGageGreenBox = new CProbabilityItemBag; 
	if ( PCBangGageGreenBox == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	PCBangGageGreenBox->Init(".\\EventItemBags\\eventitembag38.txt");

	//PCBangGageRedBox
	if ( PCBangGageRedBox != NULL )
		delete PCBangGageRedBox;

	PCBangGageRedBox = new CProbabilityItemBag; 
	if ( PCBangGageRedBox == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	PCBangGageRedBox->Init(".\\EventItemBags\\eventitembag39.txt");

	//PCBangGagePurpleBox
	if ( PCBangGagePurpleBox != NULL )
		delete PCBangGagePurpleBox;

	PCBangGagePurpleBox = new CProbabilityItemBag; 
	if ( PCBangGagePurpleBox == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	PCBangGagePurpleBox->Init(".\\EventItemBags\\eventitembag40.txt");

	//ReservedBox
	if ( ReservedBox != NULL )
		delete ReservedBox;

	ReservedBox = new CProbabilityItemBag; 
	if ( ReservedBox == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	ReservedBox->Init(".\\EventItemBags\\eventitembag45.txt");

	//RaklionSelupanItemBag
	if ( RaklionSelupanItemBag != NULL )
		delete RaklionSelupanItemBag;

	RaklionSelupanItemBag = new CProbabilityItemBag; 
	if ( RaklionSelupanItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	RaklionSelupanItemBag->Init(".\\EventItemBags\\eventitembag52.txt");

	//LuckyCoin10
	if ( LuckyCoin10 != NULL )
		delete LuckyCoin10;

	LuckyCoin10 = new CProbabilityItemBag; 
	if ( LuckyCoin10 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	LuckyCoin10->Init(".\\EventItemBags\\eventitembag56.txt");

	//LuckyCoin20
	if ( LuckyCoin20 != NULL )
		delete LuckyCoin20;

	LuckyCoin20 = new CProbabilityItemBag; 
	if ( LuckyCoin20 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	LuckyCoin20->Init(".\\EventItemBags\\eventitembag57.txt");

	//LuckyCoin30
	if ( LuckyCoin30 != NULL )
		delete LuckyCoin30;

	LuckyCoin30 = new CProbabilityItemBag; 
	if ( LuckyCoin30 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	LuckyCoin30->Init(".\\EventItemBags\\eventitembag58.txt");

	if ( IllusionTemple1ItemBag != NULL )
		delete IllusionTemple1ItemBag;

	IllusionTemple1ItemBag = new CProbabilityItemBag; 
	if ( IllusionTemple1ItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	IllusionTemple1ItemBag->Init(".\\EventItemBags\\eventitembag42.txt");

	if ( IllusionTemple2ItemBag != NULL )
		delete IllusionTemple2ItemBag;

	IllusionTemple2ItemBag = new CProbabilityItemBag; 
	if ( IllusionTemple2ItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	IllusionTemple2ItemBag->Init(".\\EventItemBags\\eventitembag43.txt");

	if ( IllusionTemple3ItemBag != NULL )
		delete IllusionTemple3ItemBag;

	IllusionTemple3ItemBag = new CProbabilityItemBag; 
	if ( IllusionTemple3ItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	IllusionTemple3ItemBag->Init(".\\EventItemBags\\eventitembag44.txt");

	if ( MoonHarvestItemBag != NULL )
		delete MoonHarvestItemBag;

	MoonHarvestItemBag = new CProbabilityItemBag; 
	if ( MoonHarvestItemBag == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	MoonHarvestItemBag->Init(".\\EventItemBags\\eventitembag46.txt");

	if ( CherryBlossom1 != NULL )
		delete CherryBlossom1;

	CherryBlossom1 = new CProbabilityItemBag; 
	if ( CherryBlossom1 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CherryBlossom1->Init(".\\EventItemBags\\eventitembag48.txt");

	if ( CherryBlossom2 != NULL )
		delete CherryBlossom2;

	CherryBlossom2 = new CProbabilityItemBag; 
	if ( CherryBlossom2 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag-A %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CherryBlossom2->Init(".\\EventItemBags\\eventitembag49.txt");

	if ( CherryBlossom3 != NULL )
		delete CherryBlossom3;

	CherryBlossom3 = new CProbabilityItemBag; 
	if ( CherryBlossom3 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag-B %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CherryBlossom3->Init(".\\EventItemBags\\eventitembag50.txt");

	if ( CherryBlossom4 != NULL )
		delete CherryBlossom4;

	CherryBlossom4 = new CProbabilityItemBag; 
	if ( CherryBlossom4 == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag-C %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	CherryBlossom4->Init(".\\EventItemBags\\eventitembag51.txt");

	//XMasEventA
	if ( XMasEventA != NULL )
		delete XMasEventA;

	XMasEventA = new CProbabilityItemBag; 
	if ( XMasEventA == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	XMasEventA->Init(".\\EventItemBags\\eventitembag53.txt");

	//XMasEventB
	if ( XMasEventB != NULL )
		delete XMasEventB;

	XMasEventB = new CProbabilityItemBag; 
	if ( XMasEventB == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag100 %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	XMasEventB->Init(".\\EventItemBags\\eventitembag54.txt");

	//XMasEventC
	if ( XMasEventC != NULL )
		delete XMasEventC;

	XMasEventC = new CProbabilityItemBag; 
	if ( XMasEventC == NULL )
	{
		// Memory allocation error
		MsgBox("CProbabilityItemBag1000 %s", lMsg.Get(MSGGET(0, 110)));
		return;
	}

	XMasEventC->Init(".\\EventItemBags\\eventitembag55.txt");
}

void SetMapName()
{
	strcpy(gMapName[0], lMsg.Get(MSGGET(7,208)));
	strcpy(gMapName[1], lMsg.Get(MSGGET(7,209)));
	strcpy(gMapName[2], lMsg.Get(MSGGET(7,210)));
	strcpy(gMapName[3], lMsg.Get(MSGGET(7,211)));
	strcpy(gMapName[4], lMsg.Get(MSGGET(7,212)));
	strcpy(gMapName[5], "Reserved");
	strcpy(gMapName[6], lMsg.Get(MSGGET(7,214)));
	strcpy(gMapName[7], lMsg.Get(MSGGET(7,213)));
	strcpy(gMapName[8], lMsg.Get(MSGGET(7,216)));
	strcpy(gMapName[9], lMsg.Get(MSGGET(7,217)));
	strcpy(gMapName[10], lMsg.Get(MSGGET(7,221)));
	strcpy(gMapName[11], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[11], "1");
	strcpy(gMapName[12], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[12], "2");
	strcpy(gMapName[13], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[13], "3");
	strcpy(gMapName[14], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[14], "4");
	strcpy(gMapName[15], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[15], "5");
	strcpy(gMapName[16], lMsg.Get(MSGGET(7,222)));
	strcat(gMapName[16], "6");
}

struct ST_EVENT_FLAG
{
	BOOL bDevilSquare : 1;
	BOOL bBloodCastle : 1;
	BOOL			  : 6;
	BOOL bXMaxEvent   : 1;
	BOOL bFireCracker : 1;
	BOOL bHeartOfLove : 1;
	BOOL bMedalEvent  : 1;
	BOOL bRingEvent   : 1;
	BOOL bEventChip   : 1;
	BOOL bEledorado   : 1;
	BOOL			  : 1;
	BOOL bNPGGChecksum: 1;
};

union STU_EVENT_FLAG
{
	ST_EVENT_FLAG EventData;
	DWORD AllData;
};

int GetEventFlag()
{
	STU_EVENT_FLAG flag;

	flag.AllData = 0;

	if (gDevilSquareEvent!=0)
	{
		flag.EventData.bDevilSquare=1;
	}
	if (g_bBloodCastle!=0)
	{
		flag.EventData.bBloodCastle=1;
	}
	if (gXMasEvent!=0)
	{
		flag.EventData.bXMaxEvent=1;
	}
	if (gFireCrackerEvent!=0)
	{
		flag.EventData.bFireCracker=1;
	}
	if (gHeartOfLoveEvent!=0)
	{
		flag.EventData.bHeartOfLove=1;
	}
	if (gMedalEvent!=0)
	{
		flag.EventData.bMedalEvent=1;
	}
	if (g_bDoRingEvent!=0)
	{
		flag.EventData.bRingEvent=1;
	}
	if (gEventChipEvent!=0)
	{
		flag.EventData.bEventChip=1;
	}
	if (gIsEledoradoEvent!=0)
	{
		flag.EventData.bEledorado=1;
	}
	if (gUseNPGGChecksum!=0)
	{
		flag.EventData.bNPGGChecksum=1;
	}	

	return flag.AllData;	
}

void ReadEventInfo(MU_EVENT_TYPE eEventType)
{
	char szTemp[256];
	switch(eEventType)
	{
		case 0: //All Events
			g_DevilSquare.Load(gDirPath.GetNewPath(".\\Events\\DevilSquare.dat"));
			gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo","DevilSquareEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","EyesOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","KeyOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_BloodCastle.Load(gDirPath.GetNewPath(".\\Events\\BloodCastle.dat"));
			g_bBloodCastle = GetPrivateProfileInt("GameServerInfo","BloodCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo","BloodCastleStartHour", 1, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo","BloodBoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo","StoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_OddEvenHour = GetPrivateProfileInt("GameServerInfo","BloodCastleOddEvenHour", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gIsDropDarkLordItem = GetPrivateProfileInt("GameServerInfo","IsDropDarkLordItem", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSleeveOfLordDropRate = GetPrivateProfileInt("GameServerInfo","SleeveOfLordDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSleeveOfLordDropLevel = GetPrivateProfileInt("GameServerInfo","SleeveOfLordDropLevel", 86, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkHorseDropRate = GetPrivateProfileInt("GameServerInfo","SoulOfDarkHorseDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkHorseropLevel = GetPrivateProfileInt("GameServerInfo","SoulOfDarkHorseropLevel", 125, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkSpiritDropRate = GetPrivateProfileInt("GameServerInfo","SoulOfDarkSpiritDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gSoulOfDarkSpiritDropLevel = GetPrivateProfileInt("GameServerInfo","SoulOfDarkSpiritDropLevel", 96, gDirPath.GetNewPath("commonserver.cfg"));
			GetPrivateProfileString("GameServerInfo", "DarkSpiritAddExperience", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gDarkSpiritAddExperience = (float)atof(szTemp);

			gIsDropGemOfDefend = GetPrivateProfileInt("GameServerInfo","IsDropGemOfDefend", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGemOfDefendDropRate = GetPrivateProfileInt("GameServerInfo","GemOfDefendDropRate", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGemOfDefendDropLevel = GetPrivateProfileInt("GameServerInfo","GemOfDefendDropLevel", 75, gDirPath.GetNewPath("commonserver.cfg"));


			gIsDropSetItemInCastleHuntZone = GetPrivateProfileInt("GameServerInfo","IsDropSetItemInCastleHuntZone", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gSetItemInCastleHuntZoneDropRate = GetPrivateProfileInt("GameServerInfo","SetItemInCastleHuntZoneDropRate", 1, gDirPath.GetNewPath("commonserver.cfg"));
			gSetItemInCastleHuntZoneDropLevel = GetPrivateProfileInt("GameServerInfo","SetItemInCastleHuntZoneDropLevel", 75, gDirPath.GetNewPath("commonserver.cfg"));

			gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo","AttackEventRegenTime", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsEledoradoEvent = GetPrivateProfileInt("GameServerInfo","IsEledoradoEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoTitanRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconRegenTime", 720, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			
			//Season 4.5 addon
			gEledoradoGoldenRabbitRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenRabbitRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenDarkKnightRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenDarkKnightRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenDevilRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenDevilRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenMonsterRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenMonsterRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenCrustRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenCrustRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenSatirosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenSatirosRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenTwintailRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenTwintailRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenIronKnightRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenIronKnightRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenNeipinRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenNeipinRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenGreatDragonRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenGreatDragonRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			//Season 3.0 moved
			gEledoradoEvent.SetEventState(gIsEledoradoEvent);
			gEledoradoEvent.Init();

			GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bDoRingEvent = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRingOrcKillGiftRate = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRingDropGiftRate = atoi(szTemp);
			g_RingAttackEvent.Load(gDirPath.GetNewPath(".\\Events\\RingAttackEvent.dat"));

			g_RingAttackEvent.EnableEvent(g_bDoRingEvent);

			//Season4 add-on
			g_bDoXMasAttackEvent = GetPrivateProfileInt("GameServerInfo","XMasAttackEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iXMasAttackEventDropRate = GetPrivateProfileInt("GameServerInfo","XMasAttackEvent_DropRate", 50, gDirPath.GetNewPath("commonserver.cfg"));
			g_iXMasAttackEventDropZen = GetPrivateProfileInt("GameServerInfo","XMasAttackEvent_DropZen", 10000, gDirPath.GetNewPath("commonserver.cfg"));

			g_XMasAttackEvent.Load(gDirPath.GetNewPath(".\\Events\\XMasAttackEvent.dat"));
			g_XMasAttackEvent.EnableEvent(g_bDoXMasAttackEvent);

			g_iXMasEvent_LuckNumber1st = GetPrivateProfileInt("GameServerInfo","XMasEvent_LuckNumber1st", 100, gDirPath.GetNewPath("commonserver.cfg"));
			g_iXMasEvent_LuckNumber2nd = GetPrivateProfileInt("GameServerInfo","XMasEvent_LuckNumber2nd", 200, gDirPath.GetNewPath("commonserver.cfg"));


			GetPrivateProfileString("GameServerInfo", "CastleDeepEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bDoCastleDeepEvent = atoi(szTemp);
			g_CastleDeepEvent.Load(gDirPath.GetNewPath(".\\Events\\CastleDeepEvent.dat"));
			g_CastleDeepEvent.EnableEvent(g_bDoCastleDeepEvent);

			GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1 = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayCount = 0;
			gEvent1ItemDropTodayMax = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayPercent = atoi(szTemp);
			gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo","FireCrackerEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo","FireCrackerDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo","ItemDropRateForFireCracker", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo","OnlyFireCrackerEffectUse", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gMedalEvent = GetPrivateProfileInt("GameServerInfo","MedalEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo","GoldMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo","SilverMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForGoldMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForSilverMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gXMasEvent = GetPrivateProfileInt("GameServerInfo","XMasEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo","XMasEvent_StarOfXMasDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo","XMasEvent_ItemDropRateForStarOfXMas", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo","HeartOfLoveEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo","HeartOfLoveDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo","ItemDropRateForHeartOfLove", 2, gDirPath.GetNewPath("commonserver.cfg"));
			GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gHappyNewYearNpcEvent = atoi(szTemp);

			if(gHappyNewYearNpcEvent != 0)
			{
				// (Option) Happy-new-year NPC speaks
				LogAddTD(lMsg.Get(MSGGET(2, 61)));
			}

			GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMerryXMasNpcEvent = atoi(szTemp);

			if(gMerryXMasNpcEvent != 0)
			{
				// (Option) Christmas NPC speaks
				LogAddTD(lMsg.Get(MSGGET(2, 60)));
			}

			g_ChaosCastle.Load(gDirPath.GetNewPath(".\\Events\\ChaosCastle.dat"));
			g_bChaosCastle = GetPrivateProfileInt("GameServerInfo","ChaosCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iKundunMarkDropRate = GetPrivateProfileInt("GameServerInfo","KundunMarkDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iMysteriousBeadDropRate1 = GetPrivateProfileInt("GameServerInfo","MysteriouseBeadDropRate1", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iMysteriousBeadDropRate2 = GetPrivateProfileInt("GameServerInfo","MysteriouseBeadDropRate2", 0, gDirPath.GetNewPath("commonserver.cfg"));

			g_iHiddenTreasureBoxOfflineRate = GetPrivateProfileInt("GameServerInfo","HiddenTreasureBoxOfflineRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
     
			GetPrivateProfileString("GameServerInfo", "EventManagerOn", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			g_bEventManagerOn = atoi(szTemp);
			g_EventManager.Load(gDirPath.GetNewPath(".\\Events\\EventManagement.dat"));
			g_EventManager.RegEvent(0, DragonEvent);
			g_EventManager.RegEvent(1, AttackEvent);
			g_EventManager.RegEvent(2, &gEledoradoEvent);
			g_EventManager.RegEvent(3, &g_RingAttackEvent);
			g_EventManager.RegEvent(4, &g_XMasAttackEvent);//Season 4.5 addon
			g_EventManager.Init(g_bEventManagerOn);

			g_iDarkLordHeartDropRate = GetPrivateProfileInt("GameServerInfo","DarkLordHeartDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDarkLordHeartOffEventRate = GetPrivateProfileInt("GameServerInfo","DarkLoadHeartOffEventRate", 0, gDirPath.GetNewPath("commonserver.cfg"));

			// Ribbon Box Event
			g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Red Ribbon Box
			g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Green Ribbon Box
			g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Blue Ribbon Box
			g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));


			// Chocolate Event
			g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Pink Chocolate Box
			g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Red Chocolate Box
			g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Blue Chocolate Box
			g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Candy Event
			g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

			// LightPurple Candy Box
			g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// Vermilion Candy Box
			g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

			// DeepBlue Candy Box
			g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 1: //Devil Square
			g_DevilSquare.Load(gDirPath.GetNewPath(".\\Events\\DevilSquare.dat"));
			gDevilSquareEvent = GetPrivateProfileInt("GameServerInfo","DevilSquareEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEyesOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","EyesOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gKeyOfDevilSquareDropRate = GetPrivateProfileInt("GameServerInfo","KeyOfDevilSquareDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 2: //Blood Castle
			g_BloodCastle.Load(gDirPath.GetNewPath(".\\Events\\BloodCastle.dat"));
			g_bBloodCastle = GetPrivateProfileInt("GameServerInfo","BloodCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_StartHour = GetPrivateProfileInt("GameServerInfo","BloodCastleStartHour", 1, gDirPath.GetNewPath("commonserver.cfg"));
			g_iAngelKingsPaperDropRate = GetPrivateProfileInt("GameServerInfo","AngelKingsPaperDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodBoneDropRate = GetPrivateProfileInt("GameServerInfo","BloodBoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iStoneDropRate = GetPrivateProfileInt("GameServerInfo","StoneDropRate", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_iBloodCastle_OddEvenHour = GetPrivateProfileInt("GameServerInfo","BloodCastleOddEvenHour", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 3: //Attack Event
			gAttackEventRegenTime = GetPrivateProfileInt("GameServerInfo","AttackEventRegenTime", 10, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 4: //Eledorado Event
			gIsEledoradoEvent = GetPrivateProfileInt("GameServerInfo","IsEledoradoEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoTitanRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconRegenTime", 720, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosRegenTime", 360, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldGoblenExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldGoblenExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoTitanExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoTitanExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldDerconExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoGoldDerconExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilLizardKingExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilLizardKingExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoDevilTantarosExItemDropRate = GetPrivateProfileInt("GameServerInfo","EledoradoDevilTantarosExItemDropRate", 10, gDirPath.GetNewPath("commonserver.cfg"));
			
			/* WZ MISSED ?
			gEledoradoGoldenRabbitRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenRabbitRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenDarkKnightRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenDarkKnightRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenDevilRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenDevilRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenMonsterRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenMonsterRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenCrustRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenCrustRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenSatirosRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenSatirosRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenTwintailRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenTwintailRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenIronKnightRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenIronKnightRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenNeipinRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenNeipinRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			gEledoradoGoldenGreatDragonRegenTime = GetPrivateProfileInt("GameServerInfo","EledoradoGoldenGreatDragonRegenTime", 180, gDirPath.GetNewPath("commonserver.cfg"));
			*/
			break;
		case 5: //Ring Event
			{
				char szTemp[256];

				GetPrivateProfileString("GameServerInfo", "RingAttackEvent", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
				g_bDoRingEvent = atoi(szTemp);
				GetPrivateProfileString("GameServerInfo", "RingOrcKillGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRingOrcKillGiftRate = atoi(szTemp);
				GetPrivateProfileString("GameServerInfo", "RingDropGiftRate", "10000", szTemp, 10, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRingDropGiftRate = atoi(szTemp);
				g_RingAttackEvent.Load(gDirPath.GetNewPath(".\\Events\\RingAttackEvent.dat"));
				
				g_RingAttackEvent.EnableEvent(g_bDoRingEvent);
			}
			break;

		case 6: //Event 1
			GetPrivateProfileString("GameServerInfo", "EVENT1", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1 = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayMax", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayCount = 0;
			gEvent1ItemDropTodayMax = atoi(szTemp);
			GetPrivateProfileString("GameServerInfo", "Event1ItemDropTodayPercent", "10000000", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gEvent1ItemDropTodayPercent = atoi(szTemp);
			break;
		case 7: //Fire Cracker
			gFireCrackerEvent = GetPrivateProfileInt("GameServerInfo","FireCrackerEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gFireCrackerDropRate = GetPrivateProfileInt("GameServerInfo","FireCrackerDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgFireCracker = GetPrivateProfileInt("GameServerInfo","ItemDropRateForFireCracker", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gOnlyFireCrackerEffectUse = GetPrivateProfileInt("GameServerInfo","OnlyFireCrackerEffectUse", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 8: //Medal Event
			gMedalEvent = GetPrivateProfileInt("GameServerInfo","MedalEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gGoldMedalDropRate = GetPrivateProfileInt("GameServerInfo","GoldMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			gSilverMedalDropRate = GetPrivateProfileInt("GameServerInfo","SilverMedalDropRate", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForGoldMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForGoldMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForSilverMedal = GetPrivateProfileInt("GameServerInfo","ItemDropRateForSilverMedal", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 9: //XMax Event
			gXMasEvent = GetPrivateProfileInt("GameServerInfo","XMasEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_StarOfXMasDropRate = GetPrivateProfileInt("GameServerInfo","XMasEvent_StarOfXMasDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_XMasEvent_ItemDropRateForStarOfXMas = GetPrivateProfileInt("GameServerInfo","XMasEvent_ItemDropRateForStarOfXMas", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 10: //Heart Of Love Event
			gHeartOfLoveEvent = GetPrivateProfileInt("GameServerInfo","HeartOfLoveEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHeartOfLoveDropRate = GetPrivateProfileInt("GameServerInfo","HeartOfLoveDropRate", 5000, gDirPath.GetNewPath("commonserver.cfg"));
			g_ItemDropRateForgHeartOfLove = GetPrivateProfileInt("GameServerInfo","ItemDropRateForHeartOfLove", 2, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 11: //Happy New Year Event
			GetPrivateProfileString("GameServerInfo", "HappyNewYearTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gHappyNewYearNpcEvent = atoi(szTemp);

			if(gHappyNewYearNpcEvent != 0)
			{
				// (Option) Happy-new-year NPC speaks
				LogAddTD(lMsg.Get(MSGGET(2, 61)));
			}
			break;
		case 12: //Merry  XMax Event NPC talk
			GetPrivateProfileString("GameServerInfo", "MerryXMasTalkNpc", "0", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMerryXMasNpcEvent = atoi(szTemp);

			if(gMerryXMasNpcEvent != 0)
			{
				// (Option) Christmas NPC speaks
				LogAddTD(lMsg.Get(MSGGET(2, 60)));
			}
			break;
		case 13: //Chaos Castle
			g_ChaosCastle.Load(gDirPath.GetNewPath(".\\Events\\ChaosCastle.dat"));
			g_bChaosCastle = GetPrivateProfileInt("GameServerInfo","ChaosCastleEvent", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 14:
				// Ribbon Box Event
				g_bRibbonBoxEvent = GetPrivateProfileInt("GameServerInfo","RibbonBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Ribbon Box
				g_iRedRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Green Ribbon Box
				g_iGreenRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iGreenRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","GreenRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Ribbon Box
				g_iBlueRibbonBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueRibbonBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueRibbonBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;

		case 15:
				// Chocolate Event
				g_bChocolateBoxEvent = GetPrivateProfileInt("GameServerInfo","ChocolateEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Pink Chocolate Box
				g_iPinkChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iPinkChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","PinkChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Red Chocolate Box
				g_iRedChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iRedChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","RedChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Blue Chocolate Box
				g_iBlueChocolateBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iBlueChocolateBoxDropZen = GetPrivateProfileInt("GameServerInfo","BlueChocolateBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;

		case 16:
				// Candy Event
				g_bCandyBoxEvent = GetPrivateProfileInt("GameServerInfo","CandyBoxEvent",0, gDirPath.GetNewPath("commonserver.cfg"));

				// LightPurple Candy Box
				g_iLightPurpleCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iLightPurpleCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","LightPurpleCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// Vermilion Candy Box
				g_iVermilionCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iVermilionCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","VermilionCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));

				// DeepBlue Candy Box
				g_iDeepBlueCandyBoxDropLevelMin = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Min",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropLevelMax = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropLv_Max",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZenRate = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZenRate",0, gDirPath.GetNewPath("commonserver.cfg"));
				g_iDeepBlueCandyBoxDropZen = GetPrivateProfileInt("GameServerInfo","DeepBlueCandyBoxDropZen",0, gDirPath.GetNewPath("commonserver.cfg"));
				break;
	}
}

void ReadGameEtcInfo(MU_ETC_TYPE eGameEtcType)
{
	char szTemp[256];

	switch ( eGameEtcType )
	{
		case 0:
			GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gCreateCharacter = atoi(szTemp);

			GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreate = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
			GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildDestroy = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
			GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreateLevel = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);

			g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));

			GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			bCanTrade = atoi(szTemp);

			bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, gDirPath.GetNewPath("commonserver.cfg"));

			GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gPkItemDrop = atoi(szTemp);

			GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gItemDropPer = atoi(szTemp);

			gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo", "AttackSpeedTimeLimit", 800, gDirPath.GetNewPath("commonserver.cfg"));
			bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo", "IsIgnorePacketHackDetect", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHackCheckCount = GetPrivateProfileInt("GameServerInfo", "HackCheckCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo", "MinimumAttackSpeedTime", 200 , gDirPath.GetNewPath("commonserver.cfg"));
			gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo", "DetectedHackKickCount", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo", "IsKickDetecHackCountLimit", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;

		case 1:
			GetPrivateProfileString("GameServerInfo", "CreateCharacter", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gCreateCharacter = atoi(szTemp);

			break;

		case 2:
			GetPrivateProfileString("GameServerInfo", "GuildCreate", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreate = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 57)), gGuildCreate);
			GetPrivateProfileString("GameServerInfo", "GuildDestroy", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildDestroy = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 58)), gGuildDestroy);
			GetPrivateProfileString("GameServerInfo", "GuildCreateLevel", "100", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gGuildCreateLevel = atoi(szTemp);
			LogAdd(lMsg.Get(MSGGET(2, 59)), gGuildCreateLevel);
			g_bCastleGuildDestoyLimit = GetPrivateProfileInt("GameServerInfo", "CastleOwnerGuildDestroyLimit", 1, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 3:
			GetPrivateProfileString("GameServerInfo", "Trade", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			bCanTrade = atoi(szTemp);
			break;
		case 4:
			bCanChaosBox = GetPrivateProfileInt("GameServerInfo", "ChaosBox", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 5:
			gDoPShopOpen = GetPrivateProfileInt("GameServerInfo", "PersonalShopOpen", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 6:
			GetPrivateProfileString("GameServerInfo", "PKItemDrop", "1", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gPkItemDrop = atoi(szTemp);
			break;
		case 7:
			GetPrivateProfileString("GameServerInfo", "ItemDropPer", "10", szTemp, 5, gDirPath.GetNewPath("commonserver.cfg"));
			gItemDropPer = atoi(szTemp);
			break;
		case 8:
			gAttackSpeedTimeLimit = GetPrivateProfileInt("GameServerInfo", "AttackSpeedTimeLimit", 800, gDirPath.GetNewPath("commonserver.cfg"));
			bIsIgnorePacketSpeedHackDetect = GetPrivateProfileInt("GameServerInfo", "IsIgnorePacketHackDetect", 0, gDirPath.GetNewPath("commonserver.cfg"));
			gHackCheckCount = GetPrivateProfileInt("GameServerInfo", "HackCheckCount", 5, gDirPath.GetNewPath("commonserver.cfg"));
			gMinimumAttackSpeedTime = GetPrivateProfileInt("GameServerInfo", "MinimumAttackSpeedTime", 200 , gDirPath.GetNewPath("commonserver.cfg"));
			gDetectedHackKickCount = GetPrivateProfileInt("GameServerInfo", "DetectedHackKickCount", 10, gDirPath.GetNewPath("commonserver.cfg"));
			gIsKickDetecHackCountLimit = GetPrivateProfileInt("GameServerInfo", "IsKickDetecHackCountLimit", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
		case 9:
			gUseNPGGChecksum = GetPrivateProfileInt("GameServerInfo", "UseNPGGChecksum", 0, gDirPath.GetNewPath("commonserver.cfg"));
			break;
	}
}

void SetEventOff() //0058C4F0
{
	if(gEventOff == TRUE)
	{
		//Lucky Coin Event
		g_bLuckyCoinEventOn = FALSE;
		g_iLuckyCoinDropRate = 0;

		//Ribbon Box Event
		g_bRibbonBoxEvent = FALSE;
		g_iRedRibbonBoxDropLevelMin = 0;
		g_iRedRibbonBoxDropLevelMax = 0;
		g_iRedRibbonBoxDropRate = 0;
		g_iRedRibbonBoxDropZenRate = 0;
		g_iRedRibbonBoxDropZen = 0;
		g_iGreenRibbonBoxDropLevelMin = 0;
		g_iGreenRibbonBoxDropLevelMax = 0;
		g_iGreenRibbonBoxDropRate = 0;
		g_iGreenRibbonBoxDropZenRate = 0;
		g_iGreenRibbonBoxDropZen = 0;
		g_iBlueRibbonBoxDropLevelMin = 0;
		g_iBlueRibbonBoxDropLevelMax = 0;
		g_iBlueRibbonBoxDropRate = 0;
		g_iBlueRibbonBoxDropZenRate = 0;
		g_iBlueRibbonBoxDropZen = 0;

		//Pouch of Blessing
		g_bNewYearLuckyBagMonsterEventOn = FALSE;

		//Chocolate Event
		g_bChocolateBoxEvent = FALSE;
		g_iPinkChocolateBoxDropLevelMin = 0;
		g_iPinkChocolateBoxDropLevelMax = 0;
		g_iPinkChocolateBoxDropRate = 0;
		g_iPinkChocolateBoxDropZenRate = 0;
		g_iPinkChocolateBoxDropZen = 0;
		g_iRedChocolateBoxDropLevelMin = 0;
		g_iRedChocolateBoxDropLevelMax = 0;
		g_iRedChocolateBoxDropRate = 0;
		g_iRedChocolateBoxDropZenRate = 0;
		g_iRedChocolateBoxDropZen = 0;
		g_iBlueChocolateBoxDropLevelMin = 0;
		g_iBlueChocolateBoxDropLevelMax = 0;
		g_iBlueChocolateBoxDropRate = 0;
		g_iBlueChocolateBoxDropZenRate = 0;
		g_iBlueChocolateBoxDropZen = 0;

		//Candy Box Event
		g_bCandyBoxEvent = FALSE;
		g_iLightPurpleCandyBoxDropLevelMin = 0;
		g_iLightPurpleCandyBoxDropLevelMax = 0;
		g_iLightPurpleCandyBoxDropRate = 0;
		g_iLightPurpleCandyBoxDropZenRate = 0;
		g_iLightPurpleCandyBoxDropZen = 0;
		g_iVermilionCandyBoxDropLevelMin = 0;
		g_iVermilionCandyBoxDropLevelMax = 0;
		g_iVermilionCandyBoxDropRate = 0;
		g_iVermilionCandyBoxDropZenRate = 0;
		g_iVermilionCandyBoxDropZen = 0;
		g_iDeepBlueCandyBoxDropLevelMin = 0;
		g_iDeepBlueCandyBoxDropLevelMax = 0;
		g_iDeepBlueCandyBoxDropRate = 0;
		g_iDeepBlueCandyBoxDropZenRate = 0;
		g_iDeepBlueCandyBoxDropZen = 0;
	}
}