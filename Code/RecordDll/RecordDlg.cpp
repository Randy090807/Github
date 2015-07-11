// RecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "MainView.h"
#include "Resource.h"
#include "View1.h"
#include "View2.h"
// CRecordDlg dialog

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_RECORD/*CRecordDlg::IDD*/, pParent)

{

}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CRecordDlg message handlers


BOOL CRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CRecordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


int CRecordDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
// 	m_pView = (CMainView*)RUNTIME_CLASS(CMainView)->CreateObject();
// 	m_pView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, (UINT)-1, NULL);
// 	m_pView->OnInitialUpdate();
// 	m_pView->ShowWindow(SW_SHOW);

	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW |
		CS_HREDRAW,
		::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH) ::GetStockObject(WHITE_BRUSH),
		::LoadIcon(NULL, IDI_APPLICATION));
	// Create the frame window with "this" as the parent
	m_pMyFrame = new CFrameWnd();
	m_pMyFrame->Create(NULL, NULL, WS_CHILD,CRect(0, 0, 1, 1), this);
	m_pMyFrame->ShowWindow(SW_SHOW);

	if (!m_wndSplitter.CreateStatic(m_pMyFrame, 2, 1))
	{
		return FALSE;
	}

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CView1), CSize(200, 200), NULL);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CView2), CSize(200, 200), NULL);
	return 0;
}


void CRecordDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pMyFrame)
	{
		m_pMyFrame->MoveWindow(0, 0, cx, cy);
	}
	if (m_wndSplitter.GetSafeHwnd())
	{
		m_wndSplitter.MoveWindow(0, 0, cx, cy);
	}
}


void CRecordDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CRecordDlg::Create(CWnd* pParentWnd /*= NULL*/)
{
	return CDialogEx::Create(IDD_RECORD, pParentWnd);
}
