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

include "TinyEngine/vendor/GLFW"
include "TinyEngine/vendor/Glad"
include "TinyEngine/vendor/imgui"


project "TinyEngine" --项目名称
    location "TinyEngine" --相对路径
    kind "SharedLib" --表明该项目是dll动态库
    language "c++"   --指定语言是c++

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")--输出目录
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")--中间临时文件的目录

	pchheader "tepch.h"
	pchsource "TinyEngine/src/tepch.cpp"

    files--该项目的文件
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs--附加包含目录
    {
		"%{prj.name}/src/",
        "%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
    }
	
	links
    {
        "GLFW",
		"Glad",
		"ImGui",
        "opengl32.lib"
    }

    filter "system:windows"--windows平台的配置
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines --预编译宏
        {
            "TE_BUILD_DLL",
            "TE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
            "_WINDLL",
            "_UNICODE",
            "UNICODE",
        }

        postbuildcommands -- build后的自定义命令
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") --拷贝引擎dll库到sanbox.exe的同一目录下去
        }

    filter "configurations:Debug"
        defines "TE_DEBUG"
        runtime "Debug"
		buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
		buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
		buildoptions "/MD"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "c++"

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
        "TinyEngine/src"
    }

    links
    {
        "TinyEngine"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
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
		buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "TE_RELEASE"
        runtime "Release"
		buildoptions "/MD"
        optimize "on"

    filter "configurations:Dist"
        defines "TE_DIST"
        runtime "Release"
		buildoptions "/MD"
        optimize "on"