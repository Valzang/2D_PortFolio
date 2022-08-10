#include "TimeManager.h"

cTimeManager::cTimeManager() : m_prevCount(), m_curCount(),
m_curFrequency(), m_deltaTime(),
m_callCount(), m_accumlate(),
m_FPS()
{

}

cTimeManager::~cTimeManager()
{

}

void cTimeManager::Init()
{
	// 현재 센 카운트
	QueryPerformanceCounter(&m_prevCount);

	// 초당 셀 수 있는 카운트 횟수
	QueryPerformanceFrequency(&m_curFrequency);
}

void cTimeManager::Update()
{
	HWND hWnd = GetFocus();
	QueryPerformanceCounter(&m_curCount);

	// 이전 프레임과 현재 프레임의 카운팅 값의 차이.
	bool before1 = false;
	// 프레임 제한 걸기
	if(m_deltaTime < 0.014)
	{
		m_deltaTime += (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
	}
	else
	{
		m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
		before1 = true;
	}


	// 이전 카운트 값을 전체값을 갱신(다음번 계산을 위해)
	m_prevCount = m_curCount;

	// 초 체크
	if (before1)
	{
		// 함수 호출 횟수 증가
		++m_callCount;
		m_accumlate += m_deltaTime; // 델타타임 누적
	}
		

	// 1초가 되면
	if (m_accumlate >= 1.0)
	{
		m_FPS = m_callCount;
		m_accumlate = 0.0;
		m_callCount = 0;

		wchar_t Buffer[255] = {};
		swprintf_s(Buffer, L"FPS : %d, DT : %.8f", m_FPS, m_deltaTime);
		SetWindowText(cCore::GetInstance()->GetMainHwnd(), Buffer);
	}

}
