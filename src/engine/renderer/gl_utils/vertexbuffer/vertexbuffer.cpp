#include"vertexbuffer.h"

#include"renderer/gl_utils/debug/debug.h"

#include"GL/glew.h"

VertexBuffer::VertexBuffer(void* pData, unsigned int size, unsigned int usage){
  GLCall(glGenBuffers(1, &_id));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
  GLCall(glBufferData(GL_ARRAY_BUFFER, size, pData, usage));
}

VertexBuffer::~VertexBuffer(){
  GLCall(glDeleteBuffers(1, &_id));
}

void VertexBuffer::Bind() const{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, _id));
}

void VertexBuffer::Unbind() const{
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
