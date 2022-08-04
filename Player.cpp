#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"

#include "Bomb.h"

#include "SceneManager.h"
#include "Scene.h"



cPlayer::cPlayer() : m_PlayerImg(nullptr), m_isMoved(false), m_isSitted(false), m_isDashing(false), m_isJumping(false)
					, m_AtkCoolTime(3.f), m_DashCoolTime(2.f), m_DashTime(0.f), m_LifeCount(3), m_AfterAttackTime(0.f)
{	
	m_curGroupType = (INT)GROUP_TYPE::PLAYER;
	m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player_Move.png");
	SetScale(Vec2((float)m_PlayerImg->GetWidth() / 6.f, (float)m_PlayerImg->GetHeight()/6.f));

	SetDir(Vec2(-2.f, 3.f));

	SetImgAttr();
	SetDirection(1);
}

cPlayer::~cPlayer()
{
	if (m_PlayerImg != NULL)
	{
		delete m_PlayerImg;
		m_PlayerImg = nullptr;
	}
}

bool cPlayer::Update()
{
	Vec2 Pos = GetPos(); 
	Vec2 Scl = GetScale();
	float curPos_x_l = Pos.x - Scl.x / 2;
	float curPos_x_r = Pos.x + Scl.x / 2;
	float curPos_y = Pos.y + Scl.y / 2;

	if (m_LifeCount < 0)
		return false;

	// 공격 시 뒤로 밀려나게끔
	if (m_AfterAttackTime > 0.f)
	{
		float Back = 100.f;
		if (m_isJumping)
			Back = 200.f;
		if (GetDirection() == 1 && g_PossibleArea[(int)(curPos_x_l - Back * DELTA_TIME)][(int)curPos_y]) // 방향에 따른 이동
			Pos.x -= Back * DELTA_TIME;
		else if (GetDirection() == -1 && g_PossibleArea[(int)(curPos_x_r + Back * DELTA_TIME)][(int)curPos_y])
			Pos.x += Back * DELTA_TIME;

		m_AfterAttackTime -= DELTA_TIME;
	}
	

	// 플랫폼 위에 없다면 중력
	if (curPos_x_l < 0 || curPos_x_r >= (int)(cCore::GetInstance()->GetResolution().x)
		|| curPos_y + m_Dir.y * DELTA_TIME >= cCore::GetInstance()->GetResolution().y)
	{
		if(curPos_x_l < 0 && curPos_x_r < 0)
			Pos.y += m_Dir.y * DELTA_TIME;
		if (curPos_x_r >= (int)(cCore::GetInstance()->GetResolution().x)
			&& curPos_x_l >= (int)(cCore::GetInstance()->GetResolution().x))
			Pos.y += m_Dir.y * DELTA_TIME;
	}
	else
	{
		if (g_PossibleArea[(int)curPos_x_l][(int)(curPos_y + m_Dir.y * DELTA_TIME)]
			&& g_PossibleArea[(int)curPos_x_r][(int)(curPos_y + m_Dir.y * DELTA_TIME)])
		{
			Pos.y += m_Dir.y * DELTA_TIME;
			if (m_Dir.y < 800.f)
			{
				if (m_isJumping)
					m_Dir.y += 1200.f * DELTA_TIME;
				else
					m_Dir.y += 250.f * DELTA_TIME;
			}
		}
		else
		{
			m_isJumping = false;
			m_Dir.y = 450.f;
		}
	}

	
		

	// 대쉬 중이라면
	if (m_isDashing) 
	{
		if (GetDirection() == -1 && g_PossibleArea[(int)(curPos_x_l - 400.f * DELTA_TIME)][(int)curPos_y]) // 방향에 따른 이동
			Pos.x -= 400.f * DELTA_TIME;
		else if (GetDirection() == 1 && g_PossibleArea[(int)(curPos_x_r + 400.f * DELTA_TIME)][(int)curPos_y])
			Pos.x += 400.f * DELTA_TIME;

		if (m_DashTime >= 0.5) // 0.5초 이상 대시중일 시 초기화
		{
			m_isDashing = false;
			m_DashTime = 0;
			m_isJumping = false;
		}
		else
		{
			m_DashTime += DELTA_TIME;
			m_DashCoolTime += DELTA_TIME;
		}
	}
	else
	{
		//if (KEY_CHECK(KEY::I, KEY_STATE::HOLD)) // 실제로 위로 움직이는 게 아닌, 회전 플랫폼에 있을 때 위쪽으로 회전시키는 용도로만 쓰임.
		//{
		//}
		if (KEY_CHECK(KEY::K, KEY_STATE::HOLD)) // 아래를 짚음.
		{
			m_isSitted = true;
			if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && m_DashCoolTime > 0.55 && !m_isJumping) // 여기서 대쉬하면서 이동을 빠르게 해야함.
			{
				m_isMoved = false;
				m_isDashing = true;
				m_DashCoolTime = 0;
				m_DashTime = 0;
			}
		}
		if (KEY_CHECK(KEY::K, KEY_STATE::UP) || KEY_CHECK(KEY::K, KEY_STATE::NONE))
		{
			m_isSitted = false;
		}

		if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && !m_isJumping && !m_isSitted && !m_isDashing )//&& isOnPlatform())
		{
			m_isJumping = true;
			m_Dir.y *= -1;
		}

		// ============================================= 좌측 이동
		if (KEY_CHECK(KEY::J, KEY_STATE::DOWN) && (KEY_CHECK(KEY::L, KEY_STATE::UP) || KEY_CHECK(KEY::L, KEY_STATE::NONE)) 
			&& m_AfterAttackTime <= 0.f)
		{
			int Left_Check = (int)(curPos_x_l - 250.f * DELTA_TIME);
			if (Left_Check < 0)
			{
				if (!m_isDashing)
					m_isMoved = true;
				SetDirection(-1);
			}
			else
			{
				if (!m_isDashing)
					m_isMoved = true;
				SetDirection(-1);
			}
			
		}
		if (KEY_CHECK(KEY::J, KEY_STATE::HOLD) &&(KEY_CHECK(KEY::L, KEY_STATE::UP) || KEY_CHECK(KEY::L, KEY_STATE::NONE)) 
			&& m_AfterAttackTime <= 0.f)
		{
			int Left_Check = (int)(curPos_x_l - 250.f * DELTA_TIME);
			if (Left_Check < 0)
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x -= 250.f * DELTA_TIME;
				SetDirection(-1);
			}
			else
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x -= 250.f * DELTA_TIME;
				SetDirection(-1);
			}

			
		}
		if (KEY_CHECK(KEY::J, KEY_STATE::UP))
		{
			m_isMoved = false;
		}

		// ============================================= 우측 이동
		if (KEY_CHECK(KEY::L, KEY_STATE::DOWN) && (KEY_CHECK(KEY::J, KEY_STATE::UP) || KEY_CHECK(KEY::J, KEY_STATE::NONE)) 
			&& m_AfterAttackTime <= 0.f)
		{
			int Right_Check = (int)(curPos_x_r + 250.f * DELTA_TIME);
			if (Right_Check >= (int)(cCore::GetInstance()->GetResolution().x))
			{
				if (!m_isDashing)
					m_isMoved = true;
				SetDirection(1);
			}
			else if (g_PossibleArea[Right_Check][(int)curPos_y])
			{
				if (!m_isDashing)
					m_isMoved = true;
				SetDirection(1);
			}			
		}
		if (KEY_CHECK(KEY::L, KEY_STATE::HOLD) && (KEY_CHECK(KEY::J, KEY_STATE::UP) || KEY_CHECK(KEY::J, KEY_STATE::NONE)) 
			&& m_AfterAttackTime <= 0.f)
		{
			int Right_Check = (int)(curPos_x_r + 250.f * DELTA_TIME);
			if (Right_Check >= (int)(cCore::GetInstance()->GetResolution().x))
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x += 250.f * DELTA_TIME;
				SetDirection(1);
			}
			else if (g_PossibleArea[Right_Check][(int)curPos_y])
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x += 250.f * DELTA_TIME;
				SetDirection(1);
			}
			
		}
		if (KEY_CHECK(KEY::L, KEY_STATE::UP))
		{
			m_isMoved = false;
		}

		// ============================================= 폭탄 설치
		if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
		{
			if (m_AtkCoolTime >= 1.5f)
			{
				m_AtkCoolTime = 0.f;
				if (m_isJumping)
					m_AfterAttackTime = 0.3f;
				else
					m_AfterAttackTime = 0.1f;
				CreateBomb();
			}
		}
		m_AtkCoolTime += DELTA_TIME;
		m_DashCoolTime += DELTA_TIME;
	}

	SetPos(Pos);
	SetPosOtherside(); // 반대쪽으로 넘어갔으면 다른 쪽으로 나오게끔

	return true;
}

void cPlayer::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = (int)GetScale().x;
	int h = (int)GetScale().y;

	int xStart = 0, yStart = 0;

	static int temp_Jump = 1;

	static int temp_Move = 1;

	if (GetDirection() == -1)
		yStart += (int)(m_PlayerImg->GetHeight() / 2.f);

	if (m_isJumping)
	{
		// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
		yStart += (int)(m_PlayerImg->GetHeight() / 3.f);
		curFrame = temp_Jump / 10;
		temp_Jump = temp_Jump >= 59 ? 1 : temp_Jump + 1;
	}
	else if (m_isMoved) // 움직이고 있다면
	{
		// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
		curFrame = temp_Move / 4;
		temp_Move = temp_Move >= 11 ? 1 : temp_Move + 1;

	}
	else if (m_isSitted)
	{
		// 앉아있다면
		yStart += (int)(m_PlayerImg->GetHeight() / 6.f);
		if (m_isDashing)
			curFrame = 1;
		else
			curFrame = 0;
	}
	else
	{
		curFrame = 0;
		temp_Jump = 1;
		temp_Move = 1;
	}

	xStart = curFrame * w;

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_PlayerImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}

void cPlayer::CreateBomb()
{
	Vec2 bomb_Pos = GetPos();
	if (GetDirection() == 1)
		bomb_Pos.x += GetScale().x / 2.5f;
	else
		bomb_Pos.x -= GetScale().x / 1.5f;
	// 폭탄 오브젝트
	cBomb* bomb = new cBomb;
	if (m_isMoved) // 움직이면서 폭탄을 날렸을 시
	{
		Vec2 temp = bomb->GetDir();
		temp.x *= 1.8f;
		bomb->SetDir(temp);
	}
	bomb->SetPos(bomb_Pos);
	bomb->SetDirection(GetDirection());

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(bomb, GROUP_TYPE::BOMB);
}
