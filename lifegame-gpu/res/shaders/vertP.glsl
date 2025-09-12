#version 330 core

layout(location = 0) in vec4 iPos;
layout(location = 1) in vec4 iCol;

out vec4 vCol;

uniform mat4 uProj;

void main(){
  gl_Position = uProj * iPos;
  vCol = iCol;
}
