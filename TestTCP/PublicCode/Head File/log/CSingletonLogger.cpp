#include "stdafx.h"
#include "CSingletonLogger.h"


CSingletonLogger::CSingletonLogger(void)
{
	
}
CSingletonLogger* CSingletonLogger::m_pSingletonLogger = new CSingletonLogger;
CSingletonLogger* CSingletonLogger::initance()
{
	return m_pSingletonLogger;
}
