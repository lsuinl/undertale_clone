#include <windows.h>

namespace GameTime
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER previousTime;
    LARGE_INTEGER currentTime;
    double deltaTime;

    int updateCount;
    int fixedUpdateCount;

    void InitTime()
    {
        // 타이머 주파수(frequency) 가져오기
        QueryPerformanceFrequency(&frequency);
        // 현재 시간 가져오기
        QueryPerformanceCounter(&previousTime);
        currentTime = previousTime;
        deltaTime = 0.0;
    }

    void UpdateTime()
    {
        previousTime = currentTime;

        // 현재 시간 가져오기
        QueryPerformanceCounter(&currentTime);

        // 밀리초 단위로 변환
        deltaTime = static_cast<double>(currentTime.QuadPart - previousTime.QuadPart) / frequency.QuadPart;
    }

    double GetDeltaTime()
    {
        return deltaTime;
    }
}
