#pragma once

namespace SGE{

struct Application{
  Application() {}
  virtual ~Application() {}
  virtual void Run() {}
};

extern Application* CreateApplication();

}

#define SGE_ENTRY_POINT\
  int main(){\
    SGE::Application* pApp = SGE::CreateApplication();\
    pApp->Run();\
    delete pApp;\
  }
