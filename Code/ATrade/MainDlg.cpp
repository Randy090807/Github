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
// CMainDlg dialog

#define ID_HOTKEY_PAGEUP	0x100
#define ID_HOTKEY_PAGEDOWN	0x101

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainDlg::IDD, pParent)
	, m_pImageLogo(CApplication::ImageDir() + _T("\\logo.jpg"))
	, m_nLev2Idx(0)
{
	PngFromIDResource(IDB_BACKGROUND, m_pImage);
	
}

CMainDlg::~CMainDlg()
{
	for (auto iter = m_Lev2Wnds.begin(); iter != m_Lev2Wnds.end(); ++iter)
	{
		delete (CWnd*)(*iter);
	}
	m_Lev2Wnds.clear();
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
	rtClient.left += 50;
	rtClient.right += 50;
	rtClient.top += 50;
	rtClient.bottom += 50;
	m_hWndTop = ::GetForegroundWindow();
	::SetWindowPos(/*m_hWndTop*/m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);

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
	
	if (m_pImage)
	{
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
		graphics.DrawImage(m_pImage, rcDest, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), UnitPixel, &ImgAtt);

		rcDest.X = 2;
		rcDest.Y = 2;
		rcDest.Width = rcDest.Height = rcClient.Height()-4;
		graphics.DrawImage(&m_pImageLogo, rcDest, 0, 0, m_pImageLogo.GetWidth(), m_pImageLogo.GetHeight(), UnitPixel, &ImgAtt);
	}
	
	
}


int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	RegisterHotKey(m_hWnd, ID_HOTKEY_PAGEUP, 0, VK_PRIOR);
	RegisterHotKey(m_hWnd, ID_HOTKEY_PAGEDOWN, 0, VK_NEXT);
	return 0;
}


void CMainDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	UnregisterHotKey(m_hWnd, ID_HOTKEY_PAGEUP);
	UnregisterHotKey(m_hWnd, ID_HOTKEY_PAGEDOWN);
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

	m_Lev2Wnds.push_back(dlg);
}


void CMainDlg::OnBnClickedBtnRecord()
{
	// TODO: Add your control notification handler code here
	CRecordDlg* dlg = new CRecordDlg();
	dlg->Create(this);
	dlg->SetOwner(this);
	dlg->ShowWindow(SW_SHOW);
}


void CMainDlg::OnBnClickedBtnSpace()
{
	// TODO: Add your control notification handler code here
	CSpaceDlg* dlg = new CSpaceDlg();
	dlg->Create(this);
	dlg->ShowWindow(SW_SHOW);
}


void CMainDlg::OnBnClickedBtnConfig()
{
	// TODO: Add your control notification handler code here
	CConfigDlg dlg;
	dlg.DoModal();
}


void CMainDlg::OnBnClickedBtnExit()
{
	// TODO: Add your control notification handler code here
	exit(0);
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
		if (nHotKeyId == ID_HOTKEY_PAGEDOWN)	// ÏÂÒ»¸ö
		{
			m_nLev2Idx++;
			if ( m_nLev2Idx >= m_Lev2Wnds.size())
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
