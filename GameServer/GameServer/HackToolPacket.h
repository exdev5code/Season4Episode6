// HackToolPacket.h: interface for the CHackToolPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HACKTOOLPACKET_H__16D8B196_F3BB_4B09_8AAE_30A62F0F1F07__INCLUDED_)
#define AFX_HACKTOOLPACKET_H__16D8B196_F3BB_4B09_8AAE_30A62F0F1F07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHackToolPacket  
{
public:
	
	CHackToolPacket* SetState(bool bResult);
	
	void ClearTick();
	void Init();
	
	BYTE CheckExpiredTick();
	void SetTick(DWORD dwTick);
	
	CHackToolPacket();
	void Clear(DWORD dwTick);
	~CHackToolPacket();

	int CheckPacketCount();
	void IncreasePacketCount(BYTE arg1, DWORD arg2);
	void GetState(int * PacketCount, DWORD * arg2, DWORD * arg3);

	DWORD	m_dwTick; //0
	bool	bLoad; //4
	BYTE	bSetTick; //5
	DWORD	unk_8; //8
	int		m_iPacketCount; //C
	DWORD	unk_10; //10
	DWORD	unk_14; //14
};

#endif // !defined(AFX_HACKTOOLPACKET_H__16D8B196_F3BB_4B09_8AAE_30A62F0F1F07__INCLUDED_)
