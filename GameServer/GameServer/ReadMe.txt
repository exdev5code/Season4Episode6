 __  __ ____   ____   _____                    
|  \/  / ___| / ___| |_   _|__  __ _ _ __ ___  
| |\/| \___ \| |       | |/ _ \/ _` | '_ ` _ \ 
| |  | |___) | |___    | |  __/ (_| | | | | | |
|_|  |_|____/ \____|   |_|\___|\__,_|_| |_| |_|

Secret Project Development

Project Name:	- Ashes
Info:			- A Clean and Full GameServer 90 Source
GameServer:		- 1.00.90 JPN
Members:		- HermeX / Crazzy
Special Thanks	- SirMaster / Prody / Mr.Marin / Willerson

Dev Info/Status:

###May 2011###
Starting Project

I think webzen uses c++ with service pack 3, 4 or 5 xD

Intereting Infos:

formulas with int and float -> variable int = (int)( (float)(value1) operation (float)(value2) ); or reversed :)

//004A5950 is new eventitemlist :)

related to pcbang connection :)
CMP DWORD PTR DS:[5D4A38C],0

//_asm jmp for float comparisons
TEST AH, 1	JE	<
TEST AH, 40	JNZ	!=
TEST AH, 41	JNZ	>
TEST AH, 41	JE	<=
TEST AH, 40	JE	==

//_asm jmp for DWORD comparisons
JA <=
JNB <
JBE >
JB >=

::
::GS-N&CS-CS 1.00.90 Decompilation Project by HermeX&Crazzy (C) 2011
:: Project started - 5.05.2011

//ALL DATA
OBJECTSTRUCT 						:: 100% ::

COMPARING CPP's :
MonsterHerd.cpp						:: 100% ::
KalimaGate.cpp						:: 100% ::
gObjMonster.cpp						:: 100% ::		
MonsterAttr.cpp						:: 100% :: 
MonsterItemMng.cpp					:: 100% ::
MonsterSetBase.cpp					:: 100% ::
DbSave.cpp							:: 100% ::
DBSockMng.cpp						:: 100% ::
DSProtocol.cpp						:: 100% ::
SProtocol.cpp						:: 100% ::
protocol.cpp						:: 100% ::
EDSProtocol.cpp						:: 100% ::
MultiAttackHackCheck.cpp			:: 100% :: - have news checks
NSerialCheck.cpp					:: 100% ::
PacketCheckSum.cpp					:: 100% ::
HackToolPacket.cpp					:: 100% ::
TDurMagicKeyChecker.cpp				:: 100% ::
ChinaHackUserKick.cpp				:: 100% :: - non-coded
SendHackLog.cpp						:: 100% ::
DevilSquare.cpp						:: 100% ::
DevilSquareGround.cpp				:: 100% ::
BattleGround.cpp					:: 100% ::
BattleSoccer.cpp					:: 100% ::
BattleSoccerManager.cpp				:: 100% :: 
DragonEvent.cpp						:: 100% :: - void CDragonEvent::Start() - changed
AttackEvent.cpp						:: 100% ::
EledoradoEvent.cpp					:: 100% ::
RingAttackEvent.cpp					:: 100% ::
WTEventItemList.cpp					:: 100% :: - non code
CastleDeepEvent.cpp					:: 100% :: - same as 77
PCBangPointSystem.cpp				:: 100% ::
GambleSystem.cpp					:: 100% ::
XMasAttackEventData.cpp				:: 100% :: - can't fix position for virtual functions
Event.cpp							:: 100% :: - need correct packets vars names cuz is all Unk_X
EventManagement.cpp					:: 100% ::
ItemBag.cpp							:: 100% ::
ItemBagEx.cpp						:: 100% ::
ProbabilityItemBag.cpp				:: 100% ::
XMasAttackEvent.cpp					:: 100% ::
MagicDamage.cpp						:: 100% ::
MagicInf.cpp						:: 100% ::
SkillAdditionInfo.cpp				:: 100% ::
SkillDelay.cpp						:: 100% ::
SkillHitBox.cpp						:: 100% ::
QuestInfo.cpp						:: 100% :: - void CQuestInfo::QuestSuccessCommand - need fix registers only >.< so lazy to do
QuestUtil.cpp						:: 100% :: - same
wsGameServer.cpp					:: 100% :: - same
WzMultiCastSock.cpp					:: 100% :: - same
giocp.cpp							:: 100% ::
\common\MyWinsockBase.cpp			:: 100% :: - same
wsJoinServerCli.cpp					:: 100% :: - same
WzQueue.cpp							:: 100% :: - same
WzUdp.cpp							:: 100% :: - same
MapClass.cpp						:: 100% :: - new func and some addons for socketsystem
MapItem.cpp							:: 100% :: - some addons for socketsystem
AcceptIp.cpp						:: 100% :: - same	
CLoginCount.cpp						:: 100% :: - same
ClosePlayer.cpp						:: 100% :: - same
ConMember.cpp						:: 100% :: - same
IpCache.cpp							:: 100% :: - same
DirPath.cpp							:: 100% :: - same
logproc.cpp							:: 100% :: - same
LogToFile.cpp						:: 100% :: - same
MoveCheck.cpp						:: 100% :: - same
\common\winutil.cpp					:: 100% :: - same
WhisperCash.cpp						:: 100% :: - same
zzzmathlib.cpp						:: 100% :: - changed
\common\WZScriptEncode.cpp			:: 100% :: - same
CWhatsUpDummyServer.cpp				:: 100% :: - same
TNotice.cpp							:: 100% :: - same
TStatistics.cpp						:: 100% :: - same
CallStackTrace.cpp					:: 100% :: - same
TServerAlertManager.cpp				:: 100% :: - macro
TServerInfoDisplayer.cpp			:: 100% :: - same
MiniDump.cpp						:: 100% :: - same
PartyClass.cpp						:: 100% :: - same
GuildClass.cpp						:: 100% :: - same
ViewportGuild.cpp					:: 100% :: - same
ObjAttack.cpp						:: 100% ::
ObjBaseAttack.cpp					:: 100% ::
ObjUseSkill.cpp						:: 100% ::
\common\classdef.cpp				:: 100% :: - same
StatMng.cpp							:: 100% :: - changed formuls
ComboAttack.cpp						:: 100% ::
ObjCalCharacter.cpp					:: 100% ::					
DarkSpirit.cpp						:: 100% ::
TUnion.cpp							:: 100% :: - same
TUnionInfo.cpp						:: 100% :: - same
MasterLevelSystem.cpp				:: 100% :: - few fixes
MasterSkillSystem.cpp				:: 100% ::
user.cpp							:: 100% ::
SocketData.cpp						:: 100% ::
SocketOption.cpp					:: 100% :: 
SocketSphere.cpp					:: 100% ::
ItemAddOption.cpp					:: 100% :: - one new func
JewelMixSystem.cpp					:: 100% :: - dupe fix
\common\SetItemOption.cpp			:: 100% :: - same
\common\zzzitem.cpp					:: 100% ::
Shop.cpp							:: 100% ::
CCastleEventItemList.cpp			:: 100% :: - macro
GMMng.cpp							:: 100% ::
MoveCommand.cpp						:: 100% :: - new checks
SetItemMacro.cpp					:: 100% ::
GameMain.cpp						:: 100% ::
GameServer.cpp						:: 100% ::
Gate.cpp							:: 100% ::
BloodCastle.cpp						:: 100% ::
ChaosCastle.cpp						:: 100% ::
ChaosCastleSetItemDrop.cpp			:: 100% :: - macro
CannonTower.cpp						:: 100% :: 
CastleCrown.cpp						:: 100% ::
CastleCrownSwitch.cpp				:: 100% ::
Guardian.cpp						:: 100% ::
GuardianStatue.cpp					:: 100% ::
LifeStone.cpp						:: 100% :: - fix added on 4.5
Mercenary.cpp						:: 100% ::
Weapon.cpp							:: 100% :: - same as 77
CastleSiege.cpp						:: 100% ::
CastleSiegeSync.cpp					:: 100% ::
MapServerManager.cpp				:: 100% ::
NpcTalk.cpp							:: 100% :: 
TMonsterSkillElement.cpp			:: 100% ::
TMonsterSkillElementInfo.cpp		:: 100% ::
TMonsterSkillManager.cpp			:: 100% ::
TMonsterSkillUnit.cpp				:: 100% :: - completed but TMonsterSkillElement::GetElementName() i cant fix position for this func :(
TMonsterAI.cpp						:: 100% :: 
TMonsterAIAgro.cpp					:: 100% :: - completed but cant fix position for .h extra class
TMonsterAIAutomata.cpp				:: 100% ::
TMonsterAIElement.cpp				:: 100% ::
TMonsterAIGroup.cpp					:: 100% ::
TMonsterAIGroupMember.cpp			:: 100% ::
TMonsterAIMovePath.cpp				:: 100% :: - completed but cant fix position for .h extra class
TMonsterAIRule.cpp					:: 100% ::
TMonsterAIRuleInfo.cpp				:: 100% ::
TMonsterAIUnit.cpp					:: 100% ::
TMonsterAIUtil.cpp					:: 100% ::
CrywolfAltar.cpp					:: 100% ::
CrywolfStatue.cpp					:: 100% ::
CrywolfDarkElf.cpp					:: 100% ::
CrywolfMonster.cpp					:: 100% ::
CrywolfTanker.cpp					:: 100% ::
Crywolf.cpp							:: 100% :: - completed but cant fix position for .h extra class
CrywolfStateTimeInfo.cpp			:: 100% ::
CrywolfSync.cpp						:: 100% ::
CrywolfUtil.cpp						:: 100% ::
ItemSystemFor380.cpp				:: 100% :: - cant fix position for DebugLog func
JewelOfHarmonySystem.cpp			:: 100% ::				
TRandomPoolMgr.cpp					:: 100% ::
KanturuMaya.cpp						:: 100% ::
KanturuMonsterMng.cpp				:: 100% ::
KanturuNightmare.cpp				:: 100% ::
KanturuBattleOfMaya.cpp				:: 100% ::
KanturuBattleOfNightmare.cpp		:: 100% ::
KanturuBattleStanby.cpp				:: 100% ::
KanturuTowerOfRefinement.cpp		:: 100% ::
KanturuBattleUserMng.cpp			:: 100% ::
KanturuEntranceNPC.cpp				:: 100% ::
Kanturu.cpp							:: 100% :: - m_iKanturuBattleCounter and int m_iKanturuBattleDate may be deleted, and func void SetKanturuTimeAttackEventInfo() has deleted
KanturuStateInfo.cpp				:: 100% ::
KanturuUtil.cpp						:: 100% :: - SendDataKanturuTimeAttackEvent - deleted from 4.5
IllusionTempleEvent.cpp				:: 100% ::
IllusionTempleProcess.cpp			:: 100% ::
MixSystem.cpp						:: 100% ::
CashShop.cpp						:: 100% ::
wsShopServerCli.cpp					:: 100% ::
CashItemPeriodSystem.cpp			:: 100% ::
CashLotterySystem.cpp				:: 100% ::
ViewportSkillState.cpp				:: 100% :: - webzen remade Add and Clear. Now is "Prev" and "Next" BuffLastEffect for CalCharacter and one master function to Clear all :)
BuffManager.cpp						:: 100% ::
BuffEffect.cpp						:: 100% ::
RaklionSelupan.cpp					:: 100% ::
RaklionBattleOfSelupan.cpp			:: 100% ::
RaklionBattleUserMng.cpp			:: 100% ::
Raklion.cpp							:: 100% ::
RaklionUtil.cpp						:: 100% ::
ChaosCard.cpp						:: 100% ::
GameEvent.cpp						:: 100% ::
GameServerAuth.cpp					:: 100% ::
LargeRand.cpp						:: 100% ::
MultiCheckSum.cpp					:: 100% ::
TSync.cpp							:: 100% ::
\common\WzMemScript.cpp				:: 100% ::