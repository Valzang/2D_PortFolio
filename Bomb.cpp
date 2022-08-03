#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI 좌측직선		0	=> 우측 직선
// PI/2 => 아래직선			-PI/2 => 위 직선
// PI/4 => 우측아래대각선		-PI/4 => 우측위 대각선

cBomb::cBomb() : m_BombImg(nullptr), m_TimeLimit(0.0)
{
	m_Dir = Vec2(-2.f, -3.f);
	m_Dir.Normalize();
	m_BombImg = Image::FromFile((WCHAR*)L"Image/Bomb.png");
	SetScale(Vec2((float)m_BombImg->GetWidth()/2, (float)m_BombImg->GetHeight()/2));

	SetImgAttr();
}

cBomb::~cBomb()
{
	if (m_BombImg != NULL)
	{
		delete m_BombImg;
		m_BombImg = nullptr;
	}
}

bool cBomb::Update()
{
	m_TimeLimit += DELTA_TIME;
	if (m_TimeLimit >= 3.f) // 3초가 지나면 사라짐, 오브젝트와 충돌 시에도 사라지게끔 해야할 듯함
		return false;
	Vec2 Pos = GetPos();

	if (!isOnPlatform())
	{
		Pos.x += -600.f * m_Dir.x * DELTA_TIME * GetDirection(); // 바라보는 방향에 맞게끔

		Pos.y += 600.f * m_Dir.y * DELTA_TIME;

		if (m_Dir.y <= 2) // 포물선 그리게끔 일정값 이하일 때는 계속 증가시켜주기.
			m_Dir.y += 8.f * DELTA_TIME;
		if (m_Dir.x > 0) // 폭탄 방향도 마찬가지
			m_Dir.x -= 0.3f * DELTA_TIME;
		else if (m_Dir.x < 0)
			m_Dir.x += 0.3f * DELTA_TIME;

		Collsion(*this, (UINT)GROUP_TYPE::PLATFORM, 1200.f);
	}	
	if (isOnPlatform())
		m_Dir.y = 0;

	//Pos.y += 500.f * DELTA_TIME * GetDirection();
	SetPos(Pos);
	SetPosOtherside();
	return true;
}

void cBomb::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale()/2;

	static int xStart = 0;
	int yStart = 0;
	if (m_TimeLimit >= 1.5f) // 소환한지 1.5초가 넘으면 깜빡이기
	{
		xStart = xStart>0 ? 0 : m_BombImg->GetWidth() / 2;
		yStart = m_BombImg->GetHeight() / 2;
	}

	int w = m_BombImg->GetWidth()/ 2, h = m_BombImg->GetHeight()/ 2;

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}
