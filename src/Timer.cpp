#include "Timer.h"

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    start = std::chrono::steady_clock::now();
}

double Timer::getTime()
{
    return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
}
