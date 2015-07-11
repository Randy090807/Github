// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MainView.h"

#define ID_REPORT_CONTROL 0x100
#define ID_REPORT_CONTROL2 0x101


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
			pItemMetrics->clrBackground = RGB(255, 0, 0);
			break;
		case 1:
		case 6:
			pItemMetrics->clrBackground = RGB(128, 192, 203);
			break;
		case 2:
		case 7:
			pItemMetrics->clrBackground = RGB(255, 218, 185);
			break;
		case 3:
		case 8:
			pItemMetrics->clrBackground = RGB(218, 165, 32);
			break;
		case 4:
		case 9:
			pItemMetrics->clrBackground = RGB(255, 255, 0);
			break;
		}
		
	}
};

class CLev2Reord2 : public CXTPReportRecord
{
public:
	CLev2Reord2()
	{

	}

	void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
	{
		if ( pDrawArgs->pRow->GetIndex()%3)
		{
			pItemMetrics->clrForeground = RGB(0, 170, 0);
		}
		else
		{
			pItemMetrics->clrForeground =  RGB(255, 0, 0);
		}
		
	}
};
// CMainView

IMPLEMENT_DYNCREATE(CMainView, CFormView)

CMainView::CMainView()
: CFormView(IDD_MAINVIEW/*CMainView::IDD*/)
, m_nDefault(100)
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

	CXTPReportColumn* pColumn = new CXTPReportColumn(0, _T("Bid"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
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

	pColumn = new CXTPReportColumn(3, _T("Ask"), 70, TRUE, XTP_REPORT_NOICON, FALSE);
	pColumn->SetAlignment(DT_VCENTER | DT_CENTER);
	pColumn->SetHeaderAlignment(DT_VCENTER | DT_CENTER);
	m_wndReport.AddColumn(pColumn);


	m_wndReport2.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 0, 0), this, ID_REPORT_CONTROL2);

	m_wndReport2.GetReportHeader()->AllowColumnRemove(FALSE);
	m_wndReport2.SetGridStyle(TRUE, xtpReportLineStyleSolid);
	m_wndReport2.SetGridStyle(FALSE, xtpReportLineStyleSolid);

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
	m_dlgTrade.Create(this);
	m_dlgTrade.SetOwner(this);
	m_dlgTrade.ShowWindow(SW_HIDE);
	//

	LoadData();
	return 0;
}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if ( m_wndReport.GetSafeHwnd())
	{
		m_wndReport.MoveWindow(0, 70, 300, cy - 70);
	}
	if (m_wndReport2.GetSafeHwnd())
	{
		m_wndReport2.MoveWindow(300, 70, cx - 300, cy - 70);
	}

	if ( m_dlgTrade.GetSafeHwnd())
	{
		CRect rcThis, rcParent;
		GetWindowRect(&rcParent);
		ClientToScreen(rcThis);

		m_dlgTrade.GetWindowRect(rcThis);
		
		int width = rcThis.Width();
		int height = rcThis.Height();

		rcThis.top = rcParent.bottom - height - 20;
		rcThis.left = rcParent.left+20;
		rcThis.bottom = rcThis.top + height;
		rcThis.right = rcThis.left + width;

		m_dlgTrade.MoveWindow(rcThis);
	}
}


void CMainView::OnDestroy()
{
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
	m_dlgTrade.SetMode(iMode);
	m_dlgTrade.Show();
	m_dlgTrade.SetFocus();	
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
	CRect rcThis, rcParent;
	GetWindowRect(&rcParent);
	ClientToScreen(rcThis);

	m_dlgTrade.GetWindowRect(rcThis);

	int width = rcThis.Width();
	int height = rcThis.Height();

	rcThis.top = rcParent.bottom - height - 20;
	rcThis.left = rcParent.left + 20;
	rcThis.bottom = rcThis.top + height;
	rcThis.right = rcThis.left + width;

	m_dlgTrade.MoveWindow(rcThis);
}
