#ifndef GMMNG_H
#define GMMNG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_GM_COMMAND 650
#define MAX_GMCOMMAND_LEN 20
#define MAX_GAME_MASTER 5


#include "user.h"


class CGMCommand
{

public:


	CGMCommand()
	{
		this->Init();
	}

	void Init()
	{
		for ( int n = 0; n<  MAX_GM_COMMAND; n++ )
		{
			this->nCmdCode[0] = -1;
		}

		this->count=0;
	}

	void Add(LPSTR command_str, int command_code,int gamemaster_code) 
	{
		strcpy(this->szCmd[this->count], command_str);
		this->nCmdCode[this->count]=command_code;
		this->nGMCode[this->count]=gamemaster_code | 0x02 | 0x20 | 0x40;//Season 4.5 changed

		if ( this->count < MAX_GM_COMMAND-1 )
		{
			this->count++;
		}
	}


public:
	
	char szCmd[MAX_GM_COMMAND][MAX_GMCOMMAND_LEN];
	int nCmdCode[MAX_GM_COMMAND];
	int nGMCode[MAX_GM_COMMAND];
	int count;
};



class CGMMng
{

public:

	CGMMng();
	virtual ~CGMMng();

	void Init();
	int GetCmd(LPSTR szCmd);
	BYTE GetData(char *szCmd,int &command_code,int &gamemaster_code);
	int ManagementProc(LPOBJ lpObj, LPSTR szCmd, int aIndex);
	LPSTR GetTokenString();
	int GetTokenNumber();
	void GetInfinityArrowMPConsumption(LPOBJ lpObj);
	void ControlInfinityArrowMPConsumption0(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption1(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption2(LPOBJ lpObj, int iValue);
	void ControlInfinityArrowMPConsumption3(LPOBJ lpObj, int iValue);
	void SetInfinityArrowTime(LPOBJ lpObj, int iValue);
	void ControlFireScreamDoubleAttackDistance(LPOBJ lpObj, int iValue);
	void ManagerInit();
	int  ManagerAdd(LPSTR name, int aIndex);
	void ManagerDel(LPSTR name);
	void ManagerSendData(LPSTR szMsg, int size);
	void BattleInfoSend(LPSTR Name1, BYTE score1, LPSTR Name2, BYTE score2);
	void DataSend(LPBYTE szMsg, int size);

	void CmdAbility(LPOBJ lpObj,char *szName);
	void CmdParty(LPOBJ lpObj,char *szName);
	void CmdSummonMonster(LPOBJ lpObj,char *szMonsterName,int MonsterCount);
	void CmdClearMonster(LPOBJ lpObj,int Dis);
	void CmdClearItem(LPOBJ lpObj,int Dis);
	void CmdClearInven(LPOBJ lpObj);
	void CmdSummonChar(LPOBJ lpObj,char * szName);
	int GetType(WORD wClass);
private:

	CGMCommand cCommand;
	char szManagerName[MAX_GAME_MASTER][11];
	int ManagerIndex[MAX_GAME_MASTER];

public:

	int WatchTargetIndex;
};

extern CGMMng cManager;

#endif