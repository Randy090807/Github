// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include "ConfigDlg.h"
#include "../Level2Dll/Level2Dlg.h"
#include "../RecordDll/RecordDlg.h"
#include "../SpaceDll/SpaceDlg.h"
#include "../Public/Utility.h"
#include "../Public/Application.h"
#include "../Public/MsgDefine.h"
#include <algorithm>
#include "../Public/Config.h"
#include "SvrSocket.h"
#include "../Public/TradeInfo.h"

CSvrSocket		g_SockSvr;
CPriceSocket	g_SockPrice;
BOOL g_StatusSrv = FALSE;
BOOL g_StatusPrice = FALSE;

// CMainDlg dialog

#define ID_HOTKEY_PAGEUP	0x100
#define ID_HOTKEY_PAGEDOWN	0x101

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_pImageLogo(CApplication::ImageDir() + _T("\\logo.jpg"))
	, m_pImage(CApplication::ImageDir() + _T("\\mainbg.png"))
	, m_nLev2Idx(0)
	, m_pWndRecord(NULL)
	, m_pWndConfig(0)
{
//	PngFromIDResource(IDB_BACKGROUND, m_pImage);
	
}

CMainDlg::~CMainDlg()
{
	for (auto iter = m_Lev2Wnds.begin(); iter != m_Lev2Wnds.end(); ++iter)
	{
		delete (*iter);
	}
	m_Lev2Wnds.clear();

	delete m_pWndRecord;
	delete m_pWndSpace;
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BTN_LEVEL2, m_btnLevel2);
	DDX_Control(pDX, IDC_BTN_CONFIG, m_btnConfig);
	DDX_Control(pDX, IDC_BTN_SPACE, m_btnSpace);
	DDX_Control(pDX, IDC_BTN_RECORD, m_btnRecord);
	DDX_Control(pDX, IDC_BTN_EXIT, m_btnExit);
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_LEVEL2, &CMainDlg::OnBnClickedBtnLevel2)
	ON_BN_CLICKED(IDC_BTN_RECORD, &CMainDlg::OnBnClickedBtnRecord)
	ON_BN_CLICKED(IDC_BTN_SPACE, &CMainDlg::OnBnClickedBtnSpace)
	ON_BN_CLICKED(IDC_BTN_CONFIG, &CMainDlg::OnBnClickedBtnConfig)
	ON_BN_CLICKED(IDC_BTN_EXIT, &CMainDlg::OnBnClickedBtnExit)
	ON_MESSAGE(UM_CLOSE_LEVEL2,&CMainDlg::OnMsgLevel2WndClose)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY, &CMainDlg::OnMsgSrvDataNofity)
	ON_MESSAGE(UM_SRV_DATA_REPORT, &CMainDlg::OnMsgSrvDataReport)
	ON_MESSAGE(UM_SRV_DATA_NOTIFY2, &CMainDlg::OnMsgSrvDataNofity2)
	ON_MESSAGE(UM_SRV_DATA_REPORT2, &CMainDlg::OnMsgSrvDataReport2)
	ON_WM_LBUTTONDOWN()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CMainDlg message handlers


BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CRect rtClient;
	GetWindowRect(rtClient);
	int width = GetSystemMetrics(SM_CXSCREEN);
	int thisWidth = rtClient.Width();
	rtClient.left = (width - rtClient.Width() )/ 2;
	rtClient.right = rtClient.left + thisWidth;
	m_hWndTop = ::GetForegroundWindow();
	::SetWindowPos(/*m_hWndTop*/m_hWnd, HWND_TOP/*HWND_TOPMOST*/, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);

	g_SockSvr.SetMsgReciver(this);
	g_SockPrice.SetMsgReciver(this);

	
	::PostMessage(m_pWndRecord->GetSafeHwnd(), UM_NOTIFY_INIT_COMPLETE, 0, 0);
	::PostMessage(m_pWndSpace->GetSafeHwnd(), UM_NOTIFY_INIT_COMPLETE, 0, 0);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CMainDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMainDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
	dc.SetBkMode(TRANSPARENT);
	
	
	Graphics graphics(dc.GetSafeHdc());
	CRect rcClient;
	GetClientRect(&rcClient);

	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	Rect rcDest;
	rcDest.X = rcClient.left;
	rcDest.Width = rcClient.Width();
	rcDest.Y = rcClient.top;
	rcDest.Height = rcClient.Height();
	graphics.DrawImage(&m_pImage, rcDest, 0, 0, m_pImage.GetWidth(), m_pImage.GetHeight(), UnitPixel, &ImgAtt);

	rcDest.X = 2;
	rcDest.Y = 2;
	rcDest.Width = rcDest.Height = rcClient.Height() - 4;
	graphics.DrawImage(&m_pImageLogo, rcDest, 0, 0, m_pImageLogo.GetWidth(), m_pImageLogo.GetHeight(), UnitPixel, &ImgAtt);

	CRect rc;
	rc.left = rcDest.GetRight() + 10;
	rc.right = rc.left + 10;
	rc.top = 10;
	rc.bottom = 20;
	
	CPen penOk, penErr;
	penOk.CreatePen(PS_SOLID, 1, RGB(0,177,0));
	penErr.CreatePen(PS_SOLID, 1, RGB(127, 127, 127));

	CBrush brushOk, brushErr;
	brushOk.CreateSolidBrush(RGB(0, 177, 0));
	brushErr.CreateSolidBrush(RGB(127, 127, 127));

	if ( g_StatusSrv)
	{
		dc.SelectObject(&penOk);
		dc.SelectObject(&brushOk);
	}
	else
	{
		dc.SelectObject(&penErr);
		dc.SelectObject(&brushErr);
	}
	dc.Ellipse( rc);

	rc.top = 30;
	rc.bottom = 40;
	if (g_StatusPrice)
	{
		dc.SelectObject(&penOk);
		dc.SelectObject(&brushOk);
	}
	else
	{
		dc.SelectObject(&penErr);
		dc.SelectObject(&brushErr);
	}
	dc.Ellipse(rc);
}


int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	RegisterHotKey(m_hWnd, ID_HOTKEY_PAGEUP, 0, VK_PRIOR);
	RegisterHotKey(m_hWnd, ID_HOTKEY_PAGEDOWN, 0, VK_NEXT);

	CTradeInfo::Inst()->SetMsgReciver(this);

	m_pWndRecord = new CRecordDlg();
	m_pWndRecord->Create(this);
	m_pWndRecord->SetOwner(this);
	m_pWndRecord->ShowWindow(SW_HIDE);

	m_pWndSpace = new CSpaceDlg();
	m_pWndSpace->Create(this);
	m_pWndSpace->SetOwner(this);
	m_pWndSpace->ShowWindow(SW_HIDE);
	
	return 0;
}


void CMainDlg::OnDestroy()
{

	CDialogEx::OnDestroy();
	
	// TODO: Add your message handler code here

	UnregisterHotKey(m_hWnd, ID_HOTKEY_PAGEUP);
	UnregisterHotKey(m_hWnd, ID_HOTKEY_PAGEDOWN);

	CConfig::Inst()->Save();
}


void CMainDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CMainDlg::OnBnClickedBtnLevel2()
{
	// TODO: Add your control notification handler code here
	CLevel2Dlg* dlg = new CLevel2Dlg();
	dlg->Create(this);
	dlg->SetOwner(this);
	dlg->ShowWindow(SW_SHOW);
	
	::PostMessage(dlg->GetSafeHwnd(), UM_NOTIFY_INIT_COMPLETE, 0, 0);

	m_Lev2Wnds.push_back(dlg);
}


void CMainDlg::OnBnClickedBtnRecord()
{
	// TODO: Add your control notification handler code here
	m_pWndRecord->ShowWindow(SW_SHOW);
	m_pWndRecord->SetActiveWindow();
	m_pWndRecord->SetFocus();
	
}


void CMainDlg::OnBnClickedBtnSpace()
{
	// TODO: Add your control notification handler code here
	m_pWndSpace->ShowWindow(SW_SHOW);
	m_pWndSpace->SetActiveWindow();
	m_pWndSpace->SetFocus();
}


void CMainDlg::OnBnClickedBtnConfig()
{
	// TODO: Add your control notification handler code here
	CConfigDlg dlg;
	m_pWndConfig = &dlg;
	dlg.DoModal();

	::PostMessage(m_pWndSpace->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, 0, 0);
	::PostMessage(m_pWndRecord->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, 0, 0);
	for (auto iter = m_Lev2Wnds.begin(); iter != m_Lev2Wnds.end(); ++iter)
	{
		::PostMessage((*iter)->GetSafeHwnd(), UM_NOTIFY_CONFIG_REFRESH, 0, 0);
	}
	m_pWndConfig = NULL;
}


void CMainDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	PostMessage(WM_CLOSE, 0, 0);
}


void CMainDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	SendMessage(WM_SYSCOMMAND, 0xF012, 0);
	CDialogEx::OnLButtonDown(nFlags, point);
}

LRESULT CMainDlg::OnMsgLevel2WndClose(WPARAM wparam, LPARAM lparam)
{
	CWnd* pWnd = (CWnd*)wparam;
	m_Lev2Wnds.erase(std::find(m_Lev2Wnds.begin(), m_Lev2Wnds.end(), pWnd));
	delete pWnd;
	return 0;
}

void CMainDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: Add your message handler code here and/or call default
	if ( m_Lev2Wnds.size() != 0)
	{
		if (nHotKeyId == ID_HOTKEY_PAGEDOWN)	// 下一个
		{
			m_nLev2Idx++;
			if ( m_nLev2Idx >= (int)m_Lev2Wnds.size())
			{
				m_nLev2Idx = 0;
			}
			::SetActiveWindow(m_Lev2Wnds[m_nLev2Idx]->GetSafeHwnd());
		}
		else if (nHotKeyId == ID_HOTKEY_PAGEUP)
		{
			m_nLev2Idx--;
			if (m_nLev2Idx <0)
			{
				m_nLev2Idx = m_Lev2Wnds.size()-1;
			}
			::SetActiveWindow(m_Lev2Wnds[m_nLev2Idx]->GetSafeHwnd());
		}
	}

	
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

LRESULT CMainDlg::OnMsgSrvDataNofity(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pMsg = (CBaseMsg*)wparam;
	
	CWnd* pWnd = FindReciverWnd(pMsg);
	if ( pWnd)
	{
		::PostMessage(pWnd->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, wparam, lparam);
	}
	else
	{
		delete pMsg;
	}

	return 0;
}

LRESULT CMainDlg::OnMsgSrvDataReport(WPARAM wparam, LPARAM lparam)
{
	CBaseMsg* pMsg = (CBaseMsg*)wparam;
	if (pMsg->Header.type == ID_CUSTOM_ADD_ORDER)
	{
		::PostMessage(m_pWndRecord->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, (WPARAM)pMsg, lparam);
	}
	else
	{
		g_SockSvr.Send(pMsg);
		delete pMsg;
	}
	
	return 0;
}

CWnd* CMainDlg::FindReciverWnd(CBaseMsg* pMsg)
{
	if (pMsg->Header.userdata == (UINT)m_pWndConfig || pMsg->Header.type == ID_CHANGE_PASSWORD_RESULT)
	{
		return m_pWndConfig;
	}
	if (pMsg->Header.userdata == (UINT)m_pWndSpace)
	{
		return m_pWndSpace;
	}
	if (pMsg->Header.userdata == (UINT)m_pWndRecord)
	{
		return m_pWndRecord;
	}

	for (auto iter = m_Lev2Wnds.begin(); iter != m_Lev2Wnds.end(); ++iter)
	{
		if ( ((DWORD)(*iter)) == pMsg->Header.userdata)
		{
			return *iter;
		}
	}

	// 推送消息
	if (pMsg->Header.type == ID_ORDER_INQUIRY_RESULT)	//订单查询返回 或 推送
	{
		return m_pWndRecord;
	}

	ASSERT(0);
	return NULL;
}

LRESULT CMainDlg::OnMsgSrvDataNofity2(WPARAM wparam, LPARAM lparam)
{
	char* pMsg = (char*)wparam;
	int l = lparam;

	MsgHeader* msgHeader = (MsgHeader*)pMsg;
	switch (msgHeader->type)
	{
	case ID_PRICE_PUSH:		// 行情推送，广播到所有Level2窗口
	case ID_TRANSACTION_PUSH:
		{
			USES_CONVERSION;
			// 更新股票全局信息
			if (msgHeader->type == ID_PRICE_PUSH)
			{
				MarketData* marketdata = (MarketData*)(((char*)wparam) + sizeof(MsgHeader));
				CTradeInfoItem* pStockItem = CTradeInfo::Inst()->GetStock(A2T(marketdata->szCode));
				ASSERT(pStockItem);
				pStockItem->nPreClose = marketdata->nPreClose;
				pStockItem->nOpen = marketdata->nOpen;
				pStockItem->nHigh = marketdata->nHigh;
				pStockItem->nLow = marketdata->nLow;
				pStockItem->nMatch = marketdata->nMatch;
				pStockItem->nAskPrice = marketdata->nAskPrice[0];
				pStockItem->nBidPrice = marketdata->nBidPrice[0];
				pStockItem->nYieldToMaturity = marketdata->nYieldToMaturity;
				pStockItem->nHighLimited = marketdata->nHighLimited;
				pStockItem->nLowLimited = marketdata->nLowLimited;
			}
		}
		for (auto iter = m_Lev2Wnds.begin(); iter != m_Lev2Wnds.end(); ++iter)
		{
			char* msg = new char[l];
			memcpy(msg, pMsg, l);
			::PostMessage((*iter)->GetSafeHwnd(), UM_SRV_DATA_NOTIFY2, (WPARAM)msg, lparam);
		}

		if (msgHeader->type != ID_TRANSACTION_PUSH)
		{
			::PostMessage(m_pWndSpace->GetSafeHwnd(), UM_SRV_DATA_NOTIFY2, wparam, lparam);
		}
		else
		{
			delete pMsg;
		}
		break;
	default:
		delete pMsg;
		ASSERT(0);
	}

	return 0;
}

LRESULT CMainDlg::OnMsgSrvDataReport2(WPARAM wparam, LPARAM lparam)
{
	char* pMsg = (char*)wparam;
	int l = lparam;
	g_SockPrice.Send(pMsg, l);
	delete pMsg;
	
	return 0;
}

