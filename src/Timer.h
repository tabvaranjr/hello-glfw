#ifndef HELLO_GLFW_TIMER_H
#define HELLO_GLFW_TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();

    void reset();
    double getTime();

private:
    std::chrono::steady_clock::time_point start;
};


#endif //HELLO_GLFW_TIMER_H
