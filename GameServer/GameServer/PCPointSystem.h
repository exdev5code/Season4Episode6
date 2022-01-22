#ifndef PCPOINTSYSTEM_H
#define PCPOINTSYSTEM_H

class cPCPointSystem
{
public:
	void ResetConfig();
	void Load();
	void LoadConfigs();
	void CreatePacketShop();
	void InitItemShop();
	void OpenShop(int Index);
	int gObjCalcItems(int X, int Y);
	void BuyItem(int Index,int Position);
	void InitPCPointForPlayer(LPOBJ gObj, int AmountPoints, int Credits );

	void MobKillForPCPoint(LPOBJ lpObj, LPOBJ lpTargetObj);
	void TimeTickPCPoint(int aIndex);

	int Ex_Enabled;
	int Ex_MaxPCPoints;

	int EnableTime;
	int TimePCPoint;
	int RewardPCPoint;

	struct
	{
		short Index;
		short ID;
		short Reward;
		int X;
		int Y;
		short Level;
		short Opt;
		short Luck;
		short Skill;
		short Dur;
		short Exc;
		short Ancient;
		short NewOpt1;
		short NewOpt2;
		short NewOpt3;
		short NewOpt4;
		short NewOpt5;
		short Cost;
		short SlotX;
	}PCShop[120];

	struct 
	{
		int Mob;
		int PcPoint;
	}Mob[100];

	int MobCount;

	short AmountRecords[3];
	bool ArrayFiledItems[15][8];
	int PacketSizes;
	BYTE PCPointPacket[4680];
	bool ChekingCallInitItemsInShop;
};
extern cPCPointSystem ExPCPointSystem;

#endif PCPOINTSYSTEM_H