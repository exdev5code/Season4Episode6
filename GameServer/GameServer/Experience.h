#ifndef _EXPERIENCE_H_
#define _EXPERIENCE_H_

#include "user.h"

#define EXPERIENCE_DIR "..\\ExTeam\\Experience.ini"
#define EXPERIENCE_MAX_RES 500

class cExperience
{
private:
	int Enable;

	struct 
	{
		int Res;
		int Exp;
	} Number[EXPERIENCE_MAX_RES];
	int rCount;

public:
	void LoadConfig();
	void Main(LPOBJ lpObj, __int64 & Experience);	//Panda User

};
extern cExperience ExExperience;

#endif