#include "StdAfx.h"

#ifdef _HAPPY_HOUR_EVENT_

#include "USER.h"
#include "HappyHour.h"
#include "Functions.h"
#include "Message.h"

cHappyHour HappyHour;

void cHappyHour::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",1,HH_DIR);
	this->PlusExp = GetPrivateProfileInt("Common","PlusExp",10,HH_DIR);
	this->PlusDrop = GetPrivateProfileInt("Common","PlusDrop",10,HH_DIR);

	this->LoadFile();

	this->StartHappyHour = false;
}

void cHappyHour::LoadFile()
{
	FILE * file = fopen(HH_DIR,"r");

	if(file == NULL)
	{
		MessageBoxA(0,HH_DIR,"LOAD ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;
	this->Count = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			this->HappyStruct[this->Count].Hour		= 0;
			this->HappyStruct[this->Count].Min		= 0;
			this->HappyStruct[this->Count].EndHour	= 0;
			this->HappyStruct[this->Count].EndMin	= 0;

			int n[4];
			sscanf(Buff, "%d %d %d %d", &n[0], &n[1], &n[2], &n[3]);
			this->HappyStruct[this->Count].Hour		= n[0];
			this->HappyStruct[this->Count].Min		= n[1];
			this->HappyStruct[this->Count].EndHour	= n[2];
			this->HappyStruct[this->Count].EndMin	= n[3];
			this->Count++;
		}
	}
	fclose(file);
}

void cHappyHour::Timetick()
{
	if(!this->Enable)return;
	SYSTEMTIME time;
	GetLocalTime(&time);
	if(time.wSecond == 00)
	{
		for(int i = 0; i < this->Count; i++)
		{
			if(HappyStruct[i].Hour == time.wHour && HappyStruct[i].Min == time.wMinute)
			{
				this->StartHappyHour = true;
				MessaageAllGlobal("[Happy Hour] Event Started!");
				MessaageAllGlobal("[Happy Hour] Exp: +%d%%%% Drop: +%d%%%%%",PlusExp,PlusDrop);
				break;
			}
			if(HappyStruct[i].EndHour == time.wHour && HappyStruct[i].EndMin == time.wMinute)
			{
				MessaageAllGlobal("[Happy Hour] Event Close!");
				this->StartHappyHour = false;
				break;
			}
		}
	}
}

void cHappyHour::UserBonusExp(__int64 & Experience)
{
	if(!this->Enable || !this->StartHappyHour) return;

	Experience += ( Experience * this->PlusExp ) / 100;
}

void cHappyHour::UserBonusZen(float & money)
{
	if(!this->Enable || !this->StartHappyHour) return;

	money += ( money * this->PlusDrop ) / 100;
}

#endif