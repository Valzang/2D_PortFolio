#pragma once
#include "Object.h"
class cBomb :
    public cObject
{
private:
    float m_Direction; // 위 아래 방향

public:
    cBomb();
    virtual ~cBomb();

    virtual void Update();
    virtual void Render(HDC _hdc);
    void SetDirection(bool _Up)
    {
        if (_Up)
            m_Direction = -1.f;
        else
            m_Direction = 1.f;
    }
};

