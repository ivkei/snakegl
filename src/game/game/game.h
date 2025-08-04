#pragma once

#include"engine/sge.h"

class Game{
public:
  Game(SGE::Window& window, std::string execDir);
  ~Game();

  void OnUpdate(float deltaSeconds);
};
