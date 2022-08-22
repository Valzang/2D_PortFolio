#pragma once
#include "Object.h"

class cPlatform : public cObject
{
protected:
    Image* m_PlatformImg;  // �̹��� ����
    int m_DecreaseDegree; // ���� ���� ����
    int m_Rot;

public:
    cPlatform();
    virtual ~cPlatform();

    virtual bool Update();
    virtual void Render(HDC _hdc);

};


