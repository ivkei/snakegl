#include"gameapplication.h"

#include<chrono>
#include<filesystem>

GameApplication::GameApplication(std::string argv0){
  SGE::Window::Stats stats = {"SnakeGL", 720, 720, false};
  _pWindow = new SGE::Window(stats);

  std::string execDir = std::filesystem::absolute(std::filesystem::current_path()/argv0).parent_path().string() + "/";
  SGE_LOG_INFO("Exec dir: ", execDir);

  _pGame = new Game(*_pWindow, execDir);
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
