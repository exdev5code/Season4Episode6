#include "stdafx.h"
#include "Mercenary.h"
#include "protocol.h"
#include "GameMain.h"
#include "LogProc.h"

#include "CastleSiegeSync.h"

CMercenary g_CsNPC_Mercenary;

CMercenary::CMercenary()
{
	this->m_iMercenaryCount = 0;
}

CMercenary::~CMercenary()
{
	return;
}

BOOL CMercenary::CreateMercenary(int iIndex, int iMercenaryTypeIndex, BYTE cTX, BYTE cTY)
{
	LPOBJ lpObj = &gObj[iIndex];
	int iMonsterIndex = -1;
	BYTE cX = cTX;
	BYTE cY = cTY;

	BYTE btMapAttr = MapC[lpObj->MapNumber].GetAttr(cX, cY);

	if(btMapAttr & 16 != 16) //siege camp?
	{
		//return FALSE;
	}

	if ( lpObj->MapNumber != MAP_INDEX_CASTLESIEGE )
	{
		::MsgOutput(iIndex, lMsg.Get(MSGGET(6, 91)));

		return FALSE;
	}

	if(g_CastleSiegeSync.GetCastleState() != CASTLESIEGE_STATE_STARTSIEGE)
	{
		::MsgOutput(iIndex, lMsg.Get(1630));
		return FALSE;
	}

	if( iMercenaryTypeIndex == 286 || iMercenaryTypeIndex == 287)
	{
		if( lpObj->m_btCsJoinSide != 1)
		{
			::MsgOutput(iIndex, lMsg.Get(1628));
			return FALSE;
		}
		if(lpObj->GuildStatus != G_MASTER && lpObj->GuildStatus != G_SUB_MASTER)
		{
			::MsgOutput(iIndex, lMsg.Get(1629));
				return FALSE;
		}
	}

	if( this->m_iMercenaryCount > 100 )
	{
		::MsgOutput(iIndex, lMsg.Get(1631));
		return FALSE;
	}

	iMonsterIndex = gObjAddMonster(lpObj->MapNumber);

	if(iMonsterIndex >= 0)
	{
		LPMONSTER_ATTRIBUTE lpattr = gMAttr.GetAttr(iMercenaryTypeIndex);

		if(lpattr == NULL)
		{
			gObjDel(iMonsterIndex);
			return FALSE;
		}

		gObjSetMonster(iMonsterIndex, iMercenaryTypeIndex);

		gObj[iMonsterIndex].Live = 1;
		gObj[iMonsterIndex].Life = lpattr->m_Hp;
		gObj[iMonsterIndex].MaxLife = lpattr->m_Hp;
		gObj[iMonsterIndex].m_PosNum = -1;
		gObj[iMonsterIndex].X = cX;
		gObj[iMonsterIndex].Y = cY;
		gObj[iMonsterIndex].MTX = cX;
		gObj[iMonsterIndex].MTY = cY;
		gObj[iMonsterIndex].TX = cX;
		gObj[iMonsterIndex].TY = cY;
		gObj[iMonsterIndex].m_OldX = cX;
		gObj[iMonsterIndex].m_OldY = cY;
		gObj[iMonsterIndex].StartX = cX;
		gObj[iMonsterIndex].StartY = cY;
		gObj[iMonsterIndex].MapNumber = lpObj->MapNumber;
		gObj[iMonsterIndex].m_MoveRange = 0;
		gObj[iMonsterIndex].Level = lpattr->m_Level;
		gObj[iMonsterIndex].Type = OBJ_MONSTER;
		gObj[iMonsterIndex].MaxRegenTime = 1000;
		gObj[iMonsterIndex].Dir = 1;
		gObj[iMonsterIndex].RegenTime = GetTickCount();
		gObj[iMonsterIndex].m_Attribute = 0;
		gObj[iMonsterIndex].DieRegen = 0;
		gObj[iMonsterIndex].m_btCsNpcType = 2;
		gObj[iMonsterIndex].m_btCsJoinSide = 1;

		::MsgOutput(iIndex, lMsg.Get(1632));

		this->m_iMercenaryCount++;

		if(lpObj->lpGuild != NULL)
		{
			LogAddTD("[CastleSiege] Mercenary is summoned [%d] - [%d][%d] [%s][%s][%d] - (Guild : %s)",iMonsterIndex, iMercenaryTypeIndex,this->m_iMercenaryCount,lpObj->AccountID,lpObj->Name,lpObj->GuildStatus,lpObj->lpGuild->Name);
		}
		else
		{
			LogAddTD("[CastleSiege] Mercenary is summoned [%d] - [%d][%d] [%s][%s][%d]",iMonsterIndex, iMercenaryTypeIndex,this->m_iMercenaryCount,lpObj->AccountID,lpObj->Name,lpObj->GuildStatus);
		}
	}
	else
	{
		::MsgOutput(iIndex, lMsg.Get(1633));
		return FALSE;
	}
	return TRUE;
}


BOOL CMercenary::DeleteMercenary(int iIndex)
{
	if ( iIndex < 0 || iIndex > OBJMAX-1 )
	{
		return FALSE;
	}

	this->m_iMercenaryCount--;

	LogAddTD("[CastleSiege] Mercenary is broken [%d] - [%d]", iIndex, this->m_iMercenaryCount);

	if ( this->m_iMercenaryCount < 0 )
	{
		this->m_iMercenaryCount = 0;
	}

	return TRUE;
}




int  CMercenary::SearchEnemy(LPOBJ lpObj)
{
	int iTargetNumber = -1;
	int iAttackRange = 0;

	lpObj->TargetNumber = -1;

	if(lpObj->Class == 286)
	{
		iAttackRange = 5;
	}
	else if(lpObj->Class == 287)
	{
		iAttackRange = 3;
	}

	int i;
	for(i = 0; i < MAX_VIEWPORT; i++)
	{
		iTargetNumber = lpObj->VpPlayer2[i].number;

		if(iTargetNumber >= 0 && gObj[iTargetNumber].Type == 1 && gObj[iTargetNumber].Live != FALSE && gObj[iTargetNumber].Teleport == FALSE)
		{
			if(gObj[iTargetNumber].m_btCsJoinSide == lpObj->m_btCsJoinSide)
			{
				continue;
			}

			//Mr.Marin Decompilation 100%
			int iTargetDisX = lpObj->X - gObj[iTargetNumber].X;
			int iTargetDisY = lpObj->Y - gObj[iTargetNumber].Y;
			int iTargetDist;
			int cY;
			int cX;
			int SquareDist = (iTargetDisX*iTargetDisX)+(iTargetDisY*iTargetDisY);

			iTargetDist = (long)sqrt((double)SquareDist);
			
			lpObj->VpPlayer2[i].dis = iTargetDist;

			if(lpObj->Dir == 1 && abs(iTargetDisX) <= 2)
			{
				cY = lpObj->Y - iAttackRange;
				if(cY <= gObj[iTargetNumber].Y)
				{
					if(lpObj->Y >= gObj[iTargetNumber].Y)
					{
						lpObj->TargetNumber = iTargetNumber;
						return 1;
					}
				}
			}

			if(lpObj->Dir == 3 && abs(iTargetDisY) <= 2)
			{
				cX = lpObj->X - iAttackRange;
				if(cX <= gObj[iTargetNumber].X)
				{
					if(lpObj->X >= gObj[iTargetNumber].X)
					{
						lpObj->TargetNumber = iTargetNumber;
						return 1;
					}
				}
			}

		}


	}
	return 0;
}




void CMercenary::MercenaryAct(int iIndex)
{
	if ( ::gObjIsConnected(iIndex) == FALSE )
	{
		return;
	}

	LPOBJ lpObj = &gObj[iIndex];


	if ( lpObj->VPCount2 < 1 )
	{
		return;
	}

	if ( this->SearchEnemy(lpObj) != 0 && lpObj->TargetNumber >= 0)
	{
		lpObj->m_ActState.Attack = 1;
		lpObj->NextActionTime = lpObj->m_AttackSpeed;
	}
	else
	{
		lpObj->NextActionTime = lpObj->m_MoveSpeed;
	}
}