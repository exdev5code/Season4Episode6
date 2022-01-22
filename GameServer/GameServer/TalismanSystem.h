#include "StdAfx.h"

#ifdef TALISMAN_SYSTEM

#define TALISMANSYSTEM_DIR "..\\ExTeam\\TalismanSystem.ini"

class cTalismanSystem
{
private:
	int Enable;

	int TalismanOfDamage;
	int TalismanOfDefence;
	int TalismanOfDouble;
	int TalismanOfExellent;
	int TalismanOfCritical;
	int TalismanOfExperience;
	int TalismanOfIgnore;
	int TalismanOfReflect;

public:
	void LoadConfig();
	void Main (int aIndex);
	void MainExperience(int aIndex,__int64 & Experience);
};
extern cTalismanSystem TalismanSystem;
#endif