#include"path.h"

#include"engine/sge.h"
#include<filesystem>

namespace SGE{

#ifdef _SNAKEGL_WINDOWS
#include<windows.h>

std::string GetExecDir(){
  char* buffer = new char[512];
  DWORD len = GetModuleFileNameA(NULL, buffer, 512);
  if (len == 0){
    SGE_LOG_ERROR("Couldnt get executable path!");
  }
  std::string res = std::filesystem::path(buffer).parent_path().string() + "/";
  delete[] buffer;
  return res;
}
#elif _SNAKEGL_LINUX
#include<unistd.h>

std::string GetExecDir(){
  char* buffer = new char[512];
  int len = readlink("/proc/self/exe", buffer, 512);
  if (len == 0){
    SGE_LOG_ERROR("Couldnt get executable path!");
  }
  std::string res = std::filesystem::path(buffer).parent_path().string() + "/";
  delete[] buffer;
  return res;
}
#else
#error "Unknown platform!"
#endif

}
