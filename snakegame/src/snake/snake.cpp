#include"snake.h"

#include"glm/gtc/epsilon.hpp"

#include"sge.h"

Snake::Snake(int initLength, glm::vec2 initHeadPos, glm::ivec2 initDirOfBodyFromHead, glm::vec4 headColor, glm::ivec2 initMoveDir)
: _head(initHeadPos),
  _moveDir(initMoveDir),
  _queriedMoveDirNextMove(initMoveDir),
  _didMove(false),
  _headColor(headColor){
  for (int i = 1; i < initLength; ++i){
    _bodyUnits.emplace_back(initHeadPos + (float)i*glm::vec2(initDirOfBodyFromHead));
  }
}

Snake::~Snake(){
}

bool Snake::IsBeyondBorder(Field& field) const{
  return _head.pos.x < 0 ||
         _head.pos.y < 0 ||
         _head.pos.x >= field.Width() ||
         _head.pos.y >= field.Height();
}

//Returns -1 if not touching one
int Snake::TouchingAppleIndex(AppleManager& appleManager) const{
  std::vector<Apple> apples = appleManager.GetApples();
  for (int i = 0; i < apples.size(); ++i){
    auto equalRes = glm::epsilonEqual(_head.pos, apples[i].pos, 0.01f);
    if (equalRes.x && equalRes.y){
      return i;
    }
  }
  return -1;
}

glm::vec2 Snake::MoveHead(){
  if (!_didMove){
    //Use queried move dir if player didnt move
    _moveDir = _queriedMoveDirNextMove;
  }
  glm::vec2 prevPos = _head.pos;

  //Head
  _head.pos += glm::vec2(_moveDir);
  _didMove = false;
  return prevPos;
}

glm::vec2 Snake::MoveBody(glm::vec2 prevPos){
  //Move body
  for (int i = 0; i < _bodyUnits.size(); ++i){
    glm::vec2 tempPrevPos = _bodyUnits[i].pos;
    _bodyUnits[i].pos = prevPos;
    prevPos = tempPrevPos;
  }
  return prevPos;
}

void Snake::MoveBodyAndGrow(glm::vec2 prevPos){
  prevPos = MoveBody(prevPos);
  _bodyUnits.emplace_back(prevPos);
}

bool Snake::IsFillingWholeField(Field& field) const{
  return _bodyUnits.size() + 1 == field.Width() * field.Height();
}

bool Snake::IsTouchingItself() const{
  for (int i = 0; i < _bodyUnits.size(); ++i){
    auto equalRes = glm::epsilonEqual(_head.pos, _bodyUnits[i].pos, 0.01f);
    if (equalRes.x && equalRes.y){
      return true;
    }
  }
  return false;
}

#define QUERY_MOVE(where, fromWhereCant)\
  if (_moveDir != fromWhereCant && _moveDir != where){\
    if (!_didMove){\
      _didMove = true;\
      _moveDir = where;\
      _queriedMoveDirNextMove = where;\
    }\
    else{\
      _queriedMoveDirNextMove = where;\
    }\
  }

void Snake::QueryMoveRight(){
  QUERY_MOVE(RT_VEC, LT_VEC);
}

void Snake::QueryMoveLeft(){
  QUERY_MOVE(LT_VEC, RT_VEC);
}

void Snake::QueryMoveDown(){
  QUERY_MOVE(DW_VEC, UP_VEC);
}

void Snake::QueryMoveUp(){
  QUERY_MOVE(UP_VEC, DW_VEC);
}
