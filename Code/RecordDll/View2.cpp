// View2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View2.h"
#include "../Public/ReportCtrlLayout.h"
#include "../Public/Application.h"
#include "../Public/Config.h"
#include "../Public/MsgDefine.h"

#define ID_REPORT_CONTROL	0x104
// CView2

//
class CView2Reord : public CXTPReportRecord
{
public:
	CView2Reord()
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		UINT count = _ttoi(pDrawArgs->pRow->GetRecord()->GetItem(8)->GetCaption());
		CString code = pDrawArgs->pRow->GetRecord()->GetItem(2)->GetCaption();
		
		for (int i = 0; i < CConfig::Inst()->RecordInfo()->BOSize(); i++)
		{
			CRecordInfo::CBigOrderInfo* pBOI = CConfig::Inst()->RecordInfo()->Item(i);
			if ( pBOI->code.CompareNoCase(code) == 0
				&& pBOI->count <= count)
			{
				pItemMetrics->clrBackground = CConfig::Inst()->RecordInfo()->clrBOColor;
			}
		}
	}
};

//////////////////////////////////////////////////////////////////////////
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
	ON_NOTIFY(NM_RCLICK, ID_REPORT_CONTROL, OnReportItemRClick)
	ON_MESSAGE(UM_NOTIFY_CONFIG_REFRESH, &CView2::OnConfigRefreshNotify)
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

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("客户端订单ID"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("时间"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("代码"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(3, _T("名称"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(4, _T("方向"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(5, _T("送单价格"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(6, _T("成交价格"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(7, _T("送单股数"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(8, _T("成交股数"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(9, _T("方式"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(10, _T("成交与否"), 70, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(11, _T("券商单号"), 100, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(12, _T("信息"), 100, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	CReportCtrlLayout::Layout(CApplication::DataDir() + _T("\\layout2.xml"), &m_wndReport);

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
	CReportCtrlLayout::SaveLayout(CApplication::DataDir() + _T("\\layout2.xml"), &m_wndReport);
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
		CXTPReportRecord* pRecord = new CView2Reord();

		pRecord->AddItem(new CXTPReportRecordItemText(_T("201302931")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("13:32:49")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("600009")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("上海机场")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("买")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("89.32")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("90.28")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("1000")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("1000")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("担保品买入")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("成交")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("283943")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("没有备注")));

		m_wndReport.AddRecord(pRecord);
	}

	m_wndReport.Populate();
}


void CView2::OnReportItemRClick(NMHDR* pNotifyStruct, LRESULT *)
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

	menu.AppendMenu(MF_STRING, 0x14, _T("保存订单"));

	int nCmd = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD
		, point.x, point.y, this);
	switch (nCmd)
	{
	case 0x14:
		SaveOrder();
		break;
	}

}

void CView2::SaveOrder()
{
	CFileDialog dlg(FALSE, _T("txt"), NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
		_T("txt docment(*.txt)|*.txt|All File(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
	}
}

LRESULT CView2::OnConfigRefreshNotify(WPARAM wparam, LPARAM lparam)
{
	m_wndReport.RedrawControl();
	return 0;
}
