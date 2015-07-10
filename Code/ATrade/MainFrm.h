
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
class CRrdMainFrm;
class CSpcMainFrm;
class  CMainFrame : public CMDIFrameWndEx
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// ����
public:

	CRrdMainFrm* m_pRecordFrm;
	CSpcMainFrm* m_pSpaceFrm;
// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCMenuBar       m_wndMenuBar;
//	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
//	CMFCToolBarImages m_UserImages;

	void CreateMDIChildFrm(CMDIChildWndEx* pWnd);
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnWindowManager();
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()
	afx_msg void OnMenuLevel2();
	afx_msg void OnMenuRecord();
	afx_msg void OnMenuSpace();
	afx_msg void OnMenuConfig();
	afx_msg void OnMenuExit();
};


