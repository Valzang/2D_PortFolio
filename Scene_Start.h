#pragma once
#include "Scene.h"

class Scene_Start : public Scene
{
private:

public:
	Scene_Start() {};
	virtual ~Scene_Start() {};

	virtual void Enter() override;
	virtual void Exit() override;

};

