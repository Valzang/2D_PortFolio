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
	// ���� �� ī��Ʈ
	QueryPerformanceCounter(&m_prevCount);

	// �ʴ� �� �� �ִ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_curFrequency);
}

void cTimeManager::Update()
{
	
	//��Ŀ�� �� �����찡 ��������
	HWND hWnd = GetFocus();

	// ��Ŀ�� �� �����찡 �ִٸ�
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
			// ���� �����Ӱ� ���� �������� ī���� ���� ����.
			if (m_isFocusing)
				m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
			else
			{
				m_isFocusing = true;
				m_deltaTime = m_deltaTime_temp;
				m_deltaTime_temp = 0.f;
			}
			++m_callCount;
			m_accumlate += m_deltaTime; // ��ŸŸ�� ����
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

	// 1�ʰ� �Ǹ�
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
