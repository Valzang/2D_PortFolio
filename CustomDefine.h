#pragma once

#include <Windows.h>
#include <vector>
#include <tchar.h>

using namespace std;

#define SINGLETON2(type) public:\
							static type* GetInstance()\
							{\
								static type mgr;\
								return &mgr;\
							}\
						private:\
							type();\
							~type();\

#define DELTA_TIME TimeManager::GetInstance()->GetDT()