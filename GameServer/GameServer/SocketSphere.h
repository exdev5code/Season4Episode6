// SocketSphere.h: interface for the CSocketSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETSPHERE_H__5BBE2F71_192F_4434_8E30_D9BCCFA0F635__INCLUDED_)
#define AFX_SOCKETSPHERE_H__5BBE2F71_192F_4434_8E30_D9BCCFA0F635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSocketSphere  
{
public:
	//CSocketSphere();
	//~CSocketSphere();

	BYTE m_btOptionIndex;// 0
	BYTE m_btEffectType; //1
	BYTE m_btElementIndex; //2
	BYTE m_btElementType; //3
	BYTE m_btOptionType; //4
	BYTE m_btOptionValue; //5 
	int m_iOptionRate; //8
	BYTE m_btSocketSlot[5]; //0C
	BYTE m_btSocketSlotCount; //11
	void ClearData();
};

#endif // !defined(AFX_SOCKETSPHERE_H__5BBE2F71_192F_4434_8E30_D9BCCFA0F635__INCLUDED_)
