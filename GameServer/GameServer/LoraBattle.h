#include "StdAfx.h"

#ifdef _LORA_BATTLE_

#include "USER.h"

#define LORABATTLE_DIR "..\\ExTeam\\Events\\LoraBattleEvent.ini"

class cLoraBattle
{
private:
	int Enable;
	bool Start;
	bool Waiting;

	int RewardWCoin;
	int RewardItem;

	int WCoin;
	int ITEM;
	int ITEM_LEVEL;

	int Fallen_DROP;
	int Fallen_ITEM;
	int Fallen_ITEM_LEVEL;

	int KillSocer[OBJMAX];

	int WaitingTick;
	int TimeTick;
	int EventTime;

	//bool BattleRing[OBJMAX];

	//int m_PK_Level[OBJMAX];

	int MaxSocer;
	int MaxIndex;

	char MSG[256];

	struct
	{
		//int StrHour;
		//int StrMin;
		int Hour;
		int Min;
		//int EndHour;
		//int EndMin;
	}Time[128];

	int Count;
	int EndCount;

public:
	void LoadConfigs();
	void StructStart(int aIndex);
	void StartEvent();
	void EndEvent();
	void TickTime();
	void BattleKillSocer(int aIndex,int aIndex2);
	void Reward(int aIndex);
	void Start1min();
	bool CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj);
};
extern cLoraBattle LoraBattle;

#endif