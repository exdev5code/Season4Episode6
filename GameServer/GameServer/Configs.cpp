#include "StdAfx.h"
#include "Configs.h"
#include "ExQuestSystem.h"
#include "OffExp.h"
#include "Experience.h"
#include "DropZenManager.h"
#include "PvPMapSystem.h"
#include "PriceManager.h"
#include "TvTEvent.h"
#include "GrandHeroSystem.h"
#include "ItemDropManager.h"
#include "MossMerchant.h"
#include "GoldenArcher.h"
#include "PCPointSystem.h"
#include "Security.h"
#include "MapExp.h"
#include "SystemOfRage.h"

#ifdef TALISMAN_SYSTEM
#include "TalismanSystem.h"
#endif

#ifdef PREMIUM_SYSTEM
#include "PremiumSystem.h"
#endif

#if __MuRain__
#include "NoobSystem.h"

#endif
#include "Reset.h"
#ifdef PACK_SYSTEM
#include "PackSystem.h"
#endif

#ifdef DROP_EVENT
#include "DropEvent.h"
#endif
#include "VipSystem.h"

#ifdef _HAPPY_HOUR_EVENT_
#include "HappyHour.h"
#endif
#ifdef _EVANGELION_EVENT_
#include "SearchEvent.h"
#endif
#include "CreditDonate.h"
#include "LoraBattle.h"
#include "BMQuest.h"
#include "ChaosMixManager.h"
#include "NewJewels.h"
#include "PlayerConnect.h"
#include "BalanceSystem.h"
#include "JewelsBank.h"
#include "NewItemDropManager.h"
#include "NPCTeleport.h"
#include "ComboCustom.h"
#include "CustomNpc.h"

cExConfigs ExConfig;

void cExConfigs::LoadConfigs()
{
#ifdef SECURITYGS
	if(!SecurityGS.TreSecurity()) return;
#endif

	

#if(_JEWELS_BANK_)
	gJewelsBank.Load();
#endif

	LoadConnectini();
	//ExQuestSystem
	ExQuestSystem.Loader();
	//OffExp System
	OffExp.LoadConfig();
	ExExperience.LoadConfig();
	DropZenManager.LoadConfig();
	PvPMapSystem.LoadConfig();
	PriceManager.LoadConfig();

	gItemDropManager.Init();
	gMossMerchant.Init();
	GoldenArcher.Load();
	ExPCPointSystem.Load();

	gMapExp.Init();

#ifdef _CHAOS_MIX_MANAGER_
	ChaosMixManager.Init();
#endif
	gReset.Load();
#if __MuRain__
	gReset.Init();
#endif

#ifdef TVTEVENT
	TvT.Load();	//TvTEvent
#endif
#if(_GRAND_HERO_SYSTEM_)
	GrandHero.Load();
#endif
#ifdef TALISMAN_SYSTEM
	TalismanSystem.LoadConfig();
#endif
#ifdef PREMIUM_SYSTEM
	Premium.Loader();
#endif

#if __MuRain__
	gNoobSystem.Init();
#endif

#ifdef PACK_SYSTEM
	gPackSystem.Load();
#endif

#ifdef DROP_EVENT
	DropEvent.LoadFile();
#endif

#ifdef _MuReal_
	VipSystem.LoadConfig();
#endif

#ifdef _HAPPY_HOUR_EVENT_
	HappyHour.LoadConfig();
#endif

#ifdef _EVANGELION_EVENT_
	SearchEvent.LoadingEvent();
#endif

#ifdef _SYSTEM_OF_RAGE_
	gSystemOfRage.Load();
#endif

#if(_CREDIT_DONATE_)
	gCreditDonate.Load();
#endif

#ifdef _LORA_BATTLE_
	LoraBattle.LoadConfigs();
#endif
#if(BM_QUEST_SYSTEM_)
	BMQuest.StartUP();
#endif
#if _NEW_JEWELS_2_
	gNewJewels.Load();
#endif
#if(_BALANS_SYSTEM_)
	gBalanceSystem.Load();
#endif

#if(NEW_ITEM_DROP)
	NewgItemDropManager.Init();
#endif

#if(CUSTOM_NPC_TELEPORT==TRUE)
	g_NPCTeleport.Load();
#endif

#if(DEV_COMBO_CUSTOM==TRUE)
	g_ComboCustom.Load();
#endif

	gCustomNpc.Load();

	//----------------
	//CommonServer
	//----------------

	this->CommonServer.EnableCheckSum = GetPrivateProfileInt("Common","CheckSum",0,CommonServer_DIR);
	this->CommonServer.Ex_PersonalID = GetPrivateProfileInt("Common","PersonalID",0,CommonServer_DIR);

	this->CommonServer.AllianceMinPlayers = GetPrivateProfileInt("Guild","AllianceMinPlayers",20,CommonServer_DIR);

	this->CommonServer.ExParty3ExpPercent = GetPrivateProfileInt("Party","Party3ExpPercent",230,CommonServer_DIR);
	this->CommonServer.ExParty4ExpPercent = GetPrivateProfileInt("Party","Party4ExpPercent",270,CommonServer_DIR);
	this->CommonServer.ExParty5ExpPercent = GetPrivateProfileInt("Party","Party5ExpPercent",300,CommonServer_DIR);
	this->CommonServer.ExPartyExpPercentOther = GetPrivateProfileInt("Party","PartyExpPercentOther",120,CommonServer_DIR);
	this->CommonServer.ExParty2ExpSetPercent = GetPrivateProfileInt("Party","Party2ExpSetPercent",160,CommonServer_DIR);
	this->CommonServer.ExParty3ExpSetPercent = GetPrivateProfileInt("Party","Party3ExpSetPercent",180,CommonServer_DIR);
	this->CommonServer.ExParty4ExpSetPercent = GetPrivateProfileInt("Party","Party4ExpSetPercent",200,CommonServer_DIR);
	this->CommonServer.ExParty5ExpSetPercent = GetPrivateProfileInt("Party","Party5ExpSetPercent",220,CommonServer_DIR);
	this->CommonServer.ExParty1ExpSetPercent = GetPrivateProfileInt("Party","Party1ExpSetPercent",150,CommonServer_DIR);

	this->CommonServer.ExDropZenParty = GetPrivateProfileInt("Party","DropZenParty",10,CommonServer_DIR);
	this->CommonServer.MaxDropZen = GetPrivateProfileInt("Party","MaxDropZen",1000000,CommonServer_DIR);

	this->CommonServer.ExExcellentAncient = GetPrivateProfileInt("Items","ExcellentAncient",1,CommonServer_DIR);
	this->CommonServer.ExExcellentSocket = GetPrivateProfileInt("Items","ExcellentSocket",1,CommonServer_DIR);
	this->CommonServer.ExAncientSocket = GetPrivateProfileInt("Items","AncientSocket",1,CommonServer_DIR);
	this->CommonServer.ExAddJoHtoAnc = GetPrivateProfileInt("Items","AddJoHtoAnc",1,CommonServer_DIR);

	this->CommonServer.Ex_ItemsDurationTime = GetPrivateProfileInt("Items","ItemsDurationTime",120,CommonServer_DIR);

	this->CommonServer.Ex_LifeRate = GetPrivateProfileInt("JewelRates","LifeRate",50,CommonServer_DIR);
	this->CommonServer.Ex_SoulRate = GetPrivateProfileInt("JewelRates","SoulRate",50,CommonServer_DIR);
	this->CommonServer.Ex_SoulRateLuck = GetPrivateProfileInt("JewelRates","SoulRateLuck",20,CommonServer_DIR);

	this->CommonServer.ExMixNormal10SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal10SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ExMix380AncExc10SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc10SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ExMixSocket10SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket10SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ExMixNormal11SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal11SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ExMix380AncExc11SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc11SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ExMixSocket11SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket11SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ExMixNormal12SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal12SuccessRate",60,CommonServer_DIR);
	this->CommonServer.ExMix380AncExc12SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc12SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ExMixSocket12SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket12SuccessRate",40,CommonServer_DIR);
	this->CommonServer.ExMixNormal13SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal13SuccessRate",55,CommonServer_DIR);
	this->CommonServer.ExMix380AncExc13SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc13SuccessRate",50,CommonServer_DIR);
	this->CommonServer.ExMixSocket13SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket13SuccessRate",35,CommonServer_DIR);
	this->CommonServer.ExMixLuckOptRateAdd = GetPrivateProfileInt("ChaosMix","MixLuckOptRateAdd",20,CommonServer_DIR);
	this->CommonServer.ExMixMaxSuccessRate = GetPrivateProfileInt("ChaosMix","MixMaxSuccessRate",75,CommonServer_DIR);
	this->CommonServer.ExWing2MaxSuccessRate = GetPrivateProfileInt("ChaosMix","Wing2MaxSuccessRate",90,CommonServer_DIR);
	this->CommonServer.ExDarkHorseMixSuccessRate = GetPrivateProfileInt("ChaosMix","DarkHorseMixSuccessRate",60,CommonServer_DIR);
	this->CommonServer.ExDarkSpiritMixSuccessRate = GetPrivateProfileInt("ChaosMix","DarkSpiritMixSuccessRate",60,CommonServer_DIR);
	this->CommonServer.ExFeatherofCondorMixMaxPercent = GetPrivateProfileInt("ChaosMix","FeatherofCondorMixMaxPercent",60,CommonServer_DIR);
	this->CommonServer.ExWingLv3MixMaxPercent = GetPrivateProfileInt("ChaosMix","WingLv3MixMaxPercent",40,CommonServer_DIR);
	this->CommonServer.ExDinorantMixRate = GetPrivateProfileInt("ChaosMix","DinorantMixRate",70,CommonServer_DIR);

	this->CommonServer.Wing2_5MaxSuccessRate = GetPrivateProfileInt("ChaosMix","Wing2_5MaxSuccessRate",60,CommonServer_DIR);
	this->CommonServer.Wing4MaxSuccessRate = GetPrivateProfileInt("ChaosMix","Wing4MaxSuccessRate",40,CommonServer_DIR);
	this->CommonServer.Wing5MaxSuccessRate = GetPrivateProfileInt("ChaosMix","Wing5MaxSuccessRate",40,CommonServer_DIR);

	this->CommonServer.Ex_MasterDropZen = GetPrivateProfileInt("MasterLevel","MasterDropZen",0,CommonServer_DIR);

	GetPrivateProfileString("Guard", "GuardMessage","Welcome to Ex-Games",this->CommonServer.GuardMessage,50,CommonServer_DIR);

	this->CommonServer.KundunAncDrop = GetPrivateProfileInt("Monsters","KundunAncDrop",2500,CommonServer_DIR);

	this->CommonServer.DisatanceObjViewe = GetPrivateProfileInt("ObjViewe","DisatanceObjViewe",15,CommonServer_DIR);

	this->CommonServer.MoveExlOptLimit = GetPrivateProfileInt("ItemMoveLimit","MoveExlOptLimit",0,CommonServer_DIR);

#if(_NEW_PT_SYSTEM_	==1)
	this->CommonServer.RePartyEnable = GetPrivateProfileInt("NewPartySystem","RePartyEnable",1,CommonServer_DIR);
	this->CommonServer.RePartyTime = GetPrivateProfileInt("NewPartySystem","RePartyTime",10,CommonServer_DIR) * 1000;
	this->CommonServer.AutoSetLeader = GetPrivateProfileInt("NewartySystem","AutoSetLeader",1,CommonServer_DIR);
	this->CommonServer.CommandSetLeader = GetPrivateProfileInt("NewartySystem","CommandSetLeader",1,CommonServer_DIR);
#endif

#ifdef _MuReal_
	this->CommonServer.WCoinTime = ( GetPrivateProfileInt("WCoin","WCoinTime",0,CommonServer_DIR) * 60 );
	this->CommonServer.WCoinReward = GetPrivateProfileInt("WCoin","WCoinReward",0,CommonServer_DIR);

	

#endif

#ifdef _EXL_DROP_RATE_
	this->CommonServer.ExlDropRate = GetPrivateProfileInt("Drop","ExlDropRate",10,CommonServer_DIR);
#endif

#ifdef _DROP_ZEN_RATE_ 
	this->CommonServer.ZenDropRate = GetPrivateProfileInt("Drop","ZenDropRate",100,CommonServer_DIR);
#endif
	this->CommonServer.ReConnect = GetPrivateProfileInt("ReConnect","ReConnect",1,CommonServer_DIR);
	this->CommonServer.MaxReflect = GetPrivateProfileInt("MaxReflect","MaxReflect",90,CommonServer_DIR);

	this->CommonServer.CountItemDropSelupan = GetPrivateProfileInt("ExTeam","CountItemDropSelupan",10,CommonServer_DIR);

	this->CommonServer.MarlonQuestReset = GetPrivateProfileInt("ExTeam","MarlonQuestReset",0,CommonServer_DIR);
	//----------------
	//		Skills
	//----------------

	this->Skills.ExStartPowerHp = GetPrivateProfileInt("DakrKnight","HPStartPower",12,Skills_DIR);
	this->Skills.ExVitality = GetPrivateProfileInt("DakrKnight","HPVitality",100,Skills_DIR);
	this->Skills.ExEnergy = GetPrivateProfileInt("DakrKnight","HPEnergy",20,Skills_DIR);
	this->Skills.ExMaxPowerHp = GetPrivateProfileInt("DakrKnight","HPMaxPower",200,Skills_DIR);

	this->Skills.ExMaster_StartPowerHp = GetPrivateProfileInt("DakrKnight","Master_HPStartPower",12,Skills_DIR);
	this->Skills.ExMaster_Vitality = GetPrivateProfileInt("DakrKnight","Master_HPVitality",100,Skills_DIR);
	this->Skills.ExMaster_Energy = GetPrivateProfileInt("DakrKnight","Master_HPEnergy",20,Skills_DIR);
	this->Skills.ExMaster_MaxPowerHp = GetPrivateProfileInt("DakrKnight","Master_HPMaxPower",200,Skills_DIR);

	this->Skills.ExMSStartPower = GetPrivateProfileInt("DarkWizard","MSStartPower",10,Skills_DIR);
	this->Skills.ExMSAgility = GetPrivateProfileInt("DarkWizard","MSAgility",50,Skills_DIR);
	this->Skills.ExMSEnergy = GetPrivateProfileInt("DarkWizard","MSEnergy",200,Skills_DIR);
	this->Skills.ExMSMaxPower = GetPrivateProfileInt("DarkWizard","MSMaxPower",50,Skills_DIR);

	this->Skills.ExMaster_MSStartPower = GetPrivateProfileInt("DarkWizard","Master_MSStartPower",10,Skills_DIR);
	this->Skills.ExMaster_MSAgility = GetPrivateProfileInt("DarkWizard","Master_MSAgility",50,Skills_DIR);
	this->Skills.ExMaster_MSEnergy = GetPrivateProfileInt("DarkWizard","Master_MSEnergy",200,Skills_DIR);
	this->Skills.ExMaster_MSMaxPower = GetPrivateProfileInt("DarkWizard","Master_MSMaxPower",50,Skills_DIR);

	this->Skills.ExWizardryPowerMax = GetPrivateProfileInt("DarkWizard","WizardryPowerMax",20,Skills_DIR);

	this->Skills.ExAttackEnergy = GetPrivateProfileInt("Elf","AttackEnergy",7,Skills_DIR);
	this->Skills.ExDefenceEnergy = GetPrivateProfileInt("Elf","DefenceEnergy",8,Skills_DIR);

	this->Skills.NeedArrow = GetPrivateProfileInt("Elf","NeedArrow",1,Skills_DIR);

	this->Skills.ExCriticalEnergy = GetPrivateProfileInt("DarkLord","CritEnergy",30,Skills_DIR);
	this->Skills.ExCriticalCommand = GetPrivateProfileInt("DarkLord","CritCommand",25,Skills_DIR);
	this->Skills.ExCritEneTime = GetPrivateProfileInt("DarkLord","CritEneTime",10,Skills_DIR);

	this->Skills.ExRefStartPower = GetPrivateProfileInt("Summoner","RefStartPower",30,Skills_DIR);
	this->Skills.ExRefEnergy = GetPrivateProfileInt("Summoner","RefEnergy",42,Skills_DIR);
	this->Skills.ExRefMaxPower = GetPrivateProfileInt("Summoner","RefMaxPower",50,Skills_DIR);
	this->Skills.ExRefStartTime = GetPrivateProfileInt("Summoner","RefStartTime",30,Skills_DIR);
	this->Skills.ExRefEneTime = GetPrivateProfileInt("Summoner","RefEneTime",25,Skills_DIR);

	this->Skills.Ex_BerserkerPower = GetPrivateProfileInt("Summoner","BerserkerPower",50,Skills_DIR);

	this->Skills.ExBerserkerStartTime = GetPrivateProfileInt("Summoner","BerserkerStartTime",30,Skills_DIR);
	this->Skills.ExBerserkerEnergyTime = GetPrivateProfileInt("Summoner","BerserkerEnergyTime",20,Skills_DIR);
	this->Skills.ExBerserkerMaxTime = GetPrivateProfileInt("Summoner","BerserkerMaxTime",0,Skills_DIR);

	this->Skills.ExBerserkerEneIncMana = GetPrivateProfileInt("Summoner","BerserkerEneIncMana",30,Skills_DIR);
	this->Skills.ExBerserkerEneDecLife = GetPrivateProfileInt("Summoner","BerserkerEneDecLife",60,Skills_DIR);

	this->Skills.Ex_BerserkerDex = GetPrivateProfileInt("Summoner","BerserkerDex",10,Skills_DIR);

	this->Skills.Ex_WeaknessPower = GetPrivateProfileInt("Summoner","WeaknessPower",30,Skills_DIR);

	this->Skills.Ex_InnovationPower = GetPrivateProfileInt("Summoner","InnovationPower",30,Skills_DIR);

	this->Skills.ExCSSKill = GetPrivateProfileInt("CastleSkills","CastleSkillsOnNormal",0,Skills_DIR);

	this->Skills.AttackByNPC = GetPrivateProfileInt("CastleSiege","AttackByNPC",20,Skills_DIR);
	this->Skills.AttackByPlayer = GetPrivateProfileInt("CastleSiege","AttackByPlayer",40,Skills_DIR);

	this->Skills.PetAttackByNPC = GetPrivateProfileInt("CastleSiegePet","PetAttackByNPC",20,Skills_DIR);
	this->Skills.PetAttackByPlayer = GetPrivateProfileInt("CastleSiegePet","PetAttackByPlayer",40,Skills_DIR);

	//Skills Level

	this->Skills.TwistingSlashLevel = GetPrivateProfileInt("Level","TwistingSlashLevel",80,Skills_DIR);
	this->Skills.RagefulBlowLevel = GetPrivateProfileInt("Level","RagefulBlowLevel",170,Skills_DIR);
	this->Skills.DeathStabLevel = GetPrivateProfileInt("Level","DeathStabLevel",160,Skills_DIR);
	this->Skills.ImpaleLevel = GetPrivateProfileInt("Level","ImpaleLevel",28,Skills_DIR);
	this->Skills.InnerStrengthLevel = GetPrivateProfileInt("Level","InnerStrengthLevel",120,Skills_DIR);
	this->Skills.PenetrationLevel = GetPrivateProfileInt("Level","PenetrationLevel",130,Skills_DIR);

	//----------------------
	//		Character
	//----------------------

	this->Character.ELFDamageMax_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexRight",4,Character_DIR);
	this->Character.ELFDamageMin_Bow_StrDexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexRight",7,Character_DIR);
	this->Character.ELFDamageMax_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_Bow_StrDexLeft",4,Character_DIR);
	this->Character.ELFDamageMin_Bow_StrDexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_Bow_StrDexLeft",7,Character_DIR);

	this->Character.ELFDamageMax_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrRight",8,Character_DIR);
	this->Character.ELFDamageMax_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexRight",4,Character_DIR);
	this->Character.ELFDamageMin_NoBow_StrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrRight",14,Character_DIR);
	this->Character.ELFDamageMin_NoBow_DexRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexRight",7,Character_DIR);

	this->Character.ELFDamageMax_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_StrLeft",8,Character_DIR);
	this->Character.ELFDamageMax_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_NoBow_DexLeft",4,Character_DIR);
	this->Character.ELFDamageMin_NoBow_StrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_StrLeft",14,Character_DIR);
	this->Character.ELFDamageMin_NoBow_DexLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_NoBow_DexLeft",7,Character_DIR);

	this->Character.ELFDamageMax_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrRight",4,Character_DIR);
	this->Character.ELFDamageMin_DexStrRight = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrRight",7,Character_DIR);
	this->Character.ELFDamageMax_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMax_DexStrLeft",4,Character_DIR);
	this->Character.ELFDamageMin_DexStrLeft = GetPrivateProfileInt("Fairy_Elf","DamageMin_DexStrLeft",7,Character_DIR);
	//----------------------
	this->Character.DKDamageMax_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMax_StrRight",4,Character_DIR);
	this->Character.DKDamageMin_StrRight = GetPrivateProfileInt("Dark_Knight","DamageMin_StrRight",6,Character_DIR);
	this->Character.DKDamageMax_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMax_StrLeft",4,Character_DIR);
	this->Character.DKDamageMin_StrLeft = GetPrivateProfileInt("Dark_Knight","DamageMin_StrLeft",6,Character_DIR);
	//----------------------
	this->Character.MGDamageMax_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrRight",4,Character_DIR);
	this->Character.MGDamageMax_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneRight",8,Character_DIR);
	this->Character.MGDamageMin_StrRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrRight",6,Character_DIR);
	this->Character.MGDamageMin_EneRight = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneRight",12,Character_DIR);

	this->Character.MGDamageMax_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_StrLeft",4,Character_DIR);
	this->Character.MGDamageMax_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMax_EneLeft",8,Character_DIR);
	this->Character.MGDamageMin_StrLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_StrLeft",6,Character_DIR);
	this->Character.MGDamageMin_EneLeft = GetPrivateProfileInt("Magic_Gladiator","DamageMin_EneLeft",12,Character_DIR);
	//----------------------
	this->Character.SUMDamageMax_StrRight = GetPrivateProfileInt("Summoner","DamageMax_StrRight",4,Character_DIR);
	this->Character.SUMDamageMin_StrRight = GetPrivateProfileInt("Summoner","DamageMin_StrRight",7,Character_DIR);
	this->Character.SUMDamageMax_StrLeft = GetPrivateProfileInt("Summoner","DamageMax_StrLeft",4,Character_DIR);
	this->Character.SUMDamageMin_StrLeft = GetPrivateProfileInt("Summoner","DamageMin_StrLeft",7,Character_DIR);
	//----------------------
	this->Character.DWDamageMax_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrRight",4,Character_DIR);
	this->Character.DWDamageMin_StrRight = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrRight",6,Character_DIR);
	this->Character.DWDamageMax_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMax_StrLeft",4,Character_DIR);
	this->Character.DWDamageMin_StrLeft = GetPrivateProfileInt("Dark_Wizard","DamageMin_StrLeft",6,Character_DIR);
	//------------------------
	this->Character.DLDamageMax_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMax_StrRight",5,Character_DIR);
	this->Character.DLDamageMax_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMax_EneRight",10,Character_DIR);
	this->Character.DLDamageMin_StrRight = GetPrivateProfileInt("Dark_Lord","DamageMin_StrRight",7,Character_DIR);
	this->Character.DLDamageMin_EneRight = GetPrivateProfileInt("Dark_Lord","DamageMin_EneRight",14,Character_DIR);

	this->Character.DLDamageMax_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_StrLeft",5,Character_DIR);
	this->Character.DLDamageMax_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMax_EneLeft",10,Character_DIR);
	this->Character.DLDamageMin_StrLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_StrLeft",7,Character_DIR);
	this->Character.DLDamageMin_EneLeft = GetPrivateProfileInt("Dark_Lord","DamageMin_EneLeft",14,Character_DIR);
	//-------------------------

	this->Character.SUMMagicDamageMax = GetPrivateProfileInt("Summoner","MagicDamageMax",4,Character_DIR);
	this->Character.SUMMagicDamageMin = GetPrivateProfileInt("Summoner","MagicDamageMin",9,Character_DIR);

	this->Character.MGMagicDamageMax = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMax",4,Character_DIR);
	this->Character.MGMagicDamageMin = GetPrivateProfileInt("Magic_Gladiator","MagicDamageMin",9,Character_DIR);

	this->Character.DWMagicDamageMax = GetPrivateProfileInt("Dark_Wizard","MagicDamageMax",4,Character_DIR);
	this->Character.DWMagicDamageMin = GetPrivateProfileInt("Dark_Wizard","MagicDamageMin",9,Character_DIR);

	//---------------------------------
	this->Character.ELFSuccessfulBlocking = GetPrivateProfileInt("Fairy_Elf","SuccessfulBlocking",4,Character_DIR);
	this->Character.DLSuccessfulBlocking = GetPrivateProfileInt("Dark_Lord","SuccessfulBlocking",7,Character_DIR);
	this->Character.SUMSuccessfulBlocking = GetPrivateProfileInt("Summoner","SuccessfulBlocking",4,Character_DIR);
	this->Character.DWSuccessfulBlocking = GetPrivateProfileInt("Dark_Wizard","SuccessfulBlocking",3,Character_DIR);
	this->Character.DKSuccessfulBlocking = GetPrivateProfileInt("Dark_Knight","SuccessfulBlocking",3,Character_DIR);
	this->Character.MGSuccessfulBlocking = GetPrivateProfileInt("Magic_Gladiator","SuccessfulBlocking",3,Character_DIR);
	//---------------------------------
	this->Character.ELFDefense = GetPrivateProfileInt("Fairy_Elf","Defense",10,Character_DIR);
	this->Character.DKDefense = GetPrivateProfileInt("Dark_Knight","Defense",3,Character_DIR);
	this->Character.DLDefense = GetPrivateProfileInt("Dark_Lord","Defense",7,Character_DIR);
	this->Character.SUMDefense = GetPrivateProfileInt("Summoner","Defense",3,Character_DIR);
	this->Character.MGDefense = GetPrivateProfileInt("Magic_Gladiator","Defense",4,Character_DIR);
	this->Character.DWDefense = GetPrivateProfileInt("Dark_Wizard","Defense",4,Character_DIR);
	//---------------------------------
	//			Commands
	//---------------------------------
	 GetPrivateProfileString("Post", "PostName","/post",Command.CommandPost,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "StrName","/str",Command.CommandAddStr,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "AgiName","/agi",Command.CommandAddAgi,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "VitName","/vit",Command.CommandAddVit,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "EneName","/ene",Command.CommandAddEne,100,Commands_DIR);
	 
	 GetPrivateProfileString("AddCommand", "CmdName","/cmd",Command.CommandAddCmd,100,Commands_DIR);
	 
	 GetPrivateProfileString("PkClear", "PkClearName","/pkclear",Command.CommandPkClear,100,Commands_DIR);

	 GetPrivateProfileString("Reset", "cmd","/reset",Command.CommandReset,100,Reset_DIR);

	 GetPrivateProfileString("GrandReset", "cmd","/grandreset",Command.CommandGrandReset,100,GrandReset_DIR);

	this->Command.PostLevel = GetPrivateProfileInt("Post","PostLevel",100,Commands_DIR);

	this->Command.OnlyPostVip = GetPrivateProfileInt("Post","OnlyPostVip",1,Commands_DIR);
	
	this->Command.PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,Commands_DIR);

	GetPrivateProfileString("Post", "PostPrist","[post]:",Command.PostPrist,100,Commands_DIR);

	this->Command.PostColor = GetPrivateProfileInt("Post","PostColor",1,Commands_DIR);

	this->Command.AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,Commands_DIR);
	this->Command.AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,Commands_DIR);

	this->Command.Ex_PkClear_Enabled = GetPrivateProfileInt("PkClear","Enabled",1,Commands_DIR);
	this->Command.Ex_PkClearLevel = GetPrivateProfileInt("PkClear","PkClearLevel",0,Commands_DIR);
	this->Command.Ex_PkClearMoney = GetPrivateProfileInt("PkClear","PkClearMoney",0,Commands_DIR);
	this->Command.Ex_PKClearType = GetPrivateProfileInt("PkClear","PKClearType",0,Commands_DIR);

	//---------------------------------
	//			Events
	//---------------------------------

	this->Event.Ex_IllusionTemplPlaerMin = GetPrivateProfileInt("IllusionTemple","ItMinPlayers",4,Events_DIR);
	this->Event.Ex_ItDropType	= GetPrivateProfileInt("IllusionTemple","ItDropType",12,Events_DIR);
	this->Event.Ex_ItDropID		= GetPrivateProfileInt("IllusionTemple","ItDropID",15,Events_DIR);
	this->Event.Ex_ItDropLevel	= GetPrivateProfileInt("IllusionTemple","ItDropLevel",0,Events_DIR);
	this->Event.Ex_ItDropSkill	= GetPrivateProfileInt("IllusionTemple","ItDropSkill",0,Events_DIR);
	this->Event.Ex_ItDropLuck	= GetPrivateProfileInt("IllusionTemple","ItDropLuck",0,Events_DIR);
	this->Event.Ex_ItDropOpt	= GetPrivateProfileInt("IllusionTemple","ItDropOpt",0,Events_DIR);
	this->Event.Ex_ItDropExcOpt	= GetPrivateProfileInt("IllusionTemple","ItDropExcOpt",0,Events_DIR);
	this->Event.Ex_ItDropAncOpt	= GetPrivateProfileInt("IllusionTemple","ItDropAncOpt",0,Events_DIR);

	this->Event.Ex_BCDropType	= GetPrivateProfileInt("BloodCastle","BCDropType",12,Events_DIR);
	this->Event.Ex_BCDropID		= GetPrivateProfileInt("BloodCastle","BCDropID",15,Events_DIR);
	this->Event.Ex_BCDropLevel	= GetPrivateProfileInt("BloodCastle","BCDropLevel",0,Events_DIR);
	this->Event.Ex_BCDropSkill	= GetPrivateProfileInt("BloodCastle","BCDropSkill",0,Events_DIR);
	this->Event.Ex_BCDropLuck	= GetPrivateProfileInt("BloodCastle","BCDropLuck",0,Events_DIR);
	this->Event.Ex_BCDropOpt	= GetPrivateProfileInt("BloodCastle","BCDropOpt",0,Events_DIR);
	this->Event.Ex_BCDropExcOpt	= GetPrivateProfileInt("BloodCastle","BCDropExcOpt",0,Events_DIR);
	this->Event.Ex_BCDropAncOpt	= GetPrivateProfileInt("BloodCastle","BCDropAncOpt",0,Events_DIR);

	this->Event.Ex_CCMinPlayer = GetPrivateProfileInt("ChaosCastle","CCMinPlayer",2,Events_DIR);

	//---------------------------------
	//			Reset
	//---------------------------------

	this->Reset.EnableResetSystem = GetPrivateProfileInt("Reset","Enable",0,Reset_DIR);	
	this->Reset.Maxres = GetPrivateProfileInt("Reset","Max.res",100,Reset_DIR);
	this->Reset.ZenForm = GetPrivateProfileInt("Reset","ZenForm",0,Reset_DIR);
	this->Reset.NeedZen = GetPrivateProfileInt("Reset","Need.Zen",0,Reset_DIR);
	this->Reset.NeedLevel = GetPrivateProfileInt("Reset","Need.Level",0,Reset_DIR);
	this->Reset.AddForm = GetPrivateProfileInt("Reset","Add.Form",0,Reset_DIR);
	this->Reset.AddPointsDW = GetPrivateProfileInt("Reset","Add.PointsDW",0,Reset_DIR);
	this->Reset.AddPointsDK = GetPrivateProfileInt("Reset","Add.PointsDK",0,Reset_DIR);
	this->Reset.AddPointsELF = GetPrivateProfileInt("Reset","Add.PointsELF",0,Reset_DIR);
	this->Reset.AddPointsSUM = GetPrivateProfileInt("Reset","Add.PointsSUM",0,Reset_DIR);
	this->Reset.AddPointsMG = GetPrivateProfileInt("Reset","Add.PointsMG",0,Reset_DIR);
	this->Reset.AddPointsDL = GetPrivateProfileInt("Reset","Add.PointsDL",0,Reset_DIR);
	//this->Reset.AddPcPoint = GetPrivateProfileInt("Reset","Add.PcPoint",0,Reset_DIR);
	this->Reset.NeedEmptyInv = GetPrivateProfileInt("Reset","Need.EmptyInv",1,Reset_DIR);

	this->Reset.AddExPoint = GetPrivateProfileInt("Reset","AddExPoint",0,Reset_DIR);
	this->Reset.AddWcoin = GetPrivateProfileInt("Reset","AddWcoin",0,Reset_DIR);

	//---------------------------------
	//			Grand Reset
	//---------------------------------

	this->GrandReset.EnableGrandResetSystem = GetPrivateProfileInt("GrandReset","Enable",0,GrandReset_DIR);	
	this->GrandReset.MaxGrandRes = GetPrivateProfileInt("GrandReset","Max.GrandRes",100,GrandReset_DIR);
	this->GrandReset.ZenForm = GetPrivateProfileInt("GrandReset","ZenForm",0,GrandReset_DIR);
	this->GrandReset.NeedZen = GetPrivateProfileInt("GrandReset","Need.Zen",0,GrandReset_DIR);
	this->GrandReset.NeedRes = GetPrivateProfileInt("GrandReset","Need.Res",0,GrandReset_DIR);
	this->GrandReset.NeedLevel = GetPrivateProfileInt("GrandReset","Need.Level",0,GrandReset_DIR);
	this->GrandReset.AddForm = GetPrivateProfileInt("GrandReset","Add.Form",0,GrandReset_DIR);
	this->GrandReset.AddPointsDW = GetPrivateProfileInt("GrandReset","Add.PointsDW",0,GrandReset_DIR);
	this->GrandReset.AddPointsDK = GetPrivateProfileInt("GrandReset","Add.PointsDK",0,GrandReset_DIR);
	this->GrandReset.AddPointsELF = GetPrivateProfileInt("GrandReset","Add.PointsELF",0,GrandReset_DIR);
	this->GrandReset.AddPointsSUM = GetPrivateProfileInt("GrandReset","Add.PointsSUM",0,GrandReset_DIR);
	this->GrandReset.AddPointsMG = GetPrivateProfileInt("GrandReset","Add.PointsMG",0,GrandReset_DIR);
	this->GrandReset.AddPointsDL = GetPrivateProfileInt("GrandReset","Add.PointsDL",0,GrandReset_DIR);
	this->GrandReset.AddPcPoint = GetPrivateProfileInt("GrandReset","Add.PcPoint",0,GrandReset_DIR);
	this->GrandReset.NeedEmptyInv = GetPrivateProfileInt("GrandReset","Need.EmptyInv",1,GrandReset_DIR);
	this->GrandReset.AddWcoin = GetPrivateProfileInt("GrandReset","AddWcoin",0,GrandReset_DIR);

	//---------------------------------
	//			Pets
	//---------------------------------

	this->Pet.Ex_PandaRingZen = GetPrivateProfileInt("PandaRing","Zen",30,Pets_DIR);
	this->Pet.Ex_PandaRingAttack = GetPrivateProfileInt("PandaRing","AttackDamage",30,Pets_DIR);
	this->Pet.Ex_PandaDef = GetPrivateProfileInt("Panda","Defense",50,Pets_DIR);
	this->Pet.Ex_PandaExp = GetPrivateProfileInt("Panda","Exp",50,Pets_DIR);

	//---------------------------------
	//			PVP 
	//---------------------------------

	this->PvP.ExPkPartySystem = GetPrivateProfileInt("PK","PKPartyOn",0,PVP_DIR);
	this->PvP.ExPkLimit = GetPrivateProfileInt("PK","PkLimit",6,PVP_DIR);
	this->PvP.DuelGate = GetPrivateProfileInt("Duel","Gate",294,PVP_DIR);

	this->PvP.AttackInDuel = GetPrivateProfileInt("Common","AttackInDuel",0,PVP_DIR);

	//---------------------------------
	//			Golden Drop
	//---------------------------------

	this->GoldenDrop.ItemType44 = GetPrivateProfileInt("Dragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex44 = GetPrivateProfileInt("Dragon","ItemIndex",13,GoldenDrop_DIR);
	this->GoldenDrop.level44 = GetPrivateProfileInt("Dragon","ItemLevel",0,GoldenDrop_DIR);

	this->GoldenDrop.ItemType43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level43 = GetPrivateProfileInt("GoldenBudgeDragon","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType78 = GetPrivateProfileInt("GoldenGoblin","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex78 = GetPrivateProfileInt("GoldenGoblin","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level78 = GetPrivateProfileInt("GoldenGoblin","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType493 = GetPrivateProfileInt("GoldenDarkKnight","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex493 = GetPrivateProfileInt("GoldenDarkKnight","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level493 = GetPrivateProfileInt("GoldenDarkKnight","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType53 = GetPrivateProfileInt("GoldenTitan","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex53 = GetPrivateProfileInt("GoldenTitan","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level53 = GetPrivateProfileInt("GoldenTitan","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType54 = GetPrivateProfileInt("GoldenSoldier","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex54 = GetPrivateProfileInt("GoldenSoldier","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level54 = GetPrivateProfileInt("GoldenSoldier","ItemLevel",8,GoldenDrop_DIR);

	this->GoldenDrop.ItemType80 = GetPrivateProfileInt("GoldenLizardKing","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex80 = GetPrivateProfileInt("GoldenLizardKing","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level80 = GetPrivateProfileInt("GoldenLizardKing","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType81 = GetPrivateProfileInt("GoldenVepar","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex81 = GetPrivateProfileInt("GoldenVepar","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level81 = GetPrivateProfileInt("GoldenVepar","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType494 = GetPrivateProfileInt("GoldenDevil","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex494 = GetPrivateProfileInt("GoldenDevil","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level494 = GetPrivateProfileInt("GoldenDevil","ItemLevel",9,GoldenDrop_DIR);

	this->GoldenDrop.ItemType82 = GetPrivateProfileInt("GoldenTantalos","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex82 = GetPrivateProfileInt("GoldenTantalos","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level82 = GetPrivateProfileInt("GoldenTantalos","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType83 = GetPrivateProfileInt("GoldenWheel","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex83 = GetPrivateProfileInt("GoldenWheel","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level83 = GetPrivateProfileInt("GoldenWheel","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType495 = GetPrivateProfileInt("GoldenGolem","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex495 = GetPrivateProfileInt("GoldenGolem","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level495 = GetPrivateProfileInt("GoldenGolem","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType496 = GetPrivateProfileInt("GoldenCrust","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex496 = GetPrivateProfileInt("GoldenCrust","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level496 = GetPrivateProfileInt("GoldenCrust","ItemLevel",10,GoldenDrop_DIR);

	this->GoldenDrop.ItemType497 = GetPrivateProfileInt("GoldenSatyrus","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex497 = GetPrivateProfileInt("GoldenSatyrus","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level497 = GetPrivateProfileInt("GoldenSatyrus","ItemLevel",11,GoldenDrop_DIR);

	this->GoldenDrop.ItemType498 = GetPrivateProfileInt("GoldenTwinTale","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex498 = GetPrivateProfileInt("GoldenTwinTale","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level498 = GetPrivateProfileInt("GoldenTwinTale","ItemLevel",11,GoldenDrop_DIR);

	this->GoldenDrop.ItemType499 = GetPrivateProfileInt("GoldenIronKnight","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex499 = GetPrivateProfileInt("GoldenIronKnight","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level499 = GetPrivateProfileInt("GoldenIronKnight","ItemLevel",12,GoldenDrop_DIR);

	this->GoldenDrop.ItemType500 = GetPrivateProfileInt("GoldenNapin","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex500 = GetPrivateProfileInt("GoldenNapin","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.level500 = GetPrivateProfileInt("GoldenNapin","ItemLevel",12,GoldenDrop_DIR);

	this->GoldenDrop.ItemType79 = GetPrivateProfileInt("GoldenDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex79 = GetPrivateProfileInt("GoldenDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel1_79 = GetPrivateProfileInt("GoldenDragon","randlevel1",8,GoldenDrop_DIR);
	this->GoldenDrop.randlevel2_79 = GetPrivateProfileInt("GoldenDragon","randlevel2",9,GoldenDrop_DIR);
	this->GoldenDrop.randlevel3_79 = GetPrivateProfileInt("GoldenDragon","randlevel3",10,GoldenDrop_DIR);
	this->GoldenDrop.countitem79 = GetPrivateProfileInt("GoldenDragon","countitem",5,GoldenDrop_DIR);

	this->GoldenDrop.ItemType501 = GetPrivateProfileInt("GoldenGreatDragon","ItemType",14,GoldenDrop_DIR);
	this->GoldenDrop.ItemIndex501 = GetPrivateProfileInt("GoldenGreatDragon","ItemIndex",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel1_501 = GetPrivateProfileInt("GoldenGreatDragon","randlevel1",11,GoldenDrop_DIR);
	this->GoldenDrop.randlevel2_501 = GetPrivateProfileInt("GoldenGreatDragon","randlevel2",12,GoldenDrop_DIR);
	this->GoldenDrop.countitem501 = GetPrivateProfileInt("GoldenGreatDragon","countitem",5,GoldenDrop_DIR);

	//---------------------------------
	//			Player Connect
	//---------------------------------

	this->PlayerConnect.EnablePlayerConnectSystem = GetPrivateProfileInt("Common","Enable",0,PlayerConnect_DIR);	
	this->PlayerConnect.ShowReset = GetPrivateProfileInt("Common","ShowReset",0,PlayerConnect_DIR);
	this->PlayerConnect.ShowGReset = GetPrivateProfileInt("Common","ShowGReset",0,PlayerConnect_DIR);

	//---------------------------------
	//			New Jewels Rate
	//---------------------------------

	this->ExNewJewel.JewelOfExellentRate = GetPrivateProfileInt("Common","JewelOfExellentRate",0,NewJewels_DIR);
	this->ExNewJewel.JewelOfDivinityRate = GetPrivateProfileInt("Common","JewelOfDivinityRate",0,NewJewels_DIR);
	this->ExNewJewel.JewelOfLuckRate = GetPrivateProfileInt("Common","JewelOfLuckRate",0,NewJewels_DIR);

	//---------------------------------
	//			OffTrade
	//---------------------------------

	this->OffTrade.OffTradeZen = GetPrivateProfileInt("Common","OffTradeZen",0,OffTrade_DIR);
	this->OffTrade.OffTradeExPoint = GetPrivateProfileInt("Common","OffTradeExPoint",0,OffTrade_DIR);
	this->OffTrade.OffTradeWcoin = GetPrivateProfileInt("Common","OffTradeWcoin",0,OffTrade_DIR);
	this->OffTrade.OffTradeCredit = GetPrivateProfileInt("Common","OffTradeCredit",1,OffTrade_DIR);

	this->OffTrade.OffTradeChaos = GetPrivateProfileInt("Common","OffTradeChaos",1,OffTrade_DIR);
	this->OffTrade.OffTradeBless = GetPrivateProfileInt("Common","OffTradeBless",1,OffTrade_DIR);
	this->OffTrade.OffTradeSoul = GetPrivateProfileInt("Common","OffTradeSoul",1,OffTrade_DIR);
	this->OffTrade.OffTradeLife = GetPrivateProfileInt("Common","OffTradeLife",1,OffTrade_DIR);


	
}