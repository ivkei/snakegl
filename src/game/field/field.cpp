#include"field.h"

#include"engine/sge.h"

Field::Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset, glm::vec4 backgroundColor, glm::vec4 unitDividerColor)
: _width(width), _height(height), _unitWidth(unitWidth), _unitHeight(unitHeight), _unitHorOffset(unitHorOffset), _unitVerOffset(unitVerOffset), _backgroundColor(backgroundColor), _unitDividerColor(unitDividerColor){
}

Field::~Field(){
}

void Field::Draw() const{
  SGE::TSRenderer::Instance()->Clear(UnitDividerColor());
  for (int i = 0; i < Width(); ++i){
    for (int j = 0; j < Height(); ++j){
      SGE::TSRenderer::Instance()->Quad(glm::vec2(i + UnitHorOffset(), j + UnitVerOffset()), glm::vec2(UnitWidth(), UnitHeight()), BackgroundColor());
    }
  }
}
