#include"logic.h"

#include"glm/gtc/matrix_transform.hpp"
#include"sge.h"

float Logic::ExecuteEverySeconds = 0.1f;

void Logic::SetKeyCallbacks(SGE::Window* pWindow, Game* pGame){
  pWindow->SetKeyCallback(SNAKEGL_KEY_ESC, [pGame = pGame](){pGame->Reset();});
  pWindow->SetKeyCallback(SNAKEGL_KEY_SPC, [pGame](){pGame->Reset();});
}

static int NeighborsCount(Field& field, int x, int y){
  int count = 0;

  for (int i = x - 1; i <= x + 1; ++i){
    for (int j = y - 1; j <= y + 1; ++j){
      int iCheck = (i + field.Width()) % field.Width();
      int jCheck = (j + field.Height()) % field.Height();
      if (iCheck == x && jCheck == y) continue;
      count += field.SlotState(iCheck, jCheck);
    }
  }

  return count;
}

void Logic::Execute(Field& field, Game& game){
  std::vector<std::vector<bool>> newField(field.Width(), std::vector<bool>(field.Height(), 0));

  for (int i = 0; i < field.Width(); ++i){
    for (int j = 0; j < field.Height(); ++j){
      int neighborsCount = NeighborsCount(field, i, j);

      //Rules
      if (neighborsCount < 2 || neighborsCount > 3) newField[i][j] = false;
      else if (neighborsCount == 3) newField[i][j] = true;
      else newField[i][j] = field.SlotState(i, j);
    }
  }

  field.GetField() = std::move(newField);
}
