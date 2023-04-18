workspace "TinyEngine" --解决方案名称
    architecture "x64" --编译平台 只编64位--(x86,x86_64,ARM)

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--临时变量 定义 输出目录
--详细的所有支持的tokens 可参考 [https://github.com/premake/premake-core/wiki/Tokens]
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--include directory relative to root folder
IncludeDir = {}
IncludeDir ["GLFW"] = "TinyEngine/vendor/GLFW/include" 
IncludeDir ["Glad"] = "TinyEngine/vendor/GLAD/include" 
IncludeDir ["ImGui"] = "TinyEngine/vendor/imgui" 
IncludeDir["glm"] = "TinyEngine/vendor/glm"
IncludeDir["stb_image"] = "TinyEngine/vendor/stb_image"
IncludeDir["entt"] = "TinyEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "TinyEngine/vendor/yaml-cpp/include"

group "Dependencies"
	include "TinyEngine/vendor/GLFW"
	include "TinyEngine/vendor/Glad"
	include "TinyEngine/vendor/imgui"
	include "TinyEngine/vendor/yaml-cpp"
group ""

project "TinyEngine" --项目名称
    location "TinyEngine" --相对路径
    kind "StaticLib" --表明该项目是静态库
    language "c++"   --指定语言是c++
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--中间临时文件的目录

	pchheader "tepch.h"
	pchsource "TinyEngine/src/tepch.cpp"

    files--该项目的文件
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
    }
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs--附加包含目录
    {
		"%{prj.name}/src/",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}"
    }
	
	links
    {
        "GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
        "opengl32.lib"
    }

    filter "system:windows"--windows平台的配置
        systemversion "latest"

        defines --预编译宏
        {
            "TE_BUILD_DLL",
            "TE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "c++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "TinyEngine/vendor/spdlog/include",
		"TinyEngine/src",
		"TinyEngine/vendor",
		"%{IncludeDir.glm}"
    }

    links
    {
        "TinyEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TE_PLATFORM_WINDOWS",
            "_UNICODE",
            "UNICODE",
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
        optimize "on"
		

project "Tiny-Editor"
    location "Tiny-Editor"
    kind "ConsoleApp"
    language "c++"
	cppdialect "C++17"
	staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "TinyEngine/vendor/spdlog/include",
		"TinyEngine/src",
		"TinyEngine/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}"
    }

    links
    {
        "TinyEngine"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "TE_PLATFORM_WINDOWS",
            "_UNICODE",
            "UNICODE",
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
        optimize "on"