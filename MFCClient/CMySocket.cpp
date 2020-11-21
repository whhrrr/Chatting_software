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

	//选中单选框按钮
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//自动回复
		//1、读编辑框的内容
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		
		//2、封包 + 组格式  时间+昵称+自动回复+内容
		CString strName;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strName);
		//发送的消息
		CString strMsg = strName +  _T("[自动回复]:") + strAutoSendMsg;
		//消息发送给服务端
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

		//时间 + 昵称 + strMsg
		strShow = dlg->CatShowString(_T(""),strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}


	CAsyncSocket::OnReceive(nErrorCode);
}
