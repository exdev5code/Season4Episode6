// SocketSphere.cpp: implementation of the CSocketSphere class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SocketSphere.h"
#include "SocketData.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/*CSocketSphere::CSocketSphere()
{

}

CSocketSphere::~CSocketSphere()
{

}*/

//0055BB50 
int CSeedSphere::GetItemIndex() //identical
{
	return this->m_iItemIndex;
}

//0055BB70 - identical
void CSocketSphere::ClearData()
{
	this->m_btOptionIndex = 0;
	this->m_btEffectType = 0;
	this->m_btElementIndex = 0;
	this->m_btElementType = 0;
	this->m_btOptionType = 0;
	this->m_btOptionValue = 0;
	this->m_iOptionRate = 0;

	for(int n = 0;n < 5;n++)
	{
		this->m_btSocketSlot[n] = 0;
	}

	this->m_btSocketSlotCount = 0;
}