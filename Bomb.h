#pragma once
#include "Object.h"
class cBomb : public cObject
{
private:
    Image* m_BombImg;  // 이미지 파일
    double m_TimeLimit;
    double m_ExplosionRange;

    // 폭발했는지
    bool m_isExploded;
    int m_ExplosionTime;

    // 발사속도
    float m_ShootSpeed;

    // 바닥에 몇 번 튕겼는지
    int m_BounceCount;

    // 
    bool m_DirChanged;


public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

    // 몇번 땅에 튕기는 지
    int GetBounceCount() { return m_BounceCount; }
    void IncreaseBounceCount() { ++m_BounceCount; }
    void SetBounce() { m_Dir.y /= -2.f; m_ShootSpeed /= 1.f; }

    // 폭발했는지
    bool GetExplode() { return m_isExploded; }
    void SetExplode();


};

