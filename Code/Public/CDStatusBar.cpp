#include "stdafx.h"
#include "CDStatusBar.h"

CCDStatusBar::CCDStatusBar(CWnd* pParent)
	: m_pParentWnd(pParent)
{
	ASSERT(pParent);
}


CCDStatusBar::~CCDStatusBar()
{
}

void CCDStatusBar::UpdateStatus(LPCTSTR lpText, CCDStatusBar::enStatus eStatus)
{
	m_szText = lpText;
	m_enStatus = eStatus;

	CRect rcClient;
	m_pParentWnd->GetClientRect(&rcClient);
	rcClient.top = rcClient.bottom - CDCSTAUTSBAR_HEIGHT;
	m_pParentWnd->InvalidateRect(rcClient);
}

void CCDStatusBar::DrawItem(CDC* pDC)
{
	CRect rcClient;
	m_pParentWnd->GetClientRect(&rcClient);
	rcClient.top = rcClient.bottom - CDCSTAUTSBAR_HEIGHT;

	pDC->FillSolidRect(rcClient, RGB(240, 240, 240));

	CFont font;
	font.CreatePointFont(90, _T("ºÚÌå"));
	pDC->SelectObject(&font);
	pDC->SetTextColor(m_enStatus == STATUS_NORMAL ? RGB(0, 0, 0)
		:m_enStatus==STATUS_ERROR?RGB(255,0,0):RGB(0,127,0));
	pDC->DrawText(m_szText, rcClient, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
}
