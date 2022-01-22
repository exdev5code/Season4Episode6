// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
#pragma warning ( disable : 4786 )	// Disable Warning of Large Debuf Strings ( truncated to 255 len )

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_WINNT 0x500

#define ENABLE_PROTOCOL_ENG	0

#define LOG_INMEDIATLY	0
#define REMOVE_CHECKSUM	0
#define DEBUG_IT 0
#define DEBUG_BUFF_EFFECT 0
#define DEBUG_SUMMONER_SKILL	0
#define DEBUG_EVENT_COUNTER	0
#define USE_M_DRIVE 0
#define TESTSERVER	0

#if (USE_M_DRIVE == 1)
#define FINAL_PATH "M:\\"
#define COMMONSERVER_PATH "M:\\commonserver.cfg"
#define SERVER_INFO_PATH "..\\data\\Serverinfo.dat"
#else
#define FINAL_PATH "..\\Data\\"
#define COMMONSERVER_PATH "..\\Data\\commonserver.cfg"
#define SERVER_INFO_PATH "DATA\\Serverinfo.dat"
#endif

#ifdef INTERNATIONAL_KOREA	
#define PROTOCOL_MOVE 0xD3
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xD7
#define PROTOCOL_BEATTACK 0x10
#endif

#ifdef INTERNATIONAL_ENGLISH
#define PROTOCOL_MOVE 0xD4
#define PROTOCOL_POSITION 0x11
#define PROTOCOL_ATTACK 0x15
#define PROTOCOL_BEATTACK 0xDB
#endif

#ifdef INTERNATIONAL_JAPAN
#define PROTOCOL_MOVE 0x1D
#define PROTOCOL_POSITION 0xD6
#define PROTOCOL_ATTACK 0xDC
#define PROTOCOL_BEATTACK 0xD7
#endif

#ifdef INTERNATIONAL_CHINA
#define PROTOCOL_MOVE 0xD7
#define PROTOCOL_POSITION 0xDD
#define PROTOCOL_ATTACK 0xD9
#define PROTOCOL_BEATTACK 0x1D
#endif

#ifdef INTERNATIONAL_TAIWAN
#define PROTOCOL_MOVE 0xD6
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xDD
#define PROTOCOL_BEATTACK 0xD2
#endif

#ifdef INTERNATIONAL_VIETNAM
#define PROTOCOL_MOVE 0xD9
#define PROTOCOL_POSITION 0xDC
#define PROTOCOL_ATTACK 0x15
#define PROTOCOL_BEATTACK 0x1D
#endif

#ifdef INTERNATIONAL_PHILIPPINES
#define PROTOCOL_MOVE 0xDD
#define PROTOCOL_POSITION 0xDF
#define PROTOCOL_ATTACK 0xD6
#define PROTOCOL_BEATTACK 0x11
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

// Windows Header Files:
#include <windows.h>
#include <winbase.h>
#include <winsock2.h>
#include "COMMCTRL.h"

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <time.h>
#include <math.h>
#include <process.h>

#include <map>
#include <string>
#include <ios>

#include <iostream> //Webzen added on 77 ??

#include <algorithm>
#include <vector>
#include <set>

// Local Header Files
#include "..\\Common\\Msg.h"

// TODO: reference additional headers your program requires here

extern CMsg			lMsg;

#define MSGGET(x,y)	(x*256)+y
//#pragma comment( lib , "wsock32.lib" )
//#pragma comment( lib , "ws2_32.lib" )
//#pragma comment( lib , "COMCTL32.lib" )


//{{AFX_INSERT_LOCATION}}
#include <afx.h>
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)

//~~~~~~~~~~~~
//Fix List
//~~~~~~~~~~~~
#define TRAFIC_FIX		TRUE
//~~~~~~~~~~~~~

//~~~~~~~~~~~~~
// Security GS
//~~~~~~~~~~~~~
//#define VMPROTECT
//#define exSECURITY

//~~~~~~~~~~~~
//Client List
//~~~~~~~~~~~~
//#define __LOCAL__	1
//#define __ExGames__	2
//#define __DoubleDamage__	3
//#define __EvilTwin__	4
#define __MuRain__	5			//Public
//#define __ImperiaL__	6
//#define __MUFreeZone__	7
//#define __MuAltair__	8
//#define _MuReal_		9
//#define _MegaMu_		10		//Skype: drynea
//#define _Mu_Online_MD_	11	//Skype: mu-online.md
//#define _zigzagmu_ru_		12		//Skype: househouse307	//92.248.196.27
//#define _muatlantik_	13
//#define _JT_MuOnline_	14
//#define _E4_MUONLINE_	15


//~~~~~~~~~~~~~~~~~~
//ExTeam Client List
//~~~~~~~~~~~~~~~~~~
//#define _Eugene_		1
#define _pravednik_	16
//#define _h3yShOk_		17
//#define FCU_MU		19
//#define MLD			20
//#define Asgorn		21
//#define xeongame		22
//#define aMUnra		23
//#define Trance242		24
//#define MUDev			25
//#define SentinelMU	26
//#define FlameMu			27

#if __ExGames__||__EvilTwin__||__MuRain__||__DoubleDamage__||__ImperiaL__||__MuAltair__
#define TVTEVENT
#endif

#ifdef __EvilTwin__
#define _GRAND_HERO_SYSTEM_	1
#endif

#if __ExGames__||__DoubleDamage__||__ImperiaL__
#define PREMIUM_SYSTEM
#endif

#if __DoubleDamage__
#define PACK_SYSTEM
#define _GRAND_HERO_SYSTEM_	1
#define _NEW_PT_SYSTEM_	1
#endif

#if __ExGames__||__ImperiaL__
#define TALISMAN_SYSTEM
#endif

#if __ImperiaL__
#define DROP_EVENT
#endif

#if __ExGames__||__DoubleDamage__||__MuRain__||__ImperiaL__||__MuAltair__
#define VISUAL_FIX
#endif

#if _MuReal_
#define VISUAL_FIX
#define _EXL_DROP_RATE_
#define _DROP_ZEN_RATE_
#define _VIP_MAP_CORD_	1	//Координаты для випа
#endif

#ifdef __ExGames__
#define _HAPPY_HOUR_EVENT_
#define _EVANGELION_EVENT_
#define _SYSTEM_OF_RAGE_
#endif

#ifdef __LOCAL__
#define _SYSTEM_OF_RAGE_
#endif

#ifdef _MegaMu_
#define PREMIUM_SYSTEM	1
#define VISUAL_FIX	1
#define _MULTI_VAULT_	1
#define _VIP_VAULT_	1	//5 сундуков для випов 2 сундука для обычных
#define _VIP_POST_	1	//Пост только вип пользователям	5$
#define _CREDIT_DONATE_	1	//Система кредит донейта как на муруз 20$
#define _VIP_OFFAFK_	1	//Оффлайн прокачка только для випов	5$
#define _CR_COIN_	1			//кредит монеты
#define _ZEN_COIN_	1

#define _PREMIUM_MOTHER_BUY_	1	//покупка випа на 30 дней за кредиты

#define PACK_SYSTEM	1
#define _GRAND_HERO_SYSTEM_	1
#define _WINGS_5LVL_
#define _WINGS4_NEW_OPT_	1
#define _WINGS5_NEW_OPT_	1
#define _CHAOS_MIX_MANAGER_	1
#define _NEW_PT_SYSTEM_	1
#define _NEW_JEWELS_2_	1
#define TVTEVENT	1
#define _PARTY_GROUP_	1
#define _NSEngine_	1
#define _JEWELS_BANK_		1	//20$
#define NEW_ITEM_DROP	1	//10$
#define NEW_HP_BAR			1	//30$

#define _SYSTEM_OF_RAGE_
#endif

#ifdef _Mu_Online_MD_
#define TVTEVENT
#define DROP_EVENT
#define _HAPPY_HOUR_EVENT_
#define PREMIUM_SYSTEM
#define _LORA_BATTLE_	1
#define BM_QUEST_SYSTEM_	1	//Квест система на карактеристики
#define VISUAL_FIX	1
#define _GRAND_HERO_SYSTEM_	1
#define _WINGS_5LVL_
#define _SYSTEM_OF_RAGE_
#define _RECONNECT_	1

#define _NSEngine_	1
#define _32K_STATS_	1

#define OFF_AFK_PRICE		1	//5$
#define _EXL_DROP_RATE_		1
#define _EVANGELION_EVENT_	1
#define NEW_HP_BAR			1	//30$
#define JoExl_IN_JoGooD		1	//5$
#endif


#ifdef _zigzagmu_ru_
#define PREMIUM_SYSTEM	1
#define TVTEVENT
#define VISUAL_FIX	1
#define _GRAND_HERO_SYSTEM_	1
#define _WINGS_5LVL_
#define _SYSTEM_OF_RAGE_
#define _RECONNECT_	1
#define CASH_SHOP_ADDITIONAL	1
//#define _ANTIHACK_	1
#define _32K_STATS_	1
#define _CREDIT_DONATE_	1	//Система кредит донейта как на муруз 20$
#define NEW_RESET_GRANDRESET	1
//#define _NSEngine_	1
#define _ZEN_COIN_	1
#define _BALANS_SYSTEM_			1	//20$
#define _PREMIUM_MOTHER_BUY_	1	//покупка випа на 30 дней за кредиты
#define NEW_HP_BAR			1	//30$
#define _JEWELS_BANK_		1	//20$
#define _NEW_PT_SYSTEM_		1
#endif

#ifdef _muatlantik_
#define _RECONNECT_	1
#endif


#ifdef __LOCAL__
#define TVTEVENT
#define DROP_EVENT
#define _HAPPY_HOUR_EVENT_
#define PREMIUM_SYSTEM
#define _LORA_BATTLE_	1
#define BM_QUEST_SYSTEM_	1	//Квест система на карактеристики
#define VISUAL_FIX	1
#define _GRAND_HERO_SYSTEM_	1
#define _WINGS_5LVL_
#define _SYSTEM_OF_RAGE_
#define _RECONNECT_	1
#define NEW_HP_BAR			1	//30$
#endif

//#define CASH_SHOP_ADDITIONAL	1
//#define _32K_STATS_	1

//#define _HAPPY_HOUR_EVENT_
//#define _EVANGELION_EVENT_




//#define _ANTIHACK_	1

//#define BC_2_MIN_END	0	//In Dev

//Customs
//#define _CR_COIN_	1			//кредит монеты
//#define _ZEN_COIN_	1
//#define _GRAND_HERO_SYSTEM_	1

//#define _WINGS4_NEW_OPT_	1
//#define _WINGS5_NEW_OPT_	1
//#define _CHAOS_MIX_MANAGER_	1
//#define _NEW_JEWELS_2_	1

#define MARLON_QUEST_COMBO_SIABLE	1


//Mu.md
//#define OFF_AFK_PRICE		1	//5$
//#define _EXL_DROP_RATE_		1
//#define _EVANGELION_EVENT_	1
//#define NEW_HP_BAR			1	//30$
//#define JoExl_IN_JoGooD		1	//5$
//#define _BALANS_SYSTEM_		1	//20$
//#define _VOTER_					1

#ifdef _JT_MuOnline_
#define NEW_HP_BAR				1	//Need Recoded
#define CASH_SHOP_ADDITIONAL	1
#define _GRAND_HERO_SYSTEM_		1
#define _VOTER_					1
#define PREMIUM_SYSTEM			1
#endif


//#define _RECONNECT_	1


#ifdef _E4_MUONLINE_

#endif

#ifdef _pravednik_
#define NEW_HP_BAR				1	//Need Recoded
#define _GRAND_HERO_SYSTEM_	1
#define _RECONNECT_	1
#define _SYSTEM_OF_RAGE_
#define PREMIUM_SYSTEM
#define _HAPPY_HOUR_EVENT_
//#define ALL_CHARACTER_CREATE_DEV	1
#define _GRAND_RESET_WCOIN_	1
#define _WINGS_5LVL_
#define JOE_FULL_OPT
//--
#define PACK_SYSTEM
#define _NEW_PT_SYSTEM_	1
#define TALISMAN_SYSTEM
#define VISUAL_FIX
#define _EXL_DROP_RATE_
#define _DROP_ZEN_RATE_
#define _VIP_MAP_CORD_	1	//Координаты для випа
#define _HAPPY_HOUR_EVENT_
#define _EVANGELION_EVENT_
#define NEW_HP_BAR			1
#define NEW_ITEM_DROP	1
#define _JEWELS_BANK_		1
#define _PARTY_GROUP_	1
#define _NEW_JEWELS_2_	1
#define _WINGS_5LVL_
#define _WINGS4_NEW_OPT_	1
#define _WINGS5_NEW_OPT_	1
#define _CR_COIN_	1			//кредит монеты
#define _ZEN_COIN_	1
#define BM_QUEST_SYSTEM_	1
#define _LORA_BATTLE_	1
#define NEW_RESET_GRANDRESET	1
#define _CREDIT_DONATE_	1
#define CASH_SHOP_ADDITIONAL	1
#define _VOTER_					1
#define ANTI_CHEAT_PLUS			TRUE
#define CMD_MAKE_ITEM			TRUE
#define CUSTOM_NPC_TELEPORT		TRUE
#define ITEM_NO_NAME_DROP_FIX	TRUE
#define DEV_COMBO_CUSTOM		1
#define _BALANS_SYSTEM_			1
#define ENABLE_ITEMS_ALLOPT		1
#endif


#ifdef _h3yShOk_
#define PREMIUM_SYSTEM			1
#define _Eugene_				1
#define _SYSTEM_OF_RAGE_		1
#define _32K_STATS_				1
#define NEW_HP_BAR				1
#define _GRAND_RESET_WCOIN_		1
#define _BALANS_SYSTEM_			1
#endif

#ifdef FCU_MU
#define _RECONNECT_				1
#define _BALANS_SYSTEM_			1
#define ELF_BUFF_2MIN			1
#endif

//MAIN FIX!!!
#define VIESHE_FIX_DC	FALSE

#ifdef MLD
#define ITEM_NO_NAME_DROP_FIX	TRUE
#endif

#ifdef Asgorn
#define _RECONNECT_	1
#define FIX_SELUPAN			//исправлен салупан
#define _NEW_PT_SYSTEM_		1
#define _GRAND_HERO_SYSTEM_	1
#define _32K_STATS_	1
#define ITEM_NO_NAME_DROP_FIX	TRUE
//#define EX_LICENSE				136373629
#endif

#ifdef xeongame
#define VMPROTECT
#define EX_LICENSE				3365654808
#define ITEM_NO_NAME_DROP_FIX	TRUE
#define _RECONNECT_				1
#define CMD_CRASH				TRUE
#define _NEW_PT_SYSTEM_			1
#define CUSTOM_NPC_TELEPORT		TRUE
#define _BALANS_SYSTEM_			1
#define CMD_MAKE_ITEM			TRUE
#define DEV_COMBO_CUSTOM		1
#define ANTI_CHEAT_PLUS			TRUE
#endif

#ifdef aMUnra
#define ITEM_NO_NAME_DROP_FIX	TRUE
#define _RECONNECT_				1
#define ANTI_CHEAT_PLUS			TRUE
#define DISABLE_LOGFILE			1
#endif

#ifdef Trance242
#define ANTI_CHEAT_PLUS			TRUE
#endif

#ifdef SentinelMU
#define ITEM_NO_NAME_DROP_FIX	TRUE
#define _RECONNECT_				1
#define ANTI_CHEAT_PLUS			TRUE
#define _BALANS_SYSTEM_			1
#define FIX_SELUPAN			//исправлен салупан
#define _NEW_PT_SYSTEM_		1
#define _GRAND_HERO_SYSTEM_	1
//#define NEW_HP_BAR				1
#define PREMIUM_SYSTEM			1
#define _SYSTEM_OF_RAGE_		1
#define _HAPPY_HOUR_EVENT_
#define TVTEVENT
#define VISUAL_FIX	1
#define _WINGS_5LVL_
//#define _NEW_JEWELS_2_	1
#define _VOTER_					1
#define _EVANGELION_EVENT_	1
#endif

#if(FlameMu)
#define DEV_COMBO_CUSTOM		1
#define ENABLE_ITEMS_ALLOPT		1
#define _GRAND_HERO_SYSTEM_		1
#define _32K_STATS_				1
#endif



//**********************
//#define _WINGS_5LVL_
#ifdef _WINGS_5LVL_
#define END_WING_NUM 194
#else
#define END_WING_NUM 188
#endif
//**********************


//+reconnect + elf baf  reguliryvat + balans igrakof