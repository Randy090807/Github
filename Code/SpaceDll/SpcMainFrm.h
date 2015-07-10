#pragma once


// CSpcMainFrm

class AFX_EXT_CLASS CSpcMainFrm : public CMDIChildWndEx
{
	DECLARE_DYNAMIC(CSpcMainFrm)

public:
	CSpcMainFrm();
	virtual ~CSpcMainFrm();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


