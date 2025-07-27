#pragma once

namespace SGE{

extern Application* CreateApplication();

struct Application{
  Application() {}
  virtual Application() {}
  virtual void Run() {}
}

}

#define SGE_ENTRY_POINT\
  int main(){\
    SGE::Application* pApp = SGE::CreateApplication();
    pApp->Run();
    delete pApp;
  }
