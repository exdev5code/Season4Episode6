#include "StdAfx.h"
#include "user.h"
#include "Experience.h"
#include "Functions.h"

cExperience ExExperience;

void cExperience::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,EXPERIENCE_DIR);
	for(int i(0);i<EXPERIENCE_MAX_RES;i++)
	{
		this->Number[i].Res = 0;
		this->Number[i].Exp = 0;
	}
	FILE * file = fopen(EXPERIENCE_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\Experience.ini Load Error","CRITICAL ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->rCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Number[this->rCount].Res = n[0];
			this->Number[this->rCount].Exp = n[1];
			this->rCount++;
		}
	}
	fclose(file);
}

void cExperience::Main(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->Enable) return;
	int aIndex = lpObj->m_Index;
	__int64 NewExp = Experience;
	for(int i=0;i<this->rCount;i++)
	{
		if(this->Number[i].Res == ExUser[aIndex].Reset)
		{
			NewExp = (( NewExp * this->Number[i].Exp ) / 100 );
			break;
		}
	}
	Experience = NewExp;
}

