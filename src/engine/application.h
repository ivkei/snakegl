#pragma once

namespace SGE{

struct Application{
  Application() {}
  virtual ~Application() {}
  virtual void Run() {}
};

extern Application* CreateApplication(int argc, char** argv);

}

#define SGE_ENTRY_POINT\
  int main(int argc, char** argv){\
    SGE_LOG_INFO("Main starts execution");\
    SGE::Application* pApp = SGE::CreateApplication(argc, argv);\
    pApp->Run();\
    delete pApp;\
  }
