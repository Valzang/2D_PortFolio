#include "TimeManager.h"

TimeManager::TimeManager() : m_prevCount(), m_curCount(),
							m_curFrequency(), m_deltaTime(),
							m_callCount(), m_accumlate(),
							m_FPS(), m_hWnd()
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Init(HWND handle)
{
	m_hWnd = handle;
	// ���� �� ī��Ʈ
	QueryPerformanceCounter(&m_prevCount);

	// �ʴ� �� �� �ִ� ī��Ʈ Ƚ��
	QueryPerformanceFrequency(&m_curFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&m_curCount);

	// ���� �����Ӱ� ���� �������� ī���� ���� ����.
	m_deltaTime = (double)(m_curCount.QuadPart - m_prevCount.QuadPart) / (double)m_curFrequency.QuadPart;

	// ���� ī��Ʈ ���� ��ü���� ����(������ ����� ����)
	m_prevCount = m_curCount;

	// �Լ� ȣ�� Ƚ�� ����
	++m_callCount;

	// �� üũ
	m_accumlate += m_deltaTime; // ��ŸŸ�� ����

	// 1�ʰ� �Ǹ�
	if (m_accumlate >= 1.0)
	{
		m_FPS = m_callCount;
		m_accumlate = 0.0;
		m_callCount = 0;

		wchar_t Buffer[255] = {};
		swprintf_s(Buffer, L"FPS : %d, DT : %.8f", m_FPS, m_deltaTime);
		SetWindowText(m_hWnd, Buffer);
	}
}