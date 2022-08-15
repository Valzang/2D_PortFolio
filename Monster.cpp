#include "Monster.h"

#include "TimeManager.h"


cMonster::cMonster() :
	m_Speed(100.f)
	, m_MonsterImg(nullptr)
{
	m_curGroupType = (INT)GROUP_TYPE::MONSTER;
}

cMonster::~cMonster()
{
	PlaySound(TEXT("Sound/EFFECT/Monster_Death.wav"), NULL, SND_ASYNC);//여기에 효과음 넣으면 될듯
	if(m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}
/*
bool cMonster::Update()
{
	//m_MonsterImg->RotateFlip(RotateNoneFlipX);
	if (m_HP <= 0)
		return false;
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
	SetPosOtherside();
	return true;
}
*/


/*
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
	Vec2 Scale = GetScale();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_MonsterImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}
*/