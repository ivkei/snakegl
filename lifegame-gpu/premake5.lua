workspace "lifegame"
architecture "x64"
configurations
{
  "Debug",
  "Release"
}

include "../vendors/glfw-3.4/"
include "../vendors/glew-2.2.0/"
include "../sge/"

project "lifegame-gpu"
  language "C++"
  cppdialect "C++23"
  staticruntime "On"

  targetdir("../build/bin/")
  objdir("../build/obj/")
  location("../build/")

  filter "system:windows"
    defines
    {
      "_SNAKEGL_WINDOWS",
    }
    runtimeResDir = path.getrelative("../build/bin/", "../build/res/")
    compiletimeResDir = path.getabsolute("res/")
    compiletimeBuildDir = path.getabsolute("../build/")
    execPath = path.join(compiletimeBuildDir, "bin", "%{prj.name}.exe")
    engineDLLPath = path.join(compiletimeBuildDir, "bin", "libsnakeglengine.dll")

  filter "system:linux"
    defines
    {
      "_SNAKEGL_LINUX",
    }
    runtimeResDir = path.getrelative("%{prj.location}/../build/bin/", "%{prj.location}/../build/res/")
    compiletimeResDir = path.getabsolute("%{prj.location}/res/")
    compiletimeBuildDir = path.getabsolute("%{prj.location}/../build/")
    execPath = path.join(compiletimeBuildDir, "bin", "%{prj.name}")
    engineDLLPath = path.join(compiletimeBuildDir, "bin", "libsnakeglengine.so")

  files
  {
    "src/**.h",
    "src/**.cpp",
  }

  includedirs{
    "src/",
    "../vendors/glm-1.0.1",
    "../sge/src/", -- For sge.h
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
    releaseDirName = "%{prj.name}_release"
    postbuildcommands{
      "{MKDIR} " .. path.join(compiletimeBuildDir, releaseDirName) .. "",
      "{COPYDIR} \"" .. compiletimeResDir .. "\" \"" .. path.join(compiletimeBuildDir, releaseDirName) .. "\"",
      "{MKDIR} " .. path.join(compiletimeBuildDir, releaseDirName, "bin") .. "",
      "{COPYFILE} \"" .. execPath .. "\" \"" .. path.join(compiletimeBuildDir, releaseDirName, "bin") .. "\"",
      "{COPYFILE} \"" .. engineDLLPath .. "\" \"" .. path.join(compiletimeBuildDir, releaseDirName, "bin") .. "\"",
    }
