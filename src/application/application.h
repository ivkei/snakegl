#pragma once

#include"window/window.h"

class Application final{
private:
  Window* _pWindow;
public:
  Application();
  ~Application();

  void Run();
};
