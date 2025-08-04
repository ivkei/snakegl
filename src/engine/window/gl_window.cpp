#include"window.h"

#include"GLFW/glfw3.h"

#include"pch/pch.h"
#include"logger.h"
#include"keys.h"

namespace SGE{

//Use address of window as key, when moved or copied ctor will handle the change
static std::unordered_map<const Window*, GLFWwindow*> addressToWindow;

const Window::Stats Window::Stats::Default = {"Application", 1280, 720, true};

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

static bool wasGlfwInit = false;

Window::Window(Stats stats)
: _stats(stats){

  if (!wasGlfwInit){
    if (!glfwInit()){
      const char* error;
      glfwGetError(&error);
      SGE_LOG_ERROR(error);
      exit(1);
    }
  }
  wasGlfwInit = true;

  //OpenGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

  //Switch profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Uncomment to use core profile
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); //Uncomment to use compatiblity profile

  //Unresizable
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  //Create a windowed mode window and its OpenGL context
  GLFWwindow* pWindow(glfwCreateWindow(stats.width, stats.height, stats.name, NULL, NULL));
  if (!pWindow){
    //If couldnt create a pWindow
    SGE_LOG_ERROR("Couldn't create a window");
    glfwTerminate();
    exit(1);
  }

  addressToWindow.emplace(this, pWindow);

  //Make the pWindow's context current
  glfwMakeContextCurrent(pWindow);

  //Set callbacks
  glfwSetKeyCallback(pWindow, KeyCallback);

  glViewport(0, 0, stats.width, stats.height);
}

void Window::Bind() const{
  GLFWwindow* pWindow = addressToWindow.at(this);
  glfwMakeContextCurrent(pWindow);
}

Window::~Window(){
  addressToWindow.erase(this);

  if (addressToWindow.size() == 0){
    glfwTerminate();
    wasGlfwInit = false;
  }
}

bool Window::ShouldTerminate() const{
  GLFWwindow* pWindow = addressToWindow.at(this);
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

void Window::SetKeyCallback(int key, void(*func)()){
  int glfwKey = KeyToGLFWKey(key);
  SGE_LOG_ASSERT(glfwKey != -1, "Invalid key passed to set callback");

  if (glfwKeyToFuncCallback.contains(glfwKey)) glfwKeyToFuncCallback.erase(glfwKey);
  glfwKeyToFuncCallback.emplace(glfwKey, func);
}

void Window::DeleteCallback(int key){
  int glfwKey = KeyToGLFWKey(key);
  SGE_LOG_ASSERT(glfwKey != -1, "Invalid key passed to delete callback");
  if (glfwKeyToFuncCallback.contains(glfwKey)) glfwKeyToFuncCallback.erase(glfwKey);
}

void Window::PollEvents() const{
  glfwPollEvents();
}

void Window::SwapBuffers() const{
  GLFWwindow* pWindow = addressToWindow.at(this);
  glfwSwapBuffers(pWindow);
}

void Window::SetVSync(bool value){
  glfwSwapInterval(value);
}

void Window::SetStats(Stats stats){
  GLFWwindow* pWindow = addressToWindow.at(this);
  glfwSetWindowSize(pWindow, stats.width, stats.height);
  glViewport(0, 0, stats.width, stats.height);
  glfwSetWindowTitle(pWindow, stats.name);
  glfwWindowHint(GLFW_RESIZABLE, stats.resizable);
} 

}
