// View1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View1.h"
#include "ModOrderDlg.h"
#include "../Public/ReportCtrlLayout.h"
#include "../Public/Application.h"
#include "../Public/Config.h"
#include "../Public/MsgDefine.h"
#include "../Public/TradeInfo.h"

#define ID_REPORT_CONTROL 0x103
// CView1

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CView1, CFormView)

CView1::CView1()
: CFormView(IDD_VIEW1/*CView1::IDD*/)
, m_bCancelTip(CConfig::Inst()->RecordInfo()->bCancelTip)
, m_bWasteResend(CConfig::Inst()->RecordInfo()->bWasteReSend)
, m_bErrorResend(CConfig::Inst()->RecordInfo()->bErrorReSend)
, m_pMsgReciver(NULL)
{

}

CView1::~CView1()
{
}

void CView1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHK_CeDanTiShi, m_bCancelTip);
	DDX_Check(pDX, IDC_CHK_FeiDanChongFa, m_bWasteResend);
	DDX_Check(pDX, IDC_CHK_CuoDanChongFa, m_bErrorResend);
}

BEGIN_MESSAGE_MAP(CView1, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(NM_RCLICK, ID_REPORT_CONTROL, OnReportItemRClick)
	ON_BN_CLICKED(IDC_CHK_CeDanTiShi, &CView1::OnBnClickedChkCedantishi)
	ON_BN_CLICKED(IDC_CHK_FeiDanChongFa, &CView1::OnBnClickedChkFeidanchongfa)
	ON_BN_CLICKED(IDC_CHK_CuoDanChongFa, &CView1::OnBnClickedChkCuodanchongfa)
	ON_MESSAGE(UM_NOTIFY_CONFIG_REFRESH, &CView1::OnConfigRefreshNotify)
END_MESSAGE_MAP()


// CView1 diagnostics

#ifdef _DEBUG
void CView1::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CView1::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView1 message handlers


int CView1::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_wndReport.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL);
	m_wndReport.CreateColumns();

	CReportCtrlLayout::Layout(CApplication::DataDir() + _T("\\Layout1.xml"), &m_wndReport);
	
	LoadData();
	return 0;
}


void CView1::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CWnd* pWnd = GetDlgItem(IDC_CHK_CeDanTiShi);
	CRect rc;
	int width = 0;
	if ( pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 450;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}
	pWnd = GetDlgItem(IDC_CHK_FeiDanChongFa);
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 300;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}
	pWnd = GetDlgItem(IDC_CHK_CuoDanChongFa);
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 150;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}

	if (m_wndReport.GetSafeHwnd())
	{
		m_wndReport.MoveWindow(30, 30, cx - 30, cy - 30);
	}
}


void CView1::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
	CReportCtrlLayout::SaveLayout(CApplication::DataDir() + _T("\\layout1.xml"), &m_wndReport);
}


void CView1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT, CSize(1, 1));
}

void CView1::LoadData()
{

}

void CView1::CancelOrder()
{
	UpdateData();

	if (m_wndReport.GetSelectedRows()->GetCount() == 0)
	{
		return;
	}
	if ( m_bCancelTip == TRUE)
	{
		if (IDYES == MessageBox(_T("提示，是否执行撤单或者批量撤单操作？"), _T("提示"), MB_YESNO | MB_ICONQUESTION))
		{
			for (int i = 0; i < m_wndReport.GetSelectedRows()->GetCount(); i++)
			{
				COrderRecord* pRecord = (COrderRecord*)(m_wndReport.GetSelectedRows()->GetAt(i)->GetRecord());
				CCancelOrderMsg* pMsg = new CCancelOrderMsg();
				pMsg->OrderRef = pRecord->GetOrderRef();
				::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
			}
			NotifyUpdate();
		}
	}
}

void CView1::ClearOrder()
{
	UpdateData();

	if (m_wndReport.GetSelectedRows()->GetCount() == 0)
	{
		return;
	}
	if (m_bCancelTip == TRUE)
	{
		if (IDYES == MessageBox(_T("提示，是否执行全部撤单操作？"), _T("提示"), MB_YESNO | MB_ICONQUESTION))
		{
			for (int i = 0; i <m_wndReport.GetRecords()->GetCount(); i++)
			{
				COrderRecord* pRecord = (COrderRecord*)(m_wndReport.GetRecords()->GetAt(i));
				CCancelOrderMsg* pMsg = new CCancelOrderMsg();
				pMsg->OrderRef = pRecord->GetOrderRef();
				::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
			}
			NotifyUpdate();
		}
	}
}

void CView1::ModifyOrder()
{
	UpdateData();

	if (m_wndReport.GetSelectedRows()->GetCount() == 0)
	{
		return;
	}

	COrderRecord* pRecord = (COrderRecord*)(m_wndReport.GetSelectedRows()->GetAt(0)->GetRecord());

	int		count = pRecord->GetVolume();
	double	price = pRecord->GetPrice();
	int		left = 0;

	CModOrderDlg dlg;
	dlg.m_nCount = count;
	dlg.m_dbPrice = price;
	if ( dlg.DoModal() == IDOK)
	{
		left = count - dlg.m_nCount;
		count = min(count, dlg.m_nCount);
		price = dlg.m_dbPrice;

		// 测销之前订单
		{
			CCancelOrderMsg* pMsg = new CCancelOrderMsg();
			pMsg->OrderRef = pRecord->GetOrderRef();
			::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
		}

		// 重新下单
		{
			CPlaceOrderMsg* pMsg = new CPlaceOrderMsg();
			pMsg->OrderType = _T("1a");
			pMsg->Price = price;
			pMsg->Volume = count;
			pMsg->OrderRef = CTradeInfo::Inst()->NextOrderInfo();
			pMsg->StockID = pRecord->GetStock();
			
			::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
		}

		// 剩余数量按照涨停融券卖出
		if ( left > 0)
		{
			CPlaceOrderMsg* pMsg = new CPlaceOrderMsg();
			pMsg->OrderType = _T("1a");
			pMsg->Price = price;
			pMsg->Volume = left;
			pMsg->OrderRef = CTradeInfo::Inst()->NextOrderInfo();
			pMsg->StockID = pRecord->GetStock();

			::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
		}
		NotifyUpdate();
	}
}

void CView1::OnReportItemRClick(NMHDR* pNotifyStruct, LRESULT *)
{
	XTP_NM_REPORTRECORDITEM* pNMGV = (XTP_NM_REPORTRECORDITEM*)(pNotifyStruct);

	CPoint point;
	GetCursorPos(&point);

	if (point.x == -1 && point.y == -1)
	{
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);
		ClientToScreen(rect);

		point = rect.TopLeft();
		point.Offset(5, 5);
	}

	CMenu menu;
	VERIFY(menu.CreatePopupMenu());

	menu.AppendMenu(MF_STRING, 0x11, _T("撤单"));
	menu.AppendMenu(MF_STRING, 0x12, _T("全部撤单"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, 0x13, _T("改单"));
	menu.AppendMenu(MF_SEPARATOR);
	menu.AppendMenu(MF_STRING, 0x14, _T("保存订单"));
	
	int nCmd = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD
		, point.x, point.y, this);
	switch (nCmd)
	{
	case 0x11:
		CancelOrder();
		break;
	case 0x12:
		ClearOrder();
		break;
	case 0x13:
		ModifyOrder();
		break;
	case 0x14:
		SaveOrder();
		break;
	}

}

void CView1::SaveOrder()
{
	CFileDialog dlg(FALSE,_T(".txt"), _T("order"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("txt docment(*.txt)|*.txt|All File(*.*)|*.*||"));
	if ( dlg.DoModal() == IDOK)
	{
	}
}


void CView1::OnBnClickedChkCedantishi()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CConfig::Inst()->RecordInfo()->bCancelTip = m_bCancelTip;
}


void CView1::OnBnClickedChkFeidanchongfa()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CConfig::Inst()->RecordInfo()->bWasteReSend = m_bWasteResend;
}


void CView1::OnBnClickedChkCuodanchongfa()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CConfig::Inst()->RecordInfo()->bErrorReSend = m_bErrorResend;
}

LRESULT CView1::OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam)
{
	m_wndReport.RedrawControl();
	return 0;
}


void CView1::Update(COrderInquiryResultMsg* pMsg)
{
	for (vector<COrderInquiryResultMsg::COrders*>::iterator iter = pMsg->Orders.begin();
		iter != pMsg->Orders.end(); ++iter)
	{
		m_wndReport.AddRecord(*iter);
	}
	m_wndReport.Populate();
}

void CView1::NotifyUpdate()
{
	::PostMessage(m_pMsgReciver->GetSafeHwnd(), WM_USER + 0x700, 0, 0);
}

void CView1::SetMsgReciver(CWnd* pWnd)
{
	ASSERT(pWnd);
	m_pMsgReciver = pWnd;
}

