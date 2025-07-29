#pragma once

#include"stdpch/stdpch.h"
#include"api.h"

#include"glm/vec4.hpp"
#include"glm/mat4x4.hpp"

namespace SGE{

//Batch renderer, batch stuff via functions and then render everything in a single draw call to the Render() member function
class SGE_API Renderer{
private:
public:
  Renderer();
  ~Renderer();

  void Render();

  //pos = bottom-left vertex pos, dimensions = width, height
  void Quad(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color = glm::vec4(1));
  void Quad(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2, glm::vec2 vertexPos3,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3);

  //pos = bottom-left vertex pos, dimensions = base width, height, triangle = isosceles
  void Trig(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color = glm::vec4(1));
  void Trig(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2);

  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices = 30, glm::vec4 color = glm::vec4(1));
  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices = 30, glm::vec4 centerColor = glm::vec4(1), glm::vec4 circumferenceColor = glm::vec4(1));
  //pos = center of the circle coordinates
  void Circle(glm::vec2 pos, float r, int vertices = 30, bool isRainbow = false);

  void FragShader(const char* path);
  void VertShader(const char* path);

  void Uniform(const char* name, int i);
  void Uniform(const char* name, float f);
  void Uniform(const char* name, glm::mat4 m);

  void Clear(glm::vec4 color = glm::vec4(0, 0, 0, 1));
};

//Type Singleton Renderer, call ::Instance() to use
using TSRenderer = Singleton<Renderer>;

}
