#pragma once

#include "StdAfx.h"

#if(CUSTOM_NPC_TELEPORT==TRUE)

class NPCTeleport
{
public:
	NPCTeleport();
	~NPCTeleport();

	void Init();
	void Load();
	void Read(char* File);
	bool Dialog(int UserIndex, int NPC_Index);

	bool Enable;
	int NPC_Class;
	int NPC_Map;
	int NPC_X;
	int NPC_Y;
	int TeleportMap;
	int TeleportX;
	int TeleportY;

	int NeedZen;
	int NeedWcoin;
	int NeedCredits;
	int NeedReset;
	int NeedLevel;
};
extern NPCTeleport g_NPCTeleport;

#endif