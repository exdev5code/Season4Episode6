#ifndef _PRICE_MANAGER_H_
#define _PRICE_MANAGER_H_

#define MAX_PRICE_ITEM 1000
#define PRICEMANAGER_DIR "..\\ExTeam\\PriceManager.ini"

class cPriceManager
{
private:
	int Enable;
	int AllSellNull;

	struct 
	{
		int Type;
		int Index;
		int Level;
		int PriceType;	//1 - Zen, 2 - ExPoint, 3 - WCoin
		int Price;
	}SellPrice[MAX_PRICE_ITEM];
	int sCount;

public:
	void LoadConfig();
	void SellPriceItem(int aIndex,int iPos,int & money);
};
extern cPriceManager PriceManager;
#endif