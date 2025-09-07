workspace "snakegl"
architecture "x64"
configurations
{
  "Debug",
  "Release"
}

include "../vendors/glfw-3.4/"
include "../vendors/glew-2.2.0/"
include "../engine/"

project "snakegame"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"

  targetdir("../build/snakegame/bin/")
  objdir("../build/snakegame/obj/")
  location("../build/snakegame/")

  filter "system:windows"
    defines
    {
      "_SNAKEGL_WINDOWS",
    }
    runtimeResDir = path.getrelative("../build/snakegame/bin/", "../build/snakegame/res/")
    compiletimeResDir = path.getabsolute("res/")
    compiletimeBuildDir = path.getabsolute("../build/snakegame/")
    execPath = path.join(compiletimeBuildDir, "bin", "snakegame.exe")
    engineDLLPath = path.join(compiletimeBuildDir, "bin", "libsnakeglengine.dll")

  filter "system:linux"
    defines
    {
      "_SNAKEGL_LINUX",
    }
    runtimeResDir = path.getrelative("%{prj.location}/../build/snakegame/bin/", "%{prj.location}/../build/snakegame/res/")
    compiletimeResDir = path.getabsolute("%{prj.location}/res/")
    compiletimeBuildDir = path.getabsolute("%{prj.location}/../build/snakegame/")
    execPath = path.join(compiletimeBuildDir, "bin", "snakegame")
    engineDLLPath = path.join(compiletimeBuildDir, "bin", "libsnakeglengine.so")

  files
  {
    "src/**.h",
    "src/**.cpp",
  }

  includedirs{
    "src/",
    "../vendors/glm-1.0.1",
    "../engine/include/",
  }

  defines
  {
    "_CRT_SECURE_NO_WARNINGS",
    "RES_DIR=\"" .. runtimeResDir .. "/\"",
    "_SNAKEGL_GAME",
  }

  postbuildcommands{
    "{COPYDIR} \"" .. compiletimeResDir .. "\" \"" .. compiletimeBuildDir .. "\""
  }

  links{
    "snakeglengine"
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
      "{MKDIR} " .. path.join(compiletimeBuildDir, "snakegamerelease") .. "",
      "{COPYDIR} \"" .. compiletimeResDir .. "\" \"" .. path.join(compiletimeBuildDir, "snakegamerelease") .. "\"",
      "{MKDIR} " .. path.join(compiletimeBuildDir, "snakegamerelease", "bin") .. "",
      "{COPYFILE} \"" .. execPath .. "\" \"" .. path.join(compiletimeBuildDir, "snakegamerelease", "bin") .. "\"",
      "{COPYFILE} \"" .. engineDLLPath .. "\" \"" .. path.join(compiletimeBuildDir, "snakegamerelease", "bin") .. "\"",
    }
