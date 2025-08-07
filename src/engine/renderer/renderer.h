#pragma once

#include"pch/pch.h"
#include"api.h"
#include"singleton.h"

#include"glm/vec4.hpp"
#include"glm/mat4x4.hpp"

namespace SGE{

//Batch renderer, batch stuff via functions and then render everything in a single draw call to the Render() member function
//To use accesss SGE::TSRenderer::Instance()
//Dont forget to specify shaders before rendering
class SGE_API Renderer{
public:
  Renderer();
  ~Renderer();

  void Render();

  //pos = bottom-left vertex pos, dimensions = width, height
  void Quad(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color = glm::vec4(1));
  void Quad(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2, glm::vec2 vertexPos3,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3);

  //pos = bottom-left vertex pos, dimensions = base width, height, triangle = right
  void Trig(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color = glm::vec4(1));
  void Trig(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2);

  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices = 30, glm::vec4 color = glm::vec4(1));
  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices, glm::vec4 centerColor, glm::vec4 circumferenceColor);
  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices, bool isRainbow);

  //Interprets first arg as source if second is false, otherwise parses a file via a file path, use SGE::GetExecDir() if needed
  void FragShader(const char* string, bool isPath = false);
  //Interprets first arg as source if second is false, otherwise parses a file via a file path, use SGE::GetExecDir() if needed
  void VertShader(const char* string, bool isPath = false);

  static const char* DefaultFragShader;
  static const char* DefaultVertShader;

  void Uniform(const char* name, int i);
  void Uniform(const char* name, float f);
  void Uniform(const char* name, glm::mat4 m);

  void Clear(glm::vec4 color = glm::vec4(0, 0, 0, 1));
};

//Type Singleton Renderer, call ::Instance() to use
using TSRenderer = Singleton<Renderer>;

}
