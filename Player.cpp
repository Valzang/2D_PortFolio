#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"

#include "Bomb.h"

#include "SceneManager.h"
#include "Scene.h"

cPlayer::cPlayer() : m_PlayerImg(nullptr), m_isMoved(false), m_isSitted(false), m_isDashing(false), m_isJumping(false)
					, m_AtkCoolTime(3.f), m_DashCoolTime(2.f), m_JumpingTime(0.f), m_DashTime(0.f), m_LifeCount(3)
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

bool cPlayer::Update()
{
	if (m_LifeCount < 0)
		return false;

	Vec2 Pos = GetPos();
	//if (OnPlatform() == false) // �÷��� ���� ���ٸ� �߷�
		//Pos.y += 500.f * DELTA_TIME; 

	// DELTA_TIME���� �ð�����ȭ �ؼ� �̵�

	if (m_isDashing) // �뽬 ���̶��
	{
		if (GetDirection() == -1) // ���⿡ ���� �̵�
			Pos.x -= 400.f * DELTA_TIME;
		else
			Pos.x += 400.f * DELTA_TIME;

		if (m_DashTime >= 0.5) // 0.5�� �̻� ������� �� �ʱ�ȭ
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
		if (KEY_CHECK(KEY::I, KEY_STATE::HOLD)) // ������ ���� �����̴� �� �ƴ�, ȸ�� �÷����� ���� �� �������� ȸ����Ű�� �뵵�θ� ����.
		{
			Pos.y -= 200.f * DELTA_TIME;
		}
		if (KEY_CHECK(KEY::K, KEY_STATE::HOLD)) // �Ʒ��� ¤��.
		{
			m_isSitted = true;
			if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && m_DashCoolTime > 0.55 && !m_isJumping) // ���⼭ �뽬�ϸ鼭 �̵��� ������ �ؾ���.
			{
				m_isMoved = false;
				m_isDashing = true;
				m_DashCoolTime = 0;
				m_DashTime = 0;
			}
		}
		if (KEY_CHECK(KEY::K, KEY_STATE::UP) || KEY_CHECK(KEY::K, KEY_STATE::NONE))
		{
			if (!m_isDashing)
				m_isSitted = false;
		}

		if (KEY_CHECK(KEY::S, KEY_STATE::DOWN) && !m_isJumping)
		{
			m_isJumping = true;
		}

		if (m_isJumping) // ���� ���̸� => ����� godown�̶�� ������ ���߿����� y�� ��ȭ�� �ٿ��־�����, �÷����� ������ ���Ŀ��� JumpingTime�� �ʿ� �������� �ȴ�.
		{
			static float godown = 500.f;
			Pos.y -= godown * DELTA_TIME;
			m_JumpingTime += DELTA_TIME;
			godown -= 15.45f;
			if (m_JumpingTime >= 1)
			{
				m_isJumping = false;
				m_JumpingTime = 0;
				godown = 500.f;
			}
		}

		// ============================================= ���� �̵�
		if (KEY_CHECK(KEY::J, KEY_STATE::DOWN))
		{
			m_isMoved = true;
			SetDirection(-1);
		}
		if (KEY_CHECK(KEY::J, KEY_STATE::HOLD))
		{
			m_isMoved = true;
			Pos.x -= 250.f * DELTA_TIME;
			SetDirection(-1);
		}
		if (KEY_CHECK(KEY::J, KEY_STATE::UP))
		{
			m_isMoved = false;
		}

		// ============================================= ���� �̵�
		if (KEY_CHECK(KEY::L, KEY_STATE::DOWN))
		{
			m_isMoved = true;
			SetDirection(1);
		}
		if (KEY_CHECK(KEY::L, KEY_STATE::HOLD))
		{
			m_isMoved = true;
			Pos.x += 250.f * DELTA_TIME;
			SetDirection(1);
		}
		if (KEY_CHECK(KEY::L, KEY_STATE::UP))
		{
			m_isMoved = false;
		}

		// ============================================= ��ź ��ġ
		if (KEY_CHECK(KEY::A, KEY_STATE::DOWN))
		{
			if (m_AtkCoolTime >= 1.5f)
			{
				m_AtkCoolTime = 0.f;
				CreateBomb();
			}
		}
		m_AtkCoolTime += DELTA_TIME;
		m_DashCoolTime += DELTA_TIME;
	}

	
	SetPos(Pos);
	SetPosOtherside();

	return true;
}

void cPlayer::Render(HDC _hdc)
{
	static int curFrame = 0;
	Graphics graphics(_hdc);

	int w = (int)GetScale().x;
	int h = (int)GetScale().y;

	int xStart = 0, yStart = 0;
	if (m_isMoved) // �����̰� �ִٸ�
	{
		// �ӵ��� ���߷������� ���� ���� ����. ���Ŀ� �õ��غ���.
		static int temp = 1;
		curFrame = temp / 4;
		temp = temp >= 11 ? 1 : temp + 1;

	}
	else if (m_isSitted)
	{
		// �ɾ��ִٸ�
		yStart = (int)(m_PlayerImg->GetHeight() / 4.f);
		if (m_isDashing)
			curFrame = 1;
		else
			curFrame = 0;
	}
	else
		curFrame = 0;

	xStart = curFrame * w;
	
	if (GetDirection() == -1) // �ݴ������ �ٶ󺼶�
		yStart += (int)(m_PlayerImg->GetHeight() / 2.f);

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_PlayerImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, w, h), xStart, yStart, w, h, UnitPixel, GetImgAttr());
}

void cPlayer::CreateBomb()
{
	Vec2 bomb_Pos = GetPos();
	if (GetDirection() == 1)
		bomb_Pos.x += GetScale().x / 2.f;

	// ��ź ������Ʈ
	cBomb* bomb = new cBomb;
	if (m_isMoved) // �����̸鼭 ��ź�� ������ ��
	{
		Vec2 temp = bomb->GetDir();
		temp.x *= 1.8;
		bomb->SetDir(temp);
	}
	bomb->SetPos(bomb_Pos);
	bomb->SetDirection(GetDirection());

	cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
	curScene->AddObject(bomb, GROUP_TYPE::BOMB);
}
