#include"engine/sge.h"

#include"gameapplication/gameapplication.h"

extern SGE::Application* SGE::CreateApplication(){
  return new GameApplication();
}

SGE_ENTRY_POINT

//TODO(kei): Refactor game part
//View takes necessary stuff for drawing??
