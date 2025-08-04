#include"shader.h"

#include"GL/glew.h"
#include"renderer/gl_utils/debug/debug.h"
#include"logger.h"

inline static unsigned int CompileShader(unsigned int type, std::string source){
  GLCall(unsigned int id = glCreateShader(type));
  const char* srcCStr = source.c_str();
  GLCall(glShaderSource(id, 1, &srcCStr, nullptr));
  GLCall(glCompileShader(id));

  //Error handling
  int result;
  GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
  //i for int
  //v for vector (array (pointer))
  if (result == GL_FALSE){
    int length;
    GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
    char* info = new char[length];

    GLCall(glGetShaderInfoLog(id, length, &length, info));
    SGE_LOG_ERROR("Compiling shader error (", (type == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader"), "): ", info);

    delete[] info;

    GLCall(glDeleteShader(id));
    return 0;
  }

  return id;
}

inline static void LinkShader(unsigned int id, unsigned int vid, unsigned int fid){
  //Attach shaders to a program
  //Tells that they are included to be linked
  GLCall(glAttachShader(id, vid));
  GLCall(glAttachShader(id, fid));

  //Link, creates an executable like a c linker
  GLCall(glLinkProgram(id));

  //Detach shaders from the program, so the linker doesnt use them anymore
  GLCall(glDetachShader(id, vid));
  GLCall(glDetachShader(id, fid));

  //Validates the program's ability to be executed, log can then be accessed
  GLCall(glValidateProgram(id));
  //Should check this after linking as well, glGetProgramiv(id, GL_LINK_STATUS, &success), glGetProgramInfoLog(id, ...)
  //Error handling
  int result;
  GLCall(glGetProgramiv(id, GL_LINK_STATUS, &result));
  if (result == GL_FALSE){
    int length;
    GLCall(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length));
    char* info = new char[length];

    GLCall(glGetProgramInfoLog(id, length, &length, info));
    SGE_LOG_ERROR("Linking shader program error: ", info);

    delete[] info;
  }

  //Delete the shaders (mark for deletion, deleted after program that uses them)
  GLCall(glDeleteShader(vid));
  GLCall(glDeleteShader(fid));
}

inline static std::string ParseFile(std::string filePath){
  SGE_LOG_INFO("Parsing Shader file path (relative): ", filePath);
  SGE_LOG_INFO("Parsing Shader file path (absolute): ", std::filesystem::absolute(filePath));
  std::fstream stream(filePath);
  SGE_LOG_INFO("Parsing Shader good state: ", stream.good());
  std::string line;
  std::stringstream shader;
  while (std::getline(stream, line)){
    shader << line << std::endl;
  }
  stream.close();
  return shader.str(); 
}

Shader::Shader()
: _id(0), _fid(0), _vid(0){
  GLCall(_id = glCreateProgram());
}

Shader::~Shader(){
  GLCall(glDeleteProgram(_id));
}

void Shader::Vert(const char* path){
  _vid = CompileShader(GL_VERTEX_SHADER, ParseFile(path).c_str());

  if (_fid != 0){
    LinkShader(_id, _vid, _fid);
    SGE_LOG_INFO("Linking program");
  }

  _locationCache.clear();
}

void Shader::Frag(const char* path){
  _fid = CompileShader(GL_FRAGMENT_SHADER, ParseFile(std::string(path)).c_str());

  if (_vid != 0){
    LinkShader(_id, _vid, _fid);
    SGE_LOG_INFO("Linking program");
  }

  _locationCache.clear();
}

void Shader::Bind() const{
  GLCall(glUseProgram(_id));
}

void Shader::Unbind() const{
  GLCall(glUseProgram(0));
}

int Shader::_GetUniformLocation(const std::string& name){
  Bind();
  if (_locationCache.find(name) != _locationCache.end())
    //Cache hit
    return _locationCache[name];

  //Cache miss
  GLCall(int location = glGetUniformLocation(_id, name.c_str()));
  _locationCache.emplace(name, location);

  if (location == -1)
    SGE_LOG_WARNING("Uniform couldn't be found, name: ", name);

  return location;
}

void Shader::SetUniform(const std::string& name, const glm::mat4& mat){
  int location = _GetUniformLocation(name);

  GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]));
  //location
  //Count
  //Transpouse, whether to convert row-major to column major, glm stores them column major
  //Address of matrix
}

void Shader::SetUniform(const std::string& name, float f0, float f1, float f2, float f3){
  int location = _GetUniformLocation(name);

  GLCall(glUniform4f(location, f0, f1, f2, f3));
}

void Shader::SetUniform(const std::string& name, int is[], int count){
  int location = _GetUniformLocation(name);

  GLCall(glUniform1iv(location, count, is));
}

void Shader::SetUniform(const std::string& name, float f0){
  int location = _GetUniformLocation(name);

  GLCall(glUniform1f(location, f0));
}

void Shader::SetUniform(const std::string& name, int i0){
  int location = _GetUniformLocation(name);

  GLCall(glUniform1i(location, i0));
}
