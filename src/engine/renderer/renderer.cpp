#include"renderer.h"

namespace SGE{

Renderer::Renderer(){
}

Renderer::~Renderer(){
}

void Renderer::Render(){
}

void Renderer::Quad(glm::vec4 color = glm::vec4(1)){
}

void Renderer::Trig(glm::vec4 color = glm::vec4(1)){
}

void Renderer::Quad(glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2, glm::vec4 vertexColor3){
}

void Renderer::Trig(glm::vec4 vertexColor0, glm::vec4 vertexColor1, glm::vec4 vertexColor2){
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

void Renderer::Clear(glm::vec4 color = glm::vec4(0, 0, 0, 1)){
}

}
