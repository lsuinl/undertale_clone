#pragma once
#include <Windows.h>
//시간을 관리합니다!
namespace GameTime
{
	void InitTime();
	void UpdateTime();
	double GetDeltaTime();
}
