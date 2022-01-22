// ------------------------------
// Decompiled by Deathway
// Date : 2007-03-09
// ------------------------------
#ifndef PRODEF_H
#define PRODEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MAX_ACCOUNT_LEN
	#define MAX_ACCOUNT_LEN	10
	#define MAX_GUILD_LEN	8
#endif

// PACKET HEAD DEFINITIONS
#define JS_ONLY_VIP_MEMBERS		0x02
#define JS_BAD_CLIENT_VERSION	0x06

#define MAX_CHAT_LEN 60

#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )
#define SET_NUMBERHW(x) ( (WORD)((DWORD)(x)>>(DWORD)16) )
#define SET_NUMBERLW(x) ( (WORD)((DWORD)(x) & 0xFFFF) )

#define MAKE_NUMBERW(x,y)  ( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  )
#define MAKE_NUMBERDW(x,y) ( (DWORD)(((WORD)((y)&0xFFFF)) | ((WORD)((x)&0xFFFF)<<16))  )

#ifndef _QWORD_DEFINED 
#define _QWORD_DEFINED 
typedef __int64 QWORD, *LPQWORD; 
#endif

#define MAKEQWORD(a, b)      ((__int64)(((DWORD)((__int64)(a) & 0xffffffff)) | ((__int64)((DWORD)((__int64)(b) & 0xffffffff))) << 32))  
#define LODWORD(l)           ((DWORD)(__int64(l) & __int64(0xffffffff)))   
#define HIDWORD(l)           ((DWORD)(__int64(l) >> __int64(32)))   

typedef struct _PHEADB	// Packet Head Byte Normal / Extended [C1:C3]
{
	unsigned char uPacketType;
	unsigned char uSize;
	unsigned char uHead;

} PHEADB, PHEADBE, *LPHEADB, *LPHEADBE; 

typedef struct _PHEADSUBB	// Packet Sub Head Byte [C1:C3]
{
	unsigned char uPacketType;
	unsigned char uSize;
	unsigned char uHead;
	unsigned char uSubHead;

} PHEADSUBB, * LPPHEADSUBB;

typedef struct _PHEADW	// Packet Head Word / Extend [C2:C4]
{
	unsigned char uPacketType;
	unsigned char uSize[2];
	unsigned char uHead;

} PHEADW, * LPPHEADW;

typedef struct _PHEADSUBW	// Packed Sub Head Word [C2:C4]
{
	unsigned char uPacketType;
	unsigned char uSize[2];
	unsigned char uHead;
	unsigned char uSubHead;

} PHEADSUBW, *LPPHEADSUBW;

struct PBMSG_HEAD
{
public:
	void set ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 18
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 22

	void setE ( LPBYTE lpBuf, BYTE head, BYTE size)	// line : 25
	{
		lpBuf[0] = 0xC3;
		lpBuf[1] = size;
		lpBuf[2] = head;
	};	// line : 29

	BYTE c; //0
	BYTE size; //1
	BYTE headcode; //2
};

struct PWMSG_HEAD	// Packet - Word Type
{
public:

	void set( LPBYTE lpBuf, BYTE head, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	void setE( LPBYTE lpBuf, BYTE head, int size)	// line : 49
	{
		lpBuf[0] = 0xC4;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
	};

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
};



struct PBMSG_HEAD2	// Packet - Byte Type
{

public:

	void set( LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};

	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

struct PWMSG_HEAD2
{

public:

	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
	BYTE subcode;
};

struct PMSG_DEFAULT
{
	PBMSG_HEAD h;
};


struct PMSG_DEFAULT2
{
	PBMSG_HEAD h;
	BYTE subcode;
};

struct PMSG_TEST
{
	PWMSG_HEAD h;
	char testbuf[1996];	// 4
	int count;	// 7D0
};

struct PMSG_DEFRESULT
{
	PBMSG_HEAD h;
	BYTE result;	// 3
};

struct SDHP_SERVERINFO
{
	struct PBMSG_HEAD h;
	unsigned char Type;
	unsigned short Port;
	char ServerName[50];
	unsigned short ServerCode;
};

struct SDHP_RESULT
{
	struct PBMSG_HEAD h;
	unsigned char Result;
	unsigned long ItemCount;
};

struct CG_REQ_CHARACTER_CREATE
{
	PHEADSUBB PHeader;
	char szName[MAX_ACCOUNT_LEN];
	BYTE btCharacterType;
};

struct GC_TRADERESULT
{
	PHEADB PHeader;
	BYTE btResult;
};

struct GC_LEVELUP
{
	PHEADSUBB PHeader;
	WORD Level;
	WORD LevelUpPoint;
	WORD MaxLife;
	WORD MaxMana;
	WORD MaxBP;
	WORD AddPoint;
	WORD MaxAddPoint;
};
#endif