#include "StdAfx.h"
#include "user.h"

#ifdef _NEW_JEWELS_2_

#define NewJewels_DIR "..\\Data\\ExData\\NewJewels.ini"

class cNewJewels
{
private:
	int Enable;

	int JewelOfExellentType;
	int JewelOfExellentIndex;
	int JewelOfExellentEnable;
	int JewelOfExellentRate;
	int JewelOfExellentMaxOpt;

	int JewelOfMisticType;
	int JewelOfMisticIndex;
	int JewelOfMisticEnable;
	int JewelOfMisticMaxLvl;
	int JewelOfMisticMinLvl;
	int JewelOfMisticRate;

	int JewelOfLuckType;
	int JewelOfLuckIndex;
	int JewelOfLuckEnable;
	int JewelOfLuckRate;

	int JewelOfSkillType;
	int JewelOfSkillIndex;
	int JewelOfSkillEnable;
	int JewelOfSkillRate;

	int JewelOfLevelType;
	int JewelOfLevelIndex;
	int JewelOfLevelEnable;
	int JewelOfLevelMax;
	int JewelOfLevelMin;
	int JewelOfLevelRate;

	int JewelOfEvalutionType;
	int JewelOfEvalutionIndex;
	int JewelOfEvalutionEnable; 
	int JewelOfEvalutionRate;

	int JewelOfAncentType;
	int JewelOfAncentIndex;
	int JewelOfAncentEnable;
	int JewelOfAncentRate;

	int JewelOfOptionType;
	int JewelOfOptionIndex;
	int JewelOfOptionEnable;
	int JewelOfOptionRate;

public:
	void Load();

	bool IsAccessory(int ItemID);
	BYTE GetExcUnusedOption(BYTE ExcellentOption);
	bool CheckJewel(int iType);
	void JewelMain(LPOBJ lpObj, int source, int target);

};
extern cNewJewels gNewJewels;

#endif



bool ExSecurityJewel(LPOBJ lpObj, int source, int target);
bool ExJewelOfExellentAdded (LPOBJ lpObj, int source, int target);
bool ExJewelOfDivinityAdded (LPOBJ lpObj, int source, int target);
bool ExJewelOfLuckAdded (LPOBJ lpObj, int source, int target);	//Jewel Of Luck

