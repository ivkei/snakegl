#pragma once

#include"sge.h"
#include"game/game.h"

class Application : public SGE::Application{
private:
  SGE::Window* _pWindow;
  Game* _pGame;
public:
  Application();
  ~Application() override;

  void Run() override;
};
