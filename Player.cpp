#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "Bomb.h"
#include "SceneManager.h"
#include "Scene.h"



cPlayer::cPlayer() : m_PlayerImg(nullptr), m_isMoved(false), m_isSitted(false), m_isDashing(false), m_isJumping(false), m_Spawning(true), m_isDamaging(false)
					, m_AtkCoolTime(3.f), m_DashCoolTime(2.f), m_DashTime(0.f), m_AfterAttackTime(0.f) , m_Xreverse(false), m_Clear(false)
					, m_AttachingTime(0.f), m_isAttached(false), m_Rotation_Degree(0), m_InvincibleTime(3.f), m_GameOver(false), m_OverCount(0)
{	
	m_curGroupType = (INT)GROUP_TYPE::PLAYER;
	m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_Enter.png");
	SetScale(Vec2((float)m_PlayerImg->GetWidth() / 14.f, (float)m_PlayerImg->GetHeight()));

	m_PlayerLifeImg = Image::FromFile((WCHAR*)L"Image/UI/Player_HP_count.png");
	m_PlayerLife_Scale = Vec2((float)m_PlayerLifeImg->GetWidth(), (float)m_PlayerLifeImg->GetHeight());

	m_PlayerLifeCountImg = Image::FromFile((WCHAR*)L"Image/UI/Number.png");
	m_LifeCount_Scale = Vec2((float)m_PlayerLifeCountImg->GetWidth() / 10.f, (float)m_PlayerLifeCountImg->GetHeight());

	m_PlayerLife_Pos = Vec2(m_LifeCount_Scale.x * 1.5f, m_LifeCount_Scale.y * 1.5f);
	m_LifeCount_Pos = Vec2(m_PlayerLife_Pos.x + m_PlayerLife_Scale.x / 2.f, m_PlayerLife_Pos.y + 7.f);

	SetHP(2);
	SetDir(Vec2(-2.f, 3.f));

	SetImgAttr();
	SetDirection(1);
}

cPlayer::cPlayer(Vec2 _SpawnPlace, int _Life) : m_PlayerImg(nullptr), m_isMoved(false), m_isSitted(false), m_isDashing(false), m_isJumping(false), m_Spawning(true)
									, m_AtkCoolTime(3.f), m_DashCoolTime(2.f), m_DashTime(0.f), m_AfterAttackTime(0.f), m_Xreverse(false), m_Clear(false)
									, m_AttachingTime(0.f), m_isAttached(false), m_Rotation_Degree(0), m_GameOver(false), m_OverCount(0)
{
	m_curGroupType = (INT)GROUP_TYPE::PLAYER;
	m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_Enter.png");
	SetScale(Vec2((float)m_PlayerImg->GetWidth() / 14.f, (float)m_PlayerImg->GetHeight()));

	m_PlayerLifeImg = Image::FromFile((WCHAR*)L"Image/UI/Player_HP_count.png");
	m_PlayerLife_Scale = Vec2((float)m_PlayerLifeImg->GetWidth(), (float)m_PlayerLifeImg->GetHeight());

	m_PlayerLifeCountImg = Image::FromFile((WCHAR*)L"Image/UI/Number.png");
	m_LifeCount_Scale = Vec2((float)m_PlayerLifeCountImg->GetWidth() / 10.f, (float)m_PlayerLifeCountImg->GetHeight());

	m_PlayerLife_Pos = Vec2(m_LifeCount_Scale.x * 1.5f, m_LifeCount_Scale.y * 1.5f);
	m_LifeCount_Pos = Vec2(m_PlayerLife_Pos.x + m_PlayerLife_Scale.x / 2.f, m_PlayerLife_Pos.y + 7.f);

	SetHP(_Life);
	SetDir(Vec2(-2.f, 3.f));

	SetImgAttr();
	SetDirection(1);

	SetSpawnPlace(_SpawnPlace);
	SetPos(_SpawnPlace);
}

cPlayer::~cPlayer()
{
	mciSendCommandW(dwID, MCI_CLOSE, 0, NULL);
	if (m_PlayerImg != NULL)
	{
		delete m_PlayerImg;
		m_PlayerImg = nullptr;
	}
	if (m_PlayerLifeImg != NULL)
	{
		delete m_PlayerLifeImg;
		m_PlayerLifeImg = nullptr;
	}
	if (m_PlayerLifeCountImg != NULL)
	{
		delete m_PlayerLifeCountImg;
		m_PlayerLifeCountImg = nullptr;
	}
}

bool cPlayer::Update()
{
	Vec2 Pos = GetPos();
	Vec2 Scl = GetScale();
	if (cSceneManager::GetInstance()->GetCurScene()->GetMonsterSize() == 0 && !m_Clear)
	{
		m_Clear = true;
		m_Dir.y *= -1;
		SetOnPlatform(false);
		delete m_PlayerImg;
		m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_Clear.png");
		SetScale(Vec2((float)m_PlayerImg->GetWidth() / 12.f, (float)m_PlayerImg->GetHeight()));		
		Pos.y -= 21.f;

		cSceneManager::GetInstance()->GetCurScene()->BGM_Stop();

		MCI_OPEN_PARMS mciOpen2;
		MCI_PLAY_PARMS mciPlay2;
		int dwID2 = 0;

		mciOpen2.lpstrDeviceType = L"WaveAudio";
		mciOpen2.lpstrElementName = L"Sound/EFFECT/Cool.wav"; // 파일 경로 입력

		mciSendCommandW(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&mciOpen2);
		dwID2 = mciOpen2.wDeviceID;		

		// play
		mciSendCommandW(dwID2, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&mciPlay2);
	}
		
	
	float curPos_x_l = Pos.x - Scl.x / 2;
	float curPos_x_r = Pos.x + Scl.x / 2;
	float curPos_y = Pos.y + Scl.y / 2;	

	if (m_Spawning)
		return true;

	if (m_GameOver && (KEY_CHECK(KEY::A, KEY_STATE::DOWN)))
		return false;

	if (m_Clear)
	{		
		if (!isOnPlatform())
		{
			Pos.y += m_Dir.y * DELTA_TIME;
			if (m_Dir.y < 800.f) // 감소속도가 일정 수준 되기 전 까지는 꾸준히 증가
				m_Dir.y += 1200.f * DELTA_TIME;
		
		}
		SetPos(Pos);
		CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
		return true;
	}
	

	// 남아 있는 목숨이 없을 때
	if (GetHP() < 0)
	{
		if (isDead())
			return true;
		else
		{
			m_Spawning = true;
			m_GameOver = true;
			return true;
		}
	}

	// 데미지를 받았을 때
	if (m_isDamaging)
	{			
		static float Screen_Bottom = (float)cCore::GetInstance()->GetResolution().y;
		SetOnPlatform(false);
		Pos.y += m_Dir.y * DELTA_TIME;
		if (m_Dir.y < 800.f) // 감소속도가 일정 수준 되기 전 까지는 꾸준히 증가
			m_Dir.y += 250.f * DELTA_TIME;
		if (Pos.y - Scl.y / 2.f >= Screen_Bottom)
		{
			m_isDamaging = false;
			Respawn();
		}
		else
			SetPos(Pos);
		return true;
	}

	// 공격 시 뒤로 밀려나게끔
	if (m_AfterAttackTime > 0.f)
	{
		float Back = 100.f;
		if (m_isJumping)
			Back = 200.f;
		if (GetDirection() == 1)
		{
			int Back_Left = (int)(curPos_x_l - Back * DELTA_TIME);
			Pos.x -= Back * DELTA_TIME;
		}
		else
		{
			int Back_Right = (int)(curPos_x_r + Back * DELTA_TIME);
			Pos.x += Back * DELTA_TIME;
		}

		m_AfterAttackTime -= DELTA_TIME;
	}
	// 안 붙어있다면
	if (!m_isAttached)
	{
		// 현재 바닥에 안 닿아있을 때
		if (!isOnPlatform())
		{
			Pos.y += m_Dir.y * DELTA_TIME;
			if (m_Dir.y < 800.f) // 감소속도가 일정 수준 되기 전 까지는 꾸준히 증가
			{
				if (m_isJumping) // 점프 중에서는 빠르게 감소
					m_Dir.y += 1200.f * DELTA_TIME;
				else // 그냥 낙하 중인 경우는 천천히 감소
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
			Pos.x -= 400.f * DELTA_TIME;
		else
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
		if ((KEY_CHECK(KEY::I, KEY_STATE::DOWN) || KEY_CHECK(KEY::I, KEY_STATE::HOLD)) 
			&& !(KEY_CHECK(KEY::K, KEY_STATE::HOLD)) && !m_isDamaging) // 실제로 위로 움직이는 게 아닌, 회전 플랫폼에 있을 때 위쪽으로 회전시키는 용도로만 쓰임.
		{
			if (m_isAttached && !GetRotating()
				&& (KEY_CHECK(KEY::J, KEY_STATE::NONE) || KEY_CHECK(KEY::J, KEY_STATE::UP))
				&& (KEY_CHECK(KEY::L, KEY_STATE::NONE) || KEY_CHECK(KEY::L, KEY_STATE::UP)))
			{
				SetRotFromDown(true);
				if(Rotate_Platform())
					m_AttachingTime = 0.f;
			}
		}
		if ((KEY_CHECK(KEY::K, KEY_STATE::DOWN) || KEY_CHECK(KEY::K, KEY_STATE::HOLD)) && !GetRotating() && !m_isDamaging) // 아래를 짚음.
		{
			if (!m_isAttached)
				m_isSitted = true;
			if (!m_isJumping && !m_isAttached
				&& (KEY_CHECK(KEY::J, KEY_STATE::NONE) || KEY_CHECK(KEY::J, KEY_STATE::UP))
				&& (KEY_CHECK(KEY::L, KEY_STATE::NONE) || KEY_CHECK(KEY::L, KEY_STATE::UP)))
			{
				SetRotFromDown(false);
				Rotate_Platform();
			}
			if (m_isAttached && KEY_CHECK(KEY::K, KEY_STATE::DOWN))
			{
				m_isAttached = false;
				m_AttachingTime = 0.f;
				SetOnPlatform(false);
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

		if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && !m_isJumping && !m_isSitted && !m_isDashing && !GetRotating() && !m_isDamaging)
		{
			if (m_isAttached)
			{
				m_isAttached = false;
				m_AttachingTime = 0.f;
			}
			else if (isOnPlatform())
			{
				m_isJumping = true;
				m_Dir.y *= -1;
			}
			SetOnPlatform(false);
		}

		// ================================================================================================================== 좌측 이동
		if ((KEY_CHECK(KEY::J, KEY_STATE::DOWN) || KEY_CHECK(KEY::J, KEY_STATE::HOLD)) && (KEY_CHECK(KEY::L, KEY_STATE::UP) || KEY_CHECK(KEY::L, KEY_STATE::NONE))
			&& m_AfterAttackTime <= 0.f && !GetRotating())
		{
			int Left_Check = (int)(curPos_x_l - 250.f * DELTA_TIME);
			if(GetDirection() == 1)
				m_PlayerImg->RotateFlip(RotateNoneFlipX);
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

		// ======================================================================================================================= 우측 이동
		if ((KEY_CHECK(KEY::L, KEY_STATE::DOWN) || KEY_CHECK(KEY::L, KEY_STATE::HOLD)) && (KEY_CHECK(KEY::J, KEY_STATE::UP) || KEY_CHECK(KEY::J, KEY_STATE::NONE))
			&& m_AfterAttackTime <= 0.f && !GetRotating())
		{
			if (!m_isDashing)
				m_isMoved = true;
			Pos.x += 250.f * DELTA_TIME;
			if( GetDirection() == -1)
				m_PlayerImg->RotateFlip(RotateNoneFlipX);
			SetDirection(1);

		}
		if (KEY_CHECK(KEY::L, KEY_STATE::UP))
		{
			m_isMoved = false;
		}

		// ============================================= 폭탄 설치
		if (KEY_CHECK(KEY::A, KEY_STATE::DOWN) && !GetRotating())
		{
			if (m_AtkCoolTime >= 3.2f)
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
		m_isJumping = false;
		m_Dir.y = 450.f;
		if (m_AttachingTime >= 1.1f)
		{
			m_isAttached = false;
			m_AttachingTime = 0.f;
			SetOnPlatform(false);
		}
		else
			m_AttachingTime += DELTA_TIME;
	}

	SetPos(Pos); 
	if (GetRotating())
	{
		if (m_Rotation_Degree >= 180 || m_Rotation_Degree <= -180)
		{
			// 플레이어의 위치를 회전 플랫폼 중점을 기준으로 점 대칭 이동
			Vec2 Platform_Pos = GetRotator()->GetPos();
			Vec2 Player_Pos = GetPos();
			Player_Pos.x -= ((Player_Pos.x - Platform_Pos.x) * 2);
			Player_Pos.y -= ((Player_Pos.y - Platform_Pos.y) * 2);
			SetRotating(false);
			m_Rotation_Degree = 0;
			SetPos(Player_Pos);
			// 더 돌아서 공중에 떠있는거 방지용
			SetOnPlatform(false);
			m_isAttached = Player_Pos.y > Platform_Pos.y ? true : false;
		}
	}
	CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);
	CollisionCheck(this, (INT)GROUP_TYPE::MONSTER);


	SetPosOtherside(); // 반대쪽으로 넘어갔으면 다른 쪽으로 나오게끔
	m_InvincibleTime = (m_InvincibleTime > 0.f) ? m_InvincibleTime - DELTA_TIME : 0.f;	
	

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

	if (m_Clear)
	{
		static int Clear_count = 0;
		static bool NotOver = false;
		static double BGM_Time = 0.f;
		xStart = Width * (Clear_count / 5);

		if (NotOver)
			BGM_Time += DELTA_TIME;

		if (Clear_count < 59)
		{
			if (Clear_count == 6)
			{
				cSceneManager::GetInstance()->GetCurScene()->BGM_Clear();
				NotOver = true;
			}
			++Clear_count;
		}

		if (BGM_Time > 3.5f)
		{
			BGM_Time = 0.f;
			NotOver = false;
			Clear_count = 0;
			cSceneManager::GetInstance()->GetCurScene()->SetMonsterSize(-1);
		}

		graphics.DrawImage(m_PlayerImg, Rect((int)Player_Pos.x - Width / 2, (int)Player_Pos.y - Height / 2, Width, Height), xStart, yStart, Width, Height, UnitPixel, GetImgAttr());
	}

	else if (!m_Spawning && !m_GameOver)
	{
		static int Img_Jump_Cursor = 1;
		static int Img_Move_Cursor = 1;

		static int Blink = 0;

		if (m_isJumping || m_isDamaging)
		{
			// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
			if ((m_InvincibleTime > 0.f && Blink<2) || m_InvincibleTime <= 0.f)
			{
				yStart += (int)(m_PlayerImg->GetHeight() / 3.f);
				if (m_InvincibleTime > 0.f)
					++Blink;
				
			}				
			else
			{
				yStart += (int)(m_PlayerImg->GetHeight() / 6.f * 5.f);
				if (Blink++ == 3)
					Blink = 0;
			}
			curFrame = Img_Jump_Cursor / 10;
			Img_Jump_Cursor = Img_Jump_Cursor >= 59 ? 1 : Img_Jump_Cursor + 1;
		}
		// 움직이고 있다면
		else if (m_isMoved) 
		{
			// 속도를 늦추려했으나 쉽게 되진 않음. 추후에 시도해볼것.
			if (m_InvincibleTime > 0.f)
			{
				if (Blink < 2)
					++Blink;
				else
				{
					yStart += (int)(m_PlayerImg->GetHeight() / 2.f);
					if (Blink++ == 3)
						Blink = 0;
				}
			}
			curFrame = Img_Move_Cursor / 4;
			Img_Move_Cursor = Img_Move_Cursor >= 11 ? 1 : Img_Move_Cursor + 1;

		}
		// 앉아있다면
		else if (m_isSitted)
		{
			if ((m_InvincibleTime > 0.f && Blink < 2) || m_InvincibleTime <= 0.f)
			{
				yStart += (int)(m_PlayerImg->GetHeight() / 6.f);
				if(m_InvincibleTime > 0.f)
					++Blink;				
			}
			else
			{
				yStart += (int)(m_PlayerImg->GetHeight() / 3.f * 2.f);
				if (Blink++ == 3)
					Blink = 0;
			}
			curFrame = m_isDashing ? 1 : 0;
		}
		// 가만히 있을 때
		else
		{
			if (m_InvincibleTime > 0.f)
			{
				if (Blink < 2)
					++Blink;
				else
				{
					yStart += (int)(m_PlayerImg->GetHeight() / 2.f);
					if (Blink++ == 3)
						Blink = 0;
				}
			}
			curFrame = 0;
			Img_Jump_Cursor = 1;
			Img_Move_Cursor = 1;
		}

		xStart = curFrame * Width;
		Gdiplus::Matrix mat;

		if (GetRotating())
		{
			Vec2 Rotator_Pos = GetRotator()->GetPos();

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

			m_Rotation_Degree += (int)(decrease * 60.f * DELTA_TIME);
		}

		if (m_isAttached)
		{
			mat.RotateAt(Gdiplus::REAL(180 % 360), Gdiplus::PointF(Player_Pos.x, Player_Pos.y)); // 플레이어 중점을 기준으로 회전
			graphics.SetTransform(&mat);

			if (!m_Xreverse)
			{
				m_PlayerImg->RotateFlip(RotateNoneFlipX);
				m_Xreverse = true;
			}
			
			// 위아래가 뒤집혀서 반대방향이 되었으므로 방향 변화해줌
		}		
		else if(m_Xreverse)
		{
			m_PlayerImg->RotateFlip(RotateNoneFlipX);
			m_Xreverse = false;
		}
		//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
		graphics.DrawImage(m_PlayerImg, Rect((int)Player_Pos.x - Width / 2, (int)Player_Pos.y - Height / 2, Width, Height), xStart, yStart, Width, Height, UnitPixel, GetImgAttr());
	}
	else if (m_GameOver)
	{
		if (m_OverCount == 0)
		{
			delete m_PlayerImg;
			m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_GameOver.png");
			SetScale(Vec2((float)m_PlayerImg->GetWidth() / 15.f, (float)m_PlayerImg->GetHeight()));
			SetPos(Vec2(640, 349));
			Width = (int)GetScale().x;
			Height = (int)GetScale().y;
		}
		xStart = Width * (m_OverCount / 3);
		if (m_OverCount >= 44)
		{
			m_Spawning = false;
			Dead();
		}
		else
			++m_OverCount;
		//											
		graphics.DrawImage(m_PlayerImg, Rect((int)Player_Pos.x - Width / 2, (int)Player_Pos.y - Height / 2, Width, Height), xStart, yStart, Width, Height, UnitPixel, GetImgAttr());
	}
	else
	{
		static int Enter_count = 0;
		xStart = Width * (Enter_count/2);
		// 진입 애니메이션이 끝나면 플레이어블 애니메이션으로 변경
		if (Enter_count >= 26)
		{
			Enter_count = 0;
			m_Spawning = false;
			m_InvincibleTime = 3.f;

			delete m_PlayerImg;
			m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_Move.png");
			SetScale(Vec2((float)m_PlayerImg->GetWidth() / 6.f, (float)m_PlayerImg->GetHeight() / 6.f));

			if(m_isAttached)
			{
				m_isAttached = false; 
				m_PlayerImg->RotateFlip(RotateNoneFlipX);
			}
		}	
		else
			++Enter_count;		
		//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
		graphics.DrawImage(m_PlayerImg, Rect((int)Player_Pos.x - Width / 2, (int)Player_Pos.y - Height / 2, Width, Height), xStart, yStart, Width, Height, UnitPixel, GetImgAttr());
	}	
	UI_Render(_hdc);
	
}

void cPlayer::CreateBomb()
{
	Vec2 bomb_Pos = GetPos();
	if (GetDirection() == 1)
		bomb_Pos.x += GetScale().x / 2.5f;
	else
		bomb_Pos.x -= GetScale().x / 2.5f;
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

	vector<cObject*> curRotate = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLATFORM];// _ROTATE];

	for (int i = 0; i < curRotate.size(); ++i)
	{
		if (curRotate[i]->GetCurGroupType() != (INT)GROUP_TYPE::PLATFORM_ROTATE)
			continue;
		Vec2 Platform_Pos = curRotate[i]->GetPos();
		Vec2 Platform_Scale = curRotate[i]->GetScale();

		float Left_End = Platform_Pos.x - Platform_Scale.x / 2.f;
		float Right_End = Platform_Pos.x + Platform_Scale.x / 2.f;
		float Top_End = Platform_Pos.y - Platform_Scale.y / 2.f;
		float Bottom_End = Platform_Pos.y + Platform_Scale.y / 2.f;

		// 플레이어의 좌우 끝 값이 플랫폼의 안에 있을 때
		if (curPos_Right-15.f > Left_End && curPos_Left+15.f < Right_End
			&& ((!m_isJumping && Top_End <= curPos_Down + m_Dir.y * DELTA_TIME && Top_End > curPos.y)
				|| ((m_isAttached && Bottom_End >= curPos_Up) && Bottom_End < curPos.y)
			|| ((m_isJumping && Bottom_End >= curPos_Up + m_Dir.y * DELTA_TIME) && Bottom_End < curPos.y)))
		{
			curRotate[i]->SetRotating(true);
			curRotate[i]->SetRotator(this);
			curRotate[i]->SetRotFromDown(GetRotFromDown());
			return true;
		}
	}
	return false;
}

void cPlayer::Damage()
{
	if (!m_Spawning && !m_isDamaging && m_InvincibleTime == 0.f)
	{
		SetHP(GetHP() - 1);
		BGM_SetAndPlay(L"Sound/EFFECT/Player_Damaged.wav");
		m_isDamaging = true;
		m_Dir.y = 450.f;
		SetOnPlatform(false);
	}	
}

void cPlayer::UI_Render(HDC _hdc)
{
	Graphics graphics_Life(_hdc);
	Graphics graphics_LifeCount(_hdc);

	int Life_w = (int)m_PlayerLife_Scale.x;
	int Life_h = (int)m_PlayerLife_Scale.y;

	Vec2 LifeCount_Pos = m_LifeCount_Pos;
	Vec2 LifeCount_Scale = m_LifeCount_Scale;

	int LifeCount_w = (int)m_LifeCount_Scale.x;
	int LifeCount_h = (int)m_LifeCount_Scale.y;

	int Life_xStart = LifeCount_w * GetHP();

	graphics_Life.DrawImage(m_PlayerLifeImg,
							Rect((int)m_PlayerLife_Pos.x - Life_w / 2, (int)m_PlayerLife_Pos.y - Life_h / 2, Life_w, Life_h),
							0, 0, Life_w, Life_h, UnitPixel, GetImgAttr());
	graphics_LifeCount.DrawImage(m_PlayerLifeCountImg,
								 Rect((int)m_LifeCount_Pos.x - LifeCount_w / 2, (int)m_LifeCount_Pos.y - LifeCount_h / 2, LifeCount_w, LifeCount_h),
								 Life_xStart, 0, LifeCount_w, LifeCount_h, UnitPixel, GetImgAttr());
}

void cPlayer::Respawn()
{
	if(m_PlayerImg != NULL)
		delete m_PlayerImg;
	SetPos(m_SpawnPlace);
	m_PlayerImg = Image::FromFile((WCHAR*)L"Image/Player/Player_Enter.png");
	SetScale(Vec2((float)m_PlayerImg->GetWidth() / 14.f, (float)m_PlayerImg->GetHeight()));
	m_Spawning = true;	
	m_isMoved = false;
	m_isSitted = false;
	m_isDashing = false;
	m_isJumping = false;
	m_InvincibleTime = 3.f;
	SetDir(Vec2(-2.f, 3.f));
	int _Score = cSceneManager::GetInstance()->GetScore() - 1200;
	if (_Score < 0)
		_Score = 0;
	cSceneManager::GetInstance()->SetScore(_Score);
	SetDirection(1);
}
