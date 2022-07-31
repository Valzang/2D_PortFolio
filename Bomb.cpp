#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"

cBomb::cBomb() : m_BombImg(nullptr)
{
	m_BombImg = Image::FromFile((WCHAR*)L"Image/Bomb.png");
	SetScale(Vec2((float)m_BombImg->GetWidth(), (float)m_BombImg->GetHeight()));

	SetImgAttr();
	SetDirection(-1);
}

cBomb::~cBomb()
{
}

bool cBomb::Update()
{
	Vec2 Pos = GetPos();
	Pos.y += 500.f * DELTA_TIME * GetDirection();
	SetPos(Pos);
	SetPosOtherside();
	return true;
}

void cBomb::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();


	int w = m_BombImg->GetWidth(), h = m_BombImg->GetHeight();

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), 0, 0, w, h, UnitPixel, GetImgAttr());
}
