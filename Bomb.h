#pragma once
#include "Object.h"
class cBomb :
    public cObject
{
private:
    Image* m_BombImg;  // 이미지 파일
    double m_TimeLimit;
    //float m_Theta; // 각도로 방향을 정함.

public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

};

