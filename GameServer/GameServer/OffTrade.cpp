#include "StdAfx.h"
#include "user.h"
#include "giocp.h"
#include "Message.h"
#include "Configs.h"
#include "GrandHeroSystem.h"
#include "ConnectEx.h"
#include "OffTrade.h"

void CreateOffTrade(int aIndex,int type)
{
	if(type == 1)	//Check OffTrade Zen Enable
	{
		if(!ExConfig.OffTrade.OffTradeZen) return;
	}
	else if (type == 2)
	{
		if(!ExConfig.OffTrade.OffTradeExPoint) return;
	}
	else if (type == 3)
	{
		if(!ExConfig.OffTrade.OffTradeWcoin) return;
	}
	else if(type == 4)
	{
		if(!ExConfig.OffTrade.OffTradeCredit) return;
	}
	else if (type == OFFCHAOS_DC)
	{
		if(!ExConfig.OffTrade.OffTradeChaos) return;
	}
	else if (type == OFFBLESS_DC)
	{
		if(!ExConfig.OffTrade.OffTradeBless) return;
	}
	else if (type == OFFSOUL_DC)
	{
		if(!ExConfig.OffTrade.OffTradeSoul) return;
	}
	else if (type == OFFLIFE_DC)
	{
		if(!ExConfig.OffTrade.OffTradeLife) return;
	}
	else
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_bPShopOpen == false)
	{
		MsgNormal(aIndex,"[OffTrade] Need Open Shop");
		return;
	}
#if(_GRAND_HERO_SYSTEM_)
	if(GrandHero.OffTradeLorenMarket(aIndex,type) == true)
	{
		return;
	}
#endif

	if(lpObj->MapNumber==0 || lpObj->MapNumber==2 || lpObj->MapNumber==3 || lpObj->MapNumber==51)
	{
		if(type == 1)
		{
			strcpy(lpObj->m_szPShopText,".::ZEN SHOP::.");
		}
		else if(type == 2)
		{
			strcpy(lpObj->m_szPShopText,".::EXPOINT SHOP::.");
		}
		else if(type == 3)
		{
			strcpy(lpObj->m_szPShopText,".::WCOINT SHOP::.");
		}
		else if(type == 4)
		{
			strcpy(lpObj->m_szPShopText,".::CREDIT SHOP::.");
		}
		else if(type == OFFCHAOS_DC)
		{
			strcpy(lpObj->m_szPShopText,CHAOS_SHOP);
		}
		else if(type == OFFBLESS_DC)
		{
			strcpy(lpObj->m_szPShopText,BLESS_SHOP);
		}
		else if(type == OFFSOUL_DC)
		{
			strcpy(lpObj->m_szPShopText,SOUL_SHOP);
		}
		else if(type == OFFLIFE_DC)
		{
			strcpy(lpObj->m_szPShopText,LIFE_SHOP);
		}

		if(lpObj->MapNumber==0)
			MessaageAllGlobal("[OffTrade][%s] Lorencia %d %d",lpObj->Name,lpObj->X,lpObj->Y);
		else if(lpObj->MapNumber==2)
			MessaageAllGlobal("[OffTrade][%s] Devias %d %d",lpObj->Name,lpObj->X,lpObj->Y);
		else if(lpObj->MapNumber==3)
			MessaageAllGlobal("[OffTrade][%s] Noria %d %d",lpObj->Name,lpObj->X,lpObj->Y);
		else if(lpObj->MapNumber==51)
			MessaageAllGlobal("[OffTrade][%s] Emblend %d %d",lpObj->Name,lpObj->X,lpObj->Y);


		//gObjCloseSet(aIndex, 2);
#ifdef _RECONNECT_
		g_ConnectEx.SendClose(aIndex,type);
#else
		CloseClient(aIndex);
		ExUser[aIndex].OffTrade = type;
#endif
	}
	else
	{
		MsgNormal(aIndex,"[OffTrade] OffTrade work only special maps");
	}
}