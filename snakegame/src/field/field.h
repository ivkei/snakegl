#pragma once

#include"glm/vec4.hpp"

#include<vector>

class Field{
private:
  int _width;
  int _height;
  float _unitWidth;
  float _unitHeight;
  float _unitHorOffset;
  float _unitVerOffset;
  glm::vec4 _backgroundColor;
  glm::vec4 _unitDividerColor;
  glm::vec4 _cellColor;

  std::vector<std::vector<bool>> _field;
public:
  //population - amount of population per field, within 255, where 255 is every cell is populate, 0 is every cell is dead
  Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset,
        glm::vec4 backgroundColor, glm::vec4 unitDividerColor, glm::vec4 cellColor,
        char population);
  ~Field();

  inline int Width() const { return _width; }
  inline int Height() const { return _height; }
  inline float UnitWidth() const { return _unitWidth; }
  inline float UnitHeight() const { return _unitHeight; }
  inline float UnitHorOffset() const { return _unitHorOffset; }
  inline float UnitVerOffset() const { return _unitVerOffset; }
  inline glm::vec4 BackgroundColor() const { return _backgroundColor; }
  inline glm::vec4 UnitDividerColor() const { return _unitDividerColor; }
  inline glm::vec4 CellColor() const { return _cellColor; }
  inline glm::vec4 SlotColor(int x, int y) const { return (_field[x][y] ? _cellColor : _backgroundColor); };

  void Update();
};
