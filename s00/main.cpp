
#include <thread>
#include "EventLoop.h"

void threadFunc()
{
    muduo::EventLoop loop;
    loop.loop();
}

int main()
{

    int i = 0;
    muduo::EventLoop loop;

    std::thread t(threadFunc);

    loop.loop();
    t.join();
    return 0;
}