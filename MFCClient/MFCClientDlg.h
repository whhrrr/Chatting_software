
// MFCClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CMFCClientDlg 对话框
class CMFCClientDlg : public CDialogEx
{
// 构造
public:
	CMFCClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnectBtn();
	afx_msg void OnBnClickedDisconnectBtn();
	CString CatShowString(CString strInfo,CString strMsg);
	CMySocket* m_client;
	CListBox m_list;
	CEdit m_input;	//shift + alt + f
	afx_msg void OnBnClickedSendBtn();
};
