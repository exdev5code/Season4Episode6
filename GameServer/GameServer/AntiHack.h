#include "StdAfx.h"
#if _ANTIHACK_
#include "user.h"

#define MAXMOVE 20

class cAntiHack
{
	public:
	cAntiHack::cAntiHack();
	cAntiHack::~cAntiHack();
	bool SHOW[OBJMAX];
	int USER[OBJMAX];
	short X[OBJMAX];
	short Y[OBJMAX];

	void Start(int aIndex);
	void MoveProc(PMSG_MOVE *Data,int  aIndex);
};
extern cAntiHack gAntiHack;

#endif