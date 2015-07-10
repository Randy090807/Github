
// ATradeView.h : CATradeView ��Ľӿ�
//

#pragma once


class CATradeView : public CView
{
protected: // �������л�����
	CATradeView();
	DECLARE_DYNCREATE(CATradeView)

// ����
public:
	CATradeDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CATradeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ATradeView.cpp �еĵ��԰汾
inline CATradeDoc* CATradeView::GetDocument() const
   { return reinterpret_cast<CATradeDoc*>(m_pDocument); }
#endif

