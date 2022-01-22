#ifndef GUILDCLASS_H
#define GUILDCLASS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef BYTE GUILDMARK[32];

#define MAX_USER_GUILD			80
#define MAX_GUILD_NOTICE_LEN	60
#define MAX_WC_GUILD_NOTICE_LEN	(MAX_GUILD_NOTICE_LEN/2)
#define MIN_GUILD_COUNT_FOR_CS	20

#define GUILD_MASTER		0x80
#define GUILD_ASSISTANT		0x40
#define GUILD_BATTLE_MASTER	0x20
#define GUILD_NORMAL_USER	0x00

#define GUILD_RELATION_UNION	0x01
#define GUILD_RELATION_RIVAL	0x02


enum GUILD_NOTIFICATION
{
	G_NOTIFICATION_SET = 0x1,
	G_NOTIFICATION_UNION_BREAKOFF = 0x10,
};

enum GUILD_OPERATION_ERRORCODE
{
	G_ERROR_NONE = 0x0,
};

enum GUILD_RELATION_OPERATION
{
	G_RELATION_OPERATION_JOIN = 0x1,
	G_RELATION_OPERATION_BREAKOFF = 0x2,
};

enum GUILD_RELATIONSHIP {
	G_RELATIONSHIP_NONE = 0x0,
	G_RELATIONSHIP_UNION = 0x1,
	G_RELATIONSHIP_RIVAL = 0x2,
	G_RELATIONSHIP_UNIONMASTER = 0x4,
	G_RELATIONSHIP_RIVALMASTER = 0x8,
};

enum GUILD_TYPE
{
	G_TYPE_NONE = 0xff,
	G_TYPE_COMMON = 0x0,
	G_TYPE_GUARD = 0x1,
};

enum GUILD_STATUS
{
	G_NONE = 0xff,
	G_PERSON = 0x0,
	G_MASTER = 0x80,
	G_SUB_MASTER = 0x40,
	G_BATTLE_MASTER = 0x20,
};

enum GUILD_REQ_COMMON_RESULT
{
	GUILD_ANS_NOTEXIST_GUILD = 0x10,
	GUILD_ANS_UNIONFAIL_BY_CASTLE = 0x10,
	GUILD_ANS_NOTEXIST_PERMISSION = 0x11,
	GUILD_ANS_NOTEXIST_EXTRA_STATUS = 0x12,
	GUILD_ANS_NOTEXIST_EXTRA_TYPE = 0x13,
	GUILD_ANS_EXIST_RELATIONSHIP_UNION = 0x15,
	GUILD_ANS_EXIST_RELATIONSHIP_RIVAL = 0x16,
	GUILD_ANS_EXIST_UNION = 0x17,
	GUILD_ANS_EXIST_RIVAL = 0x18,
	GUILD_ANS_NOTEXIST_UNION = 0x19,
	GUILD_ANS_NOTEXIST_RIVAL = 0x1a,
	GUIDL_ANS_NOT_UNION_MASTER = 0x1b,
	GUILD_ANS_NOT_GUILD_RIVAL = 0x1c,
	GUILD_ANS_CANNOT_BE_UNION_MASTER = 0x1d,
	GUILD_ANS_EXCEED_MAX_UNION_MEMBER = 0x1e,
	GUILD_ANS_CANCLE_REQUEST = 0x20,
};


struct _GUILD_INFO_STRUCT
{
	int Number;
	char Name[9];
	BYTE Mark[32];
	BYTE Count;
	BYTE TotalCount;
	char Names[MAX_USER_GUILD][11];
	short Index[MAX_USER_GUILD];
	BYTE Use[MAX_USER_GUILD];
	char pServer[MAX_USER_GUILD];
	char TargetGuildName[9];
	short TargetIndex[MAX_USER_GUILD];
	struct _GUILD_INFO_STRUCT* lpTargetGuildNode;
	BYTE WarDeclareState;
	BYTE WarState;
	BYTE WarType;
	BYTE BattleGroundIndex;
	BYTE BattleTeamCode;
	BYTE PlayScore;
	int TotalScore;
	char Notice[60];
	int GuildStatus[MAX_USER_GUILD];
	BYTE btGuildType;
	int iGuildUnion;
	int iGuildRival;
	int iTimeStamp;
	char szGuildRivalName[9];

	struct OBJECTSTRUCT* lpLifeStone;
	int btLifeStoneCount;

	struct _GUILD_INFO_STRUCT* back;
	struct _GUILD_INFO_STRUCT* next;

	_GUILD_INFO_STRUCT(){return;};
	int  GetGuildUnion(){return this->iGuildUnion;};
	int  GetGuildRival(){return this->iGuildRival;};

	void SetGuildUnion(int iGuildNumber);
	void SetGuildRival(int iGuildNumber);
	void SetTimeStamp();

	int GetTimeStamp()
	{
		return this->iTimeStamp;
	};

	BOOL CheckTimeStamp(int iTime)
	{
		return (iTime == this->iTimeStamp )? TRUE : FALSE;
	}
};

class CGuildClass
{

public:

	CGuildClass();
	virtual ~CGuildClass();
	
	void Init();
	_GUILD_INFO_STRUCT* AddGuild(int number, LPSTR guildname, LPBYTE mark, LPSTR mastername,  int score);
	_GUILD_INFO_STRUCT* AddMember(_GUILD_INFO_STRUCT* pNode, LPSTR player_name, int aIndex, int totalcount, int pServer);
	_GUILD_INFO_STRUCT* AddMember(LPSTR guild_name, LPSTR player_name, int aIndex, int totalcount, int iGuildStatus,  int pServer);
	int GetGuildMemberStatus(LPSTR szGuildName, LPSTR szMemberName);
	int SetGuildMemberStatus(LPSTR szGuildName, LPSTR szMemberName, int iGuildStatus);
	int GetGuildType(LPSTR szGuildName);
	int SetGuildType(LPSTR szGuildName, int iGuildType);
	int BuildMemberTotal(_GUILD_INFO_STRUCT* lpNode);
	int DelMember(LPSTR guild_name, LPSTR player_name);
	void AddTail(_GUILD_INFO_STRUCT* pNewNode);
	int DeleteGuild(LPSTR guildname, LPSTR commader);
	void AllDelete();
	void Print();
	void PrintGuild(LPSTR guildname);
	int ConnectUser(_GUILD_INFO_STRUCT* lpNode, LPSTR guild_name, LPSTR player_name,  int aIndex, int pServer);
	int SetServer(LPSTR guild_name, LPSTR player_name, int pServer);
	_GUILD_INFO_STRUCT* SearchGuild(LPSTR guildname);
	_GUILD_INFO_STRUCT* SearchGuild_Number(int number);
	_GUILD_INFO_STRUCT* SearchGuild_NumberAndId(int number, LPSTR name);
	int CloseMember(LPSTR guild_name, LPSTR player_name);

private:
	_GUILD_INFO_STRUCT* head;
	_GUILD_INFO_STRUCT* tail;
	std::map<std::string,_GUILD_INFO_STRUCT *> m_GuildMap;
	std::map<int,_GUILD_INFO_STRUCT *> m_GuildNumberMap;
};

BOOL gGuildNoticeStringCheck(LPSTR notice);

#endif