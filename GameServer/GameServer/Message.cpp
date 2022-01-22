#include "StdAfx.h"
#include "user.h"
#include "..\common\winutil.h"

//Message Exp
//===========
void MsgNormal(int aIndex,char* szMsg,...)
{
	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	
	GCServerMsgStringSend(szTemp, aIndex,1); // 0 = Global MSG; 1 = System information; 2 = Guild notice
}
//Chat Message
//============
void MessageChat(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	//vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	vsprintf(Message,szMsg,pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSend(aIndex,Packet, Len);
	free (Packet);
}
//ChatSend(LPOBJ lpObj, char* szChat);
//================
void MessageAllChat(int aIndex,char* szMsg,...)
{
	char Message[1024];
	va_list pArguments;
    va_start(pArguments,szMsg);
	//vsprintf_s(Message,sizeof(Message), szMsg, pArguments);
	vsprintf(Message,szMsg,pArguments);
	va_end(pArguments);
	BYTE *Packet;
	Packet = (BYTE*) malloc(200);
	memset(Packet, 0x00, 200);
	*Packet = 0xC1;
	*(Packet+2) = 0x00;	//0x00
	memcpy((Packet+13), Message, strlen(Message));
	int Len = (strlen(Message) + 0x13);
	*(Packet+1) = Len;
	DataSendAll(Packet, Len);
	free (Packet);
}
//Message All Global
//==================
void MessaageAllGlobal(char* szMsg,...)
{
	char szTemp[1024];
	va_list pArguments;
	va_start(pArguments,szMsg);
	vsprintf(szTemp,szMsg,pArguments);
	va_end(pArguments);
	AllSendServerMsg(szTemp);
}

void ChatMessageOne(int aIndex, char * msg, ...)
{
	PMSG_CHATDATA pWhisper;
	PHeadSetB((LPBYTE)&pWhisper, 0x00, sizeof(pWhisper));
	strcpy(pWhisper.chatid, gObj[aIndex].Name);
	memcpy(pWhisper.chatmsg, msg, sizeof(pWhisper.chatmsg));
	int len = strlen(pWhisper.chatmsg);

	if ( len > 0 )
	{
		pWhisper.h.size -= sizeof(pWhisper.chatmsg);
		pWhisper.h.size += len + 1;

		DataSendAll((LPBYTE)&pWhisper, pWhisper.h.size);
	}
}

void ChatMessageTwo(int aIndex, char * msg, ...)
{
	PMSG_CHATDATA_WHISPER pWhisper;
	PHeadSetB((LPBYTE)&pWhisper, 0x02, sizeof(pWhisper));
	strcpy(pWhisper.id, gObj[aIndex].Name);
	memcpy(pWhisper.chatmsg, msg, sizeof(pWhisper.chatmsg));
	int len = strlen(pWhisper.chatmsg);

	if ( len > 0 )
	{
		pWhisper.h.size -= sizeof(pWhisper.chatmsg);
		pWhisper.h.size += len + 1;

		DataSendAll((LPBYTE)&pWhisper, pWhisper.h.size);
	}
}