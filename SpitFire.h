#pragma once
#include "Object.h"
class cSpitFire : public cObject
{
private:
    Image* m_FireImg;  // �̹��� ����

public:
    cSpitFire();
    cSpitFire(Vec2 _Pos, int _Direction);
    virtual ~cSpitFire();

    virtual bool Update();
    virtual void Render(HDC _hdc);
};

