workspace "Murphy"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Murphy"
    location "Murphy"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "mppch.h"
    pchsource "Murphy/src/mppch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/vendor/SFML-2.5.1/include",
        "%{prj.name}/src"
    }

    libdirs
    {
        "%{prj.name}/vendor/SFML-2.5.1/lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "MP_PLATFORM_WINDOWS",
            "MP_BUILD_DLL"
        }

    filter "configurations:Debug"
        symbols "On"
        defines {"MP_DEBUG", "MP_ENABLE_ASSERTS"}
        links {"sfml-graphics-d", "sfml-window-d", "sfml-system-d"} 

    filter "configurations:Release"
        optimize "On"
        defines "MP_RELEASE"
        links {"sfml-graphics", "sfml-window", "sfml-system"}

    filter "configurations:Dist"
        optimize "On"
        defines "MP_DIST"
        links {"sfml-graphics", "sfml-window", "sfml-system"}


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Murphy/vendor/spdlog/include",
        "Murphy/vendor/SFML-2.5.1/include",
        "Murphy/src"
    }

    libdirs
    {
        "Murphy/vendor/SFML-2.5.1/lib"
    }

    links
    {
        "Murphy"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        defines "MP_PLATFORM_WINDOWS"

        postbuildcommands
        {
            ("{COPY} ../bin/" .. outputdir .. "/Murphy/Murphy.dll ../bin/" .. outputdir .. "/Sandbox"),
            ("{COPY} ../Murphy/vendor/SFML-2.5.1/bin/* ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        symbols "On"
        defines "MP_DEBUG"
        links {"sfml-graphics-d", "sfml-window-d", "sfml-system-d"}

    filter "configurations:Release"
        optimize "On"
        defines "MP_RELEASE"
        links {"sfml-graphics", "sfml-window", "sfml-system"}

    filter "configurations:Dist"
        optimize "On"
        defines "MP_DIST"
        links {"sfml-graphics", "sfml-window", "sfml-system"}