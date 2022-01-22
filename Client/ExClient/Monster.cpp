#include "stdafx.h"
#ifdef _GRAND_SYSTEM_
#include "Monster.h"
#include "Utilits.h"
#include "ToolKit.h"
#include "Console.h"

//int *MAP_CHECKER_ADDR = (int*)0x008C5CF8;

#define MONSTER_DIR "Data\\Monster\\"
#define NPC_DIR		"Data\\NPC\\"
#define NPC_DIR2	"NPC\\"

#if _MegaMu_ || __LOCAL__
#define ADD_MOBS_COUNT 10
#else
#define ADD_MOBS_COUNT 9
#endif
//59//9
MonsterAdd_Struct s_AddMob[ADD_MOBS_COUNT] =
{
	{520, MONSTER_DIR,	"monster173"},	//npc
	{521, MONSTER_DIR,	"Monster166"},				//npc
	{550, MONSTER_DIR,	"Monster176"},
    {551, MONSTER_DIR,	"monster178"},
    {552, MONSTER_DIR,	"Monster215"},
	{553, MONSTER_DIR,	"Monster213"},
	{554, MONSTER_DIR,	"monster169"},
	{555, MONSTER_DIR,	"Monster167"},
	{600, MONSTER_DIR,	"Monster171"},				//Boss
#if _MegaMu_ || __LOCAL__
	{601, MONSTER_DIR,	"Monster_exgames"}
#endif

	//{1, 601, MONSTER_DIR,	"CustoMob601"},
	//{1, 602, MONSTER_DIR,	"CustoMob602"},
	//{1, 603, MONSTER_DIR,	"CustoMob603"},
	//{1, 604, MONSTER_DIR,	"CustoMob604"},
	//{1, 605, MONSTER_DIR,	"CustoMob605"},
	//{1, 606, MONSTER_DIR,	"CustoMob606"},
	//{1, 607, MONSTER_DIR,	"CustoMob607"},
	//{1, 608, MONSTER_DIR,	"CustoMob608"},
	//{1, 609, MONSTER_DIR,	"CustoMob609"},
	//{1, 610, MONSTER_DIR,	"CustoMob610"},
	//{1, 611, MONSTER_DIR,	"CustoMob611"},
	//{1, 612, MONSTER_DIR,	"CustoMob612"},
	//{1, 613, MONSTER_DIR,	"CustoMob613"},
	//{1, 614, MONSTER_DIR,	"CustoMob614"},
	//{1, 615, MONSTER_DIR,	"CustoMob615"},
	//{1, 616, MONSTER_DIR,	"CustoMob616"},
	//{1, 617, MONSTER_DIR,	"CustoMob617"},
	//{1, 618, MONSTER_DIR,	"CustoMob618"},
	//{1, 619, MONSTER_DIR,	"CustoMob619"},
	//{1, 620, MONSTER_DIR,	"CustoMob620"},
	//{1, 621, MONSTER_DIR,	"CustoMob621"},
	//{1, 622, MONSTER_DIR,	"CustoMob622"},
	//{1, 623, MONSTER_DIR,	"CustoMob623"},
	//{1, 624, MONSTER_DIR,	"CustoMob624"},
	//{1, 625, MONSTER_DIR,	"CustoMob625"},
	//{1, 626, MONSTER_DIR,	"CustoMob626"},
	//{1, 627, MONSTER_DIR,	"CustoMob627"},
	//{1, 628, MONSTER_DIR,	"CustoMob628"},
	//{1, 629, MONSTER_DIR,	"CustoMob629"},
	//{1, 630, MONSTER_DIR,	"CustoMob630"},
	//{1, 631, MONSTER_DIR,	"CustoMob631"},
	//{1, 632, MONSTER_DIR,	"CustoMob632"},
	//{1, 633, MONSTER_DIR,	"CustoMob633"},
	//{1, 634, MONSTER_DIR,	"CustoMob634"},
	//{1, 635, MONSTER_DIR,	"CustoMob635"},
	//{1, 636, MONSTER_DIR,	"CustoMob636"},
	//{1, 637, MONSTER_DIR,	"CustoMob637"},
	//{1, 638, MONSTER_DIR,	"CustoMob638"},
	//{1, 639, MONSTER_DIR,	"CustoMob639"},
	//{1, 640, MONSTER_DIR,	"CustoMob640"},
	//{1, 641, MONSTER_DIR,	"CustoMob641"},
	//{1, 642, MONSTER_DIR,	"CustoMob642"},
	//{1, 643, MONSTER_DIR,	"CustoMob643"},
	//{1, 644, MONSTER_DIR,	"CustoMob644"},
	//{1, 645, MONSTER_DIR,	"CustoMob645"},
	//{1, 646, MONSTER_DIR,	"CustoMob646"},
	//{1, 647, MONSTER_DIR,	"CustoMob647"},
	//{1, 648, MONSTER_DIR,	"CustoMob648"},
	//{1, 649, MONSTER_DIR,	"CustoMob649"},
	//{1, 650, MONSTER_DIR,	"CustoMob650"},
};
DWORD dwNewMobResInx[ADD_MOBS_COUNT];

#if _MegaMu_ || __LOCAL__
#define MOBS_PARAMS_COUNT 10
#else
#define MOBS_PARAMS_COUNT 9
#endif

MobParam_Struct s_ParamMob[MOBS_PARAMS_COUNT] = 
{
	{520, "Loren Market", 4, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.0},
	{521, "Hero City", 4, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.3},
    {550, "Aidos", 2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1.3},
    {551, "ZveroLom", 2, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, 1.3},
    {552, "StriKozel", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.3},
	{553, "Brokin", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.5},
	{554, "Varol", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.5},
	{555, "Ishak", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.3},
#if _MegaMu_
	{600, "Fire Knight", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.5},
#else
	{600, "Hero Boss", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.5},
#endif
#if _MegaMu_ || __LOCAL__
	{601, "Anubis", 2, NONE, NONE, NONE, NULL, NULL, NONE, NULL, NULL, 1.0},
#endif
};

DWORD dwModelResInx, dwModelMobsID, dwModelResSizeof, dwModelResCount;
int iTempMobID = NONE;
 
void Init_Monsters() 
{
        DWORD dwResSize, dwResCount, dwTotalSize;
 
        // Get resource ID
        dwModelResSizeof = 0x0F4;//*(DWORD*)(OFFST_MODELRES_SIZEOF + 1);
        dwModelResCount = 0x2A16;//*(DWORD*)(OFFST_MODELRES_COUNT + 1);
        dwModelMobsID = 0x209;//*(DWORD*)(OFFST_MODELRES_MOBS_ID + 2);
 
        // Hook some proc for calc resource id
		HookThis((DWORD)&Hook_LoadPlayerBMD,HPROC_LOADPLAYERBMD);
 
        // Hook zero-bull load
		HookThis((DWORD)&Hook_OpenMonsterModel,HPROC_OPENMONSTERMODEL_BULL);

		//Передаем EAX в функцию в место 0
		*(BYTE*)(0x00501694)	= 0x50;
		*(BYTE*)(0x00501694+1)  = 0x90;

		//Увеличиваем лимит моделек на смерть
		*(BYTE*)(0x004DE4F0+3) = 0x40;
		*(BYTE*)(0x004DE4F0+4) = 0x9C;
 
        // Hook construct zero-bull model
		HookThis((DWORD)&Hook_ConstructMonsterModel,HPROC_CONSTMONSTERMODEL_BULL);
        // Fix load resurce id in OpenMonsterModel() HPROC_LOADBMDMODEL
		HookThis((DWORD)&Hook_FixLoadBMDModel,HPROC_LOADBMDMODEL);
        //Hook set mob name style, for change mob params
		HookThis((DWORD)&Hook_SetMonsterNameStyle,HPROC_SETMOBNAMESTYLE);
}
 
void __cdecl Hook_LoadPlayerBMD(DWORD dwResInx, LPSTR lpDir, LPSTR lpBaseName, DWORD Arg4)
{
// Hook procedure only for calc model resource indexes after heapalloc memory block
        DWORD dwEnd, dwDiff, dwSize;
 
        // calc model resource index
        dwSize = dwModelResSizeof * dwModelResCount;
        dwDiff = *lpModelResArray - *lpModelResBase;
        dwModelResInx = (dwSize - dwDiff) / dwModelResSizeof;

		//Console.ConsoleOutput(GREEN,"dwModelResInx = %d",dwModelResInx);

        // set resource index for new monsters
        for(int i=0;i<ADD_MOBS_COUNT;i++)
		{
                //dwNewMobResInx[i] = dwModelResInx - i - 1;	//DeBug
				dwNewMobResInx[i] = dwModelResInx - i - 1;// - 1;
                s_AddMob[i].dwMobID -= 1;//fix, LoadModel(mob_id) where mob_id = server_mob_id - 1
        }
        //back to load player.bmd
        HLoadBMDModel(dwResInx, lpDir, lpBaseName, Arg4);//original
}
 
void __cdecl Hook_OpenMonsterModel(DWORD dwMobNumber) 
{
	DWORD NewMob = 0;
// Change zero-bull to new mob (if need)
	//Console.ConsoleOutput(YELLOW,"dwMobNumber = %d",dwMobNumber);

    if(dwMobNumber != -1)// if not zero-bull
    {
            for(int i=0;i<ADD_MOBS_COUNT;i++) 
			{
                    if(dwMobNumber == s_AddMob[i].dwMobID) 
					{
                            NewMob = dwNewMobResInx[i] - dwModelMobsID;
                            iTempMobID = i;
                            break;
                    }
					
            }
    }
    HOpenMonsterModel(NewMob);//original
	
  //      if(dwMobNumber != -1)// if not zero-bull
  //      {
  //              for(int i=0;i<ADD_MOBS_COUNT;i++) 
		//		{
  //                      if(dwMobNumber == s_AddMob[i].dwMobID) 
		//				{
  //                              dwMobNumber = dwNewMobResInx[i] - dwModelMobsID;
  //                              iTempMobID = i;
  //                              break;
  //                      }
  //              }
  //      }
  //      else
		//{
  //              dwMobNumber = 0;
		//}
  //      HOpenMonsterModel(dwMobNumber);//original
}

void __cdecl Hook_FixLoadBMDModel(DWORD dwResInx, LPSTR lpDir, LPSTR lpBaseName, DWORD Arg4)
{
// Change load bmd model params (if need)
		if(iTempMobID != NONE)
		{
					 lpDir = s_AddMob[iTempMobID].lpDir;
					 lpBaseName = s_AddMob[iTempMobID].lpFile;
					 Arg4 = -1;
		}

        HLoadBMDModel(dwResInx, lpDir, lpBaseName, Arg4);//original

		//if(iTempMobID != NONE)
		//{
		//	if(s_AddMob[iTempMobID].Type == 2)
		//	{
		//		sub_5D5710(dwResInx, NPC_DIR2, 10497, 9728);
		//	}
		//}
}
 
DWORD __cdecl Hook_ConstructMonsterModel(DWORD Arg1, DWORD dwResInx, DWORD dwResOffst, DWORD Arg4, DWORD Arg5)
{
// Change new resource ID (if need)
        if(iTempMobID != NONE)
		{
			dwResInx = dwNewMobResInx[iTempMobID];
            iTempMobID = NONE;
        }
		return HConstructMonsterModel(Arg1, dwResInx, dwResOffst, Arg4, Arg5);//original
}
 
void __cdecl Hook_SetMonsterNameStyle(DWORD dwMemAddr, DWORD dwMobID, DWORD Arg3, DWORD Arg4)
{
// Hook for change monster parametres
        HSetMonsterNameStyle(dwMemAddr, dwMobID, Arg3, Arg4);//original
        ModifMonsParams(dwMemAddr, dwMobID);
}

void ModifMonsParams(DWORD lpUnit, DWORD dwMobID)
{
        for(int i=0;i<MOBS_PARAMS_COUNT;i++)
        {
                if(s_ParamMob[i].dwMobID==dwMobID)
                {
                        Unit_Struct *pUnit;
                        pUnit = (Unit_Struct*)lpUnit;
 
                        if(s_ParamMob[i].lpName!=NULL)
                                sprintf(pUnit->cName, "%s", s_ParamMob[i].lpName);
                       
                        if(s_ParamMob[i].bMoveOut != NONE)
                                pUnit->bMoveOut = s_ParamMob[i].bMoveOut;
 
                        if(s_ParamMob[i].bMobType!=NONE)
                                pUnit->bMobType = s_ParamMob[i].bMobType;
 
                        if(s_ParamMob[i].fSize!=NULL)
                                pUnit->fSize = s_ParamMob[i].fSize;
 
                        if(s_ParamMob[i].bPKStatus!=NONE)
                                pUnit->bPKStatus = s_ParamMob[i].bPKStatus;
 
                        //Hand first
                        if(s_ParamMob[i].sItem1ResID!=NONE)
                                pUnit->sItem1ResID = s_ParamMob[i].sItem1ResID;
 
                        if(s_ParamMob[i].bItem1IsExcl!=NONE)
                                pUnit->bItem1IsExc = s_ParamMob[i].bItem1IsExcl;
 
                        if(s_ParamMob[i].bItem1JoinID!=NONE)
                                pUnit->bItem1JoinID = s_ParamMob[i].bItem1JoinID;
 
                        //Hand second
                        if(s_ParamMob[i].sItem2ResID!=NONE)
                                pUnit->sItem2ResID = s_ParamMob[i].sItem2ResID;
 
                        if(s_ParamMob[i].bItem2IsExcl!=NONE)
                                pUnit->bItem2IsExc = s_ParamMob[i].bItem2IsExcl;
 
                        if(s_ParamMob[i].bItem2JoinID!=NONE)
                                pUnit->bItem2JoinID = s_ParamMob[i].bItem2JoinID;
                }
        }
}
#endif