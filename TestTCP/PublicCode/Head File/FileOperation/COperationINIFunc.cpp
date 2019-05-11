#include "stdafx.h"
#include "COperationINIFunc.h"
#include "Shlwapi.h"

int COperationINIFunc::GetINIFilePatch(IN CString p_strIniFileName,OUT CString &p_strIniPath)
{
	CFileFind t_FileFind;
	int nResult = CONFIG_NOERROR;
	TCHAR szPath[MAX_PATH];

	if (!GetModuleFileName(NULL, szPath, MAX_PATH))
	{
		nResult = GETMODULEPATCH_FAIL;
	}
	else
	{
		PathRemoveFileSpec(szPath);
		
		int t_nPatchLen = lstrlen(szPath);
		if (szPath[t_nPatchLen -1 ] == '\\')
		{
			p_strIniPath = szPath;
		}
		else
		{
			p_strIniPath = szPath;
			p_strIniPath = p_strIniPath + _T("\\");
		}
		p_strIniPath += p_strIniFileName;

		if (t_FileFind.FindFile(p_strIniPath))
		{
			nResult = CONFIG_NOERROR;
		}
		else
		{
			nResult = INIFILE_NOTFIND;
		}
	}

	return nResult;
}

int COperationINIFunc::GetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nDefultVal, IN CString p_strINIFilePath, OUT int &p_nVal)
{
	CFileFind t_FileFind;
	int nResult = CONFIG_NOERROR;

	if (t_FileFind.FindFile(p_strINIFilePath))
	{
		p_nVal = GetPrivateProfileInt(p_strAppName, p_strKEY, p_nDefultVal, p_strINIFilePath);
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
// FullName:  COperationINIFunc::GetProfileString
// Access:    public static 
// Returns:   int
// Qualifier: 从ini文件中读出指定键的字符串
// Parameter: IN CString p_strAppName ini文件中AppName值
// Parameter: IN CString p_strKEY ini文件中KEY值
// Parameter: IN CString p_strDefult 读取失败时默认值
// Parameter: IN int p_nSize 读出数据大小
// Parameter: IN CString p_strINIFilePath ini文件名
// Parameter: OUT CString & p_strReturnedString 输出字符串
//************************************
int COperationINIFunc::GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, IN CString p_strINIFilePath, OUT CString &p_strReturnedString)
{
	CFileFind t_FileFind;
	DWORD t_nRet = 0;
	int nResult = CONFIG_NOERROR;
	TCHAR *t_carrReturnedString = new TCHAR[p_nSize + 1];
	memset(t_carrReturnedString, 0, (p_nSize + 1));
	if (t_FileFind.FindFile(p_strINIFilePath))
	{
		t_nRet = GetPrivateProfileString(p_strAppName, p_strKEY, p_strDefult, t_carrReturnedString, p_nSize, p_strINIFilePath);
		p_strReturnedString = _T("");
		p_strReturnedString.Format(_T("%s"), t_carrReturnedString);
		nResult = CONFIG_NOERROR;
	}
	else
	{
		p_strReturnedString = _T("");
		nResult = INIFILE_NOTFIND;
	}

	return nResult;
}
