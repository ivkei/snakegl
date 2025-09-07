#pragma once

#ifdef _SNAKEGL_WINDOWS
  //Windows
  #ifdef _SNAKEGL_ENGINE
    //Engine
    #define SGE_API __declspec(dllexport)
  #else
    //Game
    #define SGE_API __declspec(dllimport)
  #endif
#elif _SNAKEGL_LINUX
  //Linux
  #define SGE_API
#else
  //Other platforms
  #error "Unknown platform"
  //#define SGE_API
#endif
