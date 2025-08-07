#pragma once

#include<unordered_map>
#include<string>

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

  //Interprets first arg as source if second is false, otherwise parses a file via a file path, use SGE::GetExecDir() if needed
  void Frag(const char* string, bool isPath = false);
  //Interprets first arg as source if second is false, otherwise parses a file via a file path, use SGE::GetExecDir() if needed
  void Vert(const char* string, bool isPath = false);
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
