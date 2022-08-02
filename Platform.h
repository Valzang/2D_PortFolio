#pragma once
#include "Object.h"

class cPlatform : public cObject
{
protected:
    Image* m_PlatformImg;  // 이미지 파일    

public:
    cPlatform();
    virtual ~cPlatform();

    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;

};


