#include "StdAfx.h"
#include "user.h"
#include "OffExp.h"
#include "GameMain.h"
#include "Message.h"
#include "ObjUseSkill.h"
#include "MagicInf.h"
#include "logproc.h"
#include "ConnectEx.h"
#include "DSProtocol.h"

cOffExp OffExp;

void cOffExp::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,OFF_EXP_DIR);
	this->KickFallen = GetPrivateProfileInt("Common","KickFallen",0,OFF_EXP_DIR);

	this->EnableTime = GetPrivateProfileInt("Common","EnableTime",0,OFF_EXP_DIR);
	this->TimeEnd = GetPrivateProfileInt("Common","Time",0,OFF_EXP_DIR);

	this->OffAfkWcoin10min = GetPrivateProfileInt("Common","OffAfkWcoin10min",0,OFF_EXP_DIR);

	this->OffAfkPriceExPoint = GetPrivateProfileInt("Common","OffAfkPriceExPoint",0,OFF_EXP_DIR);
	this->OffAfkPriceWCoin = GetPrivateProfileInt("Common","OffAfkPriceWCoin",0,OFF_EXP_DIR);
	this->OffAfkPriceCredit = GetPrivateProfileInt("Common","OffAfkPriceCredit",0,OFF_EXP_DIR);
}

void cOffExp::OffExpStart(int aIndex)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];





	if (CheckTerrain(lpObj))
	{
#ifdef _MuReal_
	LogAddC(2,"%d",ExUser[aIndex].OffAfk);
	if(!ExUser[aIndex].OffAfk)
	{
		MsgNormal(aIndex,"[OffExp] Enable OffAfk Status");
		return;
	}
#endif

	



//#ifdef _VIP_OFFAFK_
//	if(ExUser[aIndex].PremiumTime == 0)
//	{
//		MsgNormal(aIndex,"[OffExp] Offline AFK Only Vip Player");
//		return;
//	}
//#endif

#ifdef _MegaMu_
	//if(this->OffAfkWcoin10min)
	//{
	//	if(this->OffAfkWcoin10min > lpObj->m_wCashPoint)
	//	{
	//		MsgNormal(aIndex,"[OffExp] Need WCoin: %d",this->OffAfkWcoin10min);
	//		return;
	//	}
	//	GDRequestWcoinInfoLoad (lpObj,this->OffAfkWcoin10min,2);
	//	//lpObj->m_wCashPoint -= this->OffAfkWcoin10min;
	//}
#endif
#if(OFF_AFK_PRICE)
	if(this->OffAfkPriceExPoint)
	{
		if(this->OffAfkPriceExPoint > ExUser[aIndex].PCPoint)
		{
			MsgNormal(aIndex,"[OffExp] Need ExPoint: %d",this->OffAfkPriceExPoint);
			return;
		}
		ExUser[aIndex].PCPoint -= this->OffAfkPriceExPoint;
	}
	if(this->OffAfkPriceCredit)
	{
		if(this->OffAfkPriceCredit > lpObj->ExCred)
		{
			MsgNormal(aIndex,"[OffExp] Need ExCred: %d",this->OffAfkPriceCredit);
			return;
		}
		lpObj->ExCred -= this->OffAfkPriceCredit;
	}
	if(this->OffAfkPriceWCoin)
	{
		if(this->OffAfkPriceWCoin > lpObj->m_wCashPoint)
		{
			MsgNormal(aIndex,"[OffExp] Need WCoin: %d",this->OffAfkPriceWCoin);
			return;
		}
		GDRequestWcoinInfoLoad (lpObj,this->OffAfkWcoin10min,2);
	}
#endif

#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,OFFAFK_DC);
#else
		CloseClient(aIndex);
		ExUser[aIndex].OffExp = 1;
#endif
		if(this->EnableTime) ExUser[aIndex].OffExpTick = 0;
	}
	else
	{
		MsgNormal(aIndex,"[OffExp] Works just outside of town");
	}
}

//void cOffExp::TickTimes(int aIndex)
//{
//	if(!this->Enable) return; 
//
//	if(this->EnableTime)
//	{
//		LPOBJ lpObj = &gObj[aIndex];
//		ExUser[aIndex].OffExpTick++;
//		if(ExUser[aIndex].OffExpTick >= this->TimeEnd)
//		{
//			ExUser[aIndex].OffExp = 0;
//			return;
//		}
//	}
//}

void cOffExp::MainFunction(int aIndex)
{
	if(!this->Enable) return; 
	
	if(!ExUser[aIndex].OffExp) return;
	LPOBJ lpObj = &gObj[aIndex];
#ifdef _MegaMu_
	if(this->OffAfkWcoin10min)
	{
		ExUser[aIndex].OffExpWcoinTick++;
		if(ExUser[aIndex].OffExpWcoinTick >= 600)
		{
			ExUser[aIndex].OffExpWcoinTick = 0;
			if(this->OffAfkWcoin10min > lpObj->m_wCashPoint)
			{
				ExUser[aIndex].OffExp = 0;
				return;
			}
			GDRequestWcoinInfoLoad (lpObj,this->OffAfkWcoin10min,2);
		}
	}

#endif

	if(this->EnableTime)
	{
		ExUser[aIndex].OffExpTick++;
		if(ExUser[aIndex].OffExpTick >= this->TimeEnd)
		{
			ExUser[aIndex].OffExpTick = 0;
			ExUser[aIndex].OffExp = 0;
			return;
		}
	}

	

	if(!this->CheckTerrain(lpObj))
	{
		if(this->KickFallen) ExUser[aIndex].OffExp = 0;
		return;
	}

	switch(lpObj->Class)
	{
		case 0:	this->DarkWizardOff(lpObj);		break;
		case 1:	this->DarkKnightOff(lpObj);		break;
		case 2:	this->FairyElfOff(lpObj);		break;
		case 3:	this->MagicGladiatorOff(lpObj);	break;
		case 4:	this->DarkLordOff(lpObj);		break;
		case 5:	this->SummonerOff(lpObj);		break;
		case 6: this->RageFighterOff(lpObj);	break;
	}

}
//=====================================
//	Dark Wizard Offline Experience
//=====================================
void cOffExp::DarkWizardOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
	else if(gObjGetMagicSearch( lpObj, 445) != NULL) SearchSkill = 445;
	else if(gObjGetMagicSearch( lpObj, 446) != NULL) SearchSkill = 446;
	else if(gObjGetMagicSearch( lpObj, 447) != NULL) SearchSkill = 447;
	else if(gObjGetMagicSearch( lpObj, 448) != NULL) SearchSkill = 448;
	else if(gObjGetMagicSearch( lpObj, 449) != NULL) SearchSkill = 449;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Knight Offline Experience
//=====================================
void cOffExp::DarkKnightOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
	else if(gObjGetMagicSearch( lpObj, 455) != NULL) SearchSkill = 455;
	else if(gObjGetMagicSearch( lpObj, 456) != NULL) SearchSkill = 456;
	else if(gObjGetMagicSearch( lpObj, 457) != NULL) SearchSkill = 457;
	else if(gObjGetMagicSearch( lpObj, 458) != NULL) SearchSkill = 458;
	else if(gObjGetMagicSearch( lpObj, 459) != NULL) SearchSkill = 459;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(2 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Fairy Elf Offline Experience
//=====================================
void cOffExp::FairyElfOff(LPOBJ lpObj)
{
	int SearchSkill = 0;
	int dis;
	int tObjNum;
	BYTE attr;

	CMagicInf * lpMagic;

	//Buff
	SYSTEMTIME time;
	GetLocalTime(&time);
	ExUser[lpObj->m_Index].OffExpBuff++;
	if( ExUser[lpObj->m_Index].OffExpBuff == 10)
	{
		ExUser[lpObj->m_Index].OffExpBuff = 0;
		int partynum = -1;
		int partycount;
		int number;

		LPOBJ lpPartyObj;

		partynum = lpObj->PartyNumber;

		if(partynum != -1)
		{
			partycount = gParty.m_PartyS[partynum].Count;

			for(int j = 0; j < MAX_USER_IN_PARTY; j++)
			{
				number = gParty.m_PartyS[partynum].Number[j];

				if(number >= 0)
				{
					lpPartyObj = &gObj[number];

					if(lpObj->MapNumber == lpPartyObj->MapNumber)
					{
						dis = gObjCalDistance(lpObj,&gObj[number]);

						if(dis < 6)
						{
							////Defence Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 27);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							////Damage Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 28);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							////Heal Baf
							//lpMagic = gObjGetMagicSearch( lpObj, 26);
							//if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							//Defence Baf
							if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
							else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
							else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
							else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
							else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
							else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Damage Baf
							if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
							else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
							else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
							else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
							else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
							else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
							//Heal Baf
							if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
							else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
							else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
							else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
							else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
							else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
							else SearchSkill = 0;
							if(SearchSkill != 0)
							{
								lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
								if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpPartyObj->m_Index, lpMagic);
							}
						}
					}
				}
			}
		}
		else
		{
			//Defence Baf
			if(gObjGetMagicSearch( lpObj, 27) != NULL) SearchSkill = 27;
			else if(gObjGetMagicSearch( lpObj, 480) != NULL) SearchSkill = 480;
			else if(gObjGetMagicSearch( lpObj, 481) != NULL) SearchSkill = 481;
			else if(gObjGetMagicSearch( lpObj, 482) != NULL) SearchSkill = 482;
			else if(gObjGetMagicSearch( lpObj, 483) != NULL) SearchSkill = 483;
			else if(gObjGetMagicSearch( lpObj, 484) != NULL) SearchSkill = 484;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Damage Baf
			if(gObjGetMagicSearch( lpObj, 28) != NULL) SearchSkill = 28;
			else if(gObjGetMagicSearch( lpObj, 485) != NULL) SearchSkill = 485;
			else if(gObjGetMagicSearch( lpObj, 486) != NULL) SearchSkill = 486;
			else if(gObjGetMagicSearch( lpObj, 487) != NULL) SearchSkill = 487;
			else if(gObjGetMagicSearch( lpObj, 488) != NULL) SearchSkill = 488;
			else if(gObjGetMagicSearch( lpObj, 489) != NULL) SearchSkill = 489;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
			//Heal Baf
			if(gObjGetMagicSearch( lpObj, 26) != NULL) SearchSkill = 26;
			else if(gObjGetMagicSearch( lpObj, 475) != NULL) SearchSkill = 475;
			else if(gObjGetMagicSearch( lpObj, 476) != NULL) SearchSkill = 476;
			else if(gObjGetMagicSearch( lpObj, 477) != NULL) SearchSkill = 477;
			else if(gObjGetMagicSearch( lpObj, 478) != NULL) SearchSkill = 478;
			else if(gObjGetMagicSearch( lpObj, 479) != NULL) SearchSkill = 479;
			else SearchSkill = 0;
			if(SearchSkill != 0)
			{
				lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
				if(lpMagic!=NULL) gObjUseSkill.UseSkill(lpObj->m_Index, lpObj->m_Index, lpMagic);
			}
		}
	}

	lpMagic = gObjGetMagicSearch( lpObj, 235);	//Multi-Shot 235
	if(lpMagic==NULL) return;

	int NumDir[6] = {0, 50, 100, 150, 200, 250 };
	int StartDir = NumDir[rand()%6];
	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,StartDir,0,-1);

	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(5 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Magic Gladiator Offline Experience
//=====================================
void cOffExp::MagicGladiatorOff(LPOBJ lpObj)
{
	int skill;
	int NormDis;
	CMagicInf * lpMagic;
	int SearchSkill = 0;

	if(lpObj->pInventory[0].m_Type >= ITEMGET(5,0) && lpObj->pInventory[0].m_Type < ITEMGET(6,0))
	{
		if(gObjGetMagicSearch( lpObj, 9) != NULL) SearchSkill = 9;
		else if(gObjGetMagicSearch( lpObj, 530) != NULL) SearchSkill = 530;
		else if(gObjGetMagicSearch( lpObj, 531) != NULL) SearchSkill = 531;
		else if(gObjGetMagicSearch( lpObj, 532) != NULL) SearchSkill = 532;
		else if(gObjGetMagicSearch( lpObj, 533) != NULL) SearchSkill = 533;
		else if(gObjGetMagicSearch( lpObj, 534) != NULL) SearchSkill = 534;
		else return;
		skill = SearchSkill;
		NormDis = 6;
	}
	else
	{
		if(gObjGetMagicSearch( lpObj, 41) != NULL) SearchSkill = 41;
		else if(gObjGetMagicSearch( lpObj, 495) != NULL) SearchSkill = 495;
		else if(gObjGetMagicSearch( lpObj, 496) != NULL) SearchSkill = 496;
		else if(gObjGetMagicSearch( lpObj, 497) != NULL) SearchSkill = 497;
		else if(gObjGetMagicSearch( lpObj, 498) != NULL) SearchSkill = 498;
		else if(gObjGetMagicSearch( lpObj, 499) != NULL) SearchSkill = 499;
		else return;
		skill = SearchSkill;
		NormDis = 2;
	}

	lpMagic = gObjGetMagicSearch( lpObj, skill);	//Twisting Slash 41
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(NormDis >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Dark Lord Offline Experience
//=====================================
void cOffExp::DarkLordOff(LPOBJ lpObj)	//Work
{
	int Target = this->SearchTarget(lpObj);

	if(Target == -1) return;

	int SearchSkill = 0;
	CMagicInf * lpMagic;

	if(gObjGetMagicSearch( lpObj, 61) != NULL) SearchSkill = 61;
	else if(gObjGetMagicSearch( lpObj, 520) != NULL) SearchSkill = 520;
	else if(gObjGetMagicSearch( lpObj, 521) != NULL) SearchSkill = 521;
	else if(gObjGetMagicSearch( lpObj, 522) != NULL) SearchSkill = 522;
	else if(gObjGetMagicSearch( lpObj, 523) != NULL) SearchSkill = 523;
	else if(gObjGetMagicSearch( lpObj, 524) != NULL) SearchSkill = 524;
	else return;

	lpMagic = gObjGetMagicSearch( lpObj, SearchSkill);
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index,Target, lpMagic); //

	this->UseMana(lpObj->m_Index);
}
//=====================================
//	Summoner Offline Experience
//=====================================
void cOffExp::SummonerOff(LPOBJ lpObj)
{
	CMagicInf * lpMagic;
	lpMagic = gObjGetMagicSearch( lpObj, 230);	//Lightning Shock
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

//=====================================
//	Ragi Fighter Offline Experience
//=====================================
void cOffExp::RageFighterOff(LPOBJ lpObj)
{
	CMagicInf * lpMagic;
	lpMagic = gObjGetMagicSearch( lpObj, 264);	//Lightning Shock
	if(lpMagic==NULL) return;

	gObjUseSkill.UseSkill(lpObj->m_Index, lpMagic,lpObj->X, lpObj->Y,0,0,-1);

	int dis;
	int tObjNum;
	BYTE attr;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						gObjAttack(lpObj, &gObj[tObjNum], lpMagic, FALSE, 1, 0, FALSE,0);
					}
				}
			}
		}
	}

	this->UseMana(lpObj->m_Index);
}

int cOffExp::SearchTarget(LPOBJ lpObj)
{
	int dis;
	int searchtarget = -1;
	int tObjNum;
	BYTE attr;
	int TargetIndex[MAX_VIEWPORT_MONSTER];
	int TargetCount = 0;
	int IndexNumber;
	for (int n=0;n<MAX_VIEWPORT_MONSTER;n++)
	{
		tObjNum = lpObj->VpPlayer2[n].number;
		if(lpObj->VpPlayer2[n].state == 0) continue;
		if ( tObjNum >= 0 )
		{
			if ( gObj[tObjNum].Type == OBJ_MONSTER )
			{
				attr = MapC[gObj[tObjNum].MapNumber].GetAttr(gObj[tObjNum].X, gObj[tObjNum].Y);
				if ( (attr&1) != 1 )
				{
					dis = gObjCalDistance(lpObj, &gObj[tObjNum]);
					if(6 >= dis)
					{
						TargetIndex[TargetCount] = tObjNum;
						TargetCount++;
					}
				}
			}
		}
	}

	if(TargetCount == 0)	return -1;
	
	IndexNumber = rand()%TargetCount;

	searchtarget = TargetIndex[IndexNumber];

	return searchtarget;
}

void cOffExp::UseMana(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Mana > 100) return;
		
	int pos;

	pos = gObjGetManaItemPos(aIndex);

	if(pos == -1) return;

	if( lpObj->pInventory[pos].m_Type == ITEMGET(14,4) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,5) || 
		lpObj->pInventory[pos].m_Type == ITEMGET(14,6)  )
	{
		int tMana = (lpObj->pInventory[pos].m_Value*10) - (gObj[aIndex].Level);

		if ( tMana < 0 )
		{
			tMana=0;
		}

		switch ( lpObj->pInventory[pos].m_Type )
		{
		case ITEMGET(14,4):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*20/100; 
			break;
		case ITEMGET(14,5):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*30/100; 
			break;
		case ITEMGET(14,6):
			tMana += ((int)(gObj[aIndex].MaxMana + gObj[aIndex].AddMana))*40/100; 
			break;
		}

		gObj[aIndex].Mana += tMana;

		if ( gObj[aIndex].Mana > (gObj[aIndex].MaxMana+gObj[aIndex].AddMana-1.0f) )
		{
			gObj[aIndex].Mana = gObj[aIndex].MaxMana+gObj[aIndex].AddMana;
		}

		GCManaSend(aIndex, (int)gObj[aIndex].Mana, 0xFF, 0, (int)gObj[aIndex].BP);

		if ( !gObjSearchItemMinus(&gObj[aIndex], pos, 1) )
		{
			gObjInventoryItemSet(aIndex, pos, -1);
			gObj[aIndex].pInventory[pos].Clear();
			GCInventoryItemDeleteSend(aIndex, pos, 1);
		}
	}
}

bool cOffExp::CheckTerrain(LPOBJ lpObj)
{	
	BYTE attr = MapC[lpObj->MapNumber].GetAttr(lpObj->X, lpObj->Y);

	if ( (attr&1) != 1 )
	{
		return true;
	}
	else
	{
		return false;
	}
}