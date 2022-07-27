#include "Scene_Start.h"

void Scene_Start::Enter()
{
	// Object 추가
	Object* Obj = new Object;

	// Object 위치, 크기 설정

	/*
	
	Obj->SetPos(Vec2(640.f, 384.f));
	Obj->SetScale(Vec2(100.f, 100.f));
	
	*/


	// 

	AddObject(Obj, GROUP_TYPE::DEFAULT);
}

void Scene_Start::Exit()
{
}
