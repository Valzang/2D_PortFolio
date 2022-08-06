#include "Platform.h"
#include "Scene.h"

cPlatform::cPlatform() : m_PlatformImg(NULL)
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
		cScene* curScene = cSceneManager::GetInstance()->GetCurScene();
		curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER][0]->SetRotator(Platform_Pos);
		curScene->GetCurObjectVec()[(UINT)GROUP_TYPE::PLAYER][0]->SetRotating(true);
		
		int decrease = 0;

		if (GetRotFromDown())
		{
			if (Rotator_Pos.x <= Platform_Pos.x)
				decrease = 10;
			else
				decrease = -10;
		}
		else
		{
			if (Rotator_Pos.x > Platform_Pos.x)
				decrease = 10;
			else
				decrease = -10;
		}

		// Rotator의 위치값에 따라 회전 방향 다르게끔 구현해야함
		Gdiplus::Matrix mat;
		static int rot = 0;

		mat.RotateAt(Gdiplus::REAL(rot % 360), Gdiplus::PointF(Platform_Pos.x, Platform_Pos.y)); // 중점을 기준으로 회전

		graphics.SetTransform(&mat);

		rot += decrease;
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
