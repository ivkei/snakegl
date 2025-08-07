#pragma once

#include"snake/snake.h"
#include"field/field.h"
#include"applemanager/applemanager.h"
#include"game/game.h"

#include"utils/singleton.h"

#include"engine/sge.h"

class Logic{
private:
public:
  void SetKeyCallbacks(SGE::Window* pWindow, Snake* pSnake, SnakeGame* pGame);
  void Execute(Snake& snake, Field& field, AppleManager& appleManager, SnakeGame& game);
  static float ExecuteEverySeconds;
};

using TSLogic = Singleton<Logic>;
