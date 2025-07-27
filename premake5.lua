workspace "snakegl"
architecture "x64"
configurations
{
  "Debug",
  "Release"
}

include "vendors/glfw-3.4/"
include "vendors/glew-2.2.0/"

runtimeResDir = path.getrelative("%{prj.location}/build/bin/", "%{prj.location}/build/res/")
compiletimeResDir = path.getabsolute("%{prj.location}/res/")
compiletimeBuildDir = path.getabsolute("%{prj.location}/build/")

pchheader "src/stdpch/stdpch.h"
pchsource "src/stdpch/stdpch.cpp"

project "snakeglgame"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"

  targetdir("build/bin/")
  objdir("build/obj/")
  location("build/")

  files
  {
    "src/game/**.h",
    "src/game/**.cpp",
  }

  includedirs{
    "src/game",
    "src/",
    "vendors/glm-1.0.1",
    "src/engine",
  }

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
    "RES_DIR=\"" .. runtimeResDir .. "/\"",
    "_SNAKEGL_GAME",
  }

  postbuildcommands{
    "{COPYDIR} " .. compiletimeResDir .. "/ " .. compiletimeBuildDir .. "/"
  }

  links{
    "snakeglengine"
  }

  filter "system:windows"
    defines
    {
      "_SNAKEGL_WINDOWS",
    }

  filter "system:linux"
    defines
    {
      "_SNAKEGL_LINUX",
    }

filter "configurations:Debug"
    kind "ConsoleApp"
    runtime "Debug"
    symbols "on"
    defines {
      "_SNAKEGL_DEBUG",
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

project "snakeglengine"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"
  kind "SharedLib"
  pic "on"

  targetdir("build/bin/")
  objdir("build/obj/")
  location("build/")

  files
  {
    "src/engine/**.h",
    "src/engine/**.cpp",
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
    "vendors/glfw-3.4/include",
    "vendors/glew-2.2.0/include",
    "vendors/glm-1.0.1",
    "src/engine",
    "src/",
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
