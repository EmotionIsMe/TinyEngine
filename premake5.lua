workspace "TinyEngine" --�����������
    architecture "x64" --����ƽ̨ ֻ��64λ--(x86,x86_64,ARM)

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
--��ʱ���� ���� ���Ŀ¼
--��ϸ������֧�ֵ�tokens �ɲο� [https://github.com/premake/premake-core/wiki/Tokens]
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

project "TinyEngine" --��Ŀ����
    location "TinyEngine" --���·��
    kind "StaticLib" --��������Ŀ�Ǿ�̬��
    language "c++"   --ָ��������c++
	cppdialect "C++17"
	staticruntime "on"

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
    }
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs--���Ӱ���Ŀ¼
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

    filter "system:windows"--windowsƽ̨������
        systemversion "latest"

        defines --Ԥ�����
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