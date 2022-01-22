#include "stdafx.h"

#if(_LOAD_GLOW_)

#define MAX_LOAD_GLOW	1000

#define LOAD_GLOW_DIR	"Data\\ExTeam\\LoadGlow.ini"

class cLoadGlow
{

public:
	void Load();
	struct 
	{
		int Type;
		int Index;
		float Red;
		float Green;
		float Blue;
	}ILoad[MAX_LOAD_GLOW];
	int Count;

};
extern cLoadGlow gLoadGlow;

#endif