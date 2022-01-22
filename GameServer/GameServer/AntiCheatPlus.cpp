#include "StdAfx.h"
#include "AntiCheatPlus.h"
#include "..\\include\\ReadScript.h"
#include "GameMain.h"
#include "LogToFile.h"
#include "logproc.h"
#include "user.h"
//#include "ConnectEx.h"
// ----------------------------------------------------------------------------------------------

#if(ANTI_CHEAT_PLUS==TRUE)

CLogToFile g_AntiCheatLog("AntiCheat", "..\\AntiCheat\\LOG", TRUE);
// ----------------------------------------------------------------------------------------------

AntiCheatPlus g_AntiCheatPlus;
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Init()
{
	ZeroMemory(&this->TitleName, sizeof(this->TitleName));
	ZeroMemory(&this->ClassName, sizeof(this->ClassName));
	ZeroMemory(&this->InjectName, sizeof(this->InjectName));
	ZeroMemory(&this->ProcessName, sizeof(this->ProcessName));

	this->TitleCount = 0;
	this->ClassCount = 0;
	this->InjectCount = 0;
	this->ProcessCount = 0;

	this->Enable = false;

	this->DumpActive = false;
	this->TitleActive = false;
	this->ClassActive = false;
	this->InjectActive = false;
	this->ProcessActive = false;
	this->EliteActive = true;

	this->DumpTime = 10000;
	this->TitleTime = 10000;
	this->ClassTime = 10000;
	this->InjectTime = 10000;
	this->ProcessTime = 10000;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Load()
{
	this->Init();
	this->ReadConfig("..\\AntiCheat\\AntiCheatMain.ini");
	this->Read(eTitleType, "..\\AntiCheat\\CheatBase\\TitleCheat.txt");
	this->Read(eClassType, "..\\AntiCheat\\CheatBase\\ClassCheat.txt");
	this->Read(eInjectType, "..\\AntiCheat\\CheatBase\\InjectCheat.txt");
	this->Read(eProcessType, "..\\AntiCheat\\CheatBase\\ProcessCheat.txt");
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::ReadConfig(char* File)
{
	this->Enable = GetPrivateProfileInt("ExTeam", "Enable", 0, File);

	this->DumpActive = GetPrivateProfileInt("ExTeam", "DumpActive", 0, File);
	this->TitleActive = GetPrivateProfileInt("ExTeam", "TitleActive", 0, File);
	this->ClassActive = GetPrivateProfileInt("ExTeam", "ClassActive", 0, File);
	this->InjectActive = GetPrivateProfileInt("ExTeam", "InjectActive", 0, File);
	this->ProcessActive = GetPrivateProfileInt("ExTeam", "ProcessActive", 0, File);
	this->EliteActive  = GetPrivateProfileInt("ExTeam", "EliteActive", 0, File);

	this->DumpTime = GetPrivateProfileInt("ExTeam", "DumpTime", 10000, File);
	this->TitleTime = GetPrivateProfileInt("ExTeam", "TitleTime", 10000, File);
	this->ClassTime = GetPrivateProfileInt("ExTeam", "ClassTime", 10000, File);
	this->InjectTime = GetPrivateProfileInt("ExTeam", "InjectTime", 10000, File);
	this->ProcessTime = GetPrivateProfileInt("ExTeam", "ProcessTime", 10000, File);
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::Read(int type, char* File)
{
	SMDFile = fopen(File, "r");
	if( SMDFile == NULL )
	{
		return;
	}
	while(true)
	{
		SMDToken Token = GetToken();
		if( Token == END || !strcmp(TokenString, "end") )
		{
			break;
		}
		if(type==eTitleType)
		{
			if(this->TitleCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->TitleName[this->TitleCount],TokenString,sizeof(this->TitleName[this->ClassCount]));
			this->TitleCount++;
		}
		if(type==eClassType)
		{
			if(this->ClassCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ClassName[this->ClassCount],TokenString,sizeof(this->ClassName[this->ClassCount]));
			this->ClassCount++;
		}
		if(type==eInjectType)
		{
			if(this->InjectCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->InjectName[this->InjectCount],TokenString,sizeof(this->InjectName[this->InjectCount]));
			this->InjectCount++;
		}
		if(type==eProcessType)
		{
			if(this->ProcessCount >= MAX_AH_DB)
			{
				break;
			}
			memcpy(this->ProcessName[this->ProcessCount],TokenString,sizeof(this->ProcessName[this->ProcessCount]));
			this->ProcessCount++;
		}
	}

	if(type==eTitleType)
	{
		LogAdd("[Anti-Cheat] [Title Window] Loaded: %d", this->TitleCount);
	}
	if(type==eClassType)
	{
		LogAdd("[Anti-Cheat] [Class Window] Loaded: %d", this->ClassCount);
	}
	if(type==eInjectType)
	{
		LogAdd("[Anti-Cheat] [Inject Dll] Loaded: %d", this->InjectCount);
	}
	if(type==eProcessType)
	{
		LogAdd("[Anti-Cheat] [Process] Loaded: %d", this->ProcessCount);
	}

	fclose(SMDFile);
	SMDFile = NULL;
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Cheat(int UserIndex)
{
	if(!this->Enable)
	{
		return;
	}
	this->GC_Init(UserIndex);
	this->GC_Config(UserIndex);
	this->GC_Title(UserIndex);
	this->GC_Class(UserIndex);
	this->GC_Inject(UserIndex);
	this->GC_Process(UserIndex);
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::CG_Cheater(PMST_CheaterUser*aRecv, int UserIndex)
{
	if (UserIndex < 0 || UserIndex > OBJMAX-1 )
	{
		return;
	}

	LPOBJ lpUser = &gObj[UserIndex];

	if(aRecv->Result)
	{
		g_AntiCheatLog.Output("[%s][%s][%s] %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, aRecv->CheatText);
		GCServerMsgStringSend("..:: Anti-Cheat ::..", lpUser->m_Index, 0);
		GCServerMsgStringSend(aRecv->CheatText, lpUser->m_Index, 0);
		LogAddC(2,"[%s][%s][%s] %s", lpUser->AccountID, lpUser->Name, lpUser->Ip_addr, aRecv->CheatText);
#if(RECONNECT_SYSTEM==TRUE)				
		g_ReConnect.SendClose(UserIndex,NORM_DC);
#else
		CloseClient(UserIndex);
#endif
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Config(int UserIndex)
{
	PMSG_AH_CONFIG pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Config;

	pMsg.DumpActive = this->DumpActive;
	pMsg.TitleActive = this->TitleActive;
	pMsg.ClassActive = this->ClassActive;
	pMsg.InjectActive = this->InjectActive;
	pMsg.ProcessActive = this->ProcessActive;
	pMsg.EliteActive = this->EliteActive;

	pMsg.DumpTime = this->DumpTime;
	pMsg.TitleTime = this->TitleTime;
	pMsg.ClassTime = this->ClassTime;
	pMsg.InjectTime = this->InjectTime;
	pMsg.ProcessTime = this->ProcessTime;

	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Init(int UserIndex)
{
	PMSG_AH_SUB pMsg;
	pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
	pMsg.type = eAH_Init;
	DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Title(int UserIndex)
{
	for(int i = 0; i < this->TitleCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Title;
		memcpy(pMsg.Name,this->TitleName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Class(int UserIndex)
{
	for(int i = 0; i < this->ClassCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Class;
		memcpy(pMsg.Name,this->ClassName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Inject(int UserIndex)
{
	for(int i = 0; i < this->InjectCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Inject;
		memcpy(pMsg.Name,this->InjectName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

void AntiCheatPlus::GC_Process(int UserIndex)
{
	for(int i = 0; i < this->ProcessCount; i++)
	{
		PMSG_CheatBase pMsg;
		pMsg.h.set((LPBYTE)&pMsg, 0xFB, 0xFF, sizeof(pMsg));
		pMsg.type = eAH_Process;
		memcpy(pMsg.Name,this->ProcessName[i],sizeof(pMsg.Name));
		DataSend(UserIndex, (LPBYTE)&pMsg, sizeof(pMsg));
	}
}
// ----------------------------------------------------------------------------------------------

#endif