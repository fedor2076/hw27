#include "Logger.h"
#include <iostream>
#include <thread>

int main()
{
Logger logger("log.txt", 10); // создаем logger хранящий до 10 логов
//демо-----------------------------------------------------
std::thread t1([&]()
{
  for (int i = 0; i < 15; ++i)
    {
        logger.log("Thread 1: Message " + std::to_string(i));
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
});

std::thread t2([&]()
{
    for (int i = 0; i < 15; ++i)
    {
    logger.log("Thread 2: Message " + std::to_string(i));
    std::this_thread::sleep_for(std::chrono::milliseconds(70));
    }
});

t1.join();
t2.join();

std::cout << "Last message: " << logger.readLastLog() << std::endl;
}
