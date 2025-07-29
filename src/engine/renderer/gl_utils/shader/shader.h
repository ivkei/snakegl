#pragma once

#include"stdpch/stdpch.h"

#include"glm/glm.hpp"

class Shader{
private:
  unsigned int _id;
  std::string _fFilepath;
  std::string _vFilepath;
  std::unordered_map<std::string, int> _locationCache;

  int _GetUniformLocation(const std::string& name);

public:
  Shader(const std::string& vFilepath, const std::string& fFilePath);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  //Uniforms
  void SetUniform(const std::string& name, const glm::mat4& mat);
  void SetUniform(const std::string& name, float f0, float f1, float f2, float f3);
  void SetUniform(const std::string& name, float f0);
  void SetUniform(const std::string& name, int i0);
  void SetUniform(const std::string& name, int is[], int count);
};
