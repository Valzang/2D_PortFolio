#include "Platform.h"

cPlatform::cPlatform() : m_PlatformImg(NULL)
{
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

	Vec2 Temp_Pos = GetPos();
	Vec2 Scale = GetScale();
	//											�������� ���ݸ�ŭ ���ִ� ������ �⺻������ �׸���� ���ʻ�ܿ������� �׷��ֱ� ������ �׸��� ������ �ٲ��ֱ� ����.
	graphics.DrawImage(m_PlatformImg, Rect((int)Temp_Pos.x - (int)Scale.x / 2, (int)Temp_Pos.y - (int)Scale.y / 2, (int)GetScale().x, (int)GetScale().y),
					   0, 0, (int)Scale.x, (int)Scale.y, UnitPixel, GetImgAttr());
}
