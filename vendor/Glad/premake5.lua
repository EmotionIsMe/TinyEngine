project "Glad"
    kind "StaticLib"
    language "C"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/gald.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
    }
	
	includedirs--附加包含目录
    {
		"include"
    }
    
	filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
