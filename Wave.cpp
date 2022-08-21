#include "Wave.h"

cWave::cWave() : m_WaveImg(nullptr), m_FirstY(0.f)
{
	m_WaveImg = Image::FromFile((WCHAR*)L"Image/Boss_Wave.png");
	Init();	
	BGM_SetAndPlay(L"Sound/EFFECT/Water.wav");
	dwID = 2;
	m_curGroupType = (INT)GROUP_TYPE::WAVE;

	SetImgAttr();
}

cWave::cWave(Vec2 _Pos, int _Direction, cMonster_Boss* _Boss) : m_WaveImg(nullptr), m_FirstY(0.f)
{
	m_WaveImg = Image::FromFile((WCHAR*)L"Image/Boss_Wave.png");
	m_Boss = _Boss;
	Init();
	SetPos(_Pos);
	m_FirstY = _Pos.y;
	SetDirection(_Direction);
	if (GetDirection() == -1)
		m_WaveImg->RotateFlip(RotateNoneFlipX);
	m_curGroupType = (INT)GROUP_TYPE::WAVE;
	dwID = 2;
	BGM_SetAndPlay(L"Sound/EFFECT/Water.wav");

	SetImgAttr();
}

cWave::~cWave()
{
	m_Boss->m_isAttacking = false;
	if (m_WaveImg != NULL)
	{
		delete m_WaveImg;
		m_WaveImg = nullptr;
	}
}

void cWave::Init()
{
	m_ImgScale[0] = Vec2(115, 138);
	m_ImgScale[1] = Vec2(117, 140);
	m_ImgScale[2] = Vec2(111, 136);
	m_ImgScale[3] = Vec2(109, 138);
	m_ImgScale[4] = Vec2(123, 120);
	m_ImgScale[5] = Vec2(145, 110);
	m_ImgScale[6] = Vec2(149, 100);
	m_ImgScale[7] = Vec2(159, 88);
	m_ImgScale[8] = Vec2(181, 66);
	m_ImgScale[9] = Vec2(193, 68);
	m_ImgScale[10] = Vec2(207, 72);
	m_ImgScale[11] = Vec2(205, 60);
	m_ImgScale[12] = Vec2(169, 36);
	
}

bool cWave::Update()
{
	if (isDead())
		return false;
	Vec2 curPos = GetPos();
	curPos.x += 320.f * DELTA_TIME * GetDirection();
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	//CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
	CollisionCheck(this, (INT)GROUP_TYPE::BOMB);
	SetPos(curPos);
	SetPosOtherside();

	return true;
}

void cWave::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = m_ImgScale[curFrame/4];
	
	static int yStart = 0;
	if (curFrame % 4 == 0)
	{		
		Vec2 changePos;
		changePos.x = Pos.x;
		changePos.y = m_FirstY + (138.f - Scale.y)/2.f;
		SetPos(changePos);
	}
	

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_WaveImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, (int)Scale.x, (int)Scale.y), 0, yStart, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
	SetScale(Scale);

	if (curFrame >= 51)
	{
		curFrame = 0;
		yStart = 0;
		Dead();
	}
	else
	{
		++curFrame;
		if (curFrame % 4 == 0)
			yStart += (int)m_ImgScale[curFrame / 4 - 1].y;
	}
}
