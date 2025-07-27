#include"renderer.h"

#include"GL/glew.h"

namespace SGE{

Renderer::Renderer(){
}

Renderer::~Renderer(){
}

void Renderer::Render(){
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
