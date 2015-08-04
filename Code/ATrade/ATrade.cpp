
// ATrade.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ATrade.h"
#include "LoginDlg.h"
#include "MainDlg.h"
#include "../Public/Config.h"
#include "SvrSocket.h"
#include "PriceSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CSvrSocket	g_SockSvr;
extern CPriceSocket	g_SockPrice;
// CATradeApp

BEGIN_MESSAGE_MAP(CATradeApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CATradeApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CATradeApp ����

CATradeApp::CATradeApp()
{
	m_bHiColorIcons = TRUE;
	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ATrade.AppID.1.0"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CATradeApp ����

CATradeApp theApp;


// CATradeApp ��ʼ��

BOOL CATradeApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxSocketInit();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("ATRADE_V1.0"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// ��ʼ��������Ϣ
	CConfig::Inst();


	CLoginDlg dlg;
	if ( dlg.DoModal() != IDOK)
	{
		return 0;
	}

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
// 	CMultiDocTemplate* pDocTemplate;
// 	pDocTemplate = new CMultiDocTemplate(IDR_ATradeTYPE,
// 		RUNTIME_CLASS(CATradeDoc),
// 		RUNTIME_CLASS(CChildFrame), // �Զ��� MDI �ӿ��
// 		RUNTIME_CLASS(CATradeView));
// 	if (!pDocTemplate)
// 		return FALSE;
// 	AddDocTemplate(pDocTemplate);

	

	CMainDlg mainDlg;
	mainDlg.DoModal();

	// ������ MDI ��ܴ���
// 	CMainFrame* pMainFrame = new CMainFrame;
// 	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
// 	{
// 		delete pMainFrame;
// 		return FALSE;
// 	}
// 	m_pMainWnd = pMainFrame;


	// ������׼ shell ���DDE�����ļ�������������
// 	CCommandLineInfo cmdInfo;
// 	ParseCommandLine(cmdInfo);
// 
// 
// 
// 	// ��������������ָ�������  ���
// 	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
// 	if (!ProcessShellCommand(cmdInfo))
// 		return FALSE;
	// �������ѳ�ʼ���������ʾ����������и���
// 	pMainFrame->ShowWindow(m_nCmdShow);
// 	pMainFrame->UpdateWindow();

	return TRUE;
}

int CATradeApp::ExitInstance()
{
	//TODO:  �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	GdiplusShutdown(gdiplusToken);

	g_SockSvr.Close();
	g_SockPrice.Close();

	return CWinAppEx::ExitInstance();
}

// CATradeApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CATradeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CATradeApp �Զ������/���淽��

void CATradeApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CATradeApp::LoadCustomState()
{
}

void CATradeApp::SaveCustomState()
{
}

// CATradeApp ��Ϣ�������


