// Dataserver.cpp : Defines the class behaviors for the application.
// Decompilation Completed -> All Same as WebZen

#include "stdafx.h"
#include "Dataserver.h"
#include "MiniDump.h"
#include "MainFrm.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp

BEGIN_MESSAGE_MAP(CDataserverApp, CWinApp)
	//{{AFX_MSG_MAP(CDataserverApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp construction

CDataserverApp::CDataserverApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDataserverApp object

CDataserverApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp initialization

BOOL CDataserverApp::InitInstance()
{
	//AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Mu Data Server"));

	//LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	Init();

	CMainFrame* pFrame;
	pFrame = new CMainFrame();

	m_pMainWnd = pFrame;

	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// Parse command line for standard shell commands, DDE, file open
	//CCommandLineInfo cmdInfo;
	//ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	//if (!ProcessShellCommand(cmdInfo))
	//	return FALSE;

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();

	return TRUE;
}

BOOL CDataserverApp::ExitInstance()
{
	CMiniDump::End();
	return CWinApp::ExitInstance();
}

BOOL CDataserverApp::InitApplication()
{
	CMiniDump::Begin();
	return CWinApp::InitApplication();
}

void CDataserverApp::Init()
{
	m_ServerPort = GetPrivateProfileInt("Connect","Port",55960,".\\Connect.ini");

	m_position = GetPrivateProfileInt("Connect","Position",0,".\\Connect.ini");

	//m_position = 0;

	//if( strlen(m_lpCmdLine) > 1)
	//{
	//	sscanf(m_lpCmdLine, "%d %d", &m_ServerPort, &m_position);
	//}
	//else
	//{
	//	m_ServerPort = DEFDATASERVERPORT;
	//}
}

WORD CDataserverApp::GetServerPort()
{
	return m_ServerPort;
}

WORD CDataserverApp::GetServerPosition()
{
	return m_position;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	CString m_DbserverInfo;

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	m_DbserverInfo = "";
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, 1000, m_DbserverInfo);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDataserverApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDataserverApp message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	char szTemp[256];
	wsprintf(szTemp, "Dataserver version %s", szVersion);
	m_DbserverInfo = szTemp;

	UpdateData(FALSE);
	return TRUE;
}