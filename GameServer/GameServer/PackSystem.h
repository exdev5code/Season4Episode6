#include "StdAfx.h"

#ifdef PACK_SYSTEM 

#define PACK_SYSTEM_DIR "..\\ExTeam\\PackSystem.ini"

class cPackSystem
{
private:
	bool Enable;
	int MixCount;
public:
	void Load();
	void ChatOperation(int aIndex, LPBYTE Protocol);
};
extern cPackSystem gPackSystem;

#endif