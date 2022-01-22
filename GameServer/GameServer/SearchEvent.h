#include "StdAfx.h"

#ifdef _EVANGELION_EVENT_

#define SEARCH_EVENT_DIR "..\\ExTeam\\Events\\SearchEvent.ini"

#define DEF_MAP 5
#define DEF_X 123
#define DEF_Y 123

class cSearchEvent
{
private:
	int Enable;
	int IndexNPC;

	int NPC;
	int Map;

	int PresWcoin;
	int Time;
	int ItemCount;

	bool Start;
	int Tick;
	int Stage;

	void SearchIndexNPC();

	void Present(int aIndex);

	void EventStart();
	void EventEnd();

	struct  
	{
		int Hour;
		int Min;
	}TickTime[10];

	struct
	{
		int Index;
		int Type;
		int Level;
		int Skill;
		int Luck;
		int Opt;
		int Exl;
		int Anc;
	}Item[255];

	struct  
	{
		int X;
		int Y;
	}Cord[4][100];

	int Count;
	int Count2;

	int CountCord[4];
public:
	void NPCClick(int aIndex, int aNPC);
	void StartNPC();
	void LoadingEvent();
};
extern cSearchEvent SearchEvent;

#endif