#pragma once
#include "Object.h"

class cMonster :
    public cObject
{
private:
    Vec2 m_CenterPos;
    int m_HP;
    float m_Speed;
    float m_MaxDistance;
    Image* m_MonsterImg;  // 이미지 파일

public:
    virtual bool Update() override;
    cMonster();
    virtual ~cMonster();

    float GetSpeed() { return m_Speed; }
    void SetSpeed(float _speed) { m_Speed = _speed; }
    void SetMaxDist(float _dist) { m_MaxDistance = _dist; }
    virtual void Render(HDC _hdc) override;

    void SetCenterPos(Vec2 _Pos) { m_CenterPos = _Pos; }
};

