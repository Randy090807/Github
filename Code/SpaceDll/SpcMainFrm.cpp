// SpcMainFrm.cpp : implementation file
//

#include "stdafx.h"
#include "SpcMainFrm.h"
#include "MainView.h"

// CSpcMainFrm

IMPLEMENT_DYNAMIC(CSpcMainFrm, CMDIChildWndEx)

CSpcMainFrm::CSpcMainFrm()
{
	
}

CSpcMainFrm::~CSpcMainFrm()
{
}


BEGIN_MESSAGE_MAP(CSpcMainFrm, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CSpcMainFrm message handlers




int CSpcMainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);

	return 0;
}


void CSpcMainFrm::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CSpcMainFrm::OnDestroy()
{
	CMDIChildWndEx::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CSpcMainFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	CRect rc;

	CCreateContext context;
	context.m_pCurrentDoc = NULL;
	context.m_pCurrentFrame = NULL;
	context.m_pLastView = NULL;
	context.m_pNewDocTemplate = NULL;
	context.m_pNewViewClass = RUNTIME_CLASS(CMainView);

	CWnd* pView = CreateView(&context);
	pView->MoveWindow(&rc);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}
