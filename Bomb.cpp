#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
#include "Player.h"
#include "Scene.h"
// PI == -PI 좌측직선		0	=> 우측 직선
// PI/2 => 아래직선			-PI/2 => 위 직선
// PI/4 => 우측아래대각선		-PI/4 => 우측위 대각선

cBomb::cBomb() : m_BombImg(nullptr), m_TimeLimit(0.0), m_ExplosionRange(0.0), m_BounceCount(0), m_isExploded(false),
				m_DirChanged(false), m_ShootSpeed(600.f), m_ExplosionTime(0)
{
	m_curGroupType = (INT)GROUP_TYPE::BOMB;
	SetDir(Vec2(-0.8f, -3.f));
	dwID = 2;
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
	if (isDead())
	{
		if (cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER].size() != 0)
		{
			cPlayer* curPlayer = dynamic_cast<cPlayer*>(cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(INT)GROUP_TYPE::PLAYER][0]);
			curPlayer->ResetAttackTime();
		}

		return false;
	}

	else if (!m_isExploded) // 폭발하지 않았을 때
	{
		// 곧 폭발할 때
		if (m_TimeLimit >= 3.f)
			SetExplode();
		else
		{
			Vec2 Pos = GetPos();

			// 공중에 있을 때, 또는 회전플랫폼을 뚫고 내려가야 할 때
			if (!isOnPlatform() || GetThruRotate())
			{
				Pos.y += 600.f * m_Dir.y * DELTA_TIME;
				if (m_Dir.y <= 2)
				{
					// 포물선 그리게끔 일정값 이하일 때는 계속 증가시켜주기.
					if (!GetShoot())
						m_Dir.y += 8.f * DELTA_TIME;
					else
						m_Dir.y += 6.f * DELTA_TIME;
				}
				if (GetDirection() == 1) // 우측 방향일때
					Pos.x += (float)(-m_ShootSpeed * m_Dir.x * DELTA_TIME); // 바라보는 방향에 맞게끔
					//Pos.x += -600.f * m_Dir.x * DELTA_TIME; // 바라보는 방향에 맞게끔
				else // 좌측 방향일 때
					Pos.x += (float)(m_ShootSpeed * m_Dir.x * DELTA_TIME); // 바라보는 방향에 맞게끔					
					//Pos.x += 600.f * m_Dir.x * DELTA_TIME; // 바라보는 방향에 맞게끔		
			}

			// 회전 중이라면
			else if (GetRotating() && !GetShoot() && GetBounceCount() < 3)
			{
				float diff = Pos.x - GetRotator()->GetPos().x;

				// 플랫폼의 중심보다 우측에 있을 때
				if (diff > 0)
				{
					//방향이 위로 날아가야할 때
					if (GetRotateDir())
					{
						SetDirection(-1);
						SetDir(Vec2(-diff, -0.7f));
						m_ShootSpeed += diff * 4.f - 200.f;
						//m_Dir.x -= diff / 97.f;
						m_Dir.y = -1.2f;
						SetOnPlatform(false);
						SetShoot(true);
					}
					//방향이 아래로 떨어져야 할 때
					else
					{
						SetOnPlatform(false);
						SetThruRotate(true);
						SetDir(Vec2(0.f, 2.f));
					}
				}
				// 플랫폼의 중심보다 좌측에 있을 때
				else
				{
					//방향이 위로 날아가야할 때
					if (GetRotateDir())
					{
						SetDirection(1);
						SetDir(Vec2(diff, -0.7f));
						m_ShootSpeed += diff * -4.f - 200.f;
						//m_Dir.x += diff/97.f;
						m_Dir.y = -1.2f;
						SetOnPlatform(false);
						SetShoot(true);
					}
					//방향이 아래로 떨어져야 할 때
					else
					{
						SetOnPlatform(false);
						SetThruRotate(true);
						SetDir(Vec2(0.f, 2.f));
					}
				}
				SetRotating(false);
			}

			SetPos(Pos);
			CollisionCheck(this, (INT)GROUP_TYPE::PLATFORM);			
			if(GetShoot())
				CollisionCheck(this, (INT)GROUP_TYPE::MONSTER);

			SetPosOtherside();
		}		
	}
	// 폭발했을 때
	else
	{
		CollisionCheck(this, (INT)GROUP_TYPE::MONSTER);
		CollisionCheck(this, (INT)GROUP_TYPE::PLAYER);
	}

	
	return true;
}

void cBomb::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	static int xStart = 0;
	int yStart = 0, w = 0, h = 0;
	if (m_isExploded)
	{
		xStart = 0;
		w = m_BombImg->GetWidth();
		h = m_BombImg->GetHeight() / 11;
		yStart = h * (m_ExplosionTime++/2);
		if(m_ExplosionTime > 21)
			Dead();
	}
	else
	{
		w = m_BombImg->GetWidth() / 2;
		h = m_BombImg->GetHeight() / 2;
		if (m_TimeLimit >= 1.5f) // 소환한지 1.5초가 넘으면 깜빡이기
		{
			xStart = xStart > 0 ? 0 : m_BombImg->GetWidth() / 2;
			yStart = h;
		}
	}
		
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());

}

void cBomb::SetExplode()
{
	BGM_SetAndPlay(L"Sound/EFFECT/Explosion.wav");
	//PlaySound(TEXT("Sound/EFFECT/Explosion.wav"), NULL, SND_ASYNC);
	m_isExploded = true;
	if (m_BombImg != NULL)
		delete m_BombImg;
	m_BombImg = Image::FromFile((WCHAR*)L"Image/Explosion.png");
	SetScale(Vec2((float)m_BombImg->GetWidth(), (float)m_BombImg->GetHeight() / 11.f));
}
