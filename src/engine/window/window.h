#pragma once

#include"api.h"

namespace SGE{

class SGE_API Window final{
public:
  struct SGE_API Stats{
    const char* name;
    int width;
    int height;

    const static Stats Default;
  };

private:
  Stats _stats;

public:
  Window(Stats stats = Stats::Default);
  ~Window();

  bool ShouldTerminate() const;
  void SetKeyCallback(int key, void(*func)());
  void DeleteCallback(int key);
  void PollEvents() const;
  void SwapBuffers() const;
  //Binds the window's context for further rendering inside
  //No need to call if working on 1 thread or have 1 window only
  void Bind() const;

  inline int Width() const { return _stats.width; }
  inline int Height() const { return _stats.height; }
  inline const char* Name() const { return _stats.name; }

  void SetVSync(bool value);

  void SetStats(Stats stats);
};

}
