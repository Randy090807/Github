
// ATrade.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CATradeApp 构造

CATradeApp::CATradeApp()
{
	m_bHiColorIcons = TRUE;
	// TODO:  将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ATrade.AppID.1.0"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CATradeApp 对象

CATradeApp theApp;


// CATradeApp 初始化

BOOL CATradeApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxSocketInit();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("ATRADE_V1.0"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// 初始化配置信息
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

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
// 	CMultiDocTemplate* pDocTemplate;
// 	pDocTemplate = new CMultiDocTemplate(IDR_ATradeTYPE,
// 		RUNTIME_CLASS(CATradeDoc),
// 		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
// 		RUNTIME_CLASS(CATradeView));
// 	if (!pDocTemplate)
// 		return FALSE;
// 	AddDocTemplate(pDocTemplate);

	

	CMainDlg mainDlg;
	mainDlg.DoModal();

	// 创建主 MDI 框架窗口
// 	CMainFrame* pMainFrame = new CMainFrame;
// 	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
// 	{
// 		delete pMainFrame;
// 		return FALSE;
// 	}
// 	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
// 	CCommandLineInfo cmdInfo;
// 	ParseCommandLine(cmdInfo);
// 
// 
// 
// 	// 调度在命令行中指定的命令。  如果
// 	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
// 	if (!ProcessShellCommand(cmdInfo))
// 		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
// 	pMainFrame->ShowWindow(m_nCmdShow);
// 	pMainFrame->UpdateWindow();

	return TRUE;
}

int CATradeApp::ExitInstance()
{
	//TODO:  处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	GdiplusShutdown(gdiplusToken);

	g_SockSvr.Close();
	g_SockPrice.Close();

	return CWinAppEx::ExitInstance();
}

// CATradeApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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

// 用于运行对话框的应用程序命令
void CATradeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CATradeApp 自定义加载/保存方法

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

// CATradeApp 消息处理程序


