#include "Platform_Under.h"

cPlatform_Under::cPlatform_Under()
{
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform/Platform_Under.png");
	SetScale(Vec2((float)m_PlatformImg->GetWidth(), (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform_Under::~cPlatform_Under()
{
	if (m_PlatformImg != NULL)
	{
		delete m_PlatformImg;
		m_PlatformImg = nullptr;
	}
}