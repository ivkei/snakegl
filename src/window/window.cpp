#include"window.h"

#include"GLFW/glfw3.h"

#include"pch/pch.h"
#include"utils.h"

static std::unordered_map<int, GLFWwindow*> idToWindow;

const Window::Stats Window::Stats::Default = {"Application", 1280, 720};

static std::unordered_map<int, void(*)()> glfwKeyToFuncCallback;
void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods){
  if (action == GLFW_PRESS){
    try{
      glfwKeyToFuncCallback.at(key)();
    }
    catch (std::out_of_range){ //Didnt find a callback fot the key pressed
      //Do nothing
    }
  }
}

Window::Window(Stats stats)
: _windowID(0){
  srand(time(NULL));
  while (idToWindow.contains(_windowID)){
    _windowID = rand();
  }

  if (!glfwInit()){
    const char* error;
    glfwGetError(&error);
    LOG_ERROR(error);
    exit(1);
  }

  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  //Switch profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Uncomment to use core profile
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //Uncomment to use compatiblity profile

  //Create a windowed mode window and its OpenGL context
  GLFWwindow* pWindow(glfwCreateWindow(stats.width, stats.height, stats.name, NULL, NULL));
  if (!pWindow){
    //If couldnt create a pWindow
    LOG_ERROR("Couldn't create a window");
    glfwTerminate();
    exit(1);
  }

  idToWindow.emplace(_windowID, pWindow);

  //Make the pWindow's context current
  glfwMakeContextCurrent(pWindow);

  //Set callbacks
  glfwSetKeyCallback(pWindow, KeyCallback);
}

Window::~Window(){
  idToWindow.erase(_windowID);

  if (idToWindow.size() == 0){
    glfwTerminate();
  }
}

bool Window::ShouldTerminate() const{
  GLFWwindow* pWindow = idToWindow.at(_windowID);
  return glfwWindowShouldClose(pWindow);
}

//-1 if invalid key
int KeyToGLFWKey(int key){
  switch (key){
    case SNAKEGL_KEY_W: return GLFW_KEY_W;
    case SNAKEGL_KEY_A: return GLFW_KEY_A;
    case SNAKEGL_KEY_S: return GLFW_KEY_S;
    case SNAKEGL_KEY_D: return GLFW_KEY_D;
    case SNAKEGL_KEY_SPC: return GLFW_KEY_SPACE;
    case SNAKEGL_KEY_ESC: return GLFW_KEY_ESCAPE;

    default: return -1;
  }
}

void Window::SetCallback(int key, void(*func)()){
  int glfwKey = KeyToGLFWKey(key);
  ASSERT(glfwKey != -1);

  if (glfwKeyToFuncCallback.contains(glfwKey)) glfwKeyToFuncCallback.erase(glfwKey);
  glfwKeyToFuncCallback.emplace(glfwKey, func);
}

void Window::DeleteCallback(int key){
  int glfwKey = KeyToGLFWKey(key);
  ASSERT(glfwKey != -1);
  if (glfwKeyToFuncCallback.contains(glfwKey)) glfwKeyToFuncCallback.erase(glfwKey);
}

void Window::PollEvents() const{
  glfwPollEvents();
}

void Window::SwapBuffers() const{
  GLFWwindow* pWindow = idToWindow.at(_windowID);
  glfwSwapBuffers(pWindow);
}
