#pragma once

#include "StdAfx.h"

#if(_CREDIT_DONATE_)

#define CR_DONATE_DIR	"..\\ExTeam\\CreditDonate.ini"

#define MAX_DONATE_ITEM 1000

struct DONATE_ITEM
{
	char cmd[50];
	int Type;
	int Index;
	int Level;
	int Skill;
	int Luck;
	int Opt;
	int Exl;
	int Anc;
	int CrPrice;
};

class cCreditDonate
{
public:
	void Load();
	void Chat(int aIndex, LPBYTE Protocol);
	void Sell(int aIndex, int Pos, int &iAddZen);

private:
	bool Enable;
	int SellProcent;

	DONATE_ITEM Donate[MAX_DONATE_ITEM];

	int Count;

};
extern cCreditDonate gCreditDonate;

#endif