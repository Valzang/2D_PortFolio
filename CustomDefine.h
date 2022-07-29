#pragma once

#include <Windows.h>
#include <vector>
#include <tchar.h>
#include <string>

// GDI================================
#include <objidl.h>
#include <gdiplus.h>
#pragma comment(lib,"Gdiplus.lib")
using namespace Gdiplus;

static ULONG_PTR g_GdiToken;

static bool GDI_INIT = false;

static void Gdi_Init()
{
	if (!GDI_INIT)
	{
		GdiplusStartupInput gpsi;
		GdiplusStartup(&g_GdiToken, &gpsi, NULL);
		GDI_INIT = true;
	}
};

static void Gdi_End()
{
	GdiplusShutdown(g_GdiToken);
	GDI_INIT = false;
}

// GDI================================

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

#define DELTA_TIME cTimeManager::GetInstance()->GetDT()
#define KEY_CHECK(key, state) cKeyManager::GetInstance()->GetKeyState(key) == state

struct Vec2
{
	float x;
	float y;

public:
	Vec2(const POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2& operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}
	Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BOMB,
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



