#include"field.h"

#include"engine/sge.h"

Field::Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset, glm::vec4 backgroundColor, glm::vec4 unitDividerColor)
: _width(width), _height(height), _unitWidth(unitWidth), _unitHeight(unitHeight), _unitHorOffset(unitHorOffset), _unitVerOffset(unitVerOffset), _backgroundColor(backgroundColor), _unitDividerColor(unitDividerColor){
}

Field::~Field(){
}
