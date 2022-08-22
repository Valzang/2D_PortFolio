#include "TimeManager.h"

cTimeManager::cTimeManager() : m_prevCount(), m_curCount(),
m_curFrequency(), m_deltaTime(), m_deltaTime_temp(0.f),
m_callCount(), m_accumlate(),
m_FPS(), m_isFocusing(true), m_GrabTitle(false)
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
	
	//포커싱 된 윈도우가 누구인지
	HWND hWnd = GetFocus();

	// 포커싱 된 윈도우가 있다면
	if (hWnd != nullptr)
	{
		if (GetGrabTitle())
		{
			QueryPerformanceCounter(&m_curCount);
			m_prevCount = m_curCount;
			m_deltaTime = 0.f;
			m_GrabTitle = false;
		}
		else
		{
			QueryPerformanceCounter(&m_curCount);
			// 이전 프레임과 현재 프레임의 카운팅 값의 차이.
			if (m_isFocusing)
				m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
			else
			{
				m_isFocusing = true;
				m_deltaTime = m_deltaTime_temp;
				m_deltaTime_temp = 0.f;
			}
			++m_callCount;
			m_accumlate += m_deltaTime; // 델타타임 누적
		}
		
	}
	else
	{
		QueryPerformanceCounter(&m_curCount);
		m_isFocusing = false;
		if (!m_isFocusing && m_deltaTime_temp == 0.f)
			m_deltaTime_temp = m_deltaTime;
	}

	m_prevCount = m_curCount;

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
