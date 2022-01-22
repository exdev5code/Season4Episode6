#include "StdAfx.h"
#include "user.h"
#include "Configs.h"
#include "Message.h"
#include "DSProtocol.h"
// -----------------------------------------------------------------------------------------------------------------------------------------
unsigned char GetRandomExeOption(unsigned char MaxOption)
{
	unsigned char ExeOptions[6] = {1,2,4,8,16,32};
	// ----
	unsigned char Random = 0;
	unsigned char RandomEx = 0;
	unsigned char ReturnValue = 0;

	Random = rand()%(MaxOption+1);

	for (int i=0;i<Random;i++)
	{
		while ( true )
		{
			RandomEx = ExeOptions[rand()%6];

			if ( (ReturnValue&RandomEx) == 0 )
			{
				ReturnValue+=RandomEx;
				break;
			}
		}
	}
	return ReturnValue;
}
bool Ex_IsBadFileLine(char *FileLine, int &Flag)
{
	if(Flag == 0)
	{
		if(isdigit(FileLine[0]))
		{
			Flag = FileLine[0] - 48;
			return true;
		}
	}
	else if(Flag < 0 || Flag > 9)
	{
		Flag = 0;
	}

	if(!strncmp(FileLine, "end", 3))
	{
		Flag = 0;
		return true;
	}

	if(FileLine[0] == '/' || FileLine[0] == '\n')
		return true;

	for(UINT i = 0; i < strlen(FileLine); i++)
	{
		if(isalnum(FileLine[i]))
			return false;
	}
	return true;
}
int GetNumberByPercent(int Proc, int Min, int Max)
{
	int Random = rand()%100;

	if(Proc == 0 || Max == Min)
		return Min;
	
	if(Random <= Proc)
		return Max;

	if(Proc > 50)
		return GetNumberByPercent(Proc/2, Min, Max-1);
	else if(Proc < 30)
		return GetNumberByPercent(Proc*3/2, Min, Max-1);
	else
		return GetNumberByPercent(Proc, Min, Max-1);
}
int GenExcOpt(int amount)
{
	if(amount == 0)	return 0;
	// User input errors
	if (amount > 6) amount = 6;
	if (amount < 1) amount = 1;

	int opt_db[6]  = {1, 2, 4, 8, 16, 32};
	int exc = 0;

	std::random_shuffle(opt_db, opt_db + 6);

	for(int n=0; n < amount; n++)
		exc += opt_db[n];

	return exc;
}
//Возвращяет количество заданых вещей
int gObjGetItemCountInInventory(int aIndex, int ItemID,int ItemLevel)
{
	if(aIndex >= OBJMAX)
		return 0;

	LPOBJ lpObj = &gObj[aIndex];

	int Count = 0;
	for (int i = 0; i < 76; i++)
	{
		if (lpObj->pInventory[i].m_Type == ItemID && lpObj->pInventory[i].m_Level == ItemLevel)
			Count++;
	}
	return Count;
}
//Удаляет заданное количество вещей 
int gObjDeleteItemsCount(int aIndex, short Type, short Level, int dCount)
{
	if(aIndex >= OBJMAX)
		return 0;

	LPOBJ lpObj = &gObj[aIndex];

	int count = 0;
	for(int i = 0; i < 76; i++)
	{
		if(lpObj->pInventory[i].m_Type == Type && lpObj->pInventory[i].m_Level == Level)
		{
			gObjInventoryDeleteItem(aIndex, i);
			GCInventoryItemDeleteSend(aIndex, i, 1);
			count++;

			if(dCount == count)
				break;
		}
	}
	return count;
}
//==================================================================================================
// FireCracker
//==================================================================================================
void ExFireCracker(int aIndex, BYTE X, BYTE Y)
{
	LPOBJ lpObj = &gObj[aIndex];
	BYTE Packet[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y};
	DataSend(aIndex,Packet,Packet[1]);
	BYTE Packet2[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X+1, Y};
	DataSend(aIndex,Packet2,Packet2[1]);
	BYTE Packet3[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y+1};
	DataSend(aIndex,Packet3,Packet3[1]);
	BYTE Packet4[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X, Y-1};
	DataSend(aIndex,Packet4,Packet4[1]);
	BYTE Packet5[7] = {0xC1, 0x07, 0xF3, 0x40, 0x00, X-1, Y};
	DataSend(aIndex,Packet5,Packet5[1]);
}

bool ItemMoveBlockExlOpt(int exlopt_num)
{
	if(ExConfig.CommonServer.MoveExlOptLimit == 0) return true;
	int ExlOptCount = 0;
	switch (exlopt_num)
	{
		case 0: ExlOptCount = 0; break; case 1: ExlOptCount = 1; break; case 2: ExlOptCount = 1; break; case 3: ExlOptCount = 2; break; case 4: ExlOptCount = 1; break;
		case 5: ExlOptCount = 2; break; case 6: ExlOptCount = 2; break; case 7: ExlOptCount = 3; break; case 8: ExlOptCount = 1; break; case 9: ExlOptCount = 2; break;
		case 10:ExlOptCount = 2; break; case 11:ExlOptCount = 3; break; case 12:ExlOptCount = 2; break; case 13:ExlOptCount = 3; break; case 14:ExlOptCount = 3; break;
		case 15:ExlOptCount = 4; break; case 16:ExlOptCount = 1; break; case 17:ExlOptCount = 2; break; case 18:ExlOptCount = 2; break; case 19:ExlOptCount = 3; break;
		case 20:ExlOptCount = 2; break; case 21:ExlOptCount = 3; break; case 22:ExlOptCount = 3; break; case 23:ExlOptCount = 4; break; case 24:ExlOptCount = 2; break;
		case 25:ExlOptCount = 3; break; case 26:ExlOptCount = 3; break; case 27:ExlOptCount = 4; break; case 28:ExlOptCount = 3; break; case 29:ExlOptCount = 4; break;
		case 30:ExlOptCount = 4; break; case 31:ExlOptCount = 5; break; case 32:ExlOptCount = 1; break; case 33:ExlOptCount = 2; break; case 34:ExlOptCount = 2; break;
		case 35:ExlOptCount = 3; break; case 36:ExlOptCount = 2; break; case 37:ExlOptCount = 3; break; case 38:ExlOptCount = 3; break; case 39:ExlOptCount = 4; break;
		case 40:ExlOptCount = 2; break; case 41:ExlOptCount = 3; break; case 42:ExlOptCount = 3; break; case 43:ExlOptCount = 4; break; case 44:ExlOptCount = 3; break;
		case 45:ExlOptCount = 4; break; case 46:ExlOptCount = 4; break; case 47:ExlOptCount = 5; break; case 48:ExlOptCount = 2; break; case 49:ExlOptCount = 3; break;
		case 50:ExlOptCount = 3; break; case 51:ExlOptCount = 4; break; case 52:ExlOptCount = 3; break; case 53:ExlOptCount = 4; break; case 54:ExlOptCount = 4; break;
		case 55:ExlOptCount = 5; break; case 56:ExlOptCount = 3; break; case 57:ExlOptCount = 4; break; case 58:ExlOptCount = 4; break; case 59:ExlOptCount = 5; break;
		case 60:ExlOptCount = 4; break; case 61:ExlOptCount = 5; break; case 62:ExlOptCount = 5; break; case 63:ExlOptCount = 6; break; 
	}
	if(ExlOptCount >= ExConfig.CommonServer.MoveExlOptLimit) return false;
	else return true;
}
#ifdef _MuReal_
void TimeTickWCoin(int aIndex)
{
	if(!ExConfig.CommonServer.WCoinTime || !ExConfig.CommonServer.WCoinReward) return;
	if(ExUser[aIndex].OffTrade != 0) return;
	if(ExUser[aIndex].OffExp == 1)	return;
	ExUser[aIndex].WCoinTick++;
	if(ExUser[aIndex].WCoinTick >= ExConfig.CommonServer.WCoinTime)
	{
		LPOBJ lpObj = &gObj[aIndex];
		ExUser[aIndex].WCoinTick = 0;
		GDRequestWcoinInfoLoad (lpObj,ExConfig.CommonServer.WCoinReward,1);
		MsgNormal(aIndex,"[WCoinTime]: +%d",ExConfig.CommonServer.WCoinReward);
	}
}
#endif

BYTE GetExcOptionCount(BYTE ExcellentOption)
{
	int ExcellentCount = 0;
	// ----
	for( int i = 0; i < 6; i++ )
	{
		if( (ExcellentOption >> i) & 1 )
		{
			ExcellentCount++;
		}
	}
	// ----
	return ExcellentCount;
}

int EmptyPointInventory(int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int Empty = 0;
	// ----

	for( int i = INVETORY_WEAR_SIZE; i < 76; i++ )
    {
        if( !lpObj->pInventory[i].IsItem() )
		{
			Empty++;
		}
	}

	return Empty;
}