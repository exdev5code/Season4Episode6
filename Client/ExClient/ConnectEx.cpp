#include "stdafx.h"
#include "ConnectEx.h"
//#include "Import.h"
#include "TMemory.h"
#include "Protocol.h"
//#include "User.h"
#include "Interface.h"
#include "Player.h"

#include "Console.h"

#ifdef exRECONNECT
// ----------------------------------------------------------------------------------------------

ConnectEx gConnectEx;
// ----------------------------------------------------------------------------------------------

DWORD GetAccountInfo_Buff;
DWORD GetAccountInfo_Buff2;
DWORD DisconnectExcept_Buff;
DWORD DisconnectEvent_Buff;
DWORD MenuExit_Buff;
int Counter;
// ----------------------------------------------------------------------------------------------

Naked(GetAccountInfo)
{
	_asm
	{
		lea ecx, [ebp-0x18]
		mov GetAccountInfo_Buff, ecx
#if(v104D)
		lea ecx, [ebp-0x30]
#endif
#if(v103Y)
		lea ecx, [ebp-0x24]
#endif
#if(v103K)
		lea ecx, [ebp-0x24]
#endif
		mov GetAccountInfo_Buff2, ecx
	}
	// ----
	memcpy(gConnectEx.m_AccountID, (char*)GetAccountInfo_Buff, 10);
	memcpy(gConnectEx.m_Password, (char*)GetAccountInfo_Buff2, 20);

#if(v104D)
	*(DWORD*)0x8793714 = 1;
#endif
#if(v103Y)
	*(DWORD*)0x81AB96C = 1;
#endif
#if(v103K)
	*(DWORD*)0x80A816C = 1;
	
#endif
	// ----
	_asm
	{
#if(v103Y)
		mov GetAccountInfo_Buff, 0x0040C9BF
#endif
#if(v104D)
		mov GetAccountInfo_Buff, 0x0040B90D
#endif
#if(v103K)
		mov GetAccountInfo_Buff, 0x0040BD0F
		
#endif
		jmp GetAccountInfo_Buff
	}
}
// ----------------------------------------------------------------------------------------------

Naked(DisconnectEvent)
{
#if(v103Y||v103K)
	_asm
	{
		mov DisconnectEvent_Buff, EDX
	}
#endif
#if(v104D)
	_asm
	{
		mov DisconnectEvent_Buff, ecx
	}
#endif


	//gConsole.Output(cGREEN,"DisconnectEvent");

	// ----
	if( DisconnectEvent_Buff == 32 )
	{
		if( gConnectEx.m_ConnectState != ConnectExType::OnForceDisconnect )
		{
			//gConsole.Output(cGREEN,"1");
			gConnectEx.m_ConnectState = ConnectExType::OnReconnect;
		}
		else
		{
#if(v104D)
			SetByte((LPVOID)0x004DA422, 0x75);
#endif
#if(v103Y)
			//SetByte(0x006219E7
			BYTE DC[] = { 0x0F, 0x85, 0x96, 0x00, 0x00, 0x00 }; 
			WriteMemory((LPVOID)0x006219E7, DC, sizeof(DC));
#endif
#if(v103K)
			//gConsole.Output(cGREEN,"2");
			BYTE DC[] = { 0x0F, 0x85 , 0xCB, 0x00, 0x00, 0x00 }; 
			WriteMemory((LPVOID)0x0060210F, DC, sizeof(DC));
#endif
		}
		// ----
		_asm
		{
#if(v103Y)
			mov DisconnectEvent_Buff,  0x00617FA9
#endif
#if(v104D)
			mov DisconnectEvent_Buff, 0x004D038B
#endif
#if(v103K)
			mov DisconnectEvent_Buff, 0x005F8569
#endif
			jmp DisconnectEvent_Buff
		}
	}
	// ----
	_asm
	{
#if(v103Y)
		mov DisconnectEvent_Buff, 0x0061805C
#endif
#if(v104D)
		mov DisconnectEvent_Buff, 0x004D0430
#endif
#if(v103K)
		mov DisconnectEvent_Buff, 0x005F861C
#endif
		jmp DisconnectEvent_Buff
	}
}
// ----------------------------------------------------------------------------------------------

Naked(MenuExit)
{
	gConnectEx.m_ConnectState = ConnectExType::OnForceDisconnect;
	// ----
	_asm
	{
#if(v103Y)
		mov MenuExit_Buff, 0x0074833D
#endif
#if(v104D)
		mov MenuExit_Buff, 0x007A88AD	
#endif
#if(v103K)
		mov MenuExit_Buff, 0x007107B7
#endif
		
		jmp MenuExit_Buff
	}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Load()
{
	this->m_ConnectState	= ConnectExType::OnLine;
	this->m_LastSendTick	= 0;
	this->m_ReconnectTick	= 0;
	this->m_WantMUHelper	= false;
	// ----
	SetRange((LPVOID)oMenuExit, 18, ASM::NOP);
	SetOp((LPVOID)oMenuExit, (LPVOID)MenuExit, ASM::JMP);
	SetRange((LPVOID)oDisconnectEvent, 9, ASM::NOP);
	SetOp((LPVOID)oDisconnectEvent, (LPVOID)DisconnectEvent, ASM::JMP);
	SetRange((LPVOID)oGetAccountInfo, 10, ASM::NOP);
	SetOp((LPVOID)oGetAccountInfo, (LPVOID)GetAccountInfo, ASM::JMP);

#if(v104D)
	SetByte((LPVOID)0x004DA422, 0xEB);
	SetRange((LPVOID)0x0063CD76, 5, ASM::NOP);	//-> You are connected to the server	//x3
#endif
#if(v103Y)
	BYTE DC[] = { 0xE9, 0x97 , 0x00, 0x00, 0x00, 0x90 }; 
	WriteMemory((PDWORD)0x006219E7, DC, sizeof(DC));
	SetRange((LPVOID)0x006310C4, 5, ASM::NOP);	//-> You are connected to the server	//x3
#endif
#if(v103K)
	BYTE DC[] = { 0xE9, 0xCC , 0x00, 0x00, 0x00, 0x90 }; 
	WriteMemory((PDWORD)0x0060210F, DC, sizeof(DC));
	SetRange((LPVOID)0x00610F34, 5, ASM::NOP);	//-> You are connected to the server	//x3
#endif



}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Run()
{
	DWORD Delay = GetTickCount() - this->m_LastSendTick;
	// ----

	//gConsole.Output(cGREEN,"ConnectEx::Run()");

	if(	this->m_ConnectState != ConnectExType::OnReconnect )
	{
		return;
	}

	//gConsole.Output(cGREEN,"if(	this->m_ConnectState != ConnectExType::OnReconnect )");

	this->ClearGame();
	
	//gConsole.Output(cGREEN,"this->ClearGame();");
	
	this->DrawProgres();

	//gConsole.Output(cGREEN,"this->DrawProgres();");
	// ----
	if( Delay < 5000 || pPlayerState != GameProcess )
	{
		return;
	}
	// ----
	if( pOnLine == 0 )
	{
		this->Reconnect();
	}
	// ----
	if( pOnLine == 1 )
	{
		this->Relogin();
	}
	// ----
	this->m_LastSendTick = GetTickCount();
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::ClearGame()
{
	//if( *(BYTE*)(pMUHelperClass + 8) )
	//{
	//	this->m_WantMUHelper = true;
	//	pMUHelperClose(pMUHelperThis());
	//}
	// ----
	pPartyMemberCount = 0;
#if(v103Y)
	*(BYTE*)(oUserPreviewStruct + 0x2C0)	= 0;
	pPShopSet(pPShopThis2(pPShopThis1()), 0);
	pPShopRefresh(oUserPreviewStruct);

#endif

#if(v104D)
	*(BYTE*)(oUserPreviewStruct + 780)	= 0; //gObjUser.lpViewPlayer->m_Model.Unknown4 = 0;
	pPShopSet(pPShopThis2(pPShopThis1()), 0);
	pPShopRefresh(oUserPreviewStruct);
#endif

#if(v103K)
	*(BYTE*)(oUserPreviewStruct + 0x2C0)	= 0;

#endif
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::RestoreGame()
{
	// ----
	this->m_LastSendTick	= 0;
	this->m_ConnectState	= ConnectExType::OnLine;
	// ----
	//if( this->m_WantMUHelper )
	//{
	//	this->m_WantMUHelper = false;
	//	// ----
	//	if( !gObjUser.lpViewPlayer->InSafeZone )
	//	{
	//		pMUHelperStart(pMUHelperThis());
	//	}
	//}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::DrawProgres()
{
	float StartX = (MAX_WIN_WIDTH / 2) - (160.0 / 2);
	// ----
	Counter++;
	// ----
	if( Counter > 150 )
	{
		Counter = 0;
	}
	// ----
#if(v103Y)
	pDrawGUI(0x7A62, StartX, 100, 160.0, 18.0);
	pDrawGUI(0x7A63, StartX + 5, 105, Counter, 8.0);
#endif
#if(v104D)
	pDrawGUI(0x7A65, StartX, 100, 160.0, 18.0);
	pDrawGUI(0x7A66, StartX + 5, 105, Counter, 8.0);
#endif
#if(v103K)
	pDrawGUI(0x7A5B, StartX, 100, 160.0, 18.0);
	pDrawGUI(0x7A5C, StartX + 5, 105, Counter, 8.0);
#endif

	// ----
	if( pOnLine == 0 )
	{
		pDrawColorText("Reconnecting...", StartX, 104, 160, 0, eBlue, 0, 3);
	}
	else if( pOnLine == 1 )
	{
		pDrawColorText("Relogin...", StartX, 104, 160, 0, eBlue, 0, 3);
	}
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Reconnect()
{
	PMSG_ANS_SERVER_INFO pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xF4, 3, sizeof(PMSG_ANS_SERVER_INFO));
	pRequest.Port = this->m_GSPort;
	memcpy(pRequest.Ip, this->m_GSIP, 16);
	//pDataRecv(pRequest.h.headcode, (LPBYTE)&pRequest, pRequest.h.size, 0);
	DataRecv(pRequest.h.headcode, (LPBYTE)&pRequest, pRequest.h.size, 0);
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Relogin()
{
	CONNECTEX_LOGIN pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 12, sizeof(CONNECTEX_LOGIN));
	memcpy(pRequest.AccountID, this->m_AccountID, 10);
	memcpy(pRequest.Password, this->m_Password, 10);
	ObjectCharacter * pPlayer = &*(ObjectCharacter*)*(DWORD*)0x7AB351C;
	memcpy(pRequest.Name, pPlayer->Name, 10);
	pRequest.TickCount = GetTickCount();
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------

void ConnectEx::Disconnect()
{
	CONNECTEX_CLOSE pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 13, sizeof(CONNECTEX_CLOSE));
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}
// ----------------------------------------------------------------------------------------------
#endif