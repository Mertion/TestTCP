
// TestTCPDlg.h : 头文件
//

#pragma once

#include "Communicator/ConnectionSocketServer.h"
#include "Communicator/ConnectionSocketClient.h"

// CTestTCPDlg 对话框
class CTestTCPDlg : public CDialogEx
{
// 构造
public:
	CTestTCPDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TESTTCP_DIALOG };

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
	
	afx_msg void OnBnClickedButtoncreatserver();


	ConnectionSocketServer* m_ConnectionSocketServer;
	ConnectionSocketClient* m_ConnectionSocketCliet;
	afx_msg void OnBnClickedButtonCreatclient();
	afx_msg void OnBnClickedButtonServersend();
	afx_msg void OnBnClickedButtonClientsend();
	afx_msg void OnBnClickedButtonCloseserver();
	afx_msg void OnBnClickedButtonCloseclient();
};
