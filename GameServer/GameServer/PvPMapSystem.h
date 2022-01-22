#ifndef _PVP_MAP_SYSTEM_H
#define _PVP_MAP_SYSTEM_H
#include "MapClass.h"
#define PVPMAPSYSTEM_DIR	"..\\ExTeam\\PvPSystem.ini"
class cPvPMapSystem
{
private:
	int EnablePvPMap;
	int EnableLoraRing;
	struct  
	{
		int Map;
		int Status;
	}PvP[MAX_NUMBER_MAP];
	int pCount;
public:
	void LoadConfig();
	bool CheckAttackMap(LPOBJ lpObj, LPOBJ lpTargetObj);
	bool CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj);
};
extern cPvPMapSystem PvPMapSystem;

#endif