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

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("����ID"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("��������"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("�ֲ�����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("��ӯ��"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(5, _T("ƽ����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(6, _T("��ֵ"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportCur.AddColumn(pColumn);

	//
	m_wndReportInfo.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), &m_wndTab, ID_REPORT_CONTROL_INFO);

	m_wndReportInfo.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReportInfo.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReportInfo.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	pColumn = new CXTPReportColumn(0, _T("���ñ�֤��"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("������"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
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

	pColumn = new CXTPReportColumn(4, _T("��ǰ�ֲֽ��"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportInfo.AddColumn(pColumn);

	//
	m_wndReportKuiYing.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), &m_wndTab, ID_REPORT_CONTROL_KuiYing);

	m_wndReportKuiYing.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReportKuiYing.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReportKuiYing.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	pColumn = new CXTPReportColumn(0, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("��ӯ"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("������"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReportKuiYing.AddColumn(pColumn);


	//
	m_PaneReserve.Create(IDD_STOCKCOUNTDLG, &m_wndTab);
	m_PaneLeft.Create(IDD_STOCKCOUNTDLG, &m_wndTab);

	//
	m_wndTab.AddTab( &m_wndReportCur, _T("��ǰ��λ"));
	m_wndTab.AddTab( &m_wndReportInfo, _T("������Ϣ"));
	m_wndTab.AddTab( &m_wndReportKuiYing, _T("����Ʊ��ӯ��Ϣ"));
	m_wndTab.AddTab(&m_PaneReserve, _T("ԤԼȯʣ������"));
	m_wndTab.AddTab(&m_PaneLeft, _T("����ȯʣ������"));
	//
	
	for (int i = 0; i < 10; i++)
	{
		CXTPReportRecord* pRecord = new CSpaceReordCur();
		pRecord->AddItem(new CXTPReportRecordItemText(_T("000001")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("�й�����")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("�ղ�")));
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
		pRecord->AddItem(new CXTPReportRecordItemText(_T("�й�����")));
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
