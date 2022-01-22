#ifndef QUESTUTIL_H
#define QUESTUTIL_H

#include "user.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct PMSG_004A2100
{
	PBMSG_HEAD h;	// C1
	int iUserIndex;	//
	char chCharacterName[11];	//
};

typedef struct
{
	PBMSG_HEAD h;
	int Index;
	char szName[11];
	int QuestIndex;
	MONSTERKILLINFO KillInfo[5];
}PMSG_ANS_MONSTERKILLINFO, *LPMSG_ANS_MONSTERKILLINFO;

typedef struct
{
	PBMSG_HEAD h;
	int Index;
	char szName[11];
	int QuestIndex;
	MONSTERKILLINFO KillInfo[5];
}PMSG_SAVE_MONSTERKILLINFO, *LPMSG_SAVE_MONSTERKILLINFO;

class CQuestUtil  
{
public:
	CQuestUtil();
	virtual ~CQuestUtil();

	void Quest3rdRequestInfo(LPOBJ lpObj);
	void Quest3rdLoadInfo(LPBYTE aRecv);
	void Quest3rdSaveInfo(LPOBJ lpObj);
};

extern CQuestUtil g_QuestUtil;

#endif