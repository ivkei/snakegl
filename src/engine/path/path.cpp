#include"src/engine/pch/pch.h"

#include"path.h"

namespace SGE{

#ifdef _SNAKEGL_WINDOWS
#include<windows.h>

std::filesystem::path SGE_API GetExecDir(){
  char* buffer = new char[512];
  DWORD len = GetModuleFileNameA(NULL, buffer, 512);
  if (len == 0){
    SGE_LOG_ERROR("Couldnt get executable path!");
  }
  std::filesystem::path path = std::filesystem::path(buffer).parent_path();
  delete[] buffer;
  return path;
}
#elif _SNAKEGL_LINUX
#include<unistd.h>

std::filesystem::path SGE_API GetExecDir(){
  char* buffer = new char[512];
  int len = readlink("/proc/self/exe", buffer, 512);
  if (len == 0){
    SGE_LOG_ERROR("Couldnt get executable path!");
  }
  std::filesystem::path path = std::filesystem::path(buffer).parent_path();
  delete[] buffer;
  return path;
}
#else
#error "Unknown platform!"
#endif

}
