#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__


#include "..\\include\\prodef.h"
#include "Sprodef.h"
//#include "User.h"

typedef struct
{
	PBMSG_HEAD h;
	int iUserIndex;
	char szCharName[MAX_IDSTRING];
} SDHP_REQ_QUEST_MONSTER_KILL, *LPSDHP_REQ_QUEST_MONSTER_KILL;

typedef struct 
{
	PBMSG_HEAD h;
	WORD wIndex;
	DWORD dwItemSerial;
	WORD wItemIndex;
}SDHP_LOAD_MEDALINFO,* LPSDHP_LOAD_MEDALINFO;

typedef struct
{
	PBMSG_HEAD h;
	int iUserIndex;
	char szCharName[MAX_IDSTRING+1];
}MLP_REQ_MASTERLEVEL_INFO, *LPMLP_REQ_MASTERLEVEL_INFO;

typedef struct
{
	PBMSG_HEAD h;
	char Name[MAX_IDSTRING];
	BYTE SkillKeyBuffer[20];
	BYTE GameOption;
	BYTE QkeyDefine;
	BYTE WkeyDefine;
	BYTE EkeyDefine;
	BYTE ChatWindow;
	BYTE RkeyDefine;
	int QWERLevel;
}SDHP_SKILLKEYDATA,*LPSDHP_SKILLKEYDATA;

typedef struct
{
	PBMSG_HEAD h;
	int aIndex;
	char Name[MAX_IDSTRING];
	BYTE SkillKeyBuffer[20];
	BYTE GameOption;
	BYTE QkeyDefine;
	BYTE WkeyDefine;
	BYTE EkeyDefine;
	BYTE ChatWindow;
	BYTE RkeyDefine;
	int QWERLevel;
}SDHP_SKILLKEYDATA_SEND,*LPSDHP_SKILLKEYDATA_SEND;

typedef struct
{
	PBMSG_HEAD h;
	BYTE x;
	BYTE y;
	BYTE MapNumber;
	DWORD m_Number;
	short Type;
	BYTE Level;
	BYTE Dur;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE NewOption;
	int aIndex;
	short lootindex;
	BYTE SetOption;
	DWORD dwTime;
	WORD wRemainTime;
	WORD wLevel;
	WORD wLevel_T;
	char szName[MAX_IDSTRING];
	char szName_T[MAX_IDSTRING];
	BYTE btClass;
	BYTE btClass_T;
	WORD wItemIndex;
}SDHP_PROPERTY_ITEMRECV,*LPSDHP_PROPERTY_ITEMRECV;

struct SDHP_DELETE_TEMPUSERINFO_RESULT 
{
	PBMSG_HEAD h;
	char CharName[MAX_IDSTRING+1];
};

typedef struct 
{
	PBMSG_HEAD h;
	unsigned short ServerCode;
	char CharName[MAX_IDSTRING+1];
}SDHP_DELETE_TEMPUSERINFO,* LPSDHP_DELETE_TEMPUSERINFO;

struct SDHP_CHARACTER_TRANSFER_RESULT 
{
	PBMSG_HEAD h;
	char Account[MAX_IDSTRING];
	short Number;
	BYTE Result;
};

typedef struct 
{
	PBMSG_HEAD h;
	char Account[MAX_IDSTRING];
	short Number;
}SDHP_CHARACTER_TRANSFER,* LPSDHP_CHARACTER_TRANSFER;

struct SDHP_PET_ITEMCREATERECV 
{
	PBMSG_HEAD h;
	BYTE x;
	BYTE y;
	BYTE MapNumber;
	DWORD m_Number;
	short Type;
	BYTE Level;
	BYTE Dur;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE NewOption;
	int aIndex;
	short lootindex;
	BYTE SetOption;
};

typedef struct
{
	PBMSG_HEAD h;
	BYTE x;
	BYTE y;
	BYTE MapNumber;
	short Type;
	BYTE Level;
	BYTE Dur;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE NewOption;
	int aIndex;
	short lootindex;
	BYTE SetOption;
}SDHP_PET_ITEMCREATE,*LPSDHP_PET_ITEMCREATE;

struct Recv_PetItem_Info 
{
	BYTE nPos;
	DWORD nSerial;
	BYTE Level;
	int Exp;
};

struct SDHP_RECV_PETITEM_INFO 
{
	PWMSG_HEAD h;
	char AccountID[MAX_IDSTRING+1];
	WORD Number;
	BYTE InvenType;
	BYTE nCount;
};

typedef struct
{
	BYTE nPos;
	DWORD nSerial;
}Request_PetItem_Info,* LPRequest_PetItem_Info;

typedef struct
{
	PWMSG_HEAD h;
	char AccountID[MAX_IDSTRING+1];
	WORD Number;
	BYTE InvenType;
	BYTE nCount;
}SDHP_REQUEST_PETITEM_INFO,*LPSDHP_REQUEST_PETITEM_INFO;

typedef struct
{
	PWMSG_HEAD h;
	BYTE nCount;
}SDHP_SAVE_PETITEM_INFO,*LPSDHP_SAVE_PETITEM_INFO;

typedef struct
{
	DWORD nSerial;
	BYTE Level;
	int Exp;
}Save_PetItem_Info, *LPSave_PetItem_Info;

struct CSP_ANS_CASTLEDATA 
{
	PBMSG_HEAD2 h;
	int iResult;
	WORD wMapSvrNum;
	WORD wStartYear;
	BYTE btStartMonth;
	BYTE btStartDay;
	WORD wEndYear;
	BYTE btEndMonth;
	BYTE btEndDay;
	BYTE btIsSiegeGuildList;
	BYTE btIsSiegeEnded;
	BYTE btIsCastleOccupied;
	char szCastleOwnGuild[MAX_GUILDNAMESTRING];
	__int64 i64CastleMoney;
	int iTaxRateChaos;
	int iTaxRateStore;
	int iTaxHuntZone;
	int iFirstCreate;
};
typedef struct
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
	int iCastleEventCycle;
}CSP_REQ_CASTLEDATA,*LPCSP_REQ_CASTLEDATA;

typedef struct
{
	PBMSG_HEAD2 h;
	WORD wMapSvrNum;
	int iIndex;
}CSP_REQ_OWNERGUILDMASTER,*LPCSP_REQ_OWNERGUILDMASTER;



typedef struct
{
	PBMSG_HEAD h;
	int aIndex;
	char AccountId[MAX_IDSTRING];
	char OldName[MAX_IDSTRING];
	char NewName[MAX_IDSTRING];
}SDHP_CHANGE_NAME,*LPSDHP_CHANGE_NAME;

typedef struct
{
	PBMSG_HEAD h;
	char AccountId[MAX_IDSTRING+1];
	short Number;
}SDHP_REQ_SETACCOUNTINFO,*LPSDHP_REQ_SETACCOUNTINFO;


typedef struct _tagMessageSystemBroadcast
{
	PWMSG_HEAD	h;
	BYTE		btSize;
	char		szMessage[MAX_CHAT];
} MSG_SYS_BROADCAST, *LPMSG_SYS_BROADCAST;
//------------
//	Wcoin Struct
//------------
typedef struct  
{
	PBMSG_HEAD h;
	int iUserIndex;
	char Accaunt[11];
	int Count;
	int Type;
}REQ_WCOIN_INFO, *LPREQ_WCOIN_INFO;

typedef struct  
{
	PBMSG_HEAD h;
	byte btResult;
	int iUserIndex;
	int iCount;
	int Type;
}ANS_WCOIN_INFO, *LPANS_WCOIN_INFO;

//----------------------------------------------------------------------------
extern void ProtocolCore(BYTE protoNum, BYTE *aRecv, int aLen, short aIndex);

//----------------------------------------------------------------------------

#endif