#include"applemanager.h"

#include"engine/sge.h"

#include"glm/gtc/epsilon.hpp"

#include<random>
#include<ctime>

static Apple GetRandomApple(Field& field, Snake& snake, AppleManager& appleManager){
  //Snake positions
  std::vector<glm::vec2> snakePositions;
  snakePositions.push_back(snake.GetHead().pos);
  std::vector<SnakeUnit> body = snake.GetBody();
  for (int i = 0; i < body.size(); ++i){
    snakePositions.push_back(body[i].pos);
  }

  SGE_LOG_INFO("Snake positions count: ", snakePositions.size());

  //Generate unique (the one that doesnt fall on snake or on any other apple) apple
  glm::vec2 applePos;
  while (true){
    applePos = {rand() % field.Width(), rand() % field.Height()};
    SGE_LOG_INFO("Proposed random position: (", applePos.x, ", ", applePos.y, ")");
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

AppleManager::AppleManager(Field& field, Snake& snake, int applesPerField)
: _applesPerField(applesPerField){
  srand(time(NULL));

  for (int i = 0; i < _applesPerField; ++i){
    _apples.emplace_back(GetRandomApple(field, snake, *this));
  }
}

AppleManager::~AppleManager(){
}

void AppleManager::EatApple(Field& field, Snake& snake, int index){
  SGE_LOG_INFO("Index of apple eaten: ", index);
  Apple apple = GetRandomApple(field, snake, *this);
  SGE_LOG_INFO("Apple set at index: (", apple.pos.x, ", ", apple.pos.y, ")");
  _apples[index] = apple;
}

void AppleManager::DrawApples(Field& field) const{
  glm::vec4 appleColor = {0.85f, 0.45f, 0.45f, 1.0f};
  for (int i = 0; i < _applesPerField; ++i){
    SGE::TSRenderer::Instance()->Quad(glm::vec2(_apples[i].pos.x + field.UnitHorOffset(), _apples[i].pos.y + field.UnitVerOffset()), glm::vec2(field.UnitWidth(), field.UnitHeight()), appleColor);
  }
}
