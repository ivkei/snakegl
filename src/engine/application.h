#pragma once

namespace SGE{

struct Application{
  Application() {}
  virtual ~Application() {}
  virtual void Run() {}
};

//TODO(kei): remove this??
extern Application* CreateApplication();

}

//TODO(kei): auto pApp = CreateApplication
//TODO(kei): Make a default application, define something to use CreateApplicatin made by client?
//TODO(kei): Default application will use default Game, otherwise Game will just not be used
//TODO(kei): This way we can get rid of vtables and possibly speed up function execution??
#define SGE_ENTRY_POINT\
  int main(){\
    SGE::Application* pApp = SGE::CreateApplication();\
    pApp->Run();\
    delete pApp;\
  }
