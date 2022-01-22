#include "StdAfx.h"
#ifdef _GRAND_SYSTEM_
#include "Glow.h"
#include "Utilits.h"
#include "ToolKit.h"
#include "Console.h"
#include "Items.h"
#include "LoadGlow.h"

void __cdecl Glow(DWORD dwItemId, DWORD uk1, DWORD uk2, FRGB& cl, BYTE bUkn)
{

	bool OldGlow = true;

    switch(dwItemId)
    {
		//Grand Master
        case ITEM(5,40): cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; OldGlow = false; break;
		case ITEM(6,33): cl.r = 0.70; cl.g = 0.70f; cl.b = 0.70f; OldGlow = false; break;
		case ITEM(7,61):
		case ITEM(8,61):
		case ITEM(9,61):
		case ITEM(10,61):
		//cl.r = 0.60f; cl.g = 0.30f; cl.b = 1.00f; -color mg
		case ITEM(11,61):/*cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; break;*/cl.r = 0.20f; cl.g = 0.45f; cl.b = 1.00f; OldGlow = false; break;
		//Blade Master
		case ITEM(0,40): cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f; OldGlow = false; break;
		case ITEM(6,32): cl.r = 0.30f; cl.g = 1.00f; cl.b = 1.00f; OldGlow = false; break;
		case ITEM(7,60):
		case ITEM(8,60):
		case ITEM(9,60):
		case ITEM(10,60):
		case ITEM(11,60):/*cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; break;*/cl.r = 0.00f; cl.g = 0.20f; cl.b = 0.10f; OldGlow = false; break;
		//High Elf
		case ITEM(4,30): cl.r = 0.30f; cl.g = 0.30f; cl.b = 0.00f; OldGlow = false; break;
		case ITEM(7,62):
		case ITEM(8,62):
		case ITEM(9,62):
		case ITEM(10,62):
		case ITEM(11,62):cl.r = 0.10f; cl.g = 0.60f; cl.b = 0.50f; OldGlow = false; break;//cl.r = 0.00f; cl.g = 0.80f; cl.b = 0.30f; break;
		//Duel Master
		case ITEM(0,41): cl.r = 0.30f; cl.g = 0.20f; cl.b = 0.00f; OldGlow = false; break;
		case ITEM(6,31): cl.r = 0.80f; cl.g = 0.30f; cl.b = 0.10f; OldGlow = false; break;
		case ITEM(8,63):
		case ITEM(9,63):
		case ITEM(10,63):
		case ITEM(11,63):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; OldGlow = false; break;//cl.r = 0.80f; cl.g = 0.20f; cl.b = 0.10f; break;
		//Lord Emperor
		case ITEM(2,20): cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; OldGlow = false; break;
		case ITEM(6,30): cl.r = 0.90f; cl.g = 0.50f; cl.b = 0.20f; OldGlow = false; break;
		case ITEM(7,64):
		case ITEM(8,64):
		case ITEM(9,64):
		case ITEM(10,64):
		case ITEM(11,64):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; OldGlow = false; break;
		//Dimention Master
        case ITEM(5,41): cl.r = 0.10f; cl.g = 0.30f; cl.b = 0.50f; OldGlow = false; break;
		case ITEM(7,65):
		case ITEM(8,65):
		case ITEM(9,65):
		case ITEM(10,65):
		case ITEM(11,65):cl.r = 0.40f; cl.g = 0.40f; cl.b = 0.40f; OldGlow = false; break;//cl.r = 0.00f; cl.g = 0.30f; cl.b = 0.70f; break;
		//cl.r = 0.80f; cl.g = 0.90f; cl.b = 0.90f; break;	//Белый
		//cl.r = 0.30f; cl.g = 0.30f; cl.b = 0.00f; break;	//Коричневый
		//default:OldGlow = true;
    }

#ifdef _LOAD_GLOW_
	for(int i=0;i<gLoadGlow.Count;i++)
	{
		if(gLoadGlow.ILoad[i].Type == -1)
		{
			if(dwItemId == ITEM(7,gLoadGlow.ILoad[i].Index))
			{
				cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
				OldGlow = false;
			}
			else if(dwItemId == ITEM(8,gLoadGlow.ILoad[i].Index))
			{
				cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
				OldGlow = false;
			}
			else if(dwItemId == ITEM(9,gLoadGlow.ILoad[i].Index))
			{
				cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
				OldGlow = false;
			}
			else if(dwItemId == ITEM(10,gLoadGlow.ILoad[i].Index))
			{
				cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
				OldGlow = false;
			}
			else if(dwItemId == ITEM(11,gLoadGlow.ILoad[i].Index))
			{
				cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
				OldGlow = false;
			}
		}
		else if(dwItemId == ITEM(gLoadGlow.ILoad[i].Type,gLoadGlow.ILoad[i].Index))
		{
			cl.r = gLoadGlow.ILoad[i].Red; cl.g = gLoadGlow.ILoad[i].Green; cl.b = gLoadGlow.ILoad[i].Blue;
			OldGlow = false;
		}
	}
#endif

	if(OldGlow == true)
	{
		OriginalGlow(dwItemId, uk1, uk2, cl, bUkn);
	}
}

void InitGlowFunc()
{
    HookThis((DWORD)&Glow,0x005CD032);//1.03.11 Jpn
}
#endif