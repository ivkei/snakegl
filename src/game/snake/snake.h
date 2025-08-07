#pragma once

#include"field/field.h"
class AppleManager;
#include"applemanager/applemanager.h"

#include<vector>

#include"glm/vec2.hpp"

#define UP_VEC glm::ivec2(0, 1)
#define DW_VEC glm::ivec2(0, -1)
#define LT_VEC glm::ivec2(-1, 0)
#define RT_VEC glm::ivec2(1, 0)

struct SnakeUnit{
  static inline glm::vec4 DefaultColor = {0.53f,0.77f,0.86f,1.0f};
  glm::vec2 pos;
  glm::vec4 color = DefaultColor;
};
struct SnakeHead{
  glm::vec2 pos;
};

class Snake{
private:
  SnakeHead _head;
  glm::ivec2 _moveDir;
  glm::ivec2 _queriedMoveDirNextMove;
  bool _didMove;
  glm::vec4 _headColor;
  std::vector<SnakeUnit> _bodyUnits;
public:
  //initDirOfBodyFromHead should either be UP_VEC, DW_VEC, LT_VEC, RT_VEC
  //initLength includes the head
  Snake(int initLength, glm::vec2 initHeadPos, glm::ivec2 initDirOfBodyFromHead, glm::vec4 headColor, glm::ivec2 initMoveDir);
  ~Snake();

  bool IsBeyondBorder(Field& field) const;
  //Returns -1 if not touching one
  int TouchingAppleIndex(AppleManager& appleManager) const;
  //Returns position of the last (tail) unit that was left upon moving
  //prevPos is the position of the head before it moved
  glm::vec2 MoveBody(glm::vec2 prevPos);
  //prevPos is the position of the head before it moved
  void MoveBodyAndGrow(glm::vec2 prevPos);
  //Returns position of the head before move
  glm::vec2 MoveHead();
  bool IsFillingWholeField(Field& field) const;
  bool IsTouchingItself() const;

  void QueryMoveRight();
  void QueryMoveLeft();
  void QueryMoveDown();
  void QueryMoveUp();

  inline SnakeHead GetHead() const { return _head; }
  inline std::vector<SnakeUnit> GetBody() const { return _bodyUnits; }

  inline glm::vec4 HeadColor() const { return _headColor; }
};
