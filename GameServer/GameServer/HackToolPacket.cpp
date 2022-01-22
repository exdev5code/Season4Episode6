// HackToolPacket.cpp: implementation of the CHackToolPacket class.
// GameServer 90 Packet Limit Hacking Detection (Completed)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HackToolPacket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHackToolPacket* CHackToolPacket::SetState(bool bResult) //identical
{
	this->m_dwTick = 0;
	this->bLoad = bResult;
	this->bSetTick = 0;

	return this;
}

void CHackToolPacket::ClearTick() //identical
{
	this->bSetTick = 0;
	this->m_dwTick = 0;
}

void CHackToolPacket::Init() //00479E90 (identical)
{
	//empty?
}

BYTE CHackToolPacket::CheckExpiredTick() //identical
{
	if(this->m_dwTick <= GetTickCount())
	{
		if(this->bLoad == 1)
		{
			this->bSetTick = 0;
		}
		return 1;
	}
	return 0;
}

void CHackToolPacket::SetTick(DWORD dwTick) //identical
{
	this->bSetTick = 1;
	this->m_dwTick = GetTickCount() + dwTick;
}

//////////////////////////////////////////////////////////////////////////

CHackToolPacket::CHackToolPacket() //00479F40 (identical) (called in obj constructor)
{
	this->SetState(1);
	this->unk_8 = 0;
	this->m_iPacketCount = 0;
	this->unk_10 = 0;
	this->unk_14 = 0;
}

void CHackToolPacket::Clear(DWORD dwTick) //00479FA0 (identical)
{
	this->unk_8 = dwTick;
	this->m_iPacketCount = 0;
	this->unk_10 = 0;
	this->unk_14 = 0;
	this->ClearTick();
	this->SetTick(this->unk_8);
}

CHackToolPacket::~CHackToolPacket() //0047A010 (identical) (called in obj destructor)
{
	this->Init();
}

//////////////////////////////////////////////////////////////////////////
int CHackToolPacket::CheckPacketCount() //0047A040 (identical)
{
	if(CheckExpiredTick() == 1)
	{
		this->Clear(this->unk_8);
		return 2;
	}
	return 1;
}

void CHackToolPacket::IncreasePacketCount(BYTE arg1, DWORD arg2) //identical increase packet?
{
	this->m_iPacketCount++;
	this->unk_14 += arg2;

	if(arg1 == 1)
	{
		this->unk_10++;
	}
}

void CHackToolPacket::GetState(int * PacketCount, DWORD * arg2, DWORD * arg3) //0047A100 (identical)
{
	*PacketCount = this->m_iPacketCount;
	*arg2 = this->unk_10;
	*arg3 = this->unk_14;
}