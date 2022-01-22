// WZScriptEncode.cpp: implementation of the CWZScriptEncode class.
// Decompilation Completed -> All Same as WebZen
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dataserver.h"
#include "WZScriptEncode.h"
#include "..\\Include\\ReadScript.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BYTE XorTable[10]={0xA1, 0xB2, 0xAA, 0x12, 0x23, 0xF1, 0xF3, 0xD3, 0x78, 0x02};

CWZScriptEncode::CWZScriptEncode()
{
	m_pBuffer = NULL;
	m_iBufferSize = 0;
	m_iBufferCount = 0;
	m_hFile = INVALID_HANDLE_VALUE;
}

CWZScriptEncode::~CWZScriptEncode()
{
	Close();
}

int CWZScriptEncode::Open(char *filename)
{
	if(m_hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hFile);
	}

	m_hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0x80, NULL);

	if(m_hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	int filesize = GetFileSize(m_hFile, NULL);

	char* pBuffer = (char*)malloc(filesize);

	DWORD iReadFileSize;

	ReadFile(m_hFile, pBuffer, filesize, &iReadFileSize, 0);

	if(iReadFileSize == 0)
	{
		Close();
	}

	Encode(pBuffer, iReadFileSize);

	SetScriptParsingBuffer(pBuffer, iReadFileSize);

	CloseHandle(m_hFile);

	return 1;
}

void CWZScriptEncode::Close()
{
	if ( m_pBuffer != 0)
	{
		free( m_pBuffer );
	}
}

void CWZScriptEncode::Encode(char* buffer, int size)
{
	int i;

	for (i=0;i<size; i++)
	{
		buffer[i]=buffer[i]^XorTable[i%10];	
	}
}

int CWZScriptEncode::GetC()
{
	if ( m_iBufferCount >= m_iBufferSize )
	{
		return -1;
	}
	else
	{
		return m_pBuffer [ m_iBufferCount++ ];
	}
}

void CWZScriptEncode::UnGetC(int ch)
{
	if ( m_iBufferCount <= 0)
	{
		return;
	}
	else
	{
		m_iBufferCount--;

		m_pBuffer [ m_iBufferCount ] = ch;
	}
}


void CWZScriptEncode::SetScriptParsingBuffer( char* buffer, int size)
{
	m_pBuffer = buffer;
	m_iBufferSize = size;
	m_iBufferCount = 0;
}

int CWZScriptEncode::GetNumber()
{
	return (int)TokenNumber;
}

char* CWZScriptEncode::GetString()
{
	return TokenString;
}

WZSMDToken CWZScriptEncode::GetToken()
{
	char ch;
	TokenString[0] = '\0';
	do
	{
		if ( (ch =(char) GetC() ) == EOF) return T_END;

		if (ch == '/')
		{
			if ((ch =(char) GetC() )=='/')	
			{
				while ((ch != '\n') && (ch != EOF))	ch =(char) GetC();
			}
		}
	} while(  isspace(ch) );

	char *p, TempString[100];
	switch(ch)
	{	
	case '#':
		return CurrentToken = T_COMMAND;
	case ';':
		return CurrentToken = T_SEMICOLON;
	case ',':
		return CurrentToken = T_COMMA;
	case '{':
		return CurrentToken = T_LP;
	case '}':
		return CurrentToken = T_RP;
	case '0':	case '1':	case '2':	case '3':	case '4':
	case '5':	case '6':	case '7':	case '8':	case '9':
	case '.':	case '-':
		UnGetC(ch);
		p = TempString;
		while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || isdigit(ch) || ch=='-') )
			*p++ = ch;
		*p = 0;
		TokenNumber = (float)atof(TempString);
		//			sscanf(TempString," %f ",&TokenNumber);
		return CurrentToken = T_NUMBER;
	case '"':
		p = TokenString;
		while ( (  (ch = GetC() ) !=EOF) && (ch!='"'))// || isalnum(ch)) )
			*p++ = ch;
		if (ch!='"')
			UnGetC(ch);
		*p = 0;
		return CurrentToken = T_NAME;
	default:
		if (isalpha(ch))	
		{
			p = TokenString;
			*p++ = ch;
			while ( (  (ch = GetC() ) !=EOF) && (ch=='.' || ch=='_' || isalnum(ch)) )
				*p++ = ch;
			UnGetC(ch);
			*p = 0;
			return CurrentToken = T_NAME;
		}
		return CurrentToken = T_SMD_ERROR;
	}
}