#include"indexbuffer.h"

#include"renderer/gl_utils/debug/debug.h"
#include"GL/glew.h"

IndexBuffer::IndexBuffer(const unsigned int* pData, unsigned int count)
: _count{count} {
  GLCall(glGenBuffers(1, &_id));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), pData, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer(){
  GLCall(glDeleteBuffers(1, &_id));
}

void IndexBuffer::Bind() const{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id));
}

void IndexBuffer::Unbind() const{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
