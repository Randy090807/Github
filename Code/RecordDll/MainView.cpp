// MainView.cpp : implementation file
//

#include "stdafx.h"
#include "MainView.h"
#include "View1.h"
#include "View2.h"

// CMainView

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


int CMainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
	{
		return FALSE;
	}

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CView1), CSize(200, 200), NULL);
	m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CView2), CSize(200, 200), NULL);
	return 0;
}


void CMainView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_wndSplitter.GetSafeHwnd())
	{
		m_wndSplitter.MoveWindow(0, 0, cx, cy);
	}
}


void CMainView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
}


void CMainView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
}
