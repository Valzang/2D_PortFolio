#include "SpitFire.h"

cSpitFire::cSpitFire() : m_FireImg(nullptr)
{
	m_FireImg = Image::FromFile((WCHAR*)L"Image/SpitFire.png");
	SetScale(Vec2((float)m_FireImg->GetWidth() / 2.f, (float)m_FireImg->GetHeight()));
	BGM_SetAndPlay(L"Sound/EFFECT/SpitFire.wav");
	dwID = 2;
	m_curGroupType = (INT)GROUP_TYPE::SPITFIRE;

	SetImgAttr();
}

cSpitFire::cSpitFire(Vec2 _Pos, int _Direction) : m_FireImg(nullptr)
{
	m_FireImg = Image::FromFile((WCHAR*)L"Image/SpitFire.png");	
	SetScale(Vec2((float)m_FireImg->GetWidth() / 2.f, (float)m_FireImg->GetHeight()));
	SetPos(_Pos);
	SetDirection(_Direction);
	if(GetDirection()==-1)
		m_FireImg->RotateFlip(RotateNoneFlipX);
	m_curGroupType = (INT)GROUP_TYPE::SPITFIRE;
	dwID = 2;
	BGM_SetAndPlay(L"Sound/EFFECT/SpitFire.wav");

	SetImgAttr();
}

cSpitFire::~cSpitFire()
{
	if (m_FireImg != NULL)
	{
		delete m_FireImg;
		m_FireImg = nullptr;
	}
}

bool cSpitFire::Update()
{
	if (isDead())
		return false;
	Vec2 curPos = GetPos();
	curPos.x += 600.f * DELTA_TIME * GetDirection();
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
	SetPos(curPos);
	SetPosOtherside();

	return true;
}

void cSpitFire::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	static bool curFrame = false;
	int xStart = curFrame ? (int)Scale.x : 0;
	curFrame = !curFrame;

	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_FireImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, (int)Scale.x, (int)Scale.y), xStart, 0, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
}
