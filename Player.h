#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일    
    bool m_isMoved;
    double m_AtkCoolTime;

public:
    cPlayer();
    virtual ~cPlayer();
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

