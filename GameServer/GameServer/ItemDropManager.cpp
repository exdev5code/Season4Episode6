#include "stdafx.h"
#include "gObjMonster.h"
#include "..\include\ReadScript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.H"
#include "DSProtocol.h"
#include "ItemDropManager.h"
#include "Functions.h"

CItemDropManager gItemDropManager;
/*
CItemDropManager::CItemDropManager(void)
{
	return;
}

CItemDropManager::~CItemDropManager(void)
{
	return;
}
*/
void CItemDropManager::Init()
{
	SMDFile = fopen("..\\ExTeam\\ItemDropManager.ini", "r");

	gItemDropManager.ItemsCount = 0;

	if (SMDFile == NULL)
	{
		MessageBoxA(0,"[ItemDropManager]: Failed to load file ..\\ExTeam\\ItemDropManager.ini","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	int iToken = 0;

	while (true)
	{
		iToken = GetToken();

		if (iToken == END)
		{
			break;
		}

		if (iToken == NUMBER)
		{
			gItemDropManager.ItemType[gItemDropManager.ItemsCount] = (char)TokenNumber;
			
			iToken = GetToken();
			gItemDropManager.ItemIndex[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemLevel[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemDur[gItemDropManager.ItemsCount] = (unsigned char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemLuck[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemSkill[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemOption[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemExe[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.ItemAncient[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.DropMap[gItemDropManager.ItemsCount] = (char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.MobMinLvl[gItemDropManager.ItemsCount] = (unsigned char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.MobMaxLvl[gItemDropManager.ItemsCount] = (unsigned char)TokenNumber;

			iToken = GetToken();
			gItemDropManager.DropRate[gItemDropManager.ItemsCount] = (short)TokenNumber;

			gItemDropManager.ItemsCount++;
		}
	}

	fclose(SMDFile);
	//LogAdd("[ItemDropManager]: Successfuly read file %s", "..\\ExTeam\\ItemDropManager.ini");

	return;
}

bool CItemDropManager::ProccessItemDrop(LPOBJ lpMobObj)
{
	unsigned char Map = lpMobObj->MapNumber;
	unsigned char X = lpMobObj->X;
	unsigned char Y = lpMobObj->Y;
	int Type = 0;
	char Level = 0;
	unsigned char Dur = 0;
	char Luck = 0;
	char Skill = 0;
	char Opt = 0;
	char Exe = 0;
	char Anc = 0;

	if ( gItemDropManager.ItemsCount > 0 )
	{
		int iTopHitUser = gObjMonsterTopHitDamageUser(lpMobObj);

		for (int i=0;i<gItemDropManager.ItemsCount;++i)
		{
			if ( lpMobObj->MapNumber == gItemDropManager.DropMap[i] || gItemDropManager.DropMap[i] == -1 )
			{
				if ( lpMobObj->Level >= gItemDropManager.MobMinLvl[i] && lpMobObj->Level <= gItemDropManager.MobMaxLvl[i] )
				{
					if ( (rand()%10000) < gItemDropManager.DropRate[i] )
					{
						Type = ItemGetNumberMake(gItemDropManager.ItemType[i],gItemDropManager.ItemIndex[i]);

						Level = gItemDropManager.ItemLevel[i];
						Dur = gItemDropManager.ItemDur[i];
						Luck = gItemDropManager.ItemLuck[i];
						Skill = gItemDropManager.ItemSkill[i];
						Opt = gItemDropManager.ItemOption[i];
						if ( gItemDropManager.ItemExe[i] > 0 )
						{
							//Exe = GetRandomExeOption(gItemDropManager.ItemExe[i]+1);
							Exe = GenExcOpt(gItemDropManager.ItemExe[i]);
						}
						if ( gItemDropManager.ItemAncient[i] == 5 || gItemDropManager.ItemAncient[i] == 10 )
						{
							Anc = gItemDropManager.ItemAncient[i];
						}
						ItemSerialCreateSend(lpMobObj->m_Index,(BYTE)Map,(BYTE)X,(BYTE)Y,Type,(BYTE)Level,(BYTE)Dur,(BYTE)Skill,(BYTE)Luck,(BYTE)Opt,iTopHitUser,(BYTE)Exe,(BYTE)Anc);
						return true;
					}
				}
			}
		}
	}
	return false;
}