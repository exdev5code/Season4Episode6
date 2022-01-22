#include "StdAfx.h"
#include "user.h"

#ifndef _EX_QUEST_SYSTEM_H
#define _EX_QUEST_SYSTEM_H

#define MAX_EX_QUEST		1000
#define DIR_EX_QUEST_SYSTEM "..\\ExTeam\\ExQuestSystem.ini"

class cExQuest
{
public:
	int Enable;
	int NPC;
	char NameQuest[50];

	void Loader();
	void NPCClick(LPOBJ lpNpc, LPOBJ lpObj);
	void MonsterKill(LPOBJ lpObj, LPOBJ lpTargetObj);
	void Pressent(LPOBJ lpObj, int Present, int Gifts,int Level);

	struct
	{
		int Monster;
		int Count;
		int Procent;
		int Reward;
		int Gift;
		int iLevel;
		char Msg1[100];
		char Msg2[100];
	}Quest[MAX_EX_QUEST];

	int qNum;

};
extern cExQuest ExQuestSystem;
#endif _EX_QUEST_SYSTEM_H