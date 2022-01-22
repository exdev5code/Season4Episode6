// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__DE88E8C1_8830_4881_9146_DA247D027CBF__INCLUDED_)
#define AFX_MAINFRM_H__DE88E8C1_8830_4881_9146_DA247D027CBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ActiveMng.h"
#include "WZScriptEncode.h"
#include "wsJoinServer.h"
#include "MuNameCheck.h"
#include "DBSet\\GSDBSet.h"
#include "DbSet\\CharDBSet.h"
#include "DbSet\\AccountCharDBSet.h"
#include "DbSet\\CastleDBSet.h"
#include "DbSet\\CharPreviewDBSet.h"
#include "DbSet\\CrywolfDBSet.h"
#include "DbSet\\ItemExtDbSet.h"
#include "DbSet\\MasterLevelSystemDBSet.h"
#include "DbSet\\PeriodItemDBSet.h"
#include "DbSet\\PetDBSet.h"
#include "DbSet\\QuestMonKillDBSet.h"
#include "DbSet\\WarehouseDBSet.h"
#include "DbSet\\ZenEvenDb.h"
#include "DbSet\\OptionDbSet.h"
#include "DirPath.h"
#include "classdef.h"
#include "ChildView.h"
#include "RageDBSet.h"

extern char szVersion[];

extern CActiveMng cAM;

extern char szKorSkillTextFileName[];
extern char szKorItemTextFileName[];
extern char szSkillTextFileName[];
extern char szItemTextFileName[];

extern int gLanguage;
extern int gNewAccountCreate;

extern unsigned __int32 gItemCount;

extern CWZScriptEncode CWZSEncode;

extern CwsJoinServer wsjServer;

extern CMuNameCheck gMuName;

extern COptionDbSet gOptionDbSet;
extern CItemExtDbSet gItemExtDbSet;
extern CQuery GuildMemberQry;
extern CWarehouseDBSet CWhDBSet;
extern CZenEvenDb CZenEvenDBSet;
extern CCharPreviewDBSet gCharPreDBSet;
extern CPeriodItemDBSet PeriodItemDBSet;
extern CMasterLevelSystemDBSet MasterLevelSystemDBSet;
extern CQuestMonKillDBSet QuestMonKillDBSet;
extern CCrywolfDBSet CrywolfDBSet;
extern CCastleDBSet CastleDBSet;
extern CPetDBSet PetDBSet;
extern CCharDBSet gCharDbSet;
extern CAccountCharDBSet gACDbSet;

extern CGSDBSet gGSDbSet;
extern CDirPath gDirPath;
extern classdef DCInfo;

extern char szDbConnectID[];
extern char szDbConnectPass[];
extern char szDbConnectDsn[];

extern cRageSystem gRageSystem;

class CMainFrame : public CFrameWnd
{
	
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CChildView  m_wndView;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void DisplayStatusBar(char* szString);
	afx_msg BOOL ServerCreate();
	afx_msg int AcceptClient();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg LONG OnAsyncSelectServerAccept(WPARAM wParam, LPARAM lParam);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__DE88E8C1_8830_4881_9146_DA247D027CBF__INCLUDED_)
