#include "StdAfx.h"

#ifdef _GRAND_SYSTEM_

#define OFFST_MODELRES_SIZEOF 0x005D5F44
#define OFFST_MODELRES_COUNT 0x005D5F3F
#define OFFST_MODELRES_MOBS_ID 0x005DD7C5

#define HPROC_OPENMONSTERMODEL_BULL 0x00501696	//my - 00501696, loh -0x005004A8
#define HARGS_BULL_PUSH HPROC_OPENMONSTERMODEL_BULL - 2
#define HPROC_CONSTMONSTERMODEL_BULL 0x005016B1	// my - 005016B1 , loh - 0x005004C3
#define HPROC_LOADBMDMODEL 0x005DD811
#define HPROC_LOADPLAYERBMD 0x005D5FCA

#define HOpenMonsterModel ((void (__cdecl *)(DWORD dwMobNumber)) 0x005DD7BC)
//--
#define sub_5D5710 ((DWORD (__cdecl *)(DWORD Arg1, LPSTR Arg2, DWORD Arg3, DWORD Arg4)) 0x5D5710)
//--
//sub_5D5710(824, "Npc\\", 10497, 9728);

#define HConstructMonsterModel ((DWORD (__cdecl *)(DWORD Arg1, DWORD dwResInx, DWORD dwResOffst, DWORD Arg4, DWORD Arg5)) 0x004FD3A4)	//my - 004FD3A4, loh - 0x004FEDE
#define HLoadBMDModel ((DWORD (__cdecl *)(DWORD Arg1, LPSTR Arg2, LPSTR Arg3, DWORD Arg4)) 0x005D5DC3)

#define HPROC_SETMOBNAMESTYLE 0x00503ED6
#define HSetMonsterNameStyle ((DWORD (__cdecl *)(DWORD dwMemAddr, DWORD dwMobID, DWORD Arg3, DWORD Arg4)) 0x004FEDE7)

static DWORD *lpModelResBase = (DWORD *)0x6AC7AA8;
static DWORD *lpModelResArray = (DWORD *)0x596CB28;
 
struct Unit_Struct
{
        BYTE Unknown1[32];
        BYTE bPKStatus;
        BYTE Unknown2[23];
        char cName[32];
        BYTE bMoveOut;
        BYTE Unknown5[303];
        signed short sItem1ResID;
        BYTE Unknown7;
        signed char bItem1IsExc;
        BYTE Unknown8;
        signed char bItem1JoinID;//6
        BYTE Unknown9[26];//26
        signed short sItem2ResID;
        BYTE Unknown10;
        signed char bItem2IsExc;
        BYTE Unknown11;
        signed char bItem2JoinID;//6
        BYTE Unknown12[292];
        BYTE bMobType;
        BYTE Unknown13[73];
        float fSize;
};
 
struct MobParam_Struct
{
        DWORD dwMobID;
        LPSTR lpName;
        signed char bMobType;
        signed char bPKStatus;
        signed char bMoveOut;
        signed short sItem1ResID;
        signed char bItem1IsExcl;
        signed char bItem1JoinID;
        signed short sItem2ResID;
        signed char bItem2IsExcl;
        signed char bItem2JoinID;
        float fSize;
};
 
struct MonsterAdd_Struct
{
	//DWORD Type;
    DWORD dwMobID;
    char *lpDir;
    char *lpFile;
};
 
#define NONE -1

void __cdecl Hook_OpenMonsterModel(DWORD dwMobNumber);
DWORD __cdecl Hook_ConstructMonsterModel(DWORD Arg1, DWORD dwResInx, DWORD dwResOffst, DWORD Arg4, DWORD Arg5);
void __cdecl Hook_FixLoadBMDModel(DWORD dwResInx, LPSTR lpDir, LPSTR lpBaseName, DWORD Arg4);
void __cdecl Hook_LoadPlayerBMD(DWORD dwResInx, LPSTR lpDir, LPSTR lpBaseName, DWORD Arg4);
void __cdecl Hook_SetMonsterNameStyle(DWORD dwMemAddr, DWORD dwMobID, DWORD Arg3, DWORD Arg4);
void ModifMonsParams(DWORD lpUnit, DWORD dwMobID);

void Init_Monsters();
#endif

//Изменение параметров монстра
//Изменять любых монстров, как новых, так и стандартных. Структура MonsterParam_Struct:
//01.dwMobID - id юнита из Monster.txt
//02.lpName - имя юнита, если NULL то не меняется
//03.bMobType -тип юнита (0,1-unit, 2-monster, 3-can't select, 4-NPC), если NONE то не меняется
//04.bPKStatus - пк статус юнита (0-7), если NONE то не меняется
//05.bMoveOut - эффект, юнит убегает вперёд (0-1), если NONE то не меняется
//06.sItem1ResID - id ресурса модели, если NONE то не меняется
//07.bItem1IsExcl -переливается ли модель как excellent, если NONE то не меняется
//08.bItem1JoinID - join модели юнита к которому прекреплена модель sItem1ResID, если NONE то не меняется
//09.sItem2ResID - id ресурса модели, если NONE то не меняется
//10.bItem2IsExcl - переливается ли модель как excellent, если NONE то не меняется
//11.bItem2JoinID - join модели юнита к которому прекреплена модель sItem1ResID, если NONE то не меняется
//12.float fSize - размер модели(стандартно 1.0), если NULL то не меняется