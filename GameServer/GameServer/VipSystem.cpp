#include "StdAfx.h"

#ifdef _MuReal_

#include "user.h"
#include "VipSystem.h"
#include "Message.h"
#include "PCPointSystem.h"
cVipSystem VipSystem;

void cVipSystem::LoadConfig()
{
	this->vipSystemEnable = GetPrivateProfileInt("Common","vipSystemEnable",0,VIPSYSTEM_DIR);
	GetPrivateProfileString("Common", "BuyVipCMD","/buyvip",this->BuyVipCMD,sizeof(this->BuyVipCMD),VIPSYSTEM_DIR);

	this->vipExpRate = GetPrivateProfileInt("Common","vipExpRate",0,VIPSYSTEM_DIR);
	this->vipDropRate = GetPrivateProfileInt("Common","vipDropRate",0,VIPSYSTEM_DIR);

	this->priceVipCRMin = GetPrivateProfileInt("Common","priceVipCRMin",0,VIPSYSTEM_DIR);	//стоимость 1 минуты в кредитах

	GetPrivateProfileString("Common", "PostVipCmd","/postvip",this->PostVipCmd,sizeof(this->PostVipCmd),VIPSYSTEM_DIR);
	this->colorVipChatMsg = GetPrivateProfileInt("Common","colorVipChatMsg",0,VIPSYSTEM_DIR);
	GetPrivateProfileString("Common", "VipPrefics","[PostVip]",this->VipPrefics,sizeof(this->VipPrefics),VIPSYSTEM_DIR);

	this->needLvlFromTeleport = GetPrivateProfileInt("Common","needLvlFromTeleport",0,VIPSYSTEM_DIR);
	this->offTeleportPhonoman = GetPrivateProfileInt("Common","offTeleportPhonoman",0,VIPSYSTEM_DIR);
	GetPrivateProfileString("Common", "TeleportCmd","/vipteleport",this->TeleportCmd,sizeof(this->TeleportCmd),VIPSYSTEM_DIR);
	this->TeleportMap = GetPrivateProfileInt("Common","TeleportMap",0,VIPSYSTEM_DIR);
	this->TeleportX = GetPrivateProfileInt("Common","TeleportX",0,VIPSYSTEM_DIR);
	this->TeleportY = GetPrivateProfileInt("Common","TeleportY",0,VIPSYSTEM_DIR);

	//Сообщение, если не дсотаочно кредитов.
	GetPrivateProfileString("Common", "msgNotEnoughCR","Sorry you do not have enough credits.",this->msgNotEnoughCR,sizeof(this->msgNotEnoughCR),VIPSYSTEM_DIR);
	//Сообщение, если нельзя телепортироватся в вип крату фанаману
	GetPrivateProfileString("Common", "msgOffTeleportPhonoman","Sorry you Phonoman.",this->msgOffTeleportPhonoman,sizeof(this->msgOffTeleportPhonoman),VIPSYSTEM_DIR);
	//Сообщение, если не достаточно левала для телепортироватся в вип крату
	GetPrivateProfileString("Common", "msgNotNeedLvlFromTeleport ","Sorry you bad lvl from teleport vip map.",this->msgNotNeedLvlFromTeleport ,sizeof(this->msgNotNeedLvlFromTeleport ),VIPSYSTEM_DIR);
	// Вип сообщение при входе
	GetPrivateProfileString("Common", "msgVipConnect","vip connect to server. Good luck!",this->msgVipConnect,sizeof(this->msgVipConnect),VIPSYSTEM_DIR);

	this->msgVipConnectEnable = GetPrivateProfileInt("Common","msgVipConnectEnable",0,VIPSYSTEM_DIR);

	this->VipX1 = GetPrivateProfileInt("Common","VipX1",0,VIPSYSTEM_DIR);
	this->VipX2 = GetPrivateProfileInt("Common","VipX2",0,VIPSYSTEM_DIR);
	this->VipY1 = GetPrivateProfileInt("Common","VipY1",0,VIPSYSTEM_DIR);
	this->VipY2 = GetPrivateProfileInt("Common","VipY2",0,VIPSYSTEM_DIR);
}

void cVipSystem::BuyVip(int aIndex,LPBYTE Protocol)
{
	if(!this->vipSystemEnable) return;
	if(!memcmp(&Protocol[13],this->BuyVipCMD,strlen(this->BuyVipCMD)))
	{
		if(strlen((char*)Protocol+13+strlen(this->BuyVipCMD)) > 6) return;
		int VipDay = 0;
		sscanf((char*)Protocol+13+strlen(this->BuyVipCMD),"%d",&VipDay);
		if(VipDay <= 0 || VipDay > 10000) return;
		int NeedCr = VipDay * this->priceVipCRMin;
		//if(NeedCr > ExUser[aIndex].CR)
		LPOBJ lpObj = &gObj[aIndex];
		if(NeedCr > lpObj->ExCred)
		{
			MsgNormal(aIndex,"%s",this->msgNotEnoughCR);
			return;
		}
		MsgNormal(aIndex,"[BuyVip] +%d Day",VipDay);
		//ExUser[aIndex].CR -= NeedCr;
		lpObj->ExCred -= NeedCr;
		ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
		ExUser[aIndex].VipTime += (VipDay * 86400);
	}
}

void cVipSystem::ConnectMessage(int aIndex)
{
	if(!this->vipSystemEnable) return;
	if(!this->msgVipConnectEnable) return;
	//MsgNormal(aIndex,"[CR] %d",ExUser[aIndex].CR);

	//MsgNormal(aIndex,"[CR] %d",ExUser[aIndex].CR);
	if(ExUser[aIndex].VipTime > 0)
	{
		LPOBJ lpObj = &gObj[aIndex];
		MessaageAllGlobal("[%s] %s",lpObj->Name,this->msgVipConnect);
		MsgNormal(aIndex,"[Vip] %d Hour",(ExUser[aIndex].VipTime/3600));
	}
}

void cVipSystem::VipExperience(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->vipSystemEnable) return;
	int aIndex = lpObj->m_Index;
	if(ExUser[aIndex].VipTime > 0)
	{
		Experience += (( Experience * this->vipExpRate ) / 100 );
	}
}

void cVipSystem::VipZen(LPOBJ lpObj, float & money)
{
	if(!this->vipSystemEnable) return;
	int aIndex = lpObj->m_Index;
	if(ExUser[aIndex].VipTime > 0)
	{
		money += (( money * this->vipDropRate ) / 100 );
	}
}

void cVipSystem::TickTime(int aIndex)
{
	if(!this->vipSystemEnable) return;
	if(ExUser[aIndex].VipTime > 0)
	{
		ExUser[aIndex].VipTime -= 1;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(ExUser[aIndex].VipTime == 0 && this->TeleportMap == lpObj->MapNumber)
	{
		if(	(lpObj->X >= this->VipX1 && lpObj->Y <= this->VipY1) &&	(lpObj->X <= this->VipX2 && lpObj->Y >= this->VipY2) )
		{
			gObjTeleport(aIndex,0,123,123);
		}
	}
}

void cVipSystem::Teleport(int aIndex,LPBYTE Protocol)
{
	if(!this->vipSystemEnable) return;
	if(ExUser[aIndex].VipTime > 0)
	{
		if(!memcmp(&Protocol[13],this->TeleportCmd,strlen(this->TeleportCmd)))
		{
			LPOBJ lpObj = &gObj[aIndex];
			if(this->offTeleportPhonoman)
			{
				if(lpObj->m_PK_Level > 5)
				{
					MsgNormal(aIndex,"%s",this->msgOffTeleportPhonoman);
					return;
				}
			}
			if(this->needLvlFromTeleport > lpObj->Level)
			{
				MsgNormal(aIndex,"%s",this->msgNotNeedLvlFromTeleport);
				return;
			}
			gObjTeleport(aIndex,this->TeleportMap,this->TeleportX,this->TeleportY);
		}
	}
}
void cVipSystem::PostVip(int aIndex,LPBYTE Protocol)
{
	if(!this->vipSystemEnable) return;
	if(ExUser[aIndex].VipTime > 0)
	{
		if(!memcmp(&Protocol[13],this->PostVipCmd,strlen(this->PostVipCmd)))
		{
			LPOBJ lpObj = &gObj[aIndex];
			BYTE *Packet; 
			char Message[100]; 
			Packet = (BYTE*) malloc(200); 
			memset(Packet, 0x00, 200); 
			*Packet = 0xC1; 
			*(Packet+2) = 0x00; 
			switch(this->colorVipChatMsg)
			{
				case 0: sprintf(Message, "%s %s %s",lpObj->Name,this->VipPrefics, (char*)Protocol+13+strlen(this->PostVipCmd));break;
				case 1: sprintf(Message, "~%s %s %s",lpObj->Name,this->VipPrefics, (char*)Protocol+13+strlen(this->PostVipCmd));break;
				case 2: sprintf(Message, "@%s %s %s",lpObj->Name,this->VipPrefics, (char*)Protocol+13+strlen(this->PostVipCmd));break;
				case 3: sprintf(Message, "@@%s %s %s",lpObj->Name,this->VipPrefics, (char*)Protocol+13+strlen(this->PostVipCmd));break;
				default: sprintf(Message, "~%s %s %s",lpObj->Name,this->VipPrefics, (char*)Protocol+13+strlen(this->PostVipCmd));
			}
			memcpy((Packet+13), Message, strlen(Message)); 
			int Len = (strlen(Message) + 0x13); 
			*(Packet+1) = Len; 
			DataSendAll(Packet, Len); 
		}
	}
}

#endif