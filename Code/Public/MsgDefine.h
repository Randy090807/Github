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

#define ID_LOGIN						1001				//��½
#define ID_LOGIN_RESULT					1002                //��½����
#define ID_CHANGE_PASSWORD				1003                //�޸�����
#define ID_CHANGE_PASSWORD_RESULT       1004                //�޸����뷵��
#define ID_FUND_INQUIRY                 2001                //�ʽ��ѯ
#define ID_FUND_INQUIRY_RESULT          2002                //�ʽ��ѯ����
#define ID_POSITION_INQUIRY				2003                //�ֲֲ�ѯ
#define ID_POSITION_INQUIRY_RESULT      2004                //�ֲֲ�ѯ����
#define ID_ORDER_INQUIRY				2005				//������ѯ
#define ID_ORDER_INQUIRY_RESULT			2006				//������ѯ�����ػ�����
#define ID_BOOKING_INQUIRY				2007				//ԤԼ���ѯ
#define ID_BOOKING_INQUIRY_RESULT       2008				//ԤԼ���ѯ����
#define ID_TRANSACTION_RECORDS			2009				//���׼�¼��ѯ
#define ID_TRANSACTION_RECORDS_RESULT	2010				//���׼�¼��ѯ����
#define ID_PLACE_ORDER					3001				//�µ�
#define ID_PLACE_ORDER_RESULT			3002				//�µ�����
#define ID_CANCEL_ORDER					3003				//����
#define ID_CANCEL_ORDER_RESULT			3004				//��������

#define ID_SUBSCRIBE_NEW				9011				//ȫ�¶���
#define ID_SUBSCRIBE_ADD				9012				//���Ӷ���
#define ID_SUBSCRIBE_CANCEL				9013				//ȡ������
#define ID_GET_STOCK_CODE_TABLE			9021				//��ȡ��Ʊ�����
#define ID_GET_STOCK_CODE_TABLE_RESULT	9022				//��ȡ��Ʊ�������
#define ID_PRICE_PUSH					9001				//��������
#define ID_TRANSACTION_PUSH				9002				//��ʳɽ�����

#define ID_CUSTOM_SOCK_CONN_RESULT		10000				//�Զ������ͣ�SOCK���ӽ��������Ϣ
#define ID_CUSTOM_ADD_ORDER				10001				//�Զ������ͣ�Level2��������֪ͨ��Record
#define ID_CUSTOM_PRICE_SOCK_CONN_RESULT	10002				//�Զ������ͣ����� SOCK���ӽ��������Ϣ
#define ID_CUSTOM_LOGIN_INIT_RESULT	10003				//�Զ������ͣ���¼��ʼ�����

#pragma pack(1)
struct MsgHeader
{
	short flag ;	// 2�ֽ�ͷ����ʶ�� 0xDEAD
	short type ;	// 2�ֽ���Ϣ����
	UINT	userdata;
	int len  ;	// 4�ֽ����ݳ���
	
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

//��½��Ϣ
class AFX_EXT_CLASS CLoginMsg : public CBaseMsg
{
public:
	CLoginMsg();
	CString UserID;
	CString Password;

	virtual string GenJson();
	
};

//��½������Ϣ
class AFX_EXT_CLASS CLoginResultMsg : public CBaseResultMsg
{
public:
	CLoginResultMsg();;
	
	CString UserID;
	double InitBP;//��ʼ��֤��
	double BP;//���ñ�֤��
	UINT LastOrderRef;// ������ö���id���ͻ���Ϊÿ������ָ��һ������id����id���ձ������

	virtual void ParseJSon(const char* json);
};


//�޸�����
class AFX_EXT_CLASS CChangePasswordMsg : public CBaseMsg
{
public:
	CChangePasswordMsg();
	CString Password;
	CString NewPassword;

	virtual string GenJson();
};


//�޸����뷵��
class AFX_EXT_CLASS CChangePasswordResultMsg : public CBaseResultMsg
{
public:
	CChangePasswordResultMsg();

	virtual void ParseJSon(const char* json);
};

//�ʽ��ѯ
class AFX_EXT_CLASS CFundInquiryMsg : public CBaseMsg
{
public:
	CFundInquiryMsg();
	string GenJson();
};

//�ʽ��ѯ����
class AFX_EXT_CLASS CFundInquiryResultMsg : public CBaseResultMsg
{
public:
	CFundInquiryResultMsg();
	double InitBP;//��ʼ��֤��
	double BP;//���ñ�֤��
	double ClosePL;//ƽ��ӯ��
	double TradeFee;//���׷���
// 	double PosAmount;//��λ�ʽ�
// 	double PosPL;//ƽ��ӯ��
// 	double TotalPL;//��ӯ��
// 	double TradeFee;//���׷���
// 	double NetPL;//��ӯ��

	virtual void ParseJSon(const char* json);

};

//�ֲֲ�ѯ
class AFX_EXT_CLASS CPositionInquryMsg : public CBaseMsg
{
public:
	CPositionInquryMsg();
	string GenJson();
};


//�ֲֲ�ѯ����
class AFX_EXT_CLASS CPositionInquryResultMsg : public CBaseResultMsg
{
public:
	class CPositionData
	{
	public:
		CPositionData(){};
		CString StockID;
		int Volume;//������>0Ϊ��֣� <0Ϊ�ղ�
		double Amount;//�ܽ��
		double ArgPrice;//ƽ����=amount/volume
	};
public:
	CPositionInquryResultMsg();
	~CPositionInquryResultMsg();

	double BP;
	double InitBp;		// ��ʼ��֤��
	double ColosPl;		// ƽ��ӯ��
	double TradeFee;	//���׷���

	vector<CPositionData*> PositionDatas;

	virtual void ParseJSon(const char* json);
};

//������ѯ
class AFX_EXT_CLASS COrderInquiryMsg : public CBaseMsg
{
public:
	COrderInquiryMsg();
	COrderInquiryMsg(UINT UorderRef);
	UINT OrderRef;//ָ��order_ref���ѯ�˶����������ѯ����
	/*
		zhang 
		���һ��setʵ�֣�
	*/
	string GenJson();
};

//������ѯ���� �� ����
class AFX_EXT_CLASS COrderInquiryResultMsg : public CBaseResultMsg
{
public:
	class AFX_EXT_CLASS COrders
	{
	public:
		COrders(){};
		BOOL IsDone(); // �����Ƿ�ɽ�
		int		Done;//1Ϊ��ᣬ0Ϊδ��ᡣ δ���1���ѯһ�Ρ�
		int		OrderRef;//�ͻ���ָ���Ķ������
		CString OrderID;//ȯ�̲����������
		long	ReportTime;//�걨ʱ��
		CString OrderType;//��������:  1a��ͨ���� 2a��ͨ���� 1b����Ʒ���� 2b����Ʒ���� 1c�������� 2c��ȯ���� 3dԼȯ����
		CString StockID;//��Ʊ����
		int		Volume;//��������
		double	Price;//�����۸�
		int		ExeVol;//�ɽ�����
		double	ExeAmount;//�ɽ����
		double	ExePrice;//�ɽ�����
		int		Status;//����״̬   0δ��  1���� 2�ѱ� 3�ѱ����� 4���ɴ��� 5���� 6�ѳ� 7���� 8�ѳ� 9�ϵ�
		int		Error;//����������
		CString ErrMsg;//����������Ϣ

	};

public:
	COrderInquiryResultMsg();
	~COrderInquiryResultMsg();
	
	vector<COrders*> Orders;

	virtual void ParseJSon(const char* json);
};

//ԤԼ���ѯ
class AFX_EXT_CLASS CBookingInquiryMsg : public CBaseMsg
{
public:
	CBookingInquiryMsg();
	CString StockID;//ָ��order_ref���ѯ�˹�Ʊ�������ѯ����
	string GenJson();
};

//ԤԼ���ѯ����
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

//�µ�
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

//�µ�����
class AFX_EXT_CLASS CPlaceOrderResultMsg : public CBaseResultMsg
{
public:
	CPlaceOrderResultMsg();

	void Copy(CBaseMsg* other);
	virtual void ParseJSon(const char* json);
};

//����
class AFX_EXT_CLASS CCancelOrderMsg : public CBaseMsg
{
public:
	CCancelOrderMsg();
	UINT	OrderRef;

	string GenJson();
};

//��������
class AFX_EXT_CLASS CCancleOrderResultMsg : public CBaseResultMsg
{
public:
	CCancleOrderResultMsg();

	void Copy(CBaseMsg* other);
	virtual void ParseJSon(const char* json);
};

//2009 ���׼�¼��ѯ
class AFX_EXT_CLASS CTransactionRecordsMsg : public CBaseMsg
{
public:
	CTransactionRecordsMsg();
	string GenJson();
};

//2010 ���׼�¼��ѯ����
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
		double ClosePL;//ƽ��ӯ��
		double TradeFee;//���׷���
	};
public:
	CTransactionRecordsResultMsg();
	~CTransactionRecordsResultMsg();
	double InitBP;//��ʼ��֤��
	double BP;//���ñ�֤��
	double ClosePL;//ƽ��ӯ��
	double TradeFee;//���׷���
	vector<CStokes *> Stokes;

	virtual void ParseJSon(const char* json);
};
//
//#define ID_SUBSCRIBE_NEW				9011				//ȫ�¶���
//#define ID_SUBSCRIBE_ADD				9012				//���Ӷ���
//#define ID_SUBSCRIBE_CANCEL				9013				//ȡ������
//#define ID_GET_STOCK_CODE_TABLE			9021				//��ȡ��Ʊ�����
//#define ID_GET_STOCK_CODE_TABLE_RESULT	9022				//��ȡ��Ʊ�������
//#define ID_PRICE_PUSH					9001				//��������
//#define ID_TRANSACTION_PUSH				9002				//��ʳɽ�����
//
//class AFX_EXT_CLASS CSubscribeNewMsg : public CBaseMsg
//{
//public:
//	CSubscribeNewMsg(){};
//	byte *buffer;
//};

struct AFX_EXT_CLASS MarketData {
	char        szCode[32];             //ԭʼCode
	int         nActionDay;             //ҵ������(��Ȼ��)
	int         nTradingDay;            //������
	int            nTime;                 //ʱ��(HHMMSSmmm)
	int            nStatus;               //״̬
	unsigned int nPreClose;               //ǰ���̼�
	unsigned int nOpen;                   //���̼�
	unsigned int nHigh;                   //��߼�
	unsigned int nLow;                    //��ͼ�
	unsigned int nMatch;              //���¼�
	unsigned int nAskPrice[10];           //������
	unsigned int nAskVol[10];         //������
	unsigned int nBidPrice[10];           //�����
	unsigned int nBidVol[10];         //������
	unsigned int nNumTrades;          //�ɽ�����
	__int64        iVolume;               //�ɽ�����
	__int64        iTurnover;             //�ɽ��ܽ��
	__int64        nTotalBidVol;          //ί����������
	__int64        nTotalAskVol;          //ί����������
	unsigned int nWeightedAvgBidPrice;    //��Ȩƽ��ί��۸�
	unsigned int nWeightedAvgAskPrice;  //��Ȩƽ��ί���۸�
	int            nIOPV;                 //IOPV��ֵ��ֵ
	int            nYieldToMaturity;      //����������
	unsigned int nHighLimited;            //��ͣ��
	unsigned int nLowLimited;         //��ͣ��
};

// 9002    ��ʳɽ�����
struct AFX_EXT_CLASS Trasaction {
	char    szCode[32];                 //ԭʼCode
	int     nActionDay;                 //��Ȼ��
	int   nTime;                      //�ɽ�ʱ��(HHMMSSmmm)
	int   nIndex;                     //�ɽ����
	int       nPrice;                     //�ɽ��۸�
	int   nVolume;                    //�ɽ�����
	int       nTurnover;                  //�ɽ����
	int     nBSFlag;                    //��������(��'B', ����'S', ������' ')
	char    chOrderKind;                //�ɽ����
	char    chFunctionCode;             //�ɽ�����
	int       nAskOrder;                  //������ί�����
	int       nBidOrder;                  //����ί�����
};

//��������
class AFX_EXT_CLASS CPricePushMsg : public CBaseMsg
{
public:
	CPricePushMsg(){};
	CString StockID;
	int         nActionDay;             //ҵ������(��Ȼ��)
	int         nTradingDay;            //������
	int            nTime;                 //ʱ��(HHMMSSmmm)
	int            nStatus;               //״̬
	UINT nPreClose;               //ǰ���̼�
	UINT nOpen;                   //���̼�
	UINT nHigh;                   //��߼�
	UINT nLow;                    //��ͼ�
	UINT nMatch;              //���¼�
	UINT nAskPrice[10];           //������
	UINT nAskVol[10];         //������
	UINT nBidPrice[10];           //�����
	UINT nBidVol[10];         //������
	UINT nNumTrades;          //�ɽ�����
	__int64        iVolume;               //�ɽ�����
	__int64        iTurnover;             //�ɽ��ܽ��
	__int64        nTotalBidVol;          //ί����������
	__int64        nTotalAskVol;          //ί����������
	UINT nWeightedAvgBidPrice;    //��Ȩƽ��ί��۸�
	UINT nWeightedAvgAskPrice;  //��Ȩƽ��ί���۸�
	int            nIOPV;                 //IOPV��ֵ��ֵ
	int            nYieldToMaturity;      //����������
	UINT nHighLimited;            //��ͣ��
	UINT nLowLimited;         //��ͣ��
};

#pragma pack()