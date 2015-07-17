// SpaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpaceDlg.h"
#include "afxdialogex.h"
#include "MainView.h"
#include "Resource.h"

// CSpaceDlg dialog

IMPLEMENT_DYNAMIC(CSpaceDlg, CDialogEx)

CSpaceDlg::CSpaceDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_SPACE/*CSpaceDlg::IDD*/, pParent)
	, m_pView(NULL)
{

}

CSpaceDlg::~CSpaceDlg()
{
}

void CSpaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSpaceDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSpaceDlg message handlers


BOOL CSpaceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_pView = (CMainView*)RUNTIME_CLASS(CMainView)->CreateObject();
	m_pView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, (UINT)-1, NULL);
	m_pView->OnInitialUpdate();
	m_pView->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CSpaceDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


int CSpaceDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CSpaceDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pView)
	{
		m_pView->MoveWindow(0, 0, cx, cy);
	}
}


void CSpaceDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CSpaceDlg::Create(CWnd* pParentWnd)
{
	return CDialogEx::Create(IDD_SPACE, pParentWnd);

}

void CSpaceDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
//	CDialogEx::OnClose();
}
