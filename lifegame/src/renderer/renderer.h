#pragma once

#include"field/field.h"

#include"sge.h"

class Renderer{
private:
public:
  void SetupShadersAndCoord(Field& field);
  void Render(Field& field);
};

using TSRenderer = SGE::Singleton<Renderer>;
