#include "StdAfx.h"
#include "MapExp.h"
#include "MapClass.h"
#include "Functions.h"

cMapExp gMapExp;

void cMapExp::Init()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,MAPEXP_DIR);
	for(int i(0);i<MAX_NUMBER_MAP;i++)
	{
		this->Number[i].Map = 0;
		this->Number[i].Exp = 0;
	}
	FILE * file = fopen(MAPEXP_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\MapExp.ini Load Error","CRITICAL ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->mCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[2];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Number[this->mCount].Map = n[0];
			this->Number[this->mCount].Exp = n[1];
			this->mCount++;
		}
	}
	fclose(file);
}

void cMapExp::Main(LPOBJ lpObj, __int64 & Experience)
{
	if(!this->Enable) return;

	for(int i=0;i<this->mCount;i++)
	{
		if(this->Number[i].Map == lpObj->MapNumber)
		{
			Experience = (( Experience * this->Number[i].Exp ) / 100 );
			break;
		}
	}
}