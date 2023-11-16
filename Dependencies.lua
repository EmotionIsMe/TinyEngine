VULKAN_SDK = os.getenv("VULKAN_SDK")

--include directory relative to root folder
IncludeDir = {}
IncludeDir ["Box2D"]        = "%{wks.location}/TinyEngine/vendor/Box2D/include"
IncludeDir ["GLFW"]         = "%{wks.location}/TinyEngine/vendor/GLFW/include" 
IncludeDir ["Glad"]         = "%{wks.location}/TinyEngine/vendor/GLAD/include" 
IncludeDir ["ImGui"]        = "%{wks.location}/TinyEngine/vendor/imgui" 
IncludeDir ["glm"]          = "%{wks.location}/TinyEngine/vendor/glm"
IncludeDir ["stb_image"]    = "%{wks.location}/TinyEngine/vendor/stb_image"
IncludeDir ["entt"]         = "%{wks.location}/TinyEngine/vendor/entt/include"
IncludeDir ["mono"]         = "%{wks.location}/TinyEngine/vendor/mono/include"
IncludeDir ["yaml_cpp"]     = "%{wks.location}/TinyEngine/vendor/yaml-cpp/include"
IncludeDir ["ImGuizmo"]     = "%{wks.location}/TinyEngine/vendor/ImGuizmo"
IncludeDir ["shaderc"]      = "%{wks.location}/TinyEngine/vendor/shaderc/include"
IncludeDir ["SPIRV_Cross"]  = "%{wks.location}/TinyEngine/vendor/SPIRV-Cross"
IncludeDir ["VulkanSDK"]    = "%{VULKAN_SDK}/Include"

Library = {}
Library ["VulkanSDK_release"]   = "%{VULKAN_SDK}/Lib"
Library ["VulkanSDK_debug"]     = "%{wks.location}/TinyEngine/vendor/VulkanSDK/Lib"
Library ["mono"]                = "%{wks.location}/TinyEngine/vendor/mono/lib/%{cfg.buildcfg}/libmono-static-sgen.lib"

--Windows
Library ["WinSock"]     = "Ws2_32.lib"
Library ["WinMM"]       = "Winmm.lib"
Library ["WinVersion"]  = "Version.lib"
Library ["BCrypt"]      = "Bcrypt.lib"