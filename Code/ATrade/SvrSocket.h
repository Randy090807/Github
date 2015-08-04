#pragma once

// CSvrSocket command target
class CBaseMsg;
class CSvrSocket : public CAsyncSocket
{
public:
	enum {BUFF_LEN = 1024*1024};
	CSvrSocket();
	virtual ~CSvrSocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	BOOL IsConnected();
	void Send(CBaseMsg* pMsg);
	void SetMsgReciver(CWnd* pWnd);
protected:
	void Process(UINT nReciveLen);
	void ParseJson(CBaseMsg** pMsg, const char* json, int type);
	void SendMsg(CBaseMsg* pMsg, const char* json);
	char*	m_Buffer;
	UINT	m_nOffset;
	CWnd*	m_pMsgReciver;
	BOOL	bConnected;
};


