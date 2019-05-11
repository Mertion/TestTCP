
#include "stdafx.h"
#include "ConnectionSocketClient.h"


ConnectionSocketClient::ConnectionSocketClient()
{
	init();
}


ConnectionSocketClient::ConnectionSocketClient(int p_nPort, CString p_strAddress, int p_nProtocolType /*= 0*/)
{
	//ConnectionSocketClient();
	init();
	m_serAddr.sin_port = htons(p_nPort);
	//m_serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_serAddr.sin_addr.S_un.S_addr = inet_addr((CStringA)p_strAddress);

	m_nProtocolType = p_nProtocolType;
}

ConnectionSocketClient::~ConnectionSocketClient()
{
	//关闭客户端套接字
	DisConnect();
}

void ConnectionSocketClient::init()
{
	m_serAddr.sin_family = AF_INET;
	m_serAddr.sin_port = htons(0);
	m_serAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	/*m_slisten = INVALID_SOCKET;*/
	m_sclient = INVALID_SOCKET;
	m_bConnectState = false;
}

int ConnectionSocketClient::Connect()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		return ENUM_MESSAGE_CONNECTFAILED;
	}

	m_sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sclient == INVALID_SOCKET)
	{
		WSACleanup();
		return ENUM_MESSAGE_CONNECTFAILED;
	}

	if (connect(m_sclient, (sockaddr *)&m_serAddr, sizeof(m_serAddr)) == SOCKET_ERROR)
	{  //连接失败 
		closesocket(m_sclient);
		m_sclient = INVALID_SOCKET;
		WSACleanup();
		return 0;
	}

	m_bConnectState = true;
	return ENUM_MESSAGE_SUCCESS;
}


int ConnectionSocketClient::DisConnect()
{
	int ret = 0;
	if (m_sclient != INVALID_SOCKET)
	{
		ret = shutdown(m_sclient, SD_BOTH);
		closesocket(m_sclient);
		m_sclient = INVALID_SOCKET;
		WSACleanup();
	}
	m_bConnectState = false;

	return ENUM_MESSAGE_SUCCESS;
}


bool ConnectionSocketClient::ISConnect()
{
	return m_bConnectState;
}


int ConnectionSocketClient::Receive(char* p_pchrData, const int p_nDataSize, int& p_nRecDatalen)
{
	//char t_arrchrRecvData[const_nMaxReceiveDataLen] = { 0 };

	char* t_pchrRecvData = new char[p_nDataSize];
	memset(t_pchrRecvData, 0, p_nDataSize);
	int ret = recv(m_sclient, t_pchrRecvData, (p_nDataSize - 1), 0);

	memset(p_pchrData, 0, p_nDataSize);
	p_nRecDatalen = 0;
	switch (ret)
	{
	case 0:
	{
		DisConnect();
		ret = ENUM_MESSAGE_DISCONNECT;
	}
	break;
	case SOCKET_ERROR:
	{
		if (10035 == WSAGetLastError())
		{

		}
		if (10060 == WSAGetLastError())
		{

		}

		ret = ENUM_MESSAGE_CONNECTFAILED;
		DisConnect();
	}
	break;
	default:
	{
		if (ret < p_nDataSize)
		{
			memcpy(p_pchrData, t_pchrRecvData, ret);
			p_nRecDatalen = ret;
			ret = ENUM_MESSAGE_SUCCESS;
		}
		else
		{
			ret = ENUM_MESSAGE_ERROR;
		}
	}
	break;
	}

	return ret;
}


int ConnectionSocketClient::Send(char* p_pchrData, int p_nDatalen)
{
	int ret = send(m_sclient, p_pchrData, p_nDatalen, 0);
	if (ret > 0)
	{
		ret = ENUM_MESSAGE_SUCCESS;
	}
	else
	{
		ret = ENUM_MESSAGE_FAILED;
	}
	return ret;
}
