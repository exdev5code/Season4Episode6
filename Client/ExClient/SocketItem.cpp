#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_
#include "Utilits.h"
#include "ToolKit.h"
#include "SocketItem.h"
#include "Items.h"

signed int __stdcall sub_4C2CEA(signed int a1)
{
	switch(a1)
	{
		case ITEMGET(0,40):
		case ITEMGET(0,41):
		case ITEMGET(2,20):
		case ITEMGET(4,30):
		case ITEMGET(5,40):
		case ITEMGET(5,41):
		case ITEMGET(6,30):
		case ITEMGET(6,31):
		case ITEMGET(6,32):
		case ITEMGET(6,33):
			return 1;
	}

	if( a1 >= ITEMGET(7,60) && a1 <= ITEMGET(7,65) ||
		a1 >= ITEMGET(8,60) && a1 <= ITEMGET(8,65) ||
		a1 >= ITEMGET(9,60) && a1 <= ITEMGET(9,65) ||
		a1 >= ITEMGET(10,60) && a1 <= ITEMGET(10,65) ||
		a1 >= ITEMGET(11,60) && a1 <= ITEMGET(11,65) )
	{
		return 1;
	}
	else
	{
		SocketItemOriginal(a1);
	}
}

void InitSocketItem()
{
	HookThis((DWORD)&sub_4C2CEA,0x004C2CBD);
	HookThis((DWORD)&sub_4C2CEA,0x004C2CDF);
}

#endif