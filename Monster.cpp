#include "Monster.h"

#include "TimeManager.h"


cMonster::cMonster() :
	m_CenterPos(Vec2 { 0.f, 0.f })
	, m_Speed(100.f)
	, m_MaxDistance(50.f)
	, m_MonsterImg(nullptr)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/FlyingMonster.png");		
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 3.f, (float)m_MonsterImg->GetHeight()));
	
	m_imgAttr.SetColorKey(Color(0, 160, 80), Color(0, 170, 80)); // 왼쪽 컬러에서부터 오른쪽 컬러 사이 값들을 투명하게 만들어줌
	SetDirection(1);
}

cMonster::~cMonster()
{
	if(m_MonsterImg != NULL)
		delete m_MonsterImg;
}

void cMonster::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 3;
	int h = m_MonsterImg->GetHeight();

	int xStart = curFrame * w;
	curFrame = curFrame >= 2 ? 0 : curFrame + 1;

	int yStart = 0;

	Vec2 Temp_Pos = GetPos();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_MonsterImg, Rect((int)Temp_Pos.x-GetScale().x/2, (int)Temp_Pos.y - GetScale().y / 2, w, h), xStart, yStart, w, h, UnitPixel, &m_imgAttr);
}

void cMonster::Update()
{
	Vec2 CurPos = GetPos();

	// 진행 방향으로 시간당 m_Speed 만큼 이동
	CurPos.x += DELTA_TIME * m_Speed * GetDirection();

	float Dist = abs(m_CenterPos.x - CurPos.x) - m_MaxDistance;

	if (Dist > 0.f)
	{
		SetDirection(GetDirection() * -1);
		CurPos.x += Dist * GetDirection();
		m_MonsterImg->RotateFlip(RotateNoneFlipX);
	}

	SetPos(CurPos);
	
}
