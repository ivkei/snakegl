#pragma once

#include"sge_renderer/gl_utils/vertexbufferlayout.h"

class VertexArray{
private:
  unsigned int _id;
public:
  VertexArray();
  ~VertexArray();

  void AddLayout(const VertexBufferLayout& layout) const;

  void Bind() const;
  void Unbind() const;
};
