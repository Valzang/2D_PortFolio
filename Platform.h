#pragma once
#include "Object.h"

class cPlatform : public cObject
{
protected:
    Image* m_PlatformImg;  // �̹��� ����
    int m_DecreaseDegree;

public:
    cPlatform();
    virtual ~cPlatform();

    virtual bool Update() override;
    virtual void Render(HDC _hdc) override;

};


