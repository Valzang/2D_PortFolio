#include "Object.h"
//#include "CustomDefine.h"

void Object::Update()
{
	if (KeyManager::GetInstance()->GetKeyState(KEY::I) == KEY_STATE::HOLD)
	{
		m_Pos.y -= 200.f * DELTA_TIME;
	}
	if (KeyManager::GetInstance()->GetKeyState(KEY::K) == KEY_STATE::HOLD)
	{
		m_Pos.y += 200.f * DELTA_TIME;
	}
	if (KeyManager::GetInstance()->GetKeyState(KEY::J) == KEY_STATE::HOLD)
	{
		m_Pos.x -= 200.f * DELTA_TIME;
	}
	if (KeyManager::GetInstance()->GetKeyState(KEY::L) == KEY_STATE::HOLD)
	{
		m_Pos.x += 200.f * DELTA_TIME;
	}
}

void Object::Render(HDC _hdc)
{

	// Rectangle은 예시임
	Rectangle(_hdc, (int)(m_Pos.x - m_Scale.x / 2.f), (int)(m_Pos.y - m_Scale.y / 2.f),
			  (int)(m_Pos.x + m_Scale.x / 2.f), (int)(m_Pos.y + m_Scale.y / 2.f));

}
