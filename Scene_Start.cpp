#include "Scene_Start.h"

void Scene_Start::Enter()
{
	// Object �߰�
	Object* Obj = new Object;

	// Object ��ġ, ũ�� ����

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
