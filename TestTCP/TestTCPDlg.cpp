
// TestTCPDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestTCP.h"
#include "TestTCPDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestTCPDlg 对话框



CTestTCPDlg::CTestTCPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestTCPDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestTCPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestTCPDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_creatServer, &CTestTCPDlg::OnBnClickedButtoncreatserver)
	ON_BN_CLICKED(IDC_BUTTON_CreatClient, &CTestTCPDlg::OnBnClickedButtonCreatclient)
	ON_BN_CLICKED(IDC_BUTTON_ServerSend, &CTestTCPDlg::OnBnClickedButtonServersend)
	ON_BN_CLICKED(IDC_BUTTON_ClientSend, &CTestTCPDlg::OnBnClickedButtonClientsend)
	ON_BN_CLICKED(IDC_BUTTON_CloseServer, &CTestTCPDlg::OnBnClickedButtonCloseserver)
	ON_BN_CLICKED(IDC_BUTTON_CloseClient, &CTestTCPDlg::OnBnClickedButtonCloseclient)
END_MESSAGE_MAP()


// CTestTCPDlg 消息处理程序

BOOL CTestTCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	m_ConnectionSocketServer = new ConnectionSocketServer(8888, _T("127.0.0.1"), 0);
	m_ConnectionSocketCliet = new ConnectionSocketClient(8888, _T("127.0.0.1"), 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestTCPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestTCPDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTestTCPDlg::OnBnClickedButtoncreatserver()
{
	// TODO:  在此添加控件通知处理程序代码

	
	m_ConnectionSocketServer->Connect();
}


void CTestTCPDlg::OnBnClickedButtonCreatclient()
{
	// TODO:  在此添加控件通知处理程序代码

	
	m_ConnectionSocketCliet->Connect();
}


void CTestTCPDlg::OnBnClickedButtonServersend()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ConnectionSocketServer->Send("Server", 6);

	Sleep(100);
	char chrRec[256];
	int t_nLen = 0;
	m_ConnectionSocketCliet->Receive(chrRec, 256, t_nLen);

	CStringA str(chrRec);
	
}


void CTestTCPDlg::OnBnClickedButtonClientsend()
{
	// TODO:  在此添加控件通知处理程序代码
	m_ConnectionSocketCliet->Send("Client", 6);
	Sleep(100);
	char chrRec[256];
	int t_nLen = 0;
	m_ConnectionSocketServer->Receive(chrRec, 256, t_nLen);
	CStringA str(chrRec);
}


void CTestTCPDlg::OnBnClickedButtonCloseserver()
{
	// TODO:  在此添加控件通知处理程序代码

	m_ConnectionSocketServer->DisConnect();
	//delete m_ConnectionSocketServer;

}


void CTestTCPDlg::OnBnClickedButtonCloseclient()
{
	// TODO:  在此添加控件通知处理程序代码

	m_ConnectionSocketCliet->DisConnect();
}
