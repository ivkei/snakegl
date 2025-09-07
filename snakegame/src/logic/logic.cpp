#include"logic.h"

#include"glm/gtc/matrix_transform.hpp"
#include"sge.h"

float Logic::ExecuteEverySeconds = 0.2f;

void Logic::SetKeyCallbacks(SGE::Window* pWindow, Snake* pSnake, Game* pGame){
  pWindow->SetKeyCallback(SNAKEGL_KEY_W, [pSnake = pSnake](){pSnake->QueryMoveUp(); SGE_LOG_INFO("W");});
  pWindow->SetKeyCallback(SNAKEGL_KEY_A, [pSnake = pSnake](){pSnake->QueryMoveLeft(); SGE_LOG_INFO("A");});
  pWindow->SetKeyCallback(SNAKEGL_KEY_S, [pSnake = pSnake](){pSnake->QueryMoveDown(); SGE_LOG_INFO("S");});
  pWindow->SetKeyCallback(SNAKEGL_KEY_D, [pSnake = pSnake](){pSnake->QueryMoveRight(); SGE_LOG_INFO("D");});
  pWindow->SetKeyCallback(SNAKEGL_KEY_ESC, [pGame = pGame](){pGame->Reset();});
  pWindow->SetKeyCallback(SNAKEGL_KEY_SPC, [pGame](){pGame->Reset();});
}

void Logic::Execute(Snake& snake, Field& field, AppleManager& appleManager, Game& game){
  glm::vec2 prevHeadPos = snake.MoveHead();

  int appleIndex = snake.TouchingAppleIndex(appleManager);
  if (appleIndex != -1){
    snake.MoveBodyAndGrow(prevHeadPos);
    appleManager.EatApple(field, snake, appleIndex);
  }
  else{
    snake.MoveBody(prevHeadPos);
  }

  if (snake.IsBeyondBorder(field) || snake.IsTouchingItself()){
    //Game over
    game.Reset();
  }

  if (snake.IsFillingWholeField(field)){
    //Win
    game.Reset();
  }
}
