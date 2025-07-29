#include"vertexarray.h"

#include"renderer/gl_utils/debug/debug.h"

#include"GL/glew.h"

VertexArray::VertexArray(){
  GLCall(glGenVertexArrays(1, &_id));
}

VertexArray::~VertexArray(){
  GLCall(glDeleteVertexArrays(1, &_id));
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const{
  this->Bind();

  vbo.Bind();

  const auto& elems = layout.GetElements();
  unsigned int stride = layout.GetStride();

  int n = elems.size();
  int offset = 0;
  for (int i = 0; i < n; ++i){
    const auto& elem = elems[i];

    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalize, stride, (const void*)offset));

    offset += elem.size;
  }
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout) const{
  this->Bind();

  const auto& elems = layout.GetElements();
  unsigned int stride = layout.GetStride();

  int n = elems.size();
  int offset = 0;
  for (int i = 0; i < n; ++i){
    const auto& elem = elems[i];

    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i, elem.count, elem.type, elem.normalize, stride, (const void*)offset));

    offset += elem.size;
  }
}

void VertexArray::Bind() const{
  GLCall(glBindVertexArray(_id));
}

void VertexArray::Unbind() const{
  GLCall(glBindVertexArray(0));
}
