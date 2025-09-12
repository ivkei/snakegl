#pragma once

#include"sge.h"

#include"field/field.h"

#include<memory>

class Game{
private:
  std::unique_ptr<Field> _pField;
public:
  Game(SGE::Window& window);
  ~Game();

  void OnUpdate(float deltaSeconds);
  void Reset();

  static SGE::Window::Stats WindowStats;
};
