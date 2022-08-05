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

	float Map_Max_x = (float)(cCore::GetInstance()->GetResolution().x);
	float Map_Max_y = (float)(cCore::GetInstance()->GetResolution().y);

	if (m_LifeCount < 0)
		return false;

	// 공격 시 뒤로 밀려나게끔
	if (m_AfterAttackTime > 0.f)
	{
		float Back = 100.f;
		if (m_isJumping)
			Back = 200.f;
		if (GetDirection() == 1)
		{
			int Back_Left = (int)(curPos_x_l - Back * DELTA_TIME);
			if (Back_Left < 0 || Back_Left >= Map_Max_x || curPos_y >= Map_Max_y
				|| g_PossibleArea[Back_Left][(int)curPos_y])
				Pos.x -= Back * DELTA_TIME;
		}
		else
		{
			int Back_Right = (int)(curPos_x_r + Back * DELTA_TIME);
			if (Back_Right < 0 || Back_Right >= Map_Max_x || curPos_y >= Map_Max_y
				|| g_PossibleArea[Back_Right][(int)curPos_y])
				Pos.x += Back * DELTA_TIME;
		}

		m_AfterAttackTime -= DELTA_TIME;
	}
	
	int Next_Down = (int)(curPos_y + m_Dir.y * DELTA_TIME);

	// 캐릭터의 일부가 맵을 벗어났을 때
	if (curPos_x_l < 0 || curPos_x_r >= (int)(Map_Max_x)
		|| Next_Down >= Map_Max_y)
	{
		if (curPos_x_l < 0) // 캐릭터의 좌측 좌표가 맵을 벗어났을 때
		{			
			if(curPos_x_r < 0) // 캐릭터의 우측 좌표도 맵을 벗어났으면 그냥 떨어짐
				Pos.y += m_Dir.y * DELTA_TIME;
			else if (Next_Down < Map_Max_y) // 우측 좌표는 맵 안, 캐릭터의 다음 하단 좌표가 맵 안에 있을 때
			{
				if (g_PossibleArea[(int)curPos_x_r][Next_Down]) // 캐릭터 다음 하단 좌표가 플랫폼이 아닐 때
					Pos.y += m_Dir.y * DELTA_TIME;
				else // 플랫폼이면 착지 멈추고 감소 속도 복구
				{
					m_isJumping = false;
					m_Dir.y = 450.f;
				}
			}
		}
		if (curPos_x_r >= (int)(Map_Max_x)) // 캐릭터의 우측 좌표가 맵을 벗어났을 때
		{
			if (curPos_x_l >= (int)(Map_Max_x)) // 캐릭터의 좌측 좌표도 맵을 벗어났으면 그냥 떨어짐
				Pos.y += m_Dir.y * DELTA_TIME;
			else if (Next_Down < Map_Max_y) // 우측 좌표는 맵 안, 캐릭터의 다음 하단 좌표가 맵 안에 있을 때
			{
				if (g_PossibleArea[(int)curPos_x_l][Next_Down])  // 캐릭터 다음 하단 좌표가 플랫폼이 아닐 때
					Pos.y += m_Dir.y * DELTA_TIME;
				else // 플랫폼이면 착지 멈추고 감소 속도 복구
				{ 
					m_isJumping = false;
					m_Dir.y = 450.f;
				}
			}
		}
		if (m_Dir.y < 800.f) // 감소속도가 일정 수준 되기 전 까지는 꾸준히 증가
		{
			if (m_isJumping) // 점프 중에서는 빠르게 감소
				m_Dir.y += 1200.f * DELTA_TIME;
			else // 그냥 낙하 중인 경우는 천천히 감소
				m_Dir.y += 250.f * DELTA_TIME;
		}
	}
	// 캐릭터 전체가 맵 안에 있을 때
	else
	{
		if (g_PossibleArea[(int)curPos_x_l][Next_Down]
			&& g_PossibleArea[(int)curPos_x_r][Next_Down])
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
		if (GetDirection() == -1) // 방향에 따른 이동
		{
			if ((int)(curPos_x_l - 400.f * DELTA_TIME) < 0)
				Pos.x -= 400.f * DELTA_TIME;
			else if(g_PossibleArea[(int)(curPos_x_l - 400.f * DELTA_TIME)][(int)curPos_y])
				Pos.x -= 400.f * DELTA_TIME;
		}
		else
		{
			if ((int)(curPos_x_r + 400.f * DELTA_TIME) >= Map_Max_x)
				Pos.x += 400.f * DELTA_TIME;
			else if (g_PossibleArea[(int)(curPos_x_r + 400.f * DELTA_TIME)][(int)curPos_y])
				Pos.x += 400.f * DELTA_TIME;
		}

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

		if (KEY_CHECK(KEY::K, KEY_STATE::DOWN)) // 아래를 짚음.
		{
			if (!m_isJumping
				&& (KEY_CHECK(KEY::J, KEY_STATE::NONE) || KEY_CHECK(KEY::J, KEY_STATE::UP))
				&& (KEY_CHECK(KEY::L, KEY_STATE::NONE) || KEY_CHECK(KEY::L, KEY_STATE::UP)))
				Rotate_Platform();
		}
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

		// ================================================================================================================== 좌측 이동
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
			else if (g_PossibleArea[Left_Check][(int)curPos_y])
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
			else if (g_PossibleArea[Left_Check][(int)curPos_y])
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

		// ======================================================================================================================= 우측 이동
		if (KEY_CHECK(KEY::L, KEY_STATE::DOWN) && (KEY_CHECK(KEY::J, KEY_STATE::UP) || KEY_CHECK(KEY::J, KEY_STATE::NONE)) 
			&& m_AfterAttackTime <= 0.f)
		{
			int Right_Check = (int)(curPos_x_r + 250.f * DELTA_TIME);
			if (Right_Check >= (int)Map_Max_x)
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
			if (Right_Check >= (int)Map_Max_x)
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

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();

	int w = (int)Scale.x;
	int h = (int)Scale.y;

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

	if (GetRotating())
	{
		Vec2 Rotator_Pos = GetRotator();
		Vec2 Player_Pos = GetPos();
		int decrease = 0;
		if (Rotator_Pos.x < Temp_Pos.x)
			decrease = 10;
		else
			decrease = -10;

		// Rotator의 위치값에 따라 회전 방향 다르게끔 구현해야함
		Gdiplus::Matrix mat;
		static int rot = 0;

		mat.RotateAt(Gdiplus::REAL(rot % 360), Gdiplus::PointF(Rotator_Pos.x, Rotator_Pos.y)); // 중점을 기준으로 회전

		graphics.SetTransform(&mat);

		rot += decrease;
		if (rot == 180 || rot == -180)
		{
			SetRotating(false);
			rot = 0;
		}
	}
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

bool cPlayer::Rotate_Platform()
{
	Vec2 curPos = GetPos();
	float Player_Y_Down = curPos.y + GetScale().y / 2.f;
	float Player_Y_Up = curPos.y - GetScale().y / 2.f;

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	int PLATFORM_ROTATE = (INT)GROUP_TYPE::PLATFORM_ROTATE;

	for (int i = 0; i < curScene->GetCurObjectVec()[PLATFORM_ROTATE].size(); ++i)
	{
		Vec2 Platform_Pos = curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->GetPos();
		Vec2 Platform_Scale = curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->GetScale();		

		float Left_End = Platform_Pos.x - Platform_Scale.x / 2.f;
		float Right_End = Platform_Pos.x + Platform_Scale.x / 2.f;
		float Top_End = Platform_Pos.y - Platform_Scale.y / 2.f;
		float Bottom_End = Platform_Pos.y + Platform_Scale.y / 2.f;

		// 플레이어의 현 위치 중심 값이 플랫폼의 좌우끝 안에 있을 때
		if (curPos.x >= Left_End && curPos.x <= Right_End
			&& ((!m_isJumping && Top_End <= Player_Y_Down + m_Dir.y * DELTA_TIME)
			|| (m_isJumping && Bottom_End >= Player_Y_Up + m_Dir.y * DELTA_TIME)))
		{
			curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->SetRotating(true);
			curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->SetRotator(curPos);
			return true;
		}
	}
	return false;
}
