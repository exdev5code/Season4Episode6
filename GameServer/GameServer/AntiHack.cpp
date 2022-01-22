#include "StdAfx.h"
#if _ANTIHACK_
#include "AntiHack.h"
#include "user.h"
#include "logproc.h"
#include "Message.h"
#include "ConnectEx.h"

cAntiHack gAntiHack;

cAntiHack::cAntiHack()
{
	for(int i=0;i<OBJMAX;i++)
	{
		this->SHOW[i] = true;
		this->USER[i] = 0;
	}
}

cAntiHack::~cAntiHack()
{

}

void cAntiHack::Start(int aIndex)
{
	this->SHOW[aIndex] = true;
	this->USER[aIndex] = 0;
}

void cAntiHack::MoveProc(PMSG_MOVE *Data,int  aIndex)
{
	int TickTime = time(NULL);

	if(this->SHOW[aIndex] == true)
	{
		this->X[aIndex] = Data->X;
		this->Y[aIndex] = Data->Y;
		this->SHOW[aIndex] = false;
	}

	if( TickTime >= this->USER[aIndex]+5 )
	{
		this->USER[aIndex] = TickTime;
		int iX = Data->X - this->X[aIndex];
		int iY = Data->Y - this->Y[aIndex];

		if(iX < -MAXMOVE || iX > MAXMOVE || iY < -MAXMOVE || iY > MAXMOVE)
		{
			LPOBJ lpObj = &gObj[aIndex];
			LogAddC(2,"[AntiHack] Move Hack Accaunt: %s, NickName: %s",lpObj->AccountID,lpObj->Name);
#ifdef _RECONNECT_
			g_ConnectEx.SendClose(aIndex,0);
#else
		CloseClient(aIndex);
#endif
			return;
		}
		this->SHOW[aIndex] = true;		
	}
}

#endif