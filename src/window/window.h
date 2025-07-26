#pragma once

class Window final{
private:
  int _windowID;
public:
  struct Stats{
    const char* name;
    int width;
    int height;

    const static Stats Default;
  };

  Window(Stats stats = Stats::Default);
  ~Window();

  bool ShouldTerminate() const;
  void SetCallback(int key, void(*func)());
  void DeleteCallback(int key);
  void PollEvents() const;
  void SwapBuffers() const;
};
