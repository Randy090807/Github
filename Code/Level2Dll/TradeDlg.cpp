// TradeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TradeDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
#include "../Public/Config.h"
#include "../Public/EnumDefine.h"
#include "../Public/Utility.h"
#include "../Public/TradeInfo.h"

// CTradeDlg dialog
#define ID_HOTKEY_START	0x900
#define ID_HOTKEY_END	0x910

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
	ON_WM_HOTKEY()
	ON_WM_ACTIVATE()
	ON_WM_DESTROY()
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

	
	FillData();

	RegisterHotKey();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


HBRUSH CTradeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIP)
	{
		pDC->SetBkColor(RGB(255,0,0));
	}
	// TODO:  Return a different brush if the default is not desired
	return hbr;
}


BOOL CTradeDlg::Create(CWnd* pParentWnd /* = NULL */)
{
	return CDialogEx::Create(IDD_TRADE, pParentWnd);
}


void CTradeDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData();
	CTradeInfoItem* pTradeItem = CTradeInfo::Inst()->GetStock(m_pTradeInfo->StockID);
	ASSERT(pTradeItem);
	if (m_nCount > pTradeItem->BP)
	{
		UINT iRet = MessageBox(_T("股票数量超过可用预约券数，是否按照可用预约券数下单\r\n是：按照可用预约券下单\r\n否：取消此次下单"), _T("提示"), MB_YESNO | MB_ICONQUESTION);
		if ( iRet == IDYES)
		{
			m_nCount = pTradeItem->BP;
			CDialogEx::OnOK();
		}
		else 
		{
		}
	}

	
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
	CRect rcCient;
	GetClientRect(&rcCient);
	dc.FillSolidRect(rcCient, RGB(214, 219, 233));
}

void CTradeDlg::SetInfo(CQTTradeInfo* pTradeInfo)
{
	m_pTradeInfo = pTradeInfo;
}



void CTradeDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialogEx::OnCancel();
}


void CTradeDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	if (nHotKeyId >= ID_HOTKEY_START && nHotKeyId <= ID_HOTKEY_END)
	{
		CLevel2Info::CHotKeySet* pHKS = CConfig::Inst()->Level2Info()->Item(nHotKeyId-ID_HOTKEY_START);

	
		m_pTradeInfo->OrderType = pHKS->Direction;
		m_pTradeInfo->PriceType = pHKS->Price;
		m_pTradeInfo->Volume = pHKS->Count;
		m_pTradeInfo->PriceOffset = pHKS->Offset;

		FillData();
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


void CTradeDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);

	// TODO: Add your message handler code here
	if (nState == 0)
	{
		UnRegisterHotKey();
	}
	else
	{
		RegisterHotKey();
	}
}


void CTradeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	UnRegisterHotKey();
}

void CTradeDlg::RegisterHotKey()
{
	for (int i = 0; i < CConfig::Inst()->Level2Info()->HKSize(); i++)
	{
		DWORD dwVK = 0, dwModifier = 0;
		ParseHotKey(CConfig::Inst()->Level2Info()->Item(i)->HotKey, dwVK, dwModifier);
		::RegisterHotKey(m_hWnd, ID_HOTKEY_START + i, dwModifier, dwVK);
	}
}

void CTradeDlg::UnRegisterHotKey()
{
	for (int i = 0; i < CConfig::Inst()->Level2Info()->HKSize(); i++)
	{
		UnregisterHotKey(m_hWnd, ID_HOTKEY_START + i);
	}
}

void CTradeDlg::FillData()
{
	UpdateData();

	CTradeInfoItem* pTradeItem = CTradeInfo::Inst()->GetStock(m_pTradeInfo->StockID);
	ASSERT(pTradeItem);

	m_szTip = g_OrderTypeName[m_pTradeInfo->OrderType];
	switch (m_pTradeInfo->PriceType)
	{
	case 0:m_dbPrice = PriceTrans(pTradeItem->nBidPrice)/*m_pTradeInfo->BidPrice*/; break;
	case 1:m_dbPrice = PriceTrans(pTradeItem->nAskPrice); break;
	case 2:m_dbPrice = PriceTrans(pTradeItem->nHighLimited); break;
	case 3:m_dbPrice = PriceTrans(pTradeItem->nLowLimited); break;
	case 4:m_dbPrice = PriceTrans(pTradeItem->nOpen); break;
	}
	m_dbPrice += m_pTradeInfo->PriceOffset;

	if ( m_pTradeInfo->bMaxSell)
	{
		m_nCount = pTradeItem->BP;
	}
	else 
	{
		m_nCount = m_pTradeInfo->Volume == 0 ? m_pTradeInfo->DefaultVolume : m_pTradeInfo->Volume;
	}

	UpdateData(FALSE);
}
