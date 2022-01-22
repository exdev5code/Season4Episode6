#include "StdAfx.h"
#include "ConnectEx.h"
#include "GameMain.h"
#include "user.h"
#include "ConMember.h"
#include "..\common\winutil.h"
#include "logproc.h"
#include "DBSockMng.h"
#include "DSProtocol.h"
#include "SProtocol.h"
#include "Configs.h"
#include "OffTrade.h"
// -------------------------------------------------------------------------------

#if(_RECONNECT_)
// -------------------------------------------------------------------------------

ConnectEx g_ConnectEx;
// -------------------------------------------------------------------------------

BOOL PacketCheckTime2(LPOBJ lpObj) 
{
	if( (GetTickCount() - lpObj->m_PacketCheckTime) < 300 )
	{
		return FALSE;
	}

	lpObj->m_PacketCheckTime = GetTickCount();
	return TRUE;
}
// -------------------------------------------------------------------------------

void ConnectEx::SendLogin(int UserIndex, CONNECTEX_LOGIN * Data)
{
	if(!ExConfig.CommonServer.ReConnect) return;

	// ----
	BuxConvert(Data->AccountID, MAX_ACCOUNT_LEN);
	BuxConvert(Data->Password, MAX_ACCOUNT_LEN);
	// ----
	char id[11];
	id[10]=0;
	memcpy(id, Data->AccountID, sizeof(Data->AccountID));
	BuxConvert(id, MAX_ACCOUNT_LEN);
	// ----
	GJPUserClose(id); //Force connection
	// ----
	if( bCanConnectMember == TRUE )
	{
		if( ConMember.IsMember(id) == FALSE )
		{
			GCJoinResult(JS_ONLY_VIP_MEMBERS, UserIndex);
			return;
		}
	}
	// ----
	LPOBJ lpObj = &gObj[UserIndex];
	// ----
	if( gObj[UserIndex].Connected != PLAYER_CONNECTED )
	{
		LogAdd(lMsg.Get(MSGGET(1, 218)), UserIndex, id);
		CloseClient(UserIndex);
		return;
	}
	// ----
	if( gObj[UserIndex].LoginMsgSnd != FALSE )
	{
		if( gObj[UserIndex].LoginMsgSnd == TRUE )
		{
			LogAdd(lMsg.Get(MSGGET(1, 219)), UserIndex, id, gObj[UserIndex].Ip_addr );
		}
		else
		{
			LogAdd("error : %d %s %d", gObj[UserIndex].LoginMsgSnd, __FILE__, __LINE__);
		}

		return;
	}
	// ----
	if( lpObj->Connected >= PLAYER_LOGGED )
	{
		return;
	}
	// ----
	SDHP_IDPASS spMsg;
	// ----
	PHeadSetB((LPBYTE)&spMsg, 0x01, sizeof(spMsg));
	spMsg.Number = UserIndex;
	memcpy(spMsg.Id, Data->AccountID, sizeof(spMsg.Id));
	memcpy(spMsg.Pass, Data->Password, sizeof(spMsg.Pass));
	strcpy(spMsg.IpAddress, gObj[UserIndex].Ip_addr);
	gObj[UserIndex].CheckTick = Data->TickCount;
	gObj[UserIndex].CheckTick2 = GetTickCount();
	gObj[UserIndex].ConnectCheckTime = GetTickCount();
	gObj[UserIndex].CheckSpeedHack = true;
	gObj[UserIndex].LoginMsgSnd = 1;
	gObj[UserIndex].LoginMsgCount = 1;
	gObj[UserIndex].AccountID[MAX_ACCOUNT_LEN] = 0;
	gObj[UserIndex].Name[MAX_ACCOUNT_LEN] = 0;
	memcpy(gObj[UserIndex].AccountID, id, MAX_ACCOUNT_LEN);
	memcpy(gObj[UserIndex].Name, Data->Name, MAX_ACCOUNT_LEN);
	gObj[UserIndex].m_cAccountItemBlock = 0;
	gObj[UserIndex].m_ConnectEx = true;
	gObj[UserIndex].ukn_30 = 0;
	// ----
	wsJServerCli.DataSend((char*)&spMsg, spMsg.h.size);
	LogAddTD("join send : (%d)%s", UserIndex, gObj[UserIndex].AccountID);
	
	lpObj->m_bMapSvrMoveReq = false;
	lpObj->m_sPrevMapSvrCode = -1; 
	lpObj->m_sDestMapNumber = -1;
	lpObj->m_btDestX = 0;
	lpObj->m_btDestY = 0;
}
// -------------------------------------------------------------------------------

void ConnectEx::SendGame(int UserIndex)
{
	if(!ExConfig.CommonServer.ReConnect) return;
	// ----
	gObj[UserIndex].m_ConnectEx = false;
	DataServerGetCharListRequest(UserIndex);
	// ----
	if ( !PacketCheckTime2(&gObj[UserIndex]))
	{
		return;
	}
	// ----
	if ( !gObjIsAccontConnect(UserIndex, gObj[UserIndex].AccountID))
	{
		return;
	}
	// ----
	if ( gObj[UserIndex].Connected == PLAYER_PLAYING )
	{
		return;
	}
	// ----
	gObj[UserIndex].bEnableDelCharacter = FALSE;
	// ----
	char _name[MAX_ACCOUNT_LEN+1];
	SDHP_DBCHARINFOREQUEST pCRequest;
	// ----
	PHeadSetB((LPBYTE)&pCRequest, 0x06, sizeof(pCRequest));
	memset(_name, 0, MAX_ACCOUNT_LEN);
	memcpy(_name, gObj[UserIndex].Name, MAX_ACCOUNT_LEN);
	BuxConvert(_name, MAX_ACCOUNT_LEN);
	memcpy(pCRequest.Name, _name, MAX_ACCOUNT_LEN);
	strcpy(pCRequest.AccountID, gObj[UserIndex].AccountID);
	pCRequest.Number = UserIndex;
	// ----
	cDBSMng.Send((char*)&pCRequest, pCRequest.h.size);
}
// -------------------------------------------------------------------------------

void ConnectEx::SendClose(int UserIndex, int Type)
{
	if(!ExConfig.CommonServer.ReConnect) return;
	// ----
	CONNECTEX_CLOSE pRequest;
	gObj[UserIndex].DisconnectType = Type;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0xC, sizeof(CONNECTEX_CLOSE));
	DataSend(UserIndex, (LPBYTE)&pRequest, pRequest.h.size);
}
// -------------------------------------------------------------------------------

void ConnectEx::RecvClose(int UserIndex)
{
	LPOBJ lpObj = &gObj[UserIndex];

	CloseClient(UserIndex);

	if(lpObj->DisconnectType == OFFZEN_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFWC_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFPC_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFCR_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFAFK_DC)
	{
		ExUser[UserIndex].OffExp = 1;
	}

	else if(lpObj->DisconnectType == OFFCHAOS_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFBLESS_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFSOUL_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
	else if(lpObj->DisconnectType == OFFLIFE_DC)
	{
		ExUser[UserIndex].OffTrade = lpObj->DisconnectType;
	}
}
#endif
// -------------------------------------------------------------------------------