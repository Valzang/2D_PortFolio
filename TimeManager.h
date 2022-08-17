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

	double m_deltaTime; // ������ ������ �ð� ��
	double m_deltaTime_temp; // ������ ������ �ð� ��
	double m_accumlate; // 1�� üũ�� ���� ���� �ð� ��
	UINT m_callCount; // �Լ� ȣ�� Ƚ��
	UINT m_FPS; // FPS ( �ʴ� ������ �� )

	bool m_isFocusing;

	bool m_GrabTitle;

public:
	void Init();
	void Update();

	bool GetGrabTitle() { return m_GrabTitle; }
	void SetGrabTitle() { m_GrabTitle = true; }

	float GetDT() { return (float)m_deltaTime; }

};