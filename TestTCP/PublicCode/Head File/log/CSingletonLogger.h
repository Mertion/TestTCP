#pragma once
#include "CLoger.h"

class CSingletonLogger:public CLoger
{
protected:
	CSingletonLogger();

public:
	static CSingletonLogger* initance();

private:
	static CSingletonLogger* m_pSingletonLogger;

};


