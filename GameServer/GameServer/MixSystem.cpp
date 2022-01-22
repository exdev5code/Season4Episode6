//GameServer 1.00.90 JPN - Completed
#include "stdafx.h"
#include "MixSystem.h"
#include "logproc.h"
#include "GameMain.h"
#include "GameServer.h"
#include "..\common\winutil.h"
#include "DSProtocol.h"
#include "CastleSiegeSync.h"
#include "GameServerAuth.h"
#include "BloodCastle.h"
#include "..\common\SetItemOption.h"
#include "JewelOfHarmonySystem.h"
#include "giocp.h"
#include "CrywolfSync.h"
#include "CashLotterySystem.h"
#include "ChaosCard.h"
#include "ProbabilityItemBag.h"
#include "Event.h"
#include "Configs.h"

CMixSystem g_MixSystem;

CMixSystem::CMixSystem()
{
	this->iJewelofChaos = ITEMGET(12,15);
	this->iJewelofBless = ITEMGET(14,13);
	this->iJewelofSoul = ITEMGET(14,14);
	this->iJewelofCreation = ITEMGET(14,22);
	this->iBundleofBless = ITEMGET(12,30);
	this->iBundleofSoul = ITEMGET(12,31);
	this->iCondorFeather = ITEMGET(13,53);
	this->iCondorFlame = ITEMGET(13,52);
	this->iWingofStorm = ITEMGET(12,36);
	this->iWingofEternal = ITEMGET(12,37);
	this->iWingofIllusion = ITEMGET(12,38);
	this->iWingofRuin = ITEMGET(12,39);
	this->iCapeofLord = ITEMGET(12,40);
	this->iWingofDimension = ITEMGET(12,43);

	this->i3rdWingLuckRate = 50;
}

CMixSystem::~CMixSystem()
{

}

BOOL CMixSystem::ChaosBoxCheck(LPOBJ lpObj)
{
	if ( lpObj->pChaosBox == NULL )
	{
		return false;
	}

	return true;
}

BOOL CMixSystem::ChaosBoxInit(LPOBJ lpObj)
{
	int n;

	if ( lpObj->pChaosBox != NULL )
	{
		for (n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBox[n].Clear();
		}

		for (n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBoxMap[n] = -1;
		}
		return true;
	}

	lpObj->pChaosBox = new CItem[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBox == NULL )
	{
		return false;
	}

	lpObj->pChaosBoxMap = new BYTE[CHAOS_BOX_SIZE];

	if ( lpObj->pChaosBoxMap == NULL )
	{
		delete lpObj->pChaosBox;
		return false;
	}

	for (n=0;n<CHAOS_BOX_SIZE;n++)
	{
		lpObj->pChaosBoxMap[n] = -1;
	}

	return true;
}

BOOL CMixSystem::ChaosBoxItemDown(LPOBJ lpObj)
{
	if ( lpObj->pChaosBox == NULL )
	{
		return FALSE;
	}

	for (int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if (lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) ||
			//Season4.5 add-on (Talisman of Wing)
			lpObj->pChaosBox[n].m_Type == ITEMGET(13,83) || lpObj->pChaosBox[n].m_Type == ITEMGET(13,84) ||
			lpObj->pChaosBox[n].m_Type == ITEMGET(13,85) ||	lpObj->pChaosBox[n].m_Type == ITEMGET(13,86) ||
			lpObj->pChaosBox[n].m_Type == ITEMGET(13,87) || lpObj->pChaosBox[n].m_Type == ITEMGET(13,88) ||
			lpObj->pChaosBox[n].m_Type == ITEMGET(13,89) || lpObj->pChaosBox[n].m_Type == ITEMGET(13,90) ||
			lpObj->pChaosBox[n].m_Type == ITEMGET(13,91) ||	lpObj->pChaosBox[n].m_Type == ITEMGET(13,92) ||
			lpObj->pChaosBox[n].m_Type == ITEMGET(14,53))
		{
			lpObj->pChaosBox[n].Clear();
		}
		else
		{
			int op = lpObj->pChaosBox[n].m_Option1;

			if ( op > 0 )
			{
				if ( (rand() % 2) == 0 )
				{
					op--;
				}
			}

			lpObj->pChaosBox[n].m_Option1 = op;
			op = lpObj->pChaosBox[n].m_Option3;

			if ( op > 0 )
			{
				if ( (rand() % 2) == 0 )
				{
					op--;
				}
			}

			lpObj->pChaosBox[n].m_Option3 = op;

			if ( lpObj->pChaosBox[n].m_Level > 0 )
			{
				lpObj->pChaosBox[n].m_Level = rand() % lpObj->pChaosBox[n].m_Level;
			}

			float dur = (float)ItemGetDurability(lpObj->pChaosBox[n].m_Type, lpObj->pChaosBox[n].m_Level, lpObj->pChaosBox[n].IsExtItem(), lpObj->pChaosBox[n].IsSetItem());
			
			lpObj->pChaosBox[n].m_Durability =  dur * lpObj->pChaosBox[n].m_Durability / lpObj->pChaosBox[n].m_BaseDurability;
			lpObj->pChaosBox[n].Convert(lpObj->pChaosBox[n].m_Type, lpObj->pChaosBox[n].m_Option1,
				lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, lpObj->pChaosBox[n].m_NewOption,
				lpObj->pChaosBox[n].m_SetOption, lpObj->pChaosBox[n].m_ItemOptionEx, NULL, 0xFF, CURRENT_DB_VERSION);
		}
	}

	return TRUE;
}

int CMixSystem::ChaosBoxMix(LPOBJ lpObj, int & Result2, int & Result3)
{
	BYTE ExOption[8];
	int ChaosDiamond = 0;
	int ChaosItems = 0;

	if ( lpObj->pChaosBox == NULL )
	{
		return 0;
	}

	int value = 0;
	int add = 0;
	int nv = 0;
	
	Result2 = 0;
	Result3 = -1; //season4 add-on

	int WingCharmItemNum = -1; //season4.5 add-on

	lpObj->ChaosSuccessRate = 0;
	lpObj->ChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			lpObj->pChaosBox[n].OldValue();
			add = 0;
			nv = 0;

			if ( lpObj->pChaosBox[n].m_Level >= MIN_CHAOS_ITEM_LEVEL && (lpObj->pChaosBox[n].m_Option3 *4) >= MIN_CHAOS_ITEM_LEVEL )
			{
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				add = 1;

				if ( lpObj->pChaosBox[n].m_Type == ITEMGET(2,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(4,6) || lpObj->pChaosBox[n].m_Type == ITEMGET(5,7) )	// Chaos Items
				{
					Result2 = 1;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				ChaosDiamond++;
				add = 1;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )	// Jewel of Bless, Jewel of Soul
			{
				value += lpObj->pChaosBox[n].m_OldBuyMoney;
				nv = lpObj->pChaosBox[n].m_OldBuyMoney;
				add = 1;
			}

			//season4.5 add-on
			if( lpObj->pChaosBox[n].m_Type == ITEMGET(13,83) ||
				lpObj->pChaosBox[n].m_Type == ITEMGET(13,84) ||
				lpObj->pChaosBox[n].m_Type == ITEMGET(13,85) ||
				lpObj->pChaosBox[n].m_Type == ITEMGET(13,86) ||
				lpObj->pChaosBox[n].m_Type == ITEMGET(13,87) )
			{
				WingCharmItemNum = lpObj->pChaosBox[n].m_Type;
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,14) ) // Loch Feather
			{
				return FALSE;
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}

			if ( add != 0  )
			{
				ChaosItems++;
			}

			ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);
			LogAdd("[%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%u][%d][%d] Ex:[%d,%d,%d,%d,%d,%d,%d]",
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(),
				lpObj->pChaosBox[n].m_Level, lpObj->pChaosBox[n].m_Option1,
				lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3,
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability,
				nv, ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5],
				ExOption[6], lpObj->pChaosBox[n].m_SetOption);
		}
	}

	if ( ChaosDiamond == 0 )
	{
		value = 0;
	}

	if ( ChaosItems < 2 )
	{
		value = 0;
	}

	if ( iCharmOfLuckCount > 10 )
		return FALSE;
	
	lpObj->ChaosSuccessRate = value / 20000;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	if ( lpObj->ChaosSuccessRate  > 100 )
	{
		lpObj->ChaosSuccessRate = 100;
	}

	lpObj->ChaosMoney = lpObj->ChaosSuccessRate * 10000;

	LogAddTD("[%s][%s] CBMix need Zen : %d SuccessRate : %d, CharmRate : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosMoney, lpObj->ChaosSuccessRate, iCharmOfLuckCount);

	if(WingCharmItemNum > -1) //season4.5 add-on
	{
		int WingCharmIndex = WingCharmItemNum ^ ITEMGET(13,0);

		switch(WingCharmIndex)
		{
		case 83:
			Result3 = 2;
			break;
		case 84:
			Result3 = 1;
			break;
		case 85:
			Result3 = 0;
			break;
		case 86:
			Result3 = 41;
			break;
		case 87:
			Result3 = 40;
			break;
		default:
			LogAddTD("[MixSystem] WingCharmItemNum => %d , WingCharmIndex => %d", WingCharmItemNum, WingCharmIndex);
		}
	}

	return value;
}

void CMixSystem::DefaultChaosMix(LPOBJ lpObj)
{
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int aIndex = lpObj->m_Index;
	BOOL fail = TRUE;
	int MixResult2;
	lpObj->ChaosLock = TRUE;
	int WingCharmIndex = -1; //season4.5 add-on

	if ( ChaosBoxMix(lpObj, MixResult2, WingCharmIndex) == 0 )
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	int iChaosTaxMoney = (int)((__int64)lpObj->ChaosMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	lpObj->ChaosMoney += iChaosTaxMoney;

	if ( lpObj->ChaosMoney < 0 )
	{
		lpObj->ChaosMoney = 0;
	}

	if ( lpObj->Money < lpObj->ChaosMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
	}
	else 
	{
		if ( lpObj->ChaosSuccessRate > 0 )
		{
			if ( lpObj->ChaosSuccessRate >= 100 )
			{
				lpObj->ChaosSuccessRate = 100;
			}

			if ( (rand()%100) <= (lpObj->ChaosSuccessRate-1) ) 
			{
				fail = FALSE;
				pMsg.Result = CB_SUCCESS;

				int Level = rand()%5;
				int Option1 = 0;
				int Option2 = 0;
				int Option3 = 0;

				if ( (rand()%100)< (lpObj->ChaosSuccessRate/5 + 6) )
				{
					Option1 = 1;
				}

				if ( (rand()%100)< (lpObj->ChaosSuccessRate/5 + 4) )
				{
					Option2 = 1;
				}

				int OpProb;
				int OpType = rand()%3;
				OpProb = rand()%100;

				switch ( OpType )
				{
					case 0:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 4) ) 
						{
							Option3 = 3;
						}
						break;

					case 1:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 8) ) 
						{
							Option3 = 2;
						}
						break;

					case 2:
						if ( OpProb < (lpObj->ChaosSuccessRate / 5 + 12) ) 
						{
							Option3 = 1;
						}
						break;
				}

				if ( MixResult2 == 1 )
				{
					int WingType = rand()%4;
					int WingNum = 0;

					if(WingCharmIndex > -1) //season4.5 add-on
					{
						WingNum = WingCharmIndex + ITEMGET(12,0);
					}
					else if ( WingType == 0 )
					{
						WingNum = ITEMGET(12,0);
					}
					else if ( WingType == 1 )
					{
						WingNum = ITEMGET(12,1);
					}
					else if ( WingType == 2 )
					{
						WingNum = ITEMGET(12,2);
					}
					else if ( WingType == 3 ) //season3 add-on
					{
						WingNum = ITEMGET(12,41);
					}

					::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, WingNum, 0, 255, (BYTE)Option1, (BYTE)Option2, (BYTE)Option3, -1, 0, 0);
				}
				else
				{
					int ChaosItemType = rand()%3;
					int ChaosItemNum = 0;

					if ( ChaosItemType == 0 )	// Chaos Dragon Axe
					{
						ChaosItemNum = ITEMGET(2,6);
					}
					else if ( ChaosItemType == 1 )	// Chaos Nature Bow
					{
						ChaosItemNum = ITEMGET(4,6);
					}
					else if ( ChaosItemType == 2 )	// Chaos Lighting Staff
					{
						ChaosItemNum = ITEMGET(5,7);
					}

					::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ChaosItemNum, (BYTE)Level, 255, (BYTE)Option1, (BYTE)Option2, (BYTE)Option3, -1, 0, 0);
				}
			}
		}


		lpObj->Money -= lpObj->ChaosMoney;
		g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
		GCMoneySend(lpObj->m_Index, lpObj->Money);

		if ( fail == TRUE )
		{
			ChaosBoxItemDown(lpObj);
			GCUserChaosBoxSend(lpObj, 0);
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			LogAddTD("[%s][%s] CBMix Fail %d Money : %d-%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, lpObj->ChaosMoney);
			lpObj->ChaosLock = FALSE;
		}
		else
		{
			LogAddTD("[%s][%s] CBMix Success Rate:%d Money : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->ChaosMoney);
		}

		if ( gChaosEvent != FALSE )
		{
			CBUPS_ItemRequest(lpObj->m_Index, lpObj->AccountID, lpObj->Name);
		}
	}

	::gObjInventoryCommit(lpObj->m_Index);
}

void CMixSystem::LogDQChaosItem(LPOBJ lpObj)
{
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n] );

			LogAddTD("[DevilSquare,%d] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%u][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380Ex[%d] HO:[%d,%d]",
				lpObj->pChaosBox[n].m_Level,
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6],
				lpObj->pChaosBox[n].m_SetOption, lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]),
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]));
		}
	}
}

int CMixSystem::CheckDevilSquareItem(LPOBJ lpObj, int & eventitemcount, int & itemlevel)
{
	BOOL bChaoseGem = FALSE;
	BOOL bEyeOfDevil = FALSE;
	BOOL bKeyOfDevil = FALSE;
	eventitemcount = 0;
	BOOL FoundOtherItem = FALSE;
	int level = -1;
	BOOL bLevelCheck = FALSE;
	int iCharmOfLuckCount = 0;
	BOOL bCharmOfLuckOver = FALSE;

	LogAdd("[DevilSquare] Search DevilSquareItem");

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// Chaos
			{
				bChaoseGem = TRUE;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,17) )	// Eye
			{
				eventitemcount +=1;
				bEyeOfDevil = TRUE;

				if ( level != lpObj->pChaosBox[n].m_Level )
				{
					if ( level == -1 )
					{
						level = lpObj->pChaosBox[n].m_Level;
					}
					else
					{
						bLevelCheck = TRUE;
					}
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,18) )	// Key
			{
				eventitemcount +=1;
				bKeyOfDevil = TRUE;

				if ( level != lpObj->pChaosBox[n].m_Level )
				{
					if ( level == -1 )
					{
						level = lpObj->pChaosBox[n].m_Level;
					}
					else
					{
						bLevelCheck = TRUE;
					}
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;

				if ( iCharmOfLuckCount > 10 )
				{
					bCharmOfLuckOver = TRUE;
				}
			}
			else
			{
				FoundOtherItem = TRUE;
			}
		}
	}

	itemlevel = level;
	lpObj->ChaosSuccessRate = iCharmOfLuckCount;

	if ( FoundOtherItem != FALSE )
	{
		LogAdd("[DevilSquare] Other DQItems Found");
		return 0;
	}

	if ( bLevelCheck != FALSE )
	{
		LogAdd("[DevilSquare] DiffLevel DQItems Found");
		return 3;
	}

	if ( bCharmOfLuckOver == TRUE )
	{
		LogAdd("[DevilSquare] Charm Of Luck Count Over");
		return 4;
	}

	if ( bChaoseGem != FALSE && bEyeOfDevil != FALSE && bKeyOfDevil != FALSE )
	{
		LogDQChaosItem(lpObj);
		return 1;
	}

	if ( bEyeOfDevil != FALSE && bKeyOfDevil != FALSE )
	{
		LogDQChaosItem(lpObj);
		return 2;
	}

	LogAdd("[DevilSquare] DQItems Not Found");

	return 0;
}

BOOL CMixSystem::DevilSquareEventChaosMix(LPOBJ lpObj, BOOL bCheckType, int iItemLevel)
{
	BOOL fail = TRUE;
	int aIndex = lpObj->m_Index;
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;

	LogAddTD("[DevilSquare] Chaos Mix Start");

	INT nChaosNeedMoney = 0;

	int iCharmOfLuckCount = 0;
	iCharmOfLuckCount = lpObj->ChaosSuccessRate;

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		lpObj->ChaosLock = FALSE;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
	}

	switch ( iItemLevel )
	{
		case 0:
			lpObj->ChaosSuccessRate = 60;
			nChaosNeedMoney = 100000;
			break;

		case 1:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel1;
			nChaosNeedMoney = 100000;
			break;

		case 2:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel2;
			nChaosNeedMoney = 200000;
			break;

		case 3:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel3;
			nChaosNeedMoney = 400000;
			break;

		case 4:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel4;
			nChaosNeedMoney = 700000;
			break;

		case 5:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel5;
			nChaosNeedMoney = 1100000;
			break;

		case 6:
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel6;
			nChaosNeedMoney = 1600000;
			break;

		case 7: //Master
			lpObj->ChaosSuccessRate = gDQChaosSuccessRateLevel7;
			nChaosNeedMoney = 2000000;
			break;

		default:
			LogAdd("[DevilSquare] [%s][%s] Invalid DQItem Level [%d]", lpObj->AccountID, lpObj->Name, iItemLevel);

			pMsg.Result = CB_INVALID_ITEM_LEVEL;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			return 1;
			break;
	}

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( (lpObj->Money - nChaosNeedMoney) < 0 )
	{
		LogAddTD("[DevilSquare] [%s][%s] CBMix Not Enough Money [%d] need zen [%d]", lpObj->AccountID, lpObj->Name, lpObj->Money, nChaosNeedMoney);
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return 1;

	}

	if ( g_CrywolfSync.GetOccupationState() == 0 && g_iCrywolfApplyMvpBenefit )
	{	
		lpObj->ChaosSuccessRate += g_CrywolfSync.GetPlusChaosRate();
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int iRate = rand() % 100;

	if ( bCheckType == TRUE )
	{
		if ( iRate < lpObj->ChaosSuccessRate )
		{
			int DevilInv = ITEMGET(14,19);	// Devil Ticket
			ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, DevilInv, (BYTE)iItemLevel, 0, 0, 0, 0, -1, 0, 0);
			fail = FALSE;
		}
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( szAuthKey[17] != AUTHKEY17 )
	{
		::DestroyGIocp();
	}

	if ( fail == TRUE )
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DevilSquare,%d] [%s][%s] CBMix Fail %d Money : %d-%d", iItemLevel, lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney);
		lpObj->ChaosLock = FALSE;
	}
	else
	{
		LogAddTD("[DevilSquare,%d] [%s][%s] CBMix Success Rate:%d Money : %d", iItemLevel, lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, nChaosNeedMoney);
	}

	::gObjInventoryCommit(lpObj->m_Index);

	return TRUE;
}

void CMixSystem::DevilSquareItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	if ( gDevilSquareEvent != FALSE )
	{
		PMSG_CHAOSMIXRESULT pMsg;
		PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
		pMsg.Result = CB_ERROR;
		int aIndex = lpObj->m_Index;
		int eventitemcount;
		int itemlevel;
		int Ret = this->CheckDevilSquareItem(lpObj, eventitemcount, itemlevel);

		if ( Ret != FALSE )
		{
			if ( Ret == 3 )
			{
				pMsg.Result = CB_INCORRECT_MIX_ITEMS;
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] DiffLevel Devil's Key or Eyes [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;

				return;
			}
			
			if ( Ret == 2 )
			{
				pMsg.Result = CB_INCORRECT_MIX_ITEMS;
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Not Found Chaos Gem [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;
				
				return;
			}

			if ( Ret == 4 )
			{
				pMsg.Result = 0xF0;
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Charm Of Luck Over 10% [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;
				
				return;
			}

			
			if ( eventitemcount > 2 )
			{
				pMsg.Result = CB_TOO_MANY_ITEMS;
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				LogAdd("[DevilSquare] Too many Devil's Key or Eyes [%d]", eventitemcount);
				lpObj->ChaosLock = FALSE;

				return;
			}

			if ( lpObj->Level < 10 )
			{
				pMsg.Result = CB_LOW_LEVEL_USER;
				DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;

				return;
			}

			this->DevilSquareEventChaosMix(lpObj, Ret, itemlevel);
			return;
		}
		
		if ( eventitemcount > 1 )
		{
			pMsg.Result = CB_LACKING_MIX_ITEMS;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;

			return;
		}
	}

	lpObj->ChaosLock = FALSE;
}

void CMixSystem::LogPlusItemLevelChaosItem(LPOBJ lpObj, int iPlusMixLevel)
{
	int iMixLevel = 0;
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);

			if ( iPlusMixLevel == 3 )
				iMixLevel = 1;
			else if ( iPlusMixLevel == 4 )
				iMixLevel = 2;
			else if ( iPlusMixLevel == 22 )
				iMixLevel = 3;
			else if ( iPlusMixLevel == 23 )
				iMixLevel = 4;

			LogAddTD("[PlusItemLevel,%d] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%u][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380Ex:[%d] HO:[%d,%d]", iMixLevel,
				lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6], lpObj->pChaosBox[n].m_SetOption,
				lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]),
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]));
		}
	}
}

void CMixSystem::LogChaosItem(LPOBJ lpObj, LPSTR sLogType)
{
	BYTE ExOption[MAX_EXOPTION_SIZE];

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			::ItemIsBufExOption(ExOption, &lpObj->pChaosBox[n]);

			LogAddTD("[%s] [%s][%s] CBMix [%d,%s,%d,%d,%d,%d]serial:[%u][%d] Ex:[%d,%d,%d,%d,%d,%d,%d] Set:[%d] 380:[%d] HO:[%d,%d] Socket[%d,%d,%d,%d,%d]",
				sLogType, lpObj->AccountID, lpObj->Name, n, lpObj->pChaosBox[n].GetName(), lpObj->pChaosBox[n].m_Level,
				lpObj->pChaosBox[n].m_Option1, lpObj->pChaosBox[n].m_Option2, lpObj->pChaosBox[n].m_Option3, 
				lpObj->pChaosBox[n].m_Number, (int)lpObj->pChaosBox[n].m_Durability, 
				ExOption[0], ExOption[1], ExOption[2], ExOption[3], ExOption[4], ExOption[5], ExOption[6], lpObj->pChaosBox[n].m_SetOption,
				lpObj->pChaosBox[n].m_ItemOptionEx >> 7,
				g_kJewelOfHarmonySystem.GetItemStrengthenOption(&lpObj->pChaosBox[n]),
				g_kJewelOfHarmonySystem.GetItemOptionLevel(&lpObj->pChaosBox[n]),
				//season4 add-on
				lpObj->pChaosBox[n].m_SocketOption[0],
				lpObj->pChaosBox[n].m_SocketOption[1],
				lpObj->pChaosBox[n].m_SocketOption[2],
				lpObj->pChaosBox[n].m_SocketOption[3],
				lpObj->pChaosBox[n].m_SocketOption[4]);
		}
	}
}

BOOL CMixSystem::PlusItemLevelChaosMix(LPOBJ lpObj, int mixType)
{
	int ChaosGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int Plus9ItemCount = 0;
	int Plus10ItemCount = 0;
	int PlusItemPos = -1;
	int OtherItemFound = 0;
	int Plus11ItemCount = 0;
	int Plus12ItemCount = 0;
	int ExtraBlessGemCount = 0;
	int ExtraSoulGemCount = 0;

	int iCharmOfAssemblyCount = 0; //season3.5 add-on
	int iCharmOfLuckCount = 0;
	
	BYTE btItemLuckValue = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChaosGemCount++;
			}
			else if (  lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if (  lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,96) )	// Charm Of Assembly
			{
				iCharmOfAssemblyCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 9 )
			{
				Plus9ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 10 )
			{
				Plus10ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 11 )
			{
				Plus11ItemCount++;
				PlusItemPos = n;
			}
			else if ( lpObj->pChaosBox[n].m_Level == 12 )
			{
				Plus12ItemCount++;
				PlusItemPos = n;
			}
			else
			{
				OtherItemFound ++;
			}
		}
	}

	if ( iCharmOfLuckCount > 10 )
	{
		PMSG_CHAOSMIXRESULT pResult;
		PHeadSetB((LPBYTE)&pResult, 0x86, sizeof(pResult));
		LogAddTD("[PlusItemLevel] [%s][%s] CBMix Charm of luck over 10% (%d)", lpObj->AccountID, lpObj->Name, iCharmOfLuckCount);
		pResult.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
		lpObj->ChaosLock = FALSE;
		return 0;
	}

	if ( OtherItemFound != FALSE )
	{
		return FALSE;
	}

	if(iCharmOfAssemblyCount > 1)
	{
		PMSG_CHAOSMIXRESULT pResult;
		PHeadSetB((LPBYTE)&pResult, 0x86, sizeof(pResult));
		pResult.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pResult, pResult.h.size);
		lpObj->ChaosLock = FALSE;
		return 0;
	}

	lpObj->ChaosMoney = 0;
	int MixType = 0;

	if ( Plus9ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 1 && SoulGemCount == 1 && Plus10ItemCount == 0 && Plus11ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 3;
		lpObj->ChaosMoney = 2000000;
		ExtraBlessGemCount = BlessGemCount - 1;
		ExtraSoulGemCount = SoulGemCount - 1;
	}
	else if ( Plus10ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 2 && SoulGemCount == 2 && Plus9ItemCount == 0 && Plus11ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 4;
		lpObj->ChaosMoney = 4000000;
		ExtraBlessGemCount = BlessGemCount - 2;
		ExtraSoulGemCount = SoulGemCount - 2;
	}
	else if ( Plus11ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 3 && SoulGemCount == 3 && Plus9ItemCount == 0 && Plus10ItemCount == 0 && Plus12ItemCount == 0 )
	{
		MixType = 22;
		lpObj->ChaosMoney = 6000000;
		ExtraBlessGemCount = BlessGemCount - 3;
		ExtraSoulGemCount = SoulGemCount - 3;
	}
	else if ( Plus12ItemCount == 1 && ChaosGemCount == 1 && BlessGemCount == 4 && SoulGemCount == 4 && Plus9ItemCount == 0 && Plus10ItemCount == 0 && Plus11ItemCount == 0 )
	{
		MixType = 23;
		lpObj->ChaosMoney = 8000000;
		ExtraBlessGemCount = BlessGemCount - 4;
		ExtraSoulGemCount = SoulGemCount - 4;
	}

	if ( MixType != mixType )
	{
		MixType = 0;
	}

	if ( MixType == 0 )
	{
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;
	this->LogPlusItemLevelChaosItem(lpObj, MixType);
	LogAddTD("[PlusItemLevel] Chaos Mix Start");

	int iChaosTaxMoney = (int)((__int64)lpObj->ChaosMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	lpObj->ChaosMoney += iChaosTaxMoney;

	if ( lpObj->ChaosMoney < 0 )
	{
		lpObj->ChaosMoney = 0;
	}

	if ( lpObj->Money < lpObj->ChaosMoney )
	{
		LogAddTD("[PlusItemLevel] [%s][%s] CBMix Not Enough Money [%d] need zen [%d]", lpObj->AccountID, lpObj->Name, lpObj->Money, lpObj->ChaosMoney);
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return TRUE;
	}

	lpObj->Money -= lpObj->ChaosMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	BYTE btMixLevel = 0; //season4.5 add-on (local31 ebp7c)
	if( lpObj->pChaosBox[PlusItemPos].IsExtItem() == 1 ||
		lpObj->pChaosBox[PlusItemPos].IsSetItem() == 1 ||
		g_kItemSystemFor380.Is380Item(&lpObj->pChaosBox[PlusItemPos]) == 1)
	{
		btMixLevel = 2;
	}
	else
	{
		btMixLevel = 1;
	}

	//season4.5 add-on
	if(g_SocketOption.IsSocketOption(&lpObj->pChaosBox[PlusItemPos]) == 1)
	{
		btMixLevel = 3;
	}

	//season4.5 add-on
	if( (lpObj->pChaosBox[PlusItemPos].m_Type >= ITEMGET(12,0) && lpObj->pChaosBox[PlusItemPos].m_Type <= ITEMGET(12,6)) || 
		(lpObj->pChaosBox[PlusItemPos].m_Type >= ITEMGET(12,36) && lpObj->pChaosBox[PlusItemPos].m_Type <= ITEMGET(12,43)) || 
		(lpObj->pChaosBox[PlusItemPos].m_Type >= ITEMGET(12,180) && lpObj->pChaosBox[PlusItemPos].m_Type <= ITEMGET(12,END_WING_NUM)) ||		//Custom Wings4
		lpObj->pChaosBox[PlusItemPos].m_Type == ITEMGET(13,30))
	{
		btMixLevel = 1;
	}

	if ( lpObj->pChaosBox[PlusItemPos].m_Level == 9 )
	{
		if(btMixLevel == 1) //season4.5 add-on
		{
			//int ExMixNormal10SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal10SuccessRate",60,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixNormal10SuccessRate;
		}
		else if(btMixLevel == 2) //season4.5 add-on
		{
			//int ExMix380AncExc10SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc10SuccessRate",50,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMix380AncExc10SuccessRate;
		}
		else if(btMixLevel == 3) //season4.5 add-on
		{
			//int ExMixSocket10SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket10SuccessRate",40,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixSocket10SuccessRate;
		}
	}
	else if ( lpObj->pChaosBox[PlusItemPos].m_Level == 10) //season4 changed
	{
		if(btMixLevel == 1) //season4.5 add-on
		{
			//int ExMixNormal11SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal11SuccessRate",60,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixNormal11SuccessRate;
		}
		else if(btMixLevel == 2) //season4.5 add-on
		{
			//int ExMix380AncExc11SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc11SuccessRate",50,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMix380AncExc11SuccessRate;
		}
		else if(btMixLevel == 3) //season4.5 add-on
		{
			//int ExMixSocket11SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket11SuccessRate",40,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixSocket11SuccessRate;
		}
	}
	else if (lpObj->pChaosBox[PlusItemPos].m_Level == 11) //season4 changed
	{
		if(btMixLevel == 1) //season4.5 add-on
		{
			//int ExMixNormal12SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal12SuccessRate",60,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixNormal12SuccessRate;
		}
		else if(btMixLevel == 2) //season4.5 add-on
		{
			//int ExMix380AncExc12SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc12SuccessRate",50,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMix380AncExc12SuccessRate;
		}
		else if(btMixLevel == 3) //season4.5 add-on
		{
			//int ExMixSocket12SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket12SuccessRate",40,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixSocket12SuccessRate;
		}
	}
	else if ( lpObj->pChaosBox[PlusItemPos].m_Level == 12) //season4 changed
	{
		if(btMixLevel == 1) //season4.5 add-on
		{
			//int ExMixNormal13SuccessRate = GetPrivateProfileInt("ChaosMix","MixNormal13SuccessRate",55,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixNormal13SuccessRate;
		}
		else if(btMixLevel == 2) //season4.5 add-on
		{
			//int ExMix380AncExc13SuccessRate = GetPrivateProfileInt("ChaosMix","Mix380AncExc13SuccessRate",50,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMix380AncExc13SuccessRate;
		}
		else if(btMixLevel == 3) //season4.5 add-on
		{
			//int ExMixSocket13SuccessRate = GetPrivateProfileInt("ChaosMix","MixSocket13SuccessRate",35,"..\\ExTeam\\CommonServer.ini");
			lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixSocket13SuccessRate;
		}
	}
	else
	{
		lpObj->ChaosSuccessRate = 45;
	}

	if(lpObj->pChaosBox[PlusItemPos].m_Option2 != 0) //season4.5 add-on
	{
		//int ExMixLuckOptRateAdd = GetPrivateProfileInt("ChaosMix","MixLuckOptRateAdd",20,"..\\ExTeam\\CommonServer.ini");
		lpObj->ChaosSuccessRate += ExConfig.CommonServer.ExMixLuckOptRateAdd;
	}

	if ( lpObj->ChaosSuccessRate > 75 )
	{
		//int ExMixMaxSuccessRate = GetPrivateProfileInt("ChaosMix","MixMaxSuccessRate",75,"..\\ExTeam\\CommonServer.ini");
		lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExMixMaxSuccessRate;
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		lpObj->pChaosBox[PlusItemPos].m_Level++;
		pMsg.Result = CB_SUCCESS;

		CItem Item;

		float Dur = (float)ItemGetDurability(lpObj->pChaosBox[PlusItemPos].m_Type, lpObj->pChaosBox[PlusItemPos].m_Level,
			lpObj->pChaosBox[PlusItemPos].IsExtItem(), lpObj->pChaosBox[PlusItemPos].IsSetItem());

		Item.m_Level = lpObj->pChaosBox[PlusItemPos].m_Level;
		Item.m_Durability = Dur * lpObj->pChaosBox[PlusItemPos].m_Durability / lpObj->pChaosBox[PlusItemPos].m_BaseDurability;
		Item.m_JewelOfHarmonyOption = lpObj->pChaosBox[PlusItemPos].m_JewelOfHarmonyOption;
		
		//season4 add-on
		BYTE SocketOption[5];
		BYTE SocketIndex;
		g_SocketOption.GetActiveSocketOption(&lpObj->pChaosBox[PlusItemPos],SocketOption,SocketIndex);

		Item.Convert(lpObj->pChaosBox[PlusItemPos].m_Type, lpObj->pChaosBox[PlusItemPos].m_Option1, lpObj->pChaosBox[PlusItemPos].m_Option2,
			lpObj->pChaosBox[PlusItemPos].m_Option3, lpObj->pChaosBox[PlusItemPos].m_NewOption, 
			lpObj->pChaosBox[PlusItemPos].m_SetOption, lpObj->pChaosBox[PlusItemPos].m_ItemOptionEx, SocketOption, SocketIndex, CURRENT_DB_VERSION);

		Item.m_Number = lpObj->pChaosBox[PlusItemPos].m_Number;

		ItemByteConvert(pMsg.ItemInfo, Item);
		this->ChaosBoxInit(lpObj);
		::gObjChaosBoxInsertItemPos(lpObj->m_Index, Item, 0, -1);
		gObjChaosItemSet(lpObj->m_Index, 0, 1);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		if ( btItemLuckValue )
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Success %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate+5, lpObj->Money,
				lpObj->ChaosMoney, Item.m_Level, iCharmOfLuckCount);
		}
		else
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Success %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
				lpObj->ChaosMoney, Item.m_Level, iCharmOfLuckCount);
		}
	}
	else
	{
		int FailLevel = lpObj->pChaosBox[PlusItemPos].m_Level+1;

		if(iCharmOfAssemblyCount != 0)
		{
			this->BreakItemOption(lpObj);
			GCUserChaosBoxSend(lpObj, 0);
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		}
		else
		{
			this->ChaosBoxInit(lpObj);
			GCUserChaosBoxSend(lpObj, 0);
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		}

		if ( btItemLuckValue )
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Fail %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate+5, lpObj->Money,
				lpObj->ChaosMoney, FailLevel, iCharmOfLuckCount);
		}
		else
		{
			LogAddTD("[PlusItemLevel] [%s][%s] CBMix Fail %d Money : %d-%d [%d], CharmRate : %d",
				lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
				lpObj->ChaosMoney, FailLevel, iCharmOfLuckCount);
		}
	}

	lpObj->ChaosLock = FALSE;
	return TRUE;
}

//
void CMixSystem::BreakItemOption(LPOBJ lpObj)
{
	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			lpObj->pChaosBox[n].m_Level = 0;

			int iItemCode = lpObj->pChaosBox[n].m_Type;

			if(this->IsMixPossibleItem(iItemCode) == TRUE)
			{
				lpObj->pChaosBox[n].Clear();
				lpObj->pChaosBoxMap[n] = -1;
			}
		}
	}
}

BOOL CMixSystem::IsMixPossibleItem(int iItemCode) //005B1CE0
{
	switch(iItemCode)
	{
	case ITEMGET(14,53):
	case ITEMGET(12,15):
	case ITEMGET(14,13):
	case ITEMGET(14,14):
	case ITEMGET(14,96):
		return TRUE;
	}

	return FALSE;
}


BOOL CMixSystem::PegasiaChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int UniriaCount = 0;
	int ChoasGemCount = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,2) && lpObj->pChaosBox[n].m_Durability == 255.0f )	// Uniria
			{
				UniriaCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos Gem
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
		}
	}

	if ( UniriaCount != 10 || ChoasGemCount != 1 )
	{
		lpObj->ChaosLock = FALSE;
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		return 0;
	}

	int nChaosNeedMoney = 500000;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	LogChaosItem(lpObj, "DinorantMix");
	LogAddTD("[DinorantMix] Chaos Mix Start");
	//int ExDinorantMixRate = GetPrivateProfileInt("ChaosMix","DinorantMixRate",70,"..\\ExTeam\\CommonServer.ini");
	lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExDinorantMixRate;	// Succes Rate for Dinorant
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money -= nChaosNeedMoney;

	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		int Dinorant = ITEMGET(13,3);
		int Option3 = 0;

		if ( (rand()% 100) < 30 )
		{
			Option3 = 1 <<  ((rand()%3)) ;

			if ( (rand()%5) == 0 )
			{
				Option3 |= 1 << (rand()%3);
			}
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Dinorant, 0, 255, 1, 0, (BYTE)Option3, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[DinorantMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		return TRUE;
	}
	else
	{
		this->ChaosBoxInit(lpObj);	// Errase Chaos Box
		GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DinorantMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
		return FALSE;
	}
}

BOOL CMixSystem::CircleChaosMix(LPOBJ lpObj)	// Fruits
{
	lpObj->ChaosLock = TRUE;

	int CreatureGemCount = 0;
	int ChoasGemCount = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )	// Jewel of Creation
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos Gem
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
		}
	}

	if ( CreatureGemCount != 1 || ChoasGemCount != 1 )
	{
		return FALSE;
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		return 1;
	}

	if ( lpObj->Level < 10 )
	{
		pMsg.Result = CB_LOW_LEVEL_USER;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	int nChaosNeedMoney = 3000000;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	LogChaosItem(lpObj, "CircleMix");
	LogAddTD("[CircleMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = 90;	// Succes Rate for Fruit
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money -= nChaosNeedMoney;

	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100 ) < lpObj->ChaosSuccessRate )
	{
		int Fruit = ITEMGET(13,15);	// Fruit
		int FruitType;
		int RandonValue = rand() % 100;

		if ( RandonValue < 30 )
		{
			FruitType = 0;
		}
		else if ( RandonValue < 55 )
		{
			FruitType = 1;
		}
		else if ( RandonValue < 75 )
		{
			FruitType = 2;
		}
		else if ( RandonValue < 95 )
		{
			FruitType = 3;
		}
		else
		{
			FruitType = 4;
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, Fruit, (BYTE)FruitType, 255, 1, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[CircleMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

		return TRUE;
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[CircleMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;

		return FALSE;
	}
}

BOOL CMixSystem::WingChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int WingCount = 0;
	int ChoasGemCount = 0;
	int LokesFeathersCount = 0;
	int WingIndex = -1;
	int iChaosMoney = 0;
	int WingCharmItemNum = -1; //season4.5 add-on
	int iWingChaosMoney = 0;
	int iSleeveOfLord = 0;
	int iCharmOfLuckCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( (lpObj->pChaosBox[n].m_Type >= ITEMGET(12,3) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,6)) || lpObj->pChaosBox[n].m_Type == ITEMGET(12,42) || lpObj->pChaosBox[n].m_Type == ITEMGET(14,30) )	
			{
				lpObj->ChaosLock = FALSE;

				return FALSE;
			}
			if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(12,0) && lpObj->pChaosBox[n].m_Type <= ITEMGET(12,2) ) 
			{
				WingCount++;
				WingIndex = n;
				iWingChaosMoney = lpObj->pChaosBox[n].m_BuyMoney;
			}
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,41) ) //season3 add-on
			{
				WingCount++;
				WingIndex = n;
				iWingChaosMoney = lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) ) // Chaos
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,14) ) // Feather
			{
				if ( lpObj->pChaosBox[n].m_Level == 0 ) // Feather
				{
					LokesFeathersCount++;
				}
				else
				{
					iSleeveOfLord ++;
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else if(lpObj->pChaosBox[n].m_Type == ITEMGET(13,88) || //season4.5 add-on
					lpObj->pChaosBox[n].m_Type == ITEMGET(13,89) ||
					lpObj->pChaosBox[n].m_Type == ITEMGET(13,90) ||
					lpObj->pChaosBox[n].m_Type == ITEMGET(13,91) ||
					lpObj->pChaosBox[n].m_Type == ITEMGET(13,92) )
			{
				WingCharmItemNum = lpObj->pChaosBox[n].m_Type;
			}
			else if ( lpObj->pChaosBox[n].IsExtItem() != FALSE )
			{
				if ( lpObj->pChaosBox[n].m_Level >= 4 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
		}
	}

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if ( iSleeveOfLord == 1 )
	{
		if ( WingCount != 1 || ChoasGemCount != 1 || LokesFeathersCount != 0 )
		{
			lpObj->ChaosLock = FALSE;
			pMsg.Result = CB_INCORRECT_MIX_ITEMS;
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			return FALSE;
		}
	}
	else if ( LokesFeathersCount == 1 )
	{
		if ( WingCount != 1 || ChoasGemCount != 1 || iSleeveOfLord != 0 )
		{
			pMsg.Result = CB_INCORRECT_MIX_ITEMS;
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;

			return FALSE;
		}
	}
	else
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		return FALSE;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		lpObj->ChaosLock = FALSE;
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	}

	int nChaosNeedMoney = 5000000;
	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return TRUE;
	}

	CItem * pWing = &lpObj->pChaosBox[WingIndex];
	lpObj->ChaosSuccessRate = (DWORD)((DWORD)iWingChaosMoney / (DWORD)4000000);
	lpObj->ChaosSuccessRate += iChaosMoney / 40000;

	if ( lpObj->ChaosSuccessRate < 0 ) //season 2.5 fix
	{
		lpObj->ChaosSuccessRate =  100;
	}

	if ( lpObj->ChaosSuccessRate == 0 )
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return FALSE;
	}

	LogChaosItem(lpObj, "WingMix,2");
	LogAddTD("[WingMix,2] Chaos Mix Start");
	//int ExWing2MaxSuccessRate = GetPrivateProfileInt("ChaosMix","Wing2MaxSuccessRate",90,"..\\ExTeam\\CommonServer.ini");
	if(lpObj->ChaosSuccessRate > ExConfig.CommonServer.ExWing2MaxSuccessRate)
	{
		lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExWing2MaxSuccessRate;
	}

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	lpObj->Money  -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int iWingLevel = 0;
		int iItemType;
		int iItemSubType;

		if ( iSleeveOfLord != 0 )
		{
			iItemType = 13;
			iItemSubType = 30;
		}
		else
		{
			iItemType = 12;

			int iRand = rand()%5;

			if(iRand == 4)
			{
				iItemSubType = 42;
			}
			else
			{
				iItemSubType = iRand + 3;
			}
		}

		if(WingCharmItemNum > -1) //season4.5 add-on
		{
			int WingCharmIndex = WingCharmItemNum ^ ITEMGET(13,0);

			switch(WingCharmIndex)
			{
			case 88:
				iItemSubType = 5;
				break;
			case 89:
				iItemSubType = 4;
				break;
			case 90:
				iItemSubType = 3;
				break;
			case 91:
				iItemSubType = 42;
				break;
			case 92:
				iItemSubType = 6;
				break;
			default:
				LogAddTD("[MixSystem][WingChaosMix] WingCharmItemNum => %d , WingCharmIndex => %d", WingCharmItemNum, WingCharmIndex);
			}
		}

		int iWingNum = ITEMGET(iItemType, iItemSubType);
		int iOption1 = 0;
		int iOption2 = 0;
		int iOption3 = 0;

		if ( (rand()%5) == 0 )
		{
			iOption1 = 1;
		}

		int iRandomValue = rand() % 100;
		int iRandomValue2 = rand() % 3;

		switch ( iRandomValue2 )
		{
			case 0:
				if ( iRandomValue < 4 )
				{
					iOption2 = 3;	// +12
				}
				break;

			case 1:
				if ( iRandomValue < 10 )
				{
					iOption2 = 2;	// +8
				}
				break;

			case 2:
				if ( iRandomValue < 20 )
				{
					iOption2 = 1;	// +4;
				}
		}

		if ( iSleeveOfLord != FALSE )
		{
			if ( (rand()%5) == 0 )
			{
				iOption3 = 1 << (rand()%4);
			}
				iOption3 |= 0x20;
		}
		else
		{
			if ( (rand()%5) == 0 )
			{
				iOption3 = 1 << (rand()%3);
			}

			if ( (rand()%2) != 0 )
			{
				iOption3 |= 0x20;
			}
		
		}

		::ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, iWingNum, (BYTE)iWingLevel, 0, 0, (BYTE)iOption1, (BYTE)iOption2, -1, (BYTE)iOption3, 0);
		::gObjInventoryCommit(lpObj->m_Index);
		::LogAddTD("[WingMix,2] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		return TRUE;
	}
	else
	{
		for (int n=0;n<CHAOS_BOX_SIZE;n++)
		{
			lpObj->pChaosBox[n].Clear();
		}

		GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		::LogAddTD("[WingMix,2] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
		return FALSE;
	}
}

void CMixSystem::BloodCastleItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	
	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	int aIndex = lpObj->m_Index;

	int iRET_VAL = g_BloodCastle.CheckChoasMixItem(aIndex);

	int iMapNumber = g_BloodCastle.GetBridgeMapNumber(iRET_VAL-1);

	if ( BC_MAP_RANGE(iMapNumber) != FALSE )
	{
		if ( g_BloodCastle.BloodCastleChaosMix(aIndex, iRET_VAL) == false )
		{
			lpObj->ChaosLock = FALSE;
		}
		return;
	}

	switch ( iRET_VAL )
	{
		case 9:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 10:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 11:
			pMsg.Result = CB_NO_BC_CORRECT_ITEMS;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 12:
			pMsg.Result = CB_INVALID_ITEM_LEVEL;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 13:
			pMsg.Result = CB_BC_NOT_ENOUGH_ZEN;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;

		case 14:
			pMsg.Result = CB_USER_CLASS_LOW_LEVEL;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->m_Index;
			lpObj->ChaosLock = FALSE;
			break;
		case 15:
			pMsg.Result = 0xF0;
			DataSend(aIndex, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
			break;
		default:
			lpObj->ChaosLock = FALSE;
	}

}

void CMixSystem::DarkHorseChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int CreatureGemCount = 0;
	int SoulOfDarkHorse = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int iCharmOfLuckCount = 0;
	int iInvalidItemCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,31) && lpObj->pChaosBox[n].m_Level == 0 )
			{
				SoulOfDarkHorse++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
			

		}
	}

	if ( ChoasGemCount != 1 || BlessGemCount != 5 || SoulGemCount != 5 || CreatureGemCount != 1 || SoulOfDarkHorse != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return ;
	}

	LogChaosItem(lpObj, "DarkHorseMix");
	LogAddTD("[DarkHorseMix] Chaos Mix Start");
	//int ExDarkHorseMixSuccessRate = GetPrivateProfileInt("ChaosMix","DarkHorseMixSuccessRate",60,"..\\ExTeam\\CommonServer.ini");
	lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExDarkHorseMixSuccessRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int nChaosNeedMoney = 5000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int Level = 0;
		int ItemType = 13;
		int ItemSubType = 4;
		int ItemNum = ITEMGET(ItemType, ItemSubType);
		int Option1 = 0;
		int Option2 = 0;
		int Option3 = 0;

		int Add = 0;

		if ( (rand()%100) < (lpObj->ChaosSuccessRate/5+6) )
		{
			Add = 1;
		}

		if ( (rand()%5) == 0 )
		{
			Option1 = 1;
		}

		int lc22 = rand()%100;	
		int lc23 = rand()%3;

		switch ( lc23 )
		{
			case 0:
				if ( lc22 <  4 )
				{
					Option2 = 3;
				}
				break;

			case 1:
				if ( lc22 <  10 )
				{
					Option2 = 2;
				}
				break;

			case 2:
				if ( lc22 <  20 )
				{
					Option2 = 1;
				}
				break;
		}

		::PetItemSerialCreateSend(lpObj->m_Index, -2, 0, 0, ItemNum, Level, 0,Add,  Option1, Option2, -1, 0, 0); 
		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[DarkHorseMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DarkHorseMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::DarkSpiritChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int CreatureGemCount = 0;
	int SoulOfSpirit = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	int iCharmOfLuckCount = 0;
	int iInvalidItemCount = 0;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )
			{
				CreatureGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,31) && lpObj->pChaosBox[n].m_Level == 1 )
			{
				SoulOfSpirit++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( ChoasGemCount != 1 || BlessGemCount != 2 || SoulGemCount != 2 || CreatureGemCount != 1 || SoulOfSpirit != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return ;
	}

	LogChaosItem(lpObj, "DarkSpiritMix");
	LogAddTD("[DarkSpiritMix] Chaos Mix Start");
	//int ExDarkSpiritMixSuccessRate = GetPrivateProfileInt("ChaosMix","DarkSpiritMixSuccessRate",60,"..\\ExTeam\\CommonServer.ini");
	lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExDarkSpiritMixSuccessRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	int nChaosNeedMoney = 1000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int Level = 0;
		int ItemType = 13;
		int ItemSubType = 5;
		int ItemNum = ITEMGET(ItemType, ItemSubType);
		int Option1 = 0;
		int Option2 = 0;
		int Option3 = 0;

		int Add = 0;

		if ( (rand()%100) < (lpObj->ChaosSuccessRate/5+6) )
		{
			Add = 1;
		}

		if ( (rand()%5) == 0 )
		{
			Option1 = 1;
		}

		int lc22 = rand()%100;	
		int lc23 = rand()%3;

		switch ( lc23 )
		{
			case 0:
				if ( lc22 <  4 )
				{
					Option2 = 3;
				}
				break;

			case 1:
				if ( lc22 <  10 )
				{
					Option2 = 2;
				}
				break;

			case 2:
				if ( lc22 <  20 )
				{
					Option2 = 1;
				}
				break;
		}

		::PetItemSerialCreateSend(lpObj->m_Index, -2, 0, 0, ItemNum, Level, 0, Add, Option1, Option2, -1, 0, 0); 
		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[DarkSpiritMix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[DarkSpiritMix] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::BlessPotionChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iBlessGemCount = 0; //loc2
	int iChaosMoney = 0; //loc3
	int iInvalidItemCount = 0; //loc4

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc8
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				iBlessGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if(iBlessGemCount == 0)
	{
		return;
	}

	if(iInvalidItemCount > 0)
	{
		return;
	}

	if ( iBlessGemCount == 0 || iInvalidItemCount > 0)
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if ( iBlessGemCount > 25 )
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "BlessPotionMix");
	LogAddTD("[BlessPotionMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = 100;

	int nChaosNeedMoney = 100000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int ItemNum = ITEMGET(14,7);
		int Level = 0;
		int Dur = iBlessGemCount * 10;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, (BYTE)Level, (BYTE)Dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::SoulPotionChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iSoulGemCount = 0;
	int iChaosMoney = 0;
	int iInvalidItemCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				iSoulGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iSoulGemCount == 0 )
		return;

	if ( iInvalidItemCount > 0 )
		return;

	if ( iSoulGemCount > 25 )
	{
		MsgOutput(lpObj->m_Index, lMsg.Get(MSGGET(6,201)));
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "SoulPotionMix");
	LogAddTD("[SoulPotionMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = 100;

	int nChaosNeedMoney = 50000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int ItemNum = ITEMGET(14,7);
		int Level = 1;
		int Dur = iSoulGemCount * 10;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, (BYTE)Level, (BYTE)Dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[BlessPotionMix] [%s][%s] CBMix Success %d Money : %d-%d",	// #error Change to SoulPotionMix
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[SoulPotionMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::LifeStoneChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iChoasGemCount = 0;
	int iBlessGemCount = 0;
	int iSoulGemCount = 0;
	int iProtectionGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				iBlessGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				iSoulGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,31) )	// Guardian Jewel
			{
				iProtectionGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )	// Habla pe super CHOAS
			{
				iChoasGemCount++;
			}
			else 
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iChoasGemCount != 1 || iBlessGemCount != 5 || iSoulGemCount != 5 || iProtectionGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "LifeStoneMix");
	LogAddTD("[LifeStoneMix] Chaos Mix Start");
	lpObj->ChaosSuccessRate = 100;

	int nChaosNeedMoney = 5000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(13,11) , 1, 0, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[LifeStoneMix] [%s][%s] CBMix Success %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[LifeStoneMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, 
			lpObj->Money, nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}

//GS-CS Here
void CMixSystem::CastleSpecialItemMix(LPOBJ lpObj) //Identical
{
	lpObj->ChaosLock = TRUE;

	int iDefendGemCount = 0;
	int iBlessGemMixCount = 0;
	int iSoulGemMixCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if( g_CastleSiegeSync.CheckCastleOwnerMember(lpObj->m_Index)  )
	{
		if( lpObj->GuildStatus != GUILD_MASTER )
		{
			LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - No Auth( Not GuildMaster )",
				lpObj->AccountID, lpObj->Name);

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			lpObj->ChaosLock = FALSE;

			return;
		}
	}
	else
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - No Auth",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;

		return;	
	}

	if( g_iCastleItemMixLimit <= 0 )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Mix Count Limit Over",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;

		return;		
	}

	for( int n = 0; n < CHAOS_BOX_SIZE; n++ )
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,30) )
			{
				iBlessGemMixCount += lpObj->pChaosBox[n].m_Level + 1;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(12,31) )
			{
				iSoulGemMixCount += lpObj->pChaosBox[n].m_Level + 1;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,31) )
			{
				iDefendGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if( iBlessGemMixCount != 3 || iSoulGemMixCount != 3 || iDefendGemCount != 30 || iInvalidItemCount > 0 )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Item Error (DG:%d, BGx10:%d, SGx10:%d, Other:%d)",
			lpObj->AccountID, lpObj->Name, iBlessGemMixCount, iSoulGemMixCount, iDefendGemCount, iInvalidItemCount);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;

		return;	
	}

	LogChaosItem(lpObj, "Castle Special Mix");
	LogAddTD("[CastleSpecialMix] [%s][%s] Chaos Mix Start", lpObj->AccountID, lpObj->Name);

	lpObj->ChaosSuccessRate = 100;

	int nChaosNeedMoney = 1000000000;

	if( lpObj->Money < nChaosNeedMoney )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Mix Failed - Lack of Money (%d/%d)",
			lpObj->AccountID, lpObj->Name, lpObj->Money, nChaosNeedMoney);

		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;

		return;	
	}

	CItem objTempItem;

	int iPickLoopCount = 500; //HermeX Fix
	bool bItemPickSuccess = false;
	int nItemIndex;

	while( iPickLoopCount-- )
	{
		if( CastleItemMixItemBag->PickItem(objTempItem, nItemIndex) == FALSE )
		{
			LogAddTD("[CastleSpecialMix] [%s][%s] Item Pick Failed - Data Error",
				lpObj->AccountID, lpObj->Name);

			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

			lpObj->ChaosLock = FALSE;

			return;
		}
		
		int iRand = CastleItemMixItemBag->GetMinLevel(nItemIndex);
		
		if( iRand < rand() % 100 )
		{
			bItemPickSuccess = true;

			break;
		}
	}

	if( bItemPickSuccess == false )
	{
		LogAddTD("[CastleSpecialMix] [%s][%s] Item Pick Failed - Loop Count Over",
			lpObj->AccountID, lpObj->Name);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		lpObj->ChaosLock = FALSE;

		return;
	}

	objTempItem.m_Level = 0;

	if( objTempItem.m_NewOption )
	{
		objTempItem.m_NewOption = 0;

		int iOptionLoop = (rand()%3) + 2;

		while( iOptionLoop )
		{
			int iRandOp = rand()%6;

			BYTE btOption = 1 << iRandOp; 

			if( (objTempItem.m_NewOption & btOption) == 0 )
			{
				objTempItem.m_NewOption |= btOption;
				iOptionLoop--; //HermeX Fix
			}
					
		}
		objTempItem.m_Option1 = 1;

		if( (rand()%100) < 20 )
		{
			objTempItem.m_Option2 = 1;
		}
		else
		{
			objTempItem.m_Option2 = 0;
		}
	}
	else
	{
		objTempItem.m_Option2 = 1;
	}

	objTempItem.m_Durability = ItemGetDurability(objTempItem.m_Type, objTempItem.m_Level, objTempItem.m_NewOption, 0);

	lpObj->Money -= nChaosNeedMoney;

	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		ItemSerialCreateSend(lpObj->m_Index, 255, 0, 0, objTempItem.m_Type,	(BYTE)objTempItem.m_Level, (BYTE)objTempItem.m_Durability, (BYTE)objTempItem.m_Option1, (BYTE)objTempItem.m_Option2, (BYTE)objTempItem.m_Option3, -1, (BYTE)objTempItem.m_NewOption, 0);
		gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[CastleSpecialMix] [%s][%s] CBMix Success %d Money : %d-%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney);
		g_iCastleItemMixLimit--;
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[CastleSpecialMix] [%s][%s] CBMix Fail %d Money : %d-%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney);
		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::HiddenTreasureBoxItemMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iBlueCrystal = 0;
	int iRedCrystal = 0;
	int iBlackCrystal = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,26) )
			{
				switch ( lpObj->pChaosBox[n].m_Level )
				{
					case 1:
						iRedCrystal++;
						break;
					case 2:
						iBlueCrystal++;
						break;
					case 3:
						iBlackCrystal++;
						break;
				}
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	int iCrystalMixType = -1;

	if ( iInvalidItemCount == 0 )
	{
		if ( iBlueCrystal == 7 )
		{
			if ( iRedCrystal == 0 && iBlackCrystal == 0 )
			{
				iCrystalMixType = 0;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iRedCrystal == 5 )
		{
			if ( iBlueCrystal == 0 && iBlackCrystal == 0 )
			{
				iCrystalMixType = 1;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iBlackCrystal == 3 )
		{
			if ( iRedCrystal == 0 && iBlueCrystal == 0 )
			{
				iCrystalMixType = 2;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else if ( iBlueCrystal == 1 && iRedCrystal == 1 && iBlackCrystal == 1 )
		{
			{
				iCrystalMixType = 3;
				lpObj->ChaosSuccessRate = 100;
			}
		}
		else
		{
			LogAddTD("[Hidden TreasureBox Event] [%s][%s] Item Mix Failed",	lpObj->AccountID, lpObj->Name);
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			lpObj->ChaosLock = FALSE;
		}
	}
	else
	{
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] Item Mix Failed",	lpObj->AccountID, lpObj->Name);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "Hidden TreasureBox Mix");
	LogAddTD("[Hidden TreasureBox Event] [%s][%s] Chaos Mix Start", lpObj->AccountID, lpObj->Name);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		switch ( iCrystalMixType )
		{
			case 0:	case 1:	case 2:
				ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 4, 1, 0, 0, 0, -1, 0, 0);
				break;
			case 3:
				ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(12,26) , 5, 1, 0, 0, 0, -1, 0, 0);
				break;
			default:
				LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Failed - iCrystalMixType is wrong : %d",
					lpObj->AccountID, lpObj->Name, iCrystalMixType);
				DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;
				return;
		}

		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Success:%d Type:%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, iCrystalMixType);
	}
	else
	{
		LogAddTD("[Hidden TreasureBox Event] [%s][%s] CBMix Fail Rate:%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate);
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 1);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
	}

	lpObj->ChaosLock = FALSE;
}

void CMixSystem::Fenrir_01Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iStuffCount_02 = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,32) )
			{
				iStuffCount_01 += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,33) )
			{
				iStuffCount_02 += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 20 || iStuffCount_02 != 20 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "Fenrir_01Level_Mix");
	LogAddTD("[Fenrir Mix][Level 01] Chaos Mix Start");

	lpObj->ChaosSuccessRate = g_iFenrir_01Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 0;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,35);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , (BYTE)level, (BYTE)dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[Fenrir Mix][Level 01] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);

	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		LogAddTD("[Fenrir Mix][Level 01] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney, iCharmOfLuckCount);
		lpObj->ChaosLock = FALSE;
	}
}


void CMixSystem::Fenrir_02Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iStuffCount_02 = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,34) )
			{
				iStuffCount_01 += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,35) )
			{
				iStuffCount_02 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 10 || iStuffCount_02 != 5 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_02Level_Mix");
	LogAddTD("[Fenrir Mix][Level 02] Chaos Mix Start");

	lpObj->ChaosSuccessRate = g_iFenrir_02Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 0;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,36);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , (BYTE)level, (BYTE)dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::Fenrir_03Level_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iLifeGemCount = 0;
	int iChaosGemCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,36) )
			{
				iStuffCount_01 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iLifeGemCount ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 1 || iLifeGemCount != 3 || iChaosGemCount != 1 || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_03Level_Mix");
	LogAddTD("[Fenrir Mix][Level 03] Chaos Mix Start");

	lpObj->ChaosSuccessRate = g_iFenrir_03Level_MixRate;
	lpObj->ChaosSuccessRate += iCharmOfLuckCount;
	int nChaosNeedMoney = 10000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,37);
		int level = 0;
		int dur = 255;
		int op1 = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , (BYTE)level, (BYTE)dur, (BYTE)op1, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 03] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 03] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::Fenrir_04Upgrade_Mix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	int iStuffCount_01 = 0;
	int iLifeGemCount = 0;
	int iChaosGemCount = 0;
	int iAttackStuffCount = 0;
	int iDefendStuffCount = 0;
	int iAttackStuffPrice = 0;
	int iDefendStuffPrice = 0;
	int iInvalidItemCount = 0;
	int iChaosMoney = 0;
	BOOL bFenrirDamageInc = FALSE;
	BOOL bFenrirDamageDec = FALSE;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(13,37) )
			{
				iStuffCount_01 ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iLifeGemCount ++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChaosGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(0,0) &&
					  lpObj->pChaosBox[n].m_Type < ITEMGET(6,0) &&
					  lpObj->pChaosBox[n].m_Level >= 4 &&
					  lpObj->pChaosBox[n].m_Option3 >= 1)
			{
				iAttackStuffCount++;
				iAttackStuffPrice += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type >= ITEMGET(6,0) &&
					  lpObj->pChaosBox[n].m_Type < ITEMGET(12,0) &&
					  lpObj->pChaosBox[n].m_Level >= 4 &&
					  lpObj->pChaosBox[n].m_Option3 >= 1)
			{
				iDefendStuffCount++;
				iDefendStuffPrice += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iStuffCount_01 != 1 || iLifeGemCount != 5 || iChaosGemCount != 1 || ( iAttackStuffCount == 0 && iDefendStuffCount == 0 ) || iInvalidItemCount > 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}
	
	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iAttackStuffCount > 0 )
	{
		bFenrirDamageInc = TRUE;
		iChaosMoney = iAttackStuffPrice;
	}

	if ( iDefendStuffCount > 0 )
	{
		bFenrirDamageDec = TRUE;
		iChaosMoney = iDefendStuffPrice;
	}

	if ( bFenrirDamageInc && bFenrirDamageDec )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( !bFenrirDamageInc && !bFenrirDamageDec )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	LogChaosItem(lpObj, "Fenrir_04Level_Mix");
	LogAddTD("[Fenrir Mix][Level 04] Chaos Mix Start");

	int nChaosNeedMoney = 10000000;

	int iChaosTaxMoney = (int)((__int64)nChaosNeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	nChaosNeedMoney += iChaosTaxMoney;

	if ( nChaosNeedMoney < 0 )
	{
		nChaosNeedMoney = 0;
	}

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( iChaosMoney > 1000000 )
		iChaosMoney = 1000000;

	lpObj->ChaosSuccessRate = iChaosMoney * 100 / 1000000;

	if ( lpObj->ChaosSuccessRate > 79 )
		lpObj->ChaosSuccessRate = 79;

	lpObj->ChaosSuccessRate += iCharmOfLuckCount;

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,37);
		int level = 0;
		int dur = 255;
		int op1 = 1;
		int nop = 0;

		if ( bFenrirDamageInc )
		{
			nop |= 1;
		}

		if ( bFenrirDamageDec )
		{
			nop |= 2;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , (BYTE)level, (BYTE)dur, (BYTE)op1, 0, 0, -1, (BYTE)nop, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[Fenrir Mix][Level 04] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[Fenrir Mix][Level 04] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, nChaosNeedMoney,
			iCharmOfLuckCount);

		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::ShieldPotionLv1_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	if ( g_ShieldSystemOn == FALSE )
		return;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,3) )
			{
				iHealthPotionCount+=(int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = g_iShieldPotionLv1MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv1 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv1 Mix] - Mix Start");
	
	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate < g_iShieldPotionLv1MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,35);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv1 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv1 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	g_iShieldPotionLv1MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}

void CMixSystem::ShieldPotionLv2_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,38) )
			{
				iHealthPotionCount+=(int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = g_iShieldPotionLv2MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	
	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv2 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv2 Mix] - Mix Start");

	GCMoneySend(lpObj->m_Index, lpObj->Money);
	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate < g_iShieldPotionLv2MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,36);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv2 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv2 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	g_iShieldPotionLv2MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}

void CMixSystem::ShieldPotionLv3_Mix(LPOBJ lpObj)
{
	int iHealthPotionCount = 0;
	int iInvalidItemCount = 0;
	int iChaosMixPrice = 0;
	int iCharmOfLuckCount = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,39) )
			{
				iHealthPotionCount+=(int)lpObj->pChaosBox[n].m_Durability;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )	// Charm Of Luck
			{
				iCharmOfLuckCount += (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iHealthPotionCount != 3 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	if ( iCharmOfLuckCount > 10 )
	{
		pMsg.Result = 0xF0;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	iChaosMixPrice = g_iShieldPotionLv3MixMoney;
	int iChaosTaxMoney = iChaosMixPrice * g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / 100;

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iChaosMixPrice += iChaosTaxMoney;

	if ( iChaosMixPrice < 0 )
	{
		iChaosMixPrice = 0;
	}

	if ( lpObj->Money < iChaosMixPrice )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= iChaosMixPrice;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	
	LogChaosItem(lpObj, "PotionMix][ShieldPotion Lv3 Mix");
	LogAddTD("[PotionMix][ShieldPotion Lv3 Mix] - Mix Start");

	int iRate = rand() % 100;
	iRate -= iCharmOfLuckCount;

	if ( iRate < g_iShieldPotionLv3MixSuccessRate )
	{
		int ItemNum = ITEMGET(14,37);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemNum, 0, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ChaosMix][Shield Potion] Lv3 Potion Mix Success [%s][%s], Money(%d-%d), CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ChaosMix][Shield Potion] Lv3 Potion Mix [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, 	g_iShieldPotionLv3MixSuccessRate,
			lpObj->Money, iChaosMixPrice, iCharmOfLuckCount);
	}

	lpObj->ChaosLock = FALSE;
}

//005D8310   /> \55                            PUSH EBP
BOOL CMixSystem::IsCondorItemCheck(int iItemCode) //identical gs-cs 56
{
	if(iItemCode == this->iCondorFeather || iItemCode == this->iCondorFlame)
	{
		return TRUE;
	}
	return FALSE;
}

//Identical gs-cs 56
BOOL CMixSystem::CheckLevel1WingItem(int iItemCode) //func_5d8360
{
	if( iItemCode == ITEMGET(12,0) || 
		iItemCode == ITEMGET(12,1) || 
		iItemCode == ITEMGET(12,2) ||
		iItemCode == ITEMGET(12,41)) //season3 addon
	{
		return TRUE;
	}
	return FALSE;
}

//Identical gs-cs 56
BOOL CMixSystem::CheckLevel2WingItem(int iItemCode) //func_5d83b0
{
	if( iItemCode == ITEMGET(12,3) || 
		iItemCode == ITEMGET(12,4) || 
		iItemCode == ITEMGET(12,5) ||
		iItemCode == ITEMGET(12,6) ||
		iItemCode == ITEMGET(13,30) ||
		iItemCode == ITEMGET(12,42)) //season3 addon
	{
		return TRUE;
	}
	return FALSE;
}

//func_005d8410
BOOL CMixSystem::CheckLevel3WingItem(int iItemCode)
{
	if( iItemCode == this->iWingofStorm || 
		iItemCode == this->iWingofEternal || 
		iItemCode == this->iWingofIllusion ||
		iItemCode == this->iWingofRuin ||
		iItemCode == this->iCapeofLord ||
		iItemCode == this->iWingofDimension)
	{
		return TRUE;
	}
	return FALSE;
}

//func_005d8480
BOOL CMixSystem::CheckItemCondition(CItem * lpItem, short Level, BYTE Op1, BYTE Op2, BYTE Op3, BYTE SetOption, BYTE NewOption) //identical gs-cs 56
{
	if(lpItem == NULL){return FALSE;}
	if(Level != FALSE){if(lpItem->m_Level < Level){return FALSE;}}
	if(Op1 != FALSE){if(lpItem->m_Option1 < Op1){return FALSE;}}
	if(Op2 != FALSE){if(lpItem->m_Option2 < Op2){return FALSE;}}
	if(Op3 != FALSE){if(lpItem->m_Option3 < Op3){return FALSE;}}
	if(SetOption != FALSE){if(!lpItem->m_SetOption){return FALSE;}}
	if(NewOption != FALSE){if(!lpItem->m_NewOption){return FALSE;}}
	return TRUE;
}

//func_005d85c0
void CMixSystem::ThirdWingMix1(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;
	
	int loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc14
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( this->CheckLevel2WingItem(lpObj->pChaosBox[n].m_Type) != FALSE )
			{
				if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,0) != FALSE )
				{
					loc2++;
				}
			}
			else if( this->CheckItemCondition(&lpObj->pChaosBox[n],7,0,0,1,1,0) != FALSE )
			{
				loc3++;
				loc8 += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofChaos)
			{
				loc4++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofSoul)
			{
				loc5++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofCreation)
			{
				loc6++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				loc10+= (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				loc7++;
			}
		}
	}

	if(loc10 > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(loc2 != 1 || loc3 < 1 || loc4 != 1 || loc5 != 1 || loc6 != 1 || loc7 > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel1_Mix");
	LogAddTD("[ThirdWing Mix][Level 01] Chaos Mix Start");

	if(loc8 > 0)
	{
		lpObj->ChaosSuccessRate = loc8 / 300000;
	}
	//int ExFeatherofCondorMixMaxPercent = GetPrivateProfileInt("ChaosMix","FeatherofCondorMixMaxPercent",60,"..\\ExTeam\\CommonServer.ini");
	if(lpObj->ChaosSuccessRate > ExConfig.CommonServer.ExFeatherofCondorMixMaxPercent)
	{
		lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExFeatherofCondorMixMaxPercent;
	}
	else if( lpObj->ChaosSuccessRate < 1)
	{
		lpObj->ChaosSuccessRate = 1;
	}

	loc9 = lpObj->ChaosSuccessRate * 200000;

	lpObj->ChaosSuccessRate += loc10;

	loc9 = lpObj->ChaosSuccessRate * 200000; //why double? maybe inside some if

	int iChaosTaxMoney = (int)((__int64)loc9 * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if(iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	loc9 += iChaosTaxMoney;

	if(loc9 < 0)
	{
		loc9 = 0;
	}

	if ( lpObj->Money < loc9 )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= loc9;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int type = ITEMGET(13,53);
		int level = 0;
		int dur = 1;

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, type , (BYTE)level, (BYTE)dur, 0, 0, 0, -1, 0, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ThirdWing Mix][Level 01] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,	lpObj->Money, loc9, loc10);
	}
	else
	{
		this->ThirdWingMixItemDown(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ThirdWing Mix][Level 01] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,	lpObj->Money, loc9, loc10);
		lpObj->ChaosLock = FALSE;
	}
}

//func_5d8c70
void CMixSystem::ThirdWingMix2(LPOBJ lpObj)
{	
	lpObj->ChaosLock = TRUE;
	
	int loc2 = 0;
	int loc3 = 0;
	int loc4 = 0;
	int loc5 = 0;
	int loc6 = 0;
	int loc7 = 0;
	int loc8 = 0;
	int loc9 = 0;
	int loc10 = 0;
	int loc11 = 0;
	int loc12 = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc16
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( this->CheckItemCondition(&lpObj->pChaosBox[n],7,0,0,1,0,1) != FALSE )
			{
				loc2++;
				loc10 += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iCondorFeather)
			{
				loc3++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iCondorFlame)
			{
				loc4++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofChaos)
			{
				loc5++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofBless)
			{
				loc7++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofSoul)
			{
				loc6++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofCreation)
			{
				loc8++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				loc12+= (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				loc9++;
			}
		}
	}

	if(loc12 > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(loc2 < 1 || loc3 != 1 || loc4 != 1 || loc5 != 1 || loc7 != 1 || loc6 != 1 || loc8 != 1 || loc9 > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel2_Mix");
	LogAddTD("[ThirdWing Mix][Level 02] Chaos Mix Start");

	if(loc10 > 0)
	{
		lpObj->ChaosSuccessRate = loc10 / 3000000;
	}
	//int ExWingLv3MixMaxPercent = GetPrivateProfileInt("ChaosMix","WingLv3MixMaxPercent",40,"..\\ExTeam\\CommonServer.ini");
	if(lpObj->ChaosSuccessRate > ExConfig.CommonServer.ExWingLv3MixMaxPercent)
	{
		lpObj->ChaosSuccessRate = ExConfig.CommonServer.ExWingLv3MixMaxPercent;
	}
	else if( lpObj->ChaosSuccessRate < 1)
	{
		lpObj->ChaosSuccessRate = 1;
	}

	loc11 = lpObj->ChaosSuccessRate * 200000;

	lpObj->ChaosSuccessRate += loc12;

	loc11 = lpObj->ChaosSuccessRate * 200000;

	int iChaosTaxMoney = (int)((__int64)loc11 * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if(iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	loc11 += iChaosTaxMoney;

	if(loc11 < 0)
	{
		loc11 = 0;
	}

	if ( lpObj->Money < loc11 )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= loc11;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		int loc18 = rand()%6;
		int loc19 = 0;

		if(loc18 == 0)
		{
			loc19 = this->iWingofStorm;
		}
		else if( loc18 == 1)
		{
			loc19 = this->iWingofEternal;
		}
		else if( loc18 == 2)
		{
			loc19 = this->iWingofIllusion;
		}
		else if( loc18 == 3)
		{
			loc19 = this->iWingofRuin;
		}
		else if( loc18 == 4)
		{
			loc19 = this->iCapeofLord;
		}
		else if( loc18 == 5)
		{
			loc19 = this->iWingofDimension;
		}

		int loc20 = 0;
		int loc21 = 0;
		
		if( (rand()%1000) <= this->i3rdWingLuckRate )
		{
			loc21 = 1;
		}

		int loc22 = 0;
		int loc23 = 0;
		int loc24 = rand()%2;
		int loc25;
		int loc26;
		int loc27;
		int loc28;
		int loc29;

		switch ( loc24 )
		{
			case 0:
				loc25 = rand()%1000;
				if(loc25 < 400)
				{
					loc23 |= 0x10;
				}
				break;

			case 1:
				loc25 = rand()%1000;
				if(loc24 < 300)
				{
					loc23 |= 0x20;
				}
				break;
		}

		loc26 = rand()%4;
		loc27 = rand()%1000;
		loc22 = 0;

		switch( loc26 )
		{
			case 1:
				{
					if(loc27 < 120)
					{
						loc22 = 1;
					}
				}
				break;

			case 2:
				{
					if(loc27 < 60)
					{
						loc22 = 2;
					}
				}
				break;

			case 3:
				{
					if(loc27 < 30)
					{
						loc22 = 3;
					}
				}
				break;
		}

		loc28 = rand()%4;
		loc29 = rand()%1000;

		switch( loc28 )
		{
			case 0:
				{
					if(loc29 < 40)
					{
						loc23 |= 1;
					}
				}
				break;
			case 1:
				{
					if(loc29 < 20)
					{
						loc23 |= 2;
					}
				}
				break;

			case 2:
				{
					if(loc29 < 70)
					{
						loc23 |= 4;
					}
				}
				break;
			case 3:
				{
					if(loc29 < 70)
					{
						loc23 |= 8;
					}
				}
				break;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, loc19 , 0, 0, (BYTE)loc20, (BYTE)loc21, (BYTE)loc22, -1, (BYTE)loc23, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[ThirdWing Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,	lpObj->Money, loc11, loc12);
	}
	else
	{
		this->ThirdWingMixItemDown(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[ThirdWing Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,	lpObj->Money, loc11, loc12);
		lpObj->ChaosLock = FALSE;
	}
}

//005D95E0   /> \55                            PUSH EBP
void CMixSystem::ThirdWingMixItemDown(LPOBJ lpObj)
{
	if(lpObj->pChaosBox == NULL)
	{
		return;
	}

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc2
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if(CheckLevel2WingItem(lpObj->pChaosBox[n].m_Type) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else if(CheckItemCondition(&lpObj->pChaosBox[n], 0,0,0,0,1,0) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else if(CheckItemCondition(&lpObj->pChaosBox[n], 0,0,0,0,0,1) != FALSE)
			{
				ThirdWingMixItemDown2(&lpObj->pChaosBox[n]);
			}
			else
			{
				lpObj->pChaosBox[n].Clear();
			}
		}
	}
}

//005D97A0   /> \55                            PUSH EBP
void CMixSystem::ThirdWingMixItemDown2(CItem * lpItem)
{
	if(lpItem == NULL)
	{
		return;
	}

	if((rand()%2) < 1)
	{
		lpItem->m_Level -= 2;
	}
	else
	{
		lpItem->m_Level -= 3;
	}

	lpItem->m_Option3 = 0;
	lpItem->Convert(lpItem->m_Type, lpItem->m_Option1, lpItem->m_Option2, lpItem->m_Option3, lpItem->m_NewOption, lpItem->m_SetOption, lpItem->m_ItemOptionEx, lpItem->m_SocketOption, lpItem->m_SocketOptionIndex, 3);
}

void CMixSystem::SetItemChaosMix(LPOBJ lpObj)
{
	lpObj->ChaosLock = TRUE;

	int ChoasGemCount = 0;
	int BlessGemCount = 0;
	int SoulGemCount = 0;
	int MetalOfAncientCount = 0;
	int MixItemCount = 0;
	int MixSetItemIndex = 0;
	int iMixItemChaosMoney = 0;
	int iChaosMoney = 0;
	int iMetalOfAncientItemLevel = -1;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;


	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,13) )
			{
				BlessGemCount++;

				if ( BlessGemCount > 3 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,14) )
			{
				SoulGemCount++;

				if ( SoulGemCount > 3 )
				{
					iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}

			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,16) )
			{
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				ChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Level >= 6 && lpObj->pChaosBox[n].IsExtItem() != FALSE)
			{
				if ( gSetItemOption.IsSetItem(lpObj->pChaosBox[n].m_Type) != FALSE )
				{
					MixItemCount++;
					MixSetItemIndex = n;
					iMixItemChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
			else if ( ((lpObj->pChaosBox[n].m_Type >= ITEMGET(13,8) && lpObj->pChaosBox[n].m_Type < ITEMGET(13,14)) || (lpObj->pChaosBox[n].m_Type >= ITEMGET(13,20) && lpObj->pChaosBox[n].m_Type < ITEMGET(13,28) ) ) && ( lpObj->pChaosBox[n].m_Option3 >= 2  && lpObj->pChaosBox[n].m_Level >= 3 ) )	
			{
				if ( gSetItemOption.IsSetItem(lpObj->pChaosBox[n].m_Type ) != FALSE )
				{
					MixItemCount++;
					MixSetItemIndex = n;
					iMixItemChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				}
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,27) )
			{
				MetalOfAncientCount++;
				iMetalOfAncientItemLevel = lpObj->pChaosBox[n].m_Level;
			}
			else
			{
				DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
				lpObj->ChaosLock = FALSE;
			}
		}
	}


	if ( ChoasGemCount < 1 || BlessGemCount < 3 || SoulGemCount < 3 || MetalOfAncientCount != 1 || MixItemCount != 1 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "SetItemMix");
	LogAddTD("[SetItemMix] Chaos Mix Start");

	if ( gSetItemOption.CheckMixContition(lpObj->pChaosBox[MixSetItemIndex].m_Type, iMetalOfAncientItemLevel ) == FALSE )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->ChaosSuccessRate = iMixItemChaosMoney / 40000;
	lpObj->ChaosSuccessRate = iChaosMoney / 400000;

	if ( lpObj->ChaosSuccessRate > 80 )
	{
		lpObj->ChaosSuccessRate = 80;
	}

	int nChaosNeedMoney = (lpObj->ChaosSuccessRate - 50 ) * 1000000;

	if ( lpObj->Money < nChaosNeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	int setoption = gSetItemOption.MakeSetOption(lpObj->pChaosBox[MixSetItemIndex].m_Type, iMetalOfAncientItemLevel);

	if ( setoption == 0 )
	{
		pMsg.Result = CB_ERROR;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= nChaosNeedMoney;
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if ( (rand()%100) < lpObj->ChaosSuccessRate )
	{
		lpObj->pChaosBox[MixSetItemIndex].m_SetOption = setoption;

		if ( (rand()%100 ) < 80 )
		{
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption |= 4;
		}
		else
		{
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption |= 8;
		}

		pMsg.Result = CB_SUCCESS;
		CItem Item;

		float Dur = (float)ItemGetDurability(lpObj->pChaosBox[MixSetItemIndex].m_Type, lpObj->pChaosBox[MixSetItemIndex].m_Level,
			lpObj->pChaosBox[MixSetItemIndex].IsExtItem(), lpObj->pChaosBox[MixSetItemIndex].IsSetItem());

		Item.m_Level = lpObj->pChaosBox[MixSetItemIndex].m_Level;
		Item.m_Durability = Dur * lpObj->pChaosBox[MixSetItemIndex].m_Durability / lpObj->pChaosBox[MixSetItemIndex].m_BaseDurability;
		Item.m_JewelOfHarmonyOption = lpObj->pChaosBox[MixSetItemIndex].m_JewelOfHarmonyOption;

		Item.Convert(lpObj->pChaosBox[MixSetItemIndex].m_Type, lpObj->pChaosBox[MixSetItemIndex].m_Option1, lpObj->pChaosBox[MixSetItemIndex].m_Option2,
			lpObj->pChaosBox[MixSetItemIndex].m_Option3, lpObj->pChaosBox[MixSetItemIndex].m_NewOption, 
			lpObj->pChaosBox[MixSetItemIndex].m_SetOption, lpObj->pChaosBox[MixSetItemIndex].m_ItemOptionEx, lpObj->pChaosBox[MixSetItemIndex].m_SocketOption, lpObj->pChaosBox[MixSetItemIndex].m_SocketOptionIndex, CURRENT_DB_VERSION);

		Item.m_Number = lpObj->pChaosBox[MixSetItemIndex].m_Number;

		ItemByteConvert(pMsg.ItemInfo, Item);
		this->ChaosBoxInit(lpObj);
		::gObjChaosBoxInsertItemPos(lpObj->m_Index, Item, 0, -1);
		gObjChaosItemSet(lpObj->m_Index, 0, 1);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[SetItemMix] [%s][%s] CBMix Success %d Money : %d-%d (SetName:%s)", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate,
			lpObj->Money, lpObj->ChaosMoney, gSetItemOption.GetSetOptionName(lpObj->pChaosBox[MixSetItemIndex].m_Type, setoption));
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[SetItemMix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money,
			nChaosNeedMoney);

		lpObj->ChaosLock = FALSE;
	}
}

struct CB_PMSG_REQ_PRESENT
{
	PBMSG_HEAD h;	// C1:01
	char AccountId[10];	// 3
	char GameId[10];	// D
	int Sequence;	// 18
};

void CMixSystem::CBUPS_ItemRequest(int aIndex, char* AccountId, char* Name)
{
	LogAddTD("[DevilSquare] 이벤트 경품 요청 [%s][%s]", AccountId, Name);

	CB_PMSG_REQ_PRESENT pMsg;

	pMsg.h.c = 0xC1;
	pMsg.h.headcode = 0x01;
	pMsg.h.size = sizeof(pMsg);
	pMsg.Sequence = aIndex;
	memcpy(pMsg.AccountId, AccountId, sizeof(pMsg.AccountId));
	memcpy(pMsg.GameId, Name, sizeof(pMsg.GameId));

	gUdpSocCE.SendData((LPBYTE)&pMsg, pMsg.h.size);
}

void ChaosEventProtocolCore(BYTE protoNum, unsigned char* aRecv, int aLen)
{
	switch ( protoNum )
	{
		case 0x01:
			//g_MixSystem.CBUPR_ItemRequestRecv( (CB_PMSG_REQ_PRESENT_RESULT *)aRecv);
			break;
	}
}

void CMixSystem::LotteryItemMix(LPOBJ lpObj) //005B9E40
{
	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	int iLotteryItemCount = 0;
	int iInvalidItemCount = 0;
	int iItemHeight = 0;
	int iItemWidth = 0;

	int iChaosCardId = 0; //loc9

	for ( int n=0;n<CHAOS_BOX_SIZE;n++)
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,54) )
			{
				iChaosCardId = 1;
				iLotteryItemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,92) )
			{
				iChaosCardId = 2;
				iLotteryItemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,93) )
			{
				iChaosCardId = 3;
				iLotteryItemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,95) )
			{
				iChaosCardId = 4;
				iLotteryItemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 || iLotteryItemCount != 1 ) //season 2.5 fix
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if ( iChaosCardId == 0 )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "CashLottery");
	iItemHeight = 4;
	iItemWidth = 2;

	if ( !CheckLotteryInventoryEmptySpace(lpObj, iItemHeight, iItemWidth))
	{
		pMsg.Result = 0xF1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	CItem LotteryItem;

	if(iChaosCardId == 1)
	{
		g_ChaosCard.CheckChaosCardInfo("ChaosCard", &LotteryItem);
	}
	else if(iChaosCardId == 2)
	{
		g_ChaosCard.CheckChaosCardInfo("ChaosCardGold", &LotteryItem);
	}
	else if(iChaosCardId == 3)
	{
		g_ChaosCard.CheckChaosCardInfo("ChaosCardRare", &LotteryItem);
	}
	else if(iChaosCardId == 4)
	{
		g_ChaosCard.CheckChaosCardInfo("ChaosCardMini", &LotteryItem);
	}

	if ( LotteryItem.IsItem() == FALSE )
	{
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		LogAddTD("[ChaosMix][LotteryItemMix] Lottery Item Mix Failed. Can't Get Item from List.");

		return;
	}

	ItemSerialCreateSend(lpObj->m_Index, 255, 0, 0, LotteryItem.m_Type, (BYTE)LotteryItem.m_Level, (BYTE)LotteryItem.m_Durability, (BYTE)LotteryItem.m_Option1, (BYTE)LotteryItem.m_Option2, (BYTE)LotteryItem.m_Option3, lpObj->m_Index, (BYTE)LotteryItem.m_NewOption, 0);

	gObjInventoryCommit(lpObj->m_Index);

	LogAddTD("[ChaosMix][ChaosCardMix] Chaos Card Item Mix Success [%s][%s]", lpObj->AccountID, lpObj->Name);

	BYTE btExOption[MAX_EXOPTION_SIZE];

	ItemIsBufExOption(btExOption, &LotteryItem);
	
	LogAddTD("[CashShop][ChaosCardMix] - User(ID:%s,Name:%s) Item(Name:%s,Type:%d,Level:%d,Dur:%d,Skill:%d,Luck:%d,AddOption:%d,Ex:(%d,%d,%d,%d,%d,%d))",
		lpObj->AccountID, lpObj->Name, ItemAttribute[LotteryItem.m_Type].Name,
		LotteryItem.m_Type, LotteryItem.m_Level, (int)LotteryItem.m_Durability,
		LotteryItem.m_Option1, LotteryItem.m_Option2, LotteryItem.m_Option3,
		btExOption[0], btExOption[1], btExOption[2], btExOption[3], btExOption[4], btExOption[5]);
}

typedef BOOL(*CherryBlossomEventItemABCBoxOpen)(LPOBJ lpObj, BYTE btMapNumber, BYTE cX, BYTE cY, int * iDropZen);

struct ST_CHERRYBLOSSOM_MIX
{
	int	iBranchId; //1C
	bool	LoadItemInfo; //18
	BYTE	btBranchCount; //17
	BYTE	ItemDur; //16
	CherryBlossomEventItemABCBoxOpen	CherryBlossomItemList; //14
};

void CMixSystem::CherryBlossomMix(LPOBJ lpObj) //005BA390
{
	PMSG_CHAOSMIXRESULT pMsg; //loc3 and 4
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;

	ST_CHERRYBLOSSOM_MIX	CherryBlossomData = {0}; //nice wz

	for (int n=0;n<CHAOS_BOX_SIZE;n++) // loc8 -> ebp 20
	{
		if ( lpObj->pChaosBox[n].IsItem() == FALSE )
		{
			continue;
		}

		if(CherryBlossomData.iBranchId == 0)
		{
			CherryBlossomData.iBranchId = lpObj->pChaosBox[n].m_Type; //loc7

			if(CherryBlossomData.iBranchId == ITEMGET(14,88))
			{
				CherryBlossomData.btBranchCount = 10;
				CherryBlossomData.CherryBlossomItemList = CherryBlossomEventItemBoxAOpen; //loc5
			}
			else if(CherryBlossomData.iBranchId == ITEMGET(14,89))
			{
				CherryBlossomData.btBranchCount = 30;
				CherryBlossomData.CherryBlossomItemList = CherryBlossomEventItemBoxBOpen; //loc5
			}
			else if(CherryBlossomData.iBranchId == ITEMGET(14,90))
			{
				CherryBlossomData.btBranchCount = 50;
				CherryBlossomData.CherryBlossomItemList = CherryBlossomEventItemBoxCOpen; //loc5
			}
			else
			{
				CherryBlossomData.iBranchId = 0;
				continue;
			}
			CherryBlossomData.LoadItemInfo = true; //ebp-18			
		}

		if(CherryBlossomData.iBranchId == lpObj->pChaosBox[n].m_Type)
		{
            CherryBlossomData.ItemDur = (BYTE)((float)CherryBlossomData.ItemDur + lpObj->pChaosBox[n].m_Durability);
		}
		else
		{
			CherryBlossomData.LoadItemInfo = false;
            break;
		}
	}

	if( CherryBlossomData.ItemDur != CherryBlossomData.btBranchCount )
	{
		CherryBlossomData.LoadItemInfo = false;
	}

	if( CherryBlossomData.iBranchId == 0 || CherryBlossomData.LoadItemInfo == false )
	{
		pMsg.Result = CB_ERROR;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	int iItemHeight = 4;
	int iItemWidth = 2;

	if ( !CheckInventoryEmptySpace(lpObj, iItemHeight, iItemWidth))
	{
		pMsg.Result = 0xF1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if( CherryBlossomData.CherryBlossomItemList == NULL )
	{
		pMsg.Result = 0xF1;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	int iDropZen = 0;

	BOOL bCherryBlossomBoxOpen = CherryBlossomData.CherryBlossomItemList(lpObj, -1, 0, 0, &iDropZen); //

	if( bCherryBlossomBoxOpen == FALSE )
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[%s][%s] CherryBlossomMix Fail %d Money : %d-%d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->Money, lpObj->ChaosMoney);
		lpObj->ChaosLock = FALSE;
	}
	else
	{
		//season4.5 add-on start
		LogAddTD("[%s][%s] CherryBlossomMix Success Rate:%d Money : %d", lpObj->AccountID, lpObj->Name, lpObj->ChaosSuccessRate, lpObj->ChaosMoney);
		
		if(iDropZen > 0)
		{
			if(lpObj->Money + iDropZen < 2000000000)
			{
				lpObj->Money += iDropZen;
				GCMoneySend(lpObj->m_Index, lpObj->Money);
				memset(pMsg.ItemInfo, 0xFF, sizeof(pMsg.ItemInfo));
				pMsg.Result = 1;
				this->ChaosBoxInit(lpObj);
				GCUserChaosBoxSend(lpObj, 0);
				DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
				gObjInventoryCommit(lpObj->m_Index);
				return;
			}

			pMsg.Result = 0xF1;
			DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
			LogAddTD("[%s] Overflow Zen [%s][%s] [%d/%d User Zen/Zen]", "CherryBlossomMix", lpObj->AccountID, lpObj->Name, lpObj->Money, iDropZen);		
		}
		//season4.5 add-on end

		lpObj->ChaosLock = FALSE;
	}

	gObjInventoryCommit(lpObj->m_Index);
}

void CMixSystem::SocketSeedExtract(LPOBJ lpObj) //0062A5B0 identical
{
	int iExcItemCount = 0; //2
	int iSetItemCount = 0; //3
	int iHarmonyCount = 0; //4
	int iChoasGemCount = 0; //5
	int iCreationGemCount = 0; //6
	int iInvalidItemCount = 0; //7
	int iSeedExtractRate = 0; //8
	DWORD iChaosMoney = 0; //9
	int iMixMoney = 0; //10
	int iChaosTaxMoney = 0; //11
	int iSetItemNum = 0; //12
	int iExcItemNum = 0; //13
	int iHarmonyItemNum = 0; //14
	int iChoasGemItemNum = 0; //15
	int iCreationItemNum = 0; //16

	PMSG_CHAOSMIXRESULT pMsg; //loc19 and 20
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc21
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].IsExtItem() == TRUE && lpObj->pChaosBox[n].m_Level >= 4)
			{
				iExcItemCount++;
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				iExcItemNum = n;
			}
			else if ( lpObj->pChaosBox[n].IsSetItem() != FALSE && lpObj->pChaosBox[n].m_Level >= 4)
			{
				iSetItemCount++;
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				iSetItemNum = n;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,42) )
			{
				iHarmonyCount++;
				iHarmonyItemNum = n;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChoasGemCount++;
				iChoasGemItemNum = n;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )
			{
				iCreationGemCount++;
				iCreationItemNum = n;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 )
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(iExcItemCount != 1 && iSetItemCount != 1 && iHarmonyCount != 1 && iChoasGemCount != 1 && iCreationGemCount != 1)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	iChaosTaxMoney = (int)((__int64)g_iSeedExtractMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iMixMoney = g_iSeedExtractMoney + iChaosTaxMoney;

	if ( lpObj->Money < iMixMoney )
	{
		pMsg.Result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "SeedExtract");
	lpObj->Money -= iMixMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	iSeedExtractRate = 80 + (iChaosMoney / 2000000);

	if( iSeedExtractRate > 90 )
	{
		iSeedExtractRate = 90;
	}

	if(rand()%100 > iSeedExtractRate) //fail rate
	{
		lpObj->pChaosBox[iSetItemNum].m_Level -= rand()%3;
		lpObj->pChaosBox[iExcItemNum].m_Level -= rand()%3;
		lpObj->pChaosBox[iHarmonyItemNum].Clear();
		lpObj->pChaosBox[iChoasGemItemNum].Clear();
		lpObj->pChaosBox[iCreationItemNum].Clear();
		GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		LogAddTD("[%s][%s] Seed Extract Mix Failed.", lpObj->AccountID, lpObj->Name);
		return;
	}

	BYTE SocketOptionIndex = 0;
	SocketOptionIndex = g_SocketOption.SortOptionIndex(); //Sort Seed :)
	CSeed * SeedData = g_SocketOption.GetSeedData(SocketOptionIndex);

	if(SeedData != NULL)
	{
		pMsg.Result = 1;
		ItemSerialCreateSend(lpObj->m_Index, 0xFF, 0, 0, SeedData->m_iItemIndex, (BYTE)SeedData->m_btItemLevel, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
		gObjInventoryCommit(lpObj->m_Index);
		LogAddTD("[%s][%s] Seed Extract Mix Success - SeedInfo ( Index : %d, Type : %d, Level : %d, ItemCode : %d )",
		lpObj->AccountID, lpObj->Name, SeedData->m_btOptionIndex, SeedData->m_btElementIndex, SeedData->m_btItemLevel, SeedData->m_iItemIndex);
	}
	else
	{
		lpObj->pChaosBox[iSetItemNum].m_Level -= rand()%3;
		lpObj->pChaosBox[iExcItemNum].m_Level -= rand()%3;
		lpObj->pChaosBox[iHarmonyItemNum].Clear();
		lpObj->pChaosBox[iChoasGemItemNum].Clear();
		lpObj->pChaosBox[iCreationItemNum].Clear();
		GCUserChaosBoxSend(lpObj, 0);
		LogAddTD("[%s][%s] Seed Extract Mix Failed - SeedData is NULL", lpObj->AccountID, lpObj->Name);
		lpObj->ChaosLock = FALSE;
	}
}

void CMixSystem::SocketSeedSphereComposite(LPOBJ lpObj) //0062AE20 identical
{
	int iSeedSphereItemCount = 0; //2
	int iSeedItemCount = 0; //3
	int iInvalidItemCount = 0; //4
	int iChoasGemCount = 0; //5
	int iCreationGemCount = 0; //6
	int iChaosTaxMoney = 0; //7
	int iMixMoney = 0; //8
	DWORD iChaosMoney = 0; //9
	int iSeedSphereCompositeRate = 0; //10
	CItem * pSeedSphere = NULL; //11
	CItem * pSeed = NULL; //12

	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;
	lpObj->ChaosLock = TRUE;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc21
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( g_SocketOption.IsSeedSphereItem(lpObj->pChaosBox[n].m_Type) == 1)
			{
				iSeedSphereItemCount++;
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				pSeedSphere = &lpObj->pChaosBox[n];
			}
			else if( g_SocketOption.IsSeedItem(lpObj->pChaosBox[n].m_Type) == 1)
			{
				iSeedItemCount++;
				iChaosMoney += lpObj->pChaosBox[n].m_BuyMoney;
				pSeed = &lpObj->pChaosBox[n];
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )
			{
				iCreationGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 )
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(iSeedSphereItemCount != 1 && iSeedItemCount != 1 && iChoasGemCount != 1 && iCreationGemCount != 1)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	iChaosTaxMoney = (int)((__int64)g_iSeedSphereCompositeMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iMixMoney = g_iSeedSphereCompositeMoney + iChaosTaxMoney;

	if ( lpObj->Money < iMixMoney )
	{
		pMsg.Result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "SeedSphereComposite");
	iSeedSphereCompositeRate = 80 + (iChaosMoney / 200000);

	if( iSeedSphereCompositeRate > 90 )
	{
		iSeedSphereCompositeRate = 90;
	}

	lpObj->Money -= iMixMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	if(rand()%100 > iSeedSphereCompositeRate) //fail rate
	{
		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		LogAddTD("[%s][%s] SeedSphere Composite Mix Failed.", lpObj->AccountID, lpObj->Name);
	}
	else
	{
		BYTE OptionIndex = 0; //54
		BYTE SphereLevel = 0; //58
		CSeedSphere SeedSphere;

		OptionIndex = g_SocketOption.GetSeedOptionIndex(pSeedSphere->m_Type, pSeedSphere->m_Level);
		SphereLevel = g_SocketOption.GetSphereLevel(pSeed->m_Type);

		g_SocketOption.SetSeedSphereData(&SeedSphere, OptionIndex, SphereLevel);
		
		if(SeedSphere.m_iItemIndex != 0)
		{
			pMsg.Result = 1;
			ItemSerialCreateSend(lpObj->m_Index, 0xFF, 0, 0, SeedSphere.m_iItemIndex, (BYTE)SeedSphere.m_btItemLevel, 1, 0, 0, 0, lpObj->m_Index, 0, 0);
			gObjInventoryCommit(lpObj->m_Index);
			LogAddTD("[%s][%s] SeedSphere Composite Mix Success - SeedSphere Info ( Index : %d, Type : %d, Level : %d, ItemCode : %d )",
			lpObj->AccountID, lpObj->Name, SeedSphere.m_btItemByteOption, SeedSphere.m_btElementIndex, SeedSphere.m_btSocketSlotCount, SeedSphere.m_iItemIndex);
			return;
		}

		this->ChaosBoxInit(lpObj);
		GCUserChaosBoxSend(lpObj, 0);
		LogAddTD("[%s][%s] SeedSphere Composite Mix Failed - SeedSphere Data is NULL", lpObj->AccountID, lpObj->Name);
	}
	lpObj->ChaosLock = FALSE;
}

void CMixSystem::SocketSetSeedSphere(LPOBJ lpObj, BYTE SocketSlot) //0062B4A0 identical
{
	int iSocketItemCount = 0; //2
	int iInvalidItemCount = 0; //3
	int iSeedSpearItemCount = 0; //4
	int iChoasGemCount = 0; //5
	int iCreationGemCount = 0; //6
	CItem * pSocketItem = NULL; //7
	CItem * pSeedSpearItem = NULL; //8
	CItem Item;
	int iChaosTaxMoney = 0;
	int iMixMoney = 0;

	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if(SocketSlot >= 5)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	lpObj->ChaosLock = TRUE;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc21
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( g_SocketOption.CheckItemType(lpObj->pChaosBox[n].m_Type) == 1)
			{
				if(lpObj->pChaosBox[n].m_SocketOption[SocketSlot] == 0xFE) //Slot with NO OPTION
				{
					iSocketItemCount++; //
					pSocketItem = &lpObj->pChaosBox[n];
				}
			}
			else if( g_SocketOption.IsSeedSpearItem(lpObj->pChaosBox[n].m_Type) == 1)
			{
				iSeedSpearItemCount++;
				pSeedSpearItem = &lpObj->pChaosBox[n];
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,15) )
			{
				iChoasGemCount++;
			}
			else if ( lpObj->pChaosBox[n].m_Type == ITEMGET(14,22) )
			{
				iCreationGemCount++;
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 )
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(iSocketItemCount != 1 && iSeedSpearItemCount != 1 && iChoasGemCount != 1 && iCreationGemCount != 1)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if( g_SocketOption.CheckEmptySlot(pSocketItem, pSeedSpearItem->m_Type, pSeedSpearItem->m_Level) == 0)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	iChaosTaxMoney = (int)((__int64)g_iSeedSphereSetMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iMixMoney = g_iSeedSphereSetMoney + iChaosTaxMoney;

	if ( lpObj->Money < iMixMoney )
	{
		pMsg.Result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "SetSeedSphere");
	
	BYTE SocketByteOption = 0;
	SocketByteOption = g_SocketOption.GetItemSocketByteOption(pSeedSpearItem->m_Type, pSeedSpearItem->m_Level);

	if(SocketByteOption == 0xFF)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		LogAddTD("[%s][%s] Set Seed Mix Failed - SeedSphere is NULL", lpObj->AccountID, lpObj->Name);
		return;
	}

	if( g_SocketOption.CheckItemElementInfo(pSocketItem, SocketByteOption) == 0 )
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		LogAddTD("[%s][%s] Set Seed Mix Failed - Wrong Item Type for Set Socket", lpObj->AccountID, lpObj->Name);
		return;
	}

	lpObj->Money -= iMixMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	g_SocketOption.MakeManualOption(pSocketItem, SocketByteOption, SocketSlot); //Apply Visual Info

	float Dur = (float)ItemGetDurability(pSocketItem->m_Type, pSocketItem->m_Level, pSocketItem->IsExtItem(), pSocketItem->IsSetItem());

	Item.m_Number = pSocketItem->m_Number;
	Item.m_Level = pSocketItem->m_Level;
	Item.m_Durability = Dur * pSocketItem->m_Durability / pSocketItem->m_BaseDurability;
	Item.m_JewelOfHarmonyOption = pSocketItem->m_JewelOfHarmonyOption;

	Item.Convert(pSocketItem->m_Type, pSocketItem->m_Option1, pSocketItem->m_Option2, pSocketItem->m_Option3, pSocketItem->m_NewOption,
				pSocketItem->m_SetOption, pSocketItem->m_ItemOptionEx, pSocketItem->m_SocketOption, pSocketItem->m_SocketOptionIndex, CURRENT_DB_VERSION);

	lpObj->ChaosLock = FALSE;

	ItemByteConvert(pMsg.ItemInfo, Item);
	this->ChaosBoxInit(lpObj);
	::gObjChaosBoxInsertItemPos(lpObj->m_Index, Item, 0, -1);
	gObjChaosItemSet(lpObj->m_Index, 0, 1);
	GCUserChaosBoxSend(lpObj, 0);
    
	LogAddTD("[%s][%s] Set SeedSphere Mix Success - ItemInfo ( Name : %s, ItemCode : %d, Level : %d, SocketOption[%d,%d,%d,%d,%d], BonusOption : %d )",
		lpObj->AccountID, lpObj->Name, ItemAttribute[Item.m_Type].Name, Item.m_Type, Item.m_Level, Item.m_SocketOption[0], Item.m_SocketOption[1],
		Item.m_SocketOption[2], Item.m_SocketOption[3], Item.m_SocketOption[4], Item.m_SocketOptionIndex);

	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
}

void CMixSystem::SocketRemoveSeedSphere(LPOBJ lpObj, BYTE SocketSlot) //0062BDF0 identical
{
	int iSocketItemCount = 0; //2
	int iInvalidItemCount = 0; //3

	int loc4 = 0;

	int iSocketItemNum = 0; //5

	int loc6 = 0;

	int iMixMoney = 0; //7
	int iChaosTaxMoney = 0; //8

	PMSG_CHAOSMIXRESULT pMsg;
	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	if(SocketSlot >= 5)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	lpObj->ChaosLock = TRUE;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc21
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if( g_SocketOption.CheckItemType(lpObj->pChaosBox[n].m_Type) == 1)
			{
				if(lpObj->pChaosBox[n].m_SocketOption[SocketSlot] != 0xFE && lpObj->pChaosBox[n].m_SocketOption[SocketSlot] != 0xFF) //Slot with OPTION
				{
					iSocketItemCount++; //
					iSocketItemNum = n;
				}
			}
			else
			{
				iInvalidItemCount++;
			}
		}
	}

	if ( iInvalidItemCount > 0 )
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(iSocketItemCount != 1)
	{
		pMsg.Result = 7;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	iChaosTaxMoney = (int)((__int64)g_iSeedSphereRemoveMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if ( iChaosTaxMoney < 0 )
	{
		iChaosTaxMoney = 0;
	}

	iMixMoney = g_iSeedSphereRemoveMoney + iChaosTaxMoney;

	if ( lpObj->Money < iMixMoney )
	{
		pMsg.Result = 2;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	lpObj->Money -= iMixMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	LogChaosItem(lpObj, "SeedSphereRemove");
	
	g_SocketOption.RemakeSocketOption(&lpObj->pChaosBox[iSocketItemNum], SocketSlot);

	lpObj->ChaosLock = FALSE;
	gObjInventoryCommit(lpObj->m_Index);
	GCUserChaosBoxSend(lpObj, 0);

	LogAddTD("[%s][%s] SeedSphere Remove Success - ItemInfo ( Name : %s, ItemCode : %d, Level : %d, SocketOption[%d,%d,%d,%d,%d], BonusOption : %d )",
		lpObj->AccountID, lpObj->Name, ItemAttribute[lpObj->pChaosBox[iSocketItemNum].m_Type].Name, lpObj->pChaosBox[iSocketItemNum].m_Type, 
		lpObj->pChaosBox[iSocketItemNum].m_Level, lpObj->pChaosBox[iSocketItemNum].m_SocketOption[0], lpObj->pChaosBox[iSocketItemNum].m_SocketOption[1],
		lpObj->pChaosBox[iSocketItemNum].m_SocketOption[2], lpObj->pChaosBox[iSocketItemNum].m_SocketOption[3], lpObj->pChaosBox[iSocketItemNum].m_SocketOption[4], lpObj->pChaosBox[iSocketItemNum].m_SocketOptionIndex);
	
	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
}
//Mix Wing 2.5
void CMixSystem::MixWings2_5(LPOBJ lpObj)
{	
	lpObj->ChaosLock = TRUE;

	int NeedLochsFeather = 0;
	int NeedJewelOfChaos = 0;
	int Need2lvlWing = 0;
	int NeedJewelOfCreatoion = 0;
	int NeedExlItem = 0;
	int NeedMoney = 5000000;
	int RateMix	= ExConfig.CommonServer.Wing2_5MaxSuccessRate;
	int NeedError = 0;
	int MixLuckRate = 40;
	int PlusProcent = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc16
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( this->CheckLevel2WingItem(lpObj->pChaosBox[n].m_Type) != FALSE )
			{
				if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,0) != FALSE )
				{
					Need2lvlWing++;
				}
			}
			else if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,1) != FALSE )
			{
				NeedExlItem++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(13,14))	//pero
			{
				NeedLochsFeather++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofChaos)
			{
				NeedJewelOfChaos++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofCreation)
			{
				NeedJewelOfCreatoion++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				PlusProcent+= (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				NeedError++;
			}
		}
	}

	if(PlusProcent > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(NeedExlItem < 1 || NeedLochsFeather != 1 || NeedJewelOfChaos != 1 || Need2lvlWing != 1 || NeedJewelOfCreatoion != 1 || NeedError > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel2_Mix");
	LogAddTD("[ThirdWing Mix][Level 02] Chaos Mix Start");

	int iChaosTaxMoney = (int)((__int64)NeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if(iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	if ( lpObj->Money < NeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= NeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);

	srand(time(NULL));
	int MixPercent = (rand()%100);

	if ( RateMix > MixPercent)
	{
		
		int loc18 = rand()%3;
		int ItemType = 0;

		if(loc18 == 0)
		{
			ItemType = ITEMGET(12,186);
		}
		else if( loc18 == 1)
		{
			ItemType = ITEMGET(12,187);
		}
		else if( loc18 == 2)
		{
			ItemType = ITEMGET(12,188);
		}

		int ItemLuckAdd = 0;

		if( (rand()%100) <= MixLuckRate )
		{
			ItemLuckAdd = 1;
		}

		int ItemOptAdd = 0;
		int loc23 = 0;
		int loc24 = rand()%2;
		int loc25;
		int loc26;
		int loc27;
		int loc28;
		int loc29;

		switch ( loc24 )
		{
		case 0:
			loc25 = rand()%1000;
			if(loc25 < 400)
			{
				loc23 |= 0x10;
			}
			break;

		case 1:
			loc25 = rand()%1000;
			if(loc24 < 300)
			{
				loc23 |= 0x20;
			}
			break;
		}

		loc26 = rand()%4;
		loc27 = rand()%1000;

		switch( loc26 )
		{
		case 1:
			{
				if(loc27 < 120)
				{
					ItemOptAdd = 1;
				}
			}
			break;

		case 2:
			{
				if(loc27 < 60)
				{
					ItemOptAdd = 2;
				}
			}
			break;

		case 3:
			{
				if(loc27 < 30)
				{
					ItemOptAdd = 3;
				}
			}
			break;
		}

		loc28 = rand()%4;
		loc29 = rand()%1000;

		switch( loc28 )
		{
		case 0:
			{
				if(loc29 < 40)
				{
					loc23 |= 1;
				}
			}
			break;
		case 1:
			{
				if(loc29 < 20)
				{
					loc23 |= 2;
				}
			}
			break;

		case 2:
			{
				if(loc29 < 70)
				{
					loc23 |= 4;
				}
			}
			break;
		case 3:
			{
				if(loc29 < 70)
				{
					loc23 |= 8;
				}
			}
			break;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemType , 0, 0, 0, (BYTE)ItemLuckAdd, (BYTE)ItemOptAdd, -1, (BYTE)loc23, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[2.5 Wings Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[2.5 Wings Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
		lpObj->ChaosLock = FALSE;
	}
}
//Mix Wing 4
void CMixSystem::MixWings4rd(LPOBJ lpObj)
{	
	lpObj->ChaosLock = TRUE;

	int NeedCondor = 0;
	int NeedJewelOfChaos = 0;
	int NeedJewelOfCreatoion = 0;
	int Need30Bless = 0;
	int Need30Soul = 0;
	int Need3lvlWing = 0;
	int NeedExlItem = 0;
	int NeedMoney = 25000000;
	int RateMix	= ExConfig.CommonServer.Wing4MaxSuccessRate;
	int NeedError = 0;
	int MixLuckRate = 30;
	int PlusProcent = 0;

	PMSG_CHAOSMIXRESULT pMsg;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc16
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == this->iWingofStorm ||
				 lpObj->pChaosBox[n].m_Type == this->iWingofEternal ||
				 lpObj->pChaosBox[n].m_Type == this->iWingofIllusion ||
				 lpObj->pChaosBox[n].m_Type == this->iWingofRuin ||
				 lpObj->pChaosBox[n].m_Type == this->iCapeofLord ||
				 lpObj->pChaosBox[n].m_Type == this->iWingofDimension )
			{
				if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,0) != FALSE )
				{
					Need3lvlWing++;
				}
			}
			else if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,1) != FALSE )
			{
				NeedExlItem++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(13,52))	//condor
			{
				NeedCondor++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofBless)	//30 B
			{
				Need30Bless++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofSoul)	//30 S
			{
				Need30Soul++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofChaos)
			{
				NeedJewelOfChaos++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofCreation)
			{
				NeedJewelOfCreatoion++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				PlusProcent+= (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				NeedError++;
			}
		}
	}

	if(PlusProcent > 10)
	{
		pMsg.Result = 0xF0; //new macro
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	if(NeedExlItem < 1 || NeedCondor != 1 || NeedJewelOfChaos != 1 || Need3lvlWing != 1 || NeedJewelOfCreatoion != 1 || 
	   Need30Bless != 1 || Need30Soul != 1 || NeedError > 0)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "ThirdWingLevel2_Mix");
	LogAddTD("[ThirdWing Mix][Level 02] Chaos Mix Start");

	int iChaosTaxMoney = (int)((__int64)NeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if(iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	if ( lpObj->Money < NeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= NeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	srand(time(NULL));
	int MixPercent = (rand()%100);

	if ( RateMix > MixPercent)
	{
		int loc18 = rand()%6;
		int ItemType = 0;

		if(loc18 == 0)
		{
			ItemType = ITEMGET(12,180);
		}
		else if( loc18 == 1)
		{
			ItemType = ITEMGET(12,181);
		}
		else if( loc18 == 2)
		{
			ItemType = ITEMGET(12,182);
		}
		else if( loc18 == 3)
		{
			ItemType = ITEMGET(12,183);
		}
		else if( loc18 == 4)
		{
			ItemType = ITEMGET(12,184);
		}
		else if( loc18 == 5)
		{
			ItemType = ITEMGET(12,185);
		}

		int ItemLuckAdd = 0;

		if( (rand()%100) <= MixLuckRate )
		{
			ItemLuckAdd = 1;
		}

		int ItemOptAdd = 0;
		int loc23 = 0;
		int loc24 = rand()%2;
		int loc25;
		int loc26;
		int loc27;
		int loc28;
		int loc29;

		switch ( loc24 )
		{
		case 0:
			loc25 = rand()%1000;
			if(loc25 < 400)
			{
				loc23 |= 0x10;
			}
			break;

		case 1:
			loc25 = rand()%1000;
			if(loc24 < 300)
			{
				loc23 |= 0x20;
			}
			break;
		}

		loc26 = rand()%4;
		loc27 = rand()%1000;

		switch( loc26 )
		{
		case 1:
			{
				if(loc27 < 120)
				{
					ItemOptAdd = 1;
				}
			}
			break;

		case 2:
			{
				if(loc27 < 60)
				{
					ItemOptAdd = 2;
				}
			}
			break;

		case 3:
			{
				if(loc27 < 30)
				{
					ItemOptAdd = 3;
				}
			}
			break;
		}

		loc28 = rand()%4;
		loc29 = rand()%1000;

		switch( loc28 )
		{
		case 0:
			{
				if(loc29 < 40)
				{
					loc23 |= 1;
				}
			}
			break;
		case 1:
			{
				if(loc29 < 20)
				{
					loc23 |= 2;
				}
			}
			break;

		case 2:
			{
				if(loc29 < 70)
				{
					loc23 |= 4;
				}
			}
			break;
		case 3:
			{
				if(loc29 < 70)
				{
					loc23 |= 8;
				}
			}
			break;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemType , 0, 0, 0, (BYTE)ItemLuckAdd, (BYTE)ItemOptAdd, -1, (BYTE)loc23, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[4rd Wings Mix][Level 02] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[4rd Wings Mix][Level 02] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
		lpObj->ChaosLock = FALSE;
	}
}

#ifdef _WINGS_5LVL_
void CMixSystem::MixWings5rd(LPOBJ lpObj)
{	
	PMSG_CHAOSMIXRESULT pMsg;

	//if(false)//if(!ExConfig.CommonServer.Mix4Wings)	//To Continue
	//{
	//	pMsg.Result = CB_INCORRECT_MIX_ITEMS;
	//	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	//	lpObj->ChaosLock = FALSE;
	//	return;
	//}

	lpObj->ChaosLock = TRUE;

	int NeedCondor = 0;
	int NeedJewelOfChaos = 0;
	int NeedJewelOfCreatoion = 0;
	int Need30Bless = 0;
	int Need30Soul = 0;
	int Need4lvlWing = 0;
	int NeedExlItem = 0;
	int NeedMoney = 50000000;
	int RateMix	= ExConfig.CommonServer.Wing5MaxSuccessRate;
	int NeedError = 0;
	int MixLuckRate = 30;
	int PlusProcent = 0;
	int NeedAncItem = 0;

	PHeadSetB((LPBYTE)&pMsg.h, 0x86, sizeof(PMSG_CHAOSMIXRESULT));
	pMsg.Result = CB_ERROR;

	for ( int n=0;n<CHAOS_BOX_SIZE;n++) //loc16
	{
		if ( lpObj->pChaosBox[n].IsItem() == TRUE )
		{
			if ( lpObj->pChaosBox[n].m_Type == ITEMGET(12,180) ||
				 lpObj->pChaosBox[n].m_Type == ITEMGET(12,181) ||
				 lpObj->pChaosBox[n].m_Type == ITEMGET(12,182) ||
				 lpObj->pChaosBox[n].m_Type == ITEMGET(12,183) ||
				 lpObj->pChaosBox[n].m_Type == ITEMGET(12,184) ||
				 lpObj->pChaosBox[n].m_Type == ITEMGET(12,185) )
			{
				if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,0) != FALSE )
				{
					Need4lvlWing++;
				}
			}
			else if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,0,1) != FALSE )
			{
				NeedExlItem++;
			}
			else if( this->CheckItemCondition(&lpObj->pChaosBox[n],9,0,0,1,1,0) != FALSE )
			{
				NeedAncItem++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(13,52))	//condor
			{
				NeedCondor++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofBless)	//30 B
			{
				Need30Bless++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iBundleofSoul)	//30 S
			{
				Need30Soul++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofChaos)
			{
				NeedJewelOfChaos++;
			}
			else if( lpObj->pChaosBox[n].m_Type == this->iJewelofCreation)
			{
				NeedJewelOfCreatoion++;
			}
			else if( lpObj->pChaosBox[n].m_Type == ITEMGET(14,53) )
			{
				PlusProcent+= (int)lpObj->pChaosBox[n].m_Durability;
			}
			else
			{
				NeedError++;
			}
		}
	}

	//if(PlusProcent > 10)
	//{
	//	pMsg.Result = 0xF0; //new macro
	//	DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
	//	lpObj->ChaosLock = FALSE;
	//	return;
	//}

	if(NeedExlItem < 1 || NeedCondor != 1 || NeedJewelOfChaos != 1 || Need4lvlWing != 1 || NeedJewelOfCreatoion != 1 || 
	   Need30Bless != 1 || Need30Soul != 1 || NeedError > 0 || NeedAncItem != 1)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;
		return;
	}

	LogChaosItem(lpObj, "WingLevel5_Mix");
	LogAddTD("[Wings 5 Lvl Mix] Chaos Mix Start");

	int iChaosTaxMoney = (int)((__int64)NeedMoney * (__int64)g_CastleSiegeSync.GetTaxRateChaos(lpObj->m_Index) / (__int64)100);

	if(iChaosTaxMoney < 0)
	{
		iChaosTaxMoney = 0;
	}

	if ( lpObj->Money < NeedMoney )
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;

		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		lpObj->ChaosLock = FALSE;

		return;
	}

	lpObj->Money -= NeedMoney;
	g_CastleSiegeSync.AddTributeMoney(iChaosTaxMoney);
	GCMoneySend(lpObj->m_Index, lpObj->Money);
	srand(time(NULL));
	int MixPercent = (rand()%100);

	if ( RateMix > MixPercent)
	{
		int loc18 = rand()%6;
		int ItemType = 0;

		if(loc18 == 0)
		{
			ItemType = ITEMGET(12,189);
		}
		else if( loc18 == 1)
		{
			ItemType = ITEMGET(12,190);
		}
		else if( loc18 == 2)
		{
			ItemType = ITEMGET(12,191);
		}
		else if( loc18 == 3)
		{
			ItemType = ITEMGET(12,192);
		}
		else if( loc18 == 4)
		{
			ItemType = ITEMGET(12,193);
		}
		else if( loc18 == 5)
		{
			ItemType = ITEMGET(12,194);
		}

		int ItemLuckAdd = 0;

		if( (rand()%100) <= MixLuckRate )
		{
			ItemLuckAdd = 1;
		}

		int ItemOptAdd = 0;
		int loc23 = 0;
		int loc24 = rand()%2;
		int loc25;
		int loc26;
		int loc27;
		int loc28;
		int loc29;

		switch ( loc24 )
		{
		case 0:
			loc25 = rand()%1000;
			if(loc25 < 400)
			{
				loc23 |= 0x10;
			}
			break;

		case 1:
			loc25 = rand()%1000;
			if(loc24 < 300)
			{
				loc23 |= 0x20;
			}
			break;
		}

		loc26 = rand()%4;
		loc27 = rand()%1000;

		switch( loc26 )
		{
		case 1:
			{
				if(loc27 < 120)
				{
					ItemOptAdd = 1;
				}
			}
			break;

		case 2:
			{
				if(loc27 < 60)
				{
					ItemOptAdd = 2;
				}
			}
			break;

		case 3:
			{
				if(loc27 < 30)
				{
					ItemOptAdd = 3;
				}
			}
			break;
		}

		loc28 = rand()%4;
		loc29 = rand()%1000;

		switch( loc28 )
		{
		case 0:
			{
				if(loc29 < 40)
				{
					loc23 |= 1;
				}
			}
			break;
		case 1:
			{
				if(loc29 < 20)
				{
					loc23 |= 2;
				}
			}
			break;

		case 2:
			{
				if(loc29 < 70)
				{
					loc23 |= 4;
				}
			}
			break;
		case 3:
			{
				if(loc29 < 70)
				{
					loc23 |= 8;
				}
			}
			break;
		}

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ItemType , 0, 0, 0, (BYTE)ItemLuckAdd, (BYTE)ItemOptAdd, -1, (BYTE)loc23, 0);
		::gObjInventoryCommit(lpObj->m_Index);

		LogAddTD("[5rd Wings Mix] [%s][%s] CBMix Success %d Money : %d-%d, CharmRate : %d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
	}
	else
	{
		this->ChaosBoxInit(lpObj);
		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		LogAddTD("[5rd Wings Mix] [%s][%s] CBMix Fail %d Money : %d-%d",
			lpObj->AccountID, lpObj->Name, MixPercent,	lpObj->Money, NeedMoney);
		lpObj->ChaosLock = FALSE;
	}
}
#endif