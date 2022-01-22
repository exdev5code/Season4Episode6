#ifndef __SPRODEF_H__
#define __SPRODEF_H__

#include "..\\Include\\ProDef.h"
//----------------------------------------------------------------------------
// ��� ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	BYTE	Result;
} SDHP_DEFAULT_RESULT, *LPSDHP_DEFAULT_RESULT;


//----------------------------------------------------------------------------
// ����� ������ ��� 
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	DWORD		ItemCount;
} SDHP_RESULT, *LPSDHP_RESULT;

//----------------------------------------------------------------------------
// [0x00] ������ ���� ������ ������ ���
//----------------------------------------------------------------------------
typedef struct 
{	
	PBMSG_HEAD	h;
		
	BYTE			Type;		// 0:Join Server, 1:MapServer 2: ManagerServer
	unsigned short	Port;		// Server Port Number
	char			ServerName[50];
	unsigned short	ServerCode;
} SDHP_SERVERINFO, * LPSDHP_SERVERINFO;

//----------------------------------------------------------------------------
// [0x20] ���Ӽ����� ������ �����ͼ����� ������ �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	DWORD		ItemCount;
} SDHP_GAMESERVERINFO, *LPSDHP_GAMESERVERINFO;

//----------------------------------------------------------------------------
// DB ������ ĳ���� ����Ʈ�� �޶�� ��û
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	//int			UserNumber;	// ���� ���� ��ȣ 
	char		Id[MAX_IDSTRING];
	short		Number;	// ���� ���� ������ȣ	
} SDHP_GETCHARLIST, *LPSDHP_GETCHARLIST;

//----------------------------------------------------------------------------
// ĳ���� ����Ʈ ī��Ʈ  (2����Ʈ ũ�⸦ ���)
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;
	short		Number;
	BYTE		Count;
	int			DbNumber;
	BYTE		GenerableClass;		// ���˻縦 ����� �ִ� ��������..
	char		AccountId[MAX_IDSTRING+1];
	BYTE		MoveCnt;
} SDHP_CHARLISTCOUNT, *LPSDHP_CHARLISTCOUNT;

//----------------------------------------------------------------------------
// [0x02] ���� ���� ��û�� ĳ���� ����(ī���� ��ŭ �ݺ���)
// [0xF3][0x00]
//----------------------------------------------------------------------------
typedef struct
{
	BYTE Index;
	char Name[MAX_IDSTRING];
	WORD Level;
	BYTE Class;
	BYTE CtlCode;
	BYTE dbInventory[48];
	BYTE DbVersion;
	BYTE btGuildStatus;
} SDHP_CHARLIST, * LPSDHP_CHARLIST;


//----------------------------------------------------------------------------
// [0x03] ���� ���� ���� �޽���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char CharName[MAX_IDSTRING];
	char GuildName[MAX_GUILDNAMESTRING];
	BYTE Type;
} SDHP_USERCLOSE, *LPSDHP_USERCLOSE;

//----------------------------------------------------------------------------
// [0x04] ĳ���� ����� �� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;	
	int         UserNumber;
	int			DBNumber;
	short		Number;
	char        AccountId[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	BYTE		ClassSkin;
} SDHP_CREATECHAR, *LPSDHP_CREATECHAR;

//----------------------------------------------------------------------------
// [0x04] ĳ���� ����� �� ��� �����µ� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;	
	BYTE		Result;
	short		Number;
	char		AccountId[MAX_IDSTRING];
	char        Name[MAX_IDSTRING];
	BYTE		Pos;
	BYTE		ClassSkin;
	BYTE		Equipment[24];	// �����ϰ� �ִ� ���
	WORD		Level;
} SDHP_CREATECHARRESULT, *LPSDHP_CREATECHARRESULT;

//----------------------------------------------------------------------------
// 0x05 ���Ӽ����� ĳ���� ���� ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	short		Number;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	BYTE		Guild;
	char		GuildName[MAX_GUILDNAMESTRING];
} SDHP_CHARDELETE, *LPSDHP_CHARDELETE;

//----------------------------------------------------------------------------
// 0x05 ĳ���� ���� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
	short		Number;
	char		AccountID[MAX_IDSTRING];

} SDHP_CHARDELETERESULT, *LPSDHP_CHARDELETERESULT;

//----------------------------------------------------------------------------
// 0x06 ���Ӽ����� ������ ������ ĳ���� ������ ��û
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD  h;	
	char    AccountID[MAX_IDSTRING+1];
	char	Name[MAX_IDSTRING+1];
	short	Number;
} SDHP_DBCHARINFOREQUEST, *LPSDHP_DBCHARINFOREQUEST;


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------








//----------------------------------------------------------------------------
// 0x06 ĳ���� ���� ��û ��� 
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD h;
	BYTE result;
	short Number;
	char AccountID[MAX_IDSTRING];
	char Name[MAX_IDSTRING+1];
	BYTE Class;
	short Level;
	int LevelUpPoint;
	int Exp;
	int NextExp;
	int Money;
	short Str;
	short Dex;
	short Vit;
	short Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	BYTE dbInventory[MAX_DBINVENTORY];//3776
	BYTE dbMagicList[MAX_DBMAGIC];//450
	BYTE MapNumber;
	BYTE MapX;
	BYTE MapY;
	BYTE Dir;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE CtlCode;
	BYTE DbVersion;
	BYTE AccountCtlCode;
	BYTE dbQuest[MAX_QUEST];
	WORD Leadership;
	WORD ChatLitmitTime;
	int iFruitPoint;

} SDHP_DBCHAR_INFORESULT, *LPSDHP_DBCHAR_INFORESULT;

//----------------------------------------------------------------------------
// 0x07 ĳ���� ���� ���� 
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD h;
	char Name[MAX_IDSTRING+1];
	short Level;
	BYTE Class;
	int LevelUpPoint;
	int Exp;
	int NextExp;
	int Money;
	short Str;
	short Dex;
	short Vit;
	short Energy;
	WORD Life;
	WORD MaxLife;
	WORD Mana;
	WORD MaxMana;
	BYTE dbInventory[MAX_DBINVENTORY];
	BYTE dbMagicList[MAX_DBMAGIC];
	BYTE MapNumber;
	BYTE MapX;
	BYTE MapY;
	BYTE Dir;
	int PkCount;
	int PkLevel;
	int PkTime;
	BYTE dbQuest[MAX_QUEST];
	BYTE CharInfoSave;
	WORD Leadership;
	WORD ChatLitmitTime;
	int iFruitPoint;

} SDHP_DBCHAR_INFOSAVE, *LPSDHP_DBCHAR_INFOSAVE;

// [0x08] â�� �ִ� �������� ��û�Ѵ�.
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
} SDHP_GETWAREHOUSEDB, *LPSDHP_GETWAREHOUSEDB;

// [0x08] â�� �ִ� ������ ����Ʈ�� �����Ѵ�.
// [0x09] â�� �������� �����Ѵ�.
typedef struct
{
	PWMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
	int			Money;
	BYTE		dbItems[MAX_WAREHOUSEDBSIZE];
	BYTE		DbVersion;
	short		pw;
} SDHP_GETWAREHOUSEDB_SAVE, *LPSDHP_GETWAREHOUSEDB_SAVE;


// [0x10] â�� ���� �������� ����. 
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
} SDHP_GETWAREHOUSEDB_RESULT, *LPSDHP_GETWAREHOUSEDB_RESULT;


// [0x11] ĳ������ �������� �����Ѵ�.
typedef struct
{
	PWMSG_HEAD	h;
	
	char  Name[MAX_IDSTRING];	// �̸�
	BYTE  dbInventory[MAX_DBINVENTORY];	// ������ �κ��丮
} SDHP_DBCHAR_ITEMSAVE, *LPSDHP_DBCHAR_ITEMSAVE;

// [0x12] â�� ���� �����Ѵ�.
typedef struct
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	short		aIndex;
	int			Money;
} SDHP_WAREHOUSEMONEY_SAVE, *LPSDHP_WAREHOUSEMONEY_SAVE;


/*
//----------------------------------------------------------------------------
// [0x10] ���Ӽ������� ����� ���� ���� ��û
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
	char	Pass[MAX_IDSTRING];
	char	Name[MAX_IDSTRING];
	char	JoominN[MAX_JOOMINNUMBERSTR];
	char	Question[MAX_QUESTIONSTR];
	char	Answer[MAX_ANSWERSTR];
	char	PhoneN[MAX_PHONENUMBERSTR];
	char	Email[MAX_EMAILSTR];
	char    IpAddress[17];
} SDHP_ACCOUNTREQUEST, *LPSDHP_ACCOUNTREQUEST;

//----------------------------------------------------------------------------
// [0x10] ���Ӽ������� ����� ���� ���� ���
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		result;
	short		Number;
} SDHP_ACCOUNTRESULT, *LPSDHP_ACCOUNTRESULT;
*/

//----------------------------------------------------------------------------
// [0x20] Ư�����̵��� ��������� ����� ��û�Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
} SDHP_PASSQUESTION_QUERY, *LPSDHP_PASSQUESTION_QUERY;

//----------------------------------------------------------------------------
// [0x20] Ư�����̵��� ��������� ����� ��û�Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
	char	Question[MAX_QUESTIONSTR];
} SDHP_PASSQUESTION_QUERY_RESULT, *LPSDHP_PASSQUESTION_QUERY_RESULT;


//----------------------------------------------------------------------------
// [0x21] ��й�ȣ ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
	char	JoominN[MAX_JOOMINNUMBERSTR];
	char	Answer[MAX_ANSWERSTR];
	char    IpAddress[17];
} SDHP_PASSQUERY, *LPSDHP_PASSQUERY;

//----------------------------------------------------------------------------
// [0x21] ��й�ȣ ���� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
	char	Password[MAX_IDSTRING];
} SDHP_PASSQUERY_RESULT, *LPSDHP_PASSQUERY_RESULT;


//----------------------------------------------------------------------------
// [0x22] ��й�ȣ �����û
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	char	Id[MAX_IDSTRING];
	char	PassOld[MAX_IDSTRING];
	char	PassNew[MAX_IDSTRING];
	char	JoominN[MAX_JOOMINNUMBERSTR];	
	char	IpAddress[17];
} SDHP_PASSCHANGE, *LPSDHP_PASSCHANGE;


//----------------------------------------------------------------------------
// [0x22] ��й�ȣ �����û ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	short	Number;
	BYTE	Result;
} SDHP_PASSCHANGE_RESULT, *LPSDHP_PASSCHANGE_RESULT;

//----------------------------------------------------------------------------
// [0x30] ��带 �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		Master[MAX_IDSTRING+1];
	BYTE		Mark[32];
	BYTE		NumberH;
	BYTE		NumberL;
} SDHP_GUILDCREATE, *LPSDHP_GUILDCREATE;

//----------------------------------------------------------------------------
// ��� ���� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	DWORD		GuildNumber;
	
	BYTE		NumberH;
	BYTE		NumberL;
	char		Master[MAX_IDSTRING+1];
	char		GuildName[MAX_GUILDNAMESTRING+1];
	BYTE		Mark[32];
	
} SDHP_GUILDCREATE_RESULT, *LPSDHP_GUILDCREATE_RESULT;

//----------------------------------------------------------------------------
// [0x31] ��� ����
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;

	BYTE		NumberH;
	BYTE		NumberL;
	
	char		GuildName[MAX_GUILDNAMESTRING];
	char		Master[MAX_IDSTRING];
} SDHP_GUILDDESTROY, *LPSDHP_GUILDDESTROY;

//----------------------------------------------------------------------------
// [0x31] ��� ���� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		Master[MAX_IDSTRING+1];
} SDHP_GUILDDESTROY_RESULT, *LPSDHP_GUILDDESTROY_RESULT;

//----------------------------------------------------------------------------
// [0x32] ��� ��� �߰�
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		MemberID[MAX_IDSTRING+1];
	BYTE		NumberH;
	BYTE		NumberL;
} SDHP_GUILDMEMBERADD, *LPSDHP_GUILDMEMBERADD;

//----------------------------------------------------------------------------
// [0x32] ��� ��� �߰� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;

	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		MemberID[MAX_IDSTRING+1];

} SDHP_GUILDMEMBERADD_RESULT, *LPSDHP_GUILDMEMBERADD_RESULT;

//----------------------------------------------------------------------------
// [0x33] ����� ���� 
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING];
	char		MemberID[MAX_IDSTRING];
} SDHP_GUILDMEMBERDEL, *LPSDHP_GUILDMEMBERDEL;

//----------------------------------------------------------------------------
// [0x33] ����� ���� ���
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	
	BYTE		Result;
	BYTE		Flag;

	BYTE		NumberH;
	BYTE		NumberL;

	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		MemberID[MAX_IDSTRING+1];

} SDHP_GUILDMEMBERDEL_RESULT, *LPSDHP_GUILDMEMBERDEL_RESULT;


//----------------------------------------------------------------------------
// [0x34] ��� ���� ���� 
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		Master[MAX_IDSTRING+1];
	BYTE		Mark[32];
	int			Score;
	BYTE		Count;
} SDHP_GUILDUPDATE, *LPSDHP_GUILDUPDATE;

//----------------------------------------------------------------------------
// [0x35] ĳ���Ͱ� ���ӿ� ���ӽ� ��� ������ ������.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		MemberID[MAX_IDSTRING+1];
} SDHP_GUILDMEMBER_INFO, *LPSDHP_GUILDMEMBER_INFO;


//----------------------------------------------------------------------------
// [0x36] ��帶���Ͱ� �������� �� ���� ������ �������Ѵ�.
//----------------------------------------------------------------------------
typedef struct
{
	PWMSG_HEAD	h;

	char		GuildName[MAX_GUILDNAMESTRING+1];
	BYTE		Count;
} SDHP_GUILDALL_COUNT, *LPSDHP_GUILDALL_COUNT;

//----------------------------------------------------------------------------
// [0x36] ��帶���Ͱ� �������� �� ���� ������ �������Ѵ�.
//----------------------------------------------------------------------------
typedef struct
{
	char		MemberID[MAX_IDSTRING+1];
} SDHP_GUILDALL, *LPSDHP_GUILDALL;

//----------------------------------------------------------------------------
// [0x37] ��� ���ھ� ������Ʈ 
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	int			Score;
} SDHP_GUILDSCOREUPDATE, *LPSDHP_GUILDSCOREUPDATE;

//----------------------------------------------------------------------------
// [0x38] ��� ���� ����
//----------------------------------------------------------------------------
typedef struct
{
	PBMSG_HEAD	h;
	char GuildName[MAX_GUILDNAMESTRING+1];
	char szGuildNotice[MAX_GUILDNOTICE];
} SDHP_GUILDNOTICE, *LPSDHP_GUILDNOTICE;

//----------------------------------------------------------------------------
// [0x40] ��带 �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	WORD		Number;
	char		GuildName[MAX_GUILDNAMESTRING+1];
	char		Master[MAX_IDSTRING+1];
	BYTE		Mark[32];
	int			score;
} SDHP_GUILDCREATED, *LPSDHP_GUILDCREATED;

//----------------------------------------------------------------------------
// [0x50] �̺�Ʈ ZEN�� �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	int			Total;
	int			Number;
} SDHP_ZENSAVE, *LPSDHP_ZENSAVE;

//----------------------------------------------------------------------------
// [0x50] �̺�Ʈ ZEN�� �о�´�.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	char		AccountID[MAX_IDSTRING];
	int			Total;
	int			Number;
} SDHP_ZENLOAD, *LPSDHP_ZENLOAD;

//----------------------------------------------------------------------------
// [0x52] ������ ��ȣ�� �ο��޴´�.
//----------------------------------------------------------------------------
// MapNumber �� 255 �϶��� ī���� �ڽ��̴�.
typedef struct 
{
	PBMSG_HEAD	h;
	BYTE		x;
	BYTE		y;
	BYTE		MapNumber;
	short		Type;
	BYTE		Level;
	BYTE		Dur;
	BYTE		Op1;
	BYTE		Op2;
	BYTE		Op3;
	BYTE		NewOption;
	int			aIndex;
	short		lootindex;
	BYTE		SetOption;
} SDHP_ITEMCREATE, *LPSDHP_ITEMCREATE;

//----------------------------------------------------------------------------
// [0x52] ������ ��ȣ�� �ο��޴´�.
//----------------------------------------------------------------------------
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
} SDHP_ITEMCREATERECV, *LPSDHP_ITEMCREATERECV;


//----------------------------------------------------------------------------
// [0x53] ������ �̵� ��θ� �����Ѵ�.
//----------------------------------------------------------------------------
typedef struct 
{

	PBMSG_HEAD	h;
	DWORD		Serial;
	char		ServerName[20];
	char		Account[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
	char		ItemName[21];
	BYTE		X;
	BYTE		Y;
	BYTE		ItemLevel;
	BYTE		ItemOp1;
	BYTE		ItemOp2;
	BYTE		ItemOp3;

} SDHP_ITEMMOVESAVE, *LPSDHP_ITEMMOVESAVE;

//----------------------------------------------------------------------------
// [0x60] �̺�Ʈ ������ �˸���.
//----------------------------------------------------------------------------
typedef struct 
{
	PBMSG_HEAD	h;
	BYTE		Event;	
} SDHP_EVENTSTART, *LPSDHP_EVENTSTART;

// 0x30
typedef struct
{
	PBMSG_HEAD	h;
	char		Account[MAX_IDSTRING];
	char		Name[MAX_IDSTRING];
} SDHP_LOVEHEARTEVENT, * LPSDHP_LOVEHEARTEVENT;

// 0x30
typedef struct
{
	PBMSG_HEAD	h;

	BYTE		Result;

	char		Name[MAX_IDSTRING];
	int			Number;
	
} SDHP_LOVEHEARTEVENT_RESULT, * LPSDHP_LOVEHEARTEVENT_RESULT;

// 0x40 ��ü ����
typedef struct
{
	PBMSG_HEAD	h;
	char		Notice[61];
} SDHP_NOTICE, *LPSDHP_NOTICE;

// 0x41 ���� ����
typedef struct
{
	PBMSG_HEAD	h;
	char		szId[MAX_IDSTRING];
	char		Notice[61];
} SDHP_USER_NOTICE, *LPSDHP_USER_NOTICE;


// 0x42 ���� ��
typedef struct
{
	PBMSG_HEAD	h;
	int		ClientIndex;
	char	AccountID[MAX_IDSTRING];
	BYTE	ServerNum;
	char	CharName[MAX_IDSTRING];
	BYTE	Type;
} SDHP_GAME_BLOCK, *LPSDHP_GAME_BLOCK;

// 0x42 ���� �� ���
typedef struct
{
	PBMSG_HEAD	h;
	BYTE		Result;
} SDHP_GAME_BLOCK_RESULT, *LPSDHP_GAME_BLOCK_RESULT;

#endif


