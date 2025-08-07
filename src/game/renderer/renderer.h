#pragma once

#include"snake/snake.h"
#include"field/field.h"
#include"applemanager/applemanager.h"

#include"utils/singleton.h"

class Renderer{
private:
public:
  void SetupShadersAndCoord(Field& field);
  void Render(Snake& snake, Field& field, AppleManager& appleManager);
};

using TSRenderer = Singleton<Renderer>;
