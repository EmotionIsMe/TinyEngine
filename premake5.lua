include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

workspace "TinyEngine"
    architecture "x86_64"
	startproject "Tiny-Editor"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }
    
    solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "vendor/premake"
	include "TinyEngine/vendor/GLFW"
	include "TinyEngine/vendor/Glad"
	include "TinyEngine/vendor/imgui"
	include "TinyEngine/vendor/yaml-cpp"
    include "TinyEngine/vendor/Box2D"
group ""

group "Core"
	include "TinyEngine"
	include "Tiny-ScriptCore"
group ""

group "Tools"
	include "Tiny-Editor"
group ""

group "Misc"
	include "Sandbox"
group ""





