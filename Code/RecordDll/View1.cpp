// View1.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View1.h"
#include "ModOrderDlg.h"
#include "../Public/ReportCtrlLayout.h"
#include "../Public/Application.h"
#include "../Public/Config.h"

#define ID_REPORT_CONTROL 0x103
// CView1

//
class CView1Reord : public CXTPReportRecord
{
public:
	CView1Reord()
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		UINT count = _ttoi(pDrawArgs->pRow->GetRecord()->GetItem(8)->GetCaption());
		CString code = pDrawArgs->pRow->GetRecord()->GetItem(2)->GetCaption();

		for (int i = 0; i < CConfig::Inst()->RecordInfo()->BOSize(); i++)
		{
			CRecordInfo::CBigOrderInfo* pBOI = CConfig::Inst()->RecordInfo()->Item(i);
			if (pBOI->code.CompareNoCase(code) == 0
				&& pBOI->count <= count)
			{
				pItemMetrics->clrBackground = CConfig::Inst()->RecordInfo()->clrBOColor;
			}
		}
	}
};
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CView1, CFormView)

CView1::CView1()
: CFormView(IDD_VIEW1/*CView1::IDD*/)
, m_bCancelTip(CConfig::Inst()->RecordInfo()->bCancelTip)
, m_bWasteResend(CConfig::Inst()->RecordInfo()->bWasteReSend)
, m_bErrorResend(CConfig::Inst()->RecordInfo()->bErrorReSend)
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

	m_wndReport.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);
	m_wndReport.GetReportHeader()->AllowColumnResize(TRUE);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("客户端订单ID"), 70, FALSE , XTP_REPORT_NOICON, TRUE);
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
	pColumn->EnableResize(TRUE);
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

	pColumn = new CXTPReportColumn(11, _T("信息"), 100, FALSE, XTP_REPORT_NOICON, TRUE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	pColumn->EnableResize(TRUE);
	m_wndReport.AddColumn(pColumn);

	CReportCtrlLayout::Layout(CApplication::DataDir() + _T("\\layout1.xml"), &m_wndReport);
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
	m_wndReport.ResetContent(FALSE);

	for (int i = 0; i < 3; i++)
	{
		CXTPReportRecord* pRecord = new CView1Reord();

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
		pRecord->AddItem(new CXTPReportRecordItemText(_T("已报")));
		pRecord->AddItem(new CXTPReportRecordItemText(_T("没有备注")));

		m_wndReport.AddRecord(pRecord);
	}

	m_wndReport.Populate();
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
		if (IDYES != MessageBox(_T("提示，是否执行撤单或者批量撤单操作？"), _T("提示"), MB_YESNO | MB_ICONQUESTION))
		{
			return;
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
		if (IDYES != MessageBox(_T("提示，是否执行全部撤单操作？"), _T("提示"), MB_YESNO | MB_ICONQUESTION))
		{
			return;
		}
	}
}

void CView1::ModifyOrder()
{
	CModOrderDlg dlg;
	if ( dlg.DoModal() == IDOK)
	{
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
