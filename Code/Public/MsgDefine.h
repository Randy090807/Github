#pragma once

#include <vector>
using namespace std;

#define UM_CLOSE_LEVEL2					WM_USER+0x100

#define UM_NOTIFY_CONFIG_REFRESH		WM_USER+0x200
#define UM_NOTIFY_INIT_COMPLETE			WM_USER+0x201

#define UM_SRV_DATA_NOTIFY				WM_USER+0x300
#define UM_SRV_DATA_REPORT				WM_USER+0x301

#define UM_SRV_DATA_NOTIFY2				WM_USER+0x302
#define UM_SRV_DATA_REPORT2				WM_USER+0x303

#pragma warning(disable:4309)

const short MSG_HEADER_TAG = 0xDEAD;

#define ID_LOGIN						1001				//登陆
#define ID_LOGIN_RESULT					1002                //登陆返回
#define ID_CHANGE_PASSWORD				1003                //修改密码
#define ID_CHANGE_PASSWORD_RESULT       1004                //修改密码返回
#define ID_FUND_INQUIRY                 2001                //资金查询
#define ID_FUND_INQUIRY_RESULT          2002                //资金查询返回
#define ID_POSITION_INQUIRY				2003                //持仓查询
#define ID_POSITION_INQUIRY_RESULT      2004                //持仓查询返回
#define ID_ORDER_INQUIRY				2005				//订单查询
#define ID_ORDER_INQUIRY_RESULT			2006				//订单查询、返回或推送
#define ID_BOOKING_INQUIRY				2007				//预约卷查询
#define ID_BOOKING_INQUIRY_RESULT       2008				//预约卷查询返回
#define ID_TRANSACTION_RECORDS			2009				//交易记录查询
#define ID_TRANSACTION_RECORDS_RESULT	2010				//交易记录查询返回
#define ID_PLACE_ORDER					3001				//下单
#define ID_PLACE_ORDER_RESULT			3002				//下单返回
#define ID_CANCEL_ORDER					3003				//撤单
#define ID_CANCEL_ORDER_RESULT			3004				//撤单返回

#define ID_SUBSCRIBE_NEW				9011				//全新订阅
#define ID_SUBSCRIBE_ADD				9012				//增加订阅
#define ID_SUBSCRIBE_CANCEL				9013				//取消订阅
#define ID_GET_STOCK_CODE_TABLE			9021				//获取股票代码表
#define ID_GET_STOCK_CODE_TABLE_RESULT	9022				//获取股票代码表返回
#define ID_PRICE_PUSH					9001				//行情推送
#define ID_TRANSACTION_PUSH				9002				//逐笔成交推送

#define ID_CUSTOM_SOCK_CONN_RESULT		10000				//自定义类型，SOCK连接结果返回信息
#define ID_CUSTOM_ADD_ORDER				10001				//自定义类型，Level2新增订单通知到Record
#define ID_CUSTOM_PRICE_SOCK_CONN_RESULT	10002				//自定义类型，行情 SOCK连接结果返回信息
#define ID_CUSTOM_LOGIN_INIT_RESULT	10003				//自定义类型，登录初始话完成

#pragma pack(1)
struct MsgHeader
{
	short flag ;	// 2字节头部标识， 0xDEAD
	short type ;	// 2字节消息类型
	UINT	userdata;
	int len  ;	// 4字节数据长度
	
};


class AFX_EXT_CLASS CBaseMsg
{
public:
	CBaseMsg();
	virtual ~CBaseMsg(){}
	MsgHeader	Header;
	virtual void ParseJSon(const char* json){};
	virtual string GenJson(){ return ""; };
	void BuildMsgBuf(byte* buf, int& len);
	virtual void Copy(CBaseMsg* pMsg);
	CString Desc();
};

class AFX_EXT_CLASS CBaseResultMsg : public CBaseMsg
{
public:
	CBaseResultMsg(){}
	~CBaseResultMsg(){}

	UINT	Error;
	CString ErrMsg;
};

//登陆消息
class AFX_EXT_CLASS CLoginMsg : public CBaseMsg
{
public:
	CLoginMsg();
	CString UserID;
	CString Password;

	virtual string GenJson();
	
};

//登陆返回消息
class AFX_EXT_CLASS CLoginResultMsg : public CBaseResultMsg
{
public:
	CLoginResultMsg();;
	
	CString UserID;
	double InitBP;//初始保证金
	double BP;//可用保证金
	UINT LastOrderRef;// 最近可用订单id。客户端为每个订单指定一个订单id，此id当日必须递增

	virtual void ParseJSon(const char* json);
};


//修改密码
class AFX_EXT_CLASS CChangePasswordMsg : public CBaseMsg
{
public:
	CChangePasswordMsg();
	CString Password;
	CString NewPassword;

	virtual string GenJson();
};


//修改密码返回
class AFX_EXT_CLASS CChangePasswordResultMsg : public CBaseResultMsg
{
public:
	CChangePasswordResultMsg();

	virtual void ParseJSon(const char* json);
};

//资金查询
class AFX_EXT_CLASS CFundInquiryMsg : public CBaseMsg
{
public:
	CFundInquiryMsg();
	string GenJson();
};

//资金查询返回
class AFX_EXT_CLASS CFundInquiryResultMsg : public CBaseResultMsg
{
public:
	CFundInquiryResultMsg();
	double InitBP;//初始保证金
	double BP;//可用保证金
	double ClosePL;//平仓盈亏
	double TradeFee;//交易费用
// 	double PosAmount;//仓位资金
// 	double PosPL;//平仓盈亏
// 	double TotalPL;//总盈亏
// 	double TradeFee;//交易费用
// 	double NetPL;//净盈亏

	virtual void ParseJSon(const char* json);

};

//持仓查询
class AFX_EXT_CLASS CPositionInquryMsg : public CBaseMsg
{
public:
	CPositionInquryMsg();
	string GenJson();
};


//持仓查询返回
class AFX_EXT_CLASS CPositionInquryResultMsg : public CBaseResultMsg
{
public:
	class CPositionData
	{
	public:
		CPositionData(){};
		CString StockID;
		int Volume;//股数，>0为多仓， <0为空仓
		double Amount;//总金额
		double ArgPrice;//平均价=amount/volume
	};
public:
	CPositionInquryResultMsg();
	~CPositionInquryResultMsg();

	double BP;
	double InitBp;		// 初始保证金
	double ColosPl;		// 平仓盈亏
	double TradeFee;	//交易费用

	vector<CPositionData*> PositionDatas;

	virtual void ParseJSon(const char* json);
};

//订单查询
class AFX_EXT_CLASS COrderInquiryMsg : public CBaseMsg
{
public:
	COrderInquiryMsg();
	COrderInquiryMsg(UINT UorderRef);
	UINT OrderRef;//指定order_ref则查询此订单，否则查询所有
	/*
		zhang 
		添加一个set实现；
	*/
	string GenJson();
};

//订单查询返回 或 推送
class AFX_EXT_CLASS COrderInquiryResultMsg : public CBaseResultMsg
{
public:
	class AFX_EXT_CLASS COrders
	{
	public:
		COrders(){};
		BOOL IsDone(); // 订单是否成交
		int		Done;//1为完结，0为未完结。 未完结1秒查询一次。
		int		OrderRef;//客户端指定的订单编号
		CString OrderID;//券商产生订单编号
		long	ReportTime;//申报时间
		CString OrderType;//定单类型:  1a普通买入 2a普通卖出 1b担保品买入 2b担保品卖出 1c融资买入 2c融券卖出 3d约券卖出
		CString StockID;//股票代码
		int		Volume;//报单股数
		double	Price;//报单价格
		int		ExeVol;//成交股数
		double	ExeAmount;//成交金额
		double	ExePrice;//成交均价
		int		Status;//订单状态   0未报  1待报 2已报 3已报待撤 4部成待撤 5部撤 6已撤 7部成 8已成 9废单
		int		Error;//订单错误码
		CString ErrMsg;//订单错误信息

	};

public:
	COrderInquiryResultMsg();
	~COrderInquiryResultMsg();
	
	vector<COrders*> Orders;

	virtual void ParseJSon(const char* json);
};

//预约卷查询
class AFX_EXT_CLASS CBookingInquiryMsg : public CBaseMsg
{
public:
	CBookingInquiryMsg();
	CString StockID;//指定order_ref则查询此股票，否则查询所有
	string GenJson();
};

//预约卷查询返回
class AFX_EXT_CLASS CBookingInquiryResultMsg : public CBaseResultMsg
{
public:
	class CSecs
	{
	public:
		CSecs(){};
		CString StockID;
		UINT Volume;
	};

public:
	CBookingInquiryResultMsg();;
	~CBookingInquiryResultMsg();
	void Copy(CBaseMsg* other);
	void Clear();
	virtual void ParseJSon(const char* json);

	vector<CSecs*> Secs;

};

//下单
class AFX_EXT_CLASS CPlaceOrderMsg : public CBaseMsg
{
public:
	CPlaceOrderMsg();
	UINT OrderRef;
	UINT OrderID;
	CString OrderType;
	CString StockID;
	UINT Volume;
	double Price;

	string GenJson();
};

//下单返回
class AFX_EXT_CLASS CPlaceOrderResultMsg : public CBaseResultMsg
{
public:
	CPlaceOrderResultMsg();

	void Copy(CBaseMsg* other);
	virtual void ParseJSon(const char* json);
};

//撤单
class AFX_EXT_CLASS CCancelOrderMsg : public CBaseMsg
{
public:
	CCancelOrderMsg();
	UINT	OrderRef;

	string GenJson();
};

//撤单返回
class AFX_EXT_CLASS CCancleOrderResultMsg : public CBaseResultMsg
{
public:
	CCancleOrderResultMsg();

	void Copy(CBaseMsg* other);
	virtual void ParseJSon(const char* json);
};

//2009 交易记录查询
class AFX_EXT_CLASS CTransactionRecordsMsg : public CBaseMsg
{
public:
	CTransactionRecordsMsg();
	string GenJson();
};

//2010 交易记录查询返回
class AFX_EXT_CLASS CTransactionRecordsResultMsg : public CBaseResultMsg
{
public:
	class CStokes
	{
	public:
		CStokes(){};
		CString StockID;
		int BuyVol;
		double BuyAmount;
		double BuyPrice;
		int SellVol;
		double SellAmount;
		double SellPrice;
		double ClosePL;//平仓盈亏
		double TradeFee;//交易费用
	};
public:
	CTransactionRecordsResultMsg();
	~CTransactionRecordsResultMsg();
	double InitBP;//初始保证金
	double BP;//可用保证金
	double ClosePL;//平仓盈亏
	double TradeFee;//交易费用
	vector<CStokes *> Stokes;

	virtual void ParseJSon(const char* json);
};
//
//#define ID_SUBSCRIBE_NEW				9011				//全新订阅
//#define ID_SUBSCRIBE_ADD				9012				//增加订阅
//#define ID_SUBSCRIBE_CANCEL				9013				//取消订阅
//#define ID_GET_STOCK_CODE_TABLE			9021				//获取股票代码表
//#define ID_GET_STOCK_CODE_TABLE_RESULT	9022				//获取股票代码表返回
//#define ID_PRICE_PUSH					9001				//行情推送
//#define ID_TRANSACTION_PUSH				9002				//逐笔成交推送
//
//class AFX_EXT_CLASS CSubscribeNewMsg : public CBaseMsg
//{
//public:
//	CSubscribeNewMsg(){};
//	byte *buffer;
//};

struct AFX_EXT_CLASS MarketData {
	char        szCode[32];             //原始Code
	int         nActionDay;             //业务发生日(自然日)
	int         nTradingDay;            //交易日
	int            nTime;                 //时间(HHMMSSmmm)
	int            nStatus;               //状态
	unsigned int nPreClose;               //前收盘价
	unsigned int nOpen;                   //开盘价
	unsigned int nHigh;                   //最高价
	unsigned int nLow;                    //最低价
	unsigned int nMatch;              //最新价
	unsigned int nAskPrice[10];           //申卖价
	unsigned int nAskVol[10];         //申卖量
	unsigned int nBidPrice[10];           //申买价
	unsigned int nBidVol[10];         //申买量
	unsigned int nNumTrades;          //成交笔数
	__int64        iVolume;               //成交总量
	__int64        iTurnover;             //成交总金额
	__int64        nTotalBidVol;          //委托买入总量
	__int64        nTotalAskVol;          //委托卖出总量
	unsigned int nWeightedAvgBidPrice;    //加权平均委买价格
	unsigned int nWeightedAvgAskPrice;  //加权平均委卖价格
	int            nIOPV;                 //IOPV净值估值
	int            nYieldToMaturity;      //到期收益率
	unsigned int nHighLimited;            //涨停价
	unsigned int nLowLimited;         //跌停价
};

// 9002    逐笔成交推送
struct AFX_EXT_CLASS Trasaction {
	char    szCode[32];                 //原始Code
	int     nActionDay;                 //自然日
	int   nTime;                      //成交时间(HHMMSSmmm)
	int   nIndex;                     //成交编号
	int       nPrice;                     //成交价格
	int   nVolume;                    //成交数量
	int       nTurnover;                  //成交金额
	int     nBSFlag;                    //买卖方向(买：'B', 卖：'S', 不明：' ')
	char    chOrderKind;                //成交类别
	char    chFunctionCode;             //成交代码
	int       nAskOrder;                  //叫卖方委托序号
	int       nBidOrder;                  //叫买方委托序号
};

//行情推送
class AFX_EXT_CLASS CPricePushMsg : public CBaseMsg
{
public:
	CPricePushMsg(){};
	CString StockID;
	int         nActionDay;             //业务发生日(自然日)
	int         nTradingDay;            //交易日
	int            nTime;                 //时间(HHMMSSmmm)
	int            nStatus;               //状态
	UINT nPreClose;               //前收盘价
	UINT nOpen;                   //开盘价
	UINT nHigh;                   //最高价
	UINT nLow;                    //最低价
	UINT nMatch;              //最新价
	UINT nAskPrice[10];           //申卖价
	UINT nAskVol[10];         //申卖量
	UINT nBidPrice[10];           //申买价
	UINT nBidVol[10];         //申买量
	UINT nNumTrades;          //成交笔数
	__int64        iVolume;               //成交总量
	__int64        iTurnover;             //成交总金额
	__int64        nTotalBidVol;          //委托买入总量
	__int64        nTotalAskVol;          //委托卖出总量
	UINT nWeightedAvgBidPrice;    //加权平均委买价格
	UINT nWeightedAvgAskPrice;  //加权平均委卖价格
	int            nIOPV;                 //IOPV净值估值
	int            nYieldToMaturity;      //到期收益率
	UINT nHighLimited;            //涨停价
	UINT nLowLimited;         //跌停价
};

#pragma pack()