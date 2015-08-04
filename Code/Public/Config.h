#pragma once
#include <vector>
#include <map>
using namespace std;


int _sql_callback_load_Logininfo(void * notused, int argc, char ** argv, char ** szColName);
class AFX_EXT_CLASS CLoginInfo
{
	friend int _sql_callback_load_Logininfo(void * notused, int argc, char ** argv, char ** szColName);
	friend class CConfig;
public:
	CLoginInfo();
	~CLoginInfo();
protected:
	void Load();

public:
	CString		Admin;			// 管理员
	CString		Operator;		// 操作员
	CString		AssetsUnit;		// 资产单元
	CString		TradeUnit;		// 交易单元
	BOOL		IsSavePwd;		// 是否保存密码
	CString		Password;		// 密码

	CString GetSrvIP();
	CString GetSrvPort();
	CString GetPriceIP();
	CString GetPricePort();

	void AddSrvIP(LPCTSTR v);
	void AddSrvPort(LPCTSTR v);
	void AddPriceIP(LPCTSTR v);
	void AddPricePort(LPCTSTR v);

	int GetSrvIPSize();
	int GetSrvPortSize();
	int GetPriceIPSize();
	int GetPricePortSize();

	CString GetSrvIPItem(int idx);
	CString GetSrvPortItem(int idx);
	CString GetPriceIPItem(int idx);
	CString GetPricePortItem(int idx);

	
private:
	vector<CString>	vSrvIPs;	// 服务器IP列表
	vector<CString>	vSrvPorts;	// 服务器端口列表
	vector<CString>	vPriceIPs;	// 行情源IP列表
	vector<CString>	vPricePorts;// 行情源端口列表

	void Save();
};

class AFX_EXT_CLASS CStockInfo
{
	friend class CConfig;
public:
	CStockInfo();
	~CStockInfo();

	CString CodeToName(LPCTSTR code);
	void Load(const char* buf, int len);
protected:
	void Load();
	map<CString, CString>	mapDatas;
};

int _sql_callback_load_RecordInfo(void * notused, int argc, char ** argv, char ** szColName);
class AFX_EXT_CLASS CRecordInfo
{
	friend class CConfig;
	friend int _sql_callback_load_RecordInfo(void * notused, int argc, char ** argv, char ** szColName);
public:
	class CBigOrderInfo
	{
	public:
		CBigOrderInfo(){}
		CString	code;	// 股票代码
		UINT	count;	// 数量
	};
public:
	CRecordInfo();
	~CRecordInfo();

	BOOL	bCancelTip;			// 撤单是否提示
	BOOL	bErrorReSend;		// 错单是否重发
	BOOL	bWasteReSend;		// 废单是否重发
	COLORREF	clrBOColor;		// 大单颜色
	DWORD	HKCancelSingle;		// 单笔撤单快捷键
	DWORD	HKCancelBat;		// 批量撤单快捷键
	DWORD	HKModify;			// 改单快捷键


	int	BOSize();
	CRecordInfo::CBigOrderInfo* Item(int idx);
	void Delete(int idx);
	void Add(CRecordInfo::CBigOrderInfo* pBOI);
	void Clear();
	
protected:
	void ParseBOInfo(const char* xmlInfo);
	string GenBOInfo();
	void Load();
	void Save();
	vector<CRecordInfo::CBigOrderInfo*>	vBigOrders;
};

int _sql_callback_load_Level2Info(void * notused, int argc, char ** argv, char ** szColName);
class AFX_EXT_API CLevel2Info
{
	friend class CConfig;
	friend int _sql_callback_load_Level2Info(void * notused, int argc, char ** argv, char ** szColName);
public:
	class AFX_EXT_API CHotKeySet
	{
	public:
		CHotKeySet() :Direction(0), ReSend(0), Price(0), Offset(0), Count(0), HotKey(0), Default(1)
		{}
		int			Direction;	// 方向
		int			ReSend;		// 重发
		int			Price;		// 价位
		double		Offset;		// 价格偏移值
		int			Count;		// 默认股数
		DWORD		HotKey;		// 快捷键
		BOOL		Default;	// 是否为默认快捷键,F1,F2,F3,F4

		CString HotKeyName();
		CString ReSendName();
		CString	PriceName();
		CString	CountName();
		CString DirectionName();
	};
public:
	CLevel2Info();
	~CLevel2Info();

	COLORREF	clrBid16;	//Bid1/6颜色
	COLORREF	clrBid27;	//Bid2/7颜色
	COLORREF	clrBid38;	//Bid3/8颜色
	COLORREF	clrBid49;	//Bid4/9颜色
	COLORREF	clrBid510;	//Bid5/10颜色
	COLORREF	clrRise;	//上涨颜色	
	COLORREF	clrFall;	//下跌颜色

	double		dbLRSacle;	//方向键上下修改刻度
	double		dbUDSacle;	//方向键左右修改刻度

	
	int	HKSize();
	CLevel2Info::CHotKeySet* Item(int idx);
	void Delete(int idx);
	void Add(CLevel2Info::CHotKeySet* pHKS);
	void Clear();
	
protected:
	void Load();
	void Save();
	void ParseHKInfo(const char* xmlInfo);
	string GenHKInfo();
	vector<CLevel2Info::CHotKeySet*>	vHotKeys;
};

class AFX_EXT_CLASS CConfig
{
public:
	static CConfig* Inst();
	CLoginInfo* LogInfo();
	CStockInfo* StockInfo();
	CRecordInfo* RecordInfo();
	CLevel2Info* Level2Info();
	void Save();
protected:
	CConfig();
	~CConfig();

	void Init();

protected:
	CLoginInfo	m_LoginInfo;
	CStockInfo	m_StockInfo;
	CRecordInfo	m_RecordInfo;
	CLevel2Info	m_Level2Info;
};

