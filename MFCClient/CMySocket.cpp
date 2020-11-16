#include "pch.h"
#include "CMySocket.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
//���캯��
CMySocket::CMySocket()
{
}


//��������
CMySocket::~CMySocket()
{
}


void CMySocket::OnConnect(int nErrorCode)
{
	TRACE("######OnConnect");
	CMFCClientDlg* dlg = (CMFCClientDlg*) AfxGetApp()->GetMainWnd();


	CString strShow;
	CString strInfo = _T("");
	CString strMsg = _T("����������ӳɹ�");
	strShow = dlg->CatShowString(strInfo, strMsg);
	dlg->m_list.AddString(strShow);


	CAsyncSocket::OnSend(nErrorCode);


}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("######OnReceive");
	//1���������ݵ�szRecvBuf
	CMFCClientDlg* dlg = (CMFCClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[SEND_MAX_BUF] = { 0 };
	Receive(szRecvBuf, SEND_MAX_BUF, 0);

	//2����ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3����ʾ���б��

	CString strShow;
	CString strInfo = _T("����� :");
	strShow = dlg->CatShowString(strInfo, strRecvMsg);
	dlg->m_list.AddString(strShow);


	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
