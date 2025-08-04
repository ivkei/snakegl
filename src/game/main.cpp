#include"engine/sge.h"

#include"gameapplication/gameapplication.h"

extern SGE::Application* SGE::CreateApplication(int argc, char** argv){
  return new GameApplication(argv[0]);
}

SGE_ENTRY_POINT
