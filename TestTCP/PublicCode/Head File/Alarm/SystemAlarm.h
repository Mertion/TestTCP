#pragma once
#include "PUB/log/CSingletonLogger.h"

//�����ñ�����Ϣ
typedef struct _AlarmInfo
{
	//�������
	int AlarmNo;

}AlarmInfo;

//�ײ��ñ�����Ϣ
typedef struct _AlarmUnit :public AlarmInfo
{
	//����״̬�Ƿ��������һ������״̬δ������ñ��������ٴ�����淢��
	BOOL bRelease;
	_AlarmUnit()
	{
		AlarmNo = 0;
		bRelease = TRUE;
	}
}AlarmUnit;

//���ñ�����Ϣ�ص�����
typedef void(WINAPI *pfuncSetAlarmInfo) (AlarmInfo);

//������
class SystemAlarm
{
protected:
	SystemAlarm();

public:
	static SystemAlarm* initance();
	//�Զ��������״̬���������Զ��������״̬���ٴε��ÿ�ֱ������淢�ͱ���
	void AutomReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//�ֶ��������״̬������������ý������״̬�������ٴα���ʱ�Ż�����淢�ͱ���
	void NormalReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//�������״̬
	void ReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//���ñ����ص�����
	void SetAlarmCallBackFunction(void* p_pFun);
private:
	//����ָ��
	static SystemAlarm* m_pSystemAlarm;
	//�Ƿ�ʵ������־
	static bool m_bISInitance;
	//ȫ����־����
	CSingletonLogger* m_pCSingletonLogger;

	//���汨���ص�����ָ��
	pfuncSetAlarmInfo m_pfuncSetAlarmInfo;
};


