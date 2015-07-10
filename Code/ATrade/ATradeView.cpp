
// ATradeView.cpp : CATradeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "ATrade.h"
#endif

#include "ATradeDoc.h"
#include "ATradeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CATradeView

IMPLEMENT_DYNCREATE(CATradeView, CView)

BEGIN_MESSAGE_MAP(CATradeView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CATradeView ����/����

CATradeView::CATradeView()
{
	// TODO:  �ڴ˴���ӹ������

}

CATradeView::~CATradeView()
{
}

BOOL CATradeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CATradeView ����

void CATradeView::OnDraw(CDC* /*pDC*/)
{
	CATradeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CATradeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CATradeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CATradeView ���

#ifdef _DEBUG
void CATradeView::AssertValid() const
{
	CView::AssertValid();
}

void CATradeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CATradeDoc* CATradeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CATradeDoc)));
	return (CATradeDoc*)m_pDocument;
}
#endif //_DEBUG


// CATradeView ��Ϣ�������
