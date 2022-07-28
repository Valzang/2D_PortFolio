#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // 이미지 파일
    Gdiplus::ImageAttributes m_imgAttr; // 이미지 속성 담당 변수
    bool m_isMoved;

public:
    cPlayer();
    virtual ~cPlayer();
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

