#ifndef GOLDENARCHER_H
#define GOLDENARCHER_H

#include "User.h"


class cGoldenArcher
{
public:
	void Start();
	void Load();
	void ClickArcher(int PlayerID);
	int Ex_RenaCount;
	struct 
	{
		short Index;
		short ItemID;
		short Level;
		short Skill;
		short Luck;
		short Options;
		short Exl;
		short Anc;
	}Items[100];

	int ArcherItemsCount;
};
extern cGoldenArcher GoldenArcher;

#endif GOLDENARCHER_H