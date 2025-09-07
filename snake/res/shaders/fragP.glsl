#version 330 core

layout(location = 0) out vec4 oCol;

in vec4 vCol;

void main(){
  oCol = vCol;
}
