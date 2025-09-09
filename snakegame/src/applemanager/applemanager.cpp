#include"applemanager.h"

#include"sge.h"

#include"glm/gtc/epsilon.hpp"

#include<random>
#include<ctime>

//Returns -1, -1 if field is being overtaken by the snake
static Apple GetRandomApple(Field& field, Snake& snake, AppleManager& appleManager){
  //Snake positions
  std::vector<glm::vec2> snakePositions;
  snakePositions.push_back(snake.GetHead().pos);
  std::vector<SnakeUnit> body = snake.GetBody();
  for (int i = 0; i < body.size(); ++i){
    snakePositions.push_back(body[i].pos);
  }

  //Cant generate more apples, field is being overtaken
  if (snake.GetBody().size() + 1 > field.Width() * field.Height() - appleManager.ApplesPerField()){
    return {glm::vec2(-1, -1)};
  }

  //Generate unique (the one that doesnt fall on snake or on any other apple) apple
  glm::vec2 applePos;
  while (true){
    applePos = {rand() % field.Width(), rand() % field.Height()};
    bool unique = true;
    
    //Check snake position
    for (int i = 0; i < snakePositions.size(); ++i){
      auto cmpRes = glm::epsilonEqual(applePos, snakePositions[i], 0.01f);
      if (cmpRes.x && cmpRes.y){
        unique = false;
        break;
      }
    }

    //Check apples positions
    std::vector<Apple> apples = appleManager.GetApples();
    for (int i = 0; i < apples.size(); ++i){
      auto cmpRes = glm::epsilonEqual(applePos, apples[i].pos, 0.01f);
      if (cmpRes.x && cmpRes.y){
        unique = false;
        break;
      }
    }
    if (unique) break;
  }

  return {applePos};
}

AppleManager::AppleManager(Field& field, Snake& snake, int applesPerField, glm::vec4 appleColor)
: _applesPerField(applesPerField),
  _appleColor(appleColor){
  srand(time(NULL));

  for (int i = 0; i < _applesPerField; ++i){
    _apples.emplace_back(GetRandomApple(field, snake, *this));
  }
}

AppleManager::~AppleManager(){
}

void AppleManager::EatApple(Field& field, Snake& snake, int index){
  Apple apple = GetRandomApple(field, snake, *this);

  auto cmpRes = glm::epsilonEqual(apple.pos, glm::vec2(-1.0f, -1.0f), 0.01f);
  if (cmpRes.x && cmpRes.y){
    SGE_LOG_INFO("Cant fit an apple onto the screen, delete it");
    _apples.erase(_apples.begin() + index);
  }
  else{
    SGE_LOG_INFO("Apple is randomized");
    _apples[index] = apple;
  }
}
