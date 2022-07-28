#pragma once
#include "Object.h"

class cPlayer :
    public cObject
{
private:

public:
    virtual void Update() override;
    void CreateBomb();
};

