//GS-N 1.00.90 - 0xXXXXXXXX  - complete
//GS-CS 1.00.90 - 0xXXXXXXXX  - complete
#include "stdafx.h"
#include "user.h"
#include "NpcTalk.h"
#include "gObjMonster.h"
#include "..\common\winutil.h"
#include "protocol.h"
#include "GameMain.h"
#include "BloodCastle.h"
#include "gObjMonster.h"
#include "DevilSquare.h"
#include "QuestInfo.h"
#include "CastleSiegeSync.h"
#include "KanturuEntranceNPC.h"
#include "JewelOfHarmonySystem.h"
#include "Gamemain.h"
#include "Event.h"
#include "IllusionTempleEvent.h"
#include "BuffManager.h"
#include "CashShop.h"
#include "DuelManager.h"
#include "GoldenArcher.h"
#include "ExQuestSystem.h"
#include "TvTEvent.h"
#include "GrandHeroSystem.h"
#include "Reset.h"

#ifdef _EVANGELION_EVENT_
#include "SearchEvent.h"
#endif
#include "BMQuest.h"
#include "NPCTeleport.h"

BOOL NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	int npcnum = lpNpc->Class;

	if ( npcnum < 0 )
	{
		return FALSE;
	}

	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	if ( npcnum == 229 )
	{
		gQeustNpcTeleport.TalkRefAdd();
		lpObj->TargetShopNumber = npcnum;
	}

	if ( NpcQuestCheck(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

#ifdef _Eugene_
	gReset.NPCReset(lpNpc,lpObj);
#endif

	ExQuestSystem.NPCClick(lpNpc,lpObj);

#ifdef TVTEVENT
	TvT.NPCClick(lpNpc,lpObj);	//TvTEvent
#endif
#if(BM_QUEST_SYSTEM_)
	BMQuest.NPCClick(lpObj->m_Index,lpNpc->m_Index);
#endif
#if(_GRAND_HERO_SYSTEM_)
	if(GrandHero.NPCTeleport(lpNpc,lpObj) == TRUE)
	{
		return TRUE;
	}
#endif

#ifdef _EVANGELION_EVENT_
	SearchEvent.NPCClick(lpObj->m_Index,lpNpc->m_Index);
#endif

#if(CUSTOM_NPC_TELEPORT==TRUE)
	if(g_NPCTeleport.Dialog(lpObj->m_Index,lpNpc->m_Index))
	{
		return TRUE;
	}
#endif

	switch ( npcnum )
	{
		case 254:
			if ( NpcFasi ( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;

		case 241:
			if ( NpcGuildMasterTalk( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		
		case 239:
			if ( NpcBattleAnnouncer( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;

		case 249:
			if ( NpcRolensiaGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 238:
			if ( NpcChaosGoblelin( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 237:
			if ( NpcRusipher( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 253:
			if ( NpcPosionGirl( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;

		case 245:
			if ( NpcDeviasWizard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 247:
			if ( NpcDeviasGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 240:
			if ( NpcWarehouse( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 226:
			if ( NpcDarkSpiritTrainer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 242:
			if ( NpcNoriaRara( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 244:
			if ( NpcDeviasMadam( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;

		case 236:
			if ( NpcEventChipNPC( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 234:
			if ( NpcServerDivision( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 232:
			if ( NpcAngelKing( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 233:
			if ( NpcAngelMessanger( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 255:
			if ( NpcRolensiaMadam( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 250:
			if ( NpcRoadMerchant( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 246:
			if ( NpcDeviasWeapon( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 251:
			if ( NpcRorensiaSmith( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 243:
			if ( NpcNoriJangIn( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 256:
			if ( NpcJewelMixDealer( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 221:
			if ( NpcSiegeMachine_Attack( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 222:
			if ( NpcSiegeMachine_Defense( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 223:
			if ( NpcElderCircle( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 224:
			if ( NpcCastleGuard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 219:
			if ( NpcCastleGateLever( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 216:
			if ( NpcCastleCrown( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 217:
		case 218:
			if ( NpcCastleSwitch( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 220:
			if( NpcCastleHuntZoneGuard(lpNpc,lpObj) == TRUE)
			{
				return TRUE;
			}
			break;
		case 257:
			if ( NpcShadowPhantom( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 205:
			if ( NpcCrywolfAltar( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		case 206:
			if ( NpcCrywolfAltar( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		case 207:
			if ( NpcCrywolfAltar( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		case 208:
			if ( NpcCrywolfAltar( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		case 209:
			if ( NpcCrywolfAltar( lpNpc, lpObj ) == TRUE ) //ok
			{
				return TRUE;
			}
			break;
		case 259:
			if ( NpcReira ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;

		case 368:
		case 369:
		case 370:
			if ( g_kJewelOfHarmonySystem.NpcJewelOfHarmony( lpNpc, lpObj ) == TRUE )

			{
				return TRUE;
			}
			break;
		case 375:
			if ( NpcChaosCardMaster( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 367:
			if ( NpcMainatenceMachine ( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 376:
			if ( NpcPamelaSupplier( lpNpc, lpObj ) == TRUE ) //376 1 "Pamela the Supplier"
			{
				return TRUE;
			}
			break;
		case 377:
			if ( NpcAngelaSupplier( lpNpc, lpObj ) == TRUE ) //377 1 "Angela the Supplier"
			{
				return TRUE;
			}
			break;
		case 379:
			if ( NpcFirecrackerMerchant( lpNpc, lpObj ) == TRUE ) //379 1 "Natasha the Firecracker Merchant"
			{
				return TRUE;
			}
			break;
		case 385:
			if ( NpcIllusionMirage( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 380:
			if ( NpcIllusionStatue( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 383:
			if ( NpcIllusionYellowPedestal( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 384:
			if ( NpcIllusionBluePedestal( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 415:
			if ( NpcSilviaSupplier( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 416:
			if ( NpcRheaMerchant( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 417:
			if ( NpcMarceWizard( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 450:
			if ( NpcCherryBlossomSpirit( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 452:
			if ( NpcSeedMaster( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 453:
			if ( NpcSeedResearcher( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 478:
			if ( NpcLuckyCoinExchanger( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 465:
			if ( NpcXMasSantaClaus( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 467:
			if ( NpcSnowMan( lpNpc, lpObj ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 468:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 94 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 469:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj , 95) == TRUE )
			{
				return TRUE;
			}
			break;
		case 470:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 0 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 471:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 1 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 472:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 92 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 473:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 93 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 474:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj, 96 ) == TRUE )
			{
				return TRUE;
			}
			break;
		case 475:
			if ( NpcLittleSantaBuffer( lpNpc, lpObj , 97) == TRUE )
			{
				return TRUE;
			}
			break;
		case 479:
			if ( NpcTitusGatekeeper( lpNpc, lpObj ) == true )
			{
				return true;
			}
			break;
		case 492:
			if( NpcMoss( lpNpc,lpObj )  == true )
			{
				return true;
			}
			break;
	}
	return FALSE;
}

BOOL NpcMainatenceMachine(LPOBJ lpNpc, LPOBJ lpObj)
{
	g_KanturuEntranceNPC.NotifyEntranceInfo(lpObj->m_Index);
	return TRUE;
}

BOOL NpcReira(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcBattleAnnouncer(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcFasi(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
		if ( gDevilSquareEvent != FALSE )
		{
			GCServerCmd(lpObj->m_Index, 1, 6, 0);
		}
	}

	BOOL bPlayerKiller = FALSE; //Season 2.5 add-on
	
	if(lpObj->PartyNumber >= 0) //Season 2.5 add-on
	{
		if(gParty.GetPkLevel(lpObj->PartyNumber) > 4)
		{
			bPlayerKiller = TRUE;
		}
	}
	else if(lpObj->m_PK_Level > 4)
	{
		bPlayerKiller = TRUE;
	}

	if ( bPlayerKiller == TRUE )
	{
		int hour = 0;
		int min = 0;

		if ( lpNpc->TargetNumber != lpObj->m_Index )
		{
			if ( gObjGetPkTime(lpObj, hour, min) == TRUE )
			{
				char szTemp[100];

				wsprintf(szTemp, lMsg.Get(MSGGET(4, 79)), hour, min);

				ChatTargetSend(lpNpc, szTemp, lpObj->m_Index);

				lpNpc->TargetNumber = lpObj->m_Index;

				if(gPkLimitFree == 0)
				{
					return TRUE;
				}
			}
		}
		else if ( gPkLimitFree == FALSE )
		{
			int numbertext = rand() % 3;

			switch ( numbertext )
			{
				case 0:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 98)), lpObj->m_Index);
					break;

				case 1:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 99)), lpObj->m_Index);
					break;

				case 2:
					ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 100)), lpObj->m_Index);
					break;
			}

			lpNpc->TargetNumber = 0;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL NpcGuildMasterTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gGuildCreate == FALSE )
	{
		ChatTargetSend(lpNpc, "서버분할 기간에는 길드를 생성할수가 없습니다", lpObj->m_Index);
		return TRUE;
	}

	if ( lpObj->GuildNumber > 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 116)), lpObj->m_Index);
		return TRUE;
	}

	int capacity = gObjGuildMasterCapacityTest(lpObj);

	if ( capacity == 0 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 117)), lpObj->m_Index);
	}
	else if ( capacity == 2 )
	{
		ChatTargetSend(lpNpc, lMsg.Get(MSGGET(4, 118)), lpObj->m_Index);
	}
	else
	{
		GCGuildMasterQuestionSend(lpObj->m_Index);
	}

	return TRUE;
}

BOOL NpcRolensiaGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 0, 0);
	}

	return TRUE;
}

BOOL NpcChaosGoblelin(LPOBJ lpNpc, LPOBJ lpObj)
{
	gUserFindDevilSquareKeyEyes(lpObj->m_Index);

	return FALSE;
}

BOOL NpcChaosCardMaster(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_bUseLotteryEvent == FALSE )
	{
		return FALSE;
	}
	
	if ( lpObj->m_bPShopOpen == 1 )//Season 4.5 addon
	{
		GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
		
		return FALSE;
	}
	if ( bCanChaosBox == TRUE )
	{
		if ( lpObj->m_IfState.use > 0 )
		{
			return FALSE;
		}

		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed", lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x15;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 7;

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}

BOOL NpcRusipher(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gDevilSquareEvent == FALSE )
	{
		return TRUE;
	}

	int aIndex = lpObj->m_Index;

	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	if ( gUserFindDevilSquareInvitation(aIndex) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 2 ,0);
	}
	else if ( g_DevilSquare.GetState() == 1 )
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x04;

		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 12;
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 3, 0);
	}

	return TRUE;
}

BOOL NpcPosionGirl(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcDeviasWizard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcDeviasGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	return TRUE;
}

BOOL NpcDeviasWareHousemen(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcWarehouse(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcNoriaRara(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 2, 0);
	}

	return FALSE;
}

BOOL NpcDeviasMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gLanguage != 0 )
	{
	
	}
	else if ( gEnableEventNPCTalk != FALSE )
	{
		GCServerCmd(lpObj->m_Index, 4, 1, 0);
	}

	return FALSE;
}

struct PMSG_REQ_VIEW_EC_MN
{
	PBMSG_HEAD h;	// C1:01
	int iINDEX;	// 4
	char szUID[11];	// 8
};

BOOL NpcEventChipNPC(LPOBJ lpNpc, LPOBJ lpObj)
{
	GoldenArcher.ClickArcher(lpObj->m_Index);
	return true;
	/*
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}
	
	if ( lpNpc->MapNumber == 0 )
	{
		PMSG_REQ_VIEW_EC_MN pMsgTha;

		PHeadSetB((LPBYTE)&pMsgTha, 0x01, sizeof(pMsgTha));
		pMsgTha.iINDEX = lpObj->m_Index;
		strcpy(pMsgTha.szUID, lpObj->AccountID);
		pEventObj = lpNpc;

		DataSendEventChip((char*)&pMsgTha, sizeof(pMsgTha));
		
		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	if ( lpNpc->MapNumber == 2 )
	{
		PMSG_EVENTCHIPINFO Result;

		PHeadSetB((LPBYTE)&Result, 0x94, sizeof(Result));
		Result.Type = 2;
		
		DataSend(lpObj->m_Index, (LPBYTE)&Result, Result.h.size);

		lpObj->m_IfState.type = 9;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;

		return TRUE;
	}

	return FALSE;
	*/
}

BOOL NpcRorensiaSmith(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcNoriJangIn(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcQuestCheck(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( g_QuestInfo.NpcTalk(lpNpc, lpObj) != FALSE )
	{
		return TRUE;
	}

	return FALSE;
}

BOOL NpcServerDivision(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gEnableServerDivision == FALSE )
	{
		return TRUE;
	}

	if ( lpObj->lpGuild != NULL )
	{
		GCServerCmd(lpObj->m_Index, 6, 0, 0);
		return TRUE;
	}

	lpObj->m_IfState.type = 11;
	lpObj->m_IfState.state = 0;
	lpObj->m_IfState.use = 1;

	return FALSE;
}

BOOL NpcRoadMerchant(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcAngelKing(LPOBJ lpNpc, LPOBJ lpObj)
{
	BOOL iITEM_LEVEL = 0; //loc1
#if(BC_2_MIN_END==1)
	LogAddC(2,"BC_2_MIN_END: %d",g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iBC_REMAIN_MSEC);
#endif
	if ( CHECK_LIMIT(lpObj->m_cBloodCastleIndex, MAX_BLOOD_CASTLE_LEVEL) == FALSE )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

	LogAddTD("[Blood Castle] (%d) [%s][%s] Talk to Angel King",	lpObj->m_cBloodCastleIndex+1, lpObj->AccountID, lpObj->Name);

	if ( g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_bBC_REWARDED != false )
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if ( g_BloodCastle.GetCurrentState(lpObj->m_cBloodCastleIndex) != 2 || g_BloodCastle.CheckPlayStart(lpObj->m_cBloodCastleIndex) == false)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
		return FALSE;
	}

#if(BC_2_MIN_END==1)
	g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iBC_REMAIN_MSEC;
#endif
	

	if ( lpObj->m_bBloodCastleComplete == true)
	{
		GCServerCmd(lpObj->m_Index, 1, 0x2E, 0);
		return FALSE;
	}

	if( (iITEM_LEVEL = g_BloodCastle.CheckQuestItem(lpObj->m_Index)<0?0:iITEM_LEVEL = g_BloodCastle.CheckQuestItem(lpObj->m_Index)>2?0:1) ) //perfect
	{
		if ( lpNpc->m_cBloodCastleIndex != lpObj->m_cBloodCastleIndex )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		if ( g_BloodCastle.CheckUserBridgeMember(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == false )
		{
			GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
			return FALSE;
		}

		g_BloodCastle.SetUserState(lpObj->m_Index, 2);
		
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Party = lpObj->PartyNumber;
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_iExtraEXP_Win_Quest_Index = lpObj->m_Index;
		
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName, lpObj->Name, 10);
		memcpy(g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID, lpObj->AccountID, 10);
		
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName[10] = 0;
		g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID[10] = 0;
		
		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Castle Door [%s][%s]", lpObj->m_cBloodCastleIndex+1, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_CharName);

		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Destroy Saint Status [%s][%s]", lpObj->m_cBloodCastleIndex+1, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Door_AccountID, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szKill_Status_CharName);

		LogAddTD("[Blood Castle] (%d) Blood Castle Quest Succeed Result -> Win Quest [%s][%s]", lpObj->m_cBloodCastleIndex+1, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_AccountID, 
			g_BloodCastle.m_BridgeData[lpObj->m_cBloodCastleIndex].m_szWin_Quest_CharName);

		if ( g_BloodCastle.SetBridgeWinner(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest", 
					g_BloodCastle.GetBridgeIndex(lpNpc->MapNumber)+1, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register", 
					g_BloodCastle.GetBridgeIndex(lpNpc->MapNumber)+1, lpObj->AccountID, lpObj->Name);
			}
		}
		else
		{
			LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Winner Already Exist !!", 
				g_BloodCastle.GetBridgeIndex(lpNpc->MapNumber)+1, lpObj->AccountID, lpObj->Name);
			return FALSE;
		}

		g_BloodCastle.SearchUserDeleteQuestItem(lpObj->m_Index);
	}
	else
	{
		if ( g_BloodCastle.CheckUserWinnerParty(lpObj->m_cBloodCastleIndex, lpObj->m_Index) == TRUE )
		{
			lpObj->m_bBloodCastleComplete = true;

			if ( g_BloodCastle.CheckPartyExist(lpObj->m_Index) == FALSE )
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest", 
					g_BloodCastle.GetBridgeIndex(lpNpc->MapNumber)+1, lpObj->AccountID, lpObj->Name);
			}
			else
			{
				GCServerCmd(lpObj->m_Index, 1, 0x17, 0);
				LogAddTD("[Blood Castle] (%d) (Account:%s, Name:%s) Succeed Blood Castle Quest - More Party to register", 
					g_BloodCastle.GetBridgeIndex(lpNpc->MapNumber)+1, lpObj->AccountID, lpObj->Name);
			}

			return FALSE;
		}

		GCServerCmd(lpObj->m_Index, 1, 0x18, 0);
	}
	
	return FALSE;
}

BOOL NpcAngelMessanger(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	int iIndex = lpObj->m_Index;

	if ( gObj[iIndex].m_PK_Level >= 4 )
	{
		GCServerCmd(iIndex, 0x38, 0, 0);
		return TRUE;
	}

	int iITEM_LEVEL = 0;

	iITEM_LEVEL = g_BloodCastle.CheckEnterItem(lpObj->m_Index);

	if ( iITEM_LEVEL != 0 )
	{
		if ( iITEM_LEVEL != 10 && g_BloodCastle.CheckEnterLevel(lpObj->m_Index, iITEM_LEVEL-1) )
		{
			if ( g_BloodCastle.CheckEnterFreeTicket(lpObj->m_Index) == true )
			{
				iITEM_LEVEL = 10;
			}
		}

		if ( iITEM_LEVEL == 10 )
		{
			for (int i=0;i<MAX_CLOACK_LEVEL;i++)
			{
				if ( g_BloodCastle.CheckEnterLevel(lpObj->m_Index, i) == FALSE )
				{
					iITEM_LEVEL = i;
				}
			}
		}

		if ( g_BloodCastle.GetCurrentState(iITEM_LEVEL-1) == BC_STATE_CLOSED && g_BloodCastle.CheckCanEnter(iITEM_LEVEL-1) != false )
		{
			PMSG_TALKRESULT pMsg;

			pMsg.h.c = 0xC3;
			pMsg.h.headcode = 0x30;
			pMsg.h.size = sizeof(pMsg);
			pMsg.result = 0x06;

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			lpObj->m_IfState.use = 1;
			lpObj->m_IfState.type = 12;
		}
		else
		{
			GCServerCmd(lpObj->m_Index, 1, 0x14, 0);
		}
	}
	else
	{
		GCServerCmd(lpObj->m_Index, 1, 0x15, 0);
	}

	return FALSE;
}

BOOL NpcRolensiaMadam(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcDeviasWeapon(LPOBJ lpNpc, LPOBJ lpObj)
{
	return FALSE;
}

BOOL NpcDarkSpiritTrainer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( bCanChaosBox == TRUE )
	{
		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		
		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed", lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4, 194)), lpObj->m_Index, 1);
			return TRUE;
		}

		lpObj->m_IfState.type = 13;
		lpObj->m_IfState.state = 0;
		lpObj->m_IfState.use = 1;
		
		pMsg.result = 0x07;
		lpObj->bIsChaosMixCompleted = false;
		pMsg.level1 = gDQChaosSuccessRateLevel1;
		pMsg.level2 = gDQChaosSuccessRateLevel2;
		pMsg.level3 = gDQChaosSuccessRateLevel3;
		pMsg.level4 = gDQChaosSuccessRateLevel4;
		pMsg.level5 = gDQChaosSuccessRateLevel5;
		pMsg.level6 = gDQChaosSuccessRateLevel6;
		pMsg.level7 = gDQChaosSuccessRateLevel7;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		GCAnsCsMapSvrTaxInfo(lpObj->m_Index, 1, g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index));
		gObjInventoryTrans(lpObj->m_Index);

		LogAddTD("[%s][%s] Open Chaos Box", lpObj->AccountID, lpObj->Name);
		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}

BOOL NpcJewelMixDealer(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( bCanChaosBox == TRUE )
	{
		if ( (lpObj->m_IfState.use) > 0 )
		{
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x09;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 20; //season4 changed

		LogAddTD("[JewelMix] [%s][%s] Jewel Mix Dealer Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);

	}

	return TRUE;
}

struct PMSG_ANS_USE_WEAPON_INTERFACE
{
	PBMSG_HEAD2 h;	// C1:B7:00
	BYTE btResult;	// 4
	BYTE btWeaponType;	// 5
	BYTE btObjIndexH;	// 6
	BYTE btObjIndexL;	// 7
};

BOOL NpcSiegeMachine_Attack(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 1;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 15;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}

BOOL NpcSiegeMachine_Defense(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_USE_WEAPON_INTERFACE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult, 0xB7, 0x00, sizeof(pResult));

	pResult.btResult = 0;
	pResult.btWeaponType = 2;
	pResult.btObjIndexH = SET_NUMBERH(lpNpc->m_Index);
	pResult.btObjIndexL = SET_NUMBERL(lpNpc->m_Index);

	if ( gObjIsConnectedGP(lpNpc->m_iWeaponUser) == FALSE )
	{
		lpNpc->m_iWeaponUser = 0;
		lpNpc->m_btWeaponState = 1;
	}

	lpNpc->m_btWeaponState = 1;


	if ( lpNpc->m_btWeaponState == 1 )
	{
		pResult.btResult = 1;
		lpNpc->m_btWeaponState = 2;
		lpNpc->m_iWeaponUser = lpObj->m_Index;

		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 16;
	}
	else
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
	}

	return TRUE;
}

BOOL NpcElderCircle(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 85))), lpObj->m_Index);
		return TRUE;
	}

	if(strcmp(lpObj->GuildName, "") == 0 )
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 86))), lpObj->m_Index);
		return TRUE;
	}

	if(!g_CastleSiege.CheckGuildOwnCastle(lpObj->GuildName) || (lpObj->GuildStatus != G_MASTER && lpObj->GuildStatus != G_SUB_MASTER))
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 86))), lpObj->m_Index);
		return TRUE;
	}

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0C;

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;

	pMsg.level1 = 0;
	pMsg.level2 = 0;
	pMsg.level3 = 0;
	pMsg.level4 = 0;
	pMsg.level5 = 0;
	pMsg.level6 = 0;
	pMsg.level7 = 0;//Season 4.5 fix

	if( bCanChaosBox == TRUE)
	{
		lpObj->m_IfState.type = 7;

		lpObj->bIsChaosMixCompleted = false;
		lpObj->m_bIsCastleNPCUpgradeCompleted = false; 

		pMsg.level1 = 1;

		GCAnsCsMapSvrTaxInfo(lpObj->m_Index, 1, g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index));
		gObjInventoryTrans(lpObj->m_Index);

		LogAddTD("[%s][%s] Open Chaos Box", lpObj->AccountID, lpObj->Name);
		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	return TRUE;
}

BOOL NpcCastleGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		ChatTargetSend(lpNpc,(lMsg.Get(MSGGET(6, 87))), lpObj->m_Index);
		return TRUE;
	}

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = sizeof(pMsg);
	pMsg.result = 0x0D;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;


	return TRUE;
}

BOOL NpcCastleGateLever(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use) > 0 )
	{
		return TRUE;
	}

	BOOL bControlEnable = FALSE;
	BYTE btResult = 0;
	int iGateIndex = -1;

	if(g_CastleSiege.GetCastleState() == CASTLESIEGE_STATE_STARTSIEGE)
	{
		if(lpObj->m_btCsJoinSide != TRUE)
		{
			btResult = 4;
			bControlEnable = FALSE;
		}
		else
		{
			bControlEnable = TRUE;
		}
	}
	else
	{
		if(g_CastleSiege.CheckCastleOwnerMember(lpObj->m_Index) == FALSE && g_CastleSiege.CheckCastleOwnerUnionMember(lpObj->m_Index) == FALSE) //Fixed
		{
			btResult = 4;
			bControlEnable = FALSE;
		}
		else
		{
			bControlEnable = TRUE;
		}
	}

	if(bControlEnable != FALSE)
	{
		if(g_CastleSiege.CheckLeverAlive(lpNpc->m_Index) == TRUE)
		{
			if(g_CastleSiege.CheckCsGateAlive(lpNpc->m_iCsGateLeverLinkIndex) == TRUE)
			{
				btResult = 1;
				iGateIndex = lpNpc->m_iCsGateLeverLinkIndex;
			}
			else
			{
				btResult = 2;
			}
		}
		else
		{
			btResult = 3;
		}

	}

	GCAnsCsGateState(lpObj->m_Index,btResult,iGateIndex);

	if(btResult != 1)
	{
		return TRUE;
	}

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 12;

	return TRUE;
}

BOOL NpcCastleCrown(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() != CASTLESIEGE_STATE_STARTSIEGE)
	{
		return TRUE;
	}
	
	if(lpObj->m_btCsJoinSide < 2 || lpObj->m_bCsGuildInvolved == FALSE )
	{
		return TRUE;
	}

	if(g_CastleSiege.CheckUnionGuildMaster(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if( (abs(lpObj->Y - lpNpc->Y)) > 3 || (abs(lpObj->X - lpNpc->X)) > 3)
	{
		return TRUE;
	}

	if(g_CastleSiege.GetRegCrownAvailable() == FALSE )
	{
		return TRUE;
	}

	int iUserIndex = g_CastleSiege.GetCrownUserIndex();

	if(gObjIsConnected(iUserIndex) == FALSE )
	{
		int iSwitchIndex1 = g_CastleSiege.GetCrownSwitchUserIndex(217);
		int iSwitchIndex2 = g_CastleSiege.GetCrownSwitchUserIndex(218);

		if(gObjIsConnected(iSwitchIndex1) == FALSE || gObjIsConnected(iSwitchIndex2) == FALSE )
		{
			GCAnsCsAccessCrownState(lpObj->m_Index,4);
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName);
			return TRUE;
		}

		if(lpObj->m_btCsJoinSide != gObj[iSwitchIndex1].m_btCsJoinSide || lpObj->m_btCsJoinSide != gObj[iSwitchIndex2].m_btCsJoinSide)
		{
			GCAnsCsAccessCrownState(lpObj->m_Index,4);
			LogAddTD("[CastleSiege] [%s][%s] Failed to Register Castle Crown (GUILD:%s) (S1:%s/%s)(S2:%s/%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName,gObj[iSwitchIndex1].Name,gObj[iSwitchIndex1].GuildName,gObj[iSwitchIndex2].Name,gObj[iSwitchIndex2].GuildName);
			return TRUE;
		}
		else
		{
			GCAnsCsAccessCrownState(lpObj->m_Index,0);
			g_CastleSiege.SetCrownUserIndex(lpObj->m_Index);
			g_CastleSiege.SetCrownAccessUserX(lpObj->X);
			g_CastleSiege.SetCrownAccessUserY(lpObj->Y);
			g_CastleSiege.SetCrownAccessTickCount();
			g_CastleSiege.NotifyAllUserCsProgState(0,lpObj->GuildName);
			LogAddTD("[CastleSiege] [%s][%s] Start to Register Castle Crown (GUILD:%s)",lpObj->AccountID,lpObj->Name,lpObj->GuildName);
		}
	}
	else if(lpObj->m_Index != iUserIndex)
	{
		GCAnsCsAccessCrownState(lpObj->m_Index,3);
	}

	return TRUE;
}

BOOL NpcCastleSwitch(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if(g_CastleSiege.GetCastleState() != CASTLESIEGE_STATE_STARTSIEGE)
	{
		return TRUE;
	}
	
	if(lpObj->m_btCsJoinSide < 2)
	{
		return TRUE;
	}

	if( (abs(lpObj->Y - lpNpc->Y)) > 3 || (abs(lpObj->X - lpNpc->X)) > 3)
	{
		return TRUE;
	}

	if(g_CastleSiege.CheckGuardianStatueExist() == TRUE)
	{
		MsgOutput(lpObj->m_Index,lMsg.Get(MSGGET(6, 200)));
		return TRUE;
	}

	int iUserIndex = g_CastleSiege.GetCrownSwitchUserIndex(lpNpc->Class);

	if(!gObjIsConnected(iUserIndex))
	{
		GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,-1,1);
		g_CastleSiege.SetCrownSwitchUserIndex(lpNpc->Class,lpObj->m_Index);
		LogAddTD("[CastleSiege] [%s][%s] Start to Push Castle Crown Switch (GUILD:%s) - CS X:%d/Y:%d",lpObj->AccountID,lpObj->Name,lpObj->GuildName,lpNpc->X,lpNpc->Y);
	}
	else if(lpObj->m_Index != iUserIndex)
	{
		GCAnsCsAccessSwitchState(lpObj->m_Index,lpNpc->m_Index,iUserIndex,2);
	}

	return TRUE;
}

struct PMSG_ANS_GUARD_IN_CASTLE_HUNTZONE {
  /*<thisrel this+0x0>*/ /*|0x4|*/ struct PBMSG_HEAD2 h;
  /*<thisrel this+0x4>*/ /*|0x1|*/ BYTE btResult;
  /*<thisrel this+0x5>*/ /*|0x1|*/ BYTE btUsable;
  /*<thisrel this+0x8>*/ /*|0x4|*/ int iCurrentPrice;
  /*<thisrel this+0xc>*/ /*|0x4|*/ int iMaxPrice;
  /*<thisrel this+0x10>*/ /*|0x4|*/ int iUnitOfPrice;
};
// <size 0x14>

BOOL NpcCastleHuntZoneGuard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	PMSG_ANS_GUARD_IN_CASTLE_HUNTZONE pResult = {0};

	PHeadSubSetB((LPBYTE)&pResult,0xB9,0x03,sizeof(PMSG_ANS_GUARD_IN_CASTLE_HUNTZONE));
	pResult.btResult = TRUE;
	pResult.iMaxPrice = 300000;
	pResult.iUnitOfPrice = 10000;
	pResult.btUsable = 0;
	pResult.iCurrentPrice = 0;

	pResult.iCurrentPrice = g_CastleSiegeSync.GetTaxHuntZone(lpObj->m_Index,FALSE);

	if(g_CastleSiege.GetHuntZoneEnter())
	{
		pResult.btUsable = TRUE;
	}

	if(lpObj->lpGuild != NULL)
	{
		if(g_CastleSiege.CheckCastleOwnerUnionMember(lpObj->m_Index))
		{
			pResult.btResult = 2;
		}

		if(g_CastleSiege.CheckCastleOwnerMember(lpObj->m_Index))
		{
			if(lpObj->GuildStatus == G_MASTER)
			{
				pResult.btResult = 3;
			}
		}
	}
	else
	{
		if(g_CastleSiege.GetHuntZoneEnter())
		{
			pResult.btResult = TRUE;
		}
	}

	DataSend(lpObj->m_Index,(LPBYTE)&pResult,pResult.h.size);

	return TRUE;
}

BOOL NpcShadowPhantom(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	if ( lpObj->Level > g_iShadowPhantomMaxLevel || lpObj->ChangeUP3rd != false)
	{
		GCServerCmd(lpObj->m_Index, 0x0D, 0, 0);
		
		return TRUE;
	}

	int iAttack = 0;
	int iDefense = 0;
	int iDuration = 0;

	if ( lpObj->Level <= 180 )
	{
		iAttack = lpObj->Level / 3 + 45;
		iDefense = lpObj->Level / 5 + 50;
	}
	else
	{
		iAttack = 105;
		iDefense = 86;
	}

	iDuration = (lpObj->Level / 6 + 30) * 60;

	gObjApplyBuffEffectDuration(lpObj, AT_NPC_HELP, 2, iAttack, 3, iDefense, iDuration);
	return TRUE;
}

BOOL NpcCrywolfAltar(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return TRUE;//Season 4.5 fix
}

BOOL NpcPamelaSupplier(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL NpcAngelaSupplier(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL NpcFirecrackerMerchant(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

//Illusion Maybe Comes Now

BOOL NpcIllusionStatue(LPOBJ lpNpc, LPOBJ lpObj) //identical gs-cs 56
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcStatueUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionYellowPedestal(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcAlliedUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionBluePedestal(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcRelicsUser(lpObj->MapNumber, lpNpc, lpObj);

	return TRUE;
}

BOOL NpcIllusionMirage(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	g_IllusionTempleEvent.SetNpcMirageUser(lpNpc, lpObj);

	return TRUE;
}

//Season 3
BOOL NpcSilviaSupplier(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL NpcRheaMerchant(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

BOOL NpcMarceWizard(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

//005DE0F0 -> call from 5DAC4E
BOOL NpcSeedMaster(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( bCanChaosBox == TRUE )
	{
		if ( lpObj->m_IfState.use > 0 )
		{
			return TRUE;
		}

		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed", lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x17;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 7;

		LogAddTD("[JewelMix] [%s][%s] Socket Item Mix Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}

//005DE270 ->  call from 5DAC72
BOOL NpcSeedResearcher(LPOBJ lpNpc, LPOBJ lpObj)
{
		if ( bCanChaosBox == TRUE )
	{
		if ( lpObj->m_IfState.use > 0 )
		{
			return TRUE;
		}

		if ( lpObj->m_bPShopOpen == true )
		{
			LogAdd("[%s][%s] is Already Opening PShop, ChaosBox Failed", lpObj->AccountID, lpObj->Name);
			GCServerMsgStringSend(lMsg.Get(MSGGET(4,194)), lpObj->m_Index, 1);
			return TRUE;
		}

		PMSG_TALKRESULT pMsg;

		pMsg.h.c = 0xC3;
		pMsg.h.headcode = 0x30;
		pMsg.h.size = sizeof(pMsg);
		pMsg.result = 0x18;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->m_IfState.use = 1;
		lpObj->m_IfState.type = 7;

		LogAddTD("[JewelMix] [%s][%s] Socket Item Mix Start", lpObj->AccountID, lpObj->Name);

		gObjItemTextSave(lpObj);
		gObjWarehouseTextSave(lpObj);
	}

	return TRUE;
}

//005DE3F0 ->  call from 5DAC2A
BOOL NpcCherryBlossomSpirit(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

//005DE430  -> call from 5DAC96
BOOL NpcLuckyCoinExchanger(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}
	return FALSE;
}

//005DE470 call from 5DACBA
BOOL NpcXMasSantaClaus(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	EGAnsRegXMasGetPayItem(lpObj->m_Index,1);

	return TRUE;
}

//005DE4C0 call from 5DACDE
BOOL NpcSnowMan(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	ReqNPCXMasMapMoveOpen(lpObj->m_Index) ;

	return TRUE;
}

//005DE510 call from 5DAD04->5DAD2A->5DAD50->5DAD76->5DAD99->5DADB9->5DADF9
BOOL NpcLittleSantaBuffer(LPOBJ lpNpc, LPOBJ lpObj,int BuffEffect)
{
	if ( gObjIsConnected(lpObj->m_Index) == FALSE )
	{
		return TRUE;
	}

	switch(BuffEffect)
	{
	case AT_NULL_BUFF_EFFECT:
		lpObj->Life = lpObj->AddLife + lpObj->MaxLife;
		GCReFillSend(lpObj->m_Index, (int)lpObj->Life, 0xFF, 0, (int)lpObj->iShield);
		break;
	case AT_INCREASE_ATTACK:
		lpObj->Mana = lpObj->AddMana + lpObj->MaxMana;
		GCManaSend(lpObj->m_Index,(int)lpObj->Mana,0xFF,0,(int)lpObj->BP);
		break;
	case AT_XMASS_ATTACK:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_ATTACK,57,30,0,0,1800);
		break;
	case AT_XMASS_DEFENSE:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_DEFENSE,58,100,0,0,1800);
		break;
	case AT_XMASS_HEALTH:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_HEALTH,4,500,0,0,1800);
		break;
	case AT_XMASS_MANA:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_MANA,5,500,0,0,1800);
		break;
	case AT_XMASS_DEXTERITY:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_DEXTERITY,1,15,0,0,1800);
		break;
	case AT_XMASS_AG_RECOVERY:
		gObjApplyBuffEffectDuration(lpObj,AT_XMASS_AG_RECOVERY,59,10,0,0,1800);
		break;
	}

	return TRUE;
}
bool NpcTitusGatekeeper(LPOBJ lpNpc, LPOBJ lpObj)
{
	if ( (lpObj->m_IfState.use ) > 0 )
	{
		return TRUE;
	}

	lpObj->m_IfState.use = 1;
	lpObj->m_IfState.type = 20;

	PMSG_TALKRESULT pMsg;

	pMsg.h.c = 0xC3;
	pMsg.h.headcode = 0x30;
	pMsg.h.size = 9;
	pMsg.result = 0x21;

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

	g_DuelManager.SendDuelStatus(lpObj);
	
	return TRUE;
}
// ----------------------------------------------------------------------------------------------------------------------
bool NpcMoss(LPOBJ lpNpc, LPOBJ lpObj)
{
	/*
	if ( gMossMerchant.Enabled == false )
	{
		return true;
	}

	if ( gMossMerchant.Running == false )
	{
		return true;
	}
	*/
	BYTE Send2[6] = {0xC3,0x06,0x30,0x00,0x27,0x00};								 // SHOP WINDOW
			BYTE Send[71] = {0xC2,0x00,71,0x31,0x00,5,                                       // Head
							0x00,71,0x00,0x01,0x00,0x00,13*16,0x00,0xFF,0xFF,0xFF,0xFF,0xFF, // ITEM1
							0x02,72,0x00,0x01,0x00,0x00,13*16,0x00,0xFF,0xFF,0xFF,0xFF,0xFF, // ITEM2
							0x04,73,0x00,0x01,0x00,0x00,13*16,0x00,0xFF,0xFF,0xFF,0xFF,0xFF, // ITEM3
							0x06,74,0x00,0x01,0x00,0x00,13*16,0x00,0xFF,0xFF,0xFF,0xFF,0xFF, // ITEM4
							0x18,75,0x00,0x01,0x00,0x00,13*16,0x00,0xFF,0xFF,0xFF,0xFF,0xFF  // ITEM5
							};

							DataSend(lpObj->m_Index,Send2,6);
							DataSend(lpObj->m_Index,Send,71);

							lpObj->TargetShopNumber = 492;
							lpObj->m_IfState.use    = 1;
							lpObj->m_IfState.type   = 3;

	return true;
}