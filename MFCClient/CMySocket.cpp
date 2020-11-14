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
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();		
	str = dlg->m_tm.Format("%X ");
	str += _T("与服务器连接成功");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnSend(nErrorCode);


}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("######OnReceive");
	//1、接收数据到szRecvBuf
	CMFCClientDlg* dlg = (CMFCClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);

	//2、显示buf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3、显示到列表框
	CString strShow = _T("服务端 :");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");	//获取时间

	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
