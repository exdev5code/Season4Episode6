#ifndef _MAPEXP_
#define _MAPEXP_

#include "StdAfx.h"
#include "MapClass.h"

#define MAPEXP_DIR "..\\ExTeam\\MapExp.ini"

class cMapExp
{
private:
	int Enable;
	struct 
	{
		int Map;
		int Exp;
	} Number[MAX_NUMBER_MAP];
	int mCount;
public:
	void Init();
	void Main(LPOBJ lpObj, __int64 & Experience);
};
extern cMapExp gMapExp;

#endif