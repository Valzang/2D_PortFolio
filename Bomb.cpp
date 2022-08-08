#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI 좌측직선		0	=> 우측 직선
// PI/2 => 아래직선			-PI/2 => 위 직선
// PI/4 => 우측아래대각선		-PI/4 => 우측위 대각선

cBomb::cBomb() : m_BombImg(nullptr), m_TimeLimit(0.0), m_ExplosionRange(0.0), m_DirChanged(false), m_RotateToUp(false)
{
	m_curGroupType = (INT)GROUP_TYPE::BOMB;
	m_Dir = Vec2(-0.8f, -3.f);
	m_Dir.Normalize();
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
	Vec2 Scl = GetScale();

	int temp_dir = GetDirection();

	float curPos_x_l = Pos.x - Scl.x / 2;	// 폭탄의 좌측 좌표
	float curPos_x_r = Pos.x + Scl.x / 2;	// 폭탄의 우측 좌표
	float curPos_y = Pos.y + Scl.y / 2;		// 폭탄의 최하단 좌표

	float Map_Max_x = (float)(cCore::GetInstance()->GetResolution().x);
	float Map_Max_y = (float)(cCore::GetInstance()->GetResolution().y);
	

	// 공중에 있을 때
	if (!isOnPlatform())
	{
		Pos.y += 600.f * m_Dir.y * DELTA_TIME;
		curPos_y += 600.f * m_Dir.y * DELTA_TIME;
		int Next_Down = (int)(curPos_y + 600.f * m_Dir.y * DELTA_TIME);

		if (m_Dir.y <= 2) // 포물선 그리게끔 일정값 이하일 때는 계속 증가시켜주기.
			m_Dir.y += 8.f * DELTA_TIME;

		if (temp_dir == 1) // 우측 방향일때
		{
			// 하단 좌표가 맵 안에 있을 때
			if (Next_Down < Map_Max_y)
			{
				Pos.x += -600.f * m_Dir.x * DELTA_TIME; // 바라보는 방향에 맞게끔
				curPos_x_r += -600.f * m_Dir.x * DELTA_TIME;
				int Next_Left = (int)(curPos_x_l - 600.f * m_Dir.x * DELTA_TIME);
				int Next_Right = (int)(curPos_x_r - 600.f * m_Dir.x * DELTA_TIME);
				// 다음 우측 위치가 완전 맵 안에 있을 때
				if (Next_Right >= 0 && Next_Right < Map_Max_x)
				{
					// 다음 좌측 위치가 완전 맵 안에 있을 때
					if (Next_Left >= 0 && Next_Left < Map_Max_x)
					{
						if (g_PossibleArea[Next_Right][Next_Down] != 1)
						{
							if (g_PossibleArea[Next_Left][Next_Down] == 1)
							{
								SetDirection(-1);
								m_Dir.x /= 2.f;
								m_DirChanged = true;
							}
							else
							{
								SetOnPlatform(true);
								m_Dir.y = 0;
							}
						}
						else if (!m_DirChanged && g_PossibleArea[Next_Left][Next_Down] != 1)
						{
							SetOnPlatform(true);
							m_Dir.y = 0;
						}
					}
					// 다음 우측 위치가 완전 맵 밖에 있을 때
					else if (g_PossibleArea[Next_Right][Next_Down] != 1)
						SetOnPlatform(true);
				}
				// 다음 우측 위치가 완전 맵 밖에 있을 때
				else if (Next_Left >= 0 && Next_Left < Map_Max_x
						 && g_PossibleArea[Next_Left][Next_Down] != 1)
				{
					SetOnPlatform(true);
					m_Dir.y = 0;
				}
			}			
		}
		else // 좌측 방향일 때
		{
			// 하단 좌표가 맵 안에 있을 때
			if (Next_Down < Map_Max_y)
			{				
				Pos.x += 600.f * m_Dir.x * DELTA_TIME; // 바라보는 방향에 맞게끔
				curPos_x_l += 600.f * m_Dir.x * DELTA_TIME;
				int Next_Left = (int)(curPos_x_l + 600.f * m_Dir.x * DELTA_TIME);
				int Next_Right = (int)(curPos_x_r + 600.f * m_Dir.x * DELTA_TIME);
				// 다음 좌측 위치가 완전 맵 안에 있을 때
				if (Next_Left >= 0 && Next_Left < Map_Max_x)
				{
					// 다음 우측 위치가 완전 맵 안에 있을 때
					if (Next_Right >= 0 && Next_Right < Map_Max_x)
					{
						if (g_PossibleArea[Next_Left][Next_Down] != 1)
						{
							if (g_PossibleArea[Next_Right][Next_Down] == 1)
							{
								SetDirection(1);
								m_Dir.x /= 2.f;
								m_DirChanged = true;
							}
							else
							{
								SetOnPlatform(true);
								m_Dir.y = 0;
							}
						}
						else if (!m_DirChanged && g_PossibleArea[Next_Right][Next_Down] != 1)
						{
							SetOnPlatform(true);
							m_Dir.y = 0;
						}
					}
					// 다음 우측 위치가 완전 맵 밖에 있을 때
					else if (g_PossibleArea[Next_Left][Next_Down] != 1)
					{
						SetOnPlatform(true);
						m_Dir.y = 0;
					}
				}
				// 다음 좌측 위치가 완전 맵 밖에 있을 때
				else if(Next_Right >= 0 && Next_Right < Map_Max_x
					   && g_PossibleArea[Next_Right][Next_Down] != 1 )
				{
					SetOnPlatform(true);
					m_Dir.y = 0;
				}
			}
		}
	}

	// 플랫폼에 어디에 놓여있느냐에 따라 다르게 해야할 듯.
	// 회전 중이라면
	if (GetRotating())
	{
		if (m_RotateToUp)
		{

		}
		else
		{
			SetOnPlatform(false);
			Pos.y += 600.f * m_Dir.y * DELTA_TIME;
		}
	}

	if (m_Dir.x > 0) // 폭탄의 속도도 점점 0으로 향하도록
		m_Dir.x -= 0.3f * DELTA_TIME;
	else if (m_Dir.x < 0)
		m_Dir.x += 0.3f * DELTA_TIME;

	SetPos(Pos);
	SetPosOtherside();
	return true;
}

void cBomb::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Pos = GetPos();
	Vec2 Scale = GetScale()/2;

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
