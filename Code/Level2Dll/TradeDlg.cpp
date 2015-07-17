// TradeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TradeDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "../Public/Config.h"
// CTradeDlg dialog

IMPLEMENT_DYNAMIC(CTradeDlg, CDialogEx)

CTradeDlg::CTradeDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(IDD_TRADE/*CTradeDlg::IDD*/, pParent)
	, m_dbPrice(23.49)
	, m_nCount(1000)
	, m_szTip(_T(""))
{

}

CTradeDlg::~CTradeDlg()
{
}

void CTradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_dbPrice);
	DDX_Text(pDX, IDC_EDIT_COUNT, m_nCount);
	DDX_Text(pDX, IDC_STATIC_TIP, m_szTip);
	DDX_Control(pDX, IDC_EDIT_PRICE, m_editPrice);
	DDX_Control(pDX, IDC_EDIT_COUNT, m_editCount);
}


BEGIN_MESSAGE_MAP(CTradeDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_MOVING()
	ON_WM_SETFOCUS()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CTradeDlg message handlers
BOOL CTradeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CWnd* pWnd = GetParent();
	CRect rc;
	pWnd->GetWindowRect(&rc);

	CRect rcThis, rcParent;
	pWnd->GetWindowRect(&rcParent);
	pWnd->ClientToScreen(rcThis);

	GetWindowRect(rcThis);

	int width = rcThis.Width();
	int height = rcThis.Height();

	rcThis.top = rcParent.bottom - height - 20;
	rcThis.left = rcParent.left + 20;
	rcThis.bottom = rcThis.top + height;
	rcThis.right = rcThis.left + width;

	MoveWindow(rcThis);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CTradeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
	{
		pDC->SetBkColor(RGB(255, 0, 0));
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
static CString g_Tips[] = 
{
	_T("µ£±£Æ·ÂòÈë"), _T("ÈÚÈ¯Âô³ö"), _T("Ô¤Ô¼È¯Âô³ö"), _T("ÕÇÍ£ÈÚÈ¯Âô³ö")
};

void CTradeDlg::SetMode(int i)
{
	m_szTip = g_Tips[i];
//	UpdateData(FALSE);
}

BOOL CTradeDlg::Create(CWnd* pParentWnd /* = NULL */)
{
	return CDialogEx::Create(IDD_TRADE, pParentWnd);
}

void CTradeDlg::Show(BOOL bShow /*= TRUE*/ , CTradeInfo* pTradeInfo/* = NULL*/)
{
	m_editPrice.SetUpDownScale(CConfig::Inst()->Level2Info()->dbUDSacle);
	m_editPrice.SetLeftRightScale(CConfig::Inst()->Level2Info()->dbLRSacle);

	if ( bShow)
	{

		ShowWindow(SW_SHOW);
	}
	else
	{
		ShowWindow(SW_HIDE);
	}
	
}


void CTradeDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	ShowWindow(SW_HIDE);

	CDialogEx::OnOK();
}


void CTradeDlg::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);

	// TODO: Add your message handler code here
}


void CTradeDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	GetDlgItem(IDC_EDIT_PRICE)->SetFocus();
}


void CTradeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}

void CTradeDlg::SetInfo(CTradeInfo* pTradeInfo)
{
	m_pTradeInfo = pTradeInfo;
}
