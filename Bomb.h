#pragma once
#include "Object.h"
class cBomb :
    public cObject
{
private:
    Image* m_BombImg;  // �̹��� ����
    double m_TimeLimit;
    double m_ExplosionRange;
    //float m_Theta; // ������ ������ ����.

public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

};

