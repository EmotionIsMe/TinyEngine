workspace "TinyEngine" --�����������
    architecture "x64" --����ƽ̨ ֻ��64λ--(x86,x86_64,ARM)
	startproject "Tiny-Editor"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--��ʱ���� ���� ���Ŀ¼
--��ϸ������֧�ֵ�tokens �ɲο� [https://github.com/premake/premake-core/wiki/Tokens]
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

project "TinyEngine" --��Ŀ����
    location "TinyEngine" --���·��
    kind "StaticLib" --��������Ŀ�Ǿ�̬��
    language "c++"   --ָ��������c++
	cppdialect "C++17"
	staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--���Ŀ¼
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--�м���ʱ�ļ���Ŀ¼

	pchheader "tepch.h"
	pchsource "TinyEngine/src/tepch.cpp"

    files--����Ŀ���ļ�
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

    includedirs--���Ӱ���Ŀ¼
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

    filter "system:windows"--windowsƽ̨������
        systemversion "latest"

        defines --Ԥ�����
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