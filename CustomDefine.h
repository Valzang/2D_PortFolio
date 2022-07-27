#pragma once

#include <Windows.h>
#include <vector>
#include <tchar.h>
#include <string>

using namespace std;

#define SINGLETON2(type) public:\
							static type* GetInstance()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();

#define DELTA_TIME TimeManager::GetInstance()->GetDT()

struct Vec2
{
	float x;
	float y;
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	THING,

	END = 10,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_11,
	STAGE_12,
	STAGE_13,
	STAGE_14,
	STAGE_15,

	END,
};



