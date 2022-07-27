#pragma once

#include "CustomDefine.h"

class TimeManager
{
	SINGLETON2(TimeManager);

private:
	LARGE_INTEGER m_curCount;
	LARGE_INTEGER m_prevCount;
	LARGE_INTEGER m_curFrequency;

	HWND m_hWnd = NULL;

	double m_deltaTime; // ������ ������ �ð� ��
	double m_accumlate; // 1�� üũ�� ���� ���� �ð� ��
	UINT m_callCount; // �Լ� ȣ�� Ƚ��
	UINT m_FPS; // FPS ( �ʴ� ������ �� )

public:
	void Init(HWND handle);
	void Update();

	float GetDT() { return (float)m_deltaTime; }

};