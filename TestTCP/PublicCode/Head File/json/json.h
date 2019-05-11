#ifndef JSON_JSON_H_INCLUDED
# define JSON_JSON_H_INCLUDED

# include "autolink.h"
# include "value.h"
# include "reader.h"
# include "writer.h"
# include "features.h"


//#include "json/json.h" 


//���п�ģʽ�궨��˵��
//  Single 	Threaded			/ ML	LIBC(none)
//  Static 	MultiThread			/ MT	LIBCMT	_MT
//  Dynamic Link(DLL)			/ MD	MSVCRT	_MT and _DLL
//  Debug 	Single Threaded		/ MLd	LIBCD	_DEBUG
//  Debug 	Static MultiThread	/ MTd	LIBCMTD	_DEBUG and _MT
//  Debug 	Dynamic Link(DLL)	/ MDd	MSVCRTD	_DEBUG, _MT, and _DLL

//���������궨��˵��
//Visual Studio2013 _MSC_VER != 1800
//Visual Studio2012 _MSC_VER != 1700
//Visual Studio2010 _MSC_VER != 1600
//Visual Studio2008 _MSC_VER != 1500
//Visual Studio2005 _MSC_VER != 1400
//Visual Studio2003 _MSC_VER != 1300
//Visual Studio 6   _MSC_VER != 1200

//lzg 20160308 start
//���ݱ����������п�ģʽ���ز�ͬJSON��
#if (_MSC_VER != 1800) && (_MSC_VER != 1400) && (_MSC_VER != 1914)
#error Please build the lib switch for model
#endif

#ifdef _DEBUG  
#ifndef _WIN64  

#if defined(_MT) && defined(_DLL)

#if (_MSC_VER == 1800)
#pragma comment(lib,"./Lib/json_vc12_libmdd") 
#endif // _MSC_VER = 1800 
#if (_MSC_VER == 1400)
#pragma comment(lib,"./Lib/json_vc8_libmdd")  
#endif // _MSC_VER = 1400 
#if (_MSC_VER == 1914)
#pragma comment(lib,"./Lib/json_vc14_libmdd") 
#endif // _MSC_VER = 1800 
#else
#if (_MSC_VER == 1800)
#pragma comment(lib,"./Lib/json_vc12_libmtd") 
#endif // _MSC_VER = 1800 
#if (_MSC_VER == 1400)
#pragma comment(lib,"./Lib/json_vc8_libmtd")
//#pragma comment(lib,"../../../Include/Lib/JsonLib/json_vc8_libmtd")  
#endif // _MSC_VER = 1400 
#if (_MSC_VER == 1914)
#pragma comment(lib,"./Lib/json_vc14_libmtd")
#endif 
#endif

//#include "../../../Include/Lib/JsonLib/SCM3000Protocol.h"

#else  
#error Please build the lib switch for model
#pragma comment(lib,"./Lib/json_mtd_x64.lib")  
#endif  

#else  
#ifndef _WIN64  
#error Please build the lib switch for model
#pragma comment(lib,"./Lib/json_mt.lib")  
#else  
#error Please build the lib switch for model
#pragma comment(lib,"./Lib/json_mt_x64.lib")  
#endif  
#endif
//lzg 20160308 end

#endif // JSON_JSON_H_INCLUDED
