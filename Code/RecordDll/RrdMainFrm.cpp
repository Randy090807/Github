// RrdMainFrm.cpp : implementation file
//

#include "stdafx.h"
#include "RrdMainFrm.h"
#include "MainView.h"

// CRrdMainFrm

//IMPLEMENT_DYNAMIC(CRrdMainFrm, CMDIChildWndEx)

CRrdMainFrm::CRrdMainFrm()
{

}

CRrdMainFrm::~CRrdMainFrm()
{
}


BEGIN_MESSAGE_MAP(CRrdMainFrm, CMDIChildWndEx)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CRrdMainFrm message handlers
int CRrdMainFrm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIChildWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CRrdMainFrm::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CRrdMainFrm::OnDestroy()
{
	CMDIChildWndEx::OnDestroy();

	// TODO: Add your message handler code here
}


BOOL CRrdMainFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
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
