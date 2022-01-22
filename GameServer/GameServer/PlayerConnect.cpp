#include "StdAfx.h"
#include "user.h"
#include "PlayerConnect.h"
#include "Reset.h"
#include "Message.h"
#include "Configs.h"
#include "VipSystem.h"

int EnablePlayerConnectSystem = GetPrivateProfileInt("Common","Enable",0,"..\\ExTeam\\PlayerConnect.ini");	
int ShowReset = GetPrivateProfileInt("Common","ShowReset",0,"..\\ExTeam\\PlayerConnect.ini");
int ShowGReset = GetPrivateProfileInt("Common","ShowGReset",0,"..\\ExTeam\\PlayerConnect.ini");

int EnableWellcome = GetPrivateProfileInt("Common","EnableWellcome",0,"..\\ExTeam\\PlayerConnect.ini");

char MsgWellcome[50];


void LoadConnectini()
{
	GetPrivateProfileString("Common", "MsgWellcome","Wellcome to ExGames",MsgWellcome,sizeof(MsgWellcome),"..\\ExTeam\\PlayerConnect.ini");
}

void ExPlayerConnectSystem(int aIndex)
{
#ifdef _MuReal_
	VipSystem.ConnectMessage(aIndex);
#endif
	if(!EnablePlayerConnectSystem)
		return;

	LPOBJ lpObj = &gObj[aIndex];

	if(EnableWellcome)
	{
		//MessaageAllGlobal(MsgWellcome);
		GCServerMsgStringSend(MsgWellcome, aIndex,0);
	}
	

	if(ShowReset)
		MsgNormal(aIndex,"[Reset]: %d",ExUser[aIndex].Reset);
	if(ShowGReset)
		MsgNormal(aIndex,"[GReset]: %d",ExUser[aIndex].GReset);

#if(_MegaMu_)
	MsgNormal(aIndex,"[WCoin]: %d",lpObj->m_wCashPoint);
#endif
}