#include "Platform.h"

cPlatform::cPlatform() : m_PlatformImg(NULL), m_CenterPos(Vec2{ 0.f, 0.f })
{
	m_PlatformImg = Image::FromFile((WCHAR*)L"Image/Platform.png");
	SetScale(Vec2((float)m_PlatformImg->GetWidth() / 3.f, (float)m_PlatformImg->GetHeight()));
	SetImgAttr();
}

cPlatform::~cPlatform()
{
	if (m_PlatformImg != NULL)
		delete m_PlatformImg;
}

bool cPlatform::Update()
{
	return true;
}

void cPlatform::Render(HDC _hdc)
{
}
