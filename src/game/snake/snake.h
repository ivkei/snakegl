#pragma once

#include"field/field.h"
class AppleManager;
#include"applemanager/applemanager.h"

#include"glm/vec2.hpp"

#include<functional>

#define UP_VEC glm::ivec2(0, 1)
#define DW_VEC glm::ivec2(0, -1)
#define LT_VEC glm::ivec2(-1, 0)
#define RT_VEC glm::ivec2(1, 0)

struct SnakeUnit{
  inline static glm::vec4 Color = {0.53f,0.77f,0.86f,1.0f};
  glm::vec2 pos;
};
struct SnakeHead{
  inline static glm::vec4 Color = {0.67f,0.85f,0.93f,1.0f};
  glm::vec2 pos;
};

class Snake{
private:
  int _length;
  SnakeHead _head;
  std::vector<SnakeUnit> _bodyUnits;
  std::function<void()> _gameOver;
  glm::ivec2 _moveDir;
  bool _didMove;
  glm::ivec2 _queriedMoveDirNextMove;
public:
  //initDirOfBodyFromHead should either be UP_VEC, DW_VEC, LT_VEC, RT_VEC
  //initLength includes the head
  Snake(int initLength, glm::vec2 initHeadPos, glm::vec2 initDirOfBodyFromHead, std::function<void()> gameOver);
  ~Snake();

  void Draw(Field& field) const;
  void Move(Field& field, AppleManager& apple);

  void QueryMoveRight();
  void QueryMoveLeft();
  void QueryMoveDown();
  void QueryMoveUp();

  inline SnakeHead GetHead() const { return _head; }
  inline std::vector<SnakeUnit> GetBody() const { return _bodyUnits; }
};
