#include"field.h"

#include<random>
#include<ctime>

#include"sge.h"

static bool IsPopulate(unsigned char population){
  return (rand() % 255) < (int)population;
}

Field::Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset,
             glm::vec4 backgroundColor, glm::vec4 unitDividerColor, glm::vec4 cellColor,
             unsigned char population)
: _width(width), _height(height), _unitWidth(unitWidth), _unitHeight(unitHeight), _unitHorOffset(unitHorOffset), _unitVerOffset(unitVerOffset),
  _backgroundColor(backgroundColor), _unitDividerColor(unitDividerColor), _cellColor(cellColor),
  _field(std::vector<std::vector<bool>>(width, std::vector<bool>(height, 0))){

  srand(time(NULL));

  for (int i = 0; i < width; ++i){
    for (int j = 0; j < height; ++j){
      bool isPopulate = IsPopulate(population);
      _field[i][j] = isPopulate;
    }
  }
}

static int NeighborsCount(std::vector<std::vector<bool>>& field, int x, int y){
  int count = 0;

  for (int i = x - 1; i <= x + 1; ++i){
    for (int j = y - 1; j <= y + 1; ++j){
      int iCheck = i % field.size();
      int jCheck = j % field[0].size();
      if (iCheck == x && jCheck == y) continue;
      count += field[iCheck][jCheck];
    }
  }

  return count;
}

void Field::Update(){
  std::vector<std::vector<bool>> newField(_width, std::vector<bool>(_height, 0));

  for (int i = 0; i < _width; ++i){
    for (int j = 0; j < _height; ++j){
      int neighborsCount = NeighborsCount(_field, i, j);

      //Rules
      if (neighborsCount < 2 || neighborsCount > 3) newField[i][j] = false;
      else if (neighborsCount == 3) newField[i][j] = true;
      else newField[i][j] = _field[i][j];
    }
  }

  _field = std::move(newField);
}

Field::~Field(){
}
