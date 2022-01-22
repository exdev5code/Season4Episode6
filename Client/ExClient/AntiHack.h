#include "stdafx.h"

#if ANTI_HACK

#define MAX_DUMP_OFFSETS 3
#define MAX_DUMP_SIZE 32
#define MAX_PROCESS_DUMP 704	//708

typedef struct ANITHACK_PROCDUMP
{
	unsigned int m_aOffset;
	unsigned char m_aMemDump[MAX_DUMP_SIZE];
	char Name[100];
} *PANITHACK_PROCDUMP;

extern ANITHACK_PROCDUMP g_ProcessesDumps[MAX_PROCESS_DUMP];

bool LoadFilesBase(char * cFile);

void LogsAdded (char* Message,...);

#define MAIN_SIZE 1178112
#define PLAYER_SIZE 2662002
#define wzexgah_SIZE 194048
#define Glow_SIZE 69632
#define MaEx_SIZE 65536
#define mulan_SIZE 98304
#define rus_SIZE 53760
#define tex_SIZE 61440

void SystemProcessesScan();
bool ScanProcessMemory(HANDLE hProcess);
int	iGetFileSize(char* FileName);
bool iCheckFileSize(char* cFile,int Size);
bool AllCheckSizeFiles();
void CheckFilesDir(bool TypeStart);

#endif