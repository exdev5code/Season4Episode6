// LogToFile.cpp: implementation of the CLogToFile class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dataserver.h"
#include "LogToFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogToFile::CLogToFile(LPSTR LogFileName, LPSTR LogDirectoryName, BOOL bWithDate)
{
	if (strcmp(LogFileName, "") == 0)
	{
		strcpy(m_szLogFileName , "LOGDATA");
	}
	else
	{
		strcpy(m_szLogFileName , LogFileName);
	}
	
	if (!strcmp(LogDirectoryName, ""))
	{
		strcpy(m_szLogDirectoryName , "LOG");
	}
	else
	{
		strcpy(m_szLogDirectoryName  , LogDirectoryName);
	}
	
	m_bWithDate  = bWithDate;	

	CreateDirectory(LogDirectoryName, NULL);

	InitializeCriticalSection(&m_critLogToFile );
}

CLogToFile::~CLogToFile()
{
	DeleteCriticalSection(&m_critLogToFile );
}

void __cdecl CLogToFile::Output( LPSTR fmt, ...)
{
	va_list argptr;
	int iChrWritten;
	char szLogFileName[260];

	SYSTEMTIME strSystime;
	
	EnterCriticalSection(&m_critLogToFile );

	va_start(argptr, fmt);
	iChrWritten=vsprintf(m_cBUFFER , fmt, argptr);
	va_end(argptr);

	GetLocalTime(&strSystime);

	wsprintf(szLogFileName, "%s\\%s %04d-%02d-%02d.txt",
		m_szLogDirectoryName, m_szLogFileName, 
		strSystime.wYear, strSystime.wMonth, strSystime.wDay);

	if ( (m_fLogFile = fopen(szLogFileName, "a+"))==0)
	{
		LeaveCriticalSection(&m_critLogToFile ); //wz fix :)
		return;
	}

	if (m_bWithDate ==0)
	{
		fprintf(m_fLogFile , "%s\n", m_cBUFFER);
	}
	else
	{
		fprintf(m_fLogFile , "%d:%d:%d  %s\n", 
			strSystime.wHour, strSystime.wMinute, 
			strSystime.wSecond, m_cBUFFER);
	}

	fclose(m_fLogFile );

	LeaveCriticalSection(&m_critLogToFile );
}