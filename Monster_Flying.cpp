#include "Monster_Flying.h"

cMonster_Flying::cMonster_Flying()
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/FlyingMonster.png");
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 3.f, (float)m_MonsterImg->GetHeight()));

	SetImgAttr();
	SetDirection(1);
}

cMonster_Flying::~cMonster_Flying()
{
	if (m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}

bool cMonster_Flying::Update()
{
	//m_MonsterImg->RotateFlip(RotateNoneFlipX);
	if (m_HP <= 0)
		return false;
	Vec2 CurPos = GetPos();

	// ���� �������� �ð��� m_Speed ��ŭ �̵�
	if (CurPos.y >= GetFirstY() + 30.f)
		m_Speed *= -1;
	else if(CurPos.y <= GetFirstY() - 30.f)
		m_Speed *= -1;

	CurPos.y += DELTA_TIME * m_Speed;

	SetPos(CurPos);
	SetPosOtherside();
	return true;
}

void cMonster_Flying::Render(HDC _hdc)
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