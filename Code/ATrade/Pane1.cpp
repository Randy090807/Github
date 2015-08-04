// Pane1.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "Pane1.h"
#include "afxdialogex.h"
#include "../Public/EnumDefine.h"

// CPane1 dialog

IMPLEMENT_DYNAMIC(CPane1, CDialogEx)

CPane1::CPane1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPane1::IDD, pParent)
	, m_dbOffset(0.01)
{

}

CPane1::~CPane1()
{
}

void CPane1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_wndList);
	DDX_Control(pDX, IDC_COMBO1, m_cbDirect);
	DDX_Control(pDX, IDC_COMBO4, m_cbReSend);
	DDX_Control(pDX, IDC_COMBO2, m_cbPrice);
	DDX_Control(pDX, IDC_COMBO3, m_cbCount);
	DDX_Text(pDX, IDC_EDIT1, m_dbOffset);
	DDX_Control(pDX, IDC_HOTKEY1, m_HotKey);
}


BEGIN_MESSAGE_MAP(CPane1, CDialogEx)

	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, &CPane1::OnLvnItemchangedList)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_ADD, &CPane1::OnBnClickedBtnAdd)
	ON_BN_CLICKED(IDC_BTN_MODIFY, &CPane1::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CPane1::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CPane1 message handlers
void CPane1::OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if (pNMLV->uChanged == LVIF_STATE)
	{
		if (pNMLV->uNewState)
		{
			int nIndex = pNMLV->iItem;
			CLevel2Info::CHotKeySet* pHKS = (CLevel2Info::CHotKeySet*)(m_wndList.GetItemData(nIndex));
			//要进行的操作
			LoadItem(pHKS);
			GetDlgItem(IDC_BTN_DELETE)->EnableWindow(!pHKS->Default);
//			m_HotKey.EnableWindow(!pHKS->Default);
		}
	}

	*pResult = 0;
}


BOOL CPane1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_wndList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_wndList.InsertColumn(0L, _T("快捷键"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(1L, _T("方向"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(2L, _T("价位"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(3L, _T("价格偏移值"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(4L, _T("默认股数"), LVCFMT_CENTER, 100);
	m_wndList.InsertColumn(5L, _T("重发"), LVCFMT_CENTER, 100);

	m_cbDirect.ResetContent();
	for (int i = 0; i < sizeof(g_OrderTypeName) / sizeof(LPCTSTR); i++)
	{
		m_cbDirect.AddString(g_OrderTypeName[i]);
	}
	
	m_cbReSend.ResetContent();
	for (int i = 0; i < sizeof(g_ReSendName) / sizeof(LPCTSTR); i++)
	{
		m_cbReSend.AddString(g_ReSendName[i]);
	}

	m_cbPrice.ResetContent();
	for (int i = 0; i < sizeof(g_PriceName) / sizeof(LPCTSTR); i++)
	{
		m_cbPrice.AddString(g_PriceName[i]);
	}

	
	m_cbCount.ResetContent();
	m_cbCount.AddString(_T("Default"));

	for (int i = 0; i < CConfig::Inst()->Level2Info()->HKSize(); i++)
	{
		CLevel2Info::CHotKeySet* pHKS = CConfig::Inst()->Level2Info()->Item(i);
		AddItemToList(pHKS, i);
	}

	if ( m_wndList.GetItemCount() != 0)
	{
		m_wndList.SetItemState(0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
//		LoadItem((CLevel2Info::CHotKeySet*)(m_wndList.GetItemData(0)));
		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CPane1::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here

}

void CPane1::LoadItem(CLevel2Info::CHotKeySet* pHKI)
{
	ASSERT(pHKI);
	m_cbDirect.SetCurSel(pHKI->Direction);
	m_cbReSend.SetCurSel(pHKI->ReSend);
	m_cbPrice.SetCurSel(pHKI->Price);
	m_dbOffset = pHKI->Offset;
	m_cbCount.SetWindowText(pHKI->CountName());
	m_HotKey.SetHotKey(LOBYTE(pHKI->HotKey), HIBYTE(pHKI->HotKey));
}

void CPane1::SaveItem(CLevel2Info::CHotKeySet* pHKS)
{
	ASSERT(pHKS);
	pHKS->HotKey = m_HotKey.GetHotKey();
	pHKS->Direction = m_cbDirect.GetCurSel();
	pHKS->Price = m_cbPrice.GetCurSel();
	pHKS->Offset = m_dbOffset;
	pHKS->ReSend = m_cbReSend.GetCurSel();

	CString szText;
	m_cbCount.GetWindowText(szText);
	szText.Trim();

	pHKS->Count = (szText.CompareNoCase(_T("Default")) == 0) ? 0 : _ttoi(szText);
}

void CPane1::AddItemToList(CLevel2Info::CHotKeySet* pHKS, int i)
{
	m_wndList.InsertItem(i, _T(""));
	UpdateItemToList(pHKS, i);
	m_wndList.SetItemData(i, (DWORD_PTR)pHKS);
}


void CPane1::OnBnClickedBtnAdd()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	if ( m_HotKey.GetHotKey() == 0)
	{
		MessageBox(_T("热键不能为空"),_T("错误"),MB_OK|MB_ICONERROR);
		return;
	}

	for (int i = 0; i < m_wndList.GetItemCount(); i++)
	{
		CLevel2Info::CHotKeySet* pHKS = (CLevel2Info::CHotKeySet*)(m_wndList.GetItemData(i));
		if ( pHKS->HotKey == m_HotKey.GetHotKey())
		{
			MessageBox(_T("热键已经设置"), _T("错误"), MB_OK | MB_ICONERROR);
			return;
		}
	}

	CLevel2Info::CHotKeySet* pHKS = new CLevel2Info::CHotKeySet();
	pHKS->Default = FALSE;
	SaveItem(pHKS);
	CConfig::Inst()->Level2Info()->Add(pHKS);

	int idx = m_wndList.GetItemCount();
	AddItemToList(pHKS, idx);
	m_wndList.SetItemState(idx, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);

}


void CPane1::OnBnClickedBtnModify()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	int idx = m_wndList.GetNextItem(-1, LVIS_SELECTED);
	if (idx < 0)
		return;

	CLevel2Info::CHotKeySet* pHKS = (CLevel2Info::CHotKeySet*)(m_wndList.GetItemData(idx));

	if (pHKS->Default)	//
	{
		if ( pHKS->HotKey != m_HotKey.GetHotKey())
		{
			MessageBox(_T("默认快捷键[F1,F2,F3,F4]不可被修改"),_T("错误"),MB_OK|MB_ICONERROR);
			return;
		}
	}

	SaveItem(pHKS);
	UpdateItemToList(pHKS, idx);

	UpdateData(FALSE);
}


void CPane1::OnBnClickedBtnDelete()
{
	// TODO: Add your control notification handler code here
	int idx = m_wndList.GetNextItem(-1, LVIS_SELECTED);
	if (idx < 0)
		return;

	m_wndList.DeleteItem(idx);
	CConfig::Inst()->Level2Info()->Delete(idx);

	idx = min(idx, m_wndList.GetItemCount() - 1);
	m_wndList.SetItemState(idx, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
}

void CPane1::UpdateItemToList(CLevel2Info::CHotKeySet* pHKS, int i)
{
	CString szText;
	m_wndList.SetItemText(i, 0L, pHKS->HotKeyName());
	m_wndList.SetItemText(i, 1L, pHKS->DirectionName());
	m_wndList.SetItemText(i, 2L, pHKS->PriceName());
	szText.Format(_T("%.2f"), pHKS->Offset);
	m_wndList.SetItemText(i, 3L, szText);
	m_wndList.SetItemText(i, 4L, pHKS->CountName());
	m_wndList.SetItemText(i, 5L, pHKS->ReSendName());
}
BOOL CPane1::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}