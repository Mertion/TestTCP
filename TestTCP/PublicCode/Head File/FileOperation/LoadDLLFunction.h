#pragma once
enum ERROR_LOADDLLFILE
{
	ERROR_LOADDLLFILE_NOTINIT = -1,
	ERROR_LOADDLLFILE_SUCCESS = 0,
	ERROR_LOADDLLFILE_LOADDLLFAILED,
	ERROR_LOADDLLFILE_LOADFUNCTIONFAILED
};



class CLoadDLLFunction
{
public:
	//CLoadDLLFunction();
	//~CLoadDLLFunction();

	/*static CString GetModuleFileDir();*/
	static int LoadDllFile(IN CString strFileDir, IN CString strFileName, OUT HINSTANCE &pHINSTANCE);

	static int LoadFuncAddress(IN HINSTANCE &pHINSTANCE, IN CString p_strDescription, OUT void ** pFunc);
	static int CheckFuncPinterISNULL(IN void * p_pFunc, IN CString p_strDescription);
};

