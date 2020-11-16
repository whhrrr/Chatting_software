#include "pch.h"
#include "CMySocket.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
//构造函数
CMySocket::CMySocket()
{
}


//析构函数
CMySocket::~CMySocket()
{
}


void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("######OnConnect");
	CMFCClientDlg* dlg = (CMFCClientDlg*) AfxGetApp()->GetMainWnd();


	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("与服务器连接成功");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);


	CAsyncSocket::OnSend(nErrorCode);


}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("######OnReceive");
	//1、接收数据到szRecvBuf
	CMFCClientDlg* dlg = (CMFCClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);

	//2、显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3、显示到列表框

	CString strShow;
	CString strInfo = _T("服务端 :");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);


	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
