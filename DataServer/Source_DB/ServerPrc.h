#ifndef __SERVERPRC_H__
#define __SERVERPRC_H__


#include "Giocp.h"

#define MAX_SERVEROBJECT			100	// ���� ������Ʈ �ִ� ����



typedef struct
{
	int  Connected;		// ���ӵǾ� �ֳ�? 0 : ������ �ȵǾ� �ִ�.
						// 1 : ������ �Ǿ����� ���� ������ �ȵȻ���
	                    // 2 : ���� ������ �Ϸ�� ����
	char Ip[20];		// ���� �ּ�
	WORD Port;			// ������ ��� ��Ʈ��ȣ
	BYTE Type;			// ���� ���α׷��� Ÿ��
	char ServerName[51];

	WORD ServerCode;
	int pServer;
	int iMapSvrGroup;
	
	SOCKET m_socket;
	LPPER_SOCKET_CONTEXT	lpPerSocketContext;
	//PER_SOCKET_CONTEXT PerSocketContext;
} ServerObject_Struct, * LPServerObject_Struct;


extern void  gSObjInit();
extern short gSObjAdd(SOCKET socket, char *ip);
extern short gSObjDel(int index);
extern BOOL  gSObjSetInfo(int aIndex, WORD port, int type, char * servername, WORD ServerCode);
extern int gSObjIndexSerrchbyServerCode(WORD ServerCode);

extern ServerObject_Struct	gSObj[];

#endif
