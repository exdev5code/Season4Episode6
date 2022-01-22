#include "StdAfx.h"

#if(_GRAND_HERO_SYSTEM_)

#include "user.h"
/*
	нужно добавить новые атт файлы для карт
	Увеличить тайп монстров
	Увеличить константу с количеством карт
*/

#define GRANDHERO_DIR "..\\ExTeam\\GrandHeroSystem.ini"

class cGrandHero
{
private:
	int Enable;
	int GRTp;
	int GRItem;
	int MixItemRate;
	int MixMoney;
	int ExStoneDropRate;
	int BossAncDrop;
	int OffTradeLoren;

	int BossDropCount;

	int ResetTP;

	int TPMap;
	int TPX;
	int TPY;

	struct 
	{
		short Index;
		short ItemID;
		short Level;
		short Skill;
		short Luck;
		short Options;
		short Exl;
		short Anc;
	}Items[100];
	int ItemCoint;

public:
	void Load();
	void NPCLoad(int aIndex, int MonsterClass);
	bool NPCTeleport(LPOBJ lpNpc, LPOBJ lpObj);
	void ItemOption(int aIndex);
	bool SockeetItem(int ItemNumber);
	void MixGrandItem(LPOBJ lpObj);
	bool BossDrop(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool MoveGRItem(int aIndex, int ItemNumber, int target);
	bool HeroMap(int iMap);
	bool OffTradeLorenMarket(int aIndex,int type);
	void CheckGRMap(int aIndex);

};
extern cGrandHero GrandHero;

#endif
