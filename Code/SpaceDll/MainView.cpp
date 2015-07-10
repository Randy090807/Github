// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "MainView.h"

#define ID_REPORT_CONTROL_CUR	0x105
#define ID_TAB					0x106
#define ID_REPORT_CONTROL_INFO	0x107
#define ID_REPORT_CONTROL_KuiYing	0x108
// CMainView

//
class CSpaceReordCur : public CXTPReportRecord
{
public:
	CSpaceReordCur()
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		pItemMetrics->clrForeground = RGB(0, 170, 0);
	}
};

IMPLEMENT_DYNCREATE(CMainView, CView)

CMainView::CMainView()
{

}

CMainView::~CMainView()
{
}

BEGIN_MESSAGE_MAP(CMainView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, ID_TAB, &CMainView::OnTabSelectChange)
END_MESSAGE_MAP()


// CMainView drawing

void CMainView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CMainView diagnostics

#ifdef _DEBUG
void CMainView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainView message handlers


void CMainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}


int CMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code herepColumn->
	m_PaneBottom.Create(IDD_BOTTOMPANE, this);
	m_PaneBottom.ShowWindow(SW_SHOW);
	
	//
	m_wndTab.Create(CMFCTabCtrl::STYLE_3D_VS2005, CRect(0, 0, 0, 0), this, ID_TAB, CMFCBaseTabCtrl::LOCATION_TOP);

	//
	m_wndReportCur.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), &m_wndTab, ID_REPORT_CONTROL_CUR);

	m_wndReportCur.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReportCur.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReportCur.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("代码ID"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("中文名称"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("方向"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("持仓数量"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("浮盈亏"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(5, _T("平均价"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(6, _T("市值"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	//
	m_wndReportInfo.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), &m_wndTab, ID_REPORT_CONTROL_INFO);

	m_wndReportInfo.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReportInfo.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReportInfo.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	pColumn = new CXTPReportColumn(0, _T("可用保证金"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("手续费"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("Stop Loss"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("Loss From Top"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("当前持仓金额"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	//
	m_wndReportKuiYing.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), &m_wndTab, ID_REPORT_CONTROL_KuiYing);

	m_wndReportKuiYing.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReportKuiYing.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReportKuiYing.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	pColumn = new CXTPReportColumn(0, _T("代码"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("名称"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("亏盈"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("手续费"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);


	//
	m_PaneReserve.Create(IDD_STOCKCOUNTDLG, &m_wndTab);
	m_PaneLeft.Create(IDD_STOCKCOUNTDLG, &m_wndTab);

	//
	m_wndTab.AddTab( &m_wndReportCur, _T("当前仓位"));
	m_wndTab.AddTab( &m_wndReportInfo, _T("个人信息"));
	m_wndTab.AddTab( &m_wndReportKuiYing, _T("各股票亏盈信息"));
	m_wndTab.AddTab(&m_PaneReserve, _T("预约券剩余数量"));
	m_wndTab.AddTab(&m_PaneLeft, _T("可容券剩余数量"));
	//
	
	for (int i = 0; i < 10; i++)
	{
		CXTPReportRecord* pRecord = new CSpaceReordCur();
		pRecord->AddItem(new CXTPReportRecordItemText(_T("000001")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("中国银行")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("空仓")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("29382")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("0.39")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("839.23")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("12338.82")));
		m_wndReportCur.AddRecord(pRecord);
	}
	m_wndReportCur.Populate();

	for (int i = 0; i < 1; i++)
	{
		CXTPReportRecord* pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText(_T("9283942.23")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("23.92")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("10000")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("23.23")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("2932342.12")));
		m_wndReportInfo.AddRecord(pRecord);
	}
	m_wndReportInfo.Populate();

	for (int i = 0; i < 5; i++)
	{
		CXTPReportRecord* pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText(_T("000001")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("中国银行")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("0.39")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("839.23")));
		m_wndReportKuiYing.AddRecord(pRecord);
	}
	m_wndReportKuiYing.Populate();
	return 0;
}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_PaneBottom.GetSafeHwnd())
	{
		m_PaneBottom.MoveWindow(0, cy - 110, cx, 110);
	}
	if (m_wndTab.GetSafeHwnd())
	{
		m_wndTab.MoveWindow(0, 0, cx, cy - 110);
	}

}


void CMainView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
}

void CMainView::OnTabSelectChange(LPNMHDR lpNMHDR, LRESULT* pResult)
{
	
}
