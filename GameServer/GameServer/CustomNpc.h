#include "StdAfx.h"

#define MAX_CUSTOM_NPC 100

#define CUSTOM_NPC_DIR "..\\Data\\ExData\\CustomNpc.ini"

class cCustomNpc
{
private:
	int Enable;
	int NpcList[MAX_CUSTOM_NPC];
	int CountNpc;
public:
	void Load();
	void Main(int aIndex, int MonsterClass);

};

extern cCustomNpc gCustomNpc;