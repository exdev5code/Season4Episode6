#include "StdAfx.h"
#include "CustomNpc.h"
#include "user.h"
#include "Functions.h"

cCustomNpc gCustomNpc;

void cCustomNpc::Load()
{
	this->Enable = GetPrivateProfileInt("Common","Enable",0,CUSTOM_NPC_DIR);
	
	FILE * file = fopen(CUSTOM_NPC_DIR,"r");
	if(file == NULL)
	{
		MessageBoxA(0,CUSTOM_NPC_DIR,"LOAD FILE ERROR",0);
		this->Enable = false;
	}

	char Buff[256];
	int Flag = 0;
	this->CountNpc = 0;
	for (int i = 0; i < MAX_CUSTOM_NPC; i++)
	{
		this->NpcList[i] = 0;
	}
	while(!feof(file))
	{
		fgets(Buff,256,file);
		if(Ex_IsBadFileLine(Buff, Flag))
			continue;
		if(Flag == 1)
		{
			if(this->CountNpc == MAX_CUSTOM_NPC) break;
			int n[1];
			sscanf(Buff, "%d", &n[0]);
			this->NpcList[this->CountNpc] = n[0];
			this->CountNpc++;
		}
	}
	fclose(file);
}

void cCustomNpc::Main(int aIndex, int MonsterClass)
{
	if(!this->Enable)return;
 	LPOBJ lpObj = &gObj[aIndex];
	for (int i = 0; i < this->CountNpc; i++)
		if(MonsterClass == NpcList[i])
			lpObj->Type = OBJ_NPC;
}