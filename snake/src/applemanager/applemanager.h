#pragma once

#include"glm/vec2.hpp"

#include"field/field.h"
class Snake;
#include"snake/snake.h"

#include<vector>

struct Apple{
  glm::vec2 pos;
};

class AppleManager{
private:
  int _applesPerField;
  std::vector<Apple> _apples;
  glm::vec4 _appleColor;
public:
  AppleManager(Field& field, Snake& snake, int applesPerField, glm::vec4 appleColor);
  ~AppleManager();

  inline std::vector<Apple> GetApples() const { return _apples; }
  //Index of an apple in the std::vector<Apple>
  void EatApple(Field& field, Snake& snake, int index);

  inline int ApplesPerField() const { return _applesPerField; }

  inline glm::vec4 AppleColor() const { return _appleColor; }
};
