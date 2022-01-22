#include "StdAfx.h"
#ifdef PREMIUM_SYSTEM
#include "user.h"
#include "PremiumSystem.h"
#include "Message.h"
#include "PCPointSystem.h"

PremiumSystem Premium;

void PremiumSystem::Loader()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,PREMIUM_DIR);
	this->PlusExp = GetPrivateProfileInt("Common","PlusExp",0,PREMIUM_DIR);
	this->PlusZen = GetPrivateProfileInt("Common","PlusZen",0,PREMIUM_DIR);
#ifdef _PREMIUM_MOTHER_BUY_
	this->BuyVipCred = GetPrivateProfileInt("Common","BuyVipCred",1,PREMIUM_DIR);
#endif

	this->MaxDropZen = GetPrivateProfileInt("Common","MaxDropZen",1000000,PREMIUM_DIR);
}

void PremiumSystem::TickTime(int aIndex)
{
	if(!this->Enable) return;
	if(ExUser[aIndex].PremiumTime > 0)
	{
		ExUser[aIndex].PremiumTime--;
		if(ExUser[aIndex].PremiumTime == 0)
		{
			MessageChat(aIndex,"@[Premium Status] Time is over");
		}
	}
}

void PremiumSystem::Exp(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->Enable) return;
	if(ExUser[lpObj->m_Index].PremiumTime > 0)
	{
		Experience += (( Experience * this->PlusExp ) / 100 );
	}
}

void PremiumSystem::Zen(LPOBJ lpObj, float & money)
{
	if(!this->Enable) return;
	if(ExUser[lpObj->m_Index].PremiumTime > 0)
	{
		money += (( money * this->PlusZen ) / 100 );
	}
}

void PremiumSystem::ChatSell(int aIndex, LPBYTE Protocol)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		char SellCmd[] = "/sellpremium";
		if(!memcmp(&Protocol[13],SellCmd,strlen(SellCmd)))
		{
			if(strlen((char*)Protocol+13+strlen(SellCmd))>15)return;
			char sName[100];
			unsigned int Day;
			sscanf((char*)Protocol+13+strlen(SellCmd),"%s %d",&sName,&Day);
			if(Day < 0 || Day > 10000) return;
			for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;i++)
			{
				LPOBJ sObj = &gObj[i];
				if(!strcmp(sObj->Name,sName))
				{
					ExUser[i].PremiumTime += ( Day * 86400 );
					MsgNormal(aIndex,"[Sell Premium] %s",sObj->Name);
					MessageChat(i,"@[Premium Status] +%d Day",Day);
					return;
				}
			}
		}
	}
#ifdef _PREMIUM_MOTHER_BUY_
	this->ChatBuyVipUser(aIndex, Protocol);
#endif
}

void PremiumSystem::ConnectInfo(int aIndex)
{
	if(!this->Enable) return;
	if(ExUser[aIndex].PremiumTime > 0)
	{
		MessageChat(aIndex,"@[Premium Status] Active");
		MessageChat(aIndex,"@[Premium Status] Min: %d",(ExUser[aIndex].PremiumTime/60));
	}
}

#ifdef _PREMIUM_MOTHER_BUY_
void PremiumSystem::ChatBuyVipUser(int aIndex, LPBYTE Protocol)
{
	if(!this->Enable || !this->BuyVipCred) return;
	char BuyCMD[] = "/buypremium";
	if(!memcmp(&Protocol[13],BuyCMD,strlen(BuyCMD)))
	{
		LPOBJ lpObj = &gObj[aIndex];

		//int Day = 0;
		//sscanf((char*)Protocol+13+strlen(BuyCMD),"%d",&Day);
		//if(Day < 1 || Day > 10000) return;

		//int NeedCred = this->BuyVipCred * 30;

		if(this->BuyVipCred > lpObj->ExCred)
		{
			MsgNormal(aIndex,"[Buy Premium] Need %d Credits",this->BuyVipCred);
			return;
		}

		lpObj->ExCred -= this->BuyVipCred;

		ExPCPointSystem.InitPCPointForPlayer(lpObj, ExUser[aIndex].PCPoint, lpObj->ExCred );

		ExUser[aIndex].PremiumTime += 30*86400;

		MessageChat(aIndex,"@[Buy Status] Premium 30 Day");
	}
}
#endif

#endif