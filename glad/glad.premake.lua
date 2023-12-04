project "Glad"
    kind "StaticLib"
    language "C"
    targetdir "../lib/%{cfg.buildcfg}"

    includedirs {
        "/usr/include",
        "include"
    }

    files {
        "include/**.h",
        "src/*.c"
    }

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "RELEASE" }
      optimize "On"
