// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainView.h"
#include "../Public/Config.h"
#include "../Public/MsgDefine.h"
#include "../Public/EnumDefine.h"
#include "../Public/TradeInfo.h"
#include "../Public/MsgBuilder.h"
#include "../Public/Utility.h"
#include "../Public/TradeInfo.h"
#include "../Public/Utility.h"

#define SPCAE_INFO_WIDTH	200

#define ID_REPORT_CONTROL 0x100
#define ID_REPORT_CONTROL2 0x101
#define TIME_BOOKING_ID 100
#define TIME_BOOKING_INTERVAL 1*1000 


#pragma warning(disable:4018)

//
class CLev2Reord : public CXTPReportRecord
{
public:
	CLev2Reord()
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		
		switch (pDrawArgs->pRow->GetIndex())
		{
		case 0:
		case 5:
			pItemMetrics->clrBackground = CConfig::Inst()->Level2Info()->clrBid16;
			break;
		case 1:
		case 6:
			pItemMetrics->clrBackground = CConfig::Inst()->Level2Info()->clrBid27;
			break;
		case 2:
		case 7:
			pItemMetrics->clrBackground = CConfig::Inst()->Level2Info()->clrBid38;
			break;
		case 3:
		case 8:
			pItemMetrics->clrBackground = CConfig::Inst()->Level2Info()->clrBid49;
			break;
		case 4:
		case 9:
			pItemMetrics->clrBackground = CConfig::Inst()->Level2Info()->clrBid510;
			break;
		}
		
	}
};

class CLev2Reord2 : public CXTPReportRecord
{
public:
	CLev2Reord2() :bSel(FALSE)
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		pItemMetrics->clrForeground = bSel ? RGB(0, 170, 0) : RGB(255, 0, 0);	
	}
	BOOL bSel;
};
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
: CFormView(IDD_MAINVIEW/*CMainView::IDD*/)
, m_nDefault(100)
, m_szTopLImitPrice(_T("N/A"))
, m_szBottomLImitPrice(_T("N/A"))
, m_szOpenPrice(_T("N/A"))
, m_szIncrease(_T("N/A"))
, m_szBP(_T("N/A"))
, m_szMatch(_T("N/A"))
, m_nAvailed(0)
, m_nBooking(0)
, m_nOrderRef(-1)
, m_StatusBar(this)
, m_bMaxSell(FALSE)
{

}

CMainView::~CMainView()
{
}

void CMainView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DEFAULT, m_nDefault);
	DDX_Control(pDX, IDC_CB_CODE, m_cbCode);
	DDX_Text(pDX, IDC_STATIC_ZHANG, m_szTopLImitPrice);
	DDX_Text(pDX, IDC_STATIC_DIE, m_szBottomLImitPrice);
	DDX_Text(pDX, IDC_STATIC_KAIPAN, m_szOpenPrice);
	DDX_Text(pDX, IDC_STATIC_ZHANGFU, m_szIncrease);
	DDX_Text(pDX, IDC_STATIC_ZIJIN, m_szBP);
	DDX_Text(pDX, IDC_STATIC_AVAILED, m_nAvailed);
	DDX_Text(pDX, IDC_STATIC_BOOKING, m_nBooking);
	DDX_Check(pDX, IDC_CHK_MAXSELL, m_bMaxSell);
	DDX_Text(pDX, IDC_STATIC_MATCH, m_szMatch);
}

BEGIN_MESSAGE_MAP(CMainView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_HOTKEY()
	ON_WM_ACTIVATE()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_CBN_SELCHANGE(IDC_CB_CODE, &CMainView::OnCbnSelchangeCbCode)
	ON_MESSAGE(UM_NOTIFY_CONFIG_REFRESH, &CMainView::OnConfigRefreshNotify)
	ON_COMMAND(1/*IDC_CB_CODE*/, &CMainView::OnComBoEditComplete)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CMainView::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CMainView::OnMsgSrvDataReport)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY2, &CMainView::OnMsgSrvDataNofity2)
	ON_MESSAGE(UM_SRV_DATA_REPORT2, &CMainView::OnMsgSrvDataReport2)
	ON_MESSAGE(UM_NOTIFY_INIT_COMPLETE, &CMainView::OnMsgInitComplete)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainView message handlers


void CMainView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT, CSize(1, 1));
}


int CMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	m_wndReport.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL);

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);
	m_wndReport.GetPaintManager()->m_strNoItems = _T("");

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("买"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("数量"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("数量"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("卖"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);


	m_wndReport2.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL2);

	m_wndReport2.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport2.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport2.SetGridStyle(FALSE, xtpReportLineStyleSolid);
	m_wndReport2.GetPaintManager()->m_strNoItems = _T("");


	pColumn = new CXTPReportColumn(0, _T("时间"), 100, FALSE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport2.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("价格"), 100, FALSE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport2.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("数量"), 100, FALSE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport2.AddColumn(pColumn);

	//
// 	m_dlgTrade.Create(this);
// 	m_dlgTrade.SetOwner(this);
// 	m_dlgTrade.ShowWindow(SW_HIDE);
	//

//	LoadData();
	return 0;
}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ( m_wndReport.GetSafeHwnd())
	{
		m_wndReport.MoveWindow(0, 70, 300, cy - 70 - CDCSTAUTSBAR_HEIGHT);
	}
	if (m_wndReport2.GetSafeHwnd())
	{
		m_wndReport2.MoveWindow(300, 70, cx - 300, cy - 70 - CDCSTAUTSBAR_HEIGHT);
	}

// 	if ( m_dlgTrade.GetSafeHwnd())
// 	{
// 		CRect rcThis, rcParent;
// 		GetWindowRect(&rcParent);
// 		ClientToScreen(rcThis);
// 
// 		m_dlgTrade.GetWindowRect(rcThis);
// 		
// 		int width = rcThis.Width();
// 		int height = rcThis.Height();
// 
// 		rcThis.top = rcParent.bottom - height - 20;
// 		rcThis.left = rcParent.left+20;
// 		rcThis.bottom = rcThis.top + height;
// 		rcThis.right = rcThis.left + width;
// 
// 		m_dlgTrade.MoveWindow(rcThis);
// 	}
}


void CMainView::OnDestroy()
{
	CTradeInfo::Inst()->DeleteStock(m_szLastCtockID);
	
	KillTimer(TIME_BOOKING_ID);

	CFormView::OnDestroy();

	// TODO: Add your message handler code here
}


HBRUSH CMainView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_ZHANG:
	case IDC_STATIC_ZHANGFU:
		pDC->SetTextColor(RGB(255, 0, 0));
		break;
	case IDC_STATIC_DIE:
		pDC->SetTextColor(RGB(0, 170, 0));
		break;
	}
	
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}

void CMainView::LoadData()
{
	for (int i = 0; i < 10; i++)
	{
		CXTPReportRecord* pRecord = new CLev2Reord();
		
		pRecord->AddItem(new CXTPReportRecordItemNumber(70.21+rand()%10));
		pRecord->AddItem(new CXTPReportRecordItemNumber(rand()%1000));
		pRecord->AddItem(new CXTPReportRecordItemNumber(rand() % 1000));
		pRecord->AddItem(new CXTPReportRecordItemNumber(60.21 + rand() % 10));
		m_wndReport.AddRecord(pRecord);
	}
	m_wndReport.Populate();

	for (int i = 0; i < 100; i++)
	{
		CXTPReportRecord* pRecord = new CLev2Reord2();

		pRecord->AddItem(new CXTPReportRecordItemText(_T("9:23:19")));
		pRecord->AddItem(new CXTPReportRecordItemNumber(70.21 + rand() % 10));
		pRecord->AddItem(new CXTPReportRecordItemNumber(rand() % 1000));
		m_wndReport2.AddRecord(pRecord);
	}
	m_wndReport2.Populate();
}


void CMainView::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CMainView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CFormView::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	
}

void CMainView::ShowTrade(int iMode)
{
	UpdateData();

	CString szStock = m_szLastCtockID;
	CString szText = CConfig::Inst()->StockInfo()->CodeToName(szStock);
	if ( szText.IsEmpty())
	{
		m_StatusBar.UpdateStatus(_T("无效的股票代码......"),CCDStatusBar::STATUS_ERROR);
		return;
	}
	else
		m_StatusBar.UpdateStatus(_T(""), CCDStatusBar::STATUS_SUCCESS);

	CLevel2Info::CHotKeySet* pHKS = CConfig::Inst()->Level2Info()->Item(iMode);

	CTradeInfoItem* pTradeItem = CTradeInfo::Inst()->GetStock(szStock);
	ASSERT(pTradeItem);

	CQTTradeInfo tradeInfo;
	tradeInfo.OrderType = pHKS->Direction;
	tradeInfo.PriceType = pHKS->Price;
	tradeInfo.Volume = pHKS->Count;
	tradeInfo.DefaultVolume = m_nDefault;
	tradeInfo.PriceOffset = pHKS->Offset;
	tradeInfo.bMaxSell = m_bMaxSell;
	tradeInfo.StockID = szStock;

	CTradeDlg dlg(this);
	dlg.SetInfo( &tradeInfo);
	if (dlg.DoModal() == IDOK)
	{
		if (dlg.m_nCount <= m_nBooking)
		{
			CPlaceOrderMsg* pMsg = new CPlaceOrderMsg();
			pMsg->OrderType = g_OrderTypeVal[tradeInfo.OrderType];
			pMsg->Price = dlg.m_dbPrice;
			pMsg->Volume = dlg.m_nCount;
			pMsg->OrderRef = CTradeInfo::Inst()->NextOrderInfo();
			pMsg->StockID = szStock;
			::PostMessage(GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
			m_StatusBar.UpdateStatus(_T("下达订单请求中......"));

			COrderInquiryResultMsg* pMsg2 = new COrderInquiryResultMsg();
			COrderInquiryResultMsg::COrders* Sorder = new COrderInquiryResultMsg::COrders();
			pMsg2->Orders.push_back(Sorder);

			// 这里把pMsg2的消息构造出来
			pMsg2->Header.type = ID_CUSTOM_ADD_ORDER;
			Sorder->Done = 0;
			Sorder->OrderRef = pMsg->OrderRef;
			Sorder->OrderID = "";
			Sorder->OrderType = pMsg->OrderType;
			Sorder->StockID = pMsg->StockID;
			Sorder->Volume = pMsg->Volume;
			Sorder->Price = pMsg->Price;
			Sorder->ExeVol = 0;
			Sorder->ExeAmount = 0;
			Sorder->ExePrice = 0;
			Sorder->Status = 0;
			Sorder->Error = 0;
			Sorder->ErrMsg = "";

			CString str; //获取系统时间
			CTime tm;
			tm = CTime::GetCurrentTime();
			str = tm.Format("%H%M%S000");

			Sorder->ReportTime = _tstol(LPCTSTR(str));

			::PostMessage(GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg2, 0);

			m_nOrderRef = pMsg->OrderRef;

			::SetActiveWindow(GetOwner()->GetSafeHwnd());
		}
		else
		{
			m_StatusBar.UpdateStatus(_T("预约卷数量不足......"), CCDStatusBar::STATUS_ERROR);
		}
	}
}


void CMainView::OnMoving(UINT fwSide, LPRECT pRect)
{
	CFormView::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
	
}


void CMainView::OnMove(int x, int y)
{
	CFormView::OnMove(x, y);

	// TODO: Add your message handler code here
// 	CRect rcThis, rcParent;
// 	GetWindowRect(&rcParent);
// 	ClientToScreen(rcThis);
// 
// 	m_dlgTrade.GetWindowRect(rcThis);
// 
// 	int width = rcThis.Width();
// 	int height = rcThis.Height();
// 
// 	rcThis.top = rcParent.bottom - height - 20;
// 	rcThis.left = rcParent.left + 20;
// 	rcThis.bottom = rcThis.top + height;
// 	rcThis.right = rcThis.left + width;
// 
// 	m_dlgTrade.MoveWindow(rcThis);
}


void CMainView::OnCbnSelchangeCbCode()
{
	// TODO: Add your control notification handler code here
	UpdateData(FALSE);
	
	CString szText;
	m_cbCode.GetLBText(m_cbCode.GetCurSel(), szText);
	szText.Trim();

	// 刷新数据
	LoadStockData(szText);

	// 更新标题
	szText = szText + _T(" - ") + CConfig::Inst()->StockInfo()->CodeToName(szText);
	GetParent()->SetWindowText(szText);

}

void CMainView::OnComBoEditComplete()
{
	
	CWnd* pWnd = GetFocus();
	pWnd = pWnd->GetOwner();
	if ( GetDlgItem(IDC_CB_CODE) != pWnd)
	{
		return;
	}

	// 获取ComboBox文本内容
	CString szText;
	m_cbCode.GetWindowText(szText);
	szText.Trim();

	BOOL bFind = FALSE;
	for (int i = 0; i < m_cbCode.GetCount(); i++)
	{
		CString szItem;
		m_cbCode.GetLBText(i, szItem);
		if ( szText == szItem)
		{
			bFind = TRUE;
			break;
		}
	}
	if ( bFind == FALSE)
	{
		m_cbCode.AddString(szText);
	}
	
	// 刷新数据
	LoadStockData(szText);

	// 更新标题
	szText = szText + _T(" - ") + CConfig::Inst()->StockInfo()->CodeToName(szText);
	GetParent()->SetWindowText(szText);
}

void CMainView::CancelOrder()
{
	if (m_nOrderRef == -1)
	{
		m_StatusBar.UpdateStatus(_T("没有可用的订单可撤销......"),CCDStatusBar::STATUS_ERROR);
		return;
	}

	if ( IDYES == MessageBox(_T("确认撤销最近一次订单?"),_T("提示"),MB_YESNO|MB_ICONQUESTION))
	{
		CCancelOrderMsg* pMsg = new CCancelOrderMsg();
		pMsg->OrderRef = m_nOrderRef;
		m_nOrderRef = -1;
		::PostMessage(GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
		m_StatusBar.UpdateStatus(_T("撤销订单请求中......"));
	}
}

LRESULT CMainView::OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam)
{
	m_wndReport.RedrawControl();
	return 0;
}

LRESULT CMainView::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	UpdateData();

	CBaseMsg* pBaseMsg = (CBaseMsg*)wparam;
	switch (pBaseMsg->Header.type)
	{
	case ID_BOOKING_INQUIRY_RESULT:	// 预约卷查询返回
		{
			CBookingInquiryResultMsg* pMsg = (CBookingInquiryResultMsg*)wparam;
			

			for (int i = 0; i < pMsg->Secs.size(); i++)
			{
				if (!m_szLastCtockID.CompareNoCase(pMsg->Secs[i]->StockID))
				{
					if (pMsg->Error == 0)
					{
						m_nBooking = pMsg->Secs[i]->Volume;
						CTradeInfoItem* pItem = CTradeInfo::Inst()->GetStock(m_szLastCtockID);
						ASSERT(pItem);
						pItem->BP = pMsg->Secs[i]->Volume;
						//m_StatusBar.UpdateStatus(_T("预约券查询成功"), CCDStatusBar::STATUS_SUCCESS);
					}
					else
					{
						m_StatusBar.UpdateStatus(_T("预约券查询错误，错误信息：") + pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
					}
					break;
				}
			}
		}
		break;
	case ID_PLACE_ORDER_RESULT:	// 订单返回
		{
			CPlaceOrderResultMsg* pMsg = (CPlaceOrderResultMsg*)wparam;
			if ( m_nOrderRef >= 0)
			{
				if (pMsg->Error == 0)
				{
					m_StatusBar.UpdateStatus(_T("下达订单成功"), CCDStatusBar::STATUS_SUCCESS);
				}
				else
				{
					m_StatusBar.UpdateStatus(_T("下达订单错误，错误信息：") + pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
				}
			}
		}
		break;
	case ID_CANCEL_ORDER_RESULT:	// 取消订单返回
		{
			CCancleOrderResultMsg* pMsg = (CCancleOrderResultMsg*)wparam;
			if (m_nOrderRef >= 0)
			{
				if (pMsg->Error == 0)
				{
					m_StatusBar.UpdateStatus(_T("取消订单成功"), CCDStatusBar::STATUS_SUCCESS);
				}
				else
				{
					m_StatusBar.UpdateStatus(_T("取消订单错误，错误信息：") + pMsg->ErrMsg, CCDStatusBar::STATUS_ERROR);
				}
			}
		}
		break;
	}

	delete pBaseMsg;

	UpdateData(FALSE);
	return 0;
}

LRESULT CMainView::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	return 0;
}

LRESULT CMainView::OnMsgInitComplete(WPARAM wparam, LPARAM lparam)
{
	m_szBP.Format(_T("%.2f"), CTradeInfo::Inst()->BP);
	UpdateData(FALSE);
	return 0;
}

void CMainView::LoadStockData(LPCTSTR StockId)
{
	CString szText;
	szText = CConfig::Inst()->StockInfo()->CodeToName(StockId);
	if (szText.IsEmpty())
	{
		m_StatusBar.UpdateStatus(_T("无效的股票代码......"), CCDStatusBar::STATUS_ERROR);
		return;
	}
	else
		m_StatusBar.UpdateStatus(_T(""), CCDStatusBar::STATUS_SUCCESS);

	KillTimer(TIME_BOOKING_ID);

	SetTimer(TIME_BOOKING_ID, TIME_BOOKING_INTERVAL, NULL);

	//预约卷查询
	//CBookingInquiryMsg* pMsg = new CBookingInquiryMsg();
	//pMsg->StockID = StockId;
	//::PostMessage(GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
	//m_StatusBar.UpdateStatus( _T("预约券查询请求中......"));

	// 订阅行情接口
//	if ( m_szLastCtockID != StockId)
	{
		ClearData();

		// 取消上一个股票
		CTradeInfo::Inst()->DeleteStock(m_szLastCtockID);
		
		// 订阅下一个股票
		CTradeInfo::Inst()->AddStock(StockId);

		m_szLastCtockID = StockId;

		
	}
	
}


void CMainView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CFormView::OnPaint() for painting messages
	dc.SetBkMode(TRANSPARENT);

	m_StatusBar.DrawItem(&dc);

	CRect rc;
	GetClientRect(&rc);
	rc.top = rc.bottom - CDCSTAUTSBAR_HEIGHT;
	rc.left = rc.right - SPCAE_INFO_WIDTH;

//	dc.FillSolidRect(rc, RGB(240, 240, 240));
	CTradeInfoItem* pTradeItem = CTradeInfo::Inst()->GetStock(m_szLastCtockID);
	CString szText;
	szText.Format(_T("仓位 : %u      "), pTradeItem==NULL?0:pTradeItem->Space);
	CFont font;
	font.CreatePointFont(90, _T("黑体"));
	dc.SelectObject(&font);
	dc.SetTextColor( RGB(0, 0, 0));
	dc.DrawText(szText, rc, DT_SINGLELINE | DT_VCENTER | DT_RIGHT);
}


BOOL CMainView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CFormView::OnEraseBkgnd(pDC);
}


void CMainView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	if (nIDEvent = TIME_BOOKING_ID)
	{
		CString szText;
		m_cbCode.GetWindowText(szText);;
		szText.Trim();

		CBookingInquiryMsg* pMsg = new CBookingInquiryMsg();
		pMsg->StockID = szText;
		::PostMessage(GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
	}

	CFormView::OnTimer(nIDEvent);
}

LRESULT CMainView::OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam)
{
	MsgHeader* pHeader = (MsgHeader*)wparam;
	switch (pHeader->type)
	{
	case ID_PRICE_PUSH:	// 行情推送
		UpdataPrice((MarketData*)(((char*)wparam) + sizeof(MsgHeader)));
		Invalidate();
		break;
	case ID_TRANSACTION_PUSH:	// 逐笔成交推送
		UpdataTrancation((Trasaction*)(((char*)wparam) + sizeof(MsgHeader)));
		break;
	default:
		ASSERT(0);
	}
	delete (char*)wparam;
	return 0;
}

LRESULT CMainView::OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam)
{
	return 0;
}

void CMainView::ClearData()
{
	m_wndReport.ResetContent();
	m_wndReport2.ResetContent();

	m_szTopLImitPrice = _T("N/A");
	m_szBottomLImitPrice = _T("N/A");
	m_szOpenPrice = _T("N/A");
	m_szIncrease = _T("N/A");
	m_szMatch = _T("N/A");
	UpdateData(FALSE);
}

void CMainView::UpdataPrice(MarketData* marketdata)
{
	USES_CONVERSION;
	if (!strcmp(marketdata->szCode, T2A(m_szLastCtockID)))
	{
		// 加载表格信息
		if (m_wndReport.GetRecords()->GetCount() == 0)
		{
			for (int i = 0; i < 10; i++)
			{
				CXTPReportRecord* pRecord = new CLev2Reord();

				pRecord->AddItem(new CXTPReportRecordItemNumber(PriceTrans(marketdata->nBidPrice[i]), _T("%.2f")));
				pRecord->AddItem(new CXTPReportRecordItemNumber(marketdata->nBidVol[i]));
				pRecord->AddItem(new CXTPReportRecordItemNumber(marketdata->nAskVol[i]));
				pRecord->AddItem(new CXTPReportRecordItemNumber(PriceTrans(marketdata->nAskPrice[i]), _T("%.2f")));
				m_wndReport.AddRecord(pRecord);
			}
			m_wndReport.Populate();
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				CXTPReportRecord* pRecord = m_wndReport.GetRecords()->GetAt(i);

				((CXTPReportRecordItemNumber*)(pRecord->GetItem(0)))->SetValue(PriceTrans(marketdata->nBidPrice[i]));
				((CXTPReportRecordItemNumber*)(pRecord->GetItem(1)))->SetValue((marketdata->nBidVol[i] + 99) / 100);
				((CXTPReportRecordItemNumber*)(pRecord->GetItem(2)))->SetValue((marketdata->nAskVol[i] + 99) / 100);
				((CXTPReportRecordItemNumber*)(pRecord->GetItem(3)))->SetValue(PriceTrans(marketdata->nAskPrice[i]));
				m_wndReport.UpdateRecord(pRecord, FALSE);
			}
		}

		UpdateData();
		// 更新价格信息
		m_szTopLImitPrice.Format(_T("%.2f"), PriceTrans(marketdata->nHighLimited));
		m_szBottomLImitPrice.Format(_T("%.2f"), PriceTrans(marketdata->nLowLimited));
		m_szOpenPrice.Format(_T("%.2f"), PriceTrans(marketdata->nOpen));
		m_szIncrease.Format(_T("%.2f"), marketdata->nPreClose == 0 ? 0 : ((int)(marketdata->nMatch - marketdata->nPreClose))*100.0 / marketdata->nPreClose);
		m_szMatch.Format(_T("%.2f"), PriceTrans(marketdata->nMatch));
		UpdateData(FALSE);
	}
}

void CMainView::UpdataTrancation(Trasaction* trasaction)
{
	USES_CONVERSION;
	if (!strcmp(trasaction->szCode, T2A(m_szLastCtockID)))
	{
		CLev2Reord2* pRecord = new CLev2Reord2();

		pRecord->AddItem(new CXTPReportRecordItemText(FormatTime(trasaction->nTime)));
		pRecord->AddItem(new CXTPReportRecordItemNumber(PriceTrans(trasaction->nPrice), _T("%.2f")));
		pRecord->AddItem(new CXTPReportRecordItemNumber((trasaction->nVolume + 99) / 100));
		pRecord->bSel = trasaction->nBSFlag == 'B';
		m_wndReport2.GetRecords()->InsertAt(0, pRecord);
		m_wndReport2.Populate();
		m_wndReport2.EnsureFocusedRowVisible(FALSE);
		m_wndReport2.EnsureVisible(m_wndReport2.GetRows()->GetAt(0));
	}
}
