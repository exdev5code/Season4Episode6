// WZScriptEncode.h: interface for the CWZScriptEncode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WZSCRIPTENCODE_H__0708A3AD_F4E6_46CB_94C9_0592F066C147__INCLUDED_)
#define AFX_WZSCRIPTENCODE_H__0708A3AD_F4E6_46CB_94C9_0592F066C147__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum WZSMDToken {
  T_NAME = 0x0,
  T_NUMBER = 0x1,
  T_END = 0x2,
  T_COMMAND = 0x23,
  T_LP = 0x7b,
  T_RP = 0x7d,
  T_COMMA = 0x2c,
  T_SEMICOLON = 0x3b,
  T_SMD_ERROR = 0x3c,
};

class CWZScriptEncode  
{
public:
	CWZScriptEncode();
	virtual ~CWZScriptEncode();

	int Open(char* filename);
	void Close();
	void SetScriptParsingBuffer(char* buffer, int size);
	WZSMDToken GetToken();
	WZSMDToken TokenType();
	int GetNumber();
	char* GetString();
	void Encode(char* buffer, int size);
	int GetC();
	void UnGetC(int ch);

public:
	char* m_pBuffer;
	int m_iBufferSize;
	int m_iBufferCount;
	HANDLE m_hFile;
	char* m_Token;
	float TokenNumber;
	char TokenString[100];
	WZSMDToken CurrentToken;
};

extern BYTE XorTable[];

#endif // !defined(AFX_WZSCRIPTENCODE_H__0708A3AD_F4E6_46CB_94C9_0592F066C147__INCLUDED_)
