#include"application.h"

#include<chrono>
#include<filesystem>

Application::Application(){
  _pWindow = new SGE::Window(Game::WindowStats);
  _pGame = new Game(*_pWindow);
}

Application::~Application(){
  delete _pGame;
  delete _pWindow;
}

void Application::Run(){
  //Chrono now binding
  auto cnow = std::chrono::high_resolution_clock::now;
  auto lastFrame = cnow();

  float deltaSeconds;

  while(!_pWindow->ShouldTerminate()){
    auto now = cnow();
    //From nanoseconds
    deltaSeconds = (now - lastFrame).count() * 1e-9;
    lastFrame = cnow();

    _pGame->OnUpdate(deltaSeconds);

    _pWindow->PollEvents();
    _pWindow->SwapBuffers();
  }
}
