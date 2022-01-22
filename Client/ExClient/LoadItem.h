#include "stdafx.h"

#if(_ITEM_LOAD_)

#define MAX_LOAD_ITEM	1000

#define LOAD_ITEM_DIR	"Data\\ExTeam\\LoadItem.ini"

class cLoadItem
{

public:
	void Load();
	struct 
	{
		int Type;
		int Index;
		char BMD[50];
		char Dir1[50];
		char Dir2[50];
	}ILoad[MAX_LOAD_ITEM];
	int Count;

};
extern cLoadItem gLoadItem;

#endif