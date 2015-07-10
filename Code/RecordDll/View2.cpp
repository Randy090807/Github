// View2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View2.h"

#define ID_REPORT_CONTROL	0x104
// CView2

IMPLEMENT_DYNCREATE(CView2, CFormView)

CView2::CView2()
: CFormView(IDD_VIEW2/*CView2::IDD*/)
{

}

CView2::~CView2()
{
}

void CView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CView2, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CView2 diagnostics

#ifdef _DEBUG
void CView2::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CView2 message handlers


int CView2::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_wndReport.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL);

	m_wndReport.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("�ͻ��˶���ID"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("ʱ��"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(5, _T("�͵��۸�"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(6, _T("�ɽ��۸�"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(7, _T("�͵�����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(8, _T("�ɽ�����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(9, _T("��ʽ"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(10, _T("�ɽ����"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(11, _T("ȯ�̵���"), 100, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(12, _T("��Ϣ"), 100, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	LoadData();
	return 0;
}


void CView2::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_wndReport.GetSafeHwnd())
	{
		m_wndReport.MoveWindow(30, 0, cx - 30, cy);
	}
}


void CView2::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
}


void CView2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	SetScrollSizes(MM_TEXT, CSize(1, 1));
}


void CView2::LoadData()
{
	m_wndReport.ResetContent(FALSE);

	for (int i = 0; i < 10; i++)
	{
		CXTPReportRecord* pRecord = new CXTPReportRecord();

		pRecord->AddItem(new CXTPReportRecordItemText(_T("201302931")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("13:32:49")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("000009")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("�Ϻ�����")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("��")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("89.32")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("90.28")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("200")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("200")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("����Ʒ����")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("�ɽ�")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("283943")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("û�б�ע")));

		m_wndReport.AddRecord(pRecord);
	}

	m_wndReport.Populate();
}