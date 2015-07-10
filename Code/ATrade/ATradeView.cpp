
// ATradeView.cpp : CATradeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CATradeView 构造/析构

CATradeView::CATradeView()
{
	// TODO:  在此处添加构造代码

}

CATradeView::~CATradeView()
{
}

BOOL CATradeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CATradeView 绘制

void CATradeView::OnDraw(CDC* /*pDC*/)
{
	CATradeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
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


// CATradeView 诊断

#ifdef _DEBUG
void CATradeView::AssertValid() const
{
	CView::AssertValid();
}

void CATradeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CATradeDoc* CATradeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CATradeDoc)));
	return (CATradeDoc*)m_pDocument;
}
#endif //_DEBUG


// CATradeView 消息处理程序
