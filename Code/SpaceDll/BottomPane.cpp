// BottomPane.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "BottomPane.h"


// CBottomPane

IMPLEMENT_DYNCREATE(CBottomPane, CDialogEx)

CBottomPane::CBottomPane()
: CDialogEx(IDD_BOTTOMPANE/*CBottomPane::IDD*/)
{

}

CBottomPane::~CBottomPane()
{
}

void CBottomPane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBottomPane, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CBottomPane diagnostics

#ifdef _DEBUG
void CBottomPane::AssertValid() const
{
	CDialogEx::AssertValid();
}

#ifndef _WIN32_WCE
void CBottomPane::Dump(CDumpContext& dc) const
{
	CDialogEx::Dump(dc);
}
#endif
#endif //_DEBUG


// CBottomPane message handlers

int CBottomPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CBottomPane::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CWnd* pWnd = GetDlgItem(IDC_BTN_ALL);
	CRect rc;
	int width;
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 300;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}
	pWnd = GetDlgItem(IDC_BTN_MORE);
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 200;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}
	pWnd = GetDlgItem(IDC_BTN_EMPTY);
	if (pWnd)
	{
		pWnd->GetWindowRect(&rc);
		ScreenToClient(&rc);
		width = rc.Width();
		rc.left = cx - 100;
		rc.right = rc.left + width;
		pWnd->MoveWindow(rc);
	}
}


void CBottomPane::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


HBRUSH CBottomPane::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (pWnd->GetDlgCtrlID())
	{
		case IDC_STATIC_JingKuiYing:
		case IDC_STATIC_FuYingLv:
			pDC->SetTextColor(RGB(0, 170, 0));
			break;
		case IDC_STATIC_KuiYing:
			pDC->SetTextColor(RGB(255,0,0));
			break;
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


void CBottomPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	CRect rc;
	GetClientRect(&rc);
	rc.bottom = rc.top + 40;

	dc.FillSolidRect(rc, RGB(255, 255, 255));
}
