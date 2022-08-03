#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI ��������		0	=> ���� ����
// PI/2 => �Ʒ�����			-PI/2 => �� ����
// PI/4 => �����Ʒ��밢��		-PI/4 => ������ �밢��

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
	if (m_TimeLimit >= 3.f) // 3�ʰ� ������ �����, ������Ʈ�� �浹 �ÿ��� ������Բ� �ؾ��� ����
		return false;
	Vec2 Pos = GetPos();

	if (!isOnPlatform())
	{
		Pos.x += -600.f * m_Dir.x * DELTA_TIME * GetDirection(); // �ٶ󺸴� ���⿡ �°Բ�

		Pos.y += 600.f * m_Dir.y * DELTA_TIME;

		if (m_Dir.y <= 2) // ������ �׸��Բ� ������ ������ ���� ��� ���������ֱ�.
			m_Dir.y += 8.f * DELTA_TIME;
		if (m_Dir.x > 0) // ��ź ���⵵ ��������
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
	if (m_TimeLimit >= 1.5f) // ��ȯ���� 1.5�ʰ� ������ �����̱�
	{
		xStart = xStart>0 ? 0 : m_BombImg->GetWidth() / 2;
		yStart = m_BombImg->GetHeight() / 2;
	}

	int w = m_BombImg->GetWidth()/ 2, h = m_BombImg->GetHeight()/ 2;

	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}
