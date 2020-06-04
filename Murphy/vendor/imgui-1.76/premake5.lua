project "ImGui"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "include",
        "../SFML-2.5.1/include"
    }

    filter "system:windows"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "On"
        
    filter "configurations:Debug"
        buildoptions "/MTd"
        runtime "Debug"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
