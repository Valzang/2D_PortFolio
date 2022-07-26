#pragma once

#include <Windows.h>
#include <vector>
#include <tchar.h>
#include <string>
#include <cmath>
#include <assert.h>
#include <map>


#pragma comment(lib,"Msimg32.lib")

// SOUND ================================================================
#include <mmsystem.h> // Playsound를 위한 함수 (wav)
#include <Digitalv.h> //

#pragma comment(lib, "winmm.lib")

// GDI==================================================================
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

// =====================================================================

//
// For Debugging========================================================
//
//#include <iostream>
//#ifdef UNICODE
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#else
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
//#endif
// =====================================================================

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


enum class GROUP_TYPE
{
	DEFAULT,
	WAVE,
	PLATFORM,
	PLATFORM_ROTATE,
	PLATFORM_BROKEN,
	PLAYER,
	MONSTER,
	MONSTER_THORN,
	MONSTER_RUNNER,
	MONSTER_BOSS,
	THING,
	BOMB,
	SPITFIRE,

	END = 13,
};

enum class SCENE_TYPE
{
	START,
	STAGE_11,
	STAGE_12,
	STAGE_13,
	STAGE_14,
	STAGE_15,
	ENDING,

	END,
};


struct Vec2
{
	float x;
	float y;

	// 생성자 ===================================================
	Vec2(const POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
	Vec2& operator=(POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
		return *this;
	}

	template <typename T>
	Vec2& operator*(T _value)
	{
		x *= (float)_value;
		y *= (float)_value;
		return *this;
	}

	template <typename T>
	Vec2& operator/(T _value)
	{
		x /= (float)_value;
		y /= (float)_value;
		return *this;
	}

	Vec2() : x(0.f), y(0.f) {}

	template <typename T>
	Vec2(T _x, T _y) : x((float)_x), y((float)_y) {}

	// 생성자 ==============================================
	Vec2& Normalize() // 벡터 일반화
	{
		float fLen = Length();

		assert(fLen != 0.f); // 0이면 오류

		x /= fLen;
		y /= fLen;
		return*this;
	}

	double Distance(Vec2& _Other)
	{
		return pow(_Other.x - x, 2) + pow(_Other.y - y, 2);
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}
};




