#pragma once
#include "StdAfx.h"
#include "DSProtocol.h"

#if(_JEWELS_BANK_)

#define JEWELSBANK_DIR	"..\\Data\\ExData\\JewelsBank.ini"

class JewelsBank
{
private: 
	bool Enable;

public:
	void Load();

	void sendchaosbank(int aIndex, int Count);
	void sendblessbank(int aIndex, int Count);
	void sendsoulbank(int aIndex, int Count);
	void sendlifebank(int aIndex, int Count);

	void recvchaosbank(int aIndex, int Count);
	void recvblessbank(int aIndex, int Count);
	void recvsoulbank(int aIndex, int Count);
	void recvlifebank(int aIndex, int Count);
};
extern JewelsBank gJewelsBank;

#endif