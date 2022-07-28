#pragma once
#include "Object.h"

class cMonster :
    public cObject
{
private:
    Vec2 m_CenterPos;
    float m_Speed;
    float m_MaxDistance;
    Image* m_MonsterImg;  // 이미지 파일
    ImageAttributes m_imgAttr; // 이미지 속성 담당 변수

public:
    virtual void Update() override;
    cMonster();
    ~cMonster();

    float GetSpeed() { return m_Speed; }
    void SetSpeed(float _speed) { m_Speed = _speed; }
    void SetMaxDist(float _dist) { m_MaxDistance = _dist; }
    virtual void Render(HDC _hdc) override;

    void SetCenterPos(Vec2 _Pos) { m_CenterPos = _Pos; }
};

