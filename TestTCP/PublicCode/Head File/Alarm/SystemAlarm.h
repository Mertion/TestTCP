#pragma once
#include "PUB/log/CSingletonLogger.h"

//界面用报警信息
typedef struct _AlarmInfo
{
	//报警编号
	int AlarmNo;

}AlarmInfo;

//底层用报警信息
typedef struct _AlarmUnit :public AlarmInfo
{
	//报警状态是否解除，如果一个报警状态未解除，该报警不会再次向界面发送
	BOOL bRelease;
	_AlarmUnit()
	{
		AlarmNo = 0;
		bRelease = TRUE;
	}
}AlarmUnit;

//设置报警信息回调函数
typedef void(WINAPI *pfuncSetAlarmInfo) (AlarmInfo);

//报警类
class SystemAlarm
{
protected:
	SystemAlarm();

public:
	static SystemAlarm* initance();
	//自动解除报警状态，报警后自动解除报警状态，再次调用可直接向界面发送报警
	void AutomReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//手动解除报警状态，报警后需调用解除报警状态方法，再次报警时才会向界面发送报警
	void NormalReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//解除报警状态
	void ReleaseAlarm(AlarmUnit* p_AlarmUnit);
	//设置报警回调函数
	void SetAlarmCallBackFunction(void* p_pFun);
private:
	//自身指针
	static SystemAlarm* m_pSystemAlarm;
	//是否实例化标志
	static bool m_bISInitance;
	//全局日志对象
	CSingletonLogger* m_pCSingletonLogger;

	//界面报警回调函数指针
	pfuncSetAlarmInfo m_pfuncSetAlarmInfo;
};


