#include "Logger.h"

Logger::Logger(const std::string& filename, size_t maxLog) : filename(filename), maxLog(maxLog)
{
  file.open(filename, std::ios_base::app);
}
Logger::~Logger()
{
  if (file.is_open())
  {
      file.close();
  }
}

void Logger::log(const std::string& message)
{
  std::unique_lock<std::shared_mutex> lock(mutex);
  if (file.is_open())
   {
      file << message << "\n";//записываем в файл сообщение
      file.flush();
      logQueue.push_back(message);//добавляем сообщение в очередь

      if (logQueue.size() > maxLog)  // при превышении размера очереди удаляем первое сообщение
       {
            logQueue.pop_front();
       }
   }
}

std::string Logger::readLastLog()
{
  std::shared_lock<std::shared_mutex> lock(mutex);
  if (!logQueue.empty())
  {
    return logQueue.back();  // последнее сообщение из лога
  }
  return "No logs available";
}
