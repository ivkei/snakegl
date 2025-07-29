#pragma once

#include"engine/sge.h"

class Game{
public:
  Game(SGE::Window& window);
  ~Game();

  void OnUpdate(float deltaSeconds);
};
