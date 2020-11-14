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
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();		
	str = dlg->m_tm.Format("%X ");
	str += _T("����������ӳɹ�");
	dlg->m_list.AddString(str);
	CAsyncSocket::OnSend(nErrorCode);


}

void CMySocket::OnReceive(int nErrorCode)
{
	TRACE("######OnReceive");
	//1���������ݵ�szRecvBuf
	CMFCClientDlg* dlg = (CMFCClientDlg*)AfxGetApp()->GetMainWnd();
	char szRecvBuf[200] = { 0 };
	Receive(szRecvBuf, 200, 0);

	//2����ʾbuf
	USES_CONVERSION;
	CString strRecvMsg = A2W(szRecvBuf);
	//3����ʾ���б��
	CString strShow = _T("����� :");
	CString strTime;
	dlg->m_tm = CTime::GetCurrentTime();
	strTime = dlg->m_tm.Format("%X ");	//��ȡʱ��

	strShow = strTime + strShow;
	strShow += strRecvMsg;
	dlg->m_list.AddString(strShow);
	CAsyncSocket::OnReceive(nErrorCode);
}
