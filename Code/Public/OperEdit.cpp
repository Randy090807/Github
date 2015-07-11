// OperEdit.cpp : implementation file
//

#include "stdafx.h"
#include "OperEdit.h"


// COperEdit

IMPLEMENT_DYNAMIC(COperEdit, CEdit)

COperEdit::COperEdit()
:m_nUDScale(0.01)
, m_nLRScale(0.05)
{

}

COperEdit::~COperEdit()
{
}


BEGIN_MESSAGE_MAP(COperEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// COperEdit message handlers




void COperEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	if (nChar == VK_DOWN || nChar == VK_UP || nChar == VK_RIGHT || nChar == VK_LEFT)
	{
		CString szText;
		GetWindowText(szText);
		double value = _ttof(szText);

		switch (nChar)
		{
		case VK_RIGHT:
			value += m_nLRScale;
			break;
		case VK_LEFT:
			value -= m_nLRScale;
			break;
		case VK_UP:
			value -= m_nUDScale;
			break;
		case VK_DOWN:
			value += m_nUDScale;
			break;
		}
		szText.Format(_T("%.2f"), value);
		SetWindowText(szText);
	}


	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
