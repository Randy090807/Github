// SpaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpaceDlg.h"
#include "afxdialogex.h"
#include "MainView.h"
#include "Resource.h"
#include "../Public/MsgDefine.h"
// CSpaceDlg dialog

#define TIMER_ID		100
#define TIMER_INTERVAL	1000*1

IMPLEMENT_DYNAMIC(CSpaceDlg, CDialogEx)

CSpaceDlg::CSpaceDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_SPACE/*CSpaceDlg::IDD*/, pParent)
	, m_pView(NULL)
	, m_StatusBar(this)
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
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CSpaceDlg::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CSpaceDlg::OnMsgSrvDataReport)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY2, &CSpaceDlg::OnMsgSrvDataNofity2)
	ON_MESSAGE(UM_SRV_DATA_REPORT2, &CSpaceDlg::OnMsgSrvDataReport2)
	ON_MESSAGE(UM_NOTIFY_INIT_COMPLETE, &CSpaceDlg::OnMsgInitComplete)
	ON_WM_PAINT()
	ON_WM_TIMER()
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

	m_StatusBar.UpdateStatus(_T("初始化完毕......"), CCDStatusBar::STATUS_NORMAL);
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
		m_pView->MoveWindow(0, 0, cx, cy - CDCSTAUTSBAR_HEIGHT);
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

LRESULT CSpaceDlg::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	CBaseResultMsg* pBaseMsg = (CBaseResultMsg*)wparam;
	switch (pBaseMsg->Header.type)
	{
	case ID_POSITION_INQUIRY_RESULT:
	case ID_TRANSACTION_RECORDS_RESULT:
	case ID_BOOKING_INQUIRY_RESULT:
		{
			CPositionInquryResultMsg* pMsg = (CPositionInquryResultMsg*)wparam;
			if ( pMsg->Error == 0)
			{
				CString szText;
				COleDateTime dt = COleDateTime::GetCurrentTime();
				szText.Format(_T("更新数据成功，时间[%s]"), dt.Format(_T("%Y-%m-%d %H:%M:%S")));
				m_StatusBar.UpdateStatus(szText, CCDStatusBar::STATUS_SUCCESS);

				::PostMessage(m_pView->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, wparam, lparam);
			}
			else
			{
				m_StatusBar.UpdateStatus(pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
				delete pMsg;
			}
		}
		break;
	case ID_PLACE_ORDER_RESULT:
		{
			CPlaceOrderResultMsg* pMsg = (CPlaceOrderResultMsg*)wparam;
			if (pMsg->Error == 0)
			{
				m_StatusBar.UpdateStatus(_T("平仓处理成功......"), CCDStatusBar::STATUS_SUCCESS);
				::PostMessage(m_pView->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, wparam, lparam);
			}
			else
			{
				m_StatusBar.UpdateStatus(pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
				delete pMsg;
			}
		}
		break;
	default:
		ASSERT(0);
	}
//	
	return 0;
}

LRESULT CSpaceDlg::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pMsg = (CBaseMsg*)wparam;
	pMsg->Header.userdata = (UINT)this;
	

	switch (pMsg->Header.type)
	{
	case ID_POSITION_INQUIRY:
	case ID_TRANSACTION_RECORDS:
	case ID_BOOKING_INQUIRY:
		m_StatusBar.UpdateStatus(_T("更新数据中......"), CCDStatusBar::STATUS_NORMAL);
		break;
	case ID_PLACE_ORDER:
		m_StatusBar.UpdateStatus(_T("平仓处理中......"), CCDStatusBar::STATUS_NORMAL);
		break;
	case ID_CUSTOM_ADD_ORDER:
		break;
	default:
		ASSERT(0);
	}

	::PostMessage(GetOwner()->GetSafeHwnd(), UM_SRV_DATA_REPORT, wparam, lparam);
	return 0;
}

LRESULT CSpaceDlg::OnMsgInitComplete(WPARAM wparam, LPARAM lparam)
{
	QueryRequest();
	SetTimer(TIMER_ID, TIMER_INTERVAL, NULL);
	return 0;
}


void CSpaceDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	m_StatusBar.DrawItem(&dc);

	CRect rcClient;
	GetClientRect(&rcClient);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(100, 100, 100));
	dc.SelectObject(&pen);
	dc.MoveTo(0, rcClient.bottom - CDCSTAUTSBAR_HEIGHT+2);
	dc.LineTo(rcClient.right, rcClient.bottom - CDCSTAUTSBAR_HEIGHT+2);
}


void CSpaceDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if ( nIDEvent == TIMER_ID)
	{
		QueryRequest();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CSpaceDlg::QueryRequest()
{
	CBaseMsg* pMsg = new CPositionInquryMsg();
	PostMessage(UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);

	pMsg = new CTransactionRecordsMsg();
	PostMessage(UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
}

LRESULT CSpaceDlg::OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam)
{
	delete (char*)wparam;
	return 0;
}

LRESULT CSpaceDlg::OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam)
{
	delete (char*)wparam;
	return 0;
}
