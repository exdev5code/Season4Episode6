#ifndef CONFIGS_H
#define CONFIGS_H

#define CommonServer_DIR "..\\ExTeam\\CommonServer.ini"
#define Skills_DIR	"..\\ExTeam\\Skills.ini"
#define Character_DIR "..\\ExTeam\\Character.ini"
#define Commands_DIR "..\\ExTeam\\Commands.ini"
#define Events_DIR	"..\\ExTeam\\Events.ini"
#define Reset_DIR "..\\ExTeam\\Reset.ini"
#define GrandReset_DIR "..\\ExTeam\\GrandReset.ini"
#define Pets_DIR "..\\ExTeam\\Pets.ini"
#define PVP_DIR	"..\\ExTeam\\PvPSystem.ini"
#define GoldenDrop_DIR "..\\ExTeam\\Events\\GoldenInvasionDrop.ini"
#define PlayerConnect_DIR "..\\ExTeam\\PlayerConnect.ini"
#ifndef _NEW_JEWELS_2_
#define NewJewels_DIR "..\\ExTeam\\NewJewels.ini"
#endif
#define OffTrade_DIR "..\\ExTeam\\OffTrade.ini"

class cExConfigs
{
public:
	void LoadConfigs();
	//~~~~~~~~~~~~~~
	//CommonServer
	//~~~~~~~~~~~~~~
	struct sCommonServer
	{
		int EnableCheckSum;
		int Ex_PersonalID;

		int AllianceMinPlayers;

		int ExParty3ExpPercent;
		int ExParty4ExpPercent;
		int ExParty5ExpPercent;
		int ExPartyExpPercentOther;
		int ExParty2ExpSetPercent;
		int ExParty3ExpSetPercent;
		int ExParty4ExpSetPercent;
		int ExParty5ExpSetPercent;
		int ExParty1ExpSetPercent;

		int ExDropZenParty;
		int MaxDropZen;

		int ExExcellentAncient;
		int ExExcellentSocket;
		int ExAncientSocket;
		int ExAddJoHtoAnc;

		int Ex_ItemsDurationTime;

		int Ex_LifeRate;
		int Ex_SoulRate;
		int Ex_SoulRateLuck;

		int ExMixNormal10SuccessRate;
		int ExMix380AncExc10SuccessRate;
		int ExMixSocket10SuccessRate;
		int ExMixNormal11SuccessRate;
		int ExMix380AncExc11SuccessRate;
		int ExMixSocket11SuccessRate;
		int ExMixNormal12SuccessRate;
		int ExMix380AncExc12SuccessRate;
		int ExMixSocket12SuccessRate;
		int ExMixNormal13SuccessRate;
		int ExMix380AncExc13SuccessRate;
		int ExMixSocket13SuccessRate;
		int ExMixLuckOptRateAdd;
		int ExMixMaxSuccessRate;
		int ExWing2MaxSuccessRate;
		int ExDarkHorseMixSuccessRate;
		int ExDarkSpiritMixSuccessRate;
		int ExFeatherofCondorMixMaxPercent;
		int ExWingLv3MixMaxPercent;
		int ExDinorantMixRate;

		int Wing2_5MaxSuccessRate;
		int Wing4MaxSuccessRate;
		int Wing5MaxSuccessRate;

		int Ex_MasterDropZen;

		char GuardMessage[50];

		int KundunAncDrop;

		int DisatanceObjViewe;

		int MoveExlOptLimit;
#ifdef _MuReal_
		int WCoinTime;
		int WCoinReward;
#endif

#ifdef _EXL_DROP_RATE_
		int ExlDropRate;
#endif
#ifdef _DROP_ZEN_RATE_
		int ZenDropRate;
#endif
		bool ReConnect;

		int MaxReflect;

#if(_NEW_PT_SYSTEM_)
		int RePartyEnable;
		int RePartyTime;
		int AutoSetLeader;
		int CommandSetLeader;
#endif

		int CountItemDropSelupan;
		bool MarlonQuestReset;

	}CommonServer;
	//~~~~~~~~~~~~~~
	//Skills
	//~~~~~~~~~~~~~~
	struct sSkills
	{
		int ExStartPowerHp;
		int ExVitality;
		int ExEnergy;
		int ExMaxPowerHp;

		int ExMaster_StartPowerHp;
		int ExMaster_Vitality;
		int ExMaster_Energy;
		int ExMaster_MaxPowerHp;

		int ExMSStartPower;
		int ExMSAgility;
		int ExMSEnergy;
		int ExMSMaxPower;

		int ExMaster_MSStartPower;
		int ExMaster_MSAgility;
		int ExMaster_MSEnergy;
		int ExMaster_MSMaxPower;

		int ExWizardryPowerMax;

		int ExAttackEnergy;
		int ExDefenceEnergy;

		int NeedArrow;

		int ExCriticalEnergy;
		int ExCriticalCommand;
		int ExCritEneTime;

		int ExRefStartPower;
		int ExRefEnergy;
		int ExRefMaxPower;
		int ExRefStartTime;
		int ExRefEneTime;

		int Ex_BerserkerPower;

		int ExBerserkerStartTime;
		int ExBerserkerEnergyTime;
		int ExBerserkerMaxTime;
		int ExBerserkerEneIncMana;
		int ExBerserkerEneDecLife;

		int Ex_BerserkerDex;

		int Ex_WeaknessPower;
		int Ex_InnovationPower;

		int ExCSSKill;

		int AttackByNPC;
		int AttackByPlayer;

		int PetAttackByNPC;
		int PetAttackByPlayer;

		//Skills Level
		int TwistingSlashLevel;
		int RagefulBlowLevel;
		int DeathStabLevel;
		int ImpaleLevel;
		int InnerStrengthLevel;
		int PenetrationLevel;
		
	}Skills;
	//~~~~~~~~~~~~~~
	//Character
	//~~~~~~~~~~~~~~
	struct sCharacter
	{
		int ELFDamageMax_Bow_StrDexRight;
		int ELFDamageMin_Bow_StrDexRight;
		int ELFDamageMax_Bow_StrDexLeft;
		int ELFDamageMin_Bow_StrDexLeft;

		int ELFDamageMax_NoBow_StrRight;
		int ELFDamageMax_NoBow_DexRight;
		int ELFDamageMin_NoBow_StrRight;
		int ELFDamageMin_NoBow_DexRight;
		
		int ELFDamageMax_NoBow_StrLeft;
		int ELFDamageMax_NoBow_DexLeft;
		int ELFDamageMin_NoBow_StrLeft;
		int ELFDamageMin_NoBow_DexLeft;

		int ELFDamageMax_DexStrRight;
		int ELFDamageMin_DexStrRight;
		int ELFDamageMax_DexStrLeft;
		int	ELFDamageMin_DexStrLeft;
		//----------------------
		int DKDamageMax_StrRight;
		int DKDamageMin_StrRight;
		int DKDamageMax_StrLeft;
		int DKDamageMin_StrLeft;
		//----------------------
		int MGDamageMax_StrRight;
		int MGDamageMax_EneRight;
		int MGDamageMin_StrRight;
		int MGDamageMin_EneRight;

		int MGDamageMax_StrLeft;
		int MGDamageMax_EneLeft;
		int MGDamageMin_StrLeft;
		int MGDamageMin_EneLeft;

		//----------------------
		int SUMDamageMax_StrRight;
		int SUMDamageMin_StrRight;
		int SUMDamageMax_StrLeft;
		int SUMDamageMin_StrLeft;
		//----------------------
		int DWDamageMax_StrRight;
		int DWDamageMin_StrRight;
		int DWDamageMax_StrLeft;
		int DWDamageMin_StrLeft;
		//----------------------
		int DLDamageMax_StrRight;
		int DLDamageMax_EneRight;
		int DLDamageMin_StrRight;
		int DLDamageMin_EneRight;
		
		int DLDamageMax_StrLeft;
		int DLDamageMax_EneLeft;
		int DLDamageMin_StrLeft;
		int DLDamageMin_EneLeft;
		//----------------------
		int SUMMagicDamageMax;
		int SUMMagicDamageMin;
		//----------------------	
		int MGMagicDamageMax;
		int MGMagicDamageMin;
		//------
		int DWMagicDamageMax;
		int DWMagicDamageMin;	
		//------------------
		int ELFSuccessfulBlocking;
		int DLSuccessfulBlocking;
		int SUMSuccessfulBlocking;
		int DWSuccessfulBlocking;
		int DKSuccessfulBlocking;
		int MGSuccessfulBlocking;
		//--------------------
		int ELFDefense;
		int DKDefense;
		int DLDefense;
		int SUMDefense;
		int MGDefense;
		int DWDefense;

	}Character;

	struct sCommands
	{
		char CommandPost[100];	//Post
		char CommandAddStr[100];
		char CommandAddAgi[100];
		char CommandAddVit[100];
		char CommandAddEne[100];
		char CommandAddCmd[100];
		char CommandPkClear[100];
		char CommandReset[100];		// = "/reset";		//Reset
		char CommandGrandReset[100]; //= "/grandreset";	//Grand Reset
		// command configs
		int PostLevel;
		int PostMoney;
		char PostPrist[100];
		int PostColor;
		int OnlyPostVip;
		// add config
		int AddMoney;
		int AddLeveL;
		// pk clear config
		int Ex_PkClear_Enabled;
		int Ex_PkClearLevel;
		int Ex_PkClearMoney;
		int Ex_PKClearType;
	}Command;

	struct sEvent
	{
		int Ex_IllusionTemplPlaerMin;
		int Ex_ItDropType;
		int Ex_ItDropID;
		int Ex_ItDropLevel;
		int Ex_ItDropSkill;
		int Ex_ItDropLuck;
		int Ex_ItDropOpt;
		int Ex_ItDropExcOpt;
		int Ex_ItDropAncOpt;

		//Configs Blood Castle
		int Ex_BCDropType;
		int Ex_BCDropID;
		int Ex_BCDropLevel;
		int Ex_BCDropSkill;
		int Ex_BCDropLuck;
		int Ex_BCDropOpt;
		int Ex_BCDropExcOpt;
		int Ex_BCDropAncOpt;

		int Ex_CCMinPlayer;
	}Event;

	struct sReset
	{
		int EnableResetSystem;
		int Maxres;
		int ZenForm;
		int NeedZen;
		int NeedLevel;
		int AddForm;
		int AddPointsDW;
		int AddPointsDK;
		int AddPointsELF;
		int AddPointsSUM;
		int AddPointsMG;
		int AddPointsDL;
		//int AddPcPoint;
		int NeedEmptyInv;
		int AddExPoint;
		int AddWcoin;
	}Reset;

	struct sGrandReset
	{
		int EnableGrandResetSystem;	
		int MaxGrandRes;
		int ZenForm;
		int NeedZen;
		int NeedRes;
		int NeedLevel;
		int AddForm;
		int AddPointsDW;
		int AddPointsDK;
		int AddPointsELF;
		int AddPointsSUM;
		int AddPointsMG;
		int AddPointsDL;
		int AddPcPoint;
		int NeedEmptyInv;
		int AddWcoin;
	}GrandReset;

	struct sPets
	{
		int Ex_PandaRingZen;
		int Ex_PandaRingAttack;
		int Ex_PandaDef;
		int Ex_PandaExp;
	}Pet;

	struct sPvP
	{
		int ExPkPartySystem;
		int ExPkLimit;
		int DuelGate;

		int AttackInDuel;
	}PvP;

	struct sGoldenDrop
	{
		int ItemType44;
		int ItemIndex44;
		int level44;

		int ItemType43;
		int ItemIndex43;
		int level43;

		int ItemType78;
		int ItemIndex78;
		int level78;

		int ItemType493;
		int ItemIndex493;
		int level493;

		int ItemType53;
		int ItemIndex53;
		int level53;

		int ItemType54;
		int ItemIndex54;
		int level54;

		int ItemType80;
		int ItemIndex80;
		int level80;

		int ItemType81;
		int ItemIndex81;
		int level81;

		int ItemType494;
		int ItemIndex494;
		int level494;

		int ItemType82;
		int ItemIndex82;
		int level82;

		int ItemType83;
		int ItemIndex83;
		int level83;

		int ItemType495;
		int ItemIndex495;
		int level495;

		int ItemType496;
		int ItemIndex496;
		int level496;

		int ItemType497;
		int ItemIndex497;
		int level497;

		int ItemType498;
		int ItemIndex498;
		int level498;

		int ItemType499;
		int ItemIndex499;
		int level499;

		int ItemType500;
		int ItemIndex500;
		int level500;

		int ItemType79;
		int ItemIndex79;
		int randlevel1_79;
		int randlevel2_79;
		int randlevel3_79;
		int countitem79;

		int ItemType501;
		int ItemIndex501;
		int randlevel1_501;
		int randlevel2_501;
		int countitem501;

	}GoldenDrop;

	struct sPlayerConnect
	{
		int EnablePlayerConnectSystem;
		int ShowReset;
		int ShowGReset;
	}PlayerConnect;

	struct sNewJewels
	{
		int JewelOfExellentRate;
		int JewelOfLuckRate;
		int JewelOfDivinityRate;
	}ExNewJewel;

	struct sOffTrade
	{
		int OffTradeZen;
		int OffTradeExPoint;
		int OffTradeWcoin;
		int OffTradeCredit;

		int OffTradeChaos;
		int OffTradeBless;
		int OffTradeSoul;
		int OffTradeLife;
	}OffTrade;
};
extern cExConfigs ExConfig;

#endif CONFIGS_H