#pragma once

#include "CustomDefine.h"
#include "Core.h"

class cTimeManager
{
	SINGLETON2(cTimeManager);

private:
	LARGE_INTEGER m_curCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_curFrequency;

	double m_deltaTime; // 프레임 사이의 시간 값
	double m_accumlate; // 1초 체크를 위한 누적 시간 값
	UINT m_callCount; // 함수 호출 횟수
	UINT m_FPS; // FPS ( 초당 프레임 수 )

public:
	void Init();
	void Update();

	float GetDT() { return (float)m_deltaTime; }

};