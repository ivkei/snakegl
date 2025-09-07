project "snakeglengine"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"
  kind "SharedLib"
  pic "on"

  pchheader "src/sge_pch/pch.h"
  pchsource "src/sge_pch/pch.cpp"

  targetdir("../build/bin/")
  objdir("../build/obj/")
  location("../build/")

  files
  {
    "src/**.h",
    "src/**.cpp",
  }

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
    "GLEW_STATIC",
    "_SNAKEGL_ENGINE",
  }

  links
  {
    "glfw",
    "glew",
  }

  includedirs
  {
    "../vendors/glfw-3.4/include",
    "../vendors/glew-2.2.0/include",
    "../vendors/glm-1.0.1",
    "src/",
    "./", -- Root directory for pch
  }

  filter "system:windows"
    defines
    {
      "_GLFW_WIN32",
      "_SNAKEGL_WINDOWS",
    }
    links
    {
      "OpenGL32",
      "Gdi32"
    }

  filter "system:linux"
    defines
    {
      "_GLFW_X11",
      "_SNAKEGL_LINUX",
    }
    links
    {
      "GL",
      "GLU",
      "pthread",
      "Xrandr",
      "Xcursor",
      "Xi",
      "X11",
      "dl",
    }

filter "configurations:Debug"
    runtime "Debug"
    symbols "on"
    defines "_SNAKEGL_DEBUG"

filter "configurations:Release"
    runtime "Release"
    optimize "on"
    defines "_SNAKEGL_RELEASE"
