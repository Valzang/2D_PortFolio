#pragma once
#include "Object.h"

class cMonster : public cObject
{
protected:
    Vec2 m_CenterPos;
    int m_HP;
    float m_Speed;
    float m_MaxDistance;
    Image* m_MonsterImg;  // 이미지 파일

public:
    cMonster();
    virtual ~cMonster();

    float GetSpeed() { return m_Speed; }
    void SetSpeed(float _speed) { m_Speed = _speed; }
    void SetCenterPos(Vec2 _Pos) { m_CenterPos = _Pos; }
    void SetMaxDist(float _dist) { m_MaxDistance = _dist; }

    virtual bool Update() override = 0;
    virtual void Render(HDC _hdc) override = 0;

};

