#pragma once
#include "Scene.h"
class cScene_Intro : public cScene
{
private:
	Image* m_IntroAlramImg;
	Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����
	Vec2 Alram_Pos;
	Vec2 Alram_Scale;

public:
	cScene_Intro();
	virtual ~cScene_Intro();

	//virtual void Update() override;
	//virtual void Render(HDC _hdc) override;

	virtual void Enter();
	virtual void Exit();
};

