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
  //Call upon switching snake's address!
  void SetKeyCallbacks(SGE::Window* pWindow, Snake* pSnake, Game* pGame);
  void Execute(Snake& snake, Field& field, AppleManager& appleManager, Game& game);
  static float ExecuteEverySeconds;
};

using TSLogic = Singleton<Logic>;
