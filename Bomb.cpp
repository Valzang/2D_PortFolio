#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI ��������		0	=> ���� ����
// PI/2 => �Ʒ�����			-PI/2 => �� ����
// PI/4 => �����Ʒ��밢��		-PI/4 => ������ �밢��

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
	if (m_TimeLimit >= 3.f) // 3�ʰ� ������ �����, ������Ʈ�� �浹 �ÿ��� ������Բ� �ؾ��� ����
		return false;

	Vec2 Pos = GetPos();
	Vec2 Scl = GetScale();

	int temp_dir = GetDirection();

	float curPos_x_l = Pos.x - Scl.x / 2;	// ��ź�� ���� ��ǥ
	float curPos_x_r = Pos.x + Scl.x / 2;	// ��ź�� ���� ��ǥ
	float curPos_y = Pos.y + Scl.y / 2;		// ��ź�� ���ϴ� ��ǥ

	float Map_Max_x = (float)(cCore::GetInstance()->GetResolution().x);
	float Map_Max_y = (float)(cCore::GetInstance()->GetResolution().y);
	

	// ���߿� ���� ��
	if (!isOnPlatform())
	{
		Pos.y += 600.f * m_Dir.y * DELTA_TIME;
		curPos_y += 600.f * m_Dir.y * DELTA_TIME;
		int Next_Down = (int)(curPos_y + 600.f * m_Dir.y * DELTA_TIME);

		if (m_Dir.y <= 2) // ������ �׸��Բ� ������ ������ ���� ��� ���������ֱ�.
			m_Dir.y += 8.f * DELTA_TIME;

		if (temp_dir == 1) // ���� �����϶�
		{
			// �ϴ� ��ǥ�� �� �ȿ� ���� ��
			if (Next_Down < Map_Max_y)
			{
				Pos.x += -600.f * m_Dir.x * DELTA_TIME; // �ٶ󺸴� ���⿡ �°Բ�
				curPos_x_r += -600.f * m_Dir.x * DELTA_TIME;
				int Next_Left = (int)(curPos_x_l - 600.f * m_Dir.x * DELTA_TIME);
				int Next_Right = (int)(curPos_x_r - 600.f * m_Dir.x * DELTA_TIME);
				// ���� ���� ��ġ�� ���� �� �ȿ� ���� ��
				if (Next_Right >= 0 && Next_Right < Map_Max_x)
				{
					// ���� ���� ��ġ�� ���� �� �ȿ� ���� ��
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
					// ���� ���� ��ġ�� ���� �� �ۿ� ���� ��
					else if (g_PossibleArea[Next_Right][Next_Down] != 1)
						SetOnPlatform(true);
				}
				// ���� ���� ��ġ�� ���� �� �ۿ� ���� ��
				else if (Next_Left >= 0 && Next_Left < Map_Max_x
						 && g_PossibleArea[Next_Left][Next_Down] != 1)
				{
					SetOnPlatform(true);
					m_Dir.y = 0;
				}
			}			
		}
		else // ���� ������ ��
		{
			// �ϴ� ��ǥ�� �� �ȿ� ���� ��
			if (Next_Down < Map_Max_y)
			{				
				Pos.x += 600.f * m_Dir.x * DELTA_TIME; // �ٶ󺸴� ���⿡ �°Բ�
				curPos_x_l += 600.f * m_Dir.x * DELTA_TIME;
				int Next_Left = (int)(curPos_x_l + 600.f * m_Dir.x * DELTA_TIME);
				int Next_Right = (int)(curPos_x_r + 600.f * m_Dir.x * DELTA_TIME);
				// ���� ���� ��ġ�� ���� �� �ȿ� ���� ��
				if (Next_Left >= 0 && Next_Left < Map_Max_x)
				{
					// ���� ���� ��ġ�� ���� �� �ȿ� ���� ��
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
					// ���� ���� ��ġ�� ���� �� �ۿ� ���� ��
					else if (g_PossibleArea[Next_Left][Next_Down] != 1)
					{
						SetOnPlatform(true);
						m_Dir.y = 0;
					}
				}
				// ���� ���� ��ġ�� ���� �� �ۿ� ���� ��
				else if(Next_Right >= 0 && Next_Right < Map_Max_x
					   && g_PossibleArea[Next_Right][Next_Down] != 1 )
				{
					SetOnPlatform(true);
					m_Dir.y = 0;
				}
			}
		}
	}

	// �÷����� ��� �����ִ��Ŀ� ���� �ٸ��� �ؾ��� ��.
	// ȸ�� ���̶��
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

	if (m_Dir.x > 0) // ��ź�� �ӵ��� ���� 0���� ���ϵ���
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
	if (m_TimeLimit >= 1.5f) // ��ȯ���� 1.5�ʰ� ������ �����̱�
	{
		xStart = xStart>0 ? 0 : m_BombImg->GetWidth() / 2;
		yStart = m_BombImg->GetHeight() / 2;
	}

	int w = m_BombImg->GetWidth()/ 2, h = m_BombImg->GetHeight()/ 2;

	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}
