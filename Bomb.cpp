#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI 좌측직선		0	=> 우측 직선
// PI/2 => 아래직선			-PI/2 => 위 직선
// PI/4 => 우측아래대각선		-PI/4 => 우측위 대각선

cBomb::cBomb() : m_BombImg(nullptr), m_TimeLimit(0.0), m_ExplosionRange(0.0), m_BounceCount(0),
				m_DirChanged(false), m_RotateToUp(false), m_isShoot(false), m_ShootSpeed(600.f)
{
	m_curGroupType = (INT)GROUP_TYPE::BOMB;
	SetDir(Vec2(-0.8f, -3.f));
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
	if (m_TimeLimit >= 3.f) // 3초가 지나면 사라짐, 오브젝트와 충돌 시에도 사라지게끔 해야할 듯함
		return false;

	Vec2 Pos = GetPos();	

	// 공중에 있을 때, 또는 회전플랫폼을 뚫고 내려가야 할 때
	if (!isOnPlatform() || GetThruRotate())
	{
		Pos.y += 600.f * m_Dir.y * DELTA_TIME;
		if (m_Dir.y <= 2)
		{
			// 포물선 그리게끔 일정값 이하일 때는 계속 증가시켜주기.
			if (!m_isShoot)
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

	// 플랫폼에 어디에 놓여있느냐에 따라 다르게 해야할 듯.
	// 회전 중이라면
	
	else if (GetRotating() && !m_isShoot && GetBounceCount() < 3)
	{
		float diff = Pos.x - GetRotator()->GetPos().x;

		// 플랫폼의 중심보다 우측에 있을 때
		if (diff > 0)
		{
			//방향이 위로 날아가야할 때
			if (m_RotateToUp)
			{
				SetDirection(-1);
				SetDir(Vec2(-diff, -0.7f));		
				m_ShootSpeed += diff*4.f - 200.f;
				//m_Dir.x -= diff / 97.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				m_isShoot = true;
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
			if (m_RotateToUp)
			{
				SetDirection(1);
				SetDir(Vec2(diff, -0.7f));
				m_ShootSpeed += diff * -4.f - 200.f;
				//m_Dir.x += diff/97.f;
				m_Dir.y = -1.2f;
				SetOnPlatform(false);
				m_isShoot = true;
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
	CollisionCheck(this);

	SetPosOtherside();
	return true;
}

void cBomb::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale();

	static int xStart = 0;
	int yStart = 0;
	if (m_TimeLimit >= 1.5f) // 소환한지 1.5초가 넘으면 깜빡이기
	{
		xStart = xStart>0 ? 0 : m_BombImg->GetWidth() / 2;
		yStart = m_BombImg->GetHeight() / 2;
	}

	int w = m_BombImg->GetWidth()/ 2, h = m_BombImg->GetHeight()/ 2;

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());

}
