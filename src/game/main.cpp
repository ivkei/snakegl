#include"engine/sge.h"

#include"gameapplication/gameapplication.h"

SGE::Application* SGE::CreateApplication(){
  return new GameApplication();
}

SGE_ENTRY_POINT
