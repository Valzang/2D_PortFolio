#include "Platform_SideWall.h"

cPlatform_SideWall::cPlatform_SideWall()
{
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform_Side.png");
	SetScale(Vec2((float)m_PlatformImg->GetWidth(), (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform_SideWall::~cPlatform_SideWall()
{
	if (m_PlatformImg != NULL)
	{
		delete m_PlatformImg;
		m_PlatformImg = nullptr;
	}
}