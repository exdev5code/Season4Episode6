//GameServer 1.00.77 JPN - Completed
#include "stdafx.h"
#include "GameServer.h"
#include "GameServerAuth.h"
#include "gObjMonster.h"
#include "LogToFile.h"
#include "MonsterSetBase.h"
#include "GameMain.h"
#include "..\common\winutil.h"
#include "BattleSoccerManager.h"
#include "Mercenary.h"
#include "protocol.h"
#include "DSProtocol.h"
#include "BloodCastle.h"
#include "KalimaGate.h"
#include "MonsterHerd.h"
#include "CrywolfSync.h"
#include "TMonsterSkillManager.h"
#include "MonsterItemMng.h"
#include "ChaosCastle.h"
#include "QuestInfo.h"
#include "Event.h"
#include "DevilSquare.h"

#include "CastleSiege.h"
#include "LifeStone.h"

#include "IllusionTempleEvent.h"
#include "BuffManager.h"
#include "ItemAddOption.h"
#include "Raklion.h"
#include "ItemDropManager.h"
#include "Configs.h"
#include "ExQuestSystem.h"
#include "PCPointSystem.h"
#include "DropZenManager.h"
#include "GrandHeroSystem.h"
#ifdef PREMIUM_SYSTEM
#include "PremiumSystem.h"
#endif

#include "VipSystem.h"

#ifdef _HAPPY_HOUR_EVENT_
#include "HappyHour.h"
#endif
#include "SystemOfRage.h"
#include "BMQuest.h"
#include "NewItemDropManager.h"

CLogToFile KUNDUN_EVENT_LOG("KUNDUN_EVENT_LOG", ".\\KUNDUN_EVENT_LOG", 1);
CQeustNpcTeleport gQeustNpcTeleport;

void gObjMonsterMoveRegen(int x, int y, LPOBJ lpObj)
{
	gMSetBase.GetBoxPosition(lpObj->MapNumber, x-1, y-1, x+1, y+1, lpObj->X, lpObj->Y);

	lpObj->TX = lpObj->X;
	lpObj->TY = lpObj->Y;
	lpObj->MTX = lpObj->X;
	lpObj->MTY = lpObj->Y;
	lpObj->StartX = lpObj->X;
	lpObj->StartY = lpObj->Y;
}

BOOL gObjMonsterRegen(LPOBJ lpObj)
{
	int map[3];

	map[0] = 0;
	map[1] = 2;
	map[2] = 3;

	gObjViewportListProtocolDestroy(lpObj);
	gObjViewportClose(lpObj);

	lpObj->m_ActState.Attack = 0;
	lpObj->m_ActState.EmotionCount = 0;
	lpObj->m_ActState.Escape = 0;
	lpObj->m_ActState.Move = 0;
	lpObj->m_ActState.Rest = 0;
	lpObj->m_ActState.Emotion = 0;
	lpObj->TargetNumber = -1;
	lpObj->NextActionTime = 5000;

	if ( lpObj->Class == 43 )
	{
		lpObj->MapNumber = map[ rand() % 3 ];

		if ( gMSetBase.GetBoxPosition(lpObj->MapNumber, 10, 10, 240, 240, lpObj->X, lpObj->Y)== FALSE )
		{
			lpObj->Live = FALSE;
			lpObj->m_State = 4;
			lpObj->RegenTime = GetTickCount();
			lpObj->DieRegen = TRUE;
			return FALSE;
		}

		lpObj->TX = lpObj->X;
		lpObj->TY = lpObj->Y;
		lpObj->MTX = lpObj->X;
		lpObj->MTY = lpObj->Y;
		lpObj->StartX = lpObj->X;
		lpObj->StartY = lpObj->Y;
	}
	else if ( lpObj->Class == 44 )
	{

	}
	else if ( lpObj->Class == 53 || lpObj->Class == 54 || lpObj->Class == 55 || lpObj->Class == 56 )
	{
		return FALSE;
	}
	else if ( lpObj->Class >= 78 && lpObj->Class <= 83 )
	{
		return FALSE;
	}
	else if ( lpObj->Class >= 493 && lpObj->Class <= 502 )//Season 4.5 addon
    {
        return FALSE;
    }
	else if ( (lpObj->m_Attribute < 51) ? FALSE : (lpObj->m_Attribute > 58)? FALSE : TRUE )
	{
		lpObj->Live = TRUE;
		lpObj->DieRegen = FALSE;
		CreateFrustrum(lpObj->X, lpObj->Y, lpObj->m_Index);
		gObjClearViewport(lpObj);
		gObjViewportListCreate(lpObj->m_Index);
		gObjViewportListProtocolCreate(lpObj);
		return FALSE;
	}
	else if ( lpObj->Class == 460 || lpObj->Class == 461 || lpObj->Class == 462)//Season 4.5 addon
    {
        if(g_Raklion.GetRaklionState() != RAKLION_STATE_END)
        {
            return FALSE;
        }
    }
	else if ( lpObj->Class == 459 )//Season 4.5 addon
    {
        if ( g_Raklion.GetRaklionState() != RAKLION_STATE_STANDBY || g_Raklion.GetRaklionState() != RAKLION_STATE_READY )
        {
            return FALSE;
        }
    }
    else if ( lpObj->Class == 457 && lpObj->MapNumber == 58 || lpObj->Class == 458 && lpObj->MapNumber == 58 )//Season 4.5 addon
    {
        return FALSE;
    }
	else if ( gMSetBase.GetPosition(lpObj->m_PosNum, lpObj->MapNumber, lpObj->X, lpObj->Y) == FALSE )
	{
		if ( lpObj->m_Attribute == 62 )
		{
			BYTE cX = lpObj->X;
			BYTE cY = lpObj->Y;

			if(gObjGetRandomFreeLocation(lpObj->MapNumber,(BYTE&)cX,(BYTE&)cY,5,5,30) == 0 )
			{
				return FALSE;
			}
			else
			{
				lpObj->X = cX;
				lpObj->Y = cY;
			}
		}
		else
		{
			lpObj->Live = FALSE;
			lpObj->m_State = 4;
			lpObj->RegenTime = GetTickCount();
			lpObj->DieRegen = TRUE;
			return FALSE;
		}
	}
	else
	{
		lpObj->MTX = lpObj->X;
		lpObj->MTY = lpObj->Y;
		lpObj->TX = lpObj->X;
		lpObj->TY = lpObj->Y;
		lpObj->StartX = lpObj->X;
		lpObj->StartY = lpObj->Y;
	}

	gObjMonsterHitDamageInit(lpObj);

	if ( lpObj->MapNumber == MAP_INDEX_CRYWOLF_FIRSTZONE && g_CrywolfSync.GetCrywolfState() >= 2 && g_CrywolfSync.GetCrywolfState() <= 5  ) // Crywolf
	{
	
	}
	else if ( g_CrywolfSync.GetOccupationState() == 0 && g_iCrywolfApplyMvpBenefit != 0 )
	{
		lpObj->Life = (float)(( lpObj->m_iScriptMaxLife * g_CrywolfSync.GetMonHPBenefitRate()  ) / 100);
		lpObj->MaxLife = (float)((lpObj->m_iScriptMaxLife * g_CrywolfSync.GetMonHPBenefitRate() ) / 100);
	}
	return TRUE;
}

int gObjMonsterViewportIsCharacter(LPOBJ lpObj)
{
	int tObjNum;

	for ( int n = 0; n<MAX_VIEWPORT_MONSTER ; n++ )
	{
		if ( lpObj->VpPlayer2[n].state != 0 )
		{
			tObjNum = lpObj->VpPlayer2[n].number;

			if ( tObjNum == lpObj->TargetNumber ) 
			{
				return n;
			}
		}
	}

	return -1;
}

void gObjMonsterHitDamageInit(LPOBJ lpObj)
{
	for ( int i = 0; i< MAX_ST_HIT_DAMAGE ; i++ )
	{
		lpObj->sHD[i].number  = -1;
	}

	lpObj->sHDCount = 0;
}

int gObjMonsterHitDamageUserDel(LPOBJ lpObj)
{
	int delok = 0;
	int delindex = -1;

	for ( int n = 0;n<MAX_ST_HIT_DAMAGE ; n++ )
	{
		if ( lpObj->sHD[n].number >= 0 )
		{
			delok = FALSE;

			if ( gObjIsConnected(lpObj->sHD[n].number ) == TRUE )
			{
				if ( (GetTickCount()- lpObj->sHD[n].LastHitTime) > 20000 )
				{
					delok = TRUE;
				}

				if ( gObj[lpObj->sHD[n].number].MapNumber != lpObj->MapNumber)
				{
					delok = TRUE;
				}
				else if ( gObjCheckTileArea(lpObj->m_Index, gObj[lpObj->sHD[n].number].X , gObj[lpObj->sHD[n].number].Y , 20) == FALSE )
				{
					delok = TRUE;
				}
			}
			else
			{
				delok = TRUE;
			}


			if ( delok == TRUE )
			{
				lpObj->sHD[n].number = -1;
				delindex = n;
				lpObj->sHDCount--;
			}


		}
	}

	return delindex;
}

void gObjMonsterSetHitDamage(LPOBJ lpObj, int hit_player, int hit_damage)
{
	int blank = -1;

	for (int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpObj->sHD[n].number >= 0 )
		{
			if ( lpObj->sHD[n].number == hit_player )
			{
				lpObj->sHD[n].HitDamage += hit_damage;
				lpObj->sHD[n].LastHitTime = GetTickCount();

				if ( lpObj->sHD[n].HitDamage > lpObj->MaxLife )
				{
					lpObj->sHD[n].HitDamage = (int)lpObj->MaxLife;
				}

				return;
			}
		}
		else if ( blank < 0 )
		{
			blank = n;
		}
	}

	if ( blank < 0 )
	{
		blank = gObjMonsterHitDamageUserDel(lpObj);
	}

	if ( blank >= 0 )
	{
		lpObj->sHD[blank].number = hit_player;
		lpObj->sHD[blank].HitDamage = hit_damage;

		if ( lpObj->sHD[blank].HitDamage > lpObj->MaxLife )
		{
			lpObj->sHD[blank].HitDamage = (int)lpObj->MaxLife;
		}
	
		lpObj->sHD[blank].LastHitTime = GetTickCount();
		lpObj->sHDCount++;
	}
	else
	{
		LogAdd("error-L2 : Hit Damage Set error");
	}
}

int gObjMonsterTopHitDamageUser(LPOBJ lpMonObj)
{
	int MaxHitDamage = 0;
	int MaxHitDamageUser = -1;

	for ( int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpMonObj->sHD[n].number >= 0 )
		{
			if ( lpMonObj->sHD[n].HitDamage > MaxHitDamage )
			{
				MaxHitDamage = lpMonObj->sHD[n].HitDamage;
				MaxHitDamageUser = lpMonObj->sHD[n].number;
			}
		}
	}

	return MaxHitDamageUser;
}

int	gObjMonsterLastHitDamageUser(LPOBJ lpMonObj, int & hitindex)
{
	int LastHitTime = 0;
	int LastHitUser = -1;

	for ( int n=0;n<MAX_ST_HIT_DAMAGE;n++)
	{
		if ( lpMonObj->sHD[n].number >= 0 )
		{
			if ( lpMonObj->sHD[n].LastHitTime > LastHitTime )
			{
				LastHitTime = lpMonObj->sHD[n].LastHitTime;
				LastHitUser = lpMonObj->sHD[n].number;
				hitindex = n;
			}
		}
	}

	return LastHitUser;
}

BOOL gObjMonsterMoveCheck(LPOBJ lpObj, int tx, int ty)
{
	if ( lpObj->m_ActState.Emotion  == 1 )
	{
		return TRUE;
	}

	if ( lpObj->MapNumber == MAP_INDEX_KANTURU_BOSS && lpObj->m_PosNum < 0)
	{
		tx -= lpObj->StartX;
		ty -= lpObj->StartY;
		int dis = (int)(sqrt((double)tx*tx + ty*ty));

		if ( dis > 30 )
		{
			LogAddTD("[ KANTURU ][ Debug - m_PosNum ] Fail %s(Index:%d) X%d-Y%d -> X%d-Y%d(%d)", lpObj->Name, lpObj->Class, lpObj->StartX, lpObj->StartY, tx, ty, dis);
			return FALSE;
		}
	}
	else
	{
		LPMONSTER_POSITION lpPos = &gMSetBase.m_Mp[lpObj->m_PosNum];

		if ( lpPos->m_Dis < 1 )
		{
			return FALSE;
		}

		tx -= lpObj->StartX;
		ty -= lpObj->StartY;

		int dis = (int)(sqrt((double)tx * tx + ty * ty));

		if ( dis > lpPos->m_Dis)
		{
			return FALSE;
		}	
	}

	return TRUE;
}

BOOL gObjMonsterGetTargetPos(LPOBJ lpObj)
{
	int tpx;	// Target Player X
	int tpy;
	int mtx;	// Monster Target X
	int mty;
	int searchp = 0;
	int sn = 0;
	int searchcount = MAX_ROAD_PATH_TABLE/2-1;
	BYTE attr;
	BOOL result;
	LPOBJ lpTargetObj;

	if ( lpObj->m_MoveRange == 0 && (gObjSearchActiveEffect(lpObj, AT_ICE_ARROW) == TRUE) && (gObjSearchActiveEffect(lpObj, AT_STUN) == TRUE) ) //season3 changed
	{
		return FALSE;
	}

	if (gObjSearchActiveEffect(lpObj, AT_SLEEP) == TRUE) //season3 add-on
	{
		return FALSE;
	}

	if ( OBJMAX_RANGE(lpObj->TargetNumber) == FALSE )
	{
		return FALSE;
	}

	lpTargetObj = &gObj[lpObj->TargetNumber];

	if ( lpTargetObj->Teleport != 0 )
	{
		return FALSE;
	}

	int vpn = gObjMonsterViewportIsCharacter(lpObj);

	if ( vpn < 0 )
	{
		return FALSE;
	}
	
	tpx = lpTargetObj->X;
	mtx = tpx;
	tpy = lpTargetObj->Y;
	mty = tpy;
	int dis;

	if ( lpObj->m_AttackType >= 100 )
	{
		dis = lpObj->m_AttackRange + 2;
	}
	else
	{
		dis = lpObj->m_AttackRange;
	}

	if ( lpObj->X < mtx )
	{
		tpx -= dis;
	}

	if ( lpObj->X > mtx )
	{
		tpx += dis;
	}

	if ( lpObj->Y < mty )
	{
		tpy -= dis;
	}

	if ( lpObj->Y > mty )
	{
		tpy += dis;
	}

	searchp = GetPathPacketDirPos( (lpTargetObj->X - tpx), (lpTargetObj->Y - tpy) ) * 2;

	if ( MapC[lpObj->MapNumber].GetStandAttr(tpx, tpy) == 0 )
	{
		while ( searchcount-- )
		{
			mtx = lpTargetObj->X + RoadPathTable[searchp];
			mty = lpTargetObj->Y + RoadPathTable[1+searchp];
			attr = MapC[lpObj->MapNumber].GetAttr(mtx, mty);
			result = gObjMonsterMoveCheck(lpObj, mtx, mty);

			if ( lpObj->Class == 249 )
			{
				if ( (attr&2)!=2 && result == TRUE )
				{
					lpObj->MTX = mtx;
					lpObj->MTY = mty;
					return TRUE;
				}
			}
			else if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 && result == TRUE )
			{
				lpObj->MTX = mtx;
				lpObj->MTY = mty;
				return TRUE;
			}

			searchp += 2;

			if ( searchp > MAX_ROAD_PATH_TABLE-1 )
			{
				searchp = 0;
			}
		}

		return FALSE;
	}

	attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);
	result = gObjMonsterMoveCheck(lpObj, mtx, mty);

	if ( lpObj->Class == 249 )
	{
		if ( (attr&2)!=2 && result == TRUE )
		{
			lpObj->MTX = tpx;
			lpObj->MTY = tpy;
			return TRUE;
		}
	}
	else if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 && result == TRUE )
	{
		lpObj->MTX = tpx;
		lpObj->MTY = tpy;
		return TRUE;
	}

	return FALSE;
}

BOOL gObjGetTargetPos(LPOBJ lpObj, int sx, int sy, int & tx , int & ty)
{
	int tpx;	// Target Player X
	int tpy;
	int mtx;	// Monster Target X
	int mty;
	int searchp = 0;
	int sn = 0;
	int searchcount = MAX_ROAD_PATH_TABLE/2-1;
	BYTE attr;
	int dis;

	tpx = sx;
	mtx = tpx;
	tpy = sy;
	mty = tpy;

	if ( lpObj->m_AttackType >= 100 )
	{
		dis = lpObj->m_AttackRange + 2;
	}
	else
	{
		dis = lpObj->m_AttackRange;
	}

	if ( lpObj->X < mtx )
	{
		tpx -= dis;
	}

	if ( lpObj->X > mtx )
	{
		tpx += dis;
	}

	if ( lpObj->Y < mty )
	{
		tpy -= dis;
	}

	if ( lpObj->Y > mty )
	{
		tpy += dis;
	}

	searchp = GetPathPacketDirPos( sx - tpx, sy - tpy ) * 2;

	if ( MapC[lpObj->MapNumber].GetStandAttr(tpx, tpy) == 0 )
	{
		while ( searchcount-- )
		{
			mtx = sx + RoadPathTable[searchp];
			mty = sy + RoadPathTable[1+searchp];
			attr = MapC[lpObj->MapNumber].GetAttr(mtx, mty);
			
			if ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
			{
				tx = mtx;
				ty = mty;
				return TRUE;
			}

			searchp += 2;

			if ( searchp > MAX_ROAD_PATH_TABLE-1 )
			{
				searchp = 0;
			}
		}

		return FALSE;
	}

	attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);

	if ( lpObj->m_Attribute >= 100 )
	{
		if (  (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
		{
			tx = tpx;
			ty = tpy;
			return TRUE;
		}
	}
	else if  ( (attr&1) != 1 && (attr&2) != 2 && (attr&4) != 4 && (attr&8) != 8 )
	{
		tx = tpx;
		ty = tpy;
		return TRUE;
	}

	return FALSE;
}

int gObjCallMonsterSetEnemy(LPOBJ lpObj, int Target)
{
	if ( lpObj->Type != OBJ_USER )
	{
		return -1;
	}

	if( lpObj->m_RecallMon < 0)//Season 4.5 addon
	{
		return -1;
	}

	LPOBJ lpCallObj = &gObj[lpObj->m_RecallMon];

	if ( lpCallObj->TargetNumber >= 0 )
	{
		return -1;
	}

	if ( lpCallObj->TargetNumber != Target )
	{
		lpCallObj->TargetNumber = Target;
		lpCallObj->m_ActState.EmotionCount = 30;
		lpCallObj->m_ActState.Emotion = 1;
	}

	return -1;
}

int gObjMonsterSearchEnemy(LPOBJ lpObj, BYTE objtype) 
{
	int n;
	int tx;
	int ty;
	int dis;
	int mindis = lpObj->m_ViewRange;
	int searchtarget = -1;
	int tObjNum;
	int count = 3;
	int t1 = objtype;
	int t2 = objtype;

	for (n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if ( tObjNum >= 0 )
		{
			if ( (gObj[tObjNum].Type == t1 || gObj[tObjNum].Type == t2) && (gObj[tObjNum].Live != FALSE) )
			{
				if ( (gObj[tObjNum].Class >= 100 && gObj[tObjNum].Class < 110 ) || (gObj[tObjNum].Type == OBJ_MONSTER && gObj[tObjNum].m_RecallMon >= 0) )
				{

				}
				else if ( (gObj[tObjNum].Authority &2) != 2 && (gObj[tObjNum].Authority &32) != 32 && gObj[tObjNum].Teleport == 0 )
				{
					tx = lpObj->X - gObj[tObjNum].X;
					ty = lpObj->Y - gObj[tObjNum].Y;
					dis = (int)(sqrt((double)tx * tx + ty * ty));
					lpObj->VpPlayer2[n].dis = dis;

					if ( dis < mindis )
					{
						searchtarget = tObjNum;
						mindis = dis;
					}
				}
			}
		}
	}

	return searchtarget;
}

int gObjGuardSearchEnemy(LPOBJ lpObj)
{
	int n;
	int tx;
	int ty;
	int dis;
	int mindis = lpObj->m_ViewRange;
	int searchtarget = -1;
	int tObjNum;
	BYTE attr;

	for (n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;

		if ( tObjNum >= 0 )
		{
			BOOL bEnableAttack = FALSE; //Season 2.5 add-on

			if( gObj[tObjNum].PartyNumber >= 0) //Season 2.5 add-on
			{
				if( gParty.GetPkLevel(gObj[tObjNum].PartyNumber) > 4 )
				{
					bEnableAttack = TRUE;
				}
				
			}
			else if( gObj[tObjNum].m_PK_Level > 4 ) 
			{
				bEnableAttack = TRUE;
			}
			
			if ( gObj[tObjNum].Type == OBJ_USER )
			{
				if(bEnableAttack == TRUE) //Season 2.5 add-on
				{
					attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);

					if ( (attr&1) != 1 )
					{
						tx = lpObj->X - gObj[tObjNum].X;
						ty = lpObj->Y - gObj[tObjNum].Y;
						dis = (int)(sqrt((double)tx * tx + ty * ty));
						lpObj->VpPlayer2[n].dis = dis;

						if ( dis < mindis )
						{
							searchtarget = tObjNum;
							mindis = dis;
						}
					}
				}
			}
		}
	}

	return searchtarget;
}

//Identical
void gObjMonsterStateProc(LPOBJ lpObj, int aMsgCode, int aIndex, int aMsgSubCode) //00415F10
{
	if ( lpObj->m_iMonsterBattleDelay > 0 )
	{
		return;
	}

	switch ( aMsgCode )
	{
		case 0:

			if ( lpObj->m_Attribute == 0 )
			{
				return;
			}
			
			if ( gObj[aIndex].Live == FALSE || gObj[aIndex].m_State != 2)
			{
				return;
			}

			if ( lpObj->m_ActState.Emotion == 0 )
			{
				lpObj->m_ActState.Emotion = 1;
				lpObj->m_ActState.EmotionCount = 10;
			}
			else if ( lpObj->m_ActState.Emotion == 1 )
			{
				lpObj->m_ActState.EmotionCount = 10;
			}

			if ( lpObj->m_ActState.Attack == 0 && lpObj->PathStartEnd == 0)
			{
				if ( OBJMAX_RANGE(aIndex) )
				{
					int map = gObj[aIndex].MapNumber;
					BYTE attr;
					int dis = gObjCalDistance(lpObj, &gObj[aIndex]);
					int range;

					if ( lpObj->m_AttackType >= 100 )
					{
						range = lpObj->m_AttackRange +2;
					}
					else
					{
						range = lpObj->m_AttackRange;
					}

					if ( dis <= range )
					{
						if ( gObj[aIndex].m_RecallMon >= 0 )
						{
							if ( lpObj->m_RecallMon >= 0 )
							{
								if ( gObj[aIndex].Type == OBJ_MONSTER )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
							else
							{
								lpObj->TargetNumber = aIndex;
							}
						}
						else if ( (rand()%100) < 90 )
						{
							if ( lpObj->m_RecallMon >= 0 )
							{
								if ( gObj[aIndex].Type == OBJ_MONSTER )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
							else
							{
								lpObj->TargetNumber = aIndex;
							}
						}
					}
					else
					{
						BYTE wall = 0;

						wall = MapC[map].CheckWall2(lpObj->X, lpObj->Y, gObj[aIndex].X, gObj[aIndex].Y);

						if ( wall == 1 )
						{
							attr = MapC[map].GetAttr(gObj[aIndex].X, gObj[aIndex].Y);

							if ( (attr&1) != 1 )
							{
								if ( lpObj->TargetNumber < 0 )
								{
									lpObj->TargetNumber = aIndex;
								}
							}
						}
						else if( wall == 0x02 ) // 캐릭터가 앞에 있으면..
						{
						}
						else {	// 벽이거나 중간에 막혀 있다면..
							//lpObj->TargetNumber = aIndex;	// 공격상대로 지정하고	
						}

					}


					if ( lpObj->m_bIsInMonsterHerd != false && lpObj->TargetNumber == aIndex )
					{
						if ( lpObj->m_lpMonsterHerd )
						{
							lpObj->m_lpMonsterHerd->BeenAttacked (lpObj, &gObj[aIndex]);
						}
					}
				}
			}
			else
			{
				if ( (rand() % 2 )== 1 && lpObj->PathStartEnd == 0)
				{
					int IndexEnemy = lpObj->TargetNumber;

					if ( !OBJMAX_RANGE(IndexEnemy) )//Season 4.5 addon
					{
						return;
					}

					int EnemyMap = gObj[IndexEnemy].MapNumber;

					int enemydis = gObjCalDistance(lpObj, &gObj[aIndex]);
					int range;

					if ( lpObj->m_AttackType >= 100 )
					{
						range = lpObj->m_AttackRange + 2;
					}
					else
					{
						range = lpObj->m_AttackRange;
					}

					if ( enemydis <= range )
					{
						lpObj->m_ActState.Attack = 1;
						lpObj->TargetNumber = aIndex;
					}
					else
					{
						if ( MapC[EnemyMap].CheckWall2(lpObj->X, lpObj->Y, gObj[IndexEnemy].X, gObj[IndexEnemy].Y) == 1 )
						{
							lpObj->m_ActState.Attack = 1;
							lpObj->TargetNumber = aIndex;
						}
					}
				}
				else
				{
					int MaxLife = (int)lpObj->MaxLife;
					MaxLife >>= 1;

					if ( MaxLife > lpObj->Life )
					{
						if ( lpObj->m_Attribute != 2 )
						{
							lpObj->m_ActState.Emotion = 2;
							lpObj->m_ActState.EmotionCount = 2;
						}
					}
				}
			}
			break;
		case 1:
			if(lpObj->m_btCsNpcType != 0) //ok
			{
				switch(lpObj->m_btCsNpcType)
				{
					case 1:
						g_CastleSiege.DelNPC(lpObj->m_Index,lpObj->Class,lpObj->m_iCsNpcExistVal,1);
						break;
					case 2:
						g_CastleSiege.DelNPC(lpObj->m_Index,lpObj->Class,lpObj->m_iCsNpcExistVal,0);
						break;
					case 3:
						g_CastleSiege.DelNPC(lpObj->m_Index,lpObj->Class,lpObj->m_iCsNpcExistVal,0);
						break;
				}
				if( lpObj->Class == 287 || lpObj->Class == 286)
				{
					g_CsNPC_Mercenary.DeleteMercenary(lpObj->m_Index);
				}
				if(lpObj->Class == 278)
				{
					g_CsNPC_LifeStone.DeleteLifeStone(lpObj->m_Index);
				}
				gObjDel(lpObj->m_Index);
			}
			if ( KALIMA_MAP_RANGE(lpObj->MapNumber)  )
			{
				if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 || lpObj->Class == 197 || lpObj->Class == 267 )
				{
					g_KalimaGate.CreateKalimaGate2(aIndex, lpObj->MapNumber, lpObj->X, lpObj->Y);
				}
			}

			if(lpObj->Class == 409 || lpObj->Class == 410 || lpObj->Class == 411 || lpObj->Class == 412 )
			{
				//Quest Count Function
				g_QuestInfo.MonsterPlusKillCountParty(lpObj, &gObj[aIndex]);
			}

			gObjMonsterDieGiveItem(lpObj, &gObj[aIndex] );
			lpObj->NextActionTime = 500;

			if ( lpObj->m_RecallMon >= 0 )
			{
				gObjMonsterCallKill(lpObj->m_RecallMon);
			}

			if (  BC_MAP_RANGE(lpObj->MapNumber) != FALSE && lpObj->Type >= OBJ_MONSTER)
			{
				int iBridgeIndex = g_BloodCastle.GetBridgeIndex(lpObj->MapNumber); //season3 add-on

				if ( lpObj->Class == 89 || lpObj->Class == 95 || lpObj->Class == 112 || lpObj->Class == 118 || lpObj->Class == 124 || lpObj->Class == 130 || lpObj->Class == 143 || lpObj->Class == 433) //season3 changed
				{
					g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_KILL_COUNT++;
				}
				else
				{
					g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_MONSTER_KILL_COUNT++;
				}

				if ( g_BloodCastle.CheckMonsterKillCount(iBridgeIndex) != false )
				{
					if (g_BloodCastle.m_BridgeData[iBridgeIndex].m_bBC_MONSTER_KILL_COMPLETE == false )
					{
						g_BloodCastle.m_BridgeData[iBridgeIndex].m_bBC_MONSTER_KILL_COMPLETE = true;
						g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_MONSTER_MAX_COUNT = -1;

						PMSG_STATEBLOODCASTLE pMsg;

						PHeadSetB((LPBYTE)&pMsg, 0x9B, sizeof(PMSG_STATEBLOODCASTLE));

						pMsg.btPlayState = BC_STATE_PLAYEND;
						pMsg.wRemainSec = 0;
						pMsg.wMaxKillMonster = 0;
						pMsg.wCurKillMonster = 0;
						pMsg.wUserHaveWeapon = 0;
						pMsg.btWeaponNum = -1;

						g_BloodCastle.SendBridgeAnyMsg((LPBYTE)&pMsg, pMsg.h.size, iBridgeIndex);
						g_BloodCastle.ReleaseCastleBridge(iBridgeIndex);

						g_BloodCastle.m_BridgeData[iBridgeIndex].m_dwBC_TICK_DOOR_OPEN = GetTickCount() + 3000;

						LogAddTD("[Blood Castle] (%d) All of the Monster Terminated -> %d", iBridgeIndex+1, g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_MONSTER_KILL_COUNT);

						g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_MAX_COUNT = g_BloodCastle.GetCurrentLiveUserCount(iBridgeIndex)*2;
						g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_KILL_COUNT = 0;

						if ( g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_MAX_COUNT > 10) 
						{
							g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_MAX_COUNT = 10;
						}
					}

					if (g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_MONSTER_SUCCESS_MSG_COUNT < 1 )
					{
						g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_MONSTER_SUCCESS_MSG_COUNT++;
						g_BloodCastle.SendNoticeMessage(iBridgeIndex, lMsg.Get(MSGGET(4, 144))); 
					}
					
				}

				if ( g_BloodCastle.m_BridgeData[iBridgeIndex].m_bBC_MONSTER_KILL_COMPLETE != false )
				{
					if ( g_BloodCastle.CheckBossKillCount(iBridgeIndex) != false )
					{
						if ( g_BloodCastle.m_BridgeData[iBridgeIndex].m_bBC_BOSS_MONSTER_KILL_COMPLETE == false )
						{
							g_BloodCastle.m_BridgeData[iBridgeIndex].m_bBC_BOSS_MONSTER_KILL_COMPLETE = true;
							g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_MAX_COUNT = -1;

							g_BloodCastle.SetSaintStatue(iBridgeIndex);

							LogAddTD("[Blood Castle] (%d) All of the Boss Monster Terminated -> %d", iBridgeIndex+1, g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_KILL_COUNT);
						}

						if ( g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_SUCCESS_MSG_COUNT < 1 )
						{
							g_BloodCastle.m_BridgeData[iBridgeIndex].m_iBC_BOSS_MONSTER_SUCCESS_MSG_COUNT++;
							g_BloodCastle.SendNoticeMessage(iBridgeIndex, lMsg.Get(MSGGET(4, 156)));
						}
					}
				}
			}
			
			break;


		case 2:
			if ( gObj[aIndex].Live != FALSE )
			{
				if ( BC_MAP_RANGE(gObj[aIndex].MapNumber) == FALSE )
				{
					if ( gObj[aIndex].Class != 131 || ((  (lpObj->Class-132)<0)?FALSE:((lpObj->Class-132)>2)?FALSE:TRUE)==FALSE )
					{
						gObjBackSpring(lpObj, &gObj[aIndex]);
					}
				}
			}

			break;

		case 3:
			lpObj->TargetNumber = -1;
			lpObj->LastAttackerID = -1;
			lpObj->m_ActState.Emotion = 0;
			lpObj->m_ActState.Attack = 0;
			lpObj->m_ActState.Move = 0;
			lpObj->NextActionTime = 1000;
			break;

		case 4:
			lpObj->m_ActState.Emotion = 3;
			lpObj->m_ActState.EmotionCount = 1;
			break;

		case 5:
			gObjMemFree(lpObj->m_Index);
			break;

		case 6:
			if ( gObj[aIndex].Live != FALSE )
			{
				gObjBackSpring2(lpObj, &gObj[aIndex], 2);
			}

			break;

		case 7:
			if ( gObj[aIndex].Live != FALSE )
			{
				gObjBackSpring2(lpObj, &gObj[aIndex], 3);
			}
			break;

		case 55:
			gObjAttack(lpObj, &gObj[aIndex], NULL, FALSE, 0, 0, FALSE,0);
			break;

		case 56:
			{
				LPOBJ lpTargetObj = &gObj[aIndex];

				if(gObjSearchActiveEffect(lpTargetObj, AT_POISON) == FALSE ) //season3 changed
				{
					if ( retResistance(lpTargetObj, 1) == 0 )
					{
						lpTargetObj->lpAttackObj = lpObj;
						gObjApplyBuffEffectDuration(lpTargetObj, AT_POISON, 19, 3, 0, 0, aMsgSubCode);
					}
				}
			}
			break;

		case 57:
			{
				LPOBJ lpTargetObj = &gObj[aIndex];
				gObjBackSpring2(lpTargetObj, lpObj, aMsgSubCode);
			}
			break;
		//Miss Case 58 for Eletrict Surge
	}
}

void gObjMonsterProcess(LPOBJ lpObj)
{
	gObjMsgProc(lpObj);

	if ( lpObj->Live == FALSE )
	{
		return;
	}

	if ( lpObj->m_iMonsterBattleDelay > 0 )
	{
		lpObj->m_iMonsterBattleDelay--;
	}

	if ( (GetTickCount() - lpObj->CurActionTime ) < (lpObj->NextActionTime + lpObj->DelayActionTime) )
	{
		return;
	}

	lpObj->CurActionTime = GetTickCount();

	if ( BC_MAP_RANGE(lpObj->MapNumber) != FALSE )
	{
		if ( lpObj->Class == 131|| ((lpObj->Class-132<0)?FALSE:(lpObj->Class-132>2)?FALSE:TRUE) != FALSE )
		{
			return;
		}
	}

	if ( ((lpObj->m_Attribute < 51)?FALSE:(lpObj->m_Attribute > 58)?FALSE:TRUE) != FALSE )
	{
		if ( lpObj->m_Attribute == 58 )
		{
			g_KalimaGate.KalimaGateAct2(lpObj->m_Index);
			return;
		}

		g_KalimaGate.KalimaGateAct(lpObj->m_Index);
		return;
	}

	if(lpObj->Class == 283)
	{
		return;
	}
	else if(lpObj->Class == 288)
	{
		return;
	}
	else if(lpObj->Class == 278)
	{
		return;
	}

	if ( lpObj->Class >= 100 && lpObj->Class <= 110 )
	{
		gObjMonsterTrapAct(lpObj);
		
	}
	else if ( lpObj->Class == 200 )
	{
		int ground;
		int team = gCheckGoal(lpObj->X, lpObj->Y, ground);

		if ( team >= 0 )
		{
			gObjMonsterRegen(lpObj);
			gBattleSoccerScoreUpdate(ground, team);
			return;
		}
	}
	else 
	{
		if ( lpObj->Class == 287 || lpObj->Class == 286 )
		{
			g_CsNPC_Mercenary.MercenaryAct(lpObj->m_Index);
		}
		else if ( lpObj->m_bIsInMonsterHerd != false )
		{
			if ( lpObj->m_lpMonsterHerd != NULL )
			{
				lpObj->m_lpMonsterHerd->MonsterBaseAct(lpObj);
			}
		}
		else
		{
			gObjMonsterBaseAct(lpObj);
		}
	}

	if ( lpObj->m_Attribute == 100 )
	{
		if ( lpObj->m_RecallMon >= 0 && lpObj->m_RecallMon < OBJMAX )
		{
			LPOBJ lpCallMonObj;
			BOOL Success = FALSE;

			lpCallMonObj = &gObj[lpObj->m_RecallMon];


			if ( lpObj->MapNumber != lpCallMonObj->MapNumber )
			{
				Success = TRUE;
			}
	
			if ( gObjCalDistance(lpCallMonObj, lpObj)> 14 )
			{
				Success = TRUE;
			}

			if ( Success == TRUE )
			{
				gObjTeleportMagicUse(lpObj->m_Index, (BYTE)lpCallMonObj->X+1, lpCallMonObj->Y);
				lpObj->MapNumber = lpCallMonObj->MapNumber;

				return;
			}
		}
	}

	if ( lpObj->m_ActState.Move != 0 )
	{
		if ( PathFindMoveMsgSend(lpObj ) == TRUE )
		{
			lpObj->m_ActState.Move  = (DWORD)0;
		}

		lpObj->m_ActState.Move = (DWORD)0;
		return;
	}

	if ( lpObj->m_ActState.Attack == 1 )
	{
		if(lpObj->Connected == PLAYER_PLAYING && lpObj->Type == OBJ_MONSTER && lpObj->Class == 459 )//Season 4.5 addon
		{
			return;
		}

		if ( TMonsterSkillManager::CheckMonsterSkill(lpObj->Class) )
		{
			BOOL bEnableAttack = TRUE;

			if ( lpObj->TargetNumber < 0 )//Season 4.5 remake
			{
				lpObj->TargetNumber = -1;
				lpObj->m_ActState.Emotion = 0;
				lpObj->m_ActState.Attack = 0;
				lpObj->m_ActState.Move = 0;
				lpObj->NextActionTime = 1000;
				return;
			}

			if ( gObj[lpObj->TargetNumber].Live == FALSE || gObj[lpObj->TargetNumber].Teleport != 0)
				bEnableAttack = FALSE;

			if ( gObj[lpObj->TargetNumber].Connected <= PLAYER_LOGGED || gObj[lpObj->TargetNumber].CloseCount != -1 )
				bEnableAttack = FALSE;

			if ( bEnableAttack == FALSE )
			{
				lpObj->TargetNumber = -1;
				lpObj->m_ActState.Emotion = 0;
				lpObj->m_ActState.Attack = 0;
				lpObj->m_ActState.Move = 0;
				lpObj->NextActionTime = 1000;
				return;
			}
			
			if ( rand()%4 == 0 )
			{
				PMSG_ATTACK pAttackMsg;

				pAttackMsg.AttackAction = 120;
				pAttackMsg.DirDis = lpObj->Dir;
				pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
				pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);

				GCActionSend(lpObj, 120, lpObj->m_Index, lpObj->TargetNumber);
				gObjAttack(lpObj, &gObj[lpObj->TargetNumber], NULL, FALSE, 0, 0, FALSE,0);
			}
			else
			{
				TMonsterSkillManager::UseMonsterSkill(lpObj->m_Index, lpObj->TargetNumber, 0, -1, NULL);
			}

			lpObj->m_ActState.Attack = 0;
		}
		else
		{
			int AttackType = lpObj->m_AttackType;
			int lc6 = 0;

			if ( AttackType >= 100 )
			{
				if ( (rand()%5) == 0 )
				{
					AttackType -= 100;
					lc6 = TRUE;
				}
				else
				{
					AttackType = 0;
				}
			}

			if ( lc6 != FALSE || lpObj->m_AttackType == 50)
			{
				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Connected > PLAYER_LOGGED && gObj[lpObj->TargetNumber].CloseCount == -1 )
					{
						if ( gObj[lpObj->TargetNumber].Live == FALSE )
						{
							lpObj->TargetNumber = -1;
							lpObj->m_ActState.Emotion = 0;
							lpObj->m_ActState.Attack = 0;
							lpObj->m_ActState.Move = 0;
							lpObj->NextActionTime = 1000;
						}
						else if ( gObj[lpObj->TargetNumber].Teleport == 0 )
						{
							gObjMonsterMagicAttack(lpObj, -1);

							if ( lpObj->Type == OBJ_MONSTER )
							{
								if ( lpObj->m_bIsInMonsterHerd != false )
								{
									if (lpObj->m_lpMonsterHerd != NULL )
									{
										lpObj->m_lpMonsterHerd->MonsterAttackAction(lpObj, &gObj[lpObj->TargetNumber]);
									}
								}
							}
						}
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.Emotion = 0;
						lpObj->m_ActState.Attack = 0;
						lpObj->m_ActState.Move = 0;
						lpObj->NextActionTime = 1000;
					}
				}
			}
			else
			{
				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Connected > PLAYER_LOGGED &&  gObj[lpObj->TargetNumber].CloseCount == -1 )
					{
						if ( gObj[lpObj->TargetNumber].Live == FALSE )
						{
							lpObj->TargetNumber = -1;
							lpObj->m_ActState.Emotion = 0;
							lpObj->m_ActState.Attack = 0;
							lpObj->m_ActState.Move = 0;
							lpObj->NextActionTime = 1000;
						}
						else if ( gObj[lpObj->TargetNumber].Teleport == 0 )
						{
							gObjMonsterAttack(lpObj, &gObj[lpObj->TargetNumber]);

							if ( lpObj->Type == OBJ_MONSTER )
							{
								if ( lpObj->m_bIsInMonsterHerd != false )
								{
									if (lpObj->m_lpMonsterHerd != NULL )
									{
										lpObj->m_lpMonsterHerd->MonsterAttackAction(lpObj, &gObj[lpObj->TargetNumber]);
									}
								}
							}
						}
						
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.Emotion = 0;
						lpObj->m_ActState.Attack = 0;
						lpObj->m_ActState.Move = 0;
						lpObj->NextActionTime = 1000;
					}
				}
			}

			lpObj->m_ActState.Attack = 0;
		}
	}
}

//Identical
void gObjMonsterMagicAttack(LPOBJ lpObj, int iMonsterClass) //00417C90
{
	int tObjNum;
	int count = 0;

	PMSG_BEATTACK_COUNT pCount;
	PMSG_BEATTACK pAttack;

	BYTE AttackSendBuff[256];
	int ASBOfs = 0;

	PMSG_DURATION_MAGIC_RECV pDuration;

	pCount.MagicNumberH = 0;
	pCount.MagicNumberL = 0;

	pDuration.Dir = 0;

	pDuration.X = lpObj->X;
	pDuration.Y = lpObj->Y;

	CGDurationMagicRecv(&pDuration, lpObj->m_Index);

	pCount.h.c = 0xC1;
	pCount.h.headcode = PROTOCOL_BEATTACK;
	pCount.h.size = 0;
	pCount.MagicNumberH = 0;
	pCount.MagicNumberL = 0;
	pCount.Count = 0;
	pCount.X = lpObj->X;
	pCount.Y = lpObj->Y;
	ASBOfs = sizeof(pCount);

	while ( true )
	{
		if ( lpObj->VpPlayer2[count].state )
		{
			if ( lpObj->VpPlayer2[count].type == OBJ_USER )
			{
				tObjNum = lpObj->VpPlayer2[count].number;

				if ( tObjNum >= 0 )
				{
					if ( lpObj->Class == 77 )
					{
						pAttack.NumberH = SET_NUMBERH(tObjNum);
						pAttack.NumberL = SET_NUMBERL(tObjNum);
						memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
						ASBOfs+= sizeof(pAttack);
						pCount.Count++;
					}
					else if ( lpObj->Class == 275 || gObjCalDistance(lpObj, &gObj[tObjNum]) < 6 )
					{
						pAttack.NumberH = SET_NUMBERH(tObjNum);
						pAttack.NumberL = SET_NUMBERL(tObjNum);
						memcpy(&AttackSendBuff[ASBOfs], &pAttack, sizeof(pAttack));
						ASBOfs+= sizeof(pAttack);
						pCount.Count++;
					}
				}
			}
		}

		count++;

		if ( count > MAX_VIEWPORT_MONSTER-1 )
			break;
	}

	if ( pCount.Count > 0 )
	{
		pCount.h.size = ASBOfs;
		memcpy(AttackSendBuff, &pCount, sizeof(pCount));

		if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 || lpObj->Class == 197 || lpObj->Class == 267 || lpObj->Class == 275 )
		{
			gObjMonsterBeattackRecv(AttackSendBuff, lpObj->m_Index);
		}
		else
		{
			CGBeattackRecv(AttackSendBuff, lpObj->m_Index, TRUE);
		}
	}
}

void gObjUseMonsterSpecialAbillity(LPOBJ lpMonsterObj)
{
	if ( lpMonsterObj->Class == 275 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumberH = SET_NUMBERH(1);
		pAttackMsg.MagicNumberL = SET_NUMBERL(1);

		pAttackMsg.NumberH = SET_NUMBERH(lpMonsterObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpMonsterObj->TargetNumber);
		pAttackMsg.Dis = 0;

		if ( (lpMonsterObj->MaxLife / 25.0f) > lpMonsterObj->Life  )
		{
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
		}
		else if ( (lpMonsterObj->MaxLife / 5.0f) > lpMonsterObj->Life  )
		{
			CGMagicAttack(&pAttackMsg, lpMonsterObj->m_Index);
		}
	}
}

//Identical
void gObjMonsterBeattackRecv(BYTE * lpRecv, int aIndex) //00418100
{
	PMSG_BEATTACK_COUNT * lpCount = (PMSG_BEATTACK_COUNT *)lpRecv;

	int lOfs = sizeof(PMSG_BEATTACK_COUNT); //loc2
	int tNumber; //loc3
	CMagicInf * lpMagic; //loc4
	PMSG_BEATTACK * lpMsg; //loc5

	WORD MagicNumber = MAKE_NUMBERW(lpCount->MagicNumberH, lpCount->MagicNumberL);

	lpMagic = gObjGetMagic(&gObj[aIndex], MagicNumber);

	if ( lpMagic == NULL )
	{
		LogAdd("error-L3 %s %d", __FILE__, __LINE__);
		return;
	}

	int lOfs2 = lOfs;
	int pTargetNumber[128]={0};

	for (int i=0;i<lpCount->Count;i++)
	{
		lpMsg = (PMSG_BEATTACK *)&lpRecv[lOfs2];
		pTargetNumber[i] = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		lOfs2+= sizeof(PMSG_BEATTACK);
	}
	
	for (int n=0;n<lpCount->Count;n++)
	{
		lpMsg = (PMSG_BEATTACK *)&lpRecv[lOfs];
		tNumber = MAKE_NUMBERW(lpMsg->NumberH, lpMsg->NumberL);
		gObjAttack(&gObj[aIndex], &gObj[tNumber], lpMagic, 1, 1, 0 ,0,0);
		lOfs+= sizeof(PMSG_BEATTACK);
	}
}

//Identical 90
void gObjMonsterAttack(LPOBJ lpObj, LPOBJ lpTargetObj) //0041C190
{
	int AttackType = lpObj->m_AttackType;

	if ( AttackType >= 100 )
	{
		AttackType = 0;
	}

	if ( lpObj->m_iMonsterStunDelay > 0)
	{
		//return;
	}

	if( lpObj->m_iMonsterSleepDelay > 0)
	{
		//return;
	}

	if ( lpObj->m_iMonsterBattleDelay > 0 )
	{
		return;
	}

	if ( lpObj->Class == 144 || lpObj->Class == 174 || lpObj->Class == 182 || lpObj->Class == 190 || lpObj->Class == 260 || lpObj->Class == 268 )
	{
		if ( rand()%2 )
		{
			PMSG_MAGICATTACK pAttackMsg;

			pAttackMsg.MagicNumberH = SET_NUMBERH(0);
			pAttackMsg.MagicNumberL = SET_NUMBERL(0);

			pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
			pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
			pAttackMsg.Dis = 0;

			CGMagicAttack(&pAttackMsg, lpObj->m_Index);
			return;
		}

		AttackType = 0;
	}

	if ( lpObj->Class == 161 || lpObj->Class == 181 || lpObj->Class == 189 || lpObj->Class == 197 || lpObj->Class == 267 || lpObj->Class == 275  )
	{
		PMSG_MAGICATTACK pAttackMsg;

		WORD MagicNumber = rand()%6+1;

		pAttackMsg.MagicNumberH = SET_NUMBERH(MagicNumber);
		pAttackMsg.MagicNumberL = SET_NUMBERL(MagicNumber);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);

		if ( MagicNumber == 1 || MagicNumber == 2 || MagicNumber == 0 )
		{
			gObjUseMonsterSpecialAbillity(lpObj);	// Kundun
		}

		gObjMonsterMagicAttack(lpObj, lpObj->Class);
		return;
	}

	if ( lpObj->Class == 149 || lpObj->Class == 179 || lpObj->Class == 187 || lpObj->Class == 195 || lpObj->Class == 265 || lpObj->Class == 273  )
	{
		PMSG_MAGICATTACK pAttackMsg;

		WORD MagicNumber = rand()%2+1;

		pAttackMsg.MagicNumberH = SET_NUMBERH(MagicNumber);
		pAttackMsg.MagicNumberL = SET_NUMBERL(MagicNumber);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
		return;
	}
	
	if (     lpObj->Class == 145
          || lpObj->Class == 175
          || lpObj->Class == 183
          || lpObj->Class == 191
          || lpObj->Class == 261
          || lpObj->Class == 269
          || lpObj->Class == 146
          || lpObj->Class == 176
          || lpObj->Class == 184
          || lpObj->Class == 192
          || lpObj->Class == 262
          || lpObj->Class == 270
          || lpObj->Class == 147
          || lpObj->Class == 177
          || lpObj->Class == 185
          || lpObj->Class == 193
          || lpObj->Class == 263
          || lpObj->Class == 271
          || lpObj->Class == 148
          || lpObj->Class == 178
          || lpObj->Class == 186
          || lpObj->Class == 194
          || lpObj->Class == 264
          || lpObj->Class == 272
          || lpObj->Class == 160
          || lpObj->Class == 180
          || lpObj->Class == 188
          || lpObj->Class == 196
          || lpObj->Class == 266
          || lpObj->Class == 274 )
	{
		if ( (rand()%2) )
		{
			PMSG_MAGICATTACK pAttackMsg;

			pAttackMsg.MagicNumberH = SET_NUMBERH(1);
			pAttackMsg.MagicNumberL = SET_NUMBERL(1);

			pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
			pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
			pAttackMsg.Dis = 0;

			CGMagicAttack(&pAttackMsg, lpObj->m_Index);
			return;
		}
		AttackType = 0;
	}
	
	if (	 lpObj->Class == 89
          || lpObj->Class == 95
          || lpObj->Class == 112
          || lpObj->Class == 118
          || lpObj->Class == 124
          || lpObj->Class == 130
          || lpObj->Class == 143
		  || lpObj->Class == 433)
	{

		PMSG_MAGICATTACK pAttackMsg;

		WORD MagicNumber = rand()%2+1;

		pAttackMsg.MagicNumberH = SET_NUMBERH(MagicNumber);
		pAttackMsg.MagicNumberL = SET_NUMBERL(MagicNumber);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else if (  lpObj->Class == 163
            || lpObj->Class == 165
            || lpObj->Class == 167
            || lpObj->Class == 169
            || lpObj->Class == 171
            || lpObj->Class == 173
			|| lpObj->Class == 427)
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumberH = SET_NUMBERH(1);
		pAttackMsg.MagicNumberL = SET_NUMBERL(1);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else if ( lpObj->Class == 66 || lpObj->Class == 73 || lpObj->Class == 77 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumberH = SET_NUMBERH(1);
		pAttackMsg.MagicNumberL = SET_NUMBERL(1);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else if ( lpObj->Class == 66 || lpObj->Class == 73 || lpObj->Class == 77 )
	{
		PMSG_MAGICATTACK pAttackMsg;

		pAttackMsg.MagicNumberH = SET_NUMBERH(1);
		pAttackMsg.MagicNumberL = SET_NUMBERL(1);

		pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
		pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
		pAttackMsg.Dis = 0;

		CGMagicAttack(&pAttackMsg, lpObj->m_Index);
	}
	else
	{
		switch ( AttackType ) 
		{
			case 0:
				{
					PMSG_ATTACK pAttackMsg;

					pAttackMsg.AttackAction = 120;
					pAttackMsg.DirDis = lpObj->Dir;
					pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
					pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);

					CGAttack(&pAttackMsg, lpObj->m_Index);
				}
				break;
		
			default:
				{
					PMSG_MAGICATTACK pAttackMsg;

					pAttackMsg.MagicNumberH = SET_NUMBERH(0);
					pAttackMsg.MagicNumberL = SET_NUMBERL(0);

					pAttackMsg.NumberH = SET_NUMBERH(lpObj->TargetNumber);
					pAttackMsg.NumberL = SET_NUMBERL(lpObj->TargetNumber);
					pAttackMsg.Dis = 0;

					CGMagicAttack(&pAttackMsg, lpObj->m_Index);
				}
		}
	}
}

//Identical
BOOL PathFindMoveMsgSend(LPOBJ lpObj) //00418F70
{
	if ( gObjSearchActiveEffect(lpObj, AT_ICE_ARROW) == TRUE || gObjSearchActiveEffect(lpObj, AT_STUN) == TRUE ) //season3 changed
	{
		return FALSE;
	}

	if (gObjSearchActiveEffect(lpObj, AT_SLEEP) == TRUE) //season3 add-on
	{
		return FALSE;
	}

	PATH_t path;
	PMSG_MOVE pMove;
	BYTE bPath[8];
	
	pMove.h.c = 0xC1;
	pMove.h.headcode = PROTOCOL_MOVE;
	pMove.h.size = sizeof(pMove);
	pMove.X = lpObj->X;
	pMove.Y = lpObj->Y;

	BOOL bPathFound = FALSE;

	if ( lpObj->Type == OBJ_MONSTER && lpObj->m_bIsInMonsterHerd != FALSE )
	{
		bPathFound = MapC[lpObj->MapNumber].PathFinding3(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY, &path);
	}
	else
	{
		bPathFound = MapC[lpObj->MapNumber].PathFinding2(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY, &path);
	}

	if ( bPathFound )
	{
		int tx;
		int ty;
		int sx;
		int sy;
		BYTE pos = 0;

		memset(bPath, 0, sizeof(bPath));

		bPath[0] = (lpObj->Dir<<4) + ((path.PathNum-1)&0x0F);

		sx = lpObj->X;
		sy = lpObj->Y;
		lpObj->PathX[0] = lpObj->X;
		lpObj->PathY[0] = lpObj->Y;
		lpObj->PathDir[0] = lpObj->Dir;

		for (int n=1;n<path.PathNum;n++)
		{
			tx = path.PathX[n];
			ty = path.PathY[n];
			pos = GetPathPacketDirPos(tx-sx, ty-sy);
			lpObj->PathX[n] = tx;
			lpObj->PathY[n] = ty;
			lpObj->PathDir[n] = pos;
			sx = tx;
			sy = ty;

			if ( (n%2)==1 )
			{
				bPath[(n+1)/2] = (pos<<4);
			}
			else
			{
				bPath[(n+1)/2] |= pos;
			}
		}

		lpObj->Dir = bPath[0] >> 4;
		lpObj->PathCount = bPath[0] & 0x0F;
		lpObj->PathCur = 1;
		lpObj->PathTime = GetTickCount();
		bPath[0] &= 0x0F;
		bPath[0] |= pos<<4;
		memcpy(pMove.Path, bPath, sizeof(pMove.Path));

		if ( lpObj->PathCount > 0 )
		{
			MapC[lpObj->MapNumber].ClearStandAttr(lpObj->m_OldX, lpObj->m_OldY);
			MapC[lpObj->MapNumber].SetStandAttr(sx, sy);
			lpObj->m_OldX = sx;
			lpObj->m_OldY = sy;
		}

		PMoveProc(&pMove, lpObj->m_Index);
		return TRUE;
	}

	return FALSE;
}

//Identical
void gObjMonsterMoveAction(LPOBJ lpObj) //00419530
{
	if ( gObjSearchActiveEffect(lpObj, AT_ICE_ARROW) == TRUE || gObjSearchActiveEffect(lpObj, AT_STUN) == TRUE ) //season3 changed
	{
		return;
	}

	if (gObjSearchActiveEffect(lpObj, AT_SLEEP) == TRUE) //season3 add-on
	{
		return;
	}

	int maxmoverange = lpObj->m_MoveRange*2+1;
	int searchc=10;
	lpObj->NextActionTime = 1000;
	BYTE tpx;
	BYTE tpy;

	while ( searchc-- != 0 )
	{
		__try
		{
			tpx = (lpObj->X - lpObj->m_MoveRange) + (rand()%maxmoverange);
			tpy = (lpObj->Y - lpObj->m_MoveRange) + (rand()%maxmoverange);
		}
		__except(maxmoverange=1, 1)
		{

		}

		int mchk = gObjMonsterMoveCheck(lpObj, tpx, tpy);
		BYTE attr = MapC[lpObj->MapNumber].GetAttr(tpx, tpy);

		if ( (lpObj->Class ==249 || lpObj->Class == 247) && mchk )	// Guard
		{
			if ( (attr&2)!=2)
			{
				lpObj->MTX = tpx;
				lpObj->MTY = tpy;
				lpObj->m_ActState.Move = 1;
				lpObj->NextActionTime = 3000;
				return;
			}
		}
		else
		{
			if ( (attr&1)!=1 && (attr&2)!=2 && (attr&4)!=4 && (attr&8)!= 8 && mchk )
			{
				lpObj->TargetNumber = -1;
				lpObj->m_ActState.Attack = 0;
				lpObj->NextActionTime = 500;
				lpObj->m_ActState.Emotion = 0;
				lpObj->MTX = tpx;
				lpObj->MTY = tpy;
				lpObj->m_ActState.Move = 1;
				return;
			}
		}
	}
}

//Identical
void gObjMonsterBaseAct(LPOBJ lpObj) //004198D0
{
	LPOBJ lpTargetObj = NULL;

	if(lpObj->TargetNumber >= 0)
	{
		lpTargetObj = &gObj[lpObj->TargetNumber];
	}
	else
	{
		lpObj->m_ActState.Emotion = 0;
	}

	if (gObjSearchActiveEffect(lpObj, AT_SLEEP) == TRUE) //season3 add-on
	{
		return;
	}

	if ( lpObj->m_ActState.Emotion == 0 )
	{
		if ( lpObj->m_Attribute )
		{
			if ( lpObj->m_ActState.Attack )
			{
				lpObj->m_ActState.Attack = 0;
				lpObj->TargetNumber = -1;
				lpObj->NextActionTime = 500;
				//if( lpObj->m_Attribute == 100 )	LogAdd("공격중 이었다면 잠깐 쉰다.");
			}

			int actcode1 = rand()%2;

			if ( lpObj->m_Attribute == 100 )
			{
				actcode1 = 1;
			}
			
			if ( actcode1 == 0 )
			{
				lpObj->m_ActState.Rest = 1;
				lpObj->NextActionTime = 500;
			}
			else if ( lpObj->m_MoveRange > 0 && (gObjSearchActiveEffect(lpObj, AT_ICE_ARROW) == FALSE) && (gObjSearchActiveEffect(lpObj, AT_STUN) == FALSE) && (gObjSearchActiveEffect(lpObj, AT_SLEEP) == FALSE) ) //season3 changed
			{
				if ( lpObj->m_Attribute != 100 )
				{
					gObjMonsterMoveAction(lpObj);
				}
				else
				{
					int tx=0;
					int ty=0;

					if ( lpObj->m_RecallMon >= 0 )
					{
						if ( gObj[lpObj->m_RecallMon].Connected > PLAYER_LOGGED )
						{
							LPOBJ lpRecallObj = &gObj[lpObj->m_RecallMon];

							if ( lpRecallObj->m_Rest == FALSE )
							{
								if ( gObjGetTargetPos(lpObj, lpRecallObj->X, lpRecallObj->Y, tx, ty) == TRUE )
								{
									lpObj->MTX = tx;
									lpObj->MTY = ty;
									lpObj->m_ActState.Move = 1;
									lpObj->NextActionTime = 1000;
								}
							}
						}
					}
				}
			}

			if (lpObj->Class == 249 || lpObj->Class == 247 )
			{
				if ( gEvent1 )
				{
					if ( !(rand()%30) )
					{
						if ( lpObj->m_PK_Count == 0 )
						{
							ChatSend(lpObj,ExConfig.CommonServer.GuardMessage);
							lpObj->m_PK_Count = 0;
						}
					}
				}

				lpObj->TargetNumber = gObjGuardSearchEnemy(lpObj);

				if ( lpObj->TargetNumber >= 0 )
				{
					if ( gObj[lpObj->TargetNumber].Class >= 248 )
					{
						lpObj->TargetNumber = -1;
					}
				}
			}
			else 
			{
				if ( lpObj->m_Attribute == 100 )
				{
					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_MONSTER);
					if( lpObj->m_Attribute == 100 )	
					{
						//if( lpObj->TargetNumber>=0) LogAdd("적을 찾아 이동한다.");
					}
				}
				else
				{
					lpObj->TargetNumber = gObjMonsterSearchEnemy(lpObj, OBJ_USER);
				}
			}

			if ( lpObj->TargetNumber >= 0 )
			{
				lpObj->m_ActState.EmotionCount = 30;
				lpObj->m_ActState.Emotion = 1;
			}
		}
	}
	else if ( lpObj->m_ActState.Emotion == 1 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		if ( lpObj->TargetNumber >= 0 && lpObj->PathStartEnd == 0)
		{
			if ( BC_MAP_RANGE(lpObj->MapNumber) )
			{
				int iRAND_CHANGE_TARGET = rand()%10;

				if ( iRAND_CHANGE_TARGET == 3 )
				{
					lpObj->LastAttackerID = -1;
				}

				if ( iRAND_CHANGE_TARGET == 1 )
				{
					if ( lpObj->LastAttackerID != -1 && lpObj->LastAttackerID != lpObj->TargetNumber )
					{
						if ( gObj[lpObj->LastAttackerID].Connected > PLAYER_LOGGED && lpObj->MapNumber == gObj[lpObj->LastAttackerID].MapNumber )
						{
							lpObj->TargetNumber = lpObj->LastAttackerID;
							lpTargetObj = &gObj[lpObj->LastAttackerID];
						}
					}
				}
			}

			int dis = gObjCalDistance(lpObj, lpTargetObj);
			int attackrange;

			if ( lpObj->m_AttackType >= 100 )
			{
				attackrange = lpObj->m_AttackRange+2;
			}
			else
			{
				attackrange = lpObj->m_AttackRange;
			}

			if ( dis <= attackrange )
			{
				int tuser = lpObj->TargetNumber;
				int map = gObj[tuser].MapNumber;
				BYTE attr;

				if ( MapC[map].CheckWall(lpObj->X, lpObj->Y, gObj[tuser].X, gObj[tuser].Y) == TRUE )
				{
					attr = MapC[map].GetAttr(gObj[tuser].X, gObj[tuser].Y);

					if ( (attr&1) != 1 )
					{
						lpObj->m_ActState.Attack = 1;
					}
					else
					{
						lpObj->TargetNumber = -1;
						lpObj->m_ActState.EmotionCount = 30;
						lpObj->m_ActState.Emotion = 1;
					}

					lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y);
					lpObj->NextActionTime = lpObj->m_AttackSpeed;
					if( lpObj->m_Attribute == 100 )	{
						//LogAdd("근처로 가서 공격한다. 다음 액선 시간 %d",lpObj->NextActionTime);
					}
				}
				else //if(lpObj->Class == 275) //Season 2.5 add-on
				{
					lpObj->TargetNumber = -1;
					lpObj->m_ActState.Attack = 0;
					lpObj->NextActionTime = 500;
					lpObj->m_ActState.Emotion = 0;
					lpObj->m_ActState.Move = 1;
				}
			}
			else
			{
				if ( gObjMonsterGetTargetPos(lpObj) == TRUE )
				{
					if ( MapC[lpObj->MapNumber].CheckWall(lpObj->X, lpObj->Y, lpObj->MTX, lpObj->MTY) == TRUE )
					{
						lpObj->m_ActState.Move = 1;
						lpObj->NextActionTime = 400;
						lpObj->Dir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y);
					}
					else
					{
						gObjMonsterMoveAction(lpObj);
						lpObj->m_ActState.Emotion = 3;
						lpObj->m_ActState.EmotionCount = 10;

					}
				}
				else
				{
					gObjMonsterMoveAction(lpObj);
				}
			}
		}
		else
		{
		}
	}
	else if ( lpObj->m_ActState.Emotion == 2 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 1;
		lpObj->NextActionTime = 800;

		if ( lpTargetObj != NULL)
		{
			int tdir = GetPathPacketDirPos(lpTargetObj->X-lpObj->X, lpTargetObj->Y-lpObj->Y)*2;
			lpObj->MTX += RoadPathTable[tdir] * (-3);
			lpObj->MTY += RoadPathTable[tdir+1] * (-3);
		}
	}
	else if ( lpObj->m_ActState.Emotion == 3 )
	{
		if ( lpObj->m_ActState.EmotionCount > 0 )
		{
			lpObj->m_ActState.EmotionCount--;
		}
		else
		{
			lpObj->m_ActState.Emotion = 0;
		}

		lpObj->m_ActState.Move = 0;
		lpObj->m_ActState.Attack = 0;
		lpObj->NextActionTime = 400;
	}
}

void gObjTrapAttackEnemySearchX(LPOBJ lpObj, int count)
{
	lpObj->TargetNumber = -1;
	int tObjNum;
	int pos = lpObj->X;
	int y = lpObj->Y;

	for(int n =0;n<count;n++)
	{
		pos++;
		for(int i =0; i< MAX_VIEWPORT_MONSTER; i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Type==OBJ_USER)
				{
					if(gObj[tObjNum].Live)
					{
						if(y == gObj[tObjNum].Y)
						{
							if(pos == gObj[tObjNum].X)
							{
								if((gObj[tObjNum].Authority&2)!=2)
								{
									lpObj->TargetNumber = tObjNum;
									return;
								}
							}
						}
					}
				}
			}
		}
	}
}

void gObjTrapAttackEnemySearchY(LPOBJ lpObj, int count)
{
	lpObj->TargetNumber = -1;
	int tObjNum;
	int pos = lpObj->Y;
	int x = lpObj->X;

	for(int n =0;n<count;n++)
	{
		pos--;
		for(int i =0; i< MAX_VIEWPORT_MONSTER; i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if(tObjNum >= 0)
			{
				if(gObj[tObjNum].Type==1)
				{
					if(gObj[tObjNum].Live)
					{
						if(pos == gObj[tObjNum].Y)
						{
							if(x == gObj[tObjNum].X)
							{
								if((gObj[tObjNum].Authority&2)!=2)
								{
									lpObj->TargetNumber = tObjNum;
									return;
								}
							}
						}
					}
				}
			}
		}
	}
}

void gObjTrapAttackEnemySearch(LPOBJ lpObj)
{
	int tObjNum;
	lpObj->TargetNumber = -1;

	for(int i = 0; i < MAX_VIEWPORT_MONSTER;i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if(tObjNum >= 0)
		{
			if(gObj[tObjNum].Type==1)
			{
				if(gObj[tObjNum].Live)
				{
					if(lpObj->Y == gObj[tObjNum].Y)
					{
						if(lpObj->X == gObj[tObjNum].X)
						{
							if((gObj[tObjNum].Authority&2)!=2)
							{
								lpObj->TargetNumber = tObjNum;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void gObjTrapAttackEnemySearchRange(LPOBJ lpObj,int iRange)
{
	int tObjNum = -1;
	int iTargetingRate = 0;
	int iSuccessRate = 0;

	lpObj->TargetNumber = -1;

	if(lpObj->VPCount <= 0)
	{
		return;
	}

	iTargetingRate = 100 / lpObj->VPCount;

	for(int i = 0; i < MAX_VIEWPORT_MONSTER;i++)
	{
		tObjNum = lpObj->VpPlayer2[i].number;

		if(tObjNum >= 0)
		{
			if(gObj[tObjNum].Type==1)
			{
				if(gObj[tObjNum].Live)
				{
					if((lpObj->Y - iRange) <= gObj[tObjNum].Y && (lpObj->Y + iRange) >= gObj[tObjNum].Y)
					{
						if((lpObj->X - iRange) <= gObj[tObjNum].X && (lpObj->X + iRange) >= gObj[tObjNum].X)
						{
							if((gObj[tObjNum].Authority&2)!=2)
							{
								lpObj->TargetNumber = tObjNum;
								iSuccessRate = rand()%100;

								if(iSuccessRate < iTargetingRate)
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void gObjMonsterTrapAct(LPOBJ lpObj)
{
	if(lpObj->VPCount2 < 1)
	{
		return;
	}

	if(lpObj->m_AttackRange > 0)
	{
		if(lpObj->Dir == 3)
		{
			gObjTrapAttackEnemySearchX(lpObj,lpObj->m_AttackRange+1);
		}
		else if(lpObj->Dir == 1)
		{
			gObjTrapAttackEnemySearchY(lpObj,lpObj->m_AttackRange+1);
		}
		else if(lpObj->Dir == 8)
		{
			gObjTrapAttackEnemySearchRange(lpObj,lpObj->m_AttackRange);
		}
	}
	else
	{
		gObjTrapAttackEnemySearch(lpObj);
	}

	if(lpObj->TargetNumber >= 0)
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}

BYTE NewOptionRand(int level)
{
	BYTE NOption = 0;
	NOption = 1 << (rand() % 6);

	if ( (NOption &2) != 0 )
	{
		if ( (rand()%2) != 0 )
		{
			NOption = 1 << (rand()%6);
		}
	}

	if ( (rand()% 4) == 0 )
	{
		NOption |= 1 << (rand()%6);
	}

	return NOption;
}

void InventoryDropItem(LPOBJ lpObj, int DropItem)
{
	return;
}

void gObjSkylandBossSheildAttack(LPOBJ lpObj)
{
	if ( lpObj->VPCount2 < 1 ) 
		return;

	if ( lpObj->m_SkyBossMonSheildLinkIndex == -1 )
		return;

	if ( lpObj->m_SkyBossMonSheild == 0 )
		return;

	lpObj->TargetNumber = -1;

	int tObjNum;
	int shieldindex = lpObj->m_SkyBossMonSheildLinkIndex;

	if ( gObj[shieldindex].Life < 0.0f )
		return;

	if ( lpObj->m_AttackRange > 0 )
	{
		for (int i=0;i<MAX_VIEWPORT_MONSTER;i++)
		{
			tObjNum = lpObj->VpPlayer2[i].number;

			if ( tObjNum >= 0 )
			{
				if ( gObj[tObjNum].Type == OBJ_USER )
				{
					if ( gObj[tObjNum].Live )
					{
						if ( gObjCheckTileArea(gObj[tObjNum].m_Index, lpObj->X, lpObj->Y, 2) )
						{
							if ( (gObj[tObjNum].Authority&2) != 2 )
							{
								lpObj->TargetNumber = tObjNum;
							}
						}
					}
				}
			}
		}
	}
	
	if ( lpObj->TargetNumber >= 0 )
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}

BOOL IsCanNotItemDtopInDevilSquare(int ItemType)
{
	int checkitemtype = ItemType  /MAX_SUBTYPE_ITEMS;
	int checkitemindex = ItemType % MAX_SUBTYPE_ITEMS;

	if ( checkitemtype >= 7 && checkitemtype <= 11 )
	{
		if (checkitemindex== 17 ||checkitemindex == 18||checkitemindex== 19 )
		{
			return FALSE;
		}
	}
	else if ( checkitemtype == 0 )
	{
		if (checkitemindex == 17 || checkitemindex == 18)
		{
			return FALSE;
		}
	}
	else if (checkitemtype == 12 )
	{
		if (checkitemindex== 12 || checkitemindex == 13 || checkitemindex == 14||
	checkitemindex == 16 || checkitemindex == 17 || checkitemindex == 18||
	checkitemindex == 19)
		{
			return FALSE;
		}
	}
	else if ( ItemType == ITEMGET(4,17) || ItemType ==ITEMGET(5,9)  )
	{
		return FALSE;
	}

	return TRUE;

}

void gObjRefillMonsterHP(LPOBJ lpMonsterObj, int iRefillHPSec)
{
	int iMonsterHP = (int)lpMonsterObj->Life;
	int iRefillHP = 0;

	if(lpMonsterObj->Live==0)
	{
		return;
	}

	if(lpMonsterObj->Class == 275)
	{
		LPOBJ lpObj;

		if(lpMonsterObj->iObjectSecTimer > giKundunRefillHPTime)
		{
			iRefillHP = rand() % ((giKundunRefillHP > 0)? giKundunRefillHP : 1) ;

			lpMonsterObj->iObjectSecTimer = 0;

			KUNDUN_EVENT_LOG.Output("[KUNDUN] HP Log -> [%d]회복  [%d]회복시간  [%7.0f]현재HP",	iRefillHP, giKundunRefillHPTime, lpMonsterObj->Life);
			lpMonsterObj->iObjectSecTimer = 0;
		}
		else
		{
			lpMonsterObj->iObjectSecTimer++;
		}

		if(lpMonsterObj->iObjectSecTimer % giKundunHPLogSaveTime == 0)
		{
			LogAddTD("[KUNDUN][Status Log] HP:%d RefillHP:%d Map:%d X:%d Y:%d", iMonsterHP,iRefillHP,lpMonsterObj->MapNumber,lpMonsterObj->X,lpMonsterObj->Y);

			if(gObjIsConnected(lpMonsterObj->LastAttackerID))
			{
				lpObj = &gObj[lpMonsterObj->LastAttackerID];
				LogAddTD("[KUNDUN][Attacker Info] [%s][%s] HP:%d MP:%d X:%d Y:%d", lpObj->AccountID,lpObj->Name,lpObj->Life,lpObj->Mana,lpObj->X,lpObj->Y);
			}
		}

		if(!g_CrywolfSync.GetOccupationState())
		{
			if(g_CrywolfSync.GetKundunHPRefillState()==1)
			{
				if(g_iCrywolfApplyMvpBenefit!=0)
				{
					iRefillHP = 0;
					iRefillHPSec = 0;
				}
			}
		}
	}

	iMonsterHP = iMonsterHP + iRefillHP + iRefillHPSec;

	if(lpMonsterObj->MaxLife < iMonsterHP)
	{
		lpMonsterObj->Life = lpMonsterObj->MaxLife;
	}
	else
	{
		lpMonsterObj->Life = (float)iMonsterHP;
	}
}

void gObjMonsterDieRewardItems(LPOBJ lpObj, LPOBJ lpTargetObj, int iCount, int iDropRateCommonItem, int iDropRateExcellentItem, int iDropRateSetItem, BOOL bMustHaveSkill, BOOL bMustHaveLuck, BOOL bMustHaveAdditionalOption)
{
	int store_count=0;
	int DropItemNum=0;
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	BYTE NOption=0;
	int item_drop=0;
	int exitem_drop=0;
	CItem * DropItem=NULL;
	int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
	int iSetDropPer=iDropRateSetItem;
	int iExtDropPer=iDropRateExcellentItem;
	int iCommonDropPer=iDropRateCommonItem;

	for (int i=0;i<iCount;i++)
	{
		BYTE cDropX = lpObj->X;
		BYTE cDropY = lpObj->Y;

		if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
		{
			cDropX = lpObj->X;
			cDropY = lpObj->Y;
		}

		if ( (rand()%10000) < iExtDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level-25);

			if ( !DropItem )
			{
				item_drop = 0;
				exitem_drop=0;
			}
			else
			{
				item_drop = 1;
				exitem_drop=1;
			}
		}
		else if ( (rand()%10000) < iCommonDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level);

			if ( !DropItem )
			{
				item_drop = 0;
			}
			else
			{
				item_drop = 1;
			}
		}

		if ( item_drop )
		{
			type = DropItem->m_Type;
			level = DropItem->m_Level;
			dur = DropItem->m_Durability;
			x = cDropX;
			y = cDropY;

			int option1rand;
			int option2rand;
			int option3rand;
			int optionc;

			if ( exitem_drop )
			{
				option1rand = 100;
				option2rand = 1;
				option3rand = rand()%100;
				optionc = rand()%3;
				NOption = NewOptionRand(lpObj->Level);
				level = 0;
			}
			else
			{
				option1rand = 6;
				option2rand = 4;
				option3rand = rand()%100;
				optionc = rand()%3;
				NOption = 0;
			}

			if ( (rand()%100) < option1rand )
			{
				Option1 = 1;
			}

			if ( (rand()%100) < option2rand )
			{
				Option2 = 1;
			}

			switch ( optionc )
			{
				case 0:
					if ( option3rand < 4 )
						Option3=3;
					break;
				case 1:
					if ( option3rand < 8 )
						Option3=2;
					break;
				case 2:
					if ( option3rand < 12 )
						Option3=1;
					break;
			}

			if ( DropItem->m_serial )
			{
				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x,(BYTE) y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, (BYTE)NOption, 0);
			}
			else
			{
				MapC[lpObj->MapNumber].MonsterItemDrop(type, level, dur, x, y, Option1, Option2, Option3, NOption, 0, MaxHitUser, 0, 0, NULL, 0xFF);
			}
		}
	}
}

//Identical
void gObjMonsterDieGiveItem(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	//Ex_DropSystem.DropItem(lpObj,lpTargetObj);

	int store_count=0;
	int ExtDropPer=0;
	int DropItemNum=0;
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;
	unsigned char NOption=0;
	BOOL item_drop=0;
	int n;
	CItem * DropItem=NULL;

#if(BM_QUEST_SYSTEM_)
	BMQuest.MonsterKill(lpTargetObj->m_Index,lpObj->m_Index);
#endif

	ExQuestSystem.MonsterKill(lpObj,lpTargetObj);
	ExPCPointSystem.MobKillForPCPoint(lpObj,lpTargetObj);
#if(_GRAND_HERO_SYSTEM_)
	if(GrandHero.BossDrop(lpObj,lpTargetObj)) return;
#endif
	
	if( lpObj->Class == 365 )//NEW
	{
		int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			
		BYTE cDropX = lpObj->X;
		BYTE cDropY = lpObj->Y;

		NewYearLuckMonsterItemBagOpen(lpTargetObj,lpObj->MapNumber,cDropX,cDropY);
		return;
	}


	if ( lpObj->Class == 340 )	// Dark Elf
	{
		if ( g_bCrywolfMonsterDarkElfItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= g_iCrywolfMonsterDarkElfItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ Crywolf ][Reward] Monster Dark Elf ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				CrywolfDarkElfItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}
	
	if ( lpObj->Class == 349 )	// Crywolf Boss Monster
	{
		if ( g_bCrywolfBossMonsterItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= g_iCrywolfBossMonsterItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ Crywolf ][Reward] Boss Monster ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				CrywolfBossMonsterItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}		
	if ( lpObj->Class == 362 || lpObj->Class == 363 )	// Maya Hand
	{
		if ( g_bKanturuMayaHandItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= g_iKanturuMayaHandItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ KANTURU ][ Reward ] MayaHand ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				KanturuMayaHandItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}
		return;
	}
	
	if ( lpObj->Class == 361 )	// NightMare
	{
		if ( g_bKanturuNightmareItemDrop )
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= g_iKanturuNightmareItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ KANTURU ][ Reward ] Nightmare ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
				{
					cDropX = lpObj->X;
					cDropY = lpObj->Y;
				}

				KanturuNightmareItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
			}
		}

		return;
	}

	if ( lpObj->Class == 459 && lpObj->Connected == 3 )	// Season 4.5 addon
	{
		if ( g_bRaklionSelupanItemDrop != 0)
		{
			int ItemDropRate = rand()%10000;

			if ( ItemDropRate <= g_iRaklionSelupanItemDropRate )
			{
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				LogAddTD("[ RAKLION ][ Reward ] Raklion ItemDrop MaxHitUser [%s][%s]",
					lpTargetObj->AccountID, lpTargetObj->Name);

				BYTE cDropX = lpObj->X;
				BYTE cDropY = lpObj->Y;

				for(int i = 0; i < ExConfig.CommonServer.CountItemDropSelupan; i++)	//10
				{
					if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 2, 2, 10))
					{
						cDropX = lpObj->X;
						cDropY = lpObj->Y;
					}

					RaklionBossMonsterItemBagOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
				}
				
			}
		}
		return;
	}		

	if ( lpObj->m_btCsNpcType )
		return;

	if ( lpObj->Class == 295 )
	{
		int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		int iMaxCount = 1;

		for ( int i=0; i<iMaxCount ; i++ )
		{
			BYTE cDropX = lpObj->X;
			BYTE cDropY = lpObj->Y;

			LogAddTD("[Castle HuntZone] Boss Monster ItemDrop MaxHitUser [%d][%s][%s]",
				i, lpTargetObj->AccountID, lpTargetObj->Name);

			if ( gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10) == FALSE )
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			if ( i == 0 )
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			CastleHuntZoneBossRewardOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
		}
		return;
	}
	
	if ( lpObj->Class == 275 ) 
	{
		LogAddTD("[★★Kundun EVENT] Kundun die, Killer [%s][%s]",
			lpTargetObj->AccountID, lpTargetObj->Name);

		KUNDUN_EVENT_LOG.Output("[★★Kundun EVENT] Kundun die, Killer [%s][%s]",
			lpTargetObj->AccountID, lpTargetObj->Name);

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		int iMaxNumOfRewardItem = 3;

		for ( int i=0;i<iMaxNumOfRewardItem;i++)
		{
			BYTE cDropX = lpObj->X;
			BYTE cDropY = lpObj->Y;

			if ( CHECK_LIMIT(MaxHitUser, OBJMAX) )
			{

				LogAddTD("[★Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);

				KUNDUN_EVENT_LOG.Output("[★Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
			}
			else
			{
				LogAddTD("[★Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);

				KUNDUN_EVENT_LOG.Output("[★Kundun EVENT] In KALIMA(7), ItemDrop MaxHitUser [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
			}

			if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 4, 4, 10))
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			if ( lpObj->Class == 275 ) 
			{
				if ( (rand()%10000) < ExConfig.CommonServer.KundunAncDrop )
				{
					MakeRewardSetItem(MaxHitUser, cDropX, cDropY, 1, lpObj->MapNumber);

					LogAddTD("[○Kundun EVENT] Drop SetItem ");
					KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop SetItem ");

					continue;
				}
			}

			if ( OBJMAX_RANGE(MaxHitUser ))
			{
				LogAddTD("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
				KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, gObj[MaxHitUser].AccountID, gObj[MaxHitUser].Name);
			}
			else
			{
				LogAddTD("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
				KUNDUN_EVENT_LOG.Output("[○Kundun EVENT] Drop Item [%d][%s][%s]",
					i, lpTargetObj->AccountID, lpTargetObj->Name);
			}

			KundunEventItemBoxOpen(lpTargetObj, lpObj->MapNumber, cDropX, cDropY);
		}

		return;
	}
	
	if ( lpObj->Class == 249 || lpTargetObj->Class == 249 ||
		lpObj->Class == 247 || lpTargetObj->Class == 247 )	
	{
		return;
	}

	if ( lpObj->m_RecallMon >= 0 )
	{
		return;
	}
	
	if ( lpObj->Class == 131 )	
	{
		return;
	}
	
	if ( BC_STATUE_RANGE(lpObj->Class-132) )
	{
		return;
	}
	
	if( lpObj->Class == 460 || lpObj->Class == 461 || lpObj->Class == 462) // Season 4.5 Addon
	{
		return;
	}


	if ( CC_MAP_RANGE(lpObj->MapNumber) )
	{
		g_ChaosCastle.SearchNDropMonsterItem(g_ChaosCastle.GetChaosCastleIndex(lpObj->MapNumber), lpObj->m_Index, lpTargetObj->m_Index);
		
		gObjDel(lpObj->m_Index);
		
		return;
	}

	if ( lpObj->m_bIsInMonsterHerd )
	{
		MonsterHerd * lpMH = lpObj->m_lpMonsterHerd;

		if ( lpMH )
		{
			if ( lpMH->MonsterHerdItemDrop(lpObj) )
			{
				return;
			}
		}
	}
	
	//IT CHECKS
	if ( IT_MAP_RANGE(lpObj->MapNumber) )
	{
		 int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
         g_IllusionTempleEvent.SearchNDropMonsterItem(lpTargetObj);

		 return;
	}

	if( lpObj->Class == 413)
	{
		GenericBoxItemBagOpen(lpTargetObj,lpObj->MapNumber,lpObj->X,lpObj->Y);
		return;
	}

	int itemrate = lpObj->m_ItemRate;
	int moneyrate = lpObj->m_MoneyRate;

	if ( itemrate < 1 )
		itemrate = 1;

	if ( moneyrate < 1 )
		moneyrate = 1;
/*
	if ( lpObj->Class == 44 ) // Dragon
	{
		dur = 0;//Season 4.5 remake;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;

		if ( (rand()%4) > 0 )
		{
			for ( int n=0;n<4;n++)
			{
				int x = lpObj->X-2;
				int y = lpObj->Y-2;
				x+= rand()%3;
				y+= rand()%3;

				MapC[lpObj->MapNumber].MoneyItemDrop(10000, x, y);
			}

			return;
		}
		
		if ( (rand()%3) < 2 )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			type = ItemGetNumberMake(14, 13);
			ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
				Option1, Option2, Option3, MaxHitUser, 0, 0);

			return;
		}

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		type = ItemGetNumberMake(14, 14);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
	*/
	if (lpObj->Class == 44)	//Dragon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("Dragon","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("Dragon","ItemIndex",13,ExDefGID);
		//level = GetPrivateProfileInt("Dragon","ItemLevel",0,ExDefGID);
		level = ExConfig.GoldenDrop.level44;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType44, ExConfig.GoldenDrop.ItemIndex44);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		return;
	}
	///////////////////////////
	//	GoldenInvasionDrop	//
	//////////////////////////
	if (lpObj->Class == 43)	//GoldenBudgeDragon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenBudgeDragon","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenBudgeDragon","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenBudgeDragon","ItemLevel",8,ExDefGID);
		level = ExConfig.GoldenDrop.level43;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType43, ExConfig.GoldenDrop.ItemIndex43);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		return;
	}
	if (lpObj->Class == 78)	//GoldenGoblin
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenGoblin","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenGoblin","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenGoblin","ItemLevel",8,ExDefGID);
		level = ExConfig.GoldenDrop.level78;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType78, ExConfig.GoldenDrop.ItemIndex78);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		return;
	}
	if (lpObj->Class == 493)	//GoldenDarkKnight
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenDarkKnight","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenDarkKnight","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenDarkKnight","ItemLevel",8,ExDefGID);
		level = ExConfig.GoldenDrop.level493;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType493, ExConfig.GoldenDrop.ItemIndex493);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		return;
	}
/*
	if (lpObj->Class == 43 || 
		lpObj->Class == 78 || //Season 4.5 addon
		lpObj->Class == 493) //Season 4.5 addon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 8;
		type = ItemGetNumberMake(14, 11);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
*/
	if (lpObj->Class == 53)	//GoldenTitan
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenTitan","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenTitan","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenTitan","ItemLevel",8,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level53;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType53, ExConfig.GoldenDrop.ItemIndex53);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		return;
	}
	if (lpObj->Class == 54)	//GoldenSoldier
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenSoldier","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenSoldier","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenSoldier","ItemLevel",8,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level54;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType54, ExConfig.GoldenDrop.ItemIndex54);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
/*
	if (lpObj->Class == 53 || // Golden Titan
		lpObj->Class == 54 ) //Season 4.5 addon
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 8;
		type = ItemGetNumberMake(14, 11);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
*/
	if (lpObj->Class == 80)	//GoldenLizardKing
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenLizardKing","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenLizardKing","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenLizardKing","ItemLevel",9,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level80;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType80, ExConfig.GoldenDrop.ItemIndex80);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 81)	//GoldenVepar
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenVepar","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenVepar","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenVepar","ItemLevel",9,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level81;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType81, ExConfig.GoldenDrop.ItemIndex81);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 494)	//GoldenDevil
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenDevil","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenDevil","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenDevil","ItemLevel",9,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level494;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType494, ExConfig.GoldenDrop.ItemIndex494);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
/*
	//IDENTICAL
	if (lpObj->Class == 80 || //Season 4.5 addon
		lpObj->Class == 81 || //Season 4.5 addon
		lpObj->Class == 494) //Season 4.5 addon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 9;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
*/
	if (lpObj->Class == 82)	//GoldenTantalos
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenTantalos","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenTantalos","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenTantalos","ItemLevel",10,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level82;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType82, ExConfig.GoldenDrop.ItemIndex82);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 83)	//GoldenWheel
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenWheel","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenWheel","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenWheel","ItemLevel",10,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level83;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType83, ExConfig.GoldenDrop.ItemIndex83);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 495)	//GoldenGolem
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenGolem","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenGolem","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenGolem","ItemLevel",10,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level495;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType495, ExConfig.GoldenDrop.ItemIndex495);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 496)	//GoldenCrust
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenCrust","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenCrust","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenCrust","ItemLevel",10,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level496;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType496, ExConfig.GoldenDrop.ItemIndex496);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
/*
	//IDENTICAL
	if (lpObj->Class == 82 || //Season 4.5 addon
		lpObj->Class == 83 || //Season 4.5 addon
		lpObj->Class == 495 || //Season 4.5 addon
		lpObj->Class == 496) //Season 4.5 addon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 10;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
*/
	if (lpObj->Class == 497)	//GoldenSatyrus
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenSatyrus","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenSatyrus","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenSatyrus","ItemLevel",11,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level497;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType497, ExConfig.GoldenDrop.ItemIndex497);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 498)	//GoldenTwinTale
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenTwinTale","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenTwinTale","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenTwinTale","ItemLevel",11,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level498;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType498, ExConfig.GoldenDrop.ItemIndex498);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	/*
	//IDENTICAL
	if (lpObj->Class == 497 || //Season 4.5 addon
		lpObj->Class == 498) //Season 4.5 addon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 11;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
	*/
	if (lpObj->Class == 499)	//GoldenIronKnight
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenIronKnight","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenIronKnight","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenIronKnight","ItemLevel",12,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level499;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType499, ExConfig.GoldenDrop.ItemIndex499);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	if (lpObj->Class == 500)	//GoldenNapin
	{
		dur = 255.0f;
		x = lpObj->X;
		y = lpObj->Y;
		//int ItemType = GetPrivateProfileInt("GoldenNapin","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenNapin","ItemIndex",11,ExDefGID);
		//level = GetPrivateProfileInt("GoldenNapin","ItemLevel",12,ExDefGID);
		//type = ItemGetNumberMake(ItemType, ItemIndex);
		level = ExConfig.GoldenDrop.level500;
		type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType500, ExConfig.GoldenDrop.ItemIndex500);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		return;
	}
	/*
	//IDENTICAL
	if (lpObj->Class == 499 || //Season 4.5 addon
		lpObj->Class == 500) //Season 4.5 addon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		x = lpObj->X;
		y = lpObj->Y;
		dur = 255.0f;
		level = 12;
		type = ItemGetNumberMake(14, 11);
		ItemSerialCreateSend(lpObj->m_Index, lpObj->MapNumber, x, y, type, level, dur,
			Option1, Option2, Option3, MaxHitUser, 0, 0);

		return;
	}
	*/
//===========================//

	//IDENTICAL??
	if ( lpObj->Class == 79 )//Season 4.5 REMAKE GoldenDragon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		BYTE cDropX = lpObj->X;
		BYTE cDropY = lpObj->Y;
		dur = 255.0f;
		int randlevel[3];
		//int ItemType = GetPrivateProfileInt("GoldenDragon","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenDragon","ItemIndex",11,ExDefGID);
		//int randlevel1 = GetPrivateProfileInt("GoldenDragon","randlevel1",8,ExDefGID);
		//int randlevel2 = GetPrivateProfileInt("GoldenDragon","randlevel2",9,ExDefGID);
		//int randlevel3 = GetPrivateProfileInt("GoldenDragon","randlevel3",10,ExDefGID);
		//int countitem = GetPrivateProfileInt("GoldenDragon","countitem",5,ExDefGID);

		int randlevel1 = ExConfig.GoldenDrop.randlevel1_79;
		int randlevel2 = ExConfig.GoldenDrop.randlevel2_79;
		int randlevel3 = ExConfig.GoldenDrop.randlevel3_79;
		int countitem = ExConfig.GoldenDrop.countitem79;

		randlevel[0] = randlevel1;
		randlevel[1] = randlevel2;
		randlevel[2] = randlevel2;

		for(int i = 0; i < countitem; i++)
		{
			if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 2, 2, 10))
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			level = randlevel[rand() % 3];
			//type = ItemGetNumberMake(ItemType, ItemIndex);
			type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType79, ExConfig.GoldenDrop.ItemIndex79);
			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)cDropX, (BYTE)cDropY, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		}
		
		return;
	}

	//IDENTICAL??
	if ( lpObj->Class == 501 )//Season 4.5 REMAKE	GoldenGreatDragon
	{
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		BYTE cDropX = lpObj->X;
		BYTE cDropY = lpObj->Y;
		dur = 255.0f;
		int randlevel[2];
		//int ItemType = GetPrivateProfileInt("GoldenGreatDragon","ItemType",14,ExDefGID);
		//int ItemIndex = GetPrivateProfileInt("GoldenGreatDragon","ItemIndex",11,ExDefGID);
		//int randlevel1 = GetPrivateProfileInt("GoldenGreatDragon","randlevel1",11,ExDefGID);
		//int randlevel2 = GetPrivateProfileInt("GoldenGreatDragon","randlevel2",12,ExDefGID);
		//int countitem = GetPrivateProfileInt("GoldenGreatDragon","countitem",5,ExDefGID);

		int randlevel1 = ExConfig.GoldenDrop.randlevel1_501;
		int randlevel2 = ExConfig.GoldenDrop.randlevel2_501;
		int countitem = ExConfig.GoldenDrop.countitem501;

		randlevel[0] = randlevel1;
		randlevel[1] = randlevel2;


		for(int i = 0; i < countitem; i++)
		{
			if ( !gObjGetRandomItemDropLocation(lpObj->MapNumber, cDropX, cDropY, 2, 2, 10))
			{
				cDropX = lpObj->X;
				cDropY = lpObj->Y;
			}

			level = randlevel[rand() % 2];
			//type = ItemGetNumberMake(ItemType, ItemIndex);
			type = ItemGetNumberMake(ExConfig.GoldenDrop.ItemType501, ExConfig.GoldenDrop.ItemIndex501);
			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)cDropX, (BYTE)cDropY, type, (BYTE)level, (BYTE)dur,
			(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

		}
		
		return;
	}

	
	
	if ( lpObj->Class == 55 )	// Death King
	{
		if ( AttackEvent55BagOpen(lpObj)==1 )
			return;

		itemrate = 1;
	}

	if ( gItemDropManager.ProccessItemDrop(lpObj) )
		return;
#ifdef _SYSTEM_OF_RAGE_
		gSystemOfRage.JewelsDropRate(lpTargetObj, lpObj);
#endif
	if ( gEventMonsterItemDrop(lpObj, lpTargetObj) )
		return;

	if ( g_QuestInfo.MonsterItemDrop(lpObj) )
		return;
#if(NEW_ITEM_DROP)
	if ( NewgItemDropManager.ProccessItemDrop(lpObj,lpTargetObj) )
		return;
#endif
	if ( lpTargetObj->Level <= 20 )
	{
		if ( (rand()%10000) < 2000 )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
			x = lpObj->X;
			y = lpObj->Y;
			dur = 1.0f;
			level = 0;
			type = ItemGetNumberMake(14, 0);	// Apple
			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
				(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);
		}
	}

	ExtDropPer = rand()%10000;	// Excellent Drop Percent #warning
	int ItemDropPer = gItemDropPer;
	ItemDropPer += gItemDropPer * lpTargetObj->SetOpImproveItemDropRate / 100;

	int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj); //season3.5 add-on

	if(iMaxHitUser >= 0)
	{
		int iDropRate = gObjGetActiveEffect(&gObj[iMaxHitUser], ADD_OPTION_DROP_RATE); //Seal Drop Option in BuffEffect

		if(iDropRate > 0)
		{
			ItemDropPer = ItemDropPer * iDropRate / 100; //Increase Item Drop
			ExtDropPer = rand()%((2000/iDropRate)*100); //Increase Exc Drop
		}
	}
	
	
#ifdef _EXL_DROP_RATE_
	if ( ExtDropPer <= ExConfig.CommonServer.ExlDropRate )
#else
	if ( ExtDropPer == TRUE )
#endif
	{
#ifdef _EXL_DROP_RATE_
		ExtDropPer = TRUE;
#endif
		DropItem = g_MonsterItemMng.GetItem(lpObj->Level-25);

		if(DropItem != 0)
		{
			if ( g_kItemSystemFor380.Is380Item(DropItem) != 0 )
			{
                DropItem = 0;
			}
		}

		if ( !DropItem )
			item_drop = FALSE;
		else
		{
			int foundChangeupitem=0;
			
			for ( int i=0;i< 4 ;i++)	// #NEED TO CHECK IN GS-N
			{
				if ( DropItem->m_RequireClass[i] > 1 )
				{
					foundChangeupitem = TRUE;
					break;
				}
			}
#ifdef _EXL_DROP_RATE_
#else
			if ( foundChangeupitem )
				ExtDropPer = rand()%100;
#endif


			if ( ExtDropPer )
				if ( (rand()%itemrate) < ItemDropPer )
					item_drop=TRUE;
		}
	}
	else
	{
		if ( (rand()%itemrate) < ItemDropPer )
		{
			DropItem = g_MonsterItemMng.GetItem(lpObj->Level);

			if ( !DropItem )
				item_drop = FALSE;
			else
				item_drop = TRUE;

		}
	}

	if ( item_drop )
	{
		if ( !DropItem->IsItem() )
		{
			item_drop = FALSE;
		}

		int I;

		if ( DropItem->m_Type >= ITEMGET(15,0)  && DropItem->m_Type <= ITEMGET(16,0) )
		{
			I = 0;
		}

		if ( DS_MAP_RANGE(lpObj->MapNumber ) )
		{
			if ( !IsCanNotItemDtopInDevilSquare(DropItem->m_Type) )
			{
				if ( (rand()%10) )
				{
					item_drop = FALSE;
				}
			}
		}
		
		if (g_SocketOption.CheckItemType(DropItem->m_Type) == 1 && // Season 4.5 addon
			g_SocketOption.CheckMapNumber(lpObj->MapNumber) == 0)
		{
			item_drop = FALSE;
		}
		

		if ( DropItem->m_Type == ITEMGET(13,14) && lpObj->MapNumber != MAP_INDEX_ICARUS) // Loch Feather
		{	
			item_drop = FALSE;
		}

		if ( g_CrywolfSync.GetOccupationState() == 1 && g_iCrywolfApplyMvpPenalty )
		{
			// Jewels
			if ( DropItem->m_Type == ITEMGET(14,13) ||  DropItem->m_Type == ITEMGET(14,14) ||  DropItem->m_Type == ITEMGET(14,16) ||
				 DropItem->m_Type == ITEMGET(14,22) ||  DropItem->m_Type == ITEMGET(12,15) ||  DropItem->m_Type == ITEMGET(14,31) )
			{
				if ( (rand()%100) > g_CrywolfSync.GetGemDropPenaltiyRate() )
				{
					item_drop = FALSE;
				}

			}
		}
	}


	if ( item_drop)
	{
		type = DropItem->m_Type;
		level = DropItem->m_Level;

		if ( ExtDropPer == TRUE )
		{
			dur = (float)ItemGetDurability(DropItem->m_Type, 0, 1, 0);
		}
		else
		{
			dur = DropItem->m_Durability;
		}

		x = lpObj->X;
		y = lpObj->Y;

		int option1rand;
		int option2rand;
		int option3rand;
		int optionc;

		if ( ExtDropPer == TRUE )
		{
			option1rand=100;
			option2rand=1;
			option3rand=rand()%100;
			optionc=rand()%3;
			NOption = NewOptionRand(lpObj->Level);
			level = 0;
		}
		else
		{
			option1rand=6;
			option2rand=4;
			option3rand=rand()%100;
			optionc=rand()%3;
			NOption = 0;
		}

		if ( (rand()%100) < option1rand )
			Option1 = 1;

		if ( (rand()%100) < option2rand )
			Option2 = 1;

		switch ( optionc )
		{
			case 0:
				if ( option3rand < 4 )
					Option3=3;
				break;
			case 1:
				if ( option3rand < 8 )
					Option3=2;
				break;
			case 2:
				if ( option3rand < 12 )
					Option3=1;
				break;
		}

		if ( lpObj->Class == 43 ) // Golden Budge Dragon
		{
			Option1 = DropItem->m_Option1;
			Option2 = DropItem->m_Option2;
			Option3 = DropItem->m_Option3;
		}

		if ( type == ITEMGET(12,15) ||	// Chaos
			 type == ITEMGET(14,13) ||	// Bless
			 type == ITEMGET(14,14) ||	// Soul
			 type == ITEMGET(14,31) ||	// Guardian
			 type == ITEMGET(14,16))	// Life
		{
			Option1=0;
			Option2=0;
			Option3=0;
			NOption=0;
		}

		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

		if ( DropItem->m_serial )
		{
			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
				(BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, (BYTE)NOption, 0);
		}
		else
		{
			MapC[lpObj->MapNumber].MonsterItemDrop(type, level, dur, x, y, 
				Option1, Option2, Option3, NOption, 0, MaxHitUser, 0, 0, 0, 0xFF);
		}
	}
	else if ( lpObj->Money < 1 )
	{
		return;
	}
#ifdef _DROP_ZEN_RATE_
	if ( (rand()%100) < ExConfig.CommonServer.ZenDropRate )
#else
	else if ( (rand()%moneyrate) < 10 )
#endif
	{
		int x = lpObj->X;
		int y = lpObj->Y;
		float money = (float)lpObj->Money;
		money /= 2.0f;
		money += money / 100.0f * lpTargetObj->MonsterDieGetMoney;
		money = money * gAddZen; 

		if(lpTargetObj->m_MLPassiveSkill.m_iML_ZenIncrease > 0)
		{
			money += money * lpTargetObj->m_MLPassiveSkill.m_iML_ZenIncrease / 100.0f;
		}

		if ( money < 1.0f )
		{
           money = 1.0f;
		}

		if ( DS_MAP_RANGE(lpObj->MapNumber) )
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			if( MaxHitUser == -1)
			{
				return;
			}

			gObj[MaxHitUser].m_nEventMoney += (__int64)money;
		}
		else
		{
			if(lpTargetObj->PartyNumber != -1)
			{
				//int ExDropZenParty = GetPrivateProfileInt("Party","DropZenParty",10,"..\\ExTeam\\CommonServer.ini");
				money = money * ExConfig.CommonServer.ExDropZenParty;
			}
			if ( lpTargetObj->m_Change == 503 ) //Panda Ring (Season 4.6 Add-on)
			{
				//int Ex_PandaRingZen = GetPrivateProfileInt("PandaRing","Zen",30,"..\\ExTeam\\Pets.ini");
				money = money + ( money * ExConfig.Pet.Ex_PandaRingZen / 100 );
			}
			//Master Drop Zen
			if(lpTargetObj->Level == 400 && ( lpTargetObj->DbClass == 3 || lpTargetObj->DbClass == 19 || 
				lpTargetObj->DbClass == 35 || lpTargetObj->DbClass == 50 || lpTargetObj->DbClass == 66 || lpTargetObj->DbClass == 83))
			{
				//int Ex_MasterDropZen = GetPrivateProfileInt("MasterLevel","MasterDropZen",0,"..\\ExTeam\\CommonServer.ini");
				money = money * ExConfig.CommonServer.Ex_MasterDropZen;
			}
			DropZenManager.Main(lpObj,money);

#ifdef _MuReal_
			VipSystem.VipZen(lpTargetObj,money);
#endif
#ifdef _HAPPY_HOUR_EVENT_
			HappyHour.UserBonusZen(money);
#endif
#ifdef _SYSTEM_OF_RAGE_
			gSystemOfRage.DropZen (lpTargetObj->m_Index, money);
#endif

#ifdef PREMIUM_SYSTEM
			Premium.Zen(lpTargetObj,money);

			if(ExUser[lpTargetObj->m_Index].PremiumTime > 0)
			{
				if( money > Premium.MaxDropZen )
				{
					money =	Premium.MaxDropZen;
				}
			}
			else
			{
				if( money > ExConfig.CommonServer.MaxDropZen )
				{
					money =	ExConfig.CommonServer.MaxDropZen;
				}
			}
#else

			if( money > ExConfig.CommonServer.MaxDropZen )
			{
				money =	ExConfig.CommonServer.MaxDropZen;
			}
#endif

			if ( money < 1.0f )
			{
				return;
			}
			MapC[lpObj->MapNumber].MoneyItemDrop((int)money, x, y);
		}
	}

	if ( lpObj->Money < 1 )
		return;

	if ( DS_MAP_RANGE(lpObj->MapNumber) )
		return;
	
	if ( (rand()%400) == 1 )
	{
		for ( n=0;n<4;n++)
		{
			int x = lpObj->X-2;
			int y = lpObj->Y-2;
			x+= rand()%3;
			y+= rand()%3;

			int mOn = lpObj->Money;

			if( mOn > ExConfig.CommonServer.MaxDropZen )
			{
				mOn =	ExConfig.CommonServer.MaxDropZen;
			}

			MapC[lpObj->MapNumber].MoneyItemDrop(mOn, x, y);
		}
	}

	if ( gEvent1ItemDropTodayPercent > 0 )
	{
		if ( (rand()%gEvent1ItemDropTodayPercent) == 0 )
		{
			if ( gEvent1ItemDropTodayCount < gEvent1ItemDropTodayMax )
			{
				gEvent1ItemDropTodayCount++;
				type = ItemGetNumberMake(14, 12);	// Heart
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;
				level = 1;
				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y,
					type, (BYTE)level, (BYTE)dur, 0, 0, 0, -1, 0, 0);
			}
		}
	}

}

//Identical
BOOL gEventMonsterItemDrop(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	int type;
	int level;
	int x;
	int y;
	float dur=0;
	int Option1=0;
	int Option2=0;
	int Option3=0;

	if ( g_bFenrirStuffItemDrop )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		BOOL bDropStuff=FALSE;

		if ( lpObj->Level >= g_iFenrirStuff_01_DropLv_Min && lpObj->Level <= g_iFenrirStuff_01_DropLv_Max && lpObj->MapNumber == g_iFenrirStuff_01_DropMap && bDropStuff == FALSE )
		{
			if ( (rand()%10000) < g_iFenrirStuff_01_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 32);
			}
		}

		if ( lpObj->Level >= g_iFenrirStuff_02_DropLv_Min && lpObj->Level <= g_iFenrirStuff_02_DropLv_Max && lpObj->MapNumber == g_iFenrirStuff_02_DropMap && bDropStuff == FALSE )
		{
			if ( (rand()%10000) < g_iFenrirStuff_02_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 33);
			}
		}

		if ( lpObj->Level >= g_iFenrirStuff_03_DropLv_Min && lpObj->Level <= g_iFenrirStuff_03_DropLv_Max && lpObj->MapNumber == g_iFenrirStuff_03_DropMap && bDropStuff == FALSE )
		{
			if ( (rand()%10000) < g_iFenrirStuff_03_DropRate ) 
			{
				bDropStuff = TRUE;
				type = ItemGetNumberMake(13, 34);
			}
		}

		if ( bDropStuff )
		{
			level = 0;
			x = lpObj->X;
			y = lpObj->Y;
			dur = 1.0f;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1, (BYTE)Option2, (BYTE)Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	int SocketSphereItemType = 0;
    SocketSphereItemType = g_SocketOption.GetSphereItemIndex(lpObj->Level);
 
    if ( SocketSphereItemType != -1 )// Season 4.5 addon
    {
        int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
 
        ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)lpObj->X, (BYTE)lpObj->Y, SocketSphereItemType, 0, 1, 0, 0, 0, MaxHitUser, 0, 0);
       
        return TRUE;
    }

	if ( g_CompoundPotionDropOn == TRUE )
	{
		BOOL bDropStuff = FALSE;
		int iType = 0;

		if ( lpObj->Level >= g_iCompoundPotionLv1DropLevel && (rand()%10000) <= g_iCompoundPotionLv1DropRate && bDropStuff == FALSE )
		{
			bDropStuff = TRUE;
			iType = ItemGetNumberMake(14, 38);
		}

		if ( bDropStuff == FALSE && lpObj->Level >= g_iCompoundPotionLv2DropLevel && (rand()%10000) <= g_iCompoundPotionLv2DropRate  )
		{
			bDropStuff = TRUE;
			iType = ItemGetNumberMake(14, 39);
		}
		
		if ( !bDropStuff )
		{
			if ( lpObj->Level >= g_iCompoundPotionLv3DropLevel && (rand()%10000) <= g_iCompoundPotionLv3DropRate )
			{
				bDropStuff = TRUE;
				iType = ItemGetNumberMake(14, 40);
			}
		}

		if ( bDropStuff == 1 )
		{
			int level = 0;
			int dur = 1;
			int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)lpObj->X, (BYTE)lpObj->Y, iType, (BYTE)level, (BYTE)dur, 0,0,0, iMaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( gIsItemDropRingOfTransform )
	{
		if ( (rand()%10000) < gItemDropRingOfTransform )
		{
			LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

			if ( lpattr )
			{
				int level = lpattr->m_Level;
				int callbead_level = 0;

				if ( level < 0 )
					level = 0;

				callbead_level = level / 10;

				if ( callbead_level > 0 )
					callbead_level--;

				if ( callbead_level > 5 )
					callbead_level = 5;

				dur = rand()%100+100.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = callbead_level;
				type = ItemGetNumberMake(13, 10);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( gFireCrackerEvent ) 
	{
		if ( gLanguage == 0 )	// If Korea
		{
			if ( lpObj->MapNumber < 7 )
			{
				LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

				if ( lpattr )
				{
					if ( lpattr->m_Level >= 17 )
					{
						if ( (rand()%10000) < gFireCrackerDropRate )
						{
							dur = 255.0f;
							x = lpObj->X;
							y = lpObj->Y;
							level = 2;
							type = ItemGetNumberMake(14, 11);
							int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

							ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

							return TRUE;
						}
					}
				}
			}
		}
		else	// Only Fall on Party
		{
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			if ( MaxHitUser != -1 )
			{
				int partycount = gParty.GetPartyCount(gObj[MaxHitUser].PartyNumber);

				if ( partycount > 0 )
				{
					LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

					if ( lpattr )
					{
						if ( lpattr->m_Level >= 17 )
						{
							if ( (rand()%10000) < gFireCrackerDropRate )
							{
								dur = 255.0f;
								x = lpObj->X;
								y = lpObj->Y;
								level = 2;
								type = ItemGetNumberMake(14, 11);

								ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

								return TRUE;
							}
						}
					}
				}
			}
		}
	}

	if ( gXMasEvent )
	{
		if ( !StarOfXMasItemBag )
			return FALSE;

		if ( StarOfXMasItemBag->DropEventItem(lpObj->m_Index) )
			return TRUE;
	}

	if ( gHeartOfLoveEvent )
	{
		if ( gLanguage == 2 )
		{
			LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

			if ( lpattr )
			{
				if ( lpattr->m_Level >=15 )
				{
					if ( (rand()%10000) < gHeartOfLoveDropRate )
					{
						dur = 255.0f;
						x = lpObj->X;
						y = lpObj->Y;
						level = 3;
						type = ItemGetNumberMake(14, 11);
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

						return TRUE;
					}
				}
			}
		}
		else
		{
			if ( lpObj->MapNumber < 7 )
			{
				LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(lpObj->Class);

				if ( lpattr )
				{
					if ( lpattr->m_Level >=17 )
					{
						if ( (rand()%10000) < gHeartOfLoveDropRate )
						{
							dur = 255.0f;
							x = lpObj->X;
							y = lpObj->Y;
							level = 3;
							type = ItemGetNumberMake(14, 11);
							int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

							ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

							return TRUE;
						}
					}
				}
			}
		}
	}
	
	if ( gMedalEvent )
	{
		if ( lpObj->MapNumber == 1 || lpObj->MapNumber == 2 )
		{
			if ( (rand()%10000) < gSilverMedalDropRate )
			{
				dur = 255.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = 5;
				type = ItemGetNumberMake(14, 11);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->MapNumber == 4 || lpObj->MapNumber == 7 || lpObj->MapNumber == 8 )	// Gold Medal
		{
			if ( (rand()%10000) < gGoldMedalDropRate )
			{
				dur = 255.0f;
				x = lpObj->X;
				y = lpObj->Y;
				level = 6;
				type = ItemGetNumberMake(14, 11);
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( gEventChipEvent )
	{
		if ( (rand()%10000) < gBoxOfGoldDropRate )
		{
			dur = 255.0f;
			x = lpObj->X;
			y = lpObj->Y;
			level = 7;
			type = ItemGetNumberMake(14, 11);
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( szAuthKey[16] != AUTHKEY16 )
	{
		DestroyGIocp();
	}

	if ( (rand()%10000) < g_iKundunMarkDropRate )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		dur = 1.0f;
		x = lpObj->X;
		y = lpObj->Y;
		level = 0;

		if ( lpObj->Level < 25 )
			level = 0;
		else if ( lpObj->Level < 47 )
			level = 1;
		else if ( lpObj->Level < 66 )
			level = 2;
		else if ( lpObj->Level < 78 )
			level = 3;
		else if ( lpObj->Level < 84 )
			level = 4;
		else if ( lpObj->Level < 92 )
			level = 5;
		else if ( lpObj->Level < 114 )
			level = 6;
		else if ( lpObj->Level > 115 && lpObj->Level < MAX_CHAR_LEVEL+1 )
			level = 7;

		if ( level == 0 )
			return FALSE;

		type = ItemGetNumberMake(14, 29);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

		return TRUE;
	}

	if ( (rand()%10000) < g_iMarkOfTheLord )
	{
		Option1=0;
		Option2=0;
		Option3=0;
		level = 3;
		dur = 1.0f;
		x = lpObj->X;
		y = lpObj->Y;
		type = ItemGetNumberMake(14, 21);
		int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

		ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

		return TRUE;
	}

#ifdef INTERNATIONAL_JAPAN
	if ( (rand()%10000) < g_iJapan1StAnivItemDropRate )
	{
		if ( lpTargetObj->PartyNumber >= 0 )
		{
			dur = 255.0f;
			x = lpObj->X;
			y = lpObj->Y;
			type = ItemGetNumberMake(14,20);

			switch ( lpObj->MapNumber )
			{
				case 0:
					{
						level = 1;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						
						return TRUE;
					}
				case 1:
					{
						level = 2;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 2:
					{
						level = 2;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 3:
					{
						level = 1;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 4:
					{
						level = 3;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 7:
					{
						level = 4;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
				case 8:
					{
						level = 5;
						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);
						return TRUE;
					}
			}
		}
	}
#endif

	if ( gIsDropDarkLordItem )
	{
		if ( lpObj->Level >= gSleeveOfLordDropLevel )
		{
			if ( (rand()%10000) < gSleeveOfLordDropRate)
			{
				type = ItemGetNumberMake(13,14);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if ( lpObj->Level >= gSoulOfDarkHorseropLevel )
		{
			if ( (rand()%10000) < gSoulOfDarkHorseDropRate)
			{
				type = ItemGetNumberMake(13,31);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if ( lpObj->Level >= gSoulOfDarkSpiritDropLevel )
		{
			if ( (rand()%10000) < gSoulOfDarkSpiritDropRate )
			{
				type = ItemGetNumberMake(13,31);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( gIsDropGemOfDefend )
	{
		if ( lpObj->MapNumber != MAP_INDEX_KALIMA7 && lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE )
		{
		}
		else
		{
			if ( lpObj->Level >= gGemOfDefendDropLevel )
			{
				if ( (rand()%10000)< gGemOfDefendDropRate )
				{
					type = ItemGetNumberMake(14,31);
					level = 0;
					x = lpObj->X;
					y = lpObj->Y;
					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if(lpObj->MapNumber == MAP_INDEX_BALGASS_BARRACKS) //season 2.5 add-on (S4.5 pos changed)
	{
		if ( (rand()%10000)< g_iCondorFlameDropRate )
		{
			type = ItemGetNumberMake(13,52);
			level = 0;
			x = lpObj->X;
			y = lpObj->Y;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( gIsDropSetItemInCastleHuntZone !=0)	//Land of Trials
	{
		if (lpObj->MapNumber != MAP_INDEX_CASTLEHUNTZONE)
		{

		}
		else
		{
			if ( lpObj->Level >= gSetItemInCastleHuntZoneDropLevel ) //Good
			{
				if ( (rand()%10000) < gSetItemInCastleHuntZoneDropRate )
				{
					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					if ( OBJMAX_RANGE(MaxHitUser) )
					{
						LogAddTD("[Castle HuntZone] Drop SetItem [%s][%s] ", gObj[MaxHitUser].AccountID,gObj[MaxHitUser].Name);
						::MakeRewardSetItem(MaxHitUser, lpObj->X, lpObj->Y, 0, lpObj->MapNumber);
						return TRUE;
					}
				}
			}
		}
	}

	if ( g_bKanturuSpecialItemDropOn )
	{
		if ( lpObj->MapNumber == MAP_INDEX_KANTURU2 )
		{
			if ( (rand()%10000) < g_iKanturuMoonStoneDropRate )
			{
				type = ItemGetNumberMake(13,38);	// Moon Stone
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}

		if ( lpObj->MapNumber == MAP_INDEX_KANTURU1 ||
			 lpObj->MapNumber == MAP_INDEX_KANTURU2 ||
			 lpObj->MapNumber == MAP_INDEX_KANTURU_BOSS )
		{
			if ( (rand()%10000) < g_iKanturuJewelOfHarmonyDropRate )
			{
				type = ItemGetNumberMake(14,41);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( lpObj->MapNumber == MAP_INDEX_AIDA || lpObj->MapNumber == MAP_INDEX_CRYWOLF_FIRSTZONE)
	{
		bool bDropMysteriousBead = false;

		switch ( lpObj->Class )
		{
			case 304:	case 305:	case 306:
			case 307:	case 308:	case 309:
				if ( (rand()%10000) < g_iMysteriousBeadDropRate1 )
					bDropMysteriousBead = true;
				break;

			case 310:	case 311:	case 312:	case 313:
				if ( (rand()%10000) < g_iMysteriousBeadDropRate2 )
					bDropMysteriousBead = true;
				break;
		}

		if ( bDropMysteriousBead == true )
		{
			type = ItemGetNumberMake(12,26);
			level = 0;
			x = lpObj->X;
			y = lpObj->Y;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if( gDevilSquareEvent ) //season3 add-on (Master Level Devil Square)
	{
		if ( !DS_MAP_RANGE(lpObj->MapNumber ) )
		{
			if ( (rand()%10000) < g_iML_EyesOfDevilSquareDropRate )
			{
				if ( lpObj->Level >= 90 )
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 128.0f;

					level = 7;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(14,17);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}

			if ( (rand()%10000) < g_iML_KeysOfDevilSquareDropRate )
			{
				if ( lpObj->Level >= 90 )
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 128.0f;

					level = 7;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(14,18);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if ( g_iIllusionTempleEvent ) //Season 3 add-on (Master Level Illusion)
	{
		if ( !IT_MAP_RANGE(lpObj->MapNumber ) )
		{
			if ( (rand()%10000) < g_iML_OldScrollDropRate )
			{
				if ( lpObj->Level >= 96)
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 0;

					level = 6;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(13,49);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,	(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}				
			}

			if ( (rand()%10000) < g_iML_CovenantOfIllusionDropRate )
			{
				if ( lpObj->Level >= 96)
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 0;

					level = 6;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(13,50);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if ( g_bBloodCastle ) //Season 3 add-on (Master Level Blood Castle)
	{
		if ( !BC_MAP_RANGE(lpObj->MapNumber ) )
		{
			if ( (rand()%10000) < g_iML_AngelKingsPaperDropRate )
			{
				if ( lpObj->Level >= 90)
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 128.0f;

					level = 8;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(13,16);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,	(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}				
			}

			if ( (rand()%10000) < g_iML_BloodBoneDropRate )
			{
				if ( lpObj->Level >= 90)
				{
					Option1=0;
					Option2=0;
					Option3=0;

					dur = 128.0f;

					level = 8;

					x = lpObj->X;
					y = lpObj->Y;

					type = ItemGetNumberMake(13,17);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,	(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if ( g_bBloodCastle )
	{
		if ( !BC_MAP_RANGE(lpObj->MapNumber ) )
		{
			Option1=0;
			Option2=0;
			Option3=0;

			if ( (rand()%10000) < g_iAngelKingsPaperDropRate )
			{
				dur = 128.0f;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level < 32 )
					level = 1;
				else if ( lpObj->Level < 45 )
					level = 2;
				else if ( lpObj->Level < 57 )
					level = 3;
				else if ( lpObj->Level < 68 )
					level = 4;
				else if ( lpObj->Level < 76 )
					level = 5;
				else if ( lpObj->Level < 84 )
					level = 6;
				else if ( lpObj->Level < 90 )
					level = 7;
				else
					level = 8;

				if(level != 8)
				{
					type = ItemGetNumberMake(13,16);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}				
			}

			if ( (rand()%10000) < g_iBloodBoneDropRate )
			{
				dur = 128.0f;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level < 32 )
					level = 1;
				else if ( lpObj->Level < 45 )
					level = 2;
				else if ( lpObj->Level < 57 )
					level = 3;
				else if ( lpObj->Level < 68 )
					level = 4;
				else if ( lpObj->Level < 76 )
					level = 5;
				else if ( lpObj->Level < 84 )
					level = 6;
				else if ( lpObj->Level < 90 )
					level = 7;
				else
					level = 8;

				if(level != 8)
				{
					type = ItemGetNumberMake(13,17);

					int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if ( (rand()%10000) < g_iDarkLordHeartDropRate )
	{
		int iDropRate = 0;

		if ( lpTargetObj->MapNumber == 0 || lpTargetObj->MapNumber == 3 || lpTargetObj->MapNumber == 2 )
		{
			type = ItemGetNumberMake(14,11);
			level = 13;
			x = lpObj->X;
			y = lpObj->Y;
			dur = 0;
			int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

			ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

			return TRUE;
		}
	}

	if ( g_bRibbonBoxEvent )
	{
		if ( lpObj->Level >= g_iRedRibbonBoxDropLevelMin && lpObj->Level <= g_iRedRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iRedRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,32);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iGreenRibbonBoxDropLevelMin && lpObj->Level <= g_iGreenRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iGreenRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,33);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iBlueRibbonBoxDropLevelMin && lpObj->Level <= g_iBlueRibbonBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iBlueRibbonBoxDropRate )
			{
				type = ItemGetNumberMake(12,34);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( g_bChocolateBoxEvent )
	{
		if ( lpObj->Level >= g_iPinkChocolateBoxDropLevelMin && lpObj->Level <= g_iPinkChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iPinkChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,32);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iRedChocolateBoxDropLevelMin && lpObj->Level <= g_iRedChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iRedChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,33);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,
					(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iBlueChocolateBoxDropLevelMin && lpObj->Level <= g_iBlueChocolateBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iBlueChocolateBoxDropRate )
			{
				type = ItemGetNumberMake(14,34);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( g_bCandyBoxEvent )
	{
		if ( lpObj->Level >= g_iLightPurpleCandyBoxDropLevelMin && lpObj->Level <= g_iLightPurpleCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iLightPurpleCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,32);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iVermilionCandyBoxDropLevelMin && lpObj->Level <= g_iVermilionCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iVermilionCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,33);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
		else if ( lpObj->Level >= g_iDeepBlueCandyBoxDropLevelMin && lpObj->Level <= g_iDeepBlueCandyBoxDropLevelMax )
		{
			if ( (rand()%10000) < g_iDeepBlueCandyBoxDropRate )
			{
				type = ItemGetNumberMake(14,34);
				level = 1;
				x = lpObj->X;
				y = lpObj->Y;
				int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if ( g_bHallowinDayEventOn )
	{
		bool bIsBossMonster = false;

		if ( lpObj->m_Index == 349 || lpObj->m_Index == 364 || lpObj->m_Index == 361 ||
			 lpObj->m_Index == 362 || lpObj->m_Index == 363 )
			bIsBossMonster = true;

		if ( !bIsBossMonster )
		{
			if ( (rand()%10000) < g_iHallowinDayEventItemDropRate  )
			{
				if(zzzItemLevel(14,45,lpObj->Level+1) != 0) //season3 add-on
				{
					type = ItemGetNumberMake(14,45);
					level = 0;
					x = lpObj->X;
					y = lpObj->Y;
					int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

					ItemSerialCreateSend(lpTargetObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, iMaxHitUser, 0, 0);

					return TRUE;
				}
			}
		}
	}

	if( g_iSantaPolymorphRingDropOn ) //season 2.5 add-on
	{
		bool bIsBossMonster = false;

		if ( lpObj->m_Index == 349 || lpObj->m_Index == 364 || lpObj->m_Index == 361 ||
			 lpObj->m_Index == 362 || lpObj->m_Index == 363 )
			bIsBossMonster = true;

		if ( !bIsBossMonster )
		{
			if ( (rand()%10000) < g_iSantaPolymorphRingDropRate  )
			{
				type = ItemGetNumberMake(13,41);
				level = 0;
				dur = 100.0f;
				x = lpObj->X;
				y = lpObj->Y;
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, iMaxHitUser, 0, 0);

				//return TRUE; //no return wtf??
			}
		}
	}

	if ( g_iIllusionTempleEvent ) //Season 2.5 add-on
	{
		if ( !IT_MAP_RANGE(lpObj->MapNumber ) )
		{
			Option1=0;
			Option2=0;
			Option3=0;

			if ( (rand()%10000) < g_iOldScrollDropRate )
			{
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level >= 66)
				{
					if ( lpObj->Level < 72 )
					{
						level = 1;
					}
					else if ( lpObj->Level < 78 )
					{
						level = 2;
					}
					else if ( lpObj->Level < 84 )
					{
						level = 3;
					}
					else if ( lpObj->Level < 90 )
					{
						level = 4;
					}
					else if ( lpObj->Level < 96 )
					{
						level = 5;
					}
					else if ( g_iUseMaxLevelIllusionTemple )
					{
						level = 6;
					}
					else
					{
						level = 5;
					}

					if(level != 6)
					{
						type = ItemGetNumberMake(13,49);

						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur,	(BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

						return TRUE;
					}
				}				
			}

			if ( (rand()%10000) < g_iCovenantOfIllusionDropRate )
			{
				dur = 0;
				x = lpObj->X;
				y = lpObj->Y;

				if ( lpObj->Level >= 70)
				{
					if ( lpObj->Level < 76 )
					{
						level = 1;
					}
					else if ( lpObj->Level < 82 )
					{
						level = 2;
					}
					else if ( lpObj->Level < 88 )
					{
						level = 3;
					}
					else if ( lpObj->Level < 94 )
					{
						level = 4;
					}
					else if ( lpObj->Level < 100 )
					{
						level = 5;
					}
					else if ( g_iUseMaxLevelIllusionTemple )
					{
						level = 6;
					}
					else
					{
						level = 5;
					}

					if(level != 6)
					{
						type = ItemGetNumberMake(13,50);

						int MaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

						ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, MaxHitUser, 0, 0);

						return TRUE;
					}
				}				
			}
		}
	}

	if( g_bCherryBlossomEventOn ) //season 3 add-on
	{
		bool bIsBossMonster = false;

		if ( lpObj->m_Index == 349 || lpObj->m_Index == 364 || lpObj->m_Index == 361 ||
			 lpObj->m_Index == 362 || lpObj->m_Index == 363 )
			bIsBossMonster = true;

		if ( !bIsBossMonster )
		{
			if ( (rand()%10000) < g_iCherryBlossomEventItemDropRate  )
			{
				type = ItemGetNumberMake(14,84);
				level = 0;
				x = lpObj->X;
				y = lpObj->Y;
				int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);

				ItemSerialCreateSend(lpTargetObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, iMaxHitUser, 0, 0);

				return TRUE;
			}
		}
	}

	if( g_bLuckyCoinEventOn != 0)// Season 4.5 Addon
    {
        if ( (rand()%10000) < g_iLuckyCoinDropRate  )
        {
            Option1=0;
            Option2=0;
            Option3=0;
 
            level = 0;
            dur = 1.0f;
 
            x = lpObj->X;
            y = lpObj->Y;
 
            type = ItemGetNumberMake(14,100);
 
            int iMaxHitUser = gObjMonsterTopHitDamageUser(lpObj);
 
            ItemSerialCreateSend(lpObj->m_Index, (BYTE)lpObj->MapNumber, (BYTE)x, (BYTE)y, type, (BYTE)level, (BYTE)dur, (BYTE)Option1,(BYTE)Option2,(BYTE)Option3, iMaxHitUser, 0, 0);
 
            return TRUE;
 
        }
    }

	return FALSE;
}

void CQeustNpcTeleport::Run(int aIndex)
{
	if ( this->RefCount > 0 )
	{
		return;
	}

	this->TimeCount++;

	if ( this->TimeCount > gQuestNPCTeleportTime )
	{
		PMSG_MAGICATTACK_RESULT pMsg;

		this->TimeCount = 0;

		PHeadSetBE((LPBYTE)&pMsg, 0x19, sizeof(pMsg));

		pMsg.MagicNumberH = SET_NUMBERH(6);
		pMsg.MagicNumberL = SET_NUMBERL(6);

		pMsg.SourceNumberH = SET_NUMBERH(aIndex);
		pMsg.SourceNumberL = SET_NUMBERL(aIndex);
		pMsg.TargetNumberH = SET_NUMBERH(aIndex);
		pMsg.TargetNumberL = SET_NUMBERL(aIndex);

		MsgSendV2(&gObj[aIndex], (LPBYTE)&pMsg, pMsg.h.size);

		gObjViewportListProtocolDestroy(&gObj[aIndex]);
		gObjClearViewport(&gObj[aIndex]);

		int tableindex;

		while ( true )
		{
			tableindex = rand() % MAX_QUEST_TELEPORT;

			if ( this->LastMapNumber != tableindex )
			{
				this->LastMapNumber = tableindex;
				break;
			}
		}

		gObj[aIndex].X = this->m_QuestNPCTeleportPos[tableindex].x;
		gObj[aIndex].Y = this->m_QuestNPCTeleportPos[tableindex].y;
		gObj[aIndex].TX = gObj[aIndex].X;
		gObj[aIndex].TY = gObj[aIndex].Y;
		gObj[aIndex].MTX = gObj[aIndex].X;
		gObj[aIndex].MTY = gObj[aIndex].Y;
		gObj[aIndex].m_OldX = gObj[aIndex].TX;
		gObj[aIndex].m_OldY = gObj[aIndex].TY;
		gObj[aIndex].MapNumber = this->m_QuestNPCTeleportPos[tableindex].mapnum;
		gObj[aIndex].Dir = this->m_QuestNPCTeleportPos[tableindex].dir;
		gObj[aIndex].StartX = gObj[aIndex].X;
		gObj[aIndex].StartY = gObj[aIndex].Y;
		gObj[aIndex].m_State = 1;
		gObj[aIndex].PathCount = 0;

		LogAdd("NPC %d로 이동", tableindex);
	}
}




















