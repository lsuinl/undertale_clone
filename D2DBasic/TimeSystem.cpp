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
        // Ÿ�̸� ���ļ�(frequency) ��������
        QueryPerformanceFrequency(&frequency);
        // ���� �ð� ��������
        QueryPerformanceCounter(&previousTime);
        currentTime = previousTime;
        deltaTime = 0.0;
    }

    void UpdateTime()
    {
        previousTime = currentTime;

        // ���� �ð� ��������
        QueryPerformanceCounter(&currentTime);

        // �и��� ������ ��ȯ
        deltaTime = static_cast<double>(currentTime.QuadPart - previousTime.QuadPart) / frequency.QuadPart;
    }

    double GetDeltaTime()
    {
        return deltaTime;
    }
}
