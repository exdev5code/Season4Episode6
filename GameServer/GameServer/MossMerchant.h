#ifndef MOSSMARCHANT_H
#define MOSSMARCHANT_H

#define MAX_ITEM_SECTION	255

void MossEventRun(void * lpParam);

class CMossMerchant
{
public:
	void Init();
	void ReadFile();
	void ItemBuy(int aIndex,int Item);

	int ItemCount[5];

	unsigned char Type[5][MAX_ITEM_SECTION];
	unsigned short Index[5][MAX_ITEM_SECTION];
	unsigned char Level[5][MAX_ITEM_SECTION];
	unsigned char Dur[5][MAX_ITEM_SECTION];
	unsigned char Skill[5][MAX_ITEM_SECTION];
	unsigned char Luck[5][MAX_ITEM_SECTION];
	unsigned char Opt[5][MAX_ITEM_SECTION];
	unsigned char Exe[5][MAX_ITEM_SECTION];
	unsigned char Anc[5][MAX_ITEM_SECTION];
};

extern CMossMerchant gMossMerchant;

#endif