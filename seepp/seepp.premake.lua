project "SeePP"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    toolset("clang")
    targetdir "../bin/%{cfg.buildcfg}"

    includedirs {
        "../glad/include",
        "src"
    }

    files { "src/*.h", "src/*.cpp" }

    links {
        "Glad",
        "glfw",
        "dl"
    }

    filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"
