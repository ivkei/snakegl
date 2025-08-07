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
public:
  AppleManager(Field& field, Snake& snake, int applesPerField);
  ~AppleManager();

  inline std::vector<Apple> GetApples() const { return _apples; }
  //Index of an apple in the std::vector<Apple>
  void EatApple(Field& field, Snake& snake, int index);

  void DrawApples(Field& field) const;

  inline int ApplesPerField() const { return _applesPerField; }
};
