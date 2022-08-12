#include "Bomb.h"
#include "TimeManager.h"
#include "Core.h"
// PI == -PI ��������		0	=> ���� ����
// PI/2 => �Ʒ�����			-PI/2 => �� ����
// PI/4 => �����Ʒ��밢��		-PI/4 => ������ �밢��

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
	if (m_TimeLimit >= 3.f) // 3�ʰ� ������ �����, ������Ʈ�� �浹 �ÿ��� ������Բ� �ؾ��� ����
		return false;

	Vec2 Pos = GetPos();	

	// ���߿� ���� ��, �Ǵ� ȸ���÷����� �հ� �������� �� ��
	if (!isOnPlatform() || GetThruRotate())
	{
		Pos.y += 600.f * m_Dir.y * DELTA_TIME;
		if (m_Dir.y <= 2)
		{
			// ������ �׸��Բ� ������ ������ ���� ��� ���������ֱ�.
			if (!m_isShoot)
				m_Dir.y += 8.f * DELTA_TIME;
			else
				m_Dir.y += 6.f * DELTA_TIME;
		}
		if (GetDirection() == 1) // ���� �����϶�
			Pos.x += (float)(-m_ShootSpeed * m_Dir.x * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�
			//Pos.x += -600.f * m_Dir.x * DELTA_TIME; // �ٶ󺸴� ���⿡ �°Բ�
		else // ���� ������ ��
			Pos.x += (float)(m_ShootSpeed * m_Dir.x * DELTA_TIME); // �ٶ󺸴� ���⿡ �°Բ�					
			//Pos.x += 600.f * m_Dir.x * DELTA_TIME; // �ٶ󺸴� ���⿡ �°Բ�		
	}

	// �÷����� ��� �����ִ��Ŀ� ���� �ٸ��� �ؾ��� ��.
	// ȸ�� ���̶��
	
	else if (GetRotating() && !m_isShoot && GetBounceCount() < 3)
	{
		float diff = Pos.x - GetRotator()->GetPos().x;

		// �÷����� �߽ɺ��� ������ ���� ��
		if (diff > 0)
		{
			//������ ���� ���ư����� ��
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
			//������ �Ʒ��� �������� �� ��
			else
			{
				SetOnPlatform(false);
				SetThruRotate(true);
				SetDir(Vec2(0.f, 2.f));
			}
		}
		// �÷����� �߽ɺ��� ������ ���� ��
		else
		{			
			//������ ���� ���ư����� ��
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
			//������ �Ʒ��� �������� �� ��
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
	if (m_TimeLimit >= 1.5f) // ��ȯ���� 1.5�ʰ� ������ �����̱�
	{
		xStart = xStart>0 ? 0 : m_BombImg->GetWidth() / 2;
		yStart = m_BombImg->GetHeight() / 2;
	}

	int w = m_BombImg->GetWidth()/ 2, h = m_BombImg->GetHeight()/ 2;

	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_BombImg, Rect((int)Pos.x - (int)Scale.x / 2, (int)Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());

}
