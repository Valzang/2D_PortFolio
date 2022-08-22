#include "Platform_Broken.h"

cPlatform_Broken::cPlatform_Broken()
{
	m_curGroupType = (INT)GROUP_TYPE::PLATFORM_BROKEN;
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform_Broken.png");
	SetScale(Vec2((float)m_PlatformImg->GetWidth(), (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform_Broken::~cPlatform_Broken()
{
	if (m_PlatformImg != NULL)
	{
		delete m_PlatformImg;
		m_PlatformImg = nullptr;
	}
}