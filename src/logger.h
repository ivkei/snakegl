#pragma once

#include"pch/pch.h"

//TODO(kei): Get timestamp for linux isnt thread safe, fix

//This function gets current timestamp
static auto GetTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  
#ifdef _SNAKEGL_WINDOWS
  tm time;
  localtime_s(&time, &in_time_t);
  ss << std::put_time(&time, "[%Y-%m-%d, %H:%M:%S]");
#else
  ss <<  std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d, %H:%M:%S]");
#endif
  return ss.str();
}

//The logger class, has static methods to log
class Logger final {
private:
  ~Logger() = default;
  Logger() = default;
public:
  //Logs to console in the format: [timestamp] preinfo: args, in color specified
  template<class...TArgs>
  static void LogToConsole(const std::string& preinfo, const std::string& color, TArgs&&...args){
    std::cout << color << GetTimestamp() << ' ' << preinfo << ": ";
    ((std::cout << std::forward<TArgs>(args)), ...);
    std::cout << "\033[0m" << std::endl;
  }
};

#ifdef _SNAKEGL_ENABLE_LOGGING
//Log info to console, default text color applied
#define LOG_INFO(...)         Logger::LogToConsole("Info", "\033[0m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
//Log warning to console, yellow color applied
#define LOG_WARNING(...)      Logger::LogToConsole("Warning", "\033[33m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
//Log error to console, red color applied
#define LOG_ERROR(...)        Logger::LogToConsole("Error", "\033[31m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
//Log success to console, green color applied
#define LOG_SUCCESS(...)      Logger::LogToConsole("Success", "\033[32m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
#else
#define LOG_INFO(...)
#define LOG_WARNING(...)
#define LOG_ERROR(...)
#define LOG_SUCCESS(...)
#endif

#ifdef _SNAKEGL_ENABLE_LOGGING
#ifdef _SNAKEGL_ENABLE_ASSERTS
//Blue color
#define LOG_ASSERT(x, ...) if (!(x)) Logger::LogToConsole("Assertion failed (" #x ")", "\033[34m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
#else
#define LOG_ASSERT(...)
#endif
#else
#define LOG_ASSERT(...)
#endif
