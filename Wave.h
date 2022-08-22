#pragma once
#include "Object.h"
#include "Monster_Boss.h"
class cWave : public cObject
{
private:
    Image* m_WaveImg;  // 이미지 파일
    Vec2 m_ImgScale[13];
    cMonster_Boss* m_Boss;
    float m_FirstY;
    int m_curFrame;
    int m_yStart;

public:
    cWave();
    cWave(Vec2 _Pos, int _Direction, cMonster_Boss* _Boss);
    virtual ~cWave();

    void DestroyByBomb();

    void Init();

    virtual bool Update();
    virtual void Render(HDC _hdc);
};

