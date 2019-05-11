#pragma once
#include "COperationINIFunc.h"

class CINIObject :public COperationINIFunc
{
private:
	CString m_strINIFilePatch;
	CString m_strINIFileName;
public:
	CINIObject(void);
	~CINIObject(void);

	void SetINIFileName(IN CString p_strINIFileName);
	void SetINIFilePath(IN CString p_strINIFilePatch);
	int GetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nDefultVal, OUT int &p_nVal);
	int GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT CString &p_strReturnedString);
	int GetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strDefult, IN int p_nSize, OUT TCHAR *p_strReturnedString);
	int SetProfileInt(IN CString p_strAppName, IN CString p_strKEY, IN int p_nVal);
	int SetProfileString(IN CString p_strAppName, IN CString p_strKEY, IN CString p_strVal);
};