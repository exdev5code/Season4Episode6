// Dataserver.h : main header file for the DATASERVER application
//

#if !defined(AFX_DATASERVER_H__B6A0F65B_8569_47D4_AA18_648EEEF5CDDE__INCLUDED_)
#define AFX_DATASERVER_H__B6A0F65B_8569_47D4_AA18_648EEEF5CDDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp:
// See Dataserver.cpp for the implementation of this class
//

class CDataserverApp : public CWinApp
{
public:
	CDataserverApp();

	WORD m_ServerPort;
	WORD m_JoinServerPort;
	WORD m_position;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataserverApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	virtual BOOL InitApplication();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDataserverApp)
	afx_msg void Init();
	afx_msg WORD GetServerPort();
	afx_msg WORD GetServerPosition();
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATASERVER_H__B6A0F65B_8569_47D4_AA18_648EEEF5CDDE__INCLUDED_)
