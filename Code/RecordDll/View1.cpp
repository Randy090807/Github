// View1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View1.h"

#define ID_REPORT_CONTROL 0x103
// CView1

IMPLEMENT_DYNCREATE(CView1, CFormView)

CView1::CView1()
: CFormView(IDD_VIEW1/*CView1::IDD*/)
{

}

CView1::~CView1()
{
}

void CView1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CView1, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
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

	m_wndReport.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("客户端订单ID"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("时间"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("代码"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("名称"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("方向"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(5, _T("送单价格"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(6, _T("成交价格"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(7, _T("送单股数"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(8, _T("成交股数"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(9, _T("方式"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(10, _T("成交与否"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(11, _T("信息"), 100, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

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
}


void CView1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT, CSize(1, 1));
}

void CView1::LoadData()
{
	m_wndReport.ResetContent(FALSE);

	for (int i = 0; i < 3; i++)
	{
		CXTPReportRecord* pRecord = new CXTPReportRecord();

		pRecord->AddItem(new CXTPReportRecordItemText(_T("201302931")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("13:32:49")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("000009")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("上海机场")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("买")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("89.32")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("90.28")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("200")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("200")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("担保品买入")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("已报")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("没有备注")));

		m_wndReport.AddRecord(pRecord);
	}

	m_wndReport.Populate();
}
