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
  //Population is chance percentage (0%-100%) of a cell being populate
  //Everything beyond 0-100 will get clamped
  Field(int width, int height, float unitWidth, float unitHeight, float unitHorOffset, float unitVerOffset,
        glm::vec4 backgroundColor, glm::vec4 unitDividerColor, glm::vec4 cellColor,
        int population);
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
  inline bool SlotState(int x, int y) const { return _field[x][y]; };
  inline void SetField(std::vector<std::vector<bool>>&& newField) { _field = newField; };

  //Population is chance percentage (0%-100%) of a cell being populate
  //Everything beyond 0-100 will get clamped
  void Randomize(int population);
};
