#pragma once

#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <tlhelp32.h>


#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdarg.h>
#include <process.h>
#include <WinBase.h>

#include <WinSock.h>
#pragma comment (lib,"ws2_32.lib") //<- we need this lib for winsock

#include <gl\GL.h>
#pragma comment(lib, "Opengl32.lib")
#pragma comment(lib, "Ws2_32.lib")

#include "dirent.h"

#include "glext.h"
#include "..\\Cg\\cg.h"
#include "..\\Cg\\cgGL.h"
#pragma comment(lib, "cg.lib")
#pragma comment(lib, "cgGL.lib")

#define FULL_HD						TRUE


#define Naked(Function)				void __declspec(naked) Function()
//#define CONSOLE

#define v103K	1

//~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Client List
//~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define DEBUG	FALSE

//#define __LOCAL__	1
//#define __ExGames__	2
//#define __DoubleDamage__	3
//#define __EvilTwin__	4
#define __MuRain__ 5				//public
//#define __ImperiaL__	6
//#define __MUFreeZone__	7
//#define __MuAltair__	8
//#define __MuReal__	10
//#define _MegaMu_		11
//#define _Mu_Online_MD_	12
//#define _zigzagmu_ru_		12		//Skype: househouse307	//92.248.196.27
//#define _muatlantik_	13
//#define _JT_MuOnline_	14
//#define _E4_MUONLINE_	15
//#define _pravednik_	16
//#define _h3yShOk_	17		//10$
//#define EmpireMu 18
//#define FCU_MU		19
//#define Asgorn		21
//#define xeongame	22
//#define aMUnra		23
//#define Trance242		24
//#define MUDev			25
//#define SentinelMU		26
#define FlameMu			27

//#define _GS_5_

#if __DoubleDamage__
#define PACK_SYSTEM
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _IP_	"188.165.41.208"
#endif

#if __LOCAL__
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _IP_	"192.168.0.103"
#define _SERIAL_		"Td4e8UtYvLo90zZd"
#define TEXT_TITLE	"Ex-Team"
#define _SYSTEM_OF_RAGE_
#define _WINGS_5LVL_
#define exRECONNECT	1
#define _WINGS4_NEW_OPT_	1
#define _WINGS5_NEW_OPT_	1
#define _CONFIG_SAVE_	1	//5$
//#define NEW_HP_BAR		1	//30$
//#define PACK_SYSTEM
//#define _JEWELS_BANK_	1	//20$
//#define NEW_GLOW_EFFECT		1	//20$
#endif

#if __MuAltair__	//Skype: xumuk533
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _PET_CUSTOM_
#define _IP_	"91.213.8.61"
#define ITEM_TITLE "MuAltair"
#endif

#ifdef __MuReal__
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _IP_	"91.213.8.59"
#define ITEM_TITLE "MuReal"
#endif

#ifdef __ExGames__
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _IP_	"91.213.8.230"
#define _SYSTEM_OF_RAGE_
#define _WINGS_5LVL_
#endif

#ifdef _MegaMu_
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _IP_	"178.33.39.192"//"91.213.8.79"
#define _WINGS_5LVL_
#define _ITEM_LOAD_	1
#define _GRAND_SYSTEM_	1
#define PACK_SYSTEM	1
#define _LOAD_GLOW_	1
#define _WINGS4_NEW_OPT_	1
#define _WINGS5_NEW_OPT_	1
#define ITEM_EFFECT	1
#define _SYSTEM_OF_RAGE_
#define _PET_CUSTOM_
#define _JEWELS_BANK_	1	//20$
#define NEW_HP_BAR		1	//30$
//#define NEW_GLOW_EFFECT		1	//20$
#endif

#ifdef _Mu_Online_MD_
#define _IP_	"86.106.248.176"
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _WINGS_5LVL_
#define exRECONNECT	1
#define _SYSTEM_OF_RAGE_
#define _CONFIG_SAVE_	1	//5$
#define NEW_HP_BAR		1	//30$
#endif

#ifdef _zigzagmu_ru_
#define _IP_	"92.248.196.27"
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define _WINGS_5LVL_
#define _SYSTEM_OF_RAGE_
#define exRECONNECT	1
#define TEXT_TITLE	"ZigZagMu"
//#define ANTI_HACK	1
//#define _LAUNCHER_		"Updater"
#define _PET_CUSTOM_
#define NEW_HP_BAR		1	//30$
#define _JEWELS_BANK_	1	//20$
#define _CONFIG_SAVE_	1	//5$
#endif

#ifdef __MuRain__
#define _SPEED_FIX_
#define _VISUAL_FIX_
// --
#ifdef _JT_MuOnline_
#define _IP_			"77.120.211.73"	//"192.168.000.100"
#else
#if _h3yShOk_
#define _IP_			"51.225.209.18"//"92.222.213.73"	//"10.33.18.29"
#else
#define _IP_			"192.168.0.100"	//"178.75.33.120"
#endif

#endif
// --
#ifdef _h3yShOk_
#define TEXT_TITLE		"Madmu"
#else
#define TEXT_TITLE		"ExTeam"
#define _SERIAL_		"Td4e8UtYvLo90zZd"
#endif
#endif

#ifdef _muatlantik_
#define exRECONNECT	1
#endif

#ifdef _JT_MuOnline_
#define NEW_HP_BAR		1
#define _GRAND_SYSTEM_
#endif


//#define _SPEED_FIX_
//#define _VISUAL_FIX_
//#define _GRAND_SYSTEM_
//#define _IP_	"91.213.8.230"
//#define _PET_CUSTOM_
//#define _SYSTEM_OF_RAGE_
//#define _WINGS_5LVL_

//#define DEBUG_INTERFACE


//#define _ITEM_LOAD_	1
//#define _LOAD_GLOW_	1

//#define ITEM_EFFECT	1

//#define _LAUNCHER_		"Updater"

#ifdef _E4_MUONLINE_
#define _IP_			"192.168.1.100"
#define TEXT_TITLE		"ExTeam"
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _SERIAL_		"Td4e8UtYvLo90zZd"
#define exRECONNECT	1
#endif

#ifdef _pravednik_
#define exRECONNECT	1
#define _GRAND_SYSTEM_
#define NEW_HP_BAR		1
#define _SYSTEM_OF_RAGE_
#define _WINGS_5LVL_
#define NO_DLL_CLICKER
//--
#define _PET_CUSTOM_
#define ANTI_CHEAT_PLUS			TRUE
#define ANTI_ELITE			TRUE
#define NEW_HP_BAR		1	
#define _JEWELS_BANK_	1	
#define _CONFIG_SAVE_	1	
#define ITEM_EFFECT	1
#define _LOAD_GLOW_	1
#define _WINGS4_NEW_OPT_	1
#define _WINGS5_NEW_OPT_	1
#define _ITEM_LOAD_	1

#endif

#ifdef _h3yShOk_
//#define ANTI_HACK	1
#define _SYSTEM_OF_RAGE_
#define NEW_HP_BAR		1
#endif

#ifdef EmpireMu
#define ANTI_ELITE			TRUE
#endif

#ifdef FCU_MU
#define exRECONNECT	1
#define EX_AH		TRUE
#endif

#ifdef Asgorn
#define exRECONNECT		1
#define _GRAND_SYSTEM_
#define ANTI_HACK		1
//#define _IP_			"164.132.31.69"
#define _IP_			"78.26.250.56"
#define _SERIAL_		"Td4e8UtYvLo90zZd"
#define TEXT_TITLE		"Asgorn"
//#define _LAUNCHER_		"Updater"
#endif

#ifdef xeongame
#define _LAUNCHER_				"Updater"
#define exRECONNECT				1
#define _IP_					"78.36.3.197"
//#define _IP_					"192.168.1.4"
#define _SERIAL_				"NHLEL6MI4GE4ETEV"
#define TEXT_TITLE				"AGC ITEM"
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _GRAND_SYSTEM_
#define ANTI_CHEAT_PLUS			TRUE
#endif

#ifdef aMUnra 
#define _IP_					"91.213.8.29"
#define _SERIAL_				"Td4e8UtYvLo90zZe"
#define TEXT_TITLE				"aMUnra"
#define exRECONNECT				1
#define DISABLE_MINIMAP			TRUE
#define _LAUNCHER_				"Updater"
#define CLICKER_DLL				TRUE
#define ANTI_CHEAT_PLUS			TRUE

#endif

#ifdef Trance242
#define ANTI_CHEAT_PLUS			TRUE
#endif

#ifdef MUDev
#define _IP_					"192.168.0.103"
#define _SERIAL_				"Td4e8UtYvLo90zZd"
#define TEXT_TITLE				"MUDev"
#endif

#if(SentinelMU)
#define _IP_					"91.213.8.29"
#define _SERIAL_				"Td4e8UtYvLo90zZe"
#define TEXT_TITLE				"SentinelMU"
#define exRECONNECT				1
#define DISABLE_MINIMAP			TRUE
#define _LAUNCHER_				"Updater"
#define CLICKER_DLL				TRUE
#define ANTI_CHEAT_PLUS			TRUE
#define _GRAND_SYSTEM_
#define _SPEED_FIX_
#define _VISUAL_FIX_
#define _SYSTEM_OF_RAGE_
//#define NEW_HP_BAR		1
#endif

#if(FlameMu)
#define _IP_NEW_				"192.168.70.1"
#define _SERIAL_NEW_			"Td4e8UtYvLo90zZd"
#define TEXT_TITLE				"FlameMu"
#endif


#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
