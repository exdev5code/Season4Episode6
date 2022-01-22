#ifndef GIOCP_H
#define GIOCP_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define HIDE_ERRORL10
#if(TRAFIC_FIX==TRUE)
//#define MAX_EXSENDBUF_SIZE		21072
//#define MAX_IO_BUFFER_SIZE		18000
#define MAX_EXSENDBUF_SIZE		70240
#define MAX_IO_BUFFER_SIZE		60000
#define MAX_IO_THREAD_HANDLES	100
#else
#define MAX_EXSENDBUF_SIZE		7024
#define MAX_IO_BUFFER_SIZE		6000
#define MAX_IO_THREAD_HANDLES	16
#endif

typedef struct _PER_IO_CONTEXT
{
	OVERLAPPED					Overlapped;
	WSABUF						wsabuf;
	CHAR						Buffer[MAX_IO_BUFFER_SIZE];
	CHAR						BufferSecond[MAX_IO_BUFFER_SIZE];
	int							nSecondOfs;
	int							nTotalBytes;
	int							nSentBytes;
	int 						IOOperation;
	int  						nWaitIO;			// IO 작업을 진행했다면.. 기다리게 알린다.
} PER_IO_CONTEXT, * LPPER_IO_CONTEXT;

typedef struct _PER_SOCKET_CONTEXT
{
	SOCKET			m_socket;
	int				nIndex;
	_PER_IO_CONTEXT	IOContext[2];			// 0 : recv, 1 : send
	int 			dwIOCount;

} PER_SOCKET_CONTEXT, *LPPER_SOCKET_CONTEXT;



extern LPBYTE ExSendBuf;
extern int g_ServerPort;
extern HANDLE g_IocpThreadHandle;
extern HANDLE g_ThreadHandles[MAX_IO_THREAD_HANDLES];
extern CRITICAL_SECTION criti;
extern enum SOCKET_FLAG;
extern DWORD g_dwThreadCount;
extern HANDLE g_CompletionPort;	
extern SOCKET g_Listen;



void GiocpInit();
void GiocpDelete();
BOOL HackToolCheck(BYTE headcode, int size, int uIndex, BYTE xcode);
int CreateGIocp(int server_port);
void DestroyGIocp();
int CreateListenSocket();
DWORD	WINAPI IocpServerWorker(LPVOID p);
DWORD   WINAPI ServerWorkerThread(LPVOID CompletionPortID);
BOOL RecvDataParse(LPPER_IO_CONTEXT	lpIOContext, int uIndex);
int DataSend(int aIndex, LPBYTE lpMsg, DWORD dwSize);
int IoSendSecond(LPPER_SOCKET_CONTEXT lpPerSocketContext);
int IoMoreSend(LPPER_SOCKET_CONTEXT lpPerSocketContext);
BOOL UpdateCompletionPort(SOCKET sd, int ClientIndex, BOOL bAddToList);
void CloseClient(LPPER_SOCKET_CONTEXT lpPerSocketContext, BOOL bGraceful);
void CloseClient(int index);
void ResponErrorCloseClient(int index);



#endif