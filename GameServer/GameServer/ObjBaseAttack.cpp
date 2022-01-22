#include "stdafx.h"
#include "ObjBaseAttack.h"
#include "GameMain.h"
#include "LogProc.h"
#include "DevilSquare.h"
#include "BloodCastle.h"
#include "ChaosCastle.h"

#include "CrywolfAltar.h"
#include "CrywolfStatue.h"

#include "IllusionTempleEvent.h"
#include "MasterLevelSystem.h"
//GameServer 1.00.90 JPN - Completed
#include "BuffManager.h"
#include "MasterSkillSystem.h"
#include "ItemAddOption.h"

#include "Configs.h"
#include "SystemOfRage.h"

CObjBaseAttack::CObjBaseAttack()
{
	return;
}

CObjBaseAttack::~CObjBaseAttack()
{
	return;
}

BOOL CObjBaseAttack::DecreaseArrow(LPOBJ lpObj)
{
	if (lpObj->Class == CLASS_ELF && lpObj->Type == OBJ_USER )
	{
		CItem * Right = &lpObj->pInventory[0];
		CItem * Left  = &lpObj->pInventory[1];

		if ( (Right->m_Type >= ITEMGET(4,8) && Right->m_Type <= ITEMGET(4,14)) ||
			  Right->m_Type == ITEMGET(4,16) || Right->m_Type == ITEMGET(4,18) ||
			  Right->m_Type == ITEMGET(4,19) )
		{
			if ( Left->m_Type == ITEMGET(4,7) )
			{
				if ( Left->m_Durability < 1.0f )
				{
					return FALSE;
				}

				if(ExConfig.Skills.NeedArrow) Left->m_Durability -= 1.0f;

				GCItemDurSend(lpObj->m_Index, 1, (BYTE)Left->m_Durability, 0);

				if ( Left->m_Durability < 1.0f )
				{
					lpObj->pInventory[1].Clear();
					GCInventoryItemDeleteSend(lpObj->m_Index, 1, 0);
				}
			}
			else
			{
				return FALSE;
			}
		}
		else if ( (Left->m_Type >= ITEMGET(4,0) && Left->m_Type <= ITEMGET(4,6) ) ||
				   Left->m_Type == ITEMGET(4,17) ||
				   Left->m_Type == ITEMGET(4,20) ||
				   Left->m_Type == ITEMGET(4,21) ||
				   Left->m_Type == ITEMGET(4,22) ||
				   Left->m_Type == ITEMGET(4,23)) //season4 add-on
		{
			if ( Right->m_Type == ITEMGET(4,15) )
			{
				if ( Right->m_Durability < 1.0f )
				{
					return FALSE;
				}

				if(ExConfig.Skills.NeedArrow) Right->m_Durability -= 1.0f;
					
				GCItemDurSend(lpObj->m_Index, 0, (BYTE)Right->m_Durability, 0);

				if ( Right->m_Durability < 1.0f )
				{
					lpObj->pInventory[0].Clear();
					GCInventoryItemDeleteSend(lpObj->m_Index, 0, 0);
				}
			}
			else
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CObjBaseAttack::CheckAttackArea(LPOBJ lpObj, LPOBJ lpTargetObj) //Identical gs-cs 56
{
	if ( lpTargetObj->Type == OBJ_USER || lpTargetObj->m_RecallMon >= 0 )
	{
		BYTE attr = MapC[lpTargetObj->MapNumber].GetAttr(lpTargetObj->X, lpTargetObj->Y);

		if ( (attr&1) == 1 )
		{
			return FALSE;
		}
	}

	if ( lpObj->Type == OBJ_USER )
	{
		int iRet = gObjCheckAttackArea(lpObj->m_Index, lpTargetObj->m_Index);

		if ( iRet != 0 )
		{
			LogAddTD("[%s][%s] Try Attack In Not Attack Area (%s,%d,%d) errortype = %d", lpObj->AccountID, lpObj->Name, lMsg.Get(MSGGET(7, 208) + lpObj->MapNumber), lpObj->X, lpObj->Y, iRet);

			if ( bIsIgnorePacketSpeedHackDetect != FALSE )
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL CObjBaseAttack::PkCheck(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	//int ExPkPartySystem = GetPrivateProfileInt("PK","PKPartyOn",0,"..\\ExTeam\\PvPSystem.ini");
	//int ExPkLimit = GetPrivateProfileInt("PK","PkLimit",6,"..\\ExTeam\\PvPSystem.ini");
	if ( gLanguage == 0 || gLanguage == 2 || gLanguage == 4)
	{
		if ( lpObj->Type == OBJ_USER )
		{
			BOOL bPlayerKiller = FALSE; //Season 2.5 add-on
			
			//int ExPkLimit = GetPrivateProfileInt("PK","PkLimit",6,"..\\ExTeam\\PvPSystem.ini");
			if(ExConfig.PvP.ExPkPartySystem)
			{
				if(lpObj->PartyNumber >= 0) //Season 2.5 add-on
				{
					if(gParty.GetPkLevel(lpObj->PartyNumber) >= ExConfig.PvP.ExPkLimit)
					{
						bPlayerKiller = TRUE;
					}
				}
			}
			
			if(lpObj->m_PK_Level >= ExConfig.PvP.ExPkLimit) //6
			{
				bPlayerKiller = TRUE;
			}

			if(bPlayerKiller == TRUE) //Season 2.5 add-on
			{
				if (lpObj->PartyNumber >= 0 )
				{
					if ( gPkLimitFree == FALSE )
					{
						return FALSE;
					}
				}
				else if ( lpObj->m_PK_Count >= 3 )
				{
					if ( gPkLimitFree == FALSE )
					{
						return FALSE;
					}
				}
			}
		}
	}

	if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		if ( lpTargetObj->Level <= 5 || lpObj->Level <= 5 )
		{
			return FALSE;
		}

		if ( gObjGetRelationShip(lpObj, lpTargetObj) == 2 ) // Rivals
		{
			if ( gNonPK == FALSE )
			{
				return TRUE;
			}
		}

		if ( lpObj->lpGuild != NULL && lpTargetObj->lpGuild != NULL )
		{
			if ( lpObj->lpGuild->WarState == 1 && lpTargetObj->lpGuild->WarState == 1 )
			{
				if ( lpObj->lpGuild->Number == lpTargetObj->lpGuild->Number )
				{
					return FALSE;
				}
			}
		}

		if ( gObjTargetGuildWarCheck(lpObj, lpTargetObj) == FALSE && lpTargetObj->lpGuild != NULL && lpTargetObj->lpGuild->WarState != 0)
		{
			if ( lpTargetObj->lpGuild->WarType == 1 )
			{
				if ( lpTargetObj->MapNumber != 6 )
				{
					if ( !gNonPK )
					{
						return TRUE;
					}
				}
			}

			if ( CC_MAP_RANGE(lpTargetObj->MapNumber) == FALSE )
			{
				return FALSE;
			}
		}

		if ( IT_MAP_RANGE(lpObj->MapNumber) != FALSE ) //season2.5 add-on
		{
			//
		}
		else if ( CC_MAP_RANGE(lpObj->MapNumber) != FALSE )
		{
			if ( g_ChaosCastle.GetCurrentState(g_ChaosCastle.GetChaosCastleIndex(lpObj->MapNumber)) != 2 )
			{
				return FALSE;
			}
		}
		else if ( gNonPK != FALSE )
		{
			return FALSE;
		}

		if ( DS_MAP_RANGE(lpObj->MapNumber) ) // DEvil
		{
			return FALSE;
		}

		if ( BC_MAP_RANGE(lpObj->MapNumber) )
		{
			return FALSE;
		}

		if ( gObjDuelCheck(lpObj, lpTargetObj) == FALSE )
		{
			if ( gObjDuelCheck(lpTargetObj) )
			{
				if(!ExConfig.PvP.AttackInDuel)	//Fix
				{
					return FALSE;
				}
			}
		}

		if ( gLanguage == 0 || gLanguage == 2 )
		{
			BOOL bPlayerKiller = FALSE; //Season 2.5 add-on
			//int ExPkPartySystem = GetPrivateProfileInt("PK","PKPartyOn",0,"..\\ExTeam\\PvPSystem.ini");
			//int ExPkLimit = GetPrivateProfileInt("PK","PkLimit",6,"..\\ExTeam\\PvPSystem.ini");
			if(ExConfig.PvP.ExPkPartySystem)
			{
				if(lpObj->PartyNumber >= 0) //Season 2.5 add-on
				{
					if(gParty.GetPkLevel(lpObj->PartyNumber) >= ExConfig.PvP.ExPkLimit)
					{
						bPlayerKiller = TRUE;
					}
				}
			}

			if(lpObj->m_PK_Level >= ExConfig.PvP.ExPkLimit)
			{
				bPlayerKiller = TRUE;
			}

			if(bPlayerKiller == TRUE) //Season 2.5 add-on
			{
				if (lpObj->PartyNumber >= 0 )
				{
					if ( gPkLimitFree == FALSE )
					{
						return FALSE;
					}
				}
				else if ( lpObj->m_PK_Count >= 3 )
				{
					if ( gPkLimitFree == FALSE )
					{
						return FALSE;
					}
				}
			}

			bPlayerKiller = FALSE; //Season 2.5 add-on
			//int ExPkPartySystem = GetPrivateProfileInt("PK","PKPartyOn",0,"..\\ExTeam\\PvPSystem.ini");
				

			if(ExConfig.PvP.ExPkPartySystem)
			{
				if(lpTargetObj->PartyNumber >= 0) //Season 2.5 add-on
				{
					if(gParty.GetPkLevel(lpTargetObj->PartyNumber) >= ExConfig.PvP.ExPkLimit)
					{
						bPlayerKiller = TRUE;
					}
				}
			}
			if(lpTargetObj->m_PK_Level >= ExConfig.PvP.ExPkLimit)
			{
				bPlayerKiller = TRUE;
			}

			if(bPlayerKiller == 1) //Season 2.5 add-on
			{
				if (lpTargetObj->PartyNumber >= 0 )
				{
					if ( gPkLimitFree == FALSE )
					{

						if(g_CastleSiege.GetCastleState() != CASTLESIEGE_STATE_STARTSIEGE)
						{
							return FALSE;
						}
					}
				}
				else if ( lpTargetObj->m_PK_Count >= 3 )
				{
					if ( gPkLimitFree == FALSE )
					{
						if(g_CastleSiege.GetCastleState() != CASTLESIEGE_STATE_STARTSIEGE)
						{
							return FALSE;
						}
					}
				}
			}


		}
	}
	return TRUE;
}

BOOL CObjBaseAttack::ResistanceCheck(LPOBJ lpObj, LPOBJ lpTargetObj, int skill)
{
	if( lpTargetObj->Type != OBJ_USER)
	{
		if(lpTargetObj->Class == 277 || lpTargetObj->Class == 283 || lpTargetObj->Class == 288 || lpTargetObj->Class == 278 || lpTargetObj->Class == 215 || lpTargetObj->Class == 216 || lpTargetObj->Class == 217 || lpTargetObj->Class == 218 || lpTargetObj->Class == 219)
		{
			return FALSE;
		}
	}

	if( lpTargetObj->Type != OBJ_USER)
	{
		if( CRYWOLF_ALTAR_CLASS_RANGE(lpTargetObj->Class) != FALSE || CRYWOLF_STATUE_CHECK(lpTargetObj->Class) != FALSE ) //HermeX Fix @28/01/2010
		{
			return FALSE;
		}
	}

	if ( skill == 62 )
	{
		gObjBackSpring2(lpTargetObj, lpObj, 3);
	}

	if(g_MasterSkillSystem.GetSkillID(skill) == 515) //Earth Quake Master
	{
		gObjBackSpring2(lpTargetObj, lpObj, 3);
	}

	if ( skill == 19 || skill == 20 || skill == 21 || skill == 22 || skill == 23)
	{
		gObjAddMsgSendDelay(lpTargetObj, 2, lpObj->m_Index, 150, 0);
	}
	else if ( skill == 3 )	// Poison
	{
		if ( retResistance(lpTargetObj, 2) == 0 )
		{
			gObjAddMsgSendDelay(lpTargetObj, 2, lpObj->m_Index, 150, 0);
			return TRUE;
		}
		return FALSE;
	}
	else if ( skill == 1 )
	{
		if(gObjSearchActiveEffect(lpObj, AT_POISON) == 0)
		{
			if ( retResistance(lpTargetObj, 1) == 0 )
			{
				lpTargetObj->lpAttackObj = lpObj;
				gObjApplyBuffEffectDuration(lpTargetObj, AT_POISON, 19, 3, 0, 0, 20);
				return TRUE;
			}
			else
			{
				return FALSE;
			}	
		}
		else
		{
			return FALSE;
		}
	}
	else if ( skill == 38 ) // Death Poison
	{
		if(gObjSearchActiveEffect(lpTargetObj, AT_POISON) == 0)
		{
			if ( retResistance(lpTargetObj, 1) == 0 )
			{
				lpTargetObj->lpAttackObj = lpObj;
				gObjApplyBuffEffectDuration(lpTargetObj, AT_POISON, 19, 3, 0, 0, 10);
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}

		return TRUE;
	}
	else if ( skill == 7 || skill == 39 || 
		g_MasterSkillSystem.GetSkillID(skill) == 450 ) //Season4 add-on
	{
		if(gObjSearchActiveEffect(lpTargetObj, AT_ICE) == 0)
		{
			if ( retResistance(lpTargetObj, 0) == 0 )
			{
				lpTargetObj->lpAttackObj = lpObj;
				lpTargetObj->DelayActionTime = 800;
				lpTargetObj->DelayLevel = 1;
				gObjApplyBuffEffectDuration(lpTargetObj, AT_ICE, 20, 0, 0, 0, 10);
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else if ( skill == 51 ) // Ice Arrow
	{
		if(gObjSearchActiveEffect(lpTargetObj, AT_ICE_ARROW) == 0)
		{
			if ( retResistance(lpTargetObj, 0) == 0 )
			{
				gObjApplyBuffEffectDuration(lpTargetObj, AT_ICE_ARROW, 0, 0, 0, 0, 7);
				lpTargetObj->PathCount = 0;
				lpTargetObj->PathStartEnd = 0; //Season3 add-on
				gObjSetPosition(lpTargetObj->m_Index, lpTargetObj->X, lpTargetObj->Y);
			}
			else
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CObjBaseAttack::MissCheck(LPOBJ lpObj, LPOBJ lpTargetObj, int skill, int skillSuccess, int magicsend, BOOL& bAllMiss)
{
	__try
	{
		int iAttackRate = 0;	// lc20
		int iDefenseRate = lpTargetObj->m_SuccessfulBlocking;	// lc24
		int iMSBDamage = 0;	// MonsterSetBasse Damage

		if(IT_MAP_RANGE(lpTargetObj->MapNumber) != FALSE) //Season2.5 add-on Illusion
		{
			if(g_IllusionTempleEvent.GetState(lpTargetObj->MapNumber) == 2)
			{
				if ( lpTargetObj->Type == OBJ_USER )
				{
					if(g_IllusionTempleEvent.GetShieldSpellStatus(lpTargetObj->m_iIllusionTempleIndex, lpTargetObj->MapNumber) != FALSE)
					{
						GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
						return FALSE;
					}	
				}
				if(lpObj->PartyNumber == lpTargetObj->PartyNumber)
				{
					GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
					return FALSE;
				}
			}
		}

		if ( lpObj->Type == OBJ_USER )	// Miss for Uses
		{
			int iBaseLevel = lpObj->Level + lpObj->MLevel;

			if ( lpObj->Class == CLASS_DARKLORD ) // DL
			{
				iAttackRate = iBaseLevel * 5 + ((lpObj->Dexterity + lpObj->AddDexterity) * 6) / 2 + ( lpObj->Strength + lpObj->AddStrength) / 4  + ((lpObj->Leadership + lpObj->AddLeadership)/10);
				iAttackRate += iAttackRate * lpObj->SetOpImproveSuccessAttackRate / 100;
			}
			else
			{
				iAttackRate = iBaseLevel * 5 + ((lpObj->Dexterity + lpObj->AddDexterity) * 3) / 2 + ( lpObj->Strength + lpObj->AddStrength) / 4 ;
				iAttackRate += iAttackRate * lpObj->SetOpImproveSuccessAttackRate / 100;
			}
		}
		else	// Miss for Monsters
		{
			iAttackRate = lpObj->m_AttackRating;
		}

		iAttackRate += lpObj->m_MLPassiveSkill.m_iML_IncreaseAttackSuccessRate;

		if ( iAttackRate < iDefenseRate )
		{
			bAllMiss = TRUE;
		}

		if ( bAllMiss != FALSE )	// When All Miss
		{
			if ( (rand()%100) >= 5 )
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, iMSBDamage, 0);

				if (magicsend != 0 )
				{
					GCMagicAttackNumberSend(lpObj, skill, lpTargetObj->m_Index, skillSuccess);
				}

				return FALSE;
			}
		}
		else	// if the is a chance  ot hit the target
		{
			if ( (rand()%iAttackRate) < iDefenseRate)
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, iMSBDamage, 0);

				if ( magicsend != 0 )
				{
					GCMagicAttackNumberSend(lpObj, skill, lpTargetObj->m_Index,  skillSuccess);
				}

				return FALSE;
			}
		}
	}
	__except (lpObj->Level=1,-1)
	{
		LogAdd(lMsg.Get(MSGGET(2, 12)), lpObj->Name);
		return FALSE;
	}

	return TRUE;
}

BOOL CObjBaseAttack::MissCheckPvP(LPOBJ lpObj , LPOBJ lpTargetObj, int skill, int skillSuccess, int magicsend, BOOL & bAllMiss)
{
	float iAttackRate = 0;
	float iDefenseRate = 0;
	int iAttackSuccessRate = 0; 

	if(IT_MAP_RANGE(lpTargetObj->MapNumber) != FALSE) //Season2.5 add-on Illusion
	{
		if(g_IllusionTempleEvent.GetState(lpTargetObj->MapNumber) == 2)
		{
			if ( lpTargetObj->Type == OBJ_USER )
			{
				if(g_IllusionTempleEvent.GetShieldSpellStatus(lpTargetObj->m_iIllusionTempleIndex, lpTargetObj->MapNumber) != FALSE)
				{
					GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
					return FALSE;
				}	
			}
			if(lpObj->PartyNumber == lpTargetObj->PartyNumber)
			{
				GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);
				return FALSE;
			}
		}
	}

	int iBaseLevel = lpObj->Level + lpObj->MLevel;

	if ( lpObj->Class == CLASS_KNIGHT )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 45) / 10);	// #formula
	}
	else if ( lpObj->Class == CLASS_DARKLORD )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 4 ));	// #formula
	}
	else if ( lpObj->Class == CLASS_ELF )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 6 ) / 10);	// #formula
	}
	else if ( lpObj->Class == CLASS_MAGUMSA )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 35 ) / 10);	// #formula
	}
	else if ( lpObj->Class == CLASS_WIZARD )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 4 ));	// #formula
	}
	else if ( lpObj->Class == CLASS_SUMMONER )
	{
		iAttackRate = (float)(iBaseLevel * 3 + ( lpObj->Dexterity * 35 ) / 10);	// #formula
	}

	int iTargetBaseLevel = lpTargetObj->Level + lpTargetObj->MLevel;

	if ( lpTargetObj->Class == CLASS_KNIGHT )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 2);	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_DARKLORD )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 2);	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_ELF )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 10);	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_MAGUMSA )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 4);	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_WIZARD )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 4);	// #formula
	}
	else if ( lpTargetObj->Class == CLASS_SUMMONER )
	{
		iDefenseRate = (float)(iTargetBaseLevel * 2 + lpTargetObj->Dexterity / 2);	// #formula
	}

	if ( iAttackRate <= 0.0f || iDefenseRate <= 0.0f || lpObj->Level <= 0 || lpTargetObj->Level <= 0 )
	{
		return FALSE;
	}

	iAttackRate += lpObj->m_ItemOptionExFor380.OpAddAttackSuccessRatePVP;
	iDefenseRate += lpTargetObj->m_ItemOptionExFor380.OpAddDefenseSuccessRatePvP;

	iAttackRate += lpObj->m_JewelOfHarmonyEffect.HJOpAddAttackSuccessRatePVP;
	iDefenseRate += lpTargetObj->m_JewelOfHarmonyEffect.HJOpAddDefenseSuccessRatePvP;

	iAttackRate += lpObj->m_MLPassiveSkill.m_iML_AttackRate;
	iDefenseRate += lpTargetObj->m_MLPassiveSkill.m_iML_IncreasePvPDefenceRate;
#ifdef _SYSTEM_OF_RAGE_
	//LogAddC(2,"lpObj->m_Index: %d",lpObj->m_Index);
	//gSystemOfRage.AttackDefenceRate(lpObj->m_Index,lpTargetObj->m_Index, iAttackRate, iDefenseRate);
#endif
	float iExpressionA = ( iAttackRate * 10000.0f ) / ( iAttackRate + iDefenseRate );
	float iExpressionB = (float)(( iBaseLevel * 10000 ) / ( iBaseLevel + iTargetBaseLevel ));

	iExpressionA /= 10000.0f;
	iExpressionB /= 10000.0f;

	iAttackSuccessRate = (int)(100.0f * iExpressionA * g_fSuccessAttackRateOption * iExpressionB);

	if ( (iTargetBaseLevel - iBaseLevel) >= 100 )
	{
		iAttackSuccessRate -= 5;
	}
	else if ( (iTargetBaseLevel - iBaseLevel) >= 200 )
	{
		iAttackSuccessRate -= 10;
	}
	else if ( (iTargetBaseLevel - iBaseLevel) >= 300 )
	{
		iAttackSuccessRate -= 15;
	}

	DWORD dwRate = rand() % 100;

	if ( dwRate > iAttackSuccessRate )
	{
		GCDamageSend(lpObj->m_Index, lpTargetObj->m_Index, 0, 0, 0, 0);

		if ( g_bShieldComboMissOptionOn == TRUE )
		{
			if ( lpObj->comboSkill.ProgressIndex >= 0 )
			{
				LogAddTD("[Shield] ComboSkill Cancel! [%s][%s]", lpObj->AccountID, lpObj->Name);
				lpObj->comboSkill.Init();
			}
		}

		return FALSE;
	}

	return TRUE;
}

int CObjBaseAttack::GetTargetDefense(LPOBJ lpObj, LPOBJ lpTargetObj, BYTE& MsgDamage) //Identical gs-cs 56
{
	int targetdefense = lpTargetObj->m_Defense;

	if ( lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER )
	{
		targetdefense += lpTargetObj->m_ItemOptionExFor380.OpAddDefense / 2;
	}

	int iSkillMagumReduceDefense = 0;
	iSkillMagumReduceDefense = gObjGetActiveEffect(lpTargetObj, ADD_OPTION_REDUCE_DEFENSE);
	targetdefense -= (targetdefense * iSkillMagumReduceDefense)/100;
	
	if ( lpObj->m_MonsterSkillElementInfo.m_iSkillElementDefenseTime > 0 )
	{
		targetdefense += lpObj->m_MonsterSkillElementInfo.m_iSkillElementDefense;

		if ( targetdefense <0 )
		{
			targetdefense = 0;
		}
	}

	int percentdamage = 0; //loc4

	if ( lpObj->pInventory[7].IsItem() != FALSE )
	{
		percentdamage = lpObj->pInventory[7].IsWingOpGetOnePercentDamage();
		percentdamage += lpObj->pInventory[7].IsThirdWingOpGetOnePercentDamage();
	}

	percentdamage += lpObj->SetOpIgnoreDefense;

	if ( percentdamage != 0)
	{
		if ( (rand()%100) <= percentdamage)
		{
			targetdefense = 0;
			MsgDamage = 1;
		}
	}

	return targetdefense;
}

int CObjBaseAttack::GetPartyMemberCount(LPOBJ lpObj)
{
	LPOBJ lpPartyObj;
	int partynum = lpObj->PartyNumber;

	if ( OBJMAX_RANGE(partynum) == FALSE )
	{
		LogAdd("error : DecPartyMemberHPandMP %s %d", __FILE__, __LINE__);
		return 0;
	}

	int partycount = gParty.m_PartyS[partynum].Count;
	int retcount = 0;

	for ( int n=0;n<MAX_USER_IN_PARTY;n++)
	{
		int memberindex = gParty.m_PartyS[partynum].Number[n];

		if ( memberindex >= 0 )
		{
			lpPartyObj = &gObj[memberindex];

			if ( lpObj->MapNumber == lpPartyObj->MapNumber )
			{
				int dis = gObjCalDistance(lpObj, &gObj[memberindex]);
				
				if ( dis < MAX_PARTY_DISTANCE_EFFECT )
				{
					retcount++;
				}
			}
		}
	}

	return retcount;
}


/////////////
/////////////
/////////////
void ComboSkillData::Init() //forced location
{
	this->dwTime = 0;
	this->Skill[0] = -1;
	this->Skill[1] = -1;
	this->Skill[2] = -1;
	this->ProgressIndex = -1;
}