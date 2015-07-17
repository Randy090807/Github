#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "../Public/Config.h"

// CPane1 dialog

class CPane1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane1)

public:
	CPane1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane1();

// Dialog Data
	enum { IDD = IDD_PANE1 };

protected:
	CListCtrl m_wndList;
	CComboBox m_cbDirect;
	CComboBox m_cbReSend;
	CComboBox m_cbPrice;
	CComboBox m_cbCount;
	double	  m_dbOffset;
	CHotKeyCtrl m_HotKey;

	void LoadItem(CLevel2Info::CHotKeySet* pHKS);
	void SaveItem(CLevel2Info::CHotKeySet* pHS);
	void AddItemToList(CLevel2Info::CHotKeySet* pHKS, int idx);
	void UpdateItemToList(CLevel2Info::CHotKeySet* pHKS, int idx);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnLvnItemchangedList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDelete();
};
