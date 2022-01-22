#include "StdAfx.h"
#include "user.h"
#include "MapClass.h"
#include "DropZenManager.h"
#include "Functions.h"

cDropZenManager DropZenManager;

void cDropZenManager::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,DROPZEN_DIR);

	for(int i(0);i<MAX_NUMBER_MAP;i++)
	{
		this->Number[i].Map = 0;
		this->Number[i].Zen = 0;
	}
	FILE * file = fopen(DROPZEN_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\DropZenManager.ini Load Error","CRITICAL ERROR",0);
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
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->Number[this->mCount].Map = n[0];
			this->Number[this->mCount].Zen = n[1];
			this->mCount++;
		}
	}
	fclose(file);
}

void cDropZenManager::Main (LPOBJ lpObj, float & money)
{
	if(!this->Enable) return;
	for(int i=0;i<this->mCount;i++)
	{
		if(this->Number[i].Map == lpObj->MapNumber)
		{
			money = (( money * this->Number[i].Zen ) / 100 );
			return;
		}
	}
}