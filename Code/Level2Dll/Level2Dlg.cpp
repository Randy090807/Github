// Level2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Level2Dlg.h"
#include "afxdialogex.h"
#include "MainView.h"
#include "Resource.h"
#include "../Public/MsgDefine.h"
// CLevel2Dlg dialog

#define ID_HOTKEY_F1	0x100
#define ID_HOTKEY_F2	0x101
#define ID_HOTKEY_F3	0x102
#define ID_HOTKEY_F4	0x103

IMPLEMENT_DYNAMIC(CLevel2Dlg, CDialogEx)

CLevel2Dlg::CLevel2Dlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_LEVEL2/*CLevel2Dlg::IDD*/, pParent)
, m_pView(NULL)
{

}

CLevel2Dlg::~CLevel2Dlg()
{
}

void CLevel2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLevel2Dlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_HOTKEY()
	ON_WM_ACTIVATE()
	ON_WM_MOVE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CLevel2Dlg message handlers


BOOL CLevel2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_pView = (CMainView*)RUNTIME_CLASS(CMainView)->CreateObject();
	m_pView->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDD_MAINVIEW, NULL);
	m_pView->OnInitialUpdate();
	m_pView->ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CLevel2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


int CLevel2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	return 0;
}


void CLevel2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pView)
	{
		m_pView->MoveWindow(0, 0, cx, cy);
	}
}


void CLevel2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}

BOOL CLevel2Dlg::Create(CWnd* pParentWnd)
{
	return CDialogEx::Create(IDD_LEVEL2, pParentWnd);
	
}


void CLevel2Dlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	switch (nHotKeyId)
	{
	case ID_HOTKEY_F1:
		m_pView->ShowTrade(0);
		break;
	case ID_HOTKEY_F2:
		m_pView->ShowTrade(1);
		break;
	case ID_HOTKEY_F3:
		m_pView->ShowTrade(2);
		break;
	case ID_HOTKEY_F4:
		m_pView->ShowTrade(3);
		break;
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CLevel2Dlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	if (nState == 0)
	{
		UnregisterHotKey(m_hWnd, ID_HOTKEY_F1);
		UnregisterHotKey(m_hWnd, ID_HOTKEY_F2);
		UnregisterHotKey(m_hWnd, ID_HOTKEY_F3);
		UnregisterHotKey(m_hWnd, ID_HOTKEY_F4);
	}
	else
	{
		RegisterHotKey(m_hWnd, ID_HOTKEY_F1, 0, VK_F1);
		RegisterHotKey(m_hWnd, ID_HOTKEY_F2, 0, VK_F2);
		RegisterHotKey(m_hWnd, ID_HOTKEY_F3, 0, VK_F3);
		RegisterHotKey(m_hWnd, ID_HOTKEY_F4, 0, VK_F4);
	}
}


void CLevel2Dlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: Add your message handler code here
	::PostMessage(m_pView->GetSafeHwnd(), WM_MOVE, x, y);
}


void CLevel2Dlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	::PostMessage(GetOwner()->GetSafeHwnd(), UM_CLOSE_LEVEL2, (WPARAM)this, 0);
	CDialogEx::OnClose();
}

