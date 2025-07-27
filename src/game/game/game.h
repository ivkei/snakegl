#pragma once

#include"engine/sge.h"

class Game final{
public:
  Game(SGE::Window& window);
  ~Game();

  void OnUpdate(float deltaSeconds);
};
