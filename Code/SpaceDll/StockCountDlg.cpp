// StockCountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StockCountDlg.h"
#include "afxdialogex.h"
#include "../Public/MsgDefine.h"
#include "../Public/Config.h"

#define ID_REPORT_CONTROL	0x110
// CStockCountDlg dialog

IMPLEMENT_DYNAMIC(CStockCountDlg, CDialogEx)

CStockCountDlg::CStockCountDlg(int nMode, CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_STOCKCOUNTDLG/*CStockCountDlg::IDD*/, pParent)
, m_nMode(nMode)
{

}

CStockCountDlg::~CStockCountDlg()
{
}

void CStockCountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStockCountDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_FREASH, &CStockCountDlg::OnBnClickedBtnFreash)
END_MESSAGE_MAP()


// CStockCountDlg message handlers


int CStockCountDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	
	m_wndReport.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL);

	m_wndReport.GetReportHeader()->AllowColumnRemove(TRUE);
	m_wndReport.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport.SetGridStyle(FALSE, xtpReportLineStyleSolid);

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("代码ID"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(1, _T("名称"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

	pColumn = new CXTPReportColumn(2, _T("剩余数量"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);

// 	for (int i = 0; i < 10; i++)
// 	{
// 		CXTPReportRecord* pRecord = new CXTPReportRecord();
// 		pRecord->AddItem(new CXTPReportRecordItemText(_T("000001")));
// 		pRecord->AddItem(new CXTPReportRecordItemText(_T("中国银行")));
// 		pRecord->AddItem(new CXTPReportRecordItemText(_T("928329")));
// 		m_wndReport.AddRecord(pRecord);
// 	}
// 	m_wndReport.Populate();

	return 0;
}


void CStockCountDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CWnd* pWnd = GetDlgItem(IDC_BTN_FREASH);
	CRect rc;
	
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		int width = rc.Width();
		int height = rc.Height();

		rc.right = cx - 10;
		rc.left = rc.right - width;
		rc.bottom = cy - 3;
		rc.top = rc.bottom - height;

		pWnd->MoveWindow(rc);
	}

	if ( m_wndReport.GetSafeHwnd())
	{
		m_wndReport.MoveWindow(0, 0, cx, cy - 30);
	}
}


void CStockCountDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CStockCountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CStockCountDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect rc;
	GetClientRect(&rc);

	dc.FillSolidRect(rc, RGB(255, 255, 255));
}

BOOL CStockCountDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CStockCountDlg::OnBnClickedBtnFreash()
{
	// TODO: Add your control notification handler code here
	m_wndReport.ResetContent(TRUE);

	if ( m_nMode == 0)	// 预约券查询
	{
		CBookingInquiryMsg* pMsg = new CBookingInquiryMsg();
		::PostMessage(GetParent()->GetParent()->GetSafeHwnd(), UM_SRV_DATA_REPORT, (WPARAM)pMsg, 0);
	}
}

void CStockCountDlg::Updata(CBookingInquiryResultMsg* pMsg)
{
	for (auto iter = pMsg->Secs.begin(); iter != pMsg->Secs.end(); ++iter)
	{
		CXTPReportRecord* pRecord = new CXTPReportRecord();
		pRecord->AddItem(new CXTPReportRecordItemText( (*iter)->StockID));
		pRecord->AddItem(new CXTPReportRecordItemText(CConfig::Inst()->StockInfo()->CodeToName((*iter)->StockID)));
		pRecord->AddItem(new CXTPReportRecordItemNumber((*iter)->Volume));
		m_wndReport.AddRecord(pRecord);
	}
	m_wndReport.Populate();
}
