#include "stdafx.h"
#include "CINIObject.h"

CINIObject::CINIObject(void)
{
	m_strINIFileName = _T("");
	m_strINIFilePatch = _T("");
}

CINIObject::~CINIObject(void)
{

}

//************************************
// Method:    SetINIFilePatch
// FullName:  CINIObject::SetINIFilePatch
// Access:    public 
// Returns:   void
// Qualifier: 设置INI文件名，并自动绑定程序目录下的同名配置文件
// Parameter: IN CString p_strINIFileName
//************************************
void CINIObject::SetINIFileName(IN CString p_strINIFileName)
{
	m_strINIFileName = p_strINIFileName;

	GetINIFilePatch(m_strINIFileName, m_strINIFilePatch);
}

//************************************
// Method:    SetINIFilePath
// FullName:  CINIObject::SetINIFilePath
// Access:    public 
// Returns:   void
// Qualifier: 设置INI文件完整路径名
// Parameter: IN CString p_strINIFilePatch
//************************************
void CINIObject::SetINIFilePath(IN CString p_strINIFilePatch)
{
	m_strINIFilePatch = p_strINIFilePatch;
}

//************************************
// Method:    GetProfileInt
// FullName:  CINIObject::GetProfileInt
// Access:    public 
// Returns:   int
// Qualifier: 从ini文件中读出指定键的数值
// Parameter: IN CString p_strAppName
// Parameter: IN CString p_strKEY
// Parameter: IN int p_nDefultVal
// Parameter: OUT int & p_nVal
//************************************
int CINIObject::GetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nDefultVal, OUT int &p_nVal)
{
	CFileFind t_FileFind;
	int nResult = CONFIG_NOERROR;

	if (t_FileFind.FindFile(m_strINIFilePatch))
	{
		p_nVal = GetPrivateProfileInt(p_strAppName, p_strKEY, p_nDefultVal, m_strINIFilePatch);
		nResult = CONFIG_NOERROR;
	}
	else
	{
		nResult = INIFILE_NOTFIND;
	}
	
	return nResult;
}

//************************************
// Method:    GetProfileString
// FullName:  CINIObject::GetProfileString
// Access:    public static 
// Returns:   int
// Qualifier: 从ini文件中读出指定键的字符串
// Parameter: IN CString p_strAppName ini文件中AppName值
// Parameter: IN CString p_strKEY ini文件中KEY值
// Parameter: IN CString p_strDefult 读取失败时默认值
// Parameter: IN int p_nSize 读出数据大小
// Parameter: OUT CString & p_strReturnedString 输出字符串
//************************************
int CINIObject::GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT CString &p_strReturnedString)
{
	int nResult = CONFIG_NOERROR;
	TCHAR *t_carrReturnedString = new TCHAR[p_nSize];
	memset(t_carrReturnedString, 0, sizeof(TCHAR) * p_nSize);
	nResult = GetProfileString(p_strAppName, p_strKEY, p_strDefult, p_nSize, t_carrReturnedString);
	if (CONFIG_NOERROR == nResult)
	{
		p_strReturnedString = _T("");
		p_strReturnedString.Format(_T("%s"), t_carrReturnedString);
		nResult = CONFIG_NOERROR;
	}
	else
	{
		p_strReturnedString = _T("");
	}

	return nResult;
}

int CINIObject::GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT TCHAR *p_strReturnedString)
{
	DWORD t_nRet = 0;
	CFileFind t_FileFind;
	int nResult = CONFIG_NOERROR;

	memset(p_strReturnedString, 0, p_nSize);
	if (t_FileFind.FindFile(m_strINIFilePatch))
	{
		t_nRet = GetPrivateProfileString(p_strAppName, p_strKEY, p_strDefult, p_strReturnedString, (p_nSize-1), m_strINIFilePatch);
		
		nResult = CONFIG_NOERROR;
	}
	else
	{
		p_strReturnedString[0] = 0;
		nResult = INIFILE_NOTFIND;
	}

	return nResult;
}



//设置配置文件中指定键的数值
int CINIObject::SetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nVal = 0)
{

	CString t_strIntVal;
	t_strIntVal.Format(_T("%d"), p_nVal);

	return SetProfileString(p_strAppName, p_strKEY, t_strIntVal);
}
//设置配置文件中指定键的字符串
int CINIObject::SetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strVal = _T(""))
{
	CFileFind t_FileFind;
	int nResult = CONFIG_NOERROR;

	if (t_FileFind.FindFile(m_strINIFilePatch))
	{
		WritePrivateProfileString(p_strAppName, p_strKEY, p_strVal, m_strINIFilePatch);
		nResult = CONFIG_NOERROR;
	}
	else
	{
		nResult = INIFILE_NOTFIND;
	}

	return nResult;
}
