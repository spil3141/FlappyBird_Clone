-- premake5.lua

workspace "FlappyBird_Clone"
    architecture "x64"
    startproject "FlappyBird_Clone"

   configurations 
   { 
       "Debug",
       "Release",
   }

outputdir = "%{cfg.buildc
fg}-%{cfg.system}-%{cfg.architecture}"


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
        "%{wks.location}/vendor/Tiny_v0.2/includes",
        "%{wks.location}/vendor/Tiny_v0.2/vendor/spdlog/include",
        "%{wks.location}/vendor/Tiny_v0.2/vendor/ImGui",
        "%{wks.location}/vendor/Tiny_v0.2/vendor/glm/include",
        "%{wks.location}/vendor/Tiny_v0.2/vendor/asio/include",
        "%{wks.location}/vendor/Tiny_v0.2/vendor/EnTT/include"
    }

    links {
        "Tiny",
        "Glad",
        "GLFW",
        "ImGui"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "T_DEBUG"
        symbols "On"

        libdirs 
        { 
            "%{wks.location}/vendor/Tiny_v0.2/libs/debug",
        }

    filter "configurations:Release"
        defines "T_RELEASE"
        optimize "On"

        libdirs 
        { 
            "%{wks.location}/vendor/Tiny_v0.2/libs/release",
        }
