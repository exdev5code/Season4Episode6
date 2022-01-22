#include "StdAfx.h"

#ifdef _CHAOS_MIX_MANAGER_

#include "USER.h"
#include "ChaosMixManager.h"
#include "..\include\readscript.h"
#include "MixSystem.h"
#include "DSProtocol.h"

cChaosMixManager ChaosMixManager;

void cChaosMixManager::Init()
{
	SMDFile = fopen(MIX_DIR, "r");
	if ( SMDFile == NULL )
	{
		MessageBoxA(0,MIX_DIR,"LOAD FILE ERROR",0);
		ExitProcess(0);
	}
	int Token;
	int type = -1;
	this->MixCount = 0;
	while ( true )
	{
	    Token = GetToken();
        if( Token == END) break;
		this->MixID[this->MixCount] = (int)TokenNumber;			//MixID

		Token = GetToken();
		this->MixPercent[this->MixCount] = (int)TokenNumber;	//MixPercent

		Token = GetToken();
		this->MixZen[this->MixCount] = (int)TokenNumber;		//MixZen

		this->ItemCount[this->MixCount] = 0;

		while ( true )
		{
		    Token = GetToken();
			if (!strcmp("end",TokenString))	break;

			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].MixType = TokenNumber;

			Token = GetToken();	
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Type = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Index = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Lvl = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Skill = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Luck = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Opt = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Exl = TokenNumber;

			Token = GetToken();
			this->Mix[this->MixCount][this->ItemCount[this->MixCount]].Anc = TokenNumber;

			this->ItemCount[this->MixCount]++;
		}
		this->MixCount++;
    }
	fclose(SMDFile);
}

void cChaosMixManager::Box(int aIndex, int IMix, int Num)
{
	//ITEMSTRUCT ChaosItem;

	LPOBJ lpObj = &gObj[aIndex];

	PMSG_CHAOSMIXRESULT pMsg;

	pMsg.Result = CB_ERROR;

	int Percent = this->MixPercent[Num];
	int Zen = this->MixZen[Num];
	bool Error = false;
	int rNum = 0;
	int arrNum[CHAOS_ITEM] = { 0 };

	int rNumCount = 0;

	for(int i=0;i<this->ItemCount[Num];i++)
	{
		if(this->Mix[Num][i].MixType == 1)
		{
			if(!this->nIBox(aIndex,ITEMGET(this->Mix[Num][i].Type,this->Mix[Num][i].Index),this->Mix[Num][i].Lvl,this->Mix[Num][i].Skill,
			this->Mix[Num][i].Luck,this->Mix[Num][i].Opt,this->Mix[Num][i].Exl,this->Mix[Num][i].Anc))
			{
				Error == true;
			}
		}
		else if(this->Mix[Num][i].MixType == 2)
		{
			arrNum[rNumCount] = i;
			rNumCount++;
		}
	}


	if(Error == true)
	{
		pMsg.Result = CB_INCORRECT_MIX_ITEMS;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	if(lpObj->Money < Zen)
	{
		pMsg.Result = CB_NOT_ENOUGH_ZEN;
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);
		return;
	}

	srand(time(NULL));
	rNum = arrNum[rand()%rNumCount];

	lpObj->Money-=(Zen);

	GCMoneySend(aIndex, lpObj->Money);


	if(Percent > (rand()%100))
	{
		int cExl = 0;
		int cAnc = 0;

		if(this->Mix[Num][rNum].Exl > 0)
		{
			int ExcellentOpt[6] = { 1, 2, 4, 8, 16, 32 };
			srand(time(NULL));
			cExl = ExcellentOpt[rand()%6];
		}

		if(this->Mix[Num][rNum].Anc == 5 || this->Mix[Num][rNum].Anc == 10)
		{
			cAnc = this->Mix[Num][rNum].Anc;
		}

		//ChaosItem.m_Type			= ITEMGET(this->Mix[Num][rNum].Type,this->Mix[Num][rNum].Index);
		//ChaosItem.m_Level			= this->Mix[Num][rNum].Lvl;
		//ChaosItem.m_Durability		= 0;
		//ChaosItem.m_SetiLuck		= this->Mix[Num][rNum].Luck;
		//ChaosItem.m_SetiOption		= this->Mix[Num][rNum].Opt;
		//ChaosItem.m_SetiSkill		= this->Mix[Num][rNum].Skill;
		//ChaosItem.m_SetiExcellent	= cExl;
		//ChaosItem.m_SetOption		= cAnc;

		//ChaosMixSendSuccess(&ChaosItem, aIndex);

		ItemSerialCreateSend(lpObj->m_Index, -1, 0, 0, ITEMGET(this->Mix[Num][rNum].Type,this->Mix[Num][rNum].Index), 0, 0, 
			this->Mix[Num][rNum].Skill, (BYTE)this->Mix[Num][rNum].Luck, (BYTE)this->Mix[Num][rNum].Opt, -1, (BYTE)cExl, cAnc);
		::gObjInventoryCommit(lpObj->m_Index);
	}
	else
	{
		g_MixSystem.ChaosBoxInit(lpObj);

		::GCUserChaosBoxSend(lpObj, 0);
		DataSend(lpObj->m_Index, (LPBYTE)&pMsg, pMsg.h.size);

		//ChaosMixSendFail(aIndex);
	}

}

bool cChaosMixManager::Main(int aIndex, int MixIndex)
{
	for(int i=0;i<this->MixCount;i++)
	{
		if(this->MixID[i] == MixIndex)
		{
			this->Box(aIndex,MixIndex,i);
			return true;
		}
	}
	return false;
}

bool cChaosMixManager::nIBox(int aIndex, int iType, int iLevel, int iSkill, int iLuck, int iOpt, int iExl, int iAnc)
{
	//OBJECTSTRUCT * gObj = (OBJECTSTRUCT*) OBJECT_POINTER (aIndex);

	LPOBJ lpObj = &gObj[aIndex];

	int count = 0;
	for(int i = 0; i < 32; i++)
	{
		int nOpt = 0;
		int nExl = 0;
		int nAnc = 0;
		if(lpObj->pChaosBox[i].m_Option3 > 0)		nOpt = 1;
		if(lpObj->pChaosBox[i].m_NewOption > 0)		nExl = 1;
		if(lpObj->pChaosBox[i].m_SetOption > 0)		nAnc = 1;
		//----
		if( iType == 0 )
		{
			if( nOpt == iOpt
				&& nExl == iExl
				&& nAnc == iAnc )
				return true;
		}
		else
		{
			if( lpObj->pChaosBox[i].m_Type == iType 
				&& lpObj->pChaosBox[i].m_Level == iLevel
				&& nOpt == iOpt
				&& nExl == iExl
				&& nAnc == iAnc )
				return true;
		}
		//----
	}
	return false;
}

#endif