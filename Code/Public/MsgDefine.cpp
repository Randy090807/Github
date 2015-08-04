#include "stdafx.h"
#include "MsgDefine.h"
#include <json/json.h>
#include "Utility.h"

CBaseMsg::CBaseMsg()
{
	Header.flag = MSG_HEADER_TAG;
	Header.len = 0;
}

void CBaseMsg::BuildMsgBuf(byte* buf, int& len)
{
	string json = GenJson();
	Header.len = json.length();
	memcpy(buf, &Header, sizeof(Header));
	memcpy(buf + sizeof(Header), json.c_str(), json.length());
	len = json.length() + sizeof(Header);
}

void CBaseMsg::Copy(CBaseMsg* other)
{
	if (other == this)
	{
		return;
	}

	memcpy(&Header, &other->Header, sizeof(Header));
}

CString CBaseMsg::Desc()
{
	CString szText;
	szText.Format(_T("MsgHeader: Tag=0x%02X, Type=%d, Data=0x%02X, Len=%d"),
		Header.flag, Header.type, Header.userdata, Header.len);
	return szText;
}


string CLoginMsg::GenJson()
{
	USES_CONVERSION;
	Json::Value root;
	Json::FastWriter writer;
	
	root["user_id"] = T2A(UserID);
	root["password"] = T2A(Password);

	return writer.write(root);
}

CLoginMsg::CLoginMsg()
{
	Header.type = ID_LOGIN;
}

void CLoginResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{
		CString UserID;
		CString Password;

		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		UserID = A2T(data["user_id"].asString().c_str());
		InitBP = data["init_bp"].asDouble();
		BP = data["bp"].asDouble();
		LastOrderRef = data["last_order_ref"].asInt();
	}
}

CLoginResultMsg::CLoginResultMsg()
{
	Header.type = ID_LOGIN_RESULT;
}


COrderInquiryMsg::COrderInquiryMsg()
{
	Header.type = ID_ORDER_INQUIRY;
	OrderRef = -1;
}

COrderInquiryMsg::COrderInquiryMsg(UINT UorderRef)
{
	Header.type = ID_ORDER_INQUIRY;
	OrderRef = UorderRef;
}

std::string COrderInquiryMsg::GenJson()
{
	Json::Value root;
	Json::FastWriter writer;

	if (OrderRef != -1)
	{
		root["order_ref"] = OrderRef;
	}
	else
	{
		root[""] = "";//root["order_ref"] = "";
	}
	return writer.write(root);
}

CFundInquiryMsg::CFundInquiryMsg()
{
	Header.type = ID_FUND_INQUIRY;
}

std::string CFundInquiryMsg::GenJson()
{
	Json::FastWriter writer;
	Json::Value root;

	root[""] = "";

	return writer.write(root);
}

COrderInquiryResultMsg::COrderInquiryResultMsg()
{
	Header.type = ID_ORDER_INQUIRY_RESULT;
}

void COrderInquiryResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;
	if (reader.parse(json, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素  
	{

		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		Json::Value orders = data["orders"];

		for (UINT i = 0; i < orders.size(); i++)
		{
			Json::Value &current = orders[i];
			COrders* Sorder = new COrders();
			Orders.push_back(Sorder);
			Sorder->Done = current["done"].asInt();
			Sorder->OrderRef = current["order_ref"].asInt();
			Sorder->OrderID = A2T(current["order_id"].asString().c_str());
			Sorder->ReportTime = current["report_time"].asInt();
			Sorder->OrderType = A2T(current["order_type"].asString().c_str());
			Sorder->StockID = A2T(current["stock_id"].asString().c_str());
			Sorder->Volume = current["volume"].asInt();
			Sorder->Price = current["price"].asDouble();
			Sorder->ExeVol = current["exe_vol"].asInt();
			Sorder->ExeAmount = current["exe_amount"].asDouble();
			Sorder->ExePrice = current["exe_price"].asDouble();
			Sorder->Status = current["status"].asInt();
			Sorder->Error = current["error"].asInt();
			Sorder->ErrMsg = A2T(current["errmsg"].asString().c_str());
		}
	}
}

COrderInquiryResultMsg::~COrderInquiryResultMsg()
{
	for (auto iter = Orders.begin(); iter != Orders.end(); ++iter)
	{
		delete *iter;
	}
	Orders.clear();
}

CPlaceOrderMsg::CPlaceOrderMsg()
{
	Header.type = ID_PLACE_ORDER;
}

std::string CPlaceOrderMsg::GenJson()
{
	USES_CONVERSION;

	Json::Value root;
	Json::FastWriter writer;
	root["order_ref"] = OrderRef;
	root["order_id"] = "";
	root["order_type"] = T2A(OrderType);
	root["stock_id"] = T2A(StockID);
	root["volume"] = Volume;
	root["price"] = Price;

	return writer.write(root);
}

void CBookingInquiryResultMsg::Copy(CBaseMsg* other1)
{
	if (other1 == this)
		return;

	CBaseMsg::Copy(other1);
	CBookingInquiryResultMsg* other = dynamic_cast<CBookingInquiryResultMsg*>(other1);
	ASSERT(other);

	Error = other->Error;
	ErrMsg = other->ErrMsg;

	Clear();
	for (auto iter = other->Secs.begin(); iter != other->Secs.end(); ++iter)
	{
		CSecs* pSecs = new CSecs();
		pSecs->StockID = (*iter)->StockID;
		pSecs->Volume = (*iter)->Volume;

		Secs.push_back(pSecs);
	}

}

CBookingInquiryResultMsg::CBookingInquiryResultMsg()
{
	Header.type = ID_BOOKING_INQUIRY_RESULT;
}

CBookingInquiryResultMsg::~CBookingInquiryResultMsg()
{
	Clear();
}

void CBookingInquiryResultMsg::Clear()
{
	for (auto iter = Secs.begin(); iter != Secs.end(); ++iter)
	{
		delete *iter;
	}
	Secs.clear();
}

void CBookingInquiryResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		Json::Value secs = data["secs"];

		for (UINT i = 0; i < secs.size(); i++)
		{
			Json::Value &current = secs[i];
			CSecs *SSecs = new CSecs();
			Secs.push_back(SSecs);

			SSecs->StockID = A2T(current["stock_id"].asString().c_str());
			SSecs->Volume = current["volume"].asUInt();
		}
	}
}

BOOL COrderInquiryResultMsg::COrders::IsDone()
{
	int nStatus = Status;
	if (nStatus == 0 || nStatus == 1 || nStatus == 2 || nStatus == 3 || nStatus == 4 || nStatus == 5)
	{
		return FALSE;
	}
	return  TRUE;
}

CBookingInquiryMsg::CBookingInquiryMsg()
{
	Header.type = ID_BOOKING_INQUIRY;
}

std::string CBookingInquiryMsg::GenJson()
{
	USES_CONVERSION;

	Json::Value root;
	Json::FastWriter writer;

	if (StockID != "")
	{
		root["stock_id"] = T2A(StockID);
	}
	else
	{
		root[""] = "";
	}
	return writer.write(root);
}

CPlaceOrderResultMsg::CPlaceOrderResultMsg()
{
	Header.type = ID_PLACE_ORDER_RESULT;
}

void CPlaceOrderResultMsg::Copy(CBaseMsg* other1)
{
	if (other1 == this)
		return;

	CBaseMsg::Copy(other1);
	CPlaceOrderResultMsg* other = dynamic_cast<CPlaceOrderResultMsg*>(other1);
	ASSERT(other);

	Error = other->Error;
	ErrMsg = other->ErrMsg;
}

void CPlaceOrderResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asUInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());
	}
}

CCancelOrderMsg::CCancelOrderMsg()
{
	Header.type = ID_CANCEL_ORDER;
}

std::string CCancelOrderMsg::GenJson()
{
	Json::Value root;
	Json::FastWriter writer;

	root["order_ref"] = OrderRef;

	return writer.write(root);
}

CCancleOrderResultMsg::CCancleOrderResultMsg()
{
	Header.type = ID_CANCEL_ORDER_RESULT;
}

void CCancleOrderResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asUInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());
	}
}

void CCancleOrderResultMsg::Copy(CBaseMsg* other1)
{
	if (other1 == this)
	{
		return;
	}

	CBaseMsg::Copy(other1);
	CCancleOrderResultMsg* other = dynamic_cast<CCancleOrderResultMsg*>(other1);
	ASSERT(other);

	ErrMsg = other->ErrMsg;
	Error = other->Error;
}

CChangePasswordMsg::CChangePasswordMsg()
{
	Header.type = ID_CHANGE_PASSWORD;
}

std::string CChangePasswordMsg::GenJson()
{
	USES_CONVERSION;
	Json::Value root;
	Json::FastWriter writer;

	root["password"] = T2A(Password);
	root["new_password"] = T2A(NewPassword);

	return writer.write(root);
}

CChangePasswordResultMsg::CChangePasswordResultMsg()
{
	Header.type = ID_CHANGE_PASSWORD_RESULT;
}

void CChangePasswordResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());
	}
}

CPositionInquryMsg::CPositionInquryMsg()
{
	Header.type = ID_POSITION_INQUIRY;
}

std::string CPositionInquryMsg::GenJson()
{
	Json::Value root;
	Json::FastWriter writer;

	root[""] = "";
	
	return writer.write(root);
}

CPositionInquryResultMsg::CPositionInquryResultMsg()
{
	Header.type = ID_POSITION_INQUIRY_RESULT;
}


void CPositionInquryResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		BP = data["bp"].asDouble();
		InitBp = data["init_bp"].asDouble();
		ColosPl = data["close_pl"].asDouble();
		TradeFee = data["trade_fee"].asDouble();

		Json::Value hold = data["hold"];
		for (UINT i = 0; i < hold.size(); i++)
		{
			Json::Value &current = hold[i];
			CPositionData *SPositionData = new CPositionData;
			PositionDatas.push_back(SPositionData);

			SPositionData->StockID = A2T(current["stock_id"].asString().c_str());
			SPositionData->Volume = current["volume"].asInt();
			SPositionData->Amount = current["amount"].asDouble();
			SPositionData->ArgPrice = current["avg_price"].asDouble();
		}
	}
}

CPositionInquryResultMsg::~CPositionInquryResultMsg()
{
	for (auto iter = PositionDatas.begin(); iter != PositionDatas.end(); ++iter)
	{
		delete (*iter);
	}
}

CFundInquiryResultMsg::CFundInquiryResultMsg()
{
	Header.type = ID_FUND_INQUIRY_RESULT;
}

void CFundInquiryResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		InitBP = data["init_bp"].asDouble();
		BP = data["bp"].asDouble();
		ClosePL = data["close_pl"].asDouble();
		TradeFee = data["trade_fee"].asDouble();
	}
}

CTransactionRecordsMsg::CTransactionRecordsMsg()
{
	Header.type = ID_TRANSACTION_RECORDS;
}

std::string CTransactionRecordsMsg::GenJson()
{
	Json::Value root;
	Json::FastWriter writer;

	root[""] = "";

	return writer.write(root);
}

CTransactionRecordsResultMsg::CTransactionRecordsResultMsg()
{
	Header.type = ID_TRANSACTION_RECORDS_RESULT;
}

void CTransactionRecordsResultMsg::ParseJSon(const char* json)
{
	USES_CONVERSION;

	Json::Reader reader;
	Json::Value root;

	if (reader.parse(json, root))
	{
		Error = root["errcode"].asInt();
		ErrMsg = A2T(root["errmsg"].asString().c_str());

		Json::Value data = root["data"];
		InitBP = data["init_bp"].asDouble();
		BP = data["bp"].asDouble();
		ClosePL = data["close_pl"].asDouble();
		TradeFee = data["trade_fee"].asDouble();

		Json::Value stocks = data["stocks"];

		for (UINT i = 0; i < stocks.size(); i++)
		{
			Json::Value &current = stocks[i];
			CStokes* SStokes = new CStokes;
			Stokes.push_back(SStokes);

			SStokes->StockID = A2T(current["stock_id"].asString().c_str());
			SStokes->BuyVol = current["buy_vol"].asInt();
			SStokes->BuyAmount = current["buy_amount"].asDouble();
			SStokes->BuyPrice = current["buy_price"].asDouble();
			SStokes->SellVol = current["sell_vol"].asInt();
			SStokes->SellAmount = current["sell_amount"].asDouble();
			SStokes->SellPrice = current["sell_price"].asDouble();
			SStokes->ClosePL = current["close_pl"].asDouble();
			SStokes->TradeFee = current["trade_fee"].asDouble();
		}
	}
}

CTransactionRecordsResultMsg::~CTransactionRecordsResultMsg()
{
	for (auto iter = Stokes.begin(); iter != Stokes.end(); ++iter)
	{
		delete (*iter);
	}
}
