#include"logic.h"

#include"glm/gtc/matrix_transform.hpp"
#include"sge.h"

float Logic::ExecuteEverySeconds = 0.1f;

void Logic::SetKeyCallbacks(SGE::Window* pWindow, Game* pGame){
  pWindow->SetKeyCallback(SNAKEGL_KEY_ESC, [pGame = pGame](){pGame->Reset();});
  pWindow->SetKeyCallback(SNAKEGL_KEY_SPC, [pGame](){pGame->Reset();});
}

void Logic::Execute(Field& field, Game& game){
  field.Update();
}
