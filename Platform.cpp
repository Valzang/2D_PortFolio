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
	// Rotating 하라는 신호일때
	if (GetRotating() && GetCurGroupType() == (INT)GROUP_TYPE::PLATFORM_ROTATE)
	{
		Vec2 Platform_Pos = GetPos();
		Vec2 Platform_Scale = GetScale();

		cScene* curScene = cSceneManager::GetInstance()->GetCurScene();

		// 플레이어 관련 ==========================================================
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

		// 몬스터 관련 ==========================================================

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
				// 아랫방향
				if (m_DecreaseDegree > 0)
				{
					if (curMonster_Pos.x > Platform_Pos.x)
						curMonster->SetRotateDir(false);
					else
						curMonster->SetRotateDir(true);
				}
				// 윗 방향
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

				// 아랫방향
				if (m_DecreaseDegree > 0)
				{
					if (curBomb_Pos.x > Platform_Pos.x)
						curBomb->SetRotateDir(false);
					else
						curBomb->SetRotateDir(true);
				}
				// 윗 방향
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

	// Rotating 하라는 신호일때
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

		// Rotator의 위치값에 따라 회전 방향 다르게끔 구현해야함
		Gdiplus::Matrix mat;
		static int rot = 0;

		mat.RotateAt(Gdiplus::REAL(rot % 360), Gdiplus::PointF(Platform_Pos.x, Platform_Pos.y)); // 중점을 기준으로 회전

		graphics.SetTransform(&mat);

		rot += (int)(m_DecreaseDegree * 60.f * DELTA_TIME);
		if (rot >= 180 || rot <= -180)
		{
			SetRotating(false);
			rot = 0;
		}
	}
		
	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_PlatformImg, Rect((int)(Platform_Pos.x - Scale.x / 2), (int)(Platform_Pos.y - Scale.y / 2), (int)GetScale().x, (int)GetScale().y),
					   0, 0, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
}
