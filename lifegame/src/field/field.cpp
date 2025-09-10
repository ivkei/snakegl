#include"field.h"

#include<random>
#include<ctime>

#include"sge.h"

Field::Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset,
             glm::vec4 backgroundColor, glm::vec4 unitDividerColor, glm::vec4 cellColor,
             int population)
: _width(width), _height(height), _unitWidth(unitWidth), _unitHeight(unitHeight), _unitHorOffset(unitHorOffset), _unitVerOffset(unitVerOffset),
  _backgroundColor(backgroundColor), _unitDividerColor(unitDividerColor), _cellColor(cellColor),
  _field(std::vector<std::vector<bool>>(width, std::vector<bool>(height, 0))){
  Randomize(population);
}

static bool IsPopulate(unsigned char population){
  return (rand() % 100) < (int)population;
}

void Field::Randomize(int population){
  srand(time(NULL));

  for (int i = 0; i < _width; ++i){
    for (int j = 0; j < _height; ++j){
      bool isPopulate = IsPopulate(population);
      _field[i][j] = isPopulate;
    }
  }
}

Field::~Field(){
}
