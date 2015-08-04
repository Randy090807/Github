// SvrSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ATrade.h"
#include "SvrSocket.h"
#include "../Public/MsgDefine.h"
#include "../Public/Config.h"
#include "../Public/Logger.h"
#pragma warning(disable:4018)


// CSvrSocket

CSvrSocket::CSvrSocket()
	: m_pMsgReciver(NULL)
	, m_nOffset(0)
	, bConnected(FALSE)
{
	m_Buffer = new char[BUFF_LEN];
}

CSvrSocket::~CSvrSocket()
{
	delete m_Buffer;
}


// CSvrSocket member functions
void CSvrSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CLoginResultMsg* pMsg = new CLoginResultMsg();
	pMsg->Header.type = ID_CUSTOM_SOCK_CONN_RESULT;
	pMsg->Error = nErrorCode;
	SendMsg(pMsg,"");

	if ( nErrorCode == 0)
	{
		BOOL bDontLinger = FALSE;
		BOOL bRet = SetSockOpt(SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
	}

	bConnected = nErrorCode == 0;
		
	
	CAsyncSocket::OnConnect(nErrorCode);
}


void CSvrSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnClose(nErrorCode);
}


void CSvrSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	if ( nErrorCode == 0)
	{
		int nLen = Receive(m_Buffer+m_nOffset, BUFF_LEN-m_nOffset, 0);
		if ( nLen != 0)
		{
			Process(nLen);
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);
}


void CSvrSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnSend(nErrorCode);
}

void CSvrSocket::SetMsgReciver(CWnd* pWnd)
{
	ASSERT(pWnd);
	m_pMsgReciver = pWnd;
}

void CSvrSocket::Process(UINT nReciveLen)
{
	UINT uiEndPos = m_nOffset + nReciveLen;
	UINT uiOffset = 0;

	char* buffer = m_Buffer + m_nOffset;	// 当前正在处理的消息开始位置
	int  uiLeftSize = uiEndPos - uiOffset;	// 剩余尚未处理的缓冲区字节数

	while (1)
	{
		if (uiLeftSize >= sizeof(MsgHeader))
		{
			MsgHeader* pHeader = (MsgHeader*)buffer;
			if ( uiLeftSize < pHeader->len+sizeof(MsgHeader))
			{
				break;
			}

			char* json = new char[pHeader->len + 1];
			memset(json, 0, pHeader->len + 1);
			memcpy(json, buffer + sizeof(MsgHeader), pHeader->len);

			CBaseMsg* Msg = NULL;
			ParseJson(&Msg, json, pHeader->type);
			memcpy(&Msg->Header, buffer, sizeof(MsgHeader));
			SendMsg(Msg, json);
			delete json;


			buffer += pHeader->len + sizeof(MsgHeader);
			uiLeftSize -= pHeader->len + sizeof(MsgHeader);
		}
		else   // 剩余的长度小于消息的实际长度，此时可能消息头部并未收全
		{
			if (uiLeftSize && uiOffset)
			{
				memmove(m_Buffer, buffer, uiLeftSize);
			}

			m_nOffset = uiLeftSize;
			break;
		}
	}
}

void CSvrSocket::ParseJson(CBaseMsg** pMsg, const char* json, int type)
{
	CBaseMsg*& Msg = *pMsg;
	switch (type)
	{
	case ID_LOGIN_RESULT:
		Msg = new CLoginResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_ORDER_INQUIRY_RESULT:
		Msg = new COrderInquiryResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_BOOKING_INQUIRY_RESULT:
		Msg = new CBookingInquiryResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_CHANGE_PASSWORD_RESULT:
		Msg = new CChangePasswordResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_PLACE_ORDER_RESULT:
		Msg = new CPlaceOrderResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_CANCEL_ORDER_RESULT:
		Msg = new CCancleOrderResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_POSITION_INQUIRY_RESULT:
		Msg = new CPositionInquryResultMsg();
		Msg->ParseJSon(json);
		break;
	case ID_TRANSACTION_RECORDS_RESULT:
		Msg = new CTransactionRecordsResultMsg();
		Msg->ParseJSon(json);
		break;
	default:
		ASSERT(0);
		break;
	}

}

void CSvrSocket::SendMsg(CBaseMsg* pMsg, const char* json)
{
	CLogger::Inst()->Write(_T("***************************Recive Msg******************************"));
	CLogger::Inst()->Write( pMsg->Desc());
	CLogger::Inst()->Write("json: ", json, NULL);
	
	::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, (WPARAM)pMsg, 0);
}

void CSvrSocket::Send(CBaseMsg* pMsg)
{
	CLogger::Inst()->Write(_T("***************************Send Msg******************************"));
	CLogger::Inst()->Write(pMsg->Desc());

	byte* buf = new byte[1024 * 10];
	int len = 0;
	pMsg->BuildMsgBuf(buf, len);
	__super::Send(buf, len);

	buf[len] = 0;
	CLogger::Inst()->Write("josn: ", buf + sizeof(MsgHeader), NULL);

	delete buf;
}

BOOL CSvrSocket::IsConnected()
{
	return bConnected;
}
