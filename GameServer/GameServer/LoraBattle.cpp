#include "StdAfx.h"

#ifdef _LORA_BATTLE_

#include "LoraBattle.h"
#include "USER.h"
#include "Functions.h"
#include "Message.h"
#include "DSProtocol.h"

cLoraBattle LoraBattle;

void cLoraBattle::LoadConfigs()
{

	Enable = GetPrivateProfileInt("Common","Enable",1,LORABATTLE_DIR);

	if(!Enable)
		return;
	//Configs
	GetPrivateProfileStringA("Common", "MGS","[Lora Battle] Start after 1 minute",MSG,sizeof(MSG),LORABATTLE_DIR);

	this->EventTime = ( GetPrivateProfileInt("Common","EventTime",1,LORABATTLE_DIR) * 60 + 60 );

	this->RewardWCoin = GetPrivateProfileInt("Reward","RewardWCoin",1,LORABATTLE_DIR);
	this->RewardItem = GetPrivateProfileInt("Reward","RewardItem",1,LORABATTLE_DIR);

	this->WCoin = GetPrivateProfileInt("Reward","WCoin",1,LORABATTLE_DIR);
	this->ITEM = GetPrivateProfileInt("Reward","ITEM",1,LORABATTLE_DIR);
	this->ITEM_LEVEL = GetPrivateProfileInt("Reward","ITEM_LEVEL",1,LORABATTLE_DIR);

	this->Fallen_DROP = GetPrivateProfileInt("Fallen","Fallen_DROP",1,LORABATTLE_DIR);
	this->Fallen_ITEM = GetPrivateProfileInt("Fallen","Fallen_ITEM",1,LORABATTLE_DIR);
	this->Fallen_ITEM_LEVEL = GetPrivateProfileInt("Fallen","Fallen_ITEM_LEVEL",1,LORABATTLE_DIR);

	for(int i=OBJ_MAXMONSTER; i<=OBJMAX; i++)
	{
		this->KillSocer[i] = 0;
		//this->m_PK_Level[i] = 0;
	}

	this->MaxSocer	 = 0;

	this->Start = false;

	this->Waiting = false;

	this->WaitingTick = 0;

	this->TimeTick = 0;

	FILE *file = fopen(LORABATTLE_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,LORABATTLE_DIR,"LOAD ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	this->Count = 0;

	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			this->Time[this->Count].Hour	= 0;
			this->Time[this->Count].Min		= 0;

			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Time[this->Count].Hour	= n[0];
			this->Time[this->Count].Min		= n[1];;
			this->Count++;
		}
	}
	fclose(file);
}
void cLoraBattle::Start1min()
{
	this->Waiting = true;
	MessaageAllGlobal(this->MSG);
}

void cLoraBattle::StartEvent()
{
	//for(int j=OBJ_MAXMONSTER; j<OBJMAX; j++)
	//{
	//	LPOBJ lpObj = &gObj[j];
	//	this->m_PK_Level[j] = gObj->m_PK_Level;
	//}
	this->Waiting = false;
	this->Start = true;
	MessaageAllGlobal("[Lora Battle] Event Started!");
}

void cLoraBattle::EndEvent()
{
	this->Start = false;
	for(int j=OBJ_MAXMONSTER; j<OBJMAX; j++)
	{
		//MaxSocer = KillSocer[j];
		if(KillSocer[j] > MaxSocer)
		{
			this->MaxSocer = this->KillSocer[j];
			this->MaxIndex = j;
		}
	}
	for(int l=OBJ_MAXMONSTER; l<OBJMAX; l++)
	{
		if(this->KillSocer[l] == 0)
			continue;

		if(MaxSocer == KillSocer[l])
		{
			LPOBJ lpObj = &gObj[l];
			if(lpObj->Connected == PLAYER_PLAYING)
			{
				MessaageAllGlobal("[Lora Battle] Win %s !",lpObj->Name);
				this->Reward(l);
			}
		}
	}
	
	MessaageAllGlobal("[Lora Battle] Event End!");

	for(int i=OBJ_MAXMONSTER; i<OBJMAX; i++)
	{
		//LPOBJ lpObj = &gObj[i];
		this->KillSocer[i] = 0;
		//gObj->m_PK_Level = this->m_PK_Level[i];
		//GCPkLevelSend(i, gObj->m_PK_Level);
	}

	this->MaxSocer	 = 0;
}

void cLoraBattle::TickTime()
{
	if(!Enable)
		return;

	if(this->Waiting)
	{
		this->WaitingTick++;
		if(this->WaitingTick == 60)
		{
			this->StartEvent();

		}
		return;
	}

	if(this->Start)
	{
		this->TimeTick++;
		if(this->TimeTick == this->EventTime)
		{
			this->EndEvent();
		}
		return;
	}

	SYSTEMTIME time;
	GetLocalTime(&time);

	if(time.wSecond == 00)
	{
		for(int i = 0; i < this->Count; i++)
		{
/*			if(Time[i].StrHour == time.wHour && Time[i].StrMin == time.wMinute)
			{
				this->Start1min();
			}
			else */if(Time[i].Hour == time.wHour && Time[i].Min == time.wMinute)
			{
				this->Start1min();
				return;
			}
			//else if(Time[i].EndHour == time.wHour && Time[i].EndMin == time.wMinute)
			//{
			//	this->EndEvent();
			//}
		}
	}
}

void cLoraBattle::BattleKillSocer(int aIndex,int aIndex2)
{
	if(!this->Enable || !this->Start) return;

	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpTargetObj = &gObj[aIndex2];

	if(lpObj->MapNumber == 0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131)
	{
		this->KillSocer[aIndex]++;
		MsgNormal(aIndex,"[LoraBattle] Killed: %d",KillSocer[aIndex]);
		if(this->Fallen_DROP)
		{
			ItemSerialCreateSend(aIndex2,lpTargetObj->MapNumber,lpTargetObj->X,lpTargetObj->Y,Fallen_ITEM,Fallen_ITEM_LEVEL,0,0,0,0,aIndex,0,0);
		}
	}
}

void cLoraBattle::Reward(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(this->RewardWCoin)
	{
		GDRequestWcoinInfoLoad (lpObj,this->WCoin,1); //1 = +
		MsgNormal(aIndex,"[LoraBattle] Reward Gem: +%d",this->WCoin);
	}

	if(this->RewardItem)
	{
		ItemSerialCreateSend(aIndex,lpObj->MapNumber,lpObj->X,lpObj->Y,ITEM,ITEM_LEVEL,0,0,0,0,aIndex,0,0);
	}
	
	ExFireCracker(aIndex,lpObj->X,lpObj->Y);
}

void cLoraBattle::StructStart(int aIndex)
{
	this->KillSocer[aIndex] = 0;
}

bool cLoraBattle::CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->Enable || !this->Start) return true;

	if(lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		if(lpObj->MapNumber==0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131) return false;
	}
	return true;
}

#endif