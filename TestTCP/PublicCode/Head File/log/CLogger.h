#pragma once
#include <afxmt.h>
#include <direct.h>

class CLogger
{
public:
	CLogger(void);
public:
	~CLogger(void);
private:
	void WirteInfoFile(CString infoName,CString chrTime,CString Info,CString chrFilePathName);
public:
	CString m_strLogPath;
	CString m_strLogName;
	CString m_strFirstTime;
	bool m_bLogEnable;
	
	void LogEnable(bool p_bLogEnable);
	void SetLogName(CString p_strLogName);
	void LogFormat(CString p_cLogName,int p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogPath);
	void LogFormat(CString p_cLogName,LONG p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogPath);
	void LogFormat(CString p_cLogName,int p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogName2,CString p_cLogPath);
	void LogFormat(CString p_cLogName,BYTE p_cLogSwitch,CString p_cLogPath);
	
	int WriteLog(CString p_LogStr, CString p_LogPath, CString p_LogName);
	int  WriteLog(CString p_LogStr,CString p_LogPath);
	int  WriteLogOnly(CString p_LogStr,CString p_LogPath);
	int WriteLogOnly(CString p_LogStr, CString p_LogPath, CString p_LogName);
	void SetLogNameNowTime();

	char* CString2char(CString &str,DWORD *outCharLength) ;
	CString QueryExePath();
	void WriteToFile(CString exMsg,CString p_LogPath);
	void WriteToFileOnly(CString exMsg,CString p_LogPath);
	CString xByte2String(BYTE* bytes,int nArrSize);
	
	CString GetNowTime();
	int GetIsEnable(CString p_cstrFileName,CString p_cstrNode,CString p_cstrTag);
	CCriticalSection critical_section;

	void setLogPath(CString strLogPath);

};
