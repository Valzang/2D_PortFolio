#include "Monster.h"

#include "TimeManager.h"


cMonster::cMonster() : 	
	m_CenterPos(Vec2 { 0.f, 0.f })
	, m_Speed(100.f)
	, m_MaxDistance(50.f)
	, m_Direction(1)
{
}

cMonster::~cMonster()
{
}

void cMonster::Update()
{
	Vec2 CurPos = GetPos();

	// 진행 방향으로 시간당 m_Speed 만큼 이동
	CurPos.x += DELTA_TIME * m_Speed * m_Direction;

	float Dist = abs(m_CenterPos.x - CurPos.x) - m_MaxDistance;

	if (Dist > 0.f)
	{
		m_Direction *= -1;
		CurPos.x += Dist * m_Direction;
	}

	SetPos(CurPos);

	
}
