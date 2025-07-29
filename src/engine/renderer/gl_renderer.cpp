#include"renderer.h"

#include"GL/glew.h"

#include"engine/sge.h"
#include"gl_utils/debug/debug.h"
#include"logger.h"

namespace SGE{

Renderer::Renderer(){
  //Init glew, after make context
  auto err = glewInit();
  if (err != GLEW_OK){
    SGE_LOG_ERROR("Failed to init glew: ", glewGetErrorString(err));
  }

  //Add error handling
  GLEnableAutoLogging();

  //Set blending
  //                 Take the alpha Find difference between in and one
  GLCall(glBlendFunc(GL_SRC_ALPHA,  GL_ONE_MINUS_SRC_ALPHA));
  GLCall(glEnable(GL_BLEND));
}

Renderer::~Renderer(){
}

void Renderer::Render(){
  //TODO(kei): implement this file
  //TODO(kei): probably modify the gl_utils to be able to rellocate the buffer, index buffer will generate indices, and all the requests are anyways can be made by triangles
}

void Renderer::Quad(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color){
}

void Renderer::Quad(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2, glm::vec2 vertexPos3,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3){
}

void Renderer::Trig(glm::vec2 pos, glm::vec2 dimensions, glm::vec4 color){
}

void Renderer::Trig(glm::vec2 vertexPos0, glm::vec2 vertexPos1, glm::vec2 vertexPos2,
            glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2){
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, glm::vec4 color){
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, glm::vec4 centerColor, glm::vec4 circumferenceColor){
}

void Renderer::Circle(glm::vec2 pos, float r, int vertices, bool isRainbow){
}

void Renderer::FragShader(const char* path){
}

void Renderer::VertShader(const char* path){
}

void Renderer::Uniform(const char* name, int i){
}

void Renderer::Uniform(const char* name, float f){
}

void Renderer::Uniform(const char* name, glm::mat4 m){
}

void Renderer::Clear(glm::vec4 color){
}

}
