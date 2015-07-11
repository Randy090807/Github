// RTButton.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "RTButton.h"
#include "../Public/Utility.h"

// CRTButton

IMPLEMENT_DYNAMIC(CRTButton, CButton)

CRTButton::CRTButton()
{
	PngFromIDResource(IDB_BOTTON, m_pImage);
}

CRTButton::~CRTButton()
{
}


BEGIN_MESSAGE_MAP(CRTButton, CButton)
END_MESSAGE_MAP()



// CRTButton message handlers




void CRTButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	dc.SetBkMode(TRANSPARENT);

	if (m_pImage)
	{
		Graphics graphics(dc.GetSafeHdc());
		CRect rcClient; 
		GetClientRect(&rcClient);

		ImageAttributes ImgAtt;
		ImgAtt.SetWrapMode(WrapModeTileFlipXY);

		Rect rcDest(lpDrawItemStruct->rcItem.left, lpDrawItemStruct->rcItem.top, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		graphics.DrawImage(m_pImage, rcDest, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), UnitPixel, &ImgAtt);
	}

	dc.SelectObject(GetParent()->GetFont());
	dc.SetTextColor(RGB(255, 255, 255));
	CString szText;
	GetWindowText(szText);
	dc.DrawText(szText, &lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	
	dc.Detach();
}
