#pragma once
#include "Object.h"
class cBomb : public cObject
{
private:
    Image* m_BombImg;  // 이미지 파일
    double m_TimeLimit;
    double m_ExplosionRange;

    bool m_isShoot;
    float m_ShootSpeed;
    int m_BounceCount;
    bool m_DirChanged;

    bool m_RotateToUp;

public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

    bool GetIsShoot() { return m_isShoot; }
    void SetIsShoot(bool _val) { m_isShoot = _val; }
    int GetBounceCount() { return m_BounceCount; }
    void IncreaseBounceCount() { ++m_BounceCount; }
    void SetBounce() { m_Dir.y /= -2.f; m_ShootSpeed /= 1.f; }

    void SetRotateDir(bool _val) { m_RotateToUp = _val; }

};

