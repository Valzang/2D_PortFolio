#pragma once
#include "Object.h"

class cPlatform : public cObject
{
protected:
    Image* m_PlatformImg;  // 이미지 파일
    int m_DecreaseDegree; // 각도 감소 정도

public:
    cPlatform();
    virtual ~cPlatform();

    virtual bool Update();
    virtual void Render(HDC _hdc);

};


