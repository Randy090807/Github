// Lev2MainFrm.cpp : implementation file
//

#include "stdafx.h"
#include "Lev2MainFrm.h"
#include "MainView.h"

// CLev2MainFrm

IMPLEMENT_DYNAMIC(CLev2MainFrm, CMDIChildWndEx)

CLev2MainFrm::CLev2MainFrm()
{
	
}

CLev2MainFrm::~CLev2MainFrm()
{
}


BEGIN_MESSAGE_MAP(CLev2MainFrm, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CLev2MainFrm message handlers




int CLev2MainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CLev2MainFrm::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


BOOL CLev2MainFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
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
