#include "StdAfx.h"
#include "..\include\prodef.h"
// ----------------------------------------------------------------------------------------------

#if(ANTI_CHEAT_PLUS==TRUE)

#define MAX_AH_DB		256
// ----------------------------------------------------------------------------------------------

#define AH_PLUS_PATH

enum eAH
{
	eTitleType,
	eClassType,
	eInjectType,
	eProcessType,
};
// ----------------------------------------------------------------------------------------------

enum eProtocolAHSub
{
	eAH_Config,
	eAH_Init,
	eAH_Title,
	eAH_Class,
	eAH_Inject,
	eAH_Process,
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_SUB
{
	PBMSG_HEAD2 h;
	BYTE type;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_AH_CONFIG
{
	PBMSG_HEAD2 h;
	BYTE type;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;
	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;
};
// ----------------------------------------------------------------------------------------------

struct PMSG_CheatBase
{
	PBMSG_HEAD2 h;
	BYTE type;
	char Name[64];
};
// ----------------------------------------------------------------------------------------------

struct PMST_CheaterUser
{
	PBMSG_HEAD2 h;
	BYTE Result;
	char CheatText[64];
};
// ----------------------------------------------------------------------------------------------

class AntiCheatPlus
{
public:
	void Init();
	void Load();
	void ReadConfig(char* File);
	void Read(int type, char* File);

	void GC_Cheat(int UserIndex);
	void CG_Cheater(PMST_CheaterUser* aRecv, int UserIndex);

	void GC_Config(int UserIndex);
	void GC_Init(int UserIndex);
	void GC_Title(int UserIndex);
	void GC_Class(int UserIndex);
	void GC_Inject(int UserIndex);
	void GC_Process(int UserIndex);

	bool Enable;
	bool DumpActive;
	bool TitleActive;
	bool ClassActive;
	bool InjectActive;
	bool ProcessActive;
	bool EliteActive;

	WORD DumpTime;
	WORD TitleTime;
	WORD ClassTime;
	WORD InjectTime;
	WORD ProcessTime;

	char TitleName[MAX_AH_DB][64];
	char ClassName[MAX_AH_DB][64];
	char InjectName[MAX_AH_DB][64];
	char ProcessName[MAX_AH_DB][64];

	int TitleCount;
	int ClassCount;
	int InjectCount;
	int ProcessCount;
};
extern AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

#endif