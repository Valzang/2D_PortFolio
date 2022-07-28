#include "Bomb.h"
#include "TimeManager.h"

cBomb::cBomb() : m_Direction(1)
{
}

cBomb::~cBomb()
{
}

void cBomb::Update()
{

	Vec2 Pos = GetPos();
	Pos.y += 500.f * DELTA_TIME * m_Direction;

	SetPos(Pos);

}

void cBomb::Render(HDC _hdc)
{
	// Rectangle은 예시임
	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	Ellipse(_hdc, (int)(Pos.x - Scale.x / 2.f), (int)(Pos.y - Scale.y / 2.f),
			  (int)(Pos.x + Scale.x / 2.f), (int)(Pos.y + Scale.y / 2.f));
}
