#pragma once

// CSvrSocket command target
class CBaseMsg;
class CPriceSocket : public CAsyncSocket
{
public:
	enum {BUFF_LEN = 10*1024*1024};
	CPriceSocket();
	virtual ~CPriceSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	void SetMsgReciver(CWnd* pWnd);
protected:
	void Process(UINT nReciveLen);
	void SendMsg(void* pMsg, int Len);
	char*	m_Buffer;
	UINT	m_nOffset;
	CWnd*	m_pMsgReciver;
};


