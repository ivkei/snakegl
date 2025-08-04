#pragma once

#include"pch/pch.h"

namespace SGE{

#ifndef _SNAKEGL_WINDOWS
static std::mutex localtimeFuncLock;
#endif

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
  localtimeFuncLock.lock();
  ss <<  std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d, %H:%M:%S]");
  localtimeFuncLock.unlock();
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

}

#ifdef _SNAKEGL_DEBUG
#define _SNAKEGL_ENABLE_LOGGING
#define _SNAKEGL_ENABLE_ASSERTS
#endif

#ifdef _SNAKEGL_ENABLE_LOGGING
  #ifdef _SNAKEGL_ENGINE
    //Log info to console, default text color applied
    #define SGE_LOG_INFO(...)         SGE::Logger::LogToConsole("Engine Info", "\033[0m", __VA_ARGS__)
    //Log warning to console, yellow color applied
    #define SGE_LOG_WARNING(...)      SGE::Logger::LogToConsole("Engine Warning", "\033[33m", __VA_ARGS__)
    //Log error to console, red color applied
    #define SGE_LOG_ERROR(...)        SGE::Logger::LogToConsole("Engine Error", "\033[31m", __VA_ARGS__)
    //Log success to console, green color applied
    #define SGE_LOG_SUCCESS(...)      SGE::Logger::LogToConsole("Engine Success", "\033[32m", __VA_ARGS__)
    #ifdef _SNAKEGL_ENABLE_ASSERTS
      //Blue color
      #define SGE_LOG_ASSERT(x, ...) if (!(x)) SGE::Logger::LogToConsole("Engine Assertion failed (" #x ")", "\033[34m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
    #else
      #define SGE_LOG_ASSERT(...)
    #endif
  #elif _SNAKEGL_GAME
    //Log info to console, default text color applied
    #define SGE_LOG_INFO(...)         SGE::Logger::LogToConsole("Game Info", "\033[0m", __VA_ARGS__)
    //Log warning to console, yellow color applied
    #define SGE_LOG_WARNING(...)      SGE::Logger::LogToConsole("Game Warning", "\033[33m", __VA_ARGS__)
    //Log error to console, red color applied
    #define SGE_LOG_ERROR(...)        SGE::Logger::LogToConsole("Game Error", "\033[31m", __VA_ARGS__)
    //Log success to console, green color applied
    #define SGE_LOG_SUCCESS(...)      SGE::Logger::LogToConsole("Game Success", "\033[32m", __VA_ARGS__)
    #ifdef _SNAKEGL_ENABLE_ASSERTS
      //Blue color
      #define SGE_LOG_ASSERT(x, ...) if (!(x)) SGE::Logger::LogToConsole("Game Assertion failed (" #x ")", "\033[34m", __VA_ARGS__, "\n{\nFile: ", __FILE__, "\nLine: ", __LINE__, "\n}")
    #else
      #define SGE_LOG_ASSERT(...)
    #endif
  #endif
#else
#define SGE_LOG_INFO(...)
#define SGE_LOG_WARNING(...)
#define SGE_LOG_ERROR(...)
#define SGE_LOG_SUCCESS(...)
#define SGE_LOG_ASSERT(...)
#endif
