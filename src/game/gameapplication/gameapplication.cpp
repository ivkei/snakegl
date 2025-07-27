#include"gameapplication.h"

#include"stdpch/stdpch.h"

GameApplication::GameApplication(){
  SGE::Window::Stats stats = {"SnakeGL", 720, 720};
  _pWindow = new SGE::Window(stats);
  _pGame = new Game(*_pWindow);
}

GameApplication::~GameApplication(){
  delete _pGame;
  delete _pWindow;
}

void GameApplication::Run(){
  //Chrono now binding
  auto cnow = std::chrono::high_resolution_clock::now;
  auto then = cnow();

  float deltaSeconds;

  while(!_pWindow->ShouldTerminate()){
    auto now = cnow();
    //From nanoseconds
    deltaSeconds = (then - now).count() * 1e-9;

    _pGame->OnUpdate(deltaSeconds);

    _pWindow->PollEvents();
    _pWindow->SwapBuffers();

    then = cnow();
  }
}
