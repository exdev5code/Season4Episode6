#pragma once
#include "StdAfx.h"

#include "Protocol.h"

#define	pViewAttackTargetID		*(DWORD*)0x8C43A0
#define CheckBattleCursor        ((bool(__cdecl*)()) 0x517790)


struct ExViewePort
{
	PBMSG_HEAD2 h;
	short aIndex;
	int Life;
	int MaxLife;
	int SD;
	int MaxSD;
	int Level;
	int Reset;
	int GrandReset;
	int Defence;
	char Name[20];
	BYTE Live;
};


class User
{
public:
	User();

	void		Refresh();

	int			VieweTargetID;
	bool		BattleCursor;


	ExViewePort	ExViewe[MAX_VIEWPORT];


	int Premium;

	int ChaosBank;
	int BlessBank;
	int SoulBank;
	int LifeBank;
	float ExCred;


};
extern User gObjUser;