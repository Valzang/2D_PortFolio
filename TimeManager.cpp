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
	// ���� �� ī��Ʈ
	QueryPerformanceCounter(&m_prevCount);

	// �ʴ� �� �� �ִ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_curFrequency);
}

void cTimeManager::Update()
{
	HWND hWnd = GetFocus();
	QueryPerformanceCounter(&m_curCount);

	// ���� �����Ӱ� ���� �������� ī���� ���� ����.
	bool before1 = false;
	// ������ ���� �ɱ�
	if(m_deltaTime < 0.014)
	{
		m_deltaTime += (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
	}
	else
	{
		m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;
		before1 = true;
	}


	// ���� ī��Ʈ ���� ��ü���� ����(������ ����� ����)
	m_prevCount = m_curCount;

	// �� üũ
	if (before1)
	{
		// �Լ� ȣ�� Ƚ�� ����
		++m_callCount;
		m_accumlate += m_deltaTime; // ��ŸŸ�� ����
	}
		

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
