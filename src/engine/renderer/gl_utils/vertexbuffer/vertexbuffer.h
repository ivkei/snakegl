#pragma once

#include"GL/glew.h"

class VertexBuffer{
private:
  unsigned int _id;
public:
  //Pass nullptr to data to not buffer data, flush then has to be used
  VertexBuffer(void* pData, unsigned int size, unsigned int usage = GL_STATIC_DRAW);
  //If this function is in the same scope as glfwTerminate(),
  //Or called after, glGetError will continuously return OpenGL error
  //Which is not good
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};
