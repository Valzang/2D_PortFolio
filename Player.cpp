#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"

#include "Bomb.h"

#include "SceneManager.h"
#include "Scene.h"



cPlayer::cPlayer() : m_PlayerImg(nullptr), m_isMoved(false), m_isSitted(false), m_isDashing(false), m_isJumping(false)
					, m_AtkCoolTime(3.f), m_DashCoolTime(2.f), m_DashTime(0.f), m_LifeCount(3), m_AfterAttackTime(0.f)
					, m_AttachingTime(0.f), m_isAttached(false), m_Rotation_Degree(0)
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

	int Next_Down = (int)(curPos_y + m_Dir.y * DELTA_TIME);

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
				|| g_PossibleArea[Back_Left][(int)curPos_y]==1)
				Pos.x -= Back * DELTA_TIME;
		}
		else
		{
			int Back_Right = (int)(curPos_x_r + Back * DELTA_TIME);
			if (Back_Right < 0 || Back_Right >= Map_Max_x || curPos_y >= Map_Max_y
				|| g_PossibleArea[Back_Right][(int)curPos_y]==1)
				Pos.x += Back * DELTA_TIME;
		}

		m_AfterAttackTime -= DELTA_TIME;
	}
	

	// 캐릭터의 일부가 맵을 벗어났을 때
	if (curPos_x_l < 0 || curPos_x_r >= (int)(Map_Max_x)
		|| Next_Down >= Map_Max_y || Next_Down < 0)
	{
		if (curPos_x_l < 0) // 캐릭터의 좌측 좌표가 맵을 벗어났을 때
		{			
			if(curPos_x_r < 0 && !m_isAttached) // 캐릭터의 우측 좌표도 맵을 벗어났으면 그냥 떨어짐
				Pos.y += m_Dir.y * DELTA_TIME;
			else if (Next_Down < Map_Max_y) // 우측 좌표는 맵 안, 캐릭터의 다음 하단 좌표가 맵 안에 있을 때
			{
				if (g_PossibleArea[(int)curPos_x_r][Next_Down]==1 && !m_isAttached) // 캐릭터 다음 하단 좌표가 플랫폼이 아닐 때
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
			if (curPos_x_l >= (int)(Map_Max_x) && !m_isAttached) // 캐릭터의 좌측 좌표도 맵을 벗어났으면 그냥 떨어짐
				Pos.y += m_Dir.y * DELTA_TIME;
			else if (Next_Down < Map_Max_y) // 우측 좌표는 맵 안, 캐릭터의 다음 하단 좌표가 맵 안에 있을 때
			{
				if (g_PossibleArea[(int)curPos_x_l][Next_Down]==1 && !m_isAttached)  // 캐릭터 다음 하단 좌표가 플랫폼이 아닐 때
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
		if (g_PossibleArea[(int)curPos_x_l][Next_Down]==1 && g_PossibleArea[(int)curPos_x_r][Next_Down]==1
			&& !m_isAttached)
		{
			Pos.y += m_Dir.y * DELTA_TIME;
			// 점프
			if (m_isJumping ) // 문제 : 현재 회전문이 아니더라도 천장에 붙는 현상이 있음
			{
				float Check_Up = Pos.y - Scl.y / 2 + m_Dir.y * DELTA_TIME;
				if (Check_Up >= 0 && g_PossibleArea[(int)Pos.x][(int)Check_Up] == 2)
				{
					//SetPos(Pos);
					m_isAttached = true;
					SetRotFromDown(true);
					Rotate_Platform();
					m_isJumping = false;
					m_Dir.y = 450.f;
				}
			}
			
			
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
			else if(g_PossibleArea[(int)(curPos_x_l - 400.f * DELTA_TIME)][(int)curPos_y]==1)
				Pos.x -= 400.f * DELTA_TIME;
		}
		else
		{
			if ((int)(curPos_x_r + 400.f * DELTA_TIME) >= Map_Max_x)
				Pos.x += 400.f * DELTA_TIME;
			else if (g_PossibleArea[(int)(curPos_x_r + 400.f * DELTA_TIME)][(int)curPos_y]==1)
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
		if (KEY_CHECK(KEY::I, KEY_STATE::DOWN) || KEY_CHECK(KEY::I, KEY_STATE::HOLD)) // 실제로 위로 움직이는 게 아닌, 회전 플랫폼에 있을 때 위쪽으로 회전시키는 용도로만 쓰임.
		{
			if (m_isAttached && !GetRotating()
				&& (KEY_CHECK(KEY::J, KEY_STATE::NONE) || KEY_CHECK(KEY::J, KEY_STATE::UP))
				&& (KEY_CHECK(KEY::L, KEY_STATE::NONE) || KEY_CHECK(KEY::L, KEY_STATE::UP)))
			{
				SetRotFromDown(true);
				Rotate_Platform();
				m_AttachingTime = 0.f;
			}
		}
		if (KEY_CHECK(KEY::K, KEY_STATE::HOLD) && !GetRotating()) // 아래를 짚음.
		{
			m_isSitted = true;
			if (!m_isJumping && !m_isAttached
				&& (KEY_CHECK(KEY::J, KEY_STATE::NONE) || KEY_CHECK(KEY::J, KEY_STATE::UP))
				&& (KEY_CHECK(KEY::L, KEY_STATE::NONE) || KEY_CHECK(KEY::L, KEY_STATE::UP)))
			{
				SetRotFromDown(false);
				Rotate_Platform();
			}
			if (m_isAttached)
			{
				m_isAttached = false;
				m_AttachingTime = 0.f;
			}			
			
			if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && m_DashCoolTime > 0.55 && !m_isJumping && !m_isAttached && !GetRotating()) // 여기서 대쉬하면서 이동을 빠르게 해야함.
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

		if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && !m_isJumping && !m_isSitted && !m_isDashing && !GetRotating())//&& isOnPlatform())
		{
			if (m_isAttached)
			{
				m_isAttached = false;
				m_AttachingTime = 0.f;
			}
			else
			{
				m_isJumping = true;
				m_Dir.y *= -1;
			}
		}

		// ================================================================================================================== 좌측 이동
		if ((KEY_CHECK(KEY::J, KEY_STATE::DOWN) || KEY_CHECK(KEY::J, KEY_STATE::HOLD)) &&(KEY_CHECK(KEY::L, KEY_STATE::UP) || KEY_CHECK(KEY::L, KEY_STATE::NONE))
			&& m_AfterAttackTime <= 0.f && !GetRotating())
		{
			int Left_Check = (int)(curPos_x_l - 250.f * DELTA_TIME);
			if (Left_Check < 0)
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x -= 250.f * DELTA_TIME;
				SetDirection(-1);
			}
			else if (g_PossibleArea[Left_Check][(int)curPos_y]==1)
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
		if ((KEY_CHECK(KEY::L, KEY_STATE::DOWN) || KEY_CHECK(KEY::L, KEY_STATE::HOLD)) && (KEY_CHECK(KEY::J, KEY_STATE::UP) || KEY_CHECK(KEY::J, KEY_STATE::NONE))
			&& m_AfterAttackTime <= 0.f && !GetRotating())
		{
			int Right_Check = (int)(curPos_x_r + 250.f * DELTA_TIME);
			if (Right_Check >= (int)Map_Max_x)
			{
				if (!m_isDashing)
					m_isMoved = true;
				Pos.x += 250.f * DELTA_TIME;
				SetDirection(1);
			}
			else if (g_PossibleArea[Right_Check][(int)curPos_y]==1)
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

	if (m_isAttached)
	{
		if (m_AttachingTime >= 1) // 0.5초 이상 대시중일 시 초기화
		{
			m_isAttached = false;
			m_AttachingTime = 0.f;
		}
		else
			m_AttachingTime += DELTA_TIME;
	}

	if (m_Rotation_Degree == 180 || m_Rotation_Degree == -180)
	{
		// 플레이어의 위치를 회전 플랫폼 중점을 기준으로 점 대칭 이동
		Vec2 Platform_Pos = GetRotator();
		Pos.x -= ((Pos.x - Platform_Pos.x) * 2);
		Pos.y -= ((Pos.y - Platform_Pos.y) * 2);
		SetRotating(false);
		m_Rotation_Degree = 0;
		//SetPos(Player_Pos);
		m_isAttached = Pos.y > Platform_Pos.y ? true : false;
	}

	SetPos(Pos);
	SetPosOtherside(); // 반대쪽으로 넘어갔으면 다른 쪽으로 나오게끔

	return true;
}

void cPlayer::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	Vec2 Player_Pos = GetPos();
	Vec2 Player_Scale = GetScale();

	int Width = (int)Player_Scale.x;
	int Height = (int)Player_Scale.y;

	int xStart = 0, yStart = 0;

	static int Img_Jump_Cursor = 1;

	static int Img_Move_Cursor = 1;

	if (GetDirection() == -1)
		yStart += (int)(m_PlayerImg->GetHeight() / 2.f);

	if (m_isJumping)
	{
		// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
		yStart += (int)(m_PlayerImg->GetHeight() / 3.f);
		curFrame = Img_Jump_Cursor / 10;
		Img_Jump_Cursor = Img_Jump_Cursor >= 59 ? 1 : Img_Jump_Cursor + 1;
	}
	else if (m_isMoved) // 움직이고 있다면
	{
		// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
		curFrame = Img_Move_Cursor / 4;
		Img_Move_Cursor = Img_Move_Cursor >= 11 ? 1 : Img_Move_Cursor + 1;

	}
	else if (m_isSitted)
	{
		// 앉아있다면
		yStart += (int)(m_PlayerImg->GetHeight() / 6.f);
		curFrame = m_isDashing ? 1 : 0;
	}
	else
	{
		curFrame = 0;
		Img_Jump_Cursor = 1;
		Img_Move_Cursor = 1;
	}

	xStart = curFrame * Width;
	Gdiplus::Matrix mat;
	//static int Rotation_Degree = 0;

	if (GetRotating())
	{
		Vec2 Rotator_Pos = GetRotator();

		int decrease = 0;

		if (GetRotFromDown())
		{
			if (Rotator_Pos.x >= Player_Pos.x)
				decrease = 10;
			else
				decrease = -10;
		}
		else
		{
			if (Rotator_Pos.x < Player_Pos.x)
				decrease = 10;
			else
				decrease = -10;
		}

		// Rotator의 위치값에 따라 회전 방향 다르게끔 구현해야함

		mat.RotateAt(Gdiplus::REAL(m_Rotation_Degree % 360), Gdiplus::PointF(Rotator_Pos.x, Rotator_Pos.y)); // 플랫폼 중점을 기준으로 회전

		graphics.SetTransform(&mat);

		m_Rotation_Degree += decrease;		
	}

	if (m_isAttached)
	{
		mat.RotateAt(Gdiplus::REAL(180 % 360), Gdiplus::PointF(Player_Pos.x, Player_Pos.y)); // 플레이어 중점을 기준으로 회전
		graphics.SetTransform(&mat);

		// 위아래가 뒤집혀서 반대방향이 되었으므로 방향 변화해줌
		if (GetDirection() == -1)
			yStart -= (int)(m_PlayerImg->GetHeight() / 2.f);
		else
			yStart += (int)(m_PlayerImg->GetHeight() / 2.f);

	}
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_PlayerImg, Rect((int)Player_Pos.x - Width / 2, (int)Player_Pos.y - Height / 2, Width, Height), xStart, yStart, Width, Height, UnitPixel, GetImgAttr());
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
	Vec2 curScale = GetScale();
	float curPos_Left = curPos.x - curScale.x / 2.f;
	float curPos_Right = curPos.x + curScale.x / 2.f;

	float curPos_Down = curPos.y + curScale.y / 2.f;
	float curPos_Up = curPos.y - curScale.y / 2.f;

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

		// 플레이어의 좌우 끝 값이 플랫폼의 안에 있을 때
		if (curPos_Right-15.f > Left_End && curPos_Left+15.f < Right_End
			&& ((!m_isJumping && Top_End <= curPos_Down + m_Dir.y * DELTA_TIME && Top_End > curPos.y)
				|| m_isAttached || (m_isJumping && Bottom_End >= curPos_Up + m_Dir.y * DELTA_TIME) && Bottom_End < curPos.y)  )
		{
			curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->SetRotating(true);
			curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->SetRotator(curPos);
			curScene->GetCurObjectVec()[PLATFORM_ROTATE][i]->SetRotFromDown(GetRotFromDown());
			return true;
		}
	}
	return false;
}
