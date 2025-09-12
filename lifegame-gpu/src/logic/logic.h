#pragma once

#include"field/field.h"
#include"game/game.h"

#include"sge.h"

class Logic{
private:
public:
  //Call upon switching snake's address!
  void SetKeyCallbacks(SGE::Window* pWindow, Game* pGame);
  void Execute(Field& field, Game& game);
  static float ExecuteEverySeconds;
};

using TSLogic = SGE::Singleton<Logic>;
