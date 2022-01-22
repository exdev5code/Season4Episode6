#include "StdAfx.h"
#include "Functions.h"
#include "user.h"
#include "DSProtocol.h"
#include "PCPointSystem.h"
#include "Message.h"

cPCPointSystem ExPCPointSystem;

void cPCPointSystem::ResetConfig()
{
	for (int i = 0; i < 3; i++)
	{
		AmountRecords[i] = 0;
	}

	for (int i = 0; i < 120; i++)
	{
		PCShop[i].Index			= 0;
		PCShop[i].ID			= 0;
		PCShop[i].Level			= 0;
		PCShop[i].Opt			= 0;
		PCShop[i].Luck			= 0;
		PCShop[i].Skill			= 0;
		PCShop[i].Dur			= 0;
		PCShop[i].Exc			= 0;
		PCShop[i].Ancient		= 0;
		PCShop[i].NewOpt1		= 0;
		PCShop[i].NewOpt2		= 0;
		PCShop[i].NewOpt3		= 0;
		PCShop[i].NewOpt4		= 0;
		PCShop[i].NewOpt5		= 0;
		PCShop[i].Cost			= 0;
	}

	for(int j=0;j<100;j++)
	{
		Mob[j].Mob		= 0;
		Mob[j].PcPoint	= 0;
	}
}

void cPCPointSystem::Load()
{
	ResetConfig();

	this->LoadConfigs();
}

void cPCPointSystem::LoadConfigs()
{
	this->ChekingCallInitItemsInShop = false;

	this->Ex_Enabled = GetPrivateProfileInt("PCPoints","Enabled",1,"..\\ExTeam\\PCPointSystem.ini");
	this->Ex_MaxPCPoints = GetPrivateProfileInt("PCPoints","MaxPCPoints",10000,"..\\ExTeam\\PCPointSystem.ini");

	this->EnableTime = GetPrivateProfileInt("PCPoints","EnableTime",0,"..\\ExTeam\\PCPointSystem.ini");
	this->TimePCPoint = GetPrivateProfileInt("PCPoints","TimePCPoint",0,"..\\ExTeam\\PCPointSystem.ini");
	this->RewardPCPoint = GetPrivateProfileInt("PCPoints","RewardPCPoint",0,"..\\ExTeam\\PCPointSystem.ini");

	FILE *file;
	file = fopen("..\\ExTeam\\PCPointSystem.ini","r");

	if (file == NULL)
	{
		MessageBoxA(0,"[PCPointSystem] Info file Load Fail [..\\ExTeam\\PCPointSystem.ini]","CRITICAL ERROR",0);
		ExitProcess(1);
		return;
	}

	char Buff[256];
	int Flag = 0;

	MobCount = 0;

	while (!feof(file))
	{
		fgets(Buff,256,file);

		if(Ex_IsBadFileLine(Buff, Flag))
			continue;

		if (Flag == 1)
		{
			int i = AmountRecords[0];
			int n[15];
			sscanf(Buff,"%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4], &n[5], &n[6], &n[7], &n[8], &n[9], &n[10], &n[11], &n[12], &n[13], &n[14]);
			PCShop[i].Index		= n[0];
			PCShop[i].ID		= n[1];
			PCShop[i].Level		= n[2];
			PCShop[i].Opt		= n[3];
			PCShop[i].Luck		= n[4];
			PCShop[i].Skill		= n[5];
			PCShop[i].Dur		= n[6];
			PCShop[i].Exc		= n[7];
			PCShop[i].Ancient	= n[8];
			PCShop[i].NewOpt1	= n[9];
			PCShop[i].NewOpt2	= n[10];
			PCShop[i].NewOpt3	= n[11];
			PCShop[i].NewOpt4	= n[12];
			PCShop[i].NewOpt5	= n[13];
			PCShop[i].Cost		= n[14];
			AmountRecords[0]++;
		}

		if(Flag == 2)
		{
			int n[3];
			sscanf(Buff,"%d %d", &n[0], &n[1]);

			Mob[MobCount].Mob		= n[0];
			Mob[MobCount].PcPoint	= n[1];
			MobCount++;
		}
	}
	fclose(file);
}

void cPCPointSystem::CreatePacketShop()
{
	int PacketSize = 0;
	int PacketFlag = 0;
	int Size       = 0;
	BYTE Packet1[11] = {0xC1, 0x05, 0xD0, 0x06, 0x00, 0xC2, 0x00, 0x36, 0x31, HIBYTE(AmountRecords[0]), LOBYTE(AmountRecords[0])};
	BYTE Packet2[4680];

	for (int i = 0; i < AmountRecords[0]; i++)
	{
		BYTE ItemInfo[13];
		ItemInfo[0] = PCShop[i].SlotX;
		ItemInfo[1] = PCShop[i].Reward & 0xFF;
		ItemInfo[2] = (PCShop[i].Level * 8) | (PCShop[i].Skill * 128) | (PCShop[i].Luck * 4) | (PCShop[i].Opt & 3);
		ItemInfo[3] = PCShop[i].Dur;
		ItemInfo[4] = (PCShop[i].Reward & 0x100) >> 1;
		if ( PCShop[i].Opt > 3 ) ItemInfo[4]  |= 0x40;
		ItemInfo[4] |= PCShop[i].Exc;
		ItemInfo[5] = PCShop[i].Ancient;
		ItemInfo[6] = (PCShop[i].Reward & 0x1E00 ) >> 5;
		ItemInfo[7] = PCShop[i].NewOpt1;
		ItemInfo[8] = PCShop[i].NewOpt2;
		ItemInfo[9] = PCShop[i].NewOpt3;
		ItemInfo[10] = PCShop[i].NewOpt4;
		ItemInfo[11] = PCShop[i].NewOpt5;
		ItemInfo[12] = PCShop[i].Cost;

		PacketSize = (sizeof(ItemInfo) * (i + 1));
		memcpy(&Packet2[PacketFlag], ItemInfo, PacketSize);
		PacketFlag = PacketSize;
	}
	Size = (sizeof(Packet1) + PacketSize);
	memcpy(&PCPointPacket, Packet1, sizeof(Packet1));
	memcpy(&PCPointPacket[sizeof(Packet1)], Packet2, sizeof(Packet1) + PacketSize);
	PCPointPacket[6]    = HIBYTE(Size);
	PCPointPacket[7]    = LOBYTE(Size);
	this->PacketSizes = (sizeof(Packet1) + PacketSize);
}

void cPCPointSystem::InitItemShop()
{
	this->ChekingCallInitItemsInShop = true;

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 8; j++)
			this->ArrayFiledItems[i][j] = false;

	for (int k = 0; k <  AmountRecords[0]; k++)
	{
		PCShop[k].Reward = PCShop[k].Index * 512 + PCShop[k].ID;
		if (PCShop[k].Dur == 0) PCShop[k].Dur = ItemGetDurability(PCShop[k].Reward,PCShop[k].Level,PCShop[k].Exc,0);
		ItemGetSize(PCShop[k].Reward,PCShop[k].X,PCShop[k].Y);
		PCShop[k].SlotX = this->gObjCalcItems(PCShop[k].X,PCShop[k].Y);
	}
	this->CreatePacketShop();
}

void cPCPointSystem::OpenShop(int Index)
{
	if(!this->Ex_Enabled)
		return;
	if (this->ChekingCallInitItemsInShop == false)
		this->InitItemShop();
	DataSend(Index,this->PCPointPacket,this->PacketSizes);
}

int cPCPointSystem::gObjCalcItems(int X, int Y)
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 8; j++)
			if (ArrayFiledItems[i][j] == false)
			{
				bool bFlag = true;

				for (short kX = 0; kX < X; kX++)
					for(short kY = 0; kY < Y; kY++)
						if ( i + kY > 14 || j + kX > 7 || ArrayFiledItems[i+kY][j+kX])
							bFlag = false;

				if (bFlag)
				{
					for (short kX = 0; kX < X; kX++)
						for(short kY = 0; kY < Y; kY++)
							ArrayFiledItems[i+kY][j+kX] = true;
					return i*8 + j;
				}
			}
			return -1;
}

void cPCPointSystem::BuyItem(int Index,int Position)
{
	int IndexItem = -1;

	for(int i = 0; i < AmountRecords[0]; i++)
		if (Position == PCShop[i].SlotX ) IndexItem = i;

	LPOBJ lpObj = &gObj[Index];
	if(IndexItem != -1)
	{
		if (PCShop[IndexItem].Cost <= ExUser[Index].PCPoint)
		{
			if ( CheckInventoryEmptySpace(lpObj,PCShop[IndexItem].Y,PCShop[IndexItem].X) != 0 )
			{
				ItemSerialCreateSend(lpObj->m_Index,236,0,0,PCShop[IndexItem].Reward,(BYTE)PCShop[IndexItem].Level,(BYTE)PCShop[IndexItem].Dur,
					(BYTE)PCShop[IndexItem].Skill,(BYTE)PCShop[IndexItem].Luck,(BYTE)PCShop[IndexItem].Opt,-1,(BYTE)PCShop[IndexItem].Exc,(BYTE)PCShop[IndexItem].Ancient);
				ExUser[Index].PCPoint = ExUser[Index].PCPoint - PCShop[IndexItem].Cost;
				InitPCPointForPlayer(lpObj,ExUser[Index].PCPoint,lpObj->ExCred);
				GJSetCharacterInfo(lpObj, lpObj->m_Index, 0);
			}
			else
				MsgNormal(Index,"[PCShop] Your inventory is full !");
		}
		else
			MsgNormal(Index,"[PCShop] Can`t buy, need %d PCPoints!", PCShop[IndexItem].Cost);
	}
}

void cPCPointSystem::InitPCPointForPlayer(LPOBJ lpObj, int AmountPoints, int Credits )
{
	if (AmountPoints > Ex_MaxPCPoints)
	{
		AmountPoints = Ex_MaxPCPoints;
		ExUser[lpObj->m_Index].PCPoint = AmountPoints;
	}
#ifdef _MegaMu_
	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(Credits), HIBYTE(Credits),
		LOBYTE(Credits), HIBYTE(Credits)};
#else
	BYTE Packet[8] = {0xC1, 0x08 , 0xD0 , 0x04 , LOBYTE(AmountPoints), HIBYTE(AmountPoints),
		LOBYTE(Credits), HIBYTE(Credits)};
#endif

	DataSend(lpObj->m_Index, (PBYTE)Packet, Packet[1]);
}


void cPCPointSystem::MobKillForPCPoint(LPOBJ lpObj, LPOBJ lpTargetObj)//lpTargetObj - тот кто убивает
{
	if(!this->Ex_Enabled)
		return;

	for(int i=0;i<MobCount;i++)	//Fix
	{
		if(lpObj->Class == Mob[i].Mob)
		{
			ExUser[lpTargetObj->m_Index].PCPoint += Mob[i].PcPoint;
			InitPCPointForPlayer(lpTargetObj, ExUser[lpTargetObj->m_Index].PCPoint,lpObj->ExCred );
			MsgNormal(lpTargetObj->m_Index,"[PCPoint] Kill Monster +%d",Mob[i].PcPoint);
			return;
		}
	}
}

void cPCPointSystem::TimeTickPCPoint(int aIndex)
{
	if(!this->EnableTime) return;
	if(ExUser[aIndex].OffTrade != 0) return;
	if(ExUser[aIndex].OffExp == 1)	return;

	ExUser[aIndex].PCPointTick++;
	if(ExUser[aIndex].PCPointTick >= this->TimePCPoint)
	{
		LPOBJ lpObj = &gObj[aIndex];
		ExUser[aIndex].PCPointTick = 0;
		ExUser[aIndex].PCPoint	+= this->RewardPCPoint;

		this->InitPCPointForPlayer(lpObj, ExUser[aIndex].PCPoint,lpObj->ExCred );
		MsgNormal(aIndex,"[PCTime]: +%d",this->RewardPCPoint);
	}
}