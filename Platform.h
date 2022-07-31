#pragma once
#include "Object.h"

class cPlatform : public cObject
{
private:
    Vec2 m_CenterPos;
    Image* m_PlatformImg;  // �̹��� ����

public:
    cPlatform();
    virtual ~cPlatform();

    void SetCenterPos(Vec2 _Pos) { m_CenterPos = _Pos; }

    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;

};


