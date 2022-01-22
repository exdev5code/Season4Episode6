#include "StdAfx.h"
#include "BMQuest.h"
#include "Message.h"
#include "user.h"
#include "Functions.h"

#if(BM_QUEST_SYSTEM_)

cBMQuest BMQuest;

void cBMQuest::StartConfig()
{
	Enable = GetPrivateProfileInt("Common","Enable",0,_DIR_BMQUEST);
	NPC = GetPrivateProfileInt("Common","NPC",0,_DIR_BMQUEST);
	NPC_Map = GetPrivateProfileInt("Common","NPC_Map",0,_DIR_BMQUEST);
	NPC_X = GetPrivateProfileInt("Common","NPC_X",0,_DIR_BMQUEST);
	NPC_Y = GetPrivateProfileInt("Common","NPC_Y",0,_DIR_BMQUEST);

	Reset = GetPrivateProfileInt("Common","Reset",0,_DIR_BMQUEST);

	for (int i(0);i<_MAX_CLASS_BMQUEST;i++)
	{
		for(int j(0);j<_MAX_BMQUEST;j++)
		{
			Quest[i][j].Mob = 0;
			Quest[i][j].Coun = 0;
			Quest[i][j].proc = 0;
			Quest[i][j].rew = 0;
			Quest[i][j].gift = 0;
			Quest[i][j].msg[0] = NULL;
			Quest[i][j].msg2[0] = NULL;
		}
	}
}

void cBMQuest::StartUP()
{
	StartConfig();
	if(!Enable)
	{
		return;
	}

	FILE *file;
	file = fopen(_DIR_BMQUEST,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"Exeam\\BMQuest.ini Load Error","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}
	char Buff[256];
	int Flag = 0;
	Count[1] = 0;
	Count[2] = 0;
	Count[3] = 0;
	Count[4] = 0;
	Count[5] = 0;
	Count[6] = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[1][Count[1]].Mob  = n[0];
			Quest[1][Count[1]].Coun = n[1];
			Quest[1][Count[1]].proc = n[2];
			Quest[1][Count[1]].rew  = n[3];
			Quest[1][Count[1]].gift = n[4];
			sprintf(Quest[1][Count[1]].msg,"%s",mes);
			sprintf(Quest[1][Count[1]].msg2,"%s",mes2);
			Count[1]++;
		}
		if(Flag == 2)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[2][Count[2]].Mob  = n[0];
			Quest[2][Count[2]].Coun = n[1];
			Quest[2][Count[2]].proc = n[2];
			Quest[2][Count[2]].rew  = n[3];
			Quest[2][Count[2]].gift = n[4];
			sprintf(Quest[2][Count[2]].msg,"%s",mes);
			sprintf(Quest[2][Count[2]].msg2,"%s",mes2);
			Count[2]++;
		}
		if(Flag == 3)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[3][Count[3]].Mob  = n[0];
			Quest[3][Count[3]].Coun = n[1];
			Quest[3][Count[3]].proc = n[2];
			Quest[3][Count[3]].rew  = n[3];
			Quest[3][Count[3]].gift = n[4];
			sprintf(Quest[3][Count[3]].msg,"%s",mes);
			sprintf(Quest[3][Count[3]].msg2,"%s",mes2);
			Count[3]++;
		}
		if(Flag == 4)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[4][Count[4]].Mob  = n[0];
			Quest[4][Count[4]].Coun = n[1];
			Quest[4][Count[4]].proc = n[2];
			Quest[4][Count[4]].rew  = n[3];
			Quest[4][Count[4]].gift = n[4];
			sprintf(Quest[4][Count[4]].msg,"%s",mes);
			sprintf(Quest[4][Count[4]].msg2,"%s",mes2);
			Count[4]++;
		}
		if(Flag == 5)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[5][Count[5]].Mob  = n[0];
			Quest[5][Count[5]].Coun = n[1];
			Quest[5][Count[5]].proc = n[2];
			Quest[5][Count[5]].rew  = n[3];
			Quest[5][Count[5]].gift = n[4];
			sprintf(Quest[5][Count[5]].msg,"%s",mes);
			sprintf(Quest[5][Count[5]].msg2,"%s",mes2);
			Count[5]++;
		}
		if(Flag == 6)
		{
			int n[10];
			char mes[100];
			char mes2[100];
			//gets(mes);
			sscanf(Buff,"%d %d %d %d %d \"%[^\"]\" \"%[^\"]\"",&n[0],&n[1],&n[2],&n[3],&n[4],&mes,&mes2);
			Quest[6][Count[6]].Mob  = n[0];
			Quest[6][Count[6]].Coun = n[1];
			Quest[6][Count[6]].proc = n[2];
			Quest[6][Count[6]].rew  = n[3];
			Quest[6][Count[6]].gift = n[4];
			sprintf(Quest[6][Count[6]].msg,"%s",mes);
			sprintf(Quest[6][Count[6]].msg2,"%s",mes2);
			Count[6]++;
		}
	}
	fclose(file);
}

void cBMQuest::AddedCharacter(int aIndex)
{
	if(!Enable)
		return;	
	
	LPOBJ lpObj = &gObj[aIndex];

	lpObj->DamageReflect += ExUser[aIndex].BMDamageReflect;

	lpObj->m_AttackDamageMaxLeft += ExUser[aIndex].BMDamage;
	lpObj->m_AttackDamageMinLeft += ExUser[aIndex].BMDamage;
	lpObj->m_AttackDamageMaxRight += ExUser[aIndex].BMDamage;
	lpObj->m_AttackDamageMinRight += ExUser[aIndex].BMDamage;

	lpObj->m_MagicDamageMin += ExUser[aIndex].BMDamage;
	lpObj->m_MagicDamageMax += ExUser[aIndex].BMDamage;

	lpObj->m_Defense += ExUser[aIndex].BMDefense;
	lpObj->m_MagicDefense += ExUser[aIndex].BMDefense;

	lpObj->m_CriticalDamage += ExUser[aIndex].BMCriticalDamage;
	lpObj->m_ExcelentDamage += ExUser[aIndex].BMExcelentDamage;
}

void cBMQuest::CharacterInformation(int aIndex)
{
	if(!Enable)
		return;
	LPOBJ lpObj = &gObj[aIndex];
	//Log.BMQuestLogs("[%s] BMInfo Start",gObj->Name);
	MessageChat(aIndex,"@[BMInfo] +%d Reflect",ExUser[aIndex].BMDamageReflect);
	MessageChat(aIndex,"@[BMInfo] +%d Damage",ExUser[aIndex].BMDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Defense",ExUser[aIndex].BMDefense);
	MessageChat(aIndex,"@[BMInfo] +%d CritDamage",ExUser[aIndex].BMCriticalDamage);
	MessageChat(aIndex,"@[BMInfo] +%d ExcDamage",ExUser[aIndex].BMExcelentDamage);
	MessageChat(aIndex,"@[BMInfo] +%d Life",ExUser[aIndex].BMLife);
}

void cBMQuest::NPCClick(int aIndex,int aNPC)
{
	if(!Enable)
		return;
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNPC];
	if ((lpNpc->Class == NPC) && (lpNpc->MapNumber == NPC_Map) && (lpNpc->X == NPC_X) && (lpNpc->Y == NPC_Y))
	{
		//Log.BMQuestLogs("[%s] NPCdialogue",gObj->Name);
		NPCdialogue(aIndex,aNPC);
	}
}

void cBMQuest::NPCdialogue(int aIndex,int aNPC)
{
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpNpc = &gObj[aNPC];

	if(ExUser[aIndex].Reset < Reset)
	{
		char Buffs[100];
		sprintf(Buffs,"Mission is available with %d reset",Reset);
		ChatTargetSend(lpNpc,Buffs,aIndex);
		return;
	}

	int QClass = lpObj->Class+1;
	//Проверяем не закончен ли квест
	if(ExUser[aIndex].BMQuest_num < Count[QClass])
	{
		//Проверяем начат ли уже квест
		if(ExUser[aIndex].BMQuest_start == 0)
		{
			ChatTargetSend(lpNpc,"Good luck!",aIndex);
			ExUser[aIndex].BMQuest_start = 1;
			////MySQL.Execute("UPDATE Character SET BMQuest_start = 1 WHERE Name='%s'",gObj->Name);
			MessageChat(aIndex,"@[BMQuest] Mission: %d",ExUser[aIndex].BMQuest_num+1);
			MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][ExUser[aIndex].BMQuest_num].msg);
			MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
				Quest[QClass][ExUser[aIndex].BMQuest_num].msg2,
				ExUser[aIndex].BMQuest_kill,
				Quest[QClass][ExUser[aIndex].BMQuest_num].Coun);
		}
		//Если квест уже взят
		else if(ExUser[aIndex].BMQuest_start == 1)
		{
			//Если квест выполнен
			if(ExUser[aIndex].BMQuest_kill >= Quest[QClass][ExUser[aIndex].BMQuest_num].Coun)
			{
				Presents(aIndex,
					Quest[QClass][ExUser[aIndex].BMQuest_num].rew,
					Quest[QClass][ExUser[aIndex].BMQuest_num].gift); //Функция вознаграждения

				ExUser[aIndex].BMQuest_start = 0;
				ExUser[aIndex].BMQuest_num++;
				ExUser[aIndex].BMQuest_kill = 0;
				ChatTargetSend(lpNpc,"You completed the mission!",aIndex);
				//MySQL.Execute("UPDATE Character SET BMQuest_start = 0 WHERE Name='%s'",gObj->Name);
				//MySQL.Execute("UPDATE Character SET BMQuest_num = BMQuest_num + 1 WHERE Name='%s'",gObj->Name);
				////MySQL.Execute("UPDATE Character SET BMQuest_kill = 0 WHERE Name='%s'",gObj->Name);
				if(ExUser[aIndex].BMQuest_num == Count[QClass])
				{
					MessageChat(aIndex,"@[BMQuest] Finish");
				}
			}
			//Если квест не выполнен
			else
			{
				ChatTargetSend(lpNpc,"Your Mission is not finished!",aIndex);
				MessageChat(aIndex,"@[BMQuest] Mission: %d",ExUser[aIndex].BMQuest_num+1);
				MessageChat(aIndex,"@[BMQuest] %s",Quest[QClass][ExUser[aIndex].BMQuest_num].msg);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][ExUser[aIndex].BMQuest_num].msg2,
					ExUser[aIndex].BMQuest_kill,
					Quest[QClass][ExUser[aIndex].BMQuest_num].Coun);
			}
		}
	}
	else
	{
		ChatTargetSend(lpNpc,"You have completed all the Mission!",aIndex);
		MessageChat(aIndex,"@[BMQuest] Finish");
	}
}

void cBMQuest::MonsterKill(int aIndex, int mIndex)
{
	if(!Enable)
		return;
	
	LPOBJ lpObj = &gObj[aIndex];
	LPOBJ lpMob = &gObj[mIndex];

	int QClass = lpObj->Class+1;

	if(ExUser[aIndex].BMQuest_start == 1 && lpMob->Class == Quest[QClass][ExUser[aIndex].BMQuest_num].Mob)
	{
		int iRate = rand()%100+1;

		if(Quest[QClass][ExUser[aIndex].BMQuest_num].proc >= iRate)
		{			

			if(ExUser[aIndex].BMQuest_kill < Quest[QClass][ExUser[aIndex].BMQuest_num].Coun)
			{
				//Log.BMQuestLogs("[%s] MonsterKill",lpObj->Name);
				ExUser[aIndex].BMQuest_kill++;
				////MySQL.Execute("UPDATE Character SET BMQuest_kill = BMQuest_kill + 1 WHERE Name='%s'",gObj->Name);
				MessageChat(aIndex,"@[BMQuest] %s [%d/%d]",
					Quest[QClass][ExUser[aIndex].BMQuest_num].msg2,
					ExUser[aIndex].BMQuest_kill,
					Quest[QClass][ExUser[aIndex].BMQuest_num].Coun);
			
				if(ExUser[aIndex].BMQuest_kill == Quest[QClass][ExUser[aIndex].BMQuest_num].Coun)
				{
					MessageChat(aIndex,"@[BMQuest] Mission accomplished!");
				}
			}
		}
	}
}

void cBMQuest::Presents(int aIndex, int Present, int Gifts)
{
	LPOBJ lpObj = &gObj[aIndex];
	//Log.BMQuestLogs("[%s] Presents %d Gifts %d",gObj->Name,Present,Gifts);
	/*
		1 - BMDamageReflect;
		2 - BMDamage;
		3 - BMDefense;
		4 - BMCriticalDamage;
		5 - BMExcelentDamage;
		6 - BMLife;
	*/
	if(Present == 1)		//BMDamageReflect
	{
		ExUser[aIndex].BMDamageReflect += Gifts;
		//MySQL.Execute("UPDATE Character SET BMDamageReflect = BMDamageReflect + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] DamageReflect: +%d",Gifts);
	}
	else if(Present == 2)	//BMDamage
	{
		ExUser[aIndex].BMDamage += Gifts;
		//MySQL.Execute("UPDATE Character SET BMDamage = BMDamage + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Damage: +%d",Gifts);
	}
	else if(Present == 3)	//BMDefense
	{
		ExUser[aIndex].BMDefense += Gifts;
		//MySQL.Execute("UPDATE Character SET BMDefense = BMDefense + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Defense: +%d",Gifts);
	}
	else if(Present == 4)	//BMCriticalDamage
	{
		ExUser[aIndex].BMCriticalDamage += Gifts;
		//MySQL.Execute("UPDATE Character SET BMCriticalDamage = BMCriticalDamage + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] CriticalDamage: +%d",Gifts);
	}
	else if(Present == 5)	//BMExcelentDamage
	{
		ExUser[aIndex].BMExcelentDamage += Gifts;
		//MySQL.Execute("UPDATE Character SET BMExcelentDamage = BMExcelentDamage + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] ExcelentDamage: +%d",Gifts);
	}
	else if(Present == 6)	//BMLife
	{
		ExUser[aIndex].BMLife += Gifts;
		//MySQL.Execute("UPDATE Character SET BMLife = BMLife + %d WHERE Name='%s'",Gifts,gObj->Name);
		MessageChat(aIndex,"@[BMQuest] Life: +%d",Gifts);
	}
	//LevelUpEffect (aIndex,1);
	ExFireCracker(aIndex, lpObj->X, lpObj->Y);
}

#endif