#pragma once
#include "Object.h"
#include "Monster_Boss.h"
class cWave : public cObject
{
private:
    Image* m_WaveImg;  // �̹��� ����
    Vec2 m_ImgScale[13];
    cMonster_Boss* m_Boss;
    float m_FirstY;

public:
    cWave();
    cWave(Vec2 _Pos, int _Direction, cMonster_Boss* _Boss);
    virtual ~cWave();

    void Init();

    virtual bool Update();
    virtual void Render(HDC _hdc);
};
