#pragma once
#include "Object.h"
class cBomb :
    public cObject
{
private:
    Image* m_BombImg;  // �̹��� ����

public:
    cBomb();
    virtual ~cBomb();

    virtual void Update();
    virtual void Render(HDC _hdc);
};

