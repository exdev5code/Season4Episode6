#include "StdAfx.h"
#include "user.h"
#include "ExQuestSystem.h"
#include "Functions.h"
#include "Message.h"
//#include "MapClass.h"
#include "DSProtocol.h"
#include "PCPointSystem.h"
#include "GameMain.h"
#include "logproc.h"

cExQuest ExQuestSystem;

void cExQuest::Loader()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,DIR_EX_QUEST_SYSTEM);
	this->NPC = GetPrivateProfileInt("Common","NPC",0,DIR_EX_QUEST_SYSTEM);

	GetPrivateProfileString("Common", "NameQuest","Quest",this->NameQuest,sizeof(this->NameQuest),DIR_EX_QUEST_SYSTEM);

	for(int i=0;i<MAX_EX_QUEST;i++)
	{
		this->Quest[i].Monster	= 0;
		this->Quest[i].Count	= 0;
		this->Quest[i].Procent	= 0;
		this->Quest[i].Reward	= 0;
		this->Quest[i].Gift		= 0;
		this->Quest[i].iLevel	= 0;
		this->Quest[i].Msg1[0]	= NULL;
		this->Quest[i].Msg2[0]	= NULL;
	}

	FILE *file = fopen(DIR_EX_QUEST_SYSTEM,"r");
	if(file == NULL)
	{
		this->Enable = 0;
		return;
	}

	char Buff[256];
	int Flag = 0;
	qNum = 1;	//Fix

	while(!feof(file))
	{
		fgets(Buff,256,file);	
		if(Ex_IsBadFileLine(Buff, Flag))	
			continue;

		if(Flag == 1)
		{
			int n[10];
			char mes[100];
			char mes2[100];

			sscanf(Buff,"%d %d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&mes,&mes2);

			this->Quest[qNum].Monster	= n[0];
			this->Quest[qNum].Count		= n[1];
			this->Quest[qNum].Procent	= n[2];
			this->Quest[qNum].Reward	= n[3];
			this->Quest[qNum].Gift		= n[4];
			this->Quest[qNum].iLevel	= n[5];
			sprintf(this->Quest[qNum].Msg1,"%s",mes);
			sprintf(this->Quest[qNum].Msg2,"%s",mes2);

			qNum++;
		}
	}
	fclose(file);
}

void cExQuest::NPCClick(LPOBJ lpNpc, LPOBJ lpObj)
{
	if(!this->Enable)
		return;

	if(lpNpc->Class != this->NPC)
		return;

	if(ExUser[lpObj->m_Index].ExQuestNum == 0) ExUser[lpObj->m_Index].ExQuestNum++;	//Fix

	int Number = ExUser[lpObj->m_Index].ExQuestNum;

	if(Number >= this->qNum)
	{
		MessageChat(lpObj->m_Index,"@[%s]: Finish!",this->NameQuest);
		return;
	}

	if(ExUser[lpObj->m_Index].ExQuestKill == this->Quest[Number].Count)
	{
		this->Pressent(lpObj,this->Quest[Number].Reward,this->Quest[Number].Gift,this->Quest[Number].iLevel);

		ExUser[lpObj->m_Index].ExQuestNum++;
		ExUser[lpObj->m_Index].ExQuestKill = 0;
	}
	else
	{
		LPMONSTER_ATTRIBUTE lpMA = gMAttr.GetAttr(this->Quest[Number].Monster);

		MessageChat(lpObj->m_Index,"@[%s]: Mission: %d",this->NameQuest,Number);	//Fix
		MessageChat(lpObj->m_Index,"@[%s]: %s",this->NameQuest,this->Quest[Number].Msg1);
		MessageChat(lpObj->m_Index,"@[%s]: %s [%d/%d]",
			this->NameQuest,
			this->Quest[Number].Msg2,
			ExUser[lpObj->m_Index].ExQuestKill,
			this->Quest[Number].Count);
	}
}

void cExQuest::MonsterKill(LPOBJ lpObj, LPOBJ lpTargetObj)	//lpTargetObj - тот кто убивает
{
	if(!this->Enable)
		return;

	int Number = ExUser[lpTargetObj->m_Index].ExQuestNum;

	if(Number == 0 || Number >= this->qNum) return;	//New Fix

	if(lpObj->Class == this->Quest[Number].Monster)
	{
		if(this->Quest[Number].Count == ExUser[lpTargetObj->m_Index].ExQuestKill)
		{
			return;
		}

		srand(time(NULL));
		int iRate = rand()%100;

		if(this->Quest[Number].Procent > iRate)
		{
			ExUser[lpTargetObj->m_Index].ExQuestKill++;
			MessageChat(lpTargetObj->m_Index,"@[%s]: %s [%d/%d]",
				this->NameQuest,
				this->Quest[Number].Msg2,
				ExUser[lpTargetObj->m_Index].ExQuestKill,
				this->Quest[Number].Count);

			if(this->Quest[Number].Count == ExUser[lpTargetObj->m_Index].ExQuestKill)
			{
				MessageChat(lpTargetObj->m_Index,"@[%s]: Mission accomplished!",this->NameQuest);
			}
		}
	}
}

void cExQuest::Pressent(LPOBJ lpObj, int Present, int Gifts,int Level)
{
	//1- Zen, 2 - FreePoints, 3 - Items, 4 - ExPoint, 5 - Wcoin
	if(Present == 1)	//Zen
	{

		if( lpObj->Money + Gifts > 2000000000 )
		{
			lpObj->Money = 2000000000;
		}
		else
		{
			lpObj->Money += Gifts;
		}
		//MapC[lpObj->MapNumber].MoneyItemDrop((int)Gifts, lpObj->X, lpObj->Y);
		GCMoneySend(lpObj->m_Index, lpObj->Money);
	}
	else if(Present == 2)
	{
		MessageChat(lpObj->m_Index,"@[%s]: FreePoints %d!",this->NameQuest,Gifts);
		ExUser[lpObj->m_Index].ExFreePoints += Gifts;
		lpObj->LevelUpPoint += Gifts;
		GCLevelUpMsgSend(lpObj->m_Index, 0);
	}
	else if(Present == 3)
	{
		ItemSerialCreateSend(lpObj->m_Index,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,Gifts,(BYTE)Level,0,0,0,0,lpObj->m_Index,0,0);
	}
	else if(Present == 4)
	{
		MessageChat(lpObj->m_Index,"@[%s]: ExPoint %d!",this->NameQuest,Gifts);
		ExUser[lpObj->m_Index].PCPoint += Gifts;
		ExPCPointSystem.InitPCPointForPlayer(lpObj,ExUser[lpObj->m_Index].PCPoint,lpObj->ExCred);
	}
	else if(Present == 5)
	{
		MessageChat(lpObj->m_Index,"@[%s]: WCoin %d!",this->NameQuest,Gifts);
		GDRequestWcoinInfoLoad (lpObj,Gifts,1);
	}
	ExFireCracker(lpObj->m_Index, lpObj->X, lpObj->Y);
}