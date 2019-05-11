
// TestTCPDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestTCP.h"
#include "TestTCPDlg.h"
#include "afxdialogex.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestTCPDlg �Ի���



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


// CTestTCPDlg ��Ϣ�������

BOOL CTestTCPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_ConnectionSocketServer = new ConnectionSocketServer(8888, _T("127.0.0.1"), 0);
	m_ConnectionSocketCliet = new ConnectionSocketClient(8888, _T("127.0.0.1"), 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestTCPDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestTCPDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CTestTCPDlg::OnBnClickedButtoncreatserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	
	m_ConnectionSocketServer->Connect();
}


void CTestTCPDlg::OnBnClickedButtonCreatclient()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	
	m_ConnectionSocketCliet->Connect();
}


void CTestTCPDlg::OnBnClickedButtonServersend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ConnectionSocketServer->Send("Server", 6);

	Sleep(100);
	char chrRec[256];
	int t_nLen = 0;
	m_ConnectionSocketCliet->Receive(chrRec, 256, t_nLen);

	CStringA str(chrRec);
	
}


void CTestTCPDlg::OnBnClickedButtonClientsend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_ConnectionSocketCliet->Send("Client", 6);
	Sleep(100);
	char chrRec[256];
	int t_nLen = 0;
	m_ConnectionSocketServer->Receive(chrRec, 256, t_nLen);
	CStringA str(chrRec);
}


void CTestTCPDlg::OnBnClickedButtonCloseserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	m_ConnectionSocketServer->DisConnect();
	//delete m_ConnectionSocketServer;

}


void CTestTCPDlg::OnBnClickedButtonCloseclient()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	m_ConnectionSocketCliet->DisConnect();
}
