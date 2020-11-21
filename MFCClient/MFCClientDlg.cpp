
// MFCClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCClient.h"
#include "MFCClientDlg.h"
#include "afxdialogex.h"
#include<atlbase.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClientDlg 对话框



CMFCClientDlg::CMFCClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//控件关联
	DDX_Control(pDX, IDC_HISTORYMSG_LIST, m_list);
	DDX_Control(pDX, IDC_SENDMSG_EDIT, m_input);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BTN, &CMFCClientDlg::OnBnClickedConnectBtn)
	ON_BN_CLICKED(IDC_DISCONNECT_BTN, &CMFCClientDlg::OnBnClickedDisconnectBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCClientDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_SAVENAME_BTN, &CMFCClientDlg::OnBnClickedSavenameBtn)
	ON_BN_CLICKED(IDC_CLEARMSG_BTN, &CMFCClientDlg::OnBnClickedClearmsgBtn)
	ON_BN_CLICKED(IDC_AUTOSEND_CHECK, &CMFCClientDlg::OnBnClickedAutosendCheck)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CMFCClientDlg 消息处理程序

BOOL CMFCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));		//端口初始化为5000
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));	//地址初始化
	
//将昵称从配置文件中读取
	WCHAR wszName[MAX_PATH] = { 0 };			//WCHAT是宽字节的字符串
	WCHAR strPath[MAX_PATH] = { 0 };

	//获取当前路径
	GetCurrentDirectoryW(MAX_PATH, strPath);


	CString strFilePath;
	strFilePath.Format(L"%ls//Test.ini", strPath);	//L表示宽字节
	DWORD dwNum = GetPrivateProfileStringW(_T("CLIENT"),_T("NAME"),NULL, wszName,MAX_PATH,strFilePath);
	if (dwNum > 0) 
	{
		//获取文本框中内容
		SetDlgItemText(IDC_NAME_EDIT, wszName);
		UpdateData(FALSE);		//控件关联  更新配置文件
	}
	else 
	{
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), L"默认名称", strFilePath);
		SetDlgItemText(IDC_NAME_EDIT,  L"默认名称");
		UpdateData(FALSE);		//控件关联  更新配置文件
	}
	//初始化控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);				//发送按钮隐藏
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);		//断开连接发送按钮隐藏
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);		//自动发送(check)控件隐藏
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);			//连接按钮不隐藏

	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));
	m_WordColorCombo.AddString(_T("黄色"));

	m_WordColorCombo.SetCurSel(0);			//设置当前的选择下标为0
	SetDlgItemText(IDC_COLOUR_COMBO,_T("黑色"));

		


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//1、定义dc
		CPaintDC dc(this); // 用于绘制的设备上下文
		//2、确定绘制区域
		CRect rect;
		GetClientRect(&rect);
		CDialogEx::OnPaint();

		//3、定义并创建一个内存设备环境  创建兼容性DC		(CDC类)
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dcBmp);			//创建与pDc指定的设备兼容的内存设备上下文
		//4、载入资源图片
		CBitmap bmpBackGround;
		bmpBackGround.LoadBitmapW(IDB_ground_BITMAP);

		//5、将图片载入视图  bBitMap位图
		BITMAP bBitmap;
		bmpBackGround.GetBitmap(&bBitmap);

		//6、将位图选入临时的内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackGround);

		//7、绘制（将位图从源矩形复制到目标矩形，必要时可伸缩或压缩位图以符合目标矩形的尺寸）
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp,
			0, 0, bBitmap.bmWidth, bBitmap.bmHeight, SRCCOPY);

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClientDlg::OnBnClickedConnectBtn()
{

	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);				//发送按钮不隐藏
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(TRUE);		//断开连接发送按钮不隐藏
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(TRUE);		//自动发送(check)控件不隐藏
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(FALSE);			//连接按钮隐藏(不可被选中)
	// TODO: 在此添加控件通知处理程序代码
	TRACE("Connect Button");
	//拿到IP和端口
	CString strPort, strIP;

/*从控件里面获取内容*/
	//获取端口
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);
	//获取IP地址
	GetDlgItem(IDC_IPADDRESS)->GetWindowTextW(strIP);

	//CString 转 char*  
		/*问题：CString 转 char* 都如何实现*/
	USES_CONVERSION;		//使用宏
	/*USES_CONVERSION是ATL中的一个宏定义，用于编码转换*/
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	LPCSTR szIP = (LPCSTR)T2A(strIP);
	TRACE("szPort = %s , strIP = %s",szPort,szIP);
	
	//将字符串转换为int型
	int iPort = _ttoi(strPort);
	//创建一个SOCKET对象
	m_client = new CMySocket();
	//创建套接字    容错
	if (!m_client->Create()) 
	{
		TRACE("m_client Create error %d",GetLastError());
		return;
	}
	else 
	{
		TRACE("m_client Create Success!");
	}
	//进程创建和连接
	if(m_client->Connect(strIP, iPort) != SOCKET_ERROR)//不等于无效的SOCKET
	{
		TRACE("m_client Connect error %d",GetLastError());
		return;
	}
	
}

//断开连接
void CMFCClientDlg::OnBnClickedDisconnectBtn()
{
	//1、控制控件
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);				//发送按钮隐藏
	GetDlgItem(IDC_DISCONNECT_BTN)->EnableWindow(FALSE);		//断开连接发送按钮隐藏
	GetDlgItem(IDC_AUTOSEND_CHECK)->EnableWindow(FALSE);		//自动发送(check)控件隐藏
	GetDlgItem(IDC_CONNECT_BTN)->EnableWindow(TRUE);			//连接按钮不隐藏

	//2、回收资源
	m_client->Close();
	if (m_client != NULL) 
	{
		delete m_client;
		m_client = NULL;
	}
	
	//3、显示到列表框

	CString strShow;
	strShow = CatShowString(_T(""), _T("断开与服务器的连接。"));
	m_list.AddString(strShow);
	UpdateData(FALSE);

}


//发送消息标准化格式  strInfo是发送名称  strMsg是发送的消息
CString CMFCClientDlg::CatShowString(CString strInfo, CString strMsg)
{
	//时间 + 信息 + 消息
	CString strTime;
	CTime tmNow;
	tmNow = CTime::GetCurrentTime();
	strTime = tmNow.Format("%X ");	//获取时间
	CString strShow;
	strShow = strTime + strShow;
	strShow += strInfo;
	strShow += strMsg;
	return strShow;
}



void CMFCClientDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//发送信息
	//1、获取编辑框内容
	CString strTmpMsg;
	GetDlgItem(IDC_SENDMSG_EDIT)->GetWindowTextW(strTmpMsg);	//IDC_SENDMSG_EDIT是编辑框ID  获取内容到strTmpMsg中
	
	CString strName;
	GetDlgItem(IDC_NAME_EDIT)->GetWindowTextW(strName);
	strName += ":";

	strTmpMsg = strName + _T("") + strTmpMsg;
	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//2、发送给服务端
	m_client->Send(szSendBuf, SEND_MAX_BUF, 0);		//暂定200字节

	//3、显示到列表框
	CString strShow;
	strShow = CatShowString(_T(""), strTmpMsg);
	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SENDMSG_EDIT)->SetWindowTextW(_T(""));
}


void CMFCClientDlg::OnBnClickedSavenameBtn()
{
	CString strName;
	//获取文本框中内容
	GetDlgItemText(IDC_NAME_EDIT, strName);
	if (strName.GetLength() <= 0)	//容错
	{
		MessageBox(_T("昵称不能为空！！！"));
		return;
	}

	if (IDOK == AfxMessageBox(_T("是否确认修改昵称？"), MB_OKCANCEL)) 
	{
		// 保存昵称
		WCHAR strPath[MAX_PATH] = { 0 };

		//获取当前路径
		GetCurrentDirectoryW(MAX_PATH, strPath);


		CString strFilePath;
		strFilePath.Format(L"%ls//Test.ini", strPath);	//L表示宽字节

		//写配置文件
		WritePrivateProfileStringW(_T("CLIENT"), _T("NAME"), strName, strFilePath);
	}
	

}

/*自动回复控件响应函数                        单选框改为复选框
void CMFCClientDlg::OnBnClickedAutosendRadio()
{
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->GetCheck()) 
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(FALSE);
	}
	else 
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_RADIO))->SetCheck(TRUE);
	}
}*/


void CMFCClientDlg::OnBnClickedClearmsgBtn()
{
	// 清屏操作
	m_list.ResetContent();

}


void CMFCClientDlg::OnBnClickedAutosendCheck()
{
	// TODO: 在此添加控件通知处理程序代码
	if (((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->GetCheck())
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_AUTOSEND_CHECK))->SetCheck(TRUE);
	}
}


HBRUSH CMFCClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);		//拿到当前设置颜色到标题中

	if (IDC_HISTORYMSG_LIST == pWnd->GetDlgCtrlID() || IDC_SENDMSG_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}else if (strColor == L"红色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"蓝色")
		{
			pDC->SetTextColor(RGB(0, 0, 255));
		}
		else if (strColor == L"绿色")
		{
			pDC->SetTextColor(RGB(0, 255, 0));
		}
		else if (strColor == L"黄色")
		{
			pDC->SetTextColor(RGB(255, 255, 0));
		}
	}


	return hbr;
}


BOOL CMFCClientDlg::PreTranslateMessage(MSG* pMsg)
{
	//快捷键使用
	//规避回车键
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) 
	{
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE)
	{
		return TRUE;
	}
	//添加快捷键 ctrl + x 退出对话框
	if (pMsg->message == WM_KEYDOWN )
	{
		if (GetKeyState(VK_CONTROL) < 0)	//ctrl键是否按下
		{
			if (pMsg->wParam == 'X') 
			{
				CDialog::OnOK();		//退出
			}
		}
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}
