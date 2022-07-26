#include "Monster_Flying.h"

cMonster_Flying::cMonster_Flying() : m_FlyingTime(0), m_curFrame(0)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster/Monster_Flying.png");
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 3.f, (float)m_MonsterImg->GetHeight()));
	SetHP(1);
	SetImgAttr();
	SetDirection(1);
}

cMonster_Flying::cMonster_Flying(int _Direction) : m_FlyingTime(0), m_curFrame(0)
{
	m_MonsterImg = Image::FromFile((WCHAR*)L"Image/Monster/Monster_Flying.png");
	SetScale(Vec2((float)m_MonsterImg->GetWidth() / 3.f, (float)m_MonsterImg->GetHeight()));
	SetHP(1);
	SetImgAttr();
	SetDirection(_Direction);
	if(_Direction == -1)
		m_MonsterImg->RotateFlip(RotateNoneFlipX);
}

cMonster_Flying::~cMonster_Flying()
{
	int _Score = cSceneManager::GetInstance()->GetScore() + 500;
	cSceneManager::GetInstance()->SetScore(_Score);
	if (m_MonsterImg != NULL)
	{
		delete m_MonsterImg;
		m_MonsterImg = nullptr;
	}
}

bool cMonster_Flying::Update()
{
	if (GetHP() <= 0)
		return false;
	Vec2 CurPos = GetPos();
	m_FlyingTime += DELTA_TIME;
	if (m_FlyingTime >= 0.9f)
	{
		m_Speed *= -1;
		m_FlyingTime = 0;
	}
	else if (m_FlyingTime >= 0.45f && m_Speed > 0)
	{
		m_Speed *= -1;
	}

	CurPos.y += DELTA_TIME * m_Speed;

	SetPos(CurPos);
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
	SetPosOtherside();
	return true;
}

void cMonster_Flying::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	int w = m_MonsterImg->GetWidth() / 3;
	int h = m_MonsterImg->GetHeight();

	int xStart = m_curFrame * w;
	m_curFrame = m_curFrame >= 2 ? 0 : m_curFrame + 1;

	int yStart = 0;

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_MonsterImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}