#include "StdAfx.h"

#if(_JEWELS_BANK_)

struct EXINFO_UPDATE
{
	PBMSG_HEAD2 h;
	int PremiumTime;
	int Chaos;
	int Bless;
	int Soul;
	int Life;
	float ExCred;
};



class JewelsBank
{
public:
	bool Active;
	void JewelsBankImageLoad();
	void JewelsBankLoad();
	void JewelsBankDraw();

	void JewelsBankRecv(EXINFO_UPDATE * aRecv);
};
extern JewelsBank gJewelsBank;

#endif