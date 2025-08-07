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
    SGE_LOG_INFO("Main starts execution");\
    SGE::Application* pApp = SGE::CreateApplication();\
    pApp->Run();\
    delete pApp;\
    return 0;\
  }
