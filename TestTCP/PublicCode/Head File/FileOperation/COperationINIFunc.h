#pragma once

enum enumOpertionINIFileError
{
	CONFIG_NOERROR = 0,
	GETMODULEPATCH_FAIL,
	INIFILE_NOTFIND
};

class COperationINIFunc
{
public:
	static int GetINIFilePatch(IN CString p_strIniFileName,OUT CString &p_strIniPath);
	static int GetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nDefultVal, IN CString p_strINIFilePath, OUT int &p_nVal);
	static int GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, IN CString p_strINIFilePath, OUT CString &p_strReturnedString);
};