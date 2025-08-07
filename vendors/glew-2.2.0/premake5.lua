project "glew"
  kind "StaticLib"
  language "C"
  staticruntime "on"
  pic "on"

  targetdir("../../build/bin/")
  objdir("../../build/obj/")

  files
  {
    "src/glew.c",
    "include/**.h"
  }

  includedirs
  {
    "include"
  }

  defines
  {
    "GLEW_STATIC",
    "_CRT_SECURE_NO_WARNINGS"
  }

  filter "configurations:Debug"
      runtime "Debug"
      symbols "on"

  filter "configurations:Release"
      runtime "Release"
      optimize "on"
