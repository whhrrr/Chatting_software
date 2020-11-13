#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"


CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}

//回调
void CServerSocket::OnAccept(int nErrorCode)
{
	TRACE("#####OnAccept");
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	//开始接收连接连接
	dlg->m_chat = new CChatSocket;
	Accept(*(dlg->m_chat));

	CString str;
	dlg->m_tm = CTime::GetCurrentTime();


	str = dlg->m_tm.Format("%X ");
	str += _T("客户端连接成功！！！！！");
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);


}
