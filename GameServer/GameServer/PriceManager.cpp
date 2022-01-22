#include "StdAfx.h"
#include "user.h"
#include "PriceManager.h"
#include "Functions.h"
#include "PCPointSystem.h"
#include "DSProtocol.h"

cPriceManager PriceManager;

void cPriceManager::LoadConfig()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,PRICEMANAGER_DIR);
	this->AllSellNull = GetPrivateProfileInt("Common","AllSellNull",0,PRICEMANAGER_DIR);

	for(int i(0);i<MAX_PRICE_ITEM;i++)
	{
		this->SellPrice[i].Type = 0;
		this->SellPrice[i].Index = 0;
		this->SellPrice[i].Level = 0;
		this->SellPrice[i].Price = 0;
	}

	FILE * file = fopen(PRICEMANAGER_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,"ExTeam\\PriceManager.ini Load Error","CRITICAL ERROR",0);
		this->Enable = false;
	}
	if(!this->Enable)return;

	char Buff[256];
	int Flag = 0;
	this->sCount = 0;

	while(!feof(file)) // Проверяем есть ли строка в документе
	{
		fgets(Buff,256,file);//Функция читает текущую строку
		if(Ex_IsBadFileLine(Buff, Flag)) //Вспомогательная функция
			continue;
		if(Flag == 1)
		{
			int n[5];
			sscanf(Buff, "%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
			this->SellPrice[this->sCount].Type = n[0];
			this->SellPrice[this->sCount].Index = n[1];
			this->SellPrice[this->sCount].Level = n[2];
			this->SellPrice[this->sCount].PriceType = n[3];
			this->SellPrice[this->sCount].Price = n[4];
			this->sCount++;
		}
	}
	fclose(file);
}

void cPriceManager::SellPriceItem(int aIndex,int iPos,int & money)
{
	if(!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];
	for(int i=0;i<this->sCount;i++)
	{
		if ( lpObj->pInventory[iPos].m_Type == ITEMGET(this->SellPrice[i].Type,this->SellPrice[i].Index) &&
			 lpObj->pInventory[iPos].m_Level == this->SellPrice[i].Level )
		{
			if(this->SellPrice[i].PriceType == 0)	//Zen
			{
				money = this->SellPrice[i].Price;
				return;
			}
			else if(this->SellPrice[i].PriceType == 1)	//ExPoint
			{
				ExUser[aIndex].PCPoint += this->SellPrice[i].Price;
				ExPCPointSystem.InitPCPointForPlayer(lpObj, ExUser[aIndex].PCPoint,lpObj->ExCred );
				money = 0;
				return;
			}
			else if(this->SellPrice[i].PriceType == 2)	//Wcoin
			{
				GDRequestWcoinInfoLoad (lpObj,this->SellPrice[i].Price,1); //1 = +
				money = 0;
				return;
			}
		}
	}
	if(this->AllSellNull)
	{
		money = 0;
	}
}

