#include"application.h"

#include"pch/pch.h"
#include"utils.h"

Application::Application(){
  Window::Stats stats = {"SnakeGame", 720, 720};
  _pWindow = new Window(stats);
}

Application::~Application(){
  delete _pWindow;
}

void Application::Run(){
  //Chrono now binding
  auto cnow = std::chrono::high_resolution_clock::now;
  auto then = cnow();

  float deltaSeconds;

  while(!_pWindow->ShouldTerminate()){
    auto now = cnow();
    //From nanoseconds
    deltaSeconds = (then - now).count() / 10e+9;

    //Logic here

    _pWindow->PollEvents();
    _pWindow->SwapBuffers();

    then = cnow();
  }
}
