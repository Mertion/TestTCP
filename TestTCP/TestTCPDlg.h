
// TestTCPDlg.h : ͷ�ļ�
//

#pragma once

#include "Communicator/ConnectionSocketServer.h"
#include "Communicator/ConnectionSocketClient.h"

// CTestTCPDlg �Ի���
class CTestTCPDlg : public CDialogEx
{
// ����
public:
	CTestTCPDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTTCP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
