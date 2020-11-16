#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CChatSocket::CChatSocket()
{
}

CChatSocket::~CChatSocket()
{
}

void CChatSocket::OnReceive(int nErrorCode)
{
	//1、接收数据到szRecvBuf
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SERVER_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SERVER_MAX_BUF,0);
	TRACE("##### Server szRecvBuf = % s", szRecvBuf);
	//2、显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3、显示到列表框
	CString strShow;
	CString strInfo = _T("客户端 :");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);

	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
	

}
