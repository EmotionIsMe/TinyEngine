project "TinyEngine" --项目名称
    kind "StaticLib" --表明该项目是静态库
    language "c++"   --指定语言是c++
	cppdialect "C++17"
	staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")--输出目录
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")--中间临时文件的目录

	pchheader "tepch.h"
	pchsource "src/tepch.cpp"

    files--该项目的文件
    {
		"src/**.h",
		"src/**.cpp",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",

		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp"
    }
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"YAML_CPP_STATIC_DEFINE"
	}

    includedirs--附加包含目录
    {
		"src",
        "vendor/spdlog/include",
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
	
	filter "files:vendor/ImGuizmo/**.cpp"
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
