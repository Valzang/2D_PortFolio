#include "Monster.h"

#include "TimeManager.h"


cMonster::cMonster() :
	m_CenterPos(Vec2{ 0.f, 0.f })
	, m_Speed(100.f)
	, m_MaxDistance(50.f)
	, m_MonsterImg(nullptr)
	, m_HP(10)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/FlyingMonster.png");		
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 3.f, (float)m_MonsterImg->GetHeight()));
	
	SetImgAttr();
	SetDirection(1);
}

cMonster::~cMonster()
{
	if(m_MonsterImg != NULL)
		delete m_MonsterImg;
}

bool cMonster::Update()
{
	if (m_HP <= 0)
		return false;
	Vec2 CurPos = GetPos();

	// ���� �������� �ð��� m_Speed ��ŭ �̵�
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
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_MonsterImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}