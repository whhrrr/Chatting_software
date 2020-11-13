#pragma once
#include <afxsock.h>
class CChatSocket :
    public CAsyncSocket
{
public:
    CChatSocket();
    virtual ~CChatSocket();
    virtual void OnReceive(int nErrorCode);
};

