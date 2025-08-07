#pragma once

#include"engine/sge.h"

#include"field/field.h"
#include"snake/snake.h"
#include"applemanager/applemanager.h"

#include<memory>

class Game{
private:
  std::unique_ptr<Field> _pField;
  std::unique_ptr<Snake> _pSnake;
  std::unique_ptr<AppleManager> _pAppleManager;
public:
  Game(SGE::Window& window);
  ~Game();

  void OnUpdate(float deltaSeconds);
  void Reset();
};
