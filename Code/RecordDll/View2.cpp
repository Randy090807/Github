// View2.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "View2.h"
#include "../Public/ReportCtrlLayout.h"
#include "../Public/Application.h"
#include "../Public/Config.h"
#include "../Public/MsgDefine.h"
#include "../Public/MsgDefine.h"

#define ID_REPORT_CONTROL	0x104
// CView2

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
	m_wndReport.CreateColumns();

	CReportCtrlLayout::Layout(CApplication::DataDir() + _T("\\Layout2.xml"), &m_wndReport);

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

	menu.AppendMenu(MF_STRING, 0x14, _T("±£´æ¶©µ¥"));

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

void CView2::Update(COrderInquiryResultMsg* pMsg)
{
	for (vector<COrderInquiryResultMsg::COrders*>::iterator iter = pMsg->Orders.begin();
		iter != pMsg->Orders.end(); ++iter)
	{
		m_wndReport.AddRecord2(*iter);
	}

	m_wndReport.Populate();
}
