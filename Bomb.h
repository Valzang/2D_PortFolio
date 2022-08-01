#pragma once
#include "Object.h"
class cBomb :
    public cObject
{
private:
    Image* m_BombImg;  // �̹��� ����
    double m_TimeLimit;
    //float m_Theta; // ������ ������ ����.
    Vec2 m_Dir;     // ���ͷ� ������ ����.

public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

    Vec2 GetDir() { return m_Dir; }
    void SetDir(Vec2 _Dir) { m_Dir = _Dir; m_Dir.Normalize(); }
};

