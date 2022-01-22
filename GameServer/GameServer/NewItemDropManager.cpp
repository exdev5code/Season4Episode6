#include "stdafx.h"
#include "gObjMonster.h"
#include "..\include\ReadScript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.H"
#include "DSProtocol.h"
#include "NewItemDropManager.h"
#include "Functions.h"

#if(NEW_ITEM_DROP)

NewCItemDropManager NewgItemDropManager;

void NewCItemDropManager::Init()
{
	for(int i = 0; i > OBJMAX; i++)
	{
		this->iUser[i]	= false;
	}


	FILE *file = fopen(ITEM_DROP_DIR,"r");

	if (file == NULL)
	{
		MessageBoxA(0,ITEM_DROP_DIR,"CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	this->DropCount = 0;
	this->BlockCount = 0;

	char Buff[256];
	int Flag = 0;
	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int n[19];
			sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0],&n[1],&n[2],&n[3],&n[4],&n[5],&n[6],&n[7],&n[8],&n[9],&n[10],&n[11],&n[12],&n[13],&n[14],&n[15],&n[16],&n[17],&n[18]);
			this->Drop[this->DropCount].Type			= n[0];
			this->Drop[this->DropCount].Index			= n[1];
			this->Drop[this->DropCount].MinLevel		= n[2];
			this->Drop[this->DropCount].MaxLevel		= n[3];
			this->Drop[this->DropCount].Dur				= n[4];
			this->Drop[this->DropCount].OptionRate		= n[5];
			this->Drop[this->DropCount].MaxOption		= n[6];
			this->Drop[this->DropCount].LuckRate		= n[7];
			this->Drop[this->DropCount].LuckOption		= n[8];
			this->Drop[this->DropCount].SkillRate		= n[9];
			this->Drop[this->DropCount].SkillOption		= n[10];
			this->Drop[this->DropCount].ExlRate			= n[11];
			this->Drop[this->DropCount].ExlOption		= n[12];
			this->Drop[this->DropCount].AncRate			= n[13];
			this->Drop[this->DropCount].AncOption		= n[14];
			this->Drop[this->DropCount].MonsterMinLevel = n[15];
			this->Drop[this->DropCount].MonsterMaxLevel = n[16];
			this->Drop[this->DropCount].MonsterMap		= n[17];
			this->Drop[this->DropCount].ItemDropRate	= n[18];
			this->DropCount++;
		}

		if(Flag == 2)
		{
			int n[2];
			sscanf(Buff,"%d %d", &n[0],&n[1]);
			this->Block[this->BlockCount].Type	= n[0];
			this->Block[this->BlockCount].Index = n[1];
			this->BlockCount++;
		}
	}
	fclose(file);
}

bool NewCItemDropManager::ProccessItemDrop(LPOBJ lpMobObj, LPOBJ lpTargetObj)
{
	for (int i=0; i < this->DropCount; i++)
	{
		if ( lpMobObj->MapNumber == this->Drop[i].MonsterMap || this->Drop[i].MonsterMap == -1 )
		{
			if ( lpMobObj->Level >= this->Drop[i].MonsterMinLevel && lpMobObj->Level <= this->Drop[i].MonsterMaxLevel )
			{
				if ( (rand()%10000) < this->Drop[i].ItemDropRate )
				{
					int iLevel	= 0;
					int iOption	= 0;
					int iLuck	= 0;
					int iSkill	= 0;
					int iExlOpt	= 0;
					int iAncOpt	= 0;
					
					if( this->Drop[i].MaxLevel == this->Drop[i].MinLevel )
					{
						iLevel = this->Drop[i].MinLevel;
					}
					else
					{
						iLevel = this->Drop[i].MinLevel + (rand() % (this->Drop[i].MaxLevel - this->Drop[i].MinLevel + 1));
					}	

					if( this->Drop[i].MaxOption != 0 )
					{
						if( rand() % 100 < this->Drop[i].OptionRate )
						{
							iOption = rand() % this->Drop[i].MaxOption + 1;
						}
					}

					if( this->Drop[i].LuckOption == 1 )
					{
						if( rand() % 100 < this->Drop[i].LuckRate )
						{
							iLuck = 1;
						}
					}

					if( this->Drop[i].SkillOption == 1 )
					{
						if( rand() % 100 < this->Drop[i].SkillRate )
						{
							iLuck = 1;
						}
					}

					if(this->Drop[i].ExlOption)
					{
						if( rand() % 100 < this->Drop[i].ExlRate )
						{
							iExlOpt = GenExcOpt(this->Drop[i].ExlOption);
						}
					}

					if(this->Drop[i].AncOption == 5 || this->Drop[i].AncOption == 10)
					{
						if( rand() % 100 < this->Drop[i].AncRate )
						{
							iAncOpt = this->Drop[i].AncOption;
						}
					}

					this->iUser[lpMobObj->m_Index] = true;

					ItemSerialCreateSend(lpMobObj->m_Index,lpMobObj->MapNumber,lpMobObj->X,lpMobObj->Y,ITEMGET(this->Drop[i].Type,this->Drop[i].Index),iLevel,this->Drop[i].Dur,iSkill,iLuck,iOption,gObjMonsterTopHitDamageUser(lpMobObj),iExlOpt,iAncOpt);
					return true;
				}
			}
		}
	}
	return false;
}

bool NewCItemDropManager::BlockItemDrop(int aIndex, int ItemID, int MapNumber)
{
	if( MapNumber >= 0 && MapNumber <= MAX_NUMBER_MAP )
	{
		if(this->iUser[aIndex] == true)
		{
			this->iUser[aIndex] = false;
			for(int i = 0; i< this->DropCount; i++)
			{
				if(ItemID == ITEMGET(this->Drop[i].Type,this->Drop[i].Index) )
				{
					return true;
				}
			}
		}

		for(int i = 0; i< this->BlockCount; i++)
		{
			if(ItemID == ITEMGET(this->Block[i].Type,this->Block[i].Index))
			{
				LogAddTD("[DropBlock] Item %d has been blocked", ItemID);
				return false;
			}
		}
	}

	return true;
}

#endif