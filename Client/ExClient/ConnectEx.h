#pragma once
// ----------------------------------------------------------------------------------------------


/*
00663C31 - функция с коннект пакетом
*/

#include "Protocol.h"

#define pPartyMemberCount		*(DWORD*)0x7C13BE8

#define pPlayerState			*(int*)0x8D6F7C

#ifdef exRECONNECT

#if(v103K)

#define pOnLine					*(DWORD*)0x80A815C	

#define oGetAccountInfo			0x0040BD05
#define oDisconnectEvent		0x005F853D
#define oMenuExit				0x007107A5

#define oUserPreviewStruct		*(int*)0x7A723B8

#endif

#if(v103Y)

#define pOnLine					*(DWORD*)0x81AB95C	
#define pPartyMemberCount		*(DWORD*)0x7D16468

#define oGetAccountInfo			0x0040C9B5

#define oDisconnectEvent		0x00617F7D
#define oMenuExit				0x0074832B

#define pPShopThis1				((LPVOID(__cdecl*)()) 0x007B708C)
#define pPShopThis2				((LPVOID(__thiscall*)(LPVOID This)) 0x007B7233)
#define pPShopSet				((void(__thiscall*)(LPVOID This, BYTE Mode)) 0x00799EEB)
#define pPShopRefresh			((void(__cdecl*)(int Preview)) 0x00411803)

#endif

#if(v104D)

#define pOnLine					*(DWORD*)0x8793704
#define pPartyMemberCount		*(DWORD*)0x81F6B6C

#define oGetAccountInfo			0x0040B903

#define oDisconnectEvent		0x004D035A
#define oMenuExit				0x007A889B

#define pPShopThis1				((LPVOID(__cdecl*)()) 0x860FC0)
#define pPShopThis2				((LPVOID(__thiscall*)(LPVOID This)) 0x8612B0)
#define pPShopSet				((void(__thiscall*)(LPVOID This, BYTE Mode)) 0x840E20)
#define pPShopRefresh			((void(__cdecl*)(int Preview)) 0x00668460)
#endif



#define DEBUG_RECONNECT			1


#define NORM_DC		0
#define OFFZEN_DC	1
#define OFFWCOIN_DC	2
#define OFFPC_DC	3
#define OFFCR_DC	4
#define OFFAFK_DC	20

// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CONNECTEX_LOGIN
{
	PBMSG_HEAD2	h;
	char		AccountID[10];
	char		Password[10];
	char		Name[10];
	DWORD		TickCount;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct PMSG_ANS_SERVER_INFO
{
	PBMSG_HEAD2 h;
	char		Ip[16];
	WORD		Port;
};
#pragma pack(pop)
// ----------------------------------------------------------------------------------------------

#pragma pack(push, 1)
struct CONNECTEX_CLOSE
{
	PBMSG_HEAD2	h;
};
#pragma pack(pop)

namespace ConnectExType
{
	enum T
	{
		OnLine				= 0,
		OnReconnect			= 1,
		OnForceDisconnect	= 2,
	};
};
// ----------------------------------------------------------------------------------------------

class ConnectEx
{
public:
	void	Load();
	void	Run();
	// ----
	void	ClearGame();
	void	RestoreGame();
	// ----
	void	DrawProgres();
	void	LoginReq();
	void	Reconnect();
	void	Relogin();
	void	Disconnect();
	// ----
	int		m_ConnectState;
	char	m_AccountID[11];
	char	m_Password[21];
	// ----
	char	m_CSIP[16];
	WORD	m_CSPort;
	char	m_GSIP[16];
	WORD	m_GSPort;
private:
	// ----
	DWORD	m_LastSendTick;
	DWORD	m_ReconnectTick;
	bool	m_WantMUHelper;
	// ----
}; extern ConnectEx gConnectEx;
// ----------------------------------------------------------------------------------------------

#endif