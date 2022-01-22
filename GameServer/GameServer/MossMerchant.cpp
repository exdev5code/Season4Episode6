#include "StdAfx.h"
#include "MossMerchant.h"
#include "..\include\ReadScript.h"
#include "..\common\WzMemScript.h"
#include "LogProc.H"
#include "User.h"
#include "DSProtocol.h"
#include "Functions.h"

CMossMerchant gMossMerchant;

void CMossMerchant::Init()
{
	// ----
	for (int j=0;j<5;j++)
	{
		for (int i=0;i<MAX_ITEM_SECTION;i++)
		{
			gMossMerchant.Type[j][i] = -1;
			gMossMerchant.Index[j][i] = -1;
			gMossMerchant.Level[j][i] = 0;
			gMossMerchant.Dur[j][i] = 0;
			gMossMerchant.Skill[j][i] = 0;
			gMossMerchant.Luck[j][i] = 0;
			gMossMerchant.Opt[j][i] = 0;
			gMossMerchant.Exe[j][i] = 0;
			gMossMerchant.Anc[j][i] = 0;
		}
	}
	gMossMerchant.ReadFile();
}

void CMossMerchant::ReadFile()
{
	SMDFile = fopen("..\\ExTeam\\Events\\MossMerchant.ini", "r");

	if ( SMDFile == NULL )
	{
		MessageBoxA(0,"[MossMerchant] Info file Load Fail [..\\ExTeam\\Events\\MossMerchant.ini]","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	int Token;
	int type = -1;

	while ( true )
	{
	    Token = GetToken();

        if( Token == 2)
		{
            break;
		}

		type = (int)TokenNumber;

		while ( true )
		{
			if ( type < 0 || type > 4 )
			{
				break;
			}
		    Token = GetToken();

			if ( strcmp("end", TokenString ) == 0)
			{
				break;
			}

			gMossMerchant.Type[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Index[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Level[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Dur[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Skill[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Luck[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Opt[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Exe[type][ItemCount[type]] = (unsigned char)TokenNumber;

			Token = GetToken();
			gMossMerchant.Anc[type][ItemCount[type]] = (unsigned char)TokenNumber;

			gMossMerchant.ItemCount[type]++;
		    
		}
    }

	fclose(SMDFile);
	return;
}

struct PMSG_BUYRESULT
{
	unsigned char c;
	unsigned char size;
	unsigned char headcode;
	unsigned char Result;	// 3
	unsigned char ItemInfo[MAX_ITEM_INFO];	// 4
};

void CMossMerchant::ItemBuy(int aIndex,int Item)
{
	LPOBJ lpObj = &gObj[aIndex];
	PMSG_BUYRESULT pResult;

	pResult.c = 0xC1;
	pResult.size = sizeof(PMSG_BUYRESULT);
	pResult.headcode = 0x32;
	pResult.Result = -1;

	if ( gObj[aIndex].CloseType != -1 )
	{
		DataSend(aIndex, (LPBYTE)&pResult, pResult.size);
		return;
	}

	if ( !::gObjFixInventoryPointer(aIndex))
	{
		LogAdd("[Fix Inv.Ptr] False Location - %s, %d", __FILE__, __LINE__);
	}

	if ( lpObj->m_IfState.use > 0 )
	{
		if ( lpObj->m_IfState.type != 3 )
		{
			DataSend(aIndex, (LPBYTE)&pResult, pResult.size);
			return;
		}
	}

	if ( CheckInventoryEmptySpace(lpObj,4,2) == false )
	{
		GCServerMsgStringSend("[MossMerchant]: Need to make space in the inventory (4x2)",aIndex,1);
		DataSend(aIndex, (LPBYTE)&pResult, pResult.size);
		return;
	}

	if ( lpObj->Money < 1000000 )
	{
		GCServerMsgStringSend("[MossMerchant]: Need 1.000.000 zen to buy here",aIndex,1);
		DataSend(aIndex, (LPBYTE)&pResult, pResult.size);
		return;
	}

	int ItemIndex = -1;

	switch ( Item )
	{
	case 0x00:
		ItemIndex = 0;
		break;
	case 0x02:
		ItemIndex = 1;
		break;
	case 0x04:
		ItemIndex = 2;
		break;
	case 0x06:
		ItemIndex = 3;
		break;
	case 0x18:
		ItemIndex = 4;
		break;
	}

	if ( ItemIndex < 0 || ItemIndex > 4 )
	{
		return;
	}

	if ( gMossMerchant.ItemCount[ItemIndex] == 0 )
	{
		return;
	}

	int Random = rand()%gMossMerchant.ItemCount[ItemIndex];

	int NewItem = 0;
	unsigned char NewLevel = 0;
	unsigned char NewDur = 0;
	unsigned char NewSkill = 0;
	unsigned char NewLuck = 0;
	unsigned char NewOpt = 0;
	unsigned char NewExe = 0;
	unsigned char NewAnc = 0;
	unsigned char IsExe = 0;
	unsigned char IsAnc = 0;


	NewOpt = gMossMerchant.Opt[ItemIndex][Random];

	NewLuck = gMossMerchant.Luck[ItemIndex][Random];

	NewSkill = gMossMerchant.Skill[ItemIndex][Random];
	
	NewLevel = gMossMerchant.Level[ItemIndex][Random];

	if ( gMossMerchant.Anc[ItemIndex][Random] == 5 || gMossMerchant.Anc[ItemIndex][Random] == 10 )
	{
		NewAnc = gMossMerchant.Anc[ItemIndex][Random];
		IsAnc = 1;
	}
	else
		IsAnc = 0;

	//NewExe = GetRandomExeOption(gMossMerchant.Exe[ItemIndex][Random]);
	NewExe = GenExcOpt(gMossMerchant.Exe[ItemIndex][Random]);
	
	if(NewExe>0)
		IsExe = 1;

	NewItem = ITEMGET(gMossMerchant.Type[ItemIndex][Random],gMossMerchant.Index[ItemIndex][Random]);

	NewDur = ItemGetDurability(NewItem,NewLevel,IsExe,IsAnc);

	ItemSerialCreateSend(aIndex,236,0,0,NewItem,(BYTE)NewLevel,(BYTE)NewDur,(BYTE)NewSkill,(BYTE)NewLuck,(BYTE)NewOpt,aIndex,(BYTE)NewExe,(BYTE)NewAnc);

	lpObj->Money -= 1000000;
	GCMoneySend(aIndex,lpObj->Money);

	DataSend(aIndex, (LPBYTE)&pResult, pResult.size);

	return;
}