#include "StdAfx.h"

#if __MuRain__

#include "user.h"

#define NOOBSYSTEM_DIR "..\\ExTeam\\NoobSystem.ini"

class cNoobSystem
{
private:
	bool Enable;
	int MaxTime;
	int PlusExp;
public:
	void Init();
	void Timer(int aIndex);
	void Experience(LPOBJ lpObj, __int64 &Exp);
};
extern cNoobSystem gNoobSystem;

#endif