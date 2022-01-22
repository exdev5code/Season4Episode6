#include "StdAfx.h"
#include "GoldenArcher.h"
#include "Functions.h"
#include "DSProtocol.h"
#include "Message.h"

cGoldenArcher GoldenArcher;



void cGoldenArcher::Start()
{
	for (int i=0; i < 100; i++)
	{
		Items[i].Index		= 0;
		Items[i].ItemID		= 0;
		Items[i].Level		= 0;
		Items[i].Skill		= 0;
		Items[i].Luck		= 0;
		Items[i].Options	= 0;
		Items[i].Exl		= 0;
		Items[i].Anc		= 0;
	}
}

void cGoldenArcher::Load()
{
	this->Ex_RenaCount = GetPrivateProfileInt("GoldenArcher","RenaCount",1,"..\\ExTeam\\Events\\GoldenArcher.ini");
	GoldenArcher.Start();

	FILE *file;
	file = fopen("..\\ExTeam\\Events\\GoldenArcher.ini","r");

	if (file == NULL)
	{
		MessageBoxA(0,"[MossMerchant] Info file Load Fail [..\\ExTeam\\Events\\GoldenArcher.ini]","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;
	ArcherItemsCount = 0;

	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int n[8];

			sscanf(Buff,"%d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7]);

			Items[ArcherItemsCount].Index	= n[0];
			Items[ArcherItemsCount].ItemID	= n[1];
			Items[ArcherItemsCount].Level	= n[2];
			Items[ArcherItemsCount].Skill	= n[3];
			Items[ArcherItemsCount].Luck	= n[4];
			Items[ArcherItemsCount].Options	= n[5];
			Items[ArcherItemsCount].Exl		= n[6];
			Items[ArcherItemsCount].Anc		= n[7];

			ArcherItemsCount++;
		}
	}

	fclose(file);
}
void cGoldenArcher::ClickArcher(int PlayerID)
{
	LPOBJ lpObj = &gObj[PlayerID];

	if(gObjGetItemCountInInventory(PlayerID,0x01C15,0) < this->Ex_RenaCount)
	{
		MsgNormal(PlayerID,"[Archer] Need %d Rens",this->Ex_RenaCount);
		return;
	}
	gObjDeleteItemsCount(PlayerID,0x01C15,0,this->Ex_RenaCount);

	int num = rand()%ArcherItemsCount;
	int Exe = 0;
	int Anc = 0;
	int Type = ITEMGET(Items[num].Index,Items[num].ItemID);
	if ( Items[num].Exl > 0 )
		Exe = GenExcOpt(Items[num].Exl);

	if ( Items[num].Anc == 5 || Items[num].Anc == 10 )
		Anc = Items[num].Anc;

	ItemSerialCreateSend(PlayerID,(BYTE)lpObj->MapNumber,(BYTE)lpObj->X,(BYTE)lpObj->Y,Type,(BYTE)Items[num].Level,0,(BYTE)Items[num].Skill,(BYTE)Items[num].Luck,(BYTE)Items[num].Options,PlayerID,(BYTE)Exe,(BYTE)Anc);

}