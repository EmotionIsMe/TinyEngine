workspace "TinyEngine" --解决方案名称
    architecture "x64" --编译平台 只编64位--(x86,x86_64,ARM)
	startproject "Tiny-Editor"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--临时变量 定义 输出目录
--详细的所有支持的tokens 可参考 [https://github.com/premake/premake-core/wiki/Tokens]
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

VULKAN_SDK = os.getenv("VULKAN_SDK")

--include directory relative to root folder
IncludeDir = {}
IncludeDir ["Box2D"] = "TinyEngine/vendor/Box2D/include"
IncludeDir ["GLFW"] = "TinyEngine/vendor/GLFW/include" 
IncludeDir ["Glad"] = "TinyEngine/vendor/GLAD/include" 
IncludeDir ["ImGui"] = "TinyEngine/vendor/imgui" 
IncludeDir ["glm"] = "TinyEngine/vendor/glm"
IncludeDir ["stb_image"] = "TinyEngine/vendor/stb_image"
IncludeDir ["entt"] = "TinyEngine/vendor/entt/include"
IncludeDir["mono"] = "TinyEngine/vendor/mono/include"
IncludeDir ["yaml_cpp"] = "TinyEngine/vendor/yaml-cpp/include"
IncludeDir ["ImGuizmo"] = "TinyEngine/vendor/ImGuizmo"
IncludeDir ["shaderc"] = "TinyEngine/vendor/shaderc/include"
IncludeDir ["SPIRV_Cross"] = "TinyEngine/vendor/SPIRV-Cross"
IncludeDir ["VulkanSDK"] = "%{VULKAN_SDK}/Include"

Library = {}
Library ["VulkanSDK_release"] = "%{VULKAN_SDK}/Lib"
Library ["VulkanSDK_debug"] = "TinyEngine/vendor/VulkanSDK/Lib"
Library ["mono"] = "vendor/mono/lib/%{cfg.buildcfg}/libmono-static-sgen.lib"

--Windows
Library ["WinSock"] = "Ws2_32.lib"
Library ["WinMM"] = "Winmm.lib"
Library ["WinVersion"] = "Version.lib"
Library ["BCrypt"] = "Bcrypt.lib"

group "Dependencies"
	include "TinyEngine/vendor/GLFW"
	include "TinyEngine/vendor/Glad"
	include "TinyEngine/vendor/imgui"
	include "TinyEngine/vendor/yaml-cpp"
    include "TinyEngine/vendor/Box2D"
group ""

project "TinyEngine" --项目名称
    location "TinyEngine" --相对路径
    kind "StaticLib" --表明该项目是静态库
    language "c++"   --指定语言是c++
	cppdialect "C++17"
	staticruntime "off"

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
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp"
    }
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

    includedirs--附加包含目录
    {
		"%{prj.name}/src/",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.Box2D}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.VulkanSDK}"
    }
	
	links
    {
        "Box2D",
        "GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
        "opengl32.lib",
		"%{Library.mono}"
    }
	
	filter "files:TinyEngine/vendor/ImGuizmo/**.cpp"
	flags { "NoPCH" }

    filter "system:windows"--windows平台的配置
        systemversion "latest"

        defines --预编译宏
        {
            "TE_BUILD_DLL",
            "TE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
        }
		
		links
		{
			"%{Library.WinSock}",
			"%{Library.WinMM}",
			"%{Library.WinVersion}",
			"%{Library.BCrypt}",
		}

    filter "configurations:Debug"
        defines "TE_DEBUG"
        runtime "Debug"
        symbols "on"
		
		libdirs
		{
			"%{VULKAN_SDK}/Lib"
		}
		
		links
		{
			"shaderc_sharedd.lib",
			"spirv-cross-cored.lib",
			"spirv-cross-glsld.lib"
		}

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
        optimize "on"
		
		libdirs
		{
			"%{VULKAN_SDK}/Lib"
		}
		
		links
		{
			"shaderc_shared.lib",
			"spirv-cross-core.lib",
			"spirv-cross-glsl.lib"
		}

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
        optimize "on"
		
		libdirs
		{
			"%{VULKAN_SDK}/Lib"
		}
		
		links
		{
			"shaderc_shared.lib",
			"spirv-cross-core.lib",
			"spirv-cross-glsl.lib"
		}

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "c++"
	cppdialect "C++17"
	staticruntime "off"

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
	staticruntime "off"

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
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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

project "Tiny-ScriptCore"
	kind "SharedLib"
	language "C#"
	dotnetframework "4.7.2"

	targetdir ("Tiny-Editor/Resources/Scripts")
	objdir ("Tiny-Editor/Resources/Scripts/Intermediates")

	files 
	{
		"Source/**.cs",
		"Properties/**.cs"
	}

	filter "configurations:Debug"
		optimize "Off"
		symbols "Default"
		symbols "Default"

	filter "configurations:Release"
		optimize "On"
		symbols "Default"

	filter "configurations:Dist"
		optimize "Full"
		symbols "Off"