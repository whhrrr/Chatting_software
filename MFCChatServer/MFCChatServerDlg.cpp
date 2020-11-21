	
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"
#include "CServerSocket.h"

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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	//控件关联
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_list);
	DDX_Control(pDX, IDC_COLOUR_COMBO, m_WordColorCombo);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
	ON_BN_CLICKED(IDC_CLEAR_BTN, &CMFCChatServerDlg::OnBnClickedClearBtn)
	ON_BN_CLICKED(IDC_STOP_BTN, &CMFCChatServerDlg::OnBnClickedStopBtn)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_CAL_BTN, &CMFCChatServerDlg::OnBnClickedCalBtn)
	ON_BN_CLICKED(IDC_MAIL_BTN, &CMFCChatServerDlg::OnBnClickedMailBtn)
	ON_BN_CLICKED(IDC_QQ_BTN, &CMFCChatServerDlg::OnBnClickedQqBtn)
	ON_BN_CLICKED(IDB_BAIDU_BTN, &CMFCChatServerDlg::OnBnClickedBaiduBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
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
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));


	// TODO: 在此添加额外的初始化代码
//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	m_WordColorCombo.AddString(_T("黑色"));
	m_WordColorCombo.AddString(_T("红色"));
	m_WordColorCombo.AddString(_T("蓝色"));
	m_WordColorCombo.AddString(_T("绿色"));
	m_WordColorCombo.AddString(_T("黄色"));

	m_WordColorCombo.SetCurSel(0);			//设置当前的选择下标为0
	SetDlgItemText(IDC_COLOUR_COMBO, _T("黑色"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
		dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcBmp,
			0,0,bBitmap.bmWidth,bBitmap.bmHeight,SRCCOPY);
		
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//发送消息标准化格式  strInfo是发送名称  strMsg是发送的消息
CString CMFCChatServerDlg::CatShowString(CString strInfo, CString strMsg)
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

void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(TRUE);

	TRACE("#####OnBnClickedStartBtn");
	CString strPort;

	/*从控件里面获取内容*/
		//获取端口
	GetDlgItem(IDC_PORT_EDIT)->GetWindowTextW(strPort);

	//CString 转 char*  
		/*问题：CString 转 char* 都如何实现*/
	USES_CONVERSION;		//使用宏
	LPCSTR szPort = (LPCSTR)T2A(strPort);
	TRACE("szPort = %s ", szPort);
	int iPort = _ttoi(strPort);
	//创建服务器Socket对象
	m_server = new CServerSocket;
	//通过创建socket  (容错)
	if (!m_server->Create(iPort)) 
	{
		TRACE("m_Server Create errorCode = %d  !!!",GetLastError());
		return;
	}

	if (!m_server->Listen()) 
	{
		TRACE("m_Server Listen errorCode = %d  !!!", GetLastError());
		return;
	}

	CString strShow;
	CString strInfo = _T(" ");
	CString strMsg = _T("建立服务！！");
	strShow = CatShowString(strInfo, strMsg);


	m_list.AddString(strShow);
	UpdateData(FALSE);

}


void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTmpMsg;
	GetDlgItem(IDC_SEND_EDIT)->GetWindowTextW(strTmpMsg);	//IDC_SENDMSG_EDIT是编辑框ID  获取内容到strTmpMsg中

	USES_CONVERSION;
	char* szSendBuf = T2A(strTmpMsg);

	//2、发送给客户端
	m_chat->Send(szSendBuf, SERVER_MAX_BUF, 0);		//暂定200字节

	//3、显示到列表框
	CString strShow;
	CString strInfo = _T("服务端：");
	strShow = CatShowString(strInfo, strTmpMsg);


	m_list.AddString(strShow);
	UpdateData(FALSE);

	//清空编辑框
	GetDlgItem(IDC_SEND_EDIT)->SetWindowTextW(_T(""));
}


void CMFCChatServerDlg::OnBnClickedClearBtn()
{
	// 清屏操作
	m_list.ResetContent();
}


void CMFCChatServerDlg::OnBnClickedStopBtn()
{
	//控制控件
	GetDlgItem(IDC_START_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND_BTN)->EnableWindow(FALSE);

	//回收资源
	m_server->Close();
	if (m_server != NULL) 
	{
		delete m_server;
		m_server = NULL;
	}
	if (m_chat != NULL)
	{
		delete m_chat;
		m_chat = NULL;
	}

	//显示到列表框
	CString strShow;
	strShow = _T("服务器停止连接");
	m_list.AddString(strShow);
	UpdateData(FALSE);

}


HBRUSH CMFCChatServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CString strColor;
	m_WordColorCombo.GetWindowTextW(strColor);		//拿到当前设置颜色到标题中

	if (IDC_MSG_LIST == pWnd->GetDlgCtrlID() || IDC_SEND_EDIT == pWnd->GetDlgCtrlID())
	{
		if (strColor == L"黑色")
		{
			pDC->SetTextColor(RGB(0, 0, 0));
		}
		else if (strColor == L"红色")
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


void CMFCChatServerDlg::OnBnClickedCalBtn()
{
	//执行shell命令
		/*SHSTDAPI_(HINSTANCE) ShellExecuteW(_In_opt_ HWND hwnd, _In_opt_ LPCWSTR lpOperation, _In_ LPCWSTR lpFile, _In_opt_ LPCWSTR lpParameters,
		_In_opt_ LPCWSTR lpDirectory, _In_ INT nShowCmd);*/
	ShellExecute(NULL, L"open", L"calc.exe", NULL, NULL, SW_SHOWNORMAL);


}


void CMFCChatServerDlg::OnBnClickedMailBtn()
{
	ShellExecute(NULL, L"open", L"https://mail.qq.com", NULL, NULL, SW_SHOWNORMAL);
}


void CMFCChatServerDlg::OnBnClickedQqBtn()
{
	ShellExecute(NULL, L"open", L"E:\\Program Files(x86)\\Tencent\\TIM\\Bin\\QQScLauncher.exe", NULL, NULL, SW_SHOWNORMAL);
}




void CMFCChatServerDlg::OnBnClickedBaiduBtn()
{
	ShellExecute(NULL, L"open", L"www.baidu.com", NULL, NULL, SW_SHOWNORMAL);
}


BOOL CMFCChatServerDlg::PreTranslateMessage(MSG* pMsg)
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
	if (pMsg->message == WM_KEYDOWN)
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
