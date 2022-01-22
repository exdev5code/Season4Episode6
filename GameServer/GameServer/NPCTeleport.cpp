#include "StdAfx.h"
#include "NPCTeleport.h"
#include "user.h"
#include "GameMain.h"
#include "Message.h"
#include "DSProtocol.h"
#include "PCPointSystem.h"

#if(CUSTOM_NPC_TELEPORT==TRUE)

NPCTeleport g_NPCTeleport;

NPCTeleport::NPCTeleport()
{
}

NPCTeleport::~NPCTeleport()
{
}

void NPCTeleport::Init()
{
	this->Enable = false;;
	this->NPC_Class = 0;
	this->NPC_Map = 0;
	this->NPC_X = 0;
	this->NPC_Y = 0;
	this->TeleportMap = 0;
	this->TeleportX = 0;
	this->TeleportY = 0;

	this->NeedZen = 0;
	this->NeedWcoin = 0;
	this->NeedCredits = 0;
	this->NeedReset = 0;
	this->NeedLevel = 0;
}

void NPCTeleport::Load()
{
	this->Read("..\\ExTeam\\NPCTeleport.ini");
}

void NPCTeleport::Read(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);
	this->NPC_Class = GetPrivateProfileInt("ExTeam", "NPC_Class", 0, File);
	this->NPC_Map = GetPrivateProfileInt("ExTeam", "NPC_Map", 0, File);
	this->NPC_X = GetPrivateProfileInt("ExTeam", "NPC_X", 0, File);
	this->NPC_Y = GetPrivateProfileInt("ExTeam", "NPC_Y", 0, File);
	this->TeleportMap = GetPrivateProfileInt("ExTeam", "TeleportMap", 0, File);
	this->TeleportX = GetPrivateProfileInt("ExTeam", "TeleportX", 0, File);
	this->TeleportY = GetPrivateProfileInt("ExTeam", "TeleportY", 0, File);
	this->NeedZen = GetPrivateProfileInt("ExTeam", "NeedZen", 0, File);
	this->NeedWcoin = GetPrivateProfileInt("ExTeam", "NeedWcoin", 0, File);
	this->NeedCredits = GetPrivateProfileInt("ExTeam", "NeedCredits", 0, File);
	this->NeedReset = GetPrivateProfileInt("ExTeam", "NeedReset", 0, File);
	this->NeedLevel = GetPrivateProfileInt("ExTeam", "NeedLevel", 0, File);
}

bool NPCTeleport::Dialog(int UserIndex, int NPC_Index)
{
	if(!this->Enable)
	{
 		return false;
	}

	if ( OBJMAX_RANGE(UserIndex) == FALSE || OBJMAX_RANGE(NPC_Index) == FALSE)
	{
		return false;
	}

	if(!gObjIsConnected(UserIndex))
	{
		return false;
	}

	LPOBJ lpUser = &gObj[UserIndex];
	LPOBJ lpNpc = &gObj[NPC_Index];

	if(		lpNpc->Class		== this->NPC_Class 
		&&	lpNpc->MapNumber	== this->NPC_Map
		&&	lpNpc->X			== this->NPC_X
		&&	lpNpc->Y			== this->NPC_Y )
	{
		if(this->NeedLevel > lpUser->Level)
		{
			MsgNormal(UserIndex,"You need above %d Level to Teleport",this->NeedLevel);
			return true;
		}
		if(this->NeedReset > ExUser[UserIndex].Reset)
		{
			MsgNormal(UserIndex,"You need above %d Reset to Teleport",this->NeedReset);
			return true;
		}
		if(this->NeedZen > lpUser->Money)
		{
			MsgNormal(UserIndex,"You need above %d Zen to Teleport",this->NeedZen);
			return true;
		}
		if(this->NeedCredits > ExUser[UserIndex].PCPoint)
		{
			MsgNormal(UserIndex,"You need above %d Credits to Teleport",this->NeedCredits);
			return true;
		}
		if(this->NeedWcoin > lpUser->m_wCashPoint)
		{
			MsgNormal(UserIndex,"You need above %d Wcoin to Teleport",this->NeedWcoin);
			return true;
		}
		// ----
		if(this->NeedZen > 0)
		{
			lpUser->Money -= this->NeedZen;
			GCMoneySend(UserIndex, lpUser->Money);
		}
		if(this->NeedCredits > 0)
		{
			lpUser->ExCred -= this->NeedCredits;
			ExPCPointSystem.InitPCPointForPlayer(lpUser, ExUser[UserIndex].PCPoint ,lpUser->ExCred);
		}
		if(this->NeedWcoin > 0)
		{
			GDRequestWcoinInfoLoad (lpUser,this->NeedWcoin,1);
		}
		// ----
		gObjTeleport(UserIndex, this->TeleportMap,this->TeleportX,this->TeleportY);
		return true;
	}

	return false;
}
#endif