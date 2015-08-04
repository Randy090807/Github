// SvrSocket.cpp : implementation file
//

#include "stdafx.h"
#include "PriceSocket.h"
#include "../Public/MsgDefine.h"
#include "../Public/Logger.h"

// CSvrSocket

CPriceSocket::CPriceSocket()
	: m_pMsgReciver(NULL)
	, m_nOffset(0)
{
	m_Buffer = new char[BUFF_LEN];
}

CPriceSocket::~CPriceSocket()
{
	delete m_Buffer;
}

// CSvrSocket member functions
void CPriceSocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	CAsyncSocket::OnConnect(nErrorCode);

// 	char* b1 = 0;
// 	int l = 0;
// 	CMsgBuilder::BuildNewOrder(_T("000001"), b1, l);
// 	__super::Send(b1, l);
// 	delete b1;
// 
// 	
// 
// 	byte* buf = new byte[1024 * 10];
// 	char buffer[] = "000001";
// 	CBaseMsg msg;
// 	msg.Header.type = ID_SUBSCRIBE_NEW;
// 	msg.Header.len = strlen(buffer);
// 	int msgLen = sizeof(MsgHeader);
// 	memcpy(buf, &(msg.Header), msgLen);
// 	memcpy(buf + msgLen, buffer, strlen(buffer));
//	__super::Send(buf, sizeof(MsgHeader) + strlen(buffer));

	CLoginResultMsg* pMsg = new CLoginResultMsg();
	pMsg->Header.type = ID_CUSTOM_PRICE_SOCK_CONN_RESULT;
	pMsg->Error = nErrorCode;
	::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_NOTIFY, (WPARAM)pMsg, 0);

	if (nErrorCode == 0)
	{
		BOOL bDontLinger = FALSE;
		BOOL bRet = SetSockOpt(SO_DONTLINGER, (const char*)&bDontLinger, sizeof(BOOL));
	}
}


void CPriceSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnClose(nErrorCode);
}


void CPriceSocket::OnReceive(int nErrorCode)
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


void CPriceSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class

	CAsyncSocket::OnSend(nErrorCode);
}

void CPriceSocket::SetMsgReciver(CWnd* pWnd)
{
	ASSERT(pWnd);
	m_pMsgReciver = pWnd;
}

void CPriceSocket::Process(UINT nReciveLen)
{
	UINT uiEndPos = m_nOffset + nReciveLen;	// 缓冲区尾部位置
	UINT uiOffset = 0;						// 临时偏移值

	char* buffer = m_Buffer/* + m_nOffset*/;	// 当前正在处理的消息开始位置
	int  uiLeftSize = uiEndPos - uiOffset;	// 剩余尚未处理的缓冲区字节数

	while (1)
	{
		if (uiLeftSize >= sizeof(MsgHeader))
		{
			MsgHeader* pHeader = (MsgHeader*)buffer;
			if ( uiLeftSize < pHeader->len)
			{
				m_nOffset += nReciveLen;
				break;
			}
			
			int l = sizeof(MsgHeader) + pHeader->len;
			char* Msg = new char[l];
			memcpy(Msg, buffer, l);
			SendMsg(Msg,l);

			CLogger::Inst()->Write(_T("***************************receive push Msg******************************"));
			CString szText;
			szText.Format(_T("MsgHeader: Tag=0x%02X, Type=%d, Data=0x%02X, Len=%d"),
				pHeader->flag, pHeader->type, pHeader->userdata, pHeader->len);
			CLogger::Inst()->Write(szText);

			buffer += l;
			uiLeftSize -= l;
		}
		else   // 剩余的长度小于消息的实际长度，此时可能消息头部并未收
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


void CPriceSocket::SendMsg(void* pMsg, int Len)
{
	::PostMessage(m_pMsgReciver->GetSafeHwnd(), UM_SRV_DATA_NOTIFY2, (WPARAM)pMsg, Len);
}
