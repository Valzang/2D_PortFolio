#include "Platform.h"
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"
#include "Monster.h"
#include "Object.h"

cPlatform::cPlatform() : m_PlatformImg(NULL), m_DecreaseDegree(0)
{
	m_curGroupType = (INT)GROUP_TYPE::PLATFORM;
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform/Platform.png");	
	SetScale(Vec2((float)m_PlatformImg->GetWidth(), (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform::~cPlatform()
{
	if (m_PlatformImg != NULL)
	{
		delete m_PlatformImg;
		m_PlatformImg = nullptr;
	}
}

bool cPlatform::Update()
{
	if (isDead())
		return false;
	// Rotating �϶�� ��ȣ�϶�
	if (GetRotating() && GetCurGroupType() == (INT)GROUP_TYPE::PLATFORM_ROTATE)
	{
		Vec2 Platform_Pos = GetPos();
		Vec2 Platform_Scale = GetScale();

		cScene* curScene = cSceneManager::GetInstance()->GetCurScene();

		// �÷��̾� ���� ==========================================================
		if (curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER].size() == 0)
			return true;
		cPlayer* curPlayer = dynamic_cast<cPlayer*>(curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER][0]);
		Vec2 curPlayer_Pos = curPlayer->GetPos();
		Vec2 curPlayer_Scale = curPlayer->GetScale();

		if ((curPlayer_Pos.x > Platform_Pos.x - Platform_Scale.x/2.f) && (curPlayer_Pos.x < Platform_Pos.x + Platform_Scale.x / 2.f)
			&& (abs(curPlayer_Pos.y - Platform_Pos.y) <= (curPlayer_Scale.y + Platform_Scale.y) / 2.f)
			&& !curPlayer->GetDashing())
		{
			curPlayer->SetRotator(this);
			curPlayer->SetRotating(true);
			curPlayer->SetUnsitted();
		}

		// ���� ���� ==========================================================

		vector<cObject*> curMonsterVec = cSceneManager::GetInstance()->GetCurScene()->GetCurObjectVec()[(UINT)GROUP_TYPE::MONSTER];
		for (int i = 0; i < curMonsterVec.size(); ++i)
		{
			if (curMonsterVec[i]->GetCurGroupType() != (INT)GROUP_TYPE::MONSTER_RUNNER)
				continue;
			cObject* curMonster		= curMonsterVec[i];
			Vec2 curMonster_Pos		= curMonster->GetPos();
			Vec2 curMonster_Scale	= curMonster->GetScale();
						
			if ((curMonster_Pos.x > Platform_Pos.x - Platform_Scale.x / 2.f) && (curMonster_Pos.x < Platform_Pos.x + Platform_Scale.x / 2.f)
				&& (abs(curMonster_Pos.y - Platform_Pos.y) <= (curMonster_Scale.y + Platform_Scale.y) / 2.f))
			{
				curMonster->SetRotator(this);
				curMonster->SetRotating(true);
				// �Ʒ�����
				if (m_DecreaseDegree > 0)
				{
					if (curMonster_Pos.x > Platform_Pos.x)
						curMonster->SetRotateDir(false);
					else
						curMonster->SetRotateDir(true);
				}
				// �� ����
				else
				{
					if (curMonster_Pos.x > Platform_Pos.x)
						curMonster->SetRotateDir(true);
					else
						curMonster->SetRotateDir(false);
				}
			}
			else
			{
				curMonster->SetRotator(NULL);
				curMonster->SetRotating(false);
			}
		}
		

		for (int i = 0; i < curScene->GetCurObjectVec()[(INT)GROUP_TYPE::BOMB].size(); ++i)
		{
			cBomb* curBomb = dynamic_cast<cBomb*>(curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::BOMB][i]);
			Vec2 curBomb_Pos = curBomb->GetPos();
			Vec2 curBomb_Scale = curBomb->GetScale();
			if ((abs(curBomb_Pos.x - Platform_Pos.x) <= (curBomb_Scale.x + Platform_Scale.x) / 2.f)
				&& (abs(curBomb_Pos.y - Platform_Pos.y) <= (curBomb_Scale.y + Platform_Scale.y) / 2.f))
			{
				curBomb->SetRotator(this);
				curBomb->SetRotating(true);

				// �Ʒ�����
				if (m_DecreaseDegree > 0)
				{
					if (curBomb_Pos.x > Platform_Pos.x)
						curBomb->SetRotateDir(false);
					else
						curBomb->SetRotateDir(true);
				}
				// �� ����
				else
				{
					if (curBomb_Pos.x > Platform_Pos.x)
						curBomb->SetRotateDir(true);
					else
						curBomb->SetRotateDir(false);
				}
				
			}
			
		}

	}

	if (GetCurGroupType() == (INT)GROUP_TYPE::PLATFORM_BROKEN)
	{
		CollisionCheck(this, (INT)GROUP_TYPE::BOMB);
	}
	return true;
}

void cPlatform::Render(HDC _hdc)
{
	Graphics graphics(_hdc);

	Vec2 Platform_Pos = GetPos();
	Vec2 Scale = GetScale();

	// Rotating �϶�� ��ȣ�϶�
	if (GetRotating())
	{
		Vec2 Rotator_Pos = GetRotator()->GetPos();		

		if (GetRotFromDown())
		{
			if (Rotator_Pos.x <= Platform_Pos.x)
				m_DecreaseDegree = 10;
			else
				m_DecreaseDegree = -10;
		}
		else
		{
			if (Rotator_Pos.x > Platform_Pos.x)
				m_DecreaseDegree = 10;
			else
				m_DecreaseDegree = -10;
		}

		// Rotator�� ��ġ���� ���� ȸ�� ���� �ٸ��Բ� �����ؾ���
		Gdiplus::Matrix mat;
		static int rot = 0;

		mat.RotateAt(Gdiplus::REAL(rot % 360), Gdiplus::PointF(Platform_Pos.x, Platform_Pos.y)); // ������ �������� ȸ��

		graphics.SetTransform(&mat);

		rot += (int)(m_DecreaseDegree * 60.f * DELTA_TIME);
		if (rot >= 180 || rot <= -180)
		{
			SetRotating(false);
			rot = 0;
		}
	}
		
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_PlatformImg, Rect((int)(Platform_Pos.x - Scale.x / 2), (int)(Platform_Pos.y - Scale.y / 2), (int)GetScale().x, (int)GetScale().y),
					   0, 0, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
}
