#pragma once


// CLev2MainFrm

class AFX_EXT_CLASS CLev2MainFrm : public CMDIChildWndEx
{
	DECLARE_DYNAMIC(CLev2MainFrm)

public:
	CLev2MainFrm();
	virtual ~CLev2MainFrm();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


