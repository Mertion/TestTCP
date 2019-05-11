#include "stdafx.h"

#define MAX_MLCBUFSIZE 8192
const int CONST_PROTOCOLDADALEN = 9;

#define PROTOCOL_PACKAGE_SUCCESS 0
#define PROTOCOL_PACKAGE_FAILED 1

enum ENUM_PROTOCOL_UNPACKAGE
{
	ENUM_PROTOCOL_UNPACKAGE_SUCCESS = 1,			//�ɹ�������ݰ�
	ENUM_PROTOCOL_UNPACKAGE_NONE = 0,				//û������ݰ�
	ENUM_PROTOCOL_UNPACKAGE_ERROR_HEAD = -1,		//���ݰ�ͷ��ʽ����
	ENUM_PROTOCOL_UNPACKAGE_ERROR_END = -2,			//���ݰ�β��ʽ����
	ENUM_PROTOCOL_UNPACKAGE_ERROR_DATALEN = -3,		//���ݰ�β��ʽ����
	ENUM_PROTOCOL_UNPACKAGE_ERROR_CRC = -4,			//CRCУ�����
};


//************************************
// Method:    ProtocolPackage
// FullName:  ProtocolPackage
// Access:    public 
// Returns:   int
// Qualifier: Э����
// Parameter: IN const byte p_byteSourceData[] ��������
// Parameter: IN int p_nSourceDataLen �������ݳ���
// Parameter: OUT byte * p_bytearrCMD ����ָ��
// Parameter: OUT int * p_pCMDLen ����ָ���
//************************************
int __stdcall ProtocolPackage(IN const byte* p_byteSourceData, IN int p_nSourceDataLen, OUT byte* p_bytearrCMD, OUT int* p_pCMDLen);

//************************************
// Method:    ProtocolUnpacking
// FullName:  ProtocolUnpacking
// Access:    public 
// Returns:   int
// Qualifier: Э����
// Parameter: IN const byte p_byteSourceData[]
// Parameter: IN int p_nSourceDataLen
// Parameter: OUT byte * p_bytearrCMD
// Parameter: OUT int * p_pCMDLen
//************************************
int __stdcall ProtocolUnpacking(IN OUT byte* p_pbyteSourceData, IN OUT int* p_pnSourceDataLen, OUT byte* p_bytearrCMD, OUT int* p_pCMDLen);
