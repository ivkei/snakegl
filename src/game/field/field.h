#pragma once

#include"glm/vec4.hpp"

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
public:
  Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset, glm::vec4 backgroundColor, glm::vec4 unitDividerColor);
  ~Field();

  inline int Width() const { return _width; }
  inline int Height() const { return _height; }
  inline float UnitWidth() const { return _unitWidth; }
  inline float UnitHeight() const { return _unitHeight; }
  inline float UnitHorOffset() const { return _unitHorOffset; }
  inline float UnitVerOffset() const { return _unitVerOffset; }
  inline glm::vec4 BackgroundColor() const { return _backgroundColor; }
  inline glm::vec4 UnitDividerColor() const { return _unitDividerColor; }

  //Clears via renderer, no need to clear
  void Draw() const;
};
