#pragma once
#include "Object.h"
class cBomb : public cObject
{
private:
    Image* m_BombImg;  // �̹��� ����
    double m_TimeLimit;
    double m_ExplosionRange;

    // �����ߴ���
    bool m_isExploded;
    int m_ExplosionTime;

    // �߻�ӵ�
    float m_ShootSpeed;

    // �ٴڿ� �� �� ƨ�����
    int m_BounceCount;

    // 
    bool m_DirChanged;


public:
    cBomb();
    virtual ~cBomb();

    virtual bool Update();
    virtual void Render(HDC _hdc);

    // ��� ���� ƨ��� ��
    int GetBounceCount() { return m_BounceCount; }
    void IncreaseBounceCount() { ++m_BounceCount; }
    void SetBounce() { m_Dir.y /= -2.f; m_ShootSpeed /= 1.f; }

    // �����ߴ���
    bool GetExplode() { return m_isExploded; }
    void SetExplode();


};

