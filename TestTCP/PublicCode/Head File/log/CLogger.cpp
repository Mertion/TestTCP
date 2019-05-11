#include "stdafx.h"
#include "CLogger.h"
//#include "ConfigIni.h"

CLogger::CLogger(void)
{
	 m_strLogPath =_T("");
	 m_strLogName =_T("");
	 m_strFirstTime = _T("");
	 m_bLogEnable = TRUE;  

	//获得当前exe目录
	TCHAR lpFilePath[MAX_PATH]; 	 
	::GetModuleFileName(NULL,lpFilePath,MAX_PATH);
	(_tcsrchr(lpFilePath, _T('\\')) )[1] = 0;  
	CString strFilePath;
	strFilePath.Format(_T("%s\\CommLog"),lpFilePath);
	m_strLogPath = strFilePath;
	//获取初始化时系统时间
	SYSTEMTIME sysTm;
	::GetLocalTime(&sysTm); 
	m_strFirstTime.Format(_T("[%4d-%02d-%02d][%02d-%02d-%02d_%03d]"),sysTm.wYear,sysTm.wMonth,sysTm.wDay,sysTm.wHour,sysTm.wMinute,sysTm.wSecond,sysTm.wMilliseconds); 
}

void CLogger::setLogPath(CString strLogPath)
{
	m_strLogPath = strLogPath;
};
CString   CLogger::xByte2String(BYTE*   bytes,int   nArrSize) 
{ 
	CString str;
	for(int i=0;i<nArrSize;i++)
	{
		CStringA strTemp;
		strTemp.Format("%x",bytes[i]);
		if(i!=0)
		{
			str+=L"-";
		}
		if(bytes[i]<16)
		{
			str += _T("0") + (CString)strTemp;
		}
		else
		{
			str += _T("") + (CString)strTemp;
		}

	}

	return str;

}
CLogger::~CLogger(void)
{
}
char* CLogger::CString2char(CString &str,DWORD *outCharLength) 
{ 
	int len = str.GetLength(); 
	CStringA strA = (CStringA)str;
	//*outCharLength = len * 2 + 1;
	*outCharLength = len;
	char* chRtn = (char*)malloc((*outCharLength)*sizeof(char));//CString的长度中汉字算一个长度 
	memset(chRtn, 0, *outCharLength); 
	USES_CONVERSION; 
	strcpy((LPSTR)chRtn, strA.LockBuffer());
	return chRtn; 
} 
CString CLogger::QueryExePath()
{
	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL,path,MAX_PATH);
	CString p(path);
	CString subp;
	int nPos = p.ReverseFind('\\');
	//ASSERT(-1!=nPos);
	return p.Left(nPos+1);
}

//***************************************************************************************
//                                   ****文件纪录函数****                              **
//                          ****函数名称:void WirteInfoFile****                        **
//                           ****主要功能:只记录文字不添加时间****                       **
//***************************************************************************************
void CLogger::WriteToFileOnly(CString exMsg,CString p_LogPath)
{

	DWORD dwCharLength;
	char *pChar=CString2char(exMsg,&dwCharLength);


	CString strCurrentFolderPath=QueryExePath();  
	CString t_strLogName ;

	if (m_strLogName=="")
	{
		t_strLogName = m_strFirstTime;
	}
	else
	{
		t_strLogName = m_strLogName;
	}
	
	CString t_strLogPath;
	
	t_strLogPath = strCurrentFolderPath + _T("\\") + p_LogPath + _T("\\") + t_strLogName + _T(".log");
	CStringA t_strLogDir = (CStringA)strCurrentFolderPath + "\\" + (CStringA)p_LogPath;

	FILE *WFile = NULL;
	CStringA t_strAFileName(t_strLogPath);
	char *t_bufFileName = t_strAFileName.GetBuffer();
	//sprintf(chrFileNamePath,"%s",chrFilePathName);

	//创建目录
	int status = mkdir(t_strLogDir);
	//打开文件
	WFile = fopen(t_bufFileName, "a");

	fwrite(pChar, 1, dwCharLength, WFile);
	fwrite("\n", 1, 1, WFile);
	fclose(WFile);

	pChar = NULL;
}
//***************************************************************************************
//                                   ****文件纪录函数****                              **
//                          ****函数名称:void WirteInfoFile****                        **
//                           ****主要功能:记录信息到文本文件****                       **
//***************************************************************************************
void CLogger::WriteToFile(CString exMsg,CString p_LogPath)
{
	SYSTEMTIME sysTm;
	CString strTimeTag;//时间标记
	GetLocalTime(&sysTm);
	//strTimeTag.Format(L"%4d-%2d-%2d %2d:%2d:%2d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
	strTimeTag.Format(_T("[%4d-%02d-%02d][%02d:%02d:%02d.%03d]"),sysTm.wYear,sysTm.wMonth,sysTm.wDay,sysTm.wHour,sysTm.wMinute,sysTm.wSecond,sysTm.wMilliseconds); 

	CString strFullExMsg;//带时间标记的异常信息记录
	strFullExMsg=strTimeTag + exMsg;

	DWORD dwCharLength;
	char *pChar=CString2char(strFullExMsg,&dwCharLength);


	CString strCurrentFolderPath=QueryExePath();  
	CString t_strLogName ;

	if (m_strLogName=="")
	{
		t_strLogName = m_strFirstTime;
	}
	else
	{
		t_strLogName = m_strLogName;
	}
	CString t_strLogPath;
	
	t_strLogPath = strCurrentFolderPath  + _T("\\") + p_LogPath + _T("\\") + t_strLogName + _T(".log");
	CStringA t_strLogDir = (CStringA)strCurrentFolderPath + "\\" + (CStringA)p_LogPath;

	FILE *WFile = NULL;
	CStringA t_strAFileName(t_strLogPath);
	char *t_bufFileName = t_strAFileName.GetBuffer();
	//sprintf(chrFileNamePath,"%s",chrFilePathName);

	//创建目录
	int status = mkdir(t_strLogDir);
	
	//打开文件
	WFile = fopen(t_bufFileName,"a");

	fwrite(pChar,1,dwCharLength,WFile);
	fwrite("\n",1,1,WFile);
	fclose(WFile);

	pChar=NULL;
}
int  CLogger::WriteLogOnly(CString p_LogStr, CString p_LogPath, CString p_LogName)
{
	SetLogName(p_LogName);
	WriteToFileOnly(p_LogStr, p_LogPath);

	return 0;
}
int  CLogger::WriteLog(CString p_LogStr,CString p_LogPath,CString p_LogName)
{
	SetLogName(p_LogName);
	WriteToFile(p_LogStr,p_LogPath);
	
	return 0;
}
int  CLogger::WriteLog(CString p_LogStr, CString p_LogPath)
{
	if (m_bLogEnable == TRUE)
	{

		WriteToFile(p_LogStr, p_LogPath);
	}
	return 0;
}
//只记录字符串不添加时间
int  CLogger::WriteLogOnly(CString p_LogStr,CString p_LogPath)
{
	if (m_bLogEnable==TRUE)
	{

		WriteToFileOnly(p_LogStr,p_LogPath);
	}
	return 0;
}

void CLogger::SetLogName(CString p_strLogName)
{
	m_strLogName = p_strLogName;
}
//设置当前系统时间为日志名,每调用一次修改一次日志文件名
void CLogger::SetLogNameNowTime()
{
	CString FileTime =GetNowTime();
	
	m_strLogName = FileTime;
}
CString CLogger::GetNowTime()
{
	CString FileTime = _T("");
	SYSTEMTIME sysTm;
	::GetLocalTime(&sysTm); 
	FileTime.Format(_T("[%4d-%02d-%02d-%02d-%02d-%02d-%03d]"),sysTm.wYear,sysTm.wMonth,sysTm.wDay,sysTm.wHour,sysTm.wMinute,sysTm.wSecond,sysTm.wMilliseconds); 
	return FileTime;
}
void CLogger::LogEnable(bool p_bLogEnable)
{
	m_bLogEnable = p_bLogEnable;
}
void CLogger::LogFormat(CString p_cLogName,int p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogName2,CString p_cLogPath)
{
	if (p_cLogSwitch == 1)
	{
		CString strlog;
		CString strTmp;
		critical_section.Lock();
		strTmp.Format(p_cLogName + _T("%d"),p_cLogNumber);
		strlog += strTmp;
		strlog = strTmp + p_cLogName2;
		WriteLog(strlog,p_cLogPath);
		critical_section.Unlock();
	}

}
void CLogger::LogFormat(CString p_cLogName,int p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogPath)
{
	if (p_cLogSwitch == 1)
	{
		CString strlog;
		critical_section.Lock();
		strlog.Format(p_cLogName + _T("%d"),p_cLogNumber);
		WriteLog(strlog,p_cLogPath);
		critical_section.Unlock();
	}
}
void CLogger::LogFormat(CString p_cLogName,BYTE p_cLogSwitch,CString p_cLogPath)
{
	if (p_cLogSwitch == 1)
	{
		CString strlog;
		critical_section.Lock();
		WriteLog(p_cLogName,p_cLogPath);
		critical_section.Unlock();
	}
}
void CLogger::LogFormat(CString p_cLogName,LONG p_cLogNumber,BYTE p_cLogSwitch,CString p_cLogPath)
{
	if (p_cLogSwitch == 1)
	{
		CString strlog;
		critical_section.Lock();
		strlog.Format(p_cLogName + _T("%d"),p_cLogNumber);
		WriteLog(strlog,p_cLogPath);
		critical_section.Unlock();
	}
}