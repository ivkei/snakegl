#include"shader.h"

#include"GL/glew.h"
#include"renderer/gl_utils/debug/debug.h"

inline static unsigned int _CompileShader(unsigned int type, const std::string& source){
  unsigned int id = glCreateShader(type);
  const char* srcCStr = source.c_str();
  glShaderSource(id, 1, &srcCStr, nullptr);
  glCompileShader(id);

  //Error handling
  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  //i for int
  //v for vector (array (pointer))
  if (result == GL_FALSE){
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* info = new char[length];

    glGetShaderInfoLog(id, length, &length, info);
    std::cout << "\033[31m" << info << "\033[0m" << std::endl;

    delete[] info;

    glDeleteShader(id);
    return 0;
  }

  return id;
}

inline static unsigned int _CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
  auto program = glCreateProgram();
  auto vs = _CompileShader(GL_VERTEX_SHADER, vertexShader);
  auto fs = _CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  //Attach shaders to a program
  //Tells that they are included to be linked
  glAttachShader(program, vs);
  glAttachShader(program, fs);

  //Link, creates an executable like a c linker
  glLinkProgram(program);

  //Detach shaders from the program, so the linker doesnt use them anymore
  glDetachShader(program, vs);
  glDetachShader(program, fs);

  //Validates the program's ability to be executed, log can then be accessed
  GLCall(glValidateProgram(program));

  //Delete the shaders (mark for deletion, deleted after program that uses them)
  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

inline static auto _ParseFile(std::string& filePath){
  std::fstream stream(filePath);
  std::string line;
  std::stringstream shader;
  while (std::getline(stream, line)){
    shader << line << std::endl;
  }
  stream.close();
  return shader.str(); 
}


Shader::Shader(const std::string& vFilepath, const std::string& fFilepath)
: _id(0), _vFilepath(vFilepath), _fFilepath(fFilepath){

  std::string vSource = _ParseFile(_vFilepath);
  std::string fSource = _ParseFile(_fFilepath);

  _id = _CreateShader(vSource, fSource);
}

Shader::~Shader(){
  GLCall(glDeleteProgram(_id));
}

void Shader::Bind() const{
  GLCall(glUseProgram(_id));
}

void Shader::Unbind() const{
  GLCall(glUseProgram(0));
}

int Shader::_GetUniformLocation(const std::string& name){
  if (_locationCache.find(name) != _locationCache.end())
    //Cache hit
    return _locationCache[name];

  //Cache miss
  GLCall(int location = glGetUniformLocation(_id, name.c_str()));
  _locationCache.emplace(name, location);

  if (location == -1)
    std::cout << "\033[32m" << "[Warning] The uniform " << '\"' << name << '\"' << " couldnt be found!" << "\033[0m" << std::endl;

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
