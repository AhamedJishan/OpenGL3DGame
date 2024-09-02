workspace "OpenGL3DGame"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

    -- Include directories relative to root folder (solution directory)
    IncludeDir = {}

    project "OpenGL3DGame"
        location "OpenGL3DGame"
        kind "ConsoleApp"
        language "C++"
        staticruntime "On"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}/")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}/")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }

        includedirs
        {
            "%{prj.name}/src/",
            "vendor/include"
        }

        links 
        {

        }

        filter "configurations:Debug"
            defines "DEBUG"
            runtime "Debug"
            symbols "On"

        filter "configurations:Release"
            defines "RELEASE"
            runtime "Release"
            optimize "On"