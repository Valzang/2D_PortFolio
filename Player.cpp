#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"

#include "Bomb.h"

#include "SceneManager.h"
#include "Scene.h"

cPlayer::cPlayer() : m_PlayerImg(nullptr), m_isMoved(false), m_AtkCoolTime(3.f)
{
	m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player_Move.png");
	SetScale(Vec2((float)m_PlayerImg->GetWidth() / 3.f, (float)m_PlayerImg->GetHeight()/4.f));

	SetImgAttr();
	SetDirection(1);
}

cPlayer::~cPlayer()
{
	if (m_PlayerImg != NULL)
		delete m_PlayerImg;
}

void cPlayer::Update()
{
	Vec2 Pos = GetPos();

	// DELTA_TIME으로 시간동기화 해서 이동

	if (KEY_CHECK(KEY::I, KEY_STATE::HOLD))
	{
		Pos.y -= 200.f * DELTA_TIME;
	}
	if (KEY_CHECK(KEY::K, KEY_STATE::HOLD))
	{
		Pos.y += 200.f * DELTA_TIME;
	}

	// ============================================= 좌측 이동
	if (KEY_CHECK(KEY::J, KEY_STATE::DOWN))
	{		
		m_isMoved = true;
		SetDirection(-1);
	}
	if (KEY_CHECK(KEY::J, KEY_STATE::HOLD))
	{
		m_isMoved = true;
		Pos.x -= 200.f * DELTA_TIME;
		SetDirection(-1);
	}
	if (KEY_CHECK(KEY::J, KEY_STATE::UP))
	{
		m_isMoved = false;
	}

	// ============================================= 우측 이동
	if (KEY_CHECK(KEY::L, KEY_STATE::DOWN))
	{
		m_isMoved = true;
		SetDirection(1);
	}
	if (KEY_CHECK(KEY::L, KEY_STATE::HOLD))
	{
		m_isMoved = true;
		Pos.x += 200.f * DELTA_TIME;
		SetDirection(1);
	}
	if (KEY_CHECK(KEY::L, KEY_STATE::UP))
	{
		m_isMoved = false;
	}
	

	if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
	{
		if (m_AtkCoolTime >= 1.5f)
		{
			m_AtkCoolTime = 0.f;
			CreateBomb();
		}
	}
	if (KEY_CHECK(KEY::A, KEY_STATE::NONE) || KEY_CHECK(KEY::A, KEY_STATE::UP))
	{
		m_AtkCoolTime += DELTA_TIME;
	}
	SetPos(Pos);
}

void cPlayer::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = (int)GetScale().x;
	int h = (int)GetScale().y;

	int xStart = 0, yStart = 0;
	if (m_isMoved)
	{
		// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
		static int temp = 1;
		curFrame = temp / 4;
		temp = temp >= 11 ? 1 : temp + 1;

	}
	else
		curFrame = 0;

	xStart = curFrame * w;
	
	if (GetDirection() == -1)
		yStart = (int)(m_PlayerImg->GetHeight() / 2.f);

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_PlayerImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}

void cPlayer::CreateBomb()
{
	Vec2 bomb_Pos = GetPos();
	bomb_Pos.y -= GetScale().y / 2.f;

	// 폭탄 오브젝트
	cBomb* bomb = new cBomb;
	bomb->SetPos(bomb_Pos);

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(bomb, GROUP_TYPE::BOMB);
}
