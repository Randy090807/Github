// Level2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Level2Dlg.h"
#include "afxdialogex.h"
#include "MainView.h"
#include "Resource.h"
#include "../Public/MsgDefine.h"
#include "../Public/Config.h"
#include "../Public/Utility.h"


// CLevel2Dlg dialog

#define ID_HOTKEY_START	0x100
#define ID_HOTKEY_END	0x120
#define ID_HOTKEY_ESC	0x121

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
	ON_MESSAGE(UM_NOTIFY_CONFIG_REFRESH, &CLevel2Dlg::OnConfigRefreshNotify)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CLevel2Dlg::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CLevel2Dlg::OnMsgSrvDataReport)
	ON_MESSAGE(UM_NOTIFY_INIT_COMPLETE, &CLevel2Dlg::OnMsgInitComplete)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY2, &CLevel2Dlg::OnMsgSrvDataNofity2)
	ON_MESSAGE(UM_SRV_DATA_REPORT2, &CLevel2Dlg::OnMsgSrvDataReport2)
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
	if ( nHotKeyId >= ID_HOTKEY_START && nHotKeyId <= ID_HOTKEY_END)
	{
		m_pView->ShowTrade(nHotKeyId-ID_HOTKEY_START);
	}
	else if ( nHotKeyId == ID_HOTKEY_ESC)
	{
		m_pView->CancelOrder();
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CLevel2Dlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	if (nState == 0)
	{
		for (int i = 0; i < CConfig::Inst()->Level2Info()->HKSize(); i++)
		{
			UnregisterHotKey(m_hWnd, ID_HOTKEY_START + i);
		}
		UnregisterHotKey(m_hWnd, ID_HOTKEY_ESC);
	}
	else
	{
		for (int i = 0; i < CConfig::Inst()->Level2Info()->HKSize(); i++)
		{
			DWORD dwVK = 0, dwModifier = 0;
			ParseHotKey(CConfig::Inst()->Level2Info()->Item(i)->HotKey, dwVK, dwModifier);
			RegisterHotKey(m_hWnd, ID_HOTKEY_START+i, dwModifier, dwVK);
		}
		RegisterHotKey(m_hWnd, ID_HOTKEY_ESC, 0, VK_ESCAPE);
		
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

LRESULT CLevel2Dlg::OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam)
{
	::PostMessage(m_pView->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, wparam, lparam);
	return 0;
}

LRESULT CLevel2Dlg::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	::PostMessage(m_pView->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, wparam, lparam);
	return 0;
}

LRESULT CLevel2Dlg::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pMsg = (CBaseMsg*)wparam;
	pMsg->Header.userdata = (UINT)this;
	::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT, wparam, lparam);
	return 0;
}

LRESULT CLevel2Dlg::OnMsgInitComplete(WPARAM wparam, LPARAM lparam)
{
	::PostMessage(m_pView->GetSafeHwnd(), UM_NOTIFY_INIT_COMPLETE, wparam, lparam);
	return 0;
}

LRESULT CLevel2Dlg::OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam)
{
	::PostMessage(m_pView->GetSafeHwnd(), UM_SRV_DATA_NOTIFY2, wparam, lparam);
	return 0;
}

LRESULT CLevel2Dlg::OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam)
{
	MsgHeader* Header = (MsgHeader*)wparam;
	Header->userdata = (UINT)this;
	::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT2, wparam, lparam);
	return 0;
}
