#include "Platform.h"
#include "Scene.h"
#include "Player.h"
#include "Bomb.h"

cPlatform::cPlatform() : m_PlatformImg(NULL), m_DecreaseDegree(0)
{
	m_curGroupType = (INT)GROUP_TYPE::PLATFORM;
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform.png");
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
	// Rotating 하라는 신호일때
	if (GetRotating())
	{
		Vec2 Platform_Pos = GetPos();
		Vec2 Platform_Scale = GetScale();

		cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
		cPlayer* curPlayer = dynamic_cast<cPlayer*>(curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER][0]);
		if (curPlayer->GetPos().x < Platform_Pos.x + Platform_Scale.x / 2
			&& curPlayer->GetPos().x > Platform_Pos.x - Platform_Scale.x / 2)
		{
			curPlayer->SetRotator(Platform_Pos);
			curPlayer->SetRotating(true);
			curPlayer->SetUnsitted();
		}

		for (int i = 0; i < curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::BOMB].size(); ++i)
		{
			cBomb* curBomb = dynamic_cast<cBomb*>(curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::BOMB][i]);
			float curBomb_x = curBomb->GetPos().x;
			if (curBomb_x < Platform_Pos.x + Platform_Scale.x / 2
				&& curBomb_x > Platform_Pos.x - Platform_Scale.x / 2)
			{				
				curBomb->SetRotator(Platform_Pos);
				curBomb->SetRotating(true);

				// 아랫방향
				if (m_DecreaseDegree > 0)
				{
					if (curBomb_x > Platform_Pos.x)
						curBomb->SetRotateDir(false);
					else
						curBomb->SetRotateDir(true);
				}
				// 윗 방향
				else
				{
					if (curBomb_x > Platform_Pos.x)
						curBomb->SetRotateDir(true);
					else
						curBomb->SetRotateDir(false);
				}
				
			}
			
		}

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
		Vec2 Rotator_Pos = GetRotator();		

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

		rot += m_DecreaseDegree;
		if (rot == 180 || rot == -180)
		{
			//curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER][0]->
			SetRotating(false);
			rot = 0;
		}
	}

	//											스케일의 절반만큼 빼주는 이유는 기본적으로 그리기는 왼쪽상단에서부터 그려주기 때문에 그림의 중점을 바꿔주기 위함.
	graphics.DrawImage(m_PlatformImg, Rect((int)Platform_Pos.x - (int)Scale.x / 2, (int)Platform_Pos.y - (int)Scale.y / 2, (int)GetScale().x, (int)GetScale().y),
					   0, 0, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
}
