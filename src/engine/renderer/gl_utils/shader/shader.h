#pragma once

#include"pch/pch.h"

#include"glm/glm.hpp"

class Shader{
private:
  unsigned int _id;
  unsigned int _fid;
  unsigned int _vid;
  std::unordered_map<std::string, int> _locationCache;

  int _GetUniformLocation(const std::string& name);
public:
  Shader();
  ~Shader();

  void Frag(const char* path);
  void Vert(const char* path);
  void Bind() const;
  void Unbind() const;

  bool IsValid() const;

  //Uniforms
  void SetUniform(const std::string& name, const glm::mat4& mat);
  void SetUniform(const std::string& name, float f0, float f1, float f2, float f3);
  void SetUniform(const std::string& name, float f0);
  void SetUniform(const std::string& name, int i0);
  void SetUniform(const std::string& name, int is[], int count);
};
