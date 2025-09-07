#include"sge.h"

#include"gameapplication/gameapplication.h"

extern SGE::Application* SGE::CreateApplication(){
  return new GameApplication();
}

SGE_ENTRY_POINT

//TODO(kei): Update readme
//TODO(kei): Fix not launching
