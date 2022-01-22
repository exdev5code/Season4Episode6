#include "StdAfx.h"
#ifdef PREMIUM_SYSTEM
#include "user.h"

#define PREMIUM_DIR "..\\ExTeam\\PremiumSystem.ini"

class PremiumSystem
{
private:
	int Enable;

	int PlusExp;
	int PlusZen;

#ifdef _PREMIUM_MOTHER_BUY_
	int BuyVipCred;
#endif



public:
	void Loader();
	void TickTime(int aIndex);
	void Exp(LPOBJ lpObj, __int64 & Experience);
	void Zen(LPOBJ lpObj, float & money);
	void ChatSell(int aIndex, LPBYTE Protocol);
	void ConnectInfo(int aIndex);
#ifdef _PREMIUM_MOTHER_BUY_
	void ChatBuyVipUser(int aIndex, LPBYTE Protocol);
#endif
	int MaxDropZen;
};
extern PremiumSystem Premium;

#endif