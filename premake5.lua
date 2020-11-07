-- premake5.lua

workspace "FlappyBird_Clone"
    architecture "x64"
    startproject "FlappyBird_Clone"

   configurations 
   { 
       "Debug",
       "Release",
   }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "FlappyBird_Clone"
    location "FlappyBird_Clone"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    { 
        "%{wks.location}/%{prj.name}/src/**.h",
        "%{wks.location}/%{prj.name}/src/**.cpp" 
    }

    removefiles 
    {
        "%{wks.location}/%{prj.name}/src/Junk/**.cpp",
        "%{wks.location}/%{prj.name}/src/Junk/**.h"
    }

    includedirs
    {
        "%{wks.location}/%{prj.name}/src",
        "%{wks.location}/vendor/Tiny/includes",
        "%{wks.location}/vendor/Tiny/vendor/spdlog/include",
        "%{wks.location}/vendor/Tiny/vendor/ImGui",
        "%{wks.location}/vendor/Tiny/vendor/glm/include"
    }

    libdirs 
    { 
        "%{wks.location}/vendor/Tiny/libs",
    }

    links {
        "Tiny",
        "Glad",
        "GLFW",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

        defines 
        {
            "T_PLATFORM_WINDOWS",
        }


    filter "configurations:Debug"
        defines "T_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "T_RELEASE"
        optimize "On"

