#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <deque>

class Logger
{
public:
    Logger(const std::string& filename, size_t maxLog);
    ~Logger();
    void log(const std::string& message);
    std::string readLastLog();
private:
    std::string filename;
    std::ofstream file;
    std::deque<std::string> logQueue;
    size_t maxLog;
    mutable std::shared_mutex mutex;
};
