// GuardianStatue.cpp: implementation of the CGuardianStatue class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GuardianStatue.h"
#include "user.h"

CGuardianStatue g_CsNPC_GuardianStatue;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGuardianStatue::CGuardianStatue()
{

}

CGuardianStatue::~CGuardianStatue()
{

}

void CGuardianStatue::GuardianStatueAct(int iIndex)
{
	if( ::gObjIsConnected(iIndex) == FALSE )
	{
		return;
	}

	LPOBJ lpObj = &gObj[iIndex];

	if( lpObj->VPCount < 1 )
	{
		return;
	}

	int tObjNum = -1;

	for( int i = 0; i < MAX_VIEWPORT; i++ )
	{
		tObjNum = lpObj->VpPlayer[i].number;

		if( tObjNum >= 0 )
		{
			if( gObj[tObjNum].Type == OBJ_USER )
			{
				if( gObj[tObjNum].Live != FALSE )
				{
					if( gObj[tObjNum].m_btCsJoinSide == 1 )
					{
						if( abs(lpObj->Y - gObj[tObjNum].Y) <= 3 && abs(lpObj->X - gObj[tObjNum].X) <= 3 )
						{
							BOOL bIsMaxLife = FALSE;
							BOOL bIsMaxMana = FALSE;
							BOOL bIsMaxBP	= FALSE;

							if( gObj[tObjNum].Life < (gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife) )
							{
								gObj[tObjNum].Life += ( (gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife) * (lpObj->m_btCsNpcRgLevel+1) / 100 );

								if( gObj[tObjNum].Life > (gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife) )
								{
									gObj[tObjNum].Life = gObj[tObjNum].MaxLife + gObj[tObjNum].AddLife;
								}

								bIsMaxLife = TRUE;
							}
							
							if( gObj[tObjNum].Mana < (gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) )
							{
								gObj[tObjNum].Mana += ( (gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) * (lpObj->m_btCsNpcRgLevel+1)) / 100;

								if( gObj[tObjNum].Mana > (gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana) )
								{
									gObj[tObjNum].Mana = gObj[tObjNum].MaxMana + gObj[tObjNum].AddMana;
								}

								bIsMaxMana = TRUE;
							}

							if( gObj[tObjNum].BP < (gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP) )
							{
								gObj[tObjNum].BP += ( (gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP) * (lpObj->m_btCsNpcRgLevel+1) / 100);

								if( gObj[tObjNum].BP > (gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP) )
								{
									gObj[tObjNum].BP = gObj[tObjNum].MaxBP + gObj[tObjNum].AddBP;
								}

								bIsMaxBP = TRUE;
							}

							if( bIsMaxLife != FALSE )
							{
								::GCReFillSend(tObjNum, (int)gObj[tObjNum].Life, 0xFF, 1, (int)gObj[tObjNum].iShield);
							}

							if( bIsMaxMana != FALSE || bIsMaxBP != FALSE )
							{
								::GCManaSend(tObjNum, (int)gObj[tObjNum].Mana, 0xFF, 0, (int)gObj[tObjNum].BP);
							}
						}
					}
				}
			}
		}
	}
}