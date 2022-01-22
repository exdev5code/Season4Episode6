//GS-CS 1.00.90  - 0xXXXXXXXX 
#include "StdAfx.h"
#include "SocketData.h"

//************************************
//CSeed class
//************************************

//005562F0 identical
CSeed::CSeed()
{
	this->ClearData();
}

//00556320 identical
CSeed::~CSeed()
{

}

// 00556340 - identical
void CSeed::ClearData()
{
	this->m_btOptionIndex = 0;
	this->m_btElementIndex = 0;
	this->m_btItemLevel = 0;
	this->m_btOptionType = 0;

	for(int i = 0; i < 5;i++)
	{
		this->m_btSocketSlot[i] = 0;
	}

	this->m_iSocketSlotCount = 0;
	this->m_iItemIndex = 0;
}
	
//005563C0 - identical
BYTE CSeed::CheckSphere(CItem *pItem)
{
	if(pItem == NULL)
	{
		return 0;
	}

	if(pItem->IsItem() == 0)
	{
		return 0;
	}

	if(this->m_iItemIndex == pItem->m_Type && this->m_btItemLevel == pItem->m_Level)
	{
		return 1;
	}
	
	return 0;
}

//00556430 -identical
void CSeed::SetInfo(BYTE OptionIndex, BYTE ElementIndex, BYTE Level, BYTE OptionType, BYTE SocketSlot[5], int SocketSlotCount)
{
	this->m_btOptionIndex = OptionIndex;
	this->m_btElementIndex = ElementIndex;
	this->m_btItemLevel = Level;
	this->m_btOptionType = OptionType;

	for(int i = 0;i < 5;i++)
	{
		this->m_btSocketSlot[i] = SocketSlot[i];
	}

	this->m_iSocketSlotCount = SocketSlotCount;
	
	switch(ElementIndex)
	{
	case 1:	this->m_iItemIndex = ITEMGET(12,60);break;
	case 2:	this->m_iItemIndex = ITEMGET(12,61);break;
	case 3:	this->m_iItemIndex = ITEMGET(12,62);break;
	case 4:	this->m_iItemIndex = ITEMGET(12,63);break;
	case 5:	this->m_iItemIndex = ITEMGET(12,64);break;
	case 6:	this->m_iItemIndex = ITEMGET(12,65);break;
	case 7:	this->m_iItemIndex = ITEMGET(12,66);break; //reserved
	}
}

//************************************
//CSphere class
//************************************

//00556570 - identical
CSphere::CSphere()
{

}

//00556590 - identical
CSphere::~CSphere()
{

}

//005565B0 - identical
void CSphere::ClearData()
{
	this->m_btItemLevel	=   0;
	this->m_iElementIndex	=	0;
	this->m_iItemIndex	=	0;
}

//005565F0 - identical
void CSphere::SetInfo(BYTE level, int index)
{
	this->m_btItemLevel = level;
	this->m_iElementIndex = index;

	switch(level)
	{
	case 1:this->m_iItemIndex = ITEMGET(12,70);break;
	case 2:this->m_iItemIndex = ITEMGET(12,71);break;
	case 3:this->m_iItemIndex = ITEMGET(12,72);break;
	case 4:this->m_iItemIndex = ITEMGET(12,73);break;
	case 5:this->m_iItemIndex = ITEMGET(12,74);break;
	}
}

//************************************
//CSeedSphere class
//************************************

//005566B0 - identical
CSeedSphere::CSeedSphere()
{
	this->ClearData();
}

//005566E0 - identical
CSeedSphere::~CSeedSphere()
{

}

//00556700 - identical
void CSeedSphere::ClearData()
{
	this->m_btItemByteOption	= 0; // 0
	this->m_btOptionIndex	= 0; // 1
	this->m_btElementIndex	= 0; // 2
	this->m_btItemLevel	= 0; // 8
	this->m_btOptionType	= 0; // 9
	this->m_wSocketSlot  = 0; // A
	this->m_iItemIndex   = 0;  // 4
}

//00556760 //identical Calls alloc 3x
BYTE CSeedSphere::SetInfo(CSeed * lpSeed, BYTE slot_count)
{
	if(lpSeed == NULL || !slot_count)
	{
		return 0;
	}
	
	this->m_btItemByteOption	= slot_count * 50 + lpSeed->m_btOptionIndex;
	this->m_btOptionIndex	= lpSeed->m_btOptionIndex;

	this->m_btElementIndex	= lpSeed->m_btElementIndex;
	
	this->m_btItemLevel	= lpSeed->m_btItemLevel;
	
	this->m_btOptionType	= lpSeed->m_btOptionType;
	
	this->m_btSocketSlotCount	= slot_count;
	
	this->m_wSocketSlot  = lpSeed->m_btSocketSlot[slot_count-1];

	switch(lpSeed->m_btElementIndex)
	{
	case 1:this->m_iItemIndex = ITEMGET(12,100);	break;
	case 2:this->m_iItemIndex = ITEMGET(12,101);	break;
	case 3:this->m_iItemIndex = ITEMGET(12,102);	break;
	case 4:this->m_iItemIndex = ITEMGET(12,103);	break;
	case 5:this->m_iItemIndex = ITEMGET(12,104);	break;
	case 6:this->m_iItemIndex = ITEMGET(12,105);	break;
	case 7:								break;
	default:							return 0;
	}

	this->m_iItemIndex += (this->m_btSocketSlotCount - 1) * 6;

	return 1;
}

//00556900 - identical
void CSeedSphere::IncSocketSlot(BYTE value)
{
	if(this->m_wSocketSlot + value > (WORD)-2) //0xFE 
	{
		return;
	}

	this->m_wSocketSlot += value;
}