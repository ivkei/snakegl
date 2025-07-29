#pragma once

#include"renderer/gl_utils/vertexbuffer/vertexbuffer.h"
#include"renderer/gl_utils/vertexbufferlayout.h"

class VertexArray{
private:
  unsigned int _id;
public:
  VertexArray();
  ~VertexArray();

  //This function assumes that a vertex buffer is already bound
  void AddBuffer(const VertexBufferLayout& layout) const;
  void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

  void Bind() const;
  void Unbind() const;
};
