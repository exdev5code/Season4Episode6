// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E37D8EB3_D113_431E_86A3_24980E357807__INCLUDED_)
#define AFX_STDAFX_H__E37D8EB3_D113_431E_86A3_24980E357807__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning ( disable : 4786 )

#define DATASERVER_VERSION				"0.70.05T DangeR Edition"
#define DATASERVER_DATE					__DATE__

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define _WIN32_WINNT 0x500

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT

#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "..\\Include\\define.h"
#include "Logproc.h"
#include "LogToFile.h"

#define DB_CONNECT_DSN			"MuOnline"
#define DB_CONNECT_UID			"MuOnlineAdmin"
#define DB_CONNECT_PWD			"wkfwkRnfRnf"

extern char szDbConnectID[]; // idb
extern char szDbConnectPass[]; // idb
extern char szDbConnectDsn[]; // idb

#include "CQuery.h"

extern char g_szDBID_DESC[];

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//~~~~~~~~~~~
//Client List
//~~~~~~~~~~~
//#define __LOCAL__	1
//#define __ExGames__	2
//#define __DoubleDamage__	3
//#define __EvilTwin__	4
#define __MuRain__	5
//#define __ImperiaL__	6
//#define __MUFreeZone__	7
//#define __MuAltair__ 8
//#define __MuReal__	9
//#define _MegaMu_	10
//#define _Mu_Online_MD_ 11
//#define _zigzagmu_ru_		12
//#define _pravednik_	16
//#define _h3yShOk_	17
#define aMUnra

#ifdef aMUnra
#define DISABLE_LOGFILE 1
#endif

#if __ExGames__||__DoubleDamage__||__ImperiaL__
#define PREMIUM_SYSTEM
#endif

#ifdef _MegaMu_
#define PREMIUM_SYSTEM
#define _CR_MEMB_INFO_
#define _RAGE_SYSTEM_
#endif

#ifdef _Mu_Online_MD_ 
#define _RAGE_SYSTEM_
#endif

#ifdef __MuReal__
#define _CR_MEMB_INFO_
#endif

#ifdef _zigzagmu_ru_
#define PREMIUM_SYSTEM
#define _RAGE_SYSTEM_
#define _CR_MEMB_INFO_
#define _MEMB_CREDITS_
#endif

#ifdef _pravednik_
#define _RAGE_SYSTEM_
#endif

#ifdef _h3yShOk_
#define _RAGE_SYSTEM_
#endif

//#define _RAGE_SYSTEM_
//#define _CR_MEMB_INFO_

#endif // !defined(AFX_STDAFX_H__E37D8EB3_D113_431E_86A3_24980E357807__INCLUDED_)
