#include "Platform_Rotate.h"

cPlatform_Rotate::cPlatform_Rotate()
{
	m_curGroupType = (INT)GROUP_TYPE::PLATFORM_ROTATE;
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform_Rotate.png");
	SetScale(Vec2((float)m_PlatformImg->GetWidth(), (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform_Rotate::~cPlatform_Rotate()
{
	if (m_PlatformImg != NULL)
	{
		delete m_PlatformImg;
		m_PlatformImg = nullptr;
	}
}
