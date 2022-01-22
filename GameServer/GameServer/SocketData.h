#if !defined(_SOCKETDATA_)
#define _SOCKETDATA_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\\Common\\zzzitem.h"

class CSeed 
{
public:
	BYTE m_btOptionIndex; // 0
	BYTE m_btElementIndex; // 1
	BYTE m_btItemLevel; // 2
	BYTE m_btOptionType; // 3
	BYTE m_btSocketSlot[5]; // 4
	int m_iItemIndex; // 0C
	int m_iSocketSlotCount; // 10

	CSeed();
	~CSeed();
	void ClearData();
	BYTE CheckSphere(CItem *pItem);///
	void SetInfo(BYTE OptionIndex, BYTE ElementIndex, BYTE Level, BYTE OptionType, BYTE SocketSlot[5], int SocketSlotCount);
};

class CSphere 
{
public:
	BYTE m_btItemLevel; // 0
	int m_iElementIndex; // 4
	int m_iItemIndex; // 8

	CSphere();
	~CSphere();
	void ClearData();
	void SetInfo(BYTE level, int index);
};

class CSeedSphere 
{
public:
	BYTE m_btItemByteOption; // 0
	BYTE m_btOptionIndex; // 1
	BYTE m_btElementIndex; // 2
	int m_iItemIndex; // 4
	BYTE m_btItemLevel; // 8
	BYTE m_btOptionType; // 9
	WORD m_wSocketSlot; // A
	BYTE m_btSocketSlotCount;//0C

	CSeedSphere();
	~CSeedSphere();
	void ClearData();
	BYTE SetInfo(CSeed * lpSeed, BYTE slot_count);
	void IncSocketSlot(BYTE value);
	int GetItemIndex();
};
#endif