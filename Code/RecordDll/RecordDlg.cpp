// RecordDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RecordDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "View1.h"
#include "View2.h"
#include "../Public/Config.h"
#include "../Public/MsgDefine.h"
#include "../Public/TradeInfo.h"

// CRecordDlg dialog

#define ID_HOTKEY_ESC		0x105
#define ID_HOTKEY_DELETE	0x106
#define ID_HOTKEY_F10		0x107

#define QUERY_TIMER_ID			0x100
#define QUERY_TIMER_INTERVAL	1*1000

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_RECORD/*CRecordDlg::IDD*/, pParent)
, m_StatusBar(this)
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
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_HOTKEY()
	ON_MESSAGE(UM_NOTIFY_CONFIG_REFRESH, &CRecordDlg::OnConfigRefreshNotify)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CRecordDlg::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CRecordDlg::OnMsgSrvDataReport)
	ON_MESSAGE(UM_NOTIFY_INIT_COMPLETE, &CRecordDlg::OnMsgInitComplete)
	ON_MESSAGE(WM_USER+0x700, &CRecordDlg::OnMsgUpdateData)
	ON_WM_TIMER()
	ON_WM_PAINT()
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

	((CView1*)m_wndSplitter.GetPane(0, 0))->SetMsgReciver(this);
	return 0;
}


void CRecordDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_pMyFrame)
	{
		m_pMyFrame->MoveWindow(0, 0, cx, cy-CDCSTAUTSBAR_HEIGHT);
	}
	if (m_wndSplitter.GetSafeHwnd())
	{
		m_wndSplitter.MoveWindow(0, 0, cx, cy - CDCSTAUTSBAR_HEIGHT);
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


void CRecordDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
//	CDialogEx::OnClose();
}


void CRecordDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	if (nState == 0)
	{
		UnregisterHotKey(m_hWnd, ID_HOTKEY_DELETE);
		UnregisterHotKey(m_hWnd, ID_HOTKEY_ESC);
		UnregisterHotKey(m_hWnd, ID_HOTKEY_F10);
	}
	else
	{
		RegisterHotKey(m_hWnd, ID_HOTKEY_DELETE, 0, VK_DELETE);
		RegisterHotKey(m_hWnd, ID_HOTKEY_ESC, 0, VK_ESCAPE);
		RegisterHotKey(m_hWnd, ID_HOTKEY_F10, 0, VK_F10);
	}
	
}


void CRecordDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	if ( nHotKeyId == ID_HOTKEY_ESC)	// 单笔撤单或者批量撤单
	{
		CView1* pView = (CView1*)(m_wndSplitter.GetPane(0, 0));
		pView->CancelOrder();
	}
	else if ( nHotKeyId == ID_HOTKEY_DELETE)	// 全部撤单
	{
		CView1* pView = (CView1*)(m_wndSplitter.GetPane(0, 0));
		pView->ClearOrder();
	}
	else if (nHotKeyId == ID_HOTKEY_F10)	// 改单
	{
		CView1* pView = (CView1*)(m_wndSplitter.GetPane(0, 0));
		pView->ModifyOrder();
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

LRESULT CRecordDlg::OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam)
{
	CWnd* pView = (m_wndSplitter.GetPane(0, 0));
	::PostMessage(pView->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, wparam, lparam);

	pView = (m_wndSplitter.GetPane(1, 0));
	::PostMessage(pView->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, wparam, lparam);

	return 0;
}

void CRecordDlg::QueryRequest()
{
	COrderInquiryMsg* pMsg = new COrderInquiryMsg();
	::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);

	m_StatusBar.UpdateStatus(_T("更新数据中......"));
}

void CRecordDlg::QueryResponse()
{

}


void CRecordDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == QUERY_TIMER_ID)
	{
		//QueryRequest();
		/*
			zhang
			定时遍历未完结交易记录，发送未完结订单查询
		*/
		CView1* pView1 = (CView1*)(m_wndSplitter.GetPane(0, 0));
		for (int i = 0; i < pView1->m_wndReport.GetRecords()->GetCount(); i++)
		{
			COrderRecord* pRecord = (COrderRecord*)(pView1->m_wndReport.GetRecords()->GetAt(i));
			COrderInquiryMsg* pMsg = new COrderInquiryMsg(pRecord->GetOrderRef());
			::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
		}

	}

	CDialogEx::OnTimer(nIDEvent);
}

LRESULT CRecordDlg::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pBaseMsg = (CBaseMsg*)wparam;
	if ( pBaseMsg->Header.type == ID_ORDER_INQUIRY_RESULT)
	{
		COrderInquiryResultMsg* pMsg = (COrderInquiryResultMsg*)wparam;
		if (pMsg->Error == 0)
		{
			// 更新总成交股数，总成交金额信息
			int volume = 0;
			double amont = 0;
			for (auto iter = pMsg->Orders.begin(); iter != pMsg->Orders.end(); ++iter)
			{
				if ((*iter)->Done == 1)	// 完结订单
				{
					volume += (*iter)->ExeVol;
					amont += (*iter)->ExeAmount;
				}
			}
			CTradeInfo::Inst()->Volume += volume;
			CTradeInfo::Inst()->Amount += amont;


			// 刷新视图
			CView1* pView1 = (CView1*)(m_wndSplitter.GetPane(0, 0));
			pView1->Update(pMsg);

			CView2* pView2 = (CView2*)(m_wndSplitter.GetPane(1, 0));
			pView2->Update(pMsg);

			CString szText;
			COleDateTime dt = COleDateTime::GetCurrentTime();
			szText.Format(_T("更新数据成功，时间[%s]"), dt.Format(_T("%Y-%m-%d %H:%M:%S")));
			m_StatusBar.UpdateStatus(szText, CCDStatusBar::STATUS_SUCCESS);
		}
		
		else
		{
			m_StatusBar.UpdateStatus(_T("更新数据失败，原因:") + pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
		}
	}
	else if (pBaseMsg->Header.type == ID_CUSTOM_ADD_ORDER)
	{
		COrderInquiryResultMsg* pMsg = (COrderInquiryResultMsg*)wparam;
		// 刷新视图
		CView1* pView1 = (CView1*)(m_wndSplitter.GetPane(0, 0));
		pView1->Update(pMsg);
	}
	delete pBaseMsg;

	return 0;
}

LRESULT CRecordDlg::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pMsg = (CBaseMsg*)wparam;
	pMsg->Header.userdata = (UINT)this;
	::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT, wparam, lparam);
	return 0;
}

LRESULT CRecordDlg::OnMsgInitComplete(WPARAM wparam, LPARAM lparam)
{
	QueryRequest();
	SetTimer(QUERY_TIMER_ID, QUERY_TIMER_INTERVAL, NULL);
	return 0;
}


void CRecordDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	m_StatusBar.DrawItem(&dc);
}

LRESULT CRecordDlg::OnMsgUpdateData(WPARAM wparam, LPARAM lparam)
{
	QueryRequest();
	return 0;
}

