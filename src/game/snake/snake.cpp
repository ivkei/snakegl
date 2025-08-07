#include"snake.h"

#include"glm/gtc/epsilon.hpp"

#include"engine/sge.h"

Snake::Snake(int initLength, glm::vec2 initHeadPos, glm::vec2 initDirOfBodyFromHead, std::function<void()> gameOver, std::function<void()> win)
: _head(initHeadPos),
  _gameOver(gameOver),
  _win(win),
  _moveDir(glm::vec2(1, 0)),
  _queriedMoveDirNextMove(glm::vec2(1, 0)),
  _didMove(false){
  for (int i = 1; i < initLength; ++i){
    _bodyUnits.emplace_back(initHeadPos + (float)i*initDirOfBodyFromHead);
  }
}

Snake::~Snake(){
}

void Snake::Draw(Field& field) const{
  //Head
  SGE::TSRenderer::Instance()->Quad(glm::vec2(_head.pos.x + field.UnitHorOffset(), _head.pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), SnakeHead::Color);
  //Body
  for (int i = 0; i < _bodyUnits.size(); ++i){
    SGE::TSRenderer::Instance()->Quad(glm::vec2(_bodyUnits[i].pos.x + field.UnitHorOffset(), _bodyUnits[i].pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), SnakeUnit::Color);
  }
}

void Snake::Move(Field& field, AppleManager& appleManager){
  if (!_didMove){
    //Use queried move dir if player didnt move
    _moveDir = _queriedMoveDirNextMove;
  }

  glm::vec2 prevPos = _head.pos;
  _head.pos += _moveDir;
  _didMove = false;

  //Out of bounds
  if (_head.pos.x < 0 || _head.pos.y < 0 || _head.pos.x >= field.Width() || _head.pos.y >= field.Height()){
    _gameOver();
    return;
  }
  
  //Eat apple if can
  std::vector<Apple> apples = appleManager.GetApples();
  for (int i = 0; i < apples.size(); ++i){
    auto equalRes = glm::epsilonEqual(_head.pos, apples[i].pos, 0.01f);
    if (equalRes.x && equalRes.y){
      _bodyUnits.emplace(_bodyUnits.begin(), prevPos);
      appleManager.EatApple(field, *this, i);

      return; //Added a body unit, moved head
    }
  }

  //Win
  if (_bodyUnits.size() + 1 == field.Width() * field.Height()){
    _win();
  }

  //Move body, if didnt eat apple
  for (int i = 0; i < _bodyUnits.size(); ++i){
    glm::vec2 tempPrevPos = _bodyUnits[i].pos;
    _bodyUnits[i].pos = prevPos;
    prevPos = tempPrevPos;
  }

  //Hit itself
  for (int i = 0; i < _bodyUnits.size(); ++i){
    auto equalRes = glm::epsilonEqual(_head.pos, _bodyUnits[i].pos, 0.01f);
    if (equalRes.x && equalRes.y){
      _gameOver();
      return;
    }
  }
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
