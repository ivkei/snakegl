#include"gameapplication.h"

#include<chrono>
#include<filesystem>

GameApplication::GameApplication(){
  _pWindow = new SGE::Window(SnakeGame::WindowStats);
  _pGame = new SnakeGame(*_pWindow);
}

GameApplication::~GameApplication(){
  delete _pGame;
  delete _pWindow;
}

void GameApplication::Run(){
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
