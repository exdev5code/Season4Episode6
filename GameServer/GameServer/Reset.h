#include "StdAfx.h"
#include "user.h"

class cReset
{
public:
	void Load();
#if __MuRain__
	struct
	{
		int Reset;
		int Level;
	}rTab[100];
	int Count;
	void Init();
#endif
	void ExResetSystemFunciton(int aIndex);
#ifdef _Eugene_
	int NPC_Num;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;
	int NeedItemEnable;
	int NeedItemType;
	int NeedItemIndex;
	int NeedItemLevel;
	void NPCReset(LPOBJ lpNpc, LPOBJ lpObj);
#endif
};
extern cReset gReset;

