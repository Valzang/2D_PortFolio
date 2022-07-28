#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:
    Image* m_PlayerImg;  // �̹��� ����
    Gdiplus::ImageAttributes m_imgAttr; // �̹��� �Ӽ� ��� ����
    bool m_isMoved;

public:
    cPlayer();
    virtual ~cPlayer();
    virtual void Update() override;
    virtual void Render(HDC _hdc) override;
    void CreateBomb();
};

