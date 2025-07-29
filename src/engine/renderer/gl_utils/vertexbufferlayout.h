#pragma once

#include"GL/glew.h"

#include"renderer/gl_utils/debug/debug.h"
#include"stdpch/stdpch.h"
#include"logger.h"

struct VertexBufferLayoutElement{
  unsigned int count;
  unsigned int size;
  unsigned int type;
  bool normalize;
};

struct _GLType{
  unsigned int type;
  unsigned int size;
};
//This can be refactored into a template specialization thing
template<class T>
static _GLType TypeToGLType(){
  const auto& type = typeid(T);
  _GLType res;

  if (type == typeid(float)){
    res.type = GL_FLOAT;
    res.size = sizeof(float);

  } else if (type == typeid(unsigned int)){
    res.type = GL_UNSIGNED_INT;
    res.size = sizeof(unsigned int);

  } else if (type == typeid(unsigned char)){
    res.type = GL_UNSIGNED_BYTE;
    res.size = sizeof(unsigned char);

  } else{
    SGE_LOG_ERROR("Unknown type passed to TypeToGLType");
  }

  return res;
}

class VertexBufferLayout{
private:
  std::vector<VertexBufferLayoutElement> _elements;
  unsigned int _stride;
public:
  VertexBufferLayout() : _stride{0} {}
  ~VertexBufferLayout() = default;

  template<class T>
  void Push(unsigned int count, bool normalized = false){
    _GLType type = TypeToGLType<T>();

    auto size = type.size * count;
    _elements.emplace_back(count, size, type.type, normalized);
    _stride += size;
  }

  inline const std::vector<VertexBufferLayoutElement>& GetElements() const { return _elements; }
  inline unsigned int GetStride() const { return _stride; }
};
