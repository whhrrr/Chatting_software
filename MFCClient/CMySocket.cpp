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

	//ѡ�е�ѡ��ť
	if (((CButton*)dlg->GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		//�Զ��ظ�
		//1�����༭�������
		CString strAutoSendMsg;
		dlg->GetDlgItemText(IDC_AUTOSENDMSG_EDIT, strAutoSendMsg);
		
		//2����� + ���ʽ  ʱ��+�ǳ�+�Զ��ظ�+����
		CString strName;
		dlg->GetDlgItemTextW(IDC_NAME_EDIT, strName);
		//���͵���Ϣ
		CString strMsg = strName +  _T("[�Զ��ظ�]:") + strAutoSendMsg;
		//��Ϣ���͸������
		char* szSendBuf = T2A(strMsg);
		dlg->m_client->Send(szSendBuf, SEND_MAX_BUF, 0);

		//ʱ�� + �ǳ� + strMsg
		strShow = dlg->CatShowString(_T(""),strMsg);
		dlg->m_list.AddString(strShow);
		dlg->m_list.UpdateData(FALSE);
	}


	CAsyncSocket::OnReceive(nErrorCode);
}
