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
	CString		Admin;			// ����Ա
	CString		Operator;		// ����Ա
	CString		AssetsUnit;		// �ʲ���Ԫ
	CString		TradeUnit;		// ���׵�Ԫ
	BOOL		IsSavePwd;		// �Ƿ񱣴�����
	CString		Password;		// ����

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
	vector<CString>	vSrvIPs;	// ������IP�б�
	vector<CString>	vSrvPorts;	// �������˿��б�
	vector<CString>	vPriceIPs;	// ����ԴIP�б�
	vector<CString>	vPricePorts;// ����Դ�˿��б�

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
		CString	code;	// ��Ʊ����
		UINT	count;	// ����
	};
public:
	CRecordInfo();
	~CRecordInfo();

	BOOL	bCancelTip;			// �����Ƿ���ʾ
	BOOL	bErrorReSend;		// ���Ƿ��ط�
	BOOL	bWasteReSend;		// �ϵ��Ƿ��ط�
	COLORREF	clrBOColor;		// ����ɫ
	DWORD	HKCancelSingle;		// ���ʳ�����ݼ�
	DWORD	HKCancelBat;		// ����������ݼ�
	DWORD	HKModify;			// �ĵ���ݼ�


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
		int			Direction;	// ����
		int			ReSend;		// �ط�
		int			Price;		// ��λ
		double		Offset;		// �۸�ƫ��ֵ
		int			Count;		// Ĭ�Ϲ���
		DWORD		HotKey;		// ��ݼ�
		BOOL		Default;	// �Ƿ�ΪĬ�Ͽ�ݼ�,F1,F2,F3,F4

		CString HotKeyName();
		CString ReSendName();
		CString	PriceName();
		CString	CountName();
		CString DirectionName();
	};
public:
	CLevel2Info();
	~CLevel2Info();

	COLORREF	clrBid16;	//Bid1/6��ɫ
	COLORREF	clrBid27;	//Bid2/7��ɫ
	COLORREF	clrBid38;	//Bid3/8��ɫ
	COLORREF	clrBid49;	//Bid4/9��ɫ
	COLORREF	clrBid510;	//Bid5/10��ɫ
	COLORREF	clrRise;	//������ɫ	
	COLORREF	clrFall;	//�µ���ɫ

	double		dbLRSacle;	//����������޸Ŀ̶�
	double		dbUDSacle;	//����������޸Ŀ̶�

	
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

