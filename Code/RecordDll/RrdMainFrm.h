#pragma once


// CRrdMainFrm

class AFX_EXT_CLASS CRrdMainFrm : public CMDIChildWndEx
{
//	DECLARE_DYNAMIC(CRrdMainFrm)

public:
	CRrdMainFrm();
	virtual ~CRrdMainFrm();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


