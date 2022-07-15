workspace "AWE"
    architecture "x64"
    startproject "Game"

configurations
{
    "Debug",
    "Release"
}

-- VARIABLES --

-- Include directories 
IncludeDir = {}

IncludeDir["AWE_SRC"] = "AWE/src"
IncludeDir["GLFW"] = "AWE/vendor/glfw/include"

-- Output directory
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AWE/vendor/glfw/premake5.lua"

project "AWE"
    location "AWE"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "AWEpch.h"
    pchsource "%{IncludeDir.AWE_SRC}/AWEpch.cpp"

    files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

    includedirs
    {
        "%{IncludeDir.AWE_SRC}",
        "%{IncludeDir.GLFW}"
    }

    links
    {
        "GLFW"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "AWE_PLATFORM_WINDOWS",
            "AWE_BUILD_DLL"
        }

        postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game")
		}

    filter "configurations:Debug"
        defines "AWE_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AWE_RELEASE"
        symbols "On"
        optimize "On"

project "Game"
    location "Game"
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
        "%{IncludeDir.AWE_SRC}"
    }

    links
    {
        "AWE"
    }

	filter "system:windows"
	    cppdialect "C++20"
	    systemversion "latest"

	    defines 
	    {
		    "AWE_PLATFORM_WINDOWS"
	    }

	filter "configurations:Debug"
		defines "AWE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "AWE_RELEASE"
		symbols "On"
		optimize "On"