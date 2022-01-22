//GameServer 1.00.77 JPN - Completed
#include "stdafx.h"
#include "TNotice.h"
#include "user.h"
#include "giocp.h"
#include "..\common\winutil.h"

void TNotice::MakeNoticeMsg(void * lpNotice, BYTE btType, char * szNoticeMsg)
{
	PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;
	pNotice->type  = btType;

	wsprintf(pNotice->Notice, szNoticeMsg);
	PHeadSetB((LPBYTE)pNotice, 0x0D, strlen(pNotice->Notice) + sizeof(PMSG_NOTICE) - sizeof(pNotice->Notice) + 1 );
}

void TNotice::MakeNoticeMsgEx(void * lpNotice, BYTE btType, char * szNoticeMsg, ...)
{
	PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;
	pNotice->type = btType;

	va_list pArguments;
	va_start(pArguments, szNoticeMsg);
	vsprintf((char*)pNotice->Notice, (char*)szNoticeMsg, pArguments);
	va_end(pArguments);

	PHeadSetB((LPBYTE)pNotice, 0x0D, strlen(pNotice->Notice)  + sizeof(PMSG_NOTICE) - sizeof(pNotice->Notice) + 1);
}

void TNotice::SetNoticeProperty(void * lpNotice, BYTE btType, DWORD dwColor, BYTE btCount, WORD wDelay, BYTE btSpeed)
{
	PMSG_NOTICE * pNotice =(PMSG_NOTICE *) lpNotice;

	pNotice->type = btType;
	pNotice->dwColor = dwColor;
	pNotice->btCount = btCount;
	pNotice->wDelay = wDelay;
	pNotice->btSpeed = btSpeed;
}

void TNotice::SendNoticeToAllUser(void * lpNotice)
{
	PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;

	for ( int n = OBJ_STARTUSERINDEX ; n < OBJMAX ; n++)
	{
		if ( gObj[n].Connected == PLAYER_PLAYING )
		{
			if ( gObj[n].Type  == OBJ_USER )
			{
				DataSend(n, (LPBYTE)pNotice  , pNotice->h.size  );
			}
		}
	}
}

void TNotice::SendNoticeToUser(int aIndex, void * lpNotice)
{
	PMSG_NOTICE * pNotice = (PMSG_NOTICE *)lpNotice;
	DataSend(aIndex, (LPBYTE)pNotice, pNotice->h.size  );
}

void TNotice::AllSendServerMsg(LPSTR chatmsg)
{
	PMSG_NOTICE pNotice;
	
	MakeNoticeMsg((TNotice *)&pNotice, 0,  chatmsg);

	for ( int n = OBJ_STARTUSERINDEX ; n < OBJMAX ; n++)
	{
		if ( gObj[n].Connected == PLAYER_PLAYING )
		{
			if ( gObj[n].Type  == OBJ_USER )
			{
				DataSend(n, (LPBYTE)&pNotice , pNotice.h.size );
			}
		}
	}
}

void TNotice::GCServerMsgStringSend(LPSTR szMsg, int aIndex, BYTE type)
{
	PMSG_NOTICE pNotice;
	
	MakeNoticeMsg(&pNotice, type, szMsg);
	DataSend(aIndex, (LPBYTE)&pNotice, pNotice.h.size);
}

TNotice::TNotice(BYTE btType)
{
	this->m_Notice.btCount = 1;
	this->m_Notice.btSpeed = 20;
	this->m_Notice.dwColor = _ARGB(255, 255, 200, 80 );
	this->m_Notice.wDelay = 0;
	this->m_Notice.type = btType;
}

void TNotice::SendToAllUser(LPSTR szMsg, ...)
{
	va_list pArguments;
	va_start(pArguments, szMsg);
	vsprintf(this->m_Notice.Notice, (char*)szMsg, pArguments);
	va_end(pArguments);

	PHeadSetB((LPBYTE)&this->m_Notice, 0x0D, strlen(this->m_Notice.Notice)  + sizeof(PMSG_NOTICE) - sizeof(this->m_Notice.Notice) + 1);

	for ( int n = OBJ_STARTUSERINDEX ; n < OBJMAX ; n++)
	{
		if ( gObj[n].Connected == PLAYER_PLAYING )
		{
			if ( gObj[n].Type  == OBJ_USER )
			{
				DataSend(n, (LPBYTE)&this->m_Notice , this->m_Notice.h.size );
			}
		}
	}
}

void TNotice::SendToUser(int aIndex, LPSTR szMsg, ...)
{
	va_list pArguments;
	va_start(pArguments, szMsg);

	vsprintf(this->m_Notice.Notice, (char*)szMsg, pArguments);
	va_end(pArguments);

	PHeadSetB((LPBYTE)&this->m_Notice, 0x0D, strlen(this->m_Notice.Notice)  + sizeof(PMSG_NOTICE) - sizeof(this->m_Notice.Notice) + 1);
	DataSend(aIndex, (LPBYTE)&this->m_Notice , this->m_Notice.h.size );

}