#pragma once

#include"engine/sge.h"
#include"game/game.h"

class GameApplication : public SGE::Application{
private:
  Window* _pWindow;
  Game* _pGame;
public:
  GameApplication();
  ~GameApplication() override;

  void Run() override;
};
