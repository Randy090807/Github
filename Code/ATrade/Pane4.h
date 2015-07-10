#pragma once
#include "afxwin.h"

#include "../Public/ShortcutEdit.h"
// CPane4 dialog

class CPane4 : public CDialogEx
{
	DECLARE_DYNAMIC(CPane4)

public:
	CPane4(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPane4();

// Dialog Data
	enum { IDD = IDD_PANE4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CShortcutEdit m_EditCeDan;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CShortcutEdit m_EditPiLiangCeDan;
	CShortcutEdit m_EditGaiDan;
	virtual BOOL OnInitDialog();
};
