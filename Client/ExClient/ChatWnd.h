#pragma once

const int GetDisplayMsgType = 0x6F7FE0;  
const int SetDisplayMsgType = 0x6F7F95;

const int ShowChatMsgs = 0x6F5584;

const int ShowChatMsgsCall_Hook = 0x6F7927;

const int NewCall = 0x8510BA;

const int FixSysMsg1_Hook = 0x6F60AC;      
const int FixSysMsg1_FALSE = FixSysMsg1_Hook+5; 
const int FixSysMsg1_TRUE = 0x6F6165;

const int FixSysMsg2_Hook = 0x6F63B3;
const int FixSysMsg2_FALSE = FixSysMsg2_Hook+5; 
const int FixSysMsg2_TRUE = 0x6F64B6;

const int FixSysMsg3_Hook = 0x6F6715;
const int FixSysMsg3_FALSE = FixSysMsg3_Hook+5; 
const int FixSysMsg3_TRUE = 0x6F67DA;

#if(ANTI_ELITE==TRUE)
class AntiElite
{
public:
	static void __thiscall  Check(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin);
};
extern AntiElite g_AntiElite;
#endif

void ChatWndHooks(); 