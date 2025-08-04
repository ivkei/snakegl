#pragma once

#include"engine/sge.h"
#include"game/game.h"

class GameApplication : public SGE::Application{
private:
  SGE::Window* _pWindow;
  Game* _pGame;
public:
  GameApplication(std::string argv0);
  ~GameApplication() override;

  void Run() override;
};
