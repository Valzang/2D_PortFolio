#include "Wave.h"

cWave::cWave() : m_WaveImg(nullptr)
{
	m_WaveImg = Image::FromFile((WCHAR*)L"Image/Boss_Wave.png");
	Init();	
	BGM_SetAndPlay(L"Sound/EFFECT/SpitFire.wav");
	dwID = 2;
	m_curGroupType = (INT)GROUP_TYPE::SPITFIRE;

	SetImgAttr();
}

cWave::cWave(Vec2 _Pos, int _Direction, cMonster_Boss* _Boss) : m_WaveImg(nullptr)
{
	m_WaveImg = Image::FromFile((WCHAR*)L"Image/Boss_Wave.png");
	m_Boss = _Boss;
	Init();
	SetPos(_Pos);
	SetDirection(_Direction);
	if (GetDirection() == -1)
		m_WaveImg->RotateFlip(RotateNoneFlipX);
	m_curGroupType = (INT)GROUP_TYPE::SPITFIRE;
	dwID = 2;
	BGM_SetAndPlay(L"Sound/EFFECT/SpitFire.wav");

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
	ImgScale[0] = Vec2(115, 138);
	ImgScale[1] = Vec2(117, 140);
	ImgScale[2] = Vec2(111, 136);
	ImgScale[3] = Vec2(109, 138);
	ImgScale[4] = Vec2(123, 120);
	ImgScale[5] = Vec2(145, 110);
	ImgScale[6] = Vec2(149, 100);
	ImgScale[7] = Vec2(159, 88);
	ImgScale[8] = Vec2(181, 66);
	ImgScale[9] = Vec2(193, 68);
	ImgScale[10] = Vec2(207, 72);
	ImgScale[11] = Vec2(205, 60);
	ImgScale[12] = Vec2(169, 36);
	
}

bool cWave::Update()
{
	if (isDead())
		return false;
	Vec2 curPos = GetPos();
	curPos.x += 500.f * DELTA_TIME * GetDirection();
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
	CollisionCheck(this, (INT)GROUP_TYPE::BOMB);
	SetPos(curPos);
	SetPosOtherside();

	return true;
}

void cWave::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	cout << "현재 소환 중인 웨이브 " << curFrame / 2 << "의 (x,y) : (" << ImgScale[curFrame / 2].x << "," << ImgScale[curFrame / 2].y << ") // yStart = ";
	Vec2 Pos = GetPos();
	Vec2 Scale = ImgScale[curFrame/2];

	static int yStart = 0;
	//yStart = Scale.y != yStart ? yStart + Scale.y : yStart;
	//yStart += Scale.y;
	cout << yStart << '\n';
	

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_WaveImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, (int)Scale.x, (int)Scale.y), 0, yStart, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
	SetScale(Scale);

	if (curFrame >= 26)
	{
		curFrame = 0;
		yStart = 0;
		Dead();
	}
	else
		++curFrame;

	yStart = yStart == Scale.y ? yStart - Scale.y : Scale.y;
}
