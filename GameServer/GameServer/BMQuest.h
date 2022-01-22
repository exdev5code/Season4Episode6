#include "user.h"
#include "StdAfx.h"

#if(BM_QUEST_SYSTEM_)

#define _MAX_BMQUEST 1000
#define _DIR_BMQUEST "..\\ExTeam\\BMQuest.ini"
#define _MAX_CLASS_BMQUEST 7

class cBMQuest
{
public:
	int Enable;
	int NPC;
	int NPC_Map;
	int	NPC_X;
	int	NPC_Y;

	int Reset;

	struct
	{
		int Mob;
		int Coun;
		int proc;
		int rew;
		int gift;
		char msg[100];
		char msg2[100];
	}Quest[_MAX_CLASS_BMQUEST][_MAX_BMQUEST];

	void StartConfig();
	void StartUP();
	void AddedCharacter(int aIndex);
	void CharacterInformation(int aIndex);
	void NPCClick(int aIndex,int aNPC);
	void NPCdialogue(int aIndex,int aNPC);
	void MonsterKill(int aIndex, int aMob);
	void Presents(int aIndex, int Present, int Gifts);

	int Count[_MAX_CLASS_BMQUEST];
};
extern cBMQuest BMQuest;

#endif