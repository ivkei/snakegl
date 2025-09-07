#pragma once

void GLEnableAutoLogging();
void GLClearErrors();
void GLLogErrors(const char* name, const char* file, int line);

#define GLCall(x)\
  GLClearErrors();\
  x;\
  GLLogErrors(#x, __FILE__, __LINE__)
