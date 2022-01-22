#include "StdAfx.h"

#if(NEW_ITEM_DROP)

#define ITEM_DROP_DIR	"..\\Data\\ExData\\ItemDropManager.ini"
#define MAX_DROP_ITEM	1000

#include "User.h"

class NewCItemDropManager
{
public:
	void Init();
	bool ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj);
	bool BlockItemDrop(int aIndex, int ItemID, int MapNumber);

private:

	bool iUser[OBJMAX];

	int DropCount;
	struct 
	{
		int Type;
		int Index;
		int MinLevel;
		int MaxLevel;
		int Dur;
		int OptionRate;
		int MaxOption;
		int LuckRate;
		int LuckOption;
		int SkillRate;
		int SkillOption;
		int ExlRate;
		int ExlOption;
		int AncRate;
		int AncOption;
		int MonsterMinLevel;
		int MonsterMaxLevel;
		int MonsterMap;
		int ItemDropRate;
	}Drop[MAX_DROP_ITEM];

	int BlockCount;
	struct
	{
		int Type;
		int Index;
	}Block[MAX_DROP_ITEM];
};

extern NewCItemDropManager NewgItemDropManager;

#endif