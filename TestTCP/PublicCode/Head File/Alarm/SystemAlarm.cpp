#include "stdafx.h"
#include "SystemAlarm.h"


SystemAlarm::SystemAlarm(void)
{
	
}

SystemAlarm* SystemAlarm::m_pSystemAlarm = new SystemAlarm;
bool SystemAlarm::m_bISInitance = false;

SystemAlarm* SystemAlarm::initance()
{
	if (!m_bISInitance)
	{
		m_bISInitance = true;
		m_pSystemAlarm->m_pCSingletonLogger = CSingletonLogger::initance();
		m_pSystemAlarm->m_pfuncSetAlarmInfo = NULL;
	}

	return m_pSystemAlarm;
}

void SystemAlarm::AutomReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (NULL != m_pfuncSetAlarmInfo)
	{
		m_pCSingletonLogger->Wirtelog(CLoger::ENUM_LOGSWITCH_WARNING, "AlarmNo: %d", p_AlarmUnit->AlarmNo);
		m_pfuncSetAlarmInfo((AlarmInfo)(*p_AlarmUnit));
	}
	
}

void SystemAlarm::NormalReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (p_AlarmUnit->bRelease)
	{
		m_pCSingletonLogger->Wirtelog(CLoger::ENUM_LOGSWITCH_DEBUG, "Normal Alarm No:%d  ", p_AlarmUnit->AlarmNo);
		p_AlarmUnit->bRelease = FALSE;
		AutomReleaseAlarm(p_AlarmUnit);
	}
}

void SystemAlarm::ReleaseAlarm(AlarmUnit* p_AlarmUnit)
{
	if (!p_AlarmUnit->bRelease)
	{
		m_pCSingletonLogger->Wirtelog(CLoger::ENUM_LOGSWITCH_DEBUG, "Release No:%d Alarm ", p_AlarmUnit->AlarmNo);
	}
	p_AlarmUnit->bRelease = TRUE;
}

void SystemAlarm::SetAlarmCallBackFunction(void* p_pFun)
{
	m_pfuncSetAlarmInfo = (pfuncSetAlarmInfo)p_pFun;
}
