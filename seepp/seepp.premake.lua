project "SeePP"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    toolset("clang")
    targetdir "../bin/%{cfg.buildcfg}"

    includedirs {
        "../glad/include",
        "src",
        "vendor"
    }

    files { "src/*.h", "src/*.cpp" }

    links {
        "Glad",
        "fmt",
        "spdlog",
        "glfw",
        "dl"
    }

    filter "configurations:Debug"
      defines { "DEBUG", "SPDLOG_FMT_EXTERNAL", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG" }
      symbols "On"

    filter "configurations:Release"
      defines { "NDEBUG", "SPDLOG_FMT_EXTERNAL", "SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_INFO" }
      optimize "On"
