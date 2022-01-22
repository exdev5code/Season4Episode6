//GameServer 1.00.77 JPN - Completed
#include "stdafx.h"
#include "NSerialCheck.h"

NSerialCheck::NSerialCheck()
{
	this->init();
}

NSerialCheck::~NSerialCheck()
{
	return;
}

void NSerialCheck::init()
{
	this->m_serial=-1;
	this->m_SendSeiral=0;
}

BOOL NSerialCheck::InCheck(BYTE serial)
{
	BYTE m_s=this->m_serial;
	m_s++;

	if ( m_s  == serial )
	{
		this->m_serial = serial;
		return TRUE;
	}

	return FALSE;
}

int NSerialCheck::GetSerial()
{
	return this->m_serial;
}

BYTE NSerialCheck::GetSendSerial()
{
	return this->m_SendSeiral++;
}