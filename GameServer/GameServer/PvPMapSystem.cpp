#include "StdAfx.h"
#include "user.h"
#include "Functions.h"
#include "MapClass.h"
#include "PvPMapSystem.h"

cPvPMapSystem PvPMapSystem;

void cPvPMapSystem::LoadConfig()
{
	this->EnablePvPMap = GetPrivateProfileInt("Common","EnablePvPMap",0,PVPMAPSYSTEM_DIR);
	this->EnableLoraRing = GetPrivateProfileInt("Common","EnableLoraRing",0,PVPMAPSYSTEM_DIR);

	for(int i(0);i<MAX_NUMBER_MAP;i++)
	{
		this->PvP[i].Map = 0;
		this->PvP[i].Status = 0;
	}

	FILE * file = fopen(PVPMAPSYSTEM_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\PvPSystem.ini Load Error","CRITICAL ERROR",0);
		this->EnablePvPMap = false;
	}
	if(!this->EnablePvPMap)return;

	char Buff[256];
	int Flag = 0;
	this->pCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[3];
			sscanf(Buff, "%d %d", &n[0], &n[1]);
			this->PvP[this->pCount].Map = n[0];
			this->PvP[this->pCount].Status = n[1];
			this->pCount++;
		}
	}
	fclose(file);
}
//0 - Нормально, 1 - можно убивать и не фонишся, 2 - нельзя атаковать цель
bool cPvPMapSystem::CheckAttackMap(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->EnablePvPMap) return true;
	if(lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		for(int i=0;i<this->pCount;i++)
		{
			if(this->PvP[i].Map == lpObj->MapNumber && this->PvP[i].Status == 2) return false;
		}
	}
	return true;
}

bool cPvPMapSystem::CheckPkMap(LPOBJ lpObj, LPOBJ lpTargetObj)
{
	if(!this->EnablePvPMap) return true;
	if(lpObj->Type == OBJ_USER && lpTargetObj->Type == OBJ_USER)
	{
		if(this->EnableLoraRing)
		{
			if(lpObj->MapNumber==0 && lpObj->X >= 137 && lpObj->X <= 144 && lpObj->Y >= 124 && lpObj->Y <= 131) return false;
		}
		for(int i=0;i<this->pCount;i++)
		{
			if(this->PvP[i].Map == lpObj->MapNumber && this->PvP[i].Status == 1) return false;
		}
	}
	return true;
}