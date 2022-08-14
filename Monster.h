#pragma once
#include "Object.h"

class cMonster : public cObject
{
protected:
    float m_Speed;
    Image* m_MonsterImg;  // 이미지 파일

public:
    cMonster();
    virtual ~cMonster();

    float GetSpeed() { return m_Speed; }
    void SetSpeed(float _speed) { m_Speed = _speed; }

    virtual bool Update() override = 0;
    virtual void Render(HDC _hdc) override = 0;

};

