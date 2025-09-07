#include"sge.h"

#include"application/application.h"

extern SGE::Application* SGE::CreateApplication(){
  return new Application();
}

SGE_ENTRY_POINT
