#ifndef __CONNECT_H__
#define __CONNECT_H__

#include <afxsock.h>

class CConnect: public CAsyncSocket 
{
public:
	CConnect();				//构造函数
	virtual ~CConnect();	//析构函数
	// Implementation
protected:
	virtual void OnAccept( int nErrorCode );
	virtual void OnConnect( int nErrorCode );
	virtual void OnReceive( int nErrorCode );
	virtual void OnClose( int nErrorCode );
};

#endif