#include "StdAfx.h"
#include "user.h"
#include "..\\common\\winutil.h"
#include "DSProtocol.h"
#include "protocol.h"
#include "ExUser.h"
#include "logproc.h"
#include "GameMain.h"

#ifdef NEW_HP_BAR

struct VieweCharEx
{
	short aIndex;
	int Life;
	int MaxLife;
	int SD;
	int MaxSD;
	short Level;
	short Reset;
	short GrandReset;
	short Defence;
	char Name[20];
};

struct CGExUserHpBar
{
	//PBMSG_HEAD2 h;
	struct PWMSG_HEAD h;
	VieweCharEx Vp[40];	//MAX_VIEWPORT
};

void ExUserVieweport(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == 0)
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Connected < PLAYER_PLAYING)
	{
		return;
	}

	CGExUserHpBar exSend;
	memset(&exSend,-1,sizeof(exSend));
	PHeadSetW((LPBYTE)&exSend, 0xFA,  sizeof(exSend));	

	int count = 0;

	for(int n = 0; n < OBJMAX; n++)
	{
		LPOBJ lpTempObj = &gObj[n];

		if(lpTempObj->Connected == PLAYER_PLAYING)
		{
			if(lpTempObj->m_State == 1 || lpTempObj->m_State == 2)
			{
				if(lpObj->MapNumber == lpTempObj->MapNumber)
				{
					if(gObjCheckViewport(aIndex,lpTempObj->X,lpTempObj->Y) == 1)
					{
						if(lpTempObj->Type != OBJ_MONSTER && lpTempObj->Type != OBJ_USER) continue;

						exSend.Vp[count].aIndex = n;
						exSend.Vp[count].Life = (DWORD)gObj[n].Life;
						exSend.Vp[count].MaxLife = (DWORD)gObj[n].MaxLife + gObj[n].AddLife;
						exSend.Vp[count].SD = (DWORD)gObj[n].iShield;
						exSend.Vp[count].MaxSD = (DWORD)gObj[n].iMaxShield + gObj[n].iAddShield;
						exSend.Vp[count].Level = lpTempObj->Level;
						exSend.Vp[count].Reset = ExUser[n].Reset;
						exSend.Vp[count].GrandReset = ExUser[n].GReset;
						exSend.Vp[count].Defence = lpTempObj->m_Defense;

						//exSend.Vp[count].Live = lpTempObj->Live;

						if(lpTempObj->Type == OBJ_MONSTER)
						{
							LPMONSTER_ATTRIBUTE lpMonsterAttr = NULL;//loc68
							lpMonsterAttr = gMAttr.GetAttr(gObj[n].Class);
							memcpy(exSend.Vp[count].Name,lpMonsterAttr->m_Name,sizeof(exSend.Vp[count].Name));
						}
						else
						{
							strcpy(exSend.Vp[count].Name,gObj[n].Name);
							//lpMonsterAttr = gMAttr.GetAttr(MonsterClass);
						}

						count++;

						if(count == 40-1) break;
					}
				}
			}
		}
	}

	DataSend(aIndex,(LPBYTE)&exSend,sizeof(exSend));
}

#endif

void ExUserDataSend(int aIndex)
{
	EXINFO_UPDATE rSend;
	LPOBJ lpObj =&gObj[aIndex];
	rSend.h.set((LPBYTE)&rSend, 0xFB, 14, sizeof(rSend));
	rSend.PremiumTime = ExUser[aIndex].PremiumTime;
	rSend.Chaos = lpObj->ChaosBank;
	rSend.Bless = lpObj->BlessBank;
	rSend.Soul = lpObj->SoulBank;
	rSend.Life = lpObj->LifeBank;
	rSend.ExCred = lpObj->ExCred;
	DataSend(aIndex,(LPBYTE)&rSend,sizeof(rSend));
}

