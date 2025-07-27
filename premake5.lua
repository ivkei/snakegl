workspace "snakegl"
architecture "x64"
configurations
{
  "Debug",
  "Release"
}

include "vendors/glfw-3.4/"
include "vendors/glew-2.2.0/"

project "snakegl"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"

  targetdir("build/bin/")
  objdir("build/obj/")
  location("build/")

  files
  {
    "src/**.h",
    "src/**.cpp",
  }

  runtimeResDir = path.getrelative("%{prj.location}/build/bin/", "%{prj.location}/build/res/")

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
    "GLEW_STATIC",
    "RES_DIR=\"" .. runtimeResDir .. "/\"",
  }

  links
  {
    "glfw",
    "glew",
  }

  includedirs
  {
    "vendors/glfw-3.4/include",
    "vendors/glew-2.2.0/include",
    "vendors/glm-1.0.1",
    "src/",
  }

  compiletimeResDir = path.getabsolute("%{prj.location}/res/")
  compiletimeBuildDir = path.getabsolute("%{prj.location}/build/")

  postbuildcommands{
    "{COPYDIR} " .. compiletimeResDir .. "/ " .. compiletimeBuildDir .. "/"
  }

  pchheader "src/pch/pch.h"
  pchsource "src/pch/pch.cpp"

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
    kind "ConsoleApp"
    runtime "Debug"
    symbols "on"
    defines {
      "_SNAKEGL_DEBUG",
      "_SNAKEGL_ENABLE_LOGGING",
      "_SNAKEGL_ENABLE_ASSERTS"
    }

filter "configurations:Release"
    kind "WindowedApp"
    runtime "Release"
    optimize "on"
    defines "_SNAKEGL_RELEASE"
    postbuildcommands{
      "{MKDIR} " .. compiletimeBuildDir .. "/snakegl",
      "{COPYDIR} " .. compiletimeResDir .. "/ " .. compiletimeBuildDir .. "/snakegl",
      "{COPYDIR} " .. compiletimeBuildDir .. "/bin " .. compiletimeBuildDir .. "/snakegl"
    }
