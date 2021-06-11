workspace "PBR-IBL"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Shipping"
	}
	startproject "PBR-IBL-DX11"
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
ThirdPartyIncludeDir = {}
ThirdPartyIncludeDir["std_image"] = "%{wks.location}/ThirdParty/std_image"

project "PBR-IBL-DX11"
	location "PBR-IBL"
	kind "WindowedApp"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"PBR-IBL/Src/**.h",
		"PBR-IBL/Src/**.hpp",
		"PBR-IBL/Src/**.cpp",
		"PBR-IBL/include/**.h",
		"PBR-IBL/include/**.cpp",
	}

	includedirs
	{
		"PBR-IBL/include",
	}

	filter "system:Windows"
		systemversion "latest" -- To use the latest version of the SDK available

	filter "configurations:Debug"
		defines "LEMON_DEBUG"
		buildoptions "/MDd"
	    symbols "On"
	filter "configurations:Release"
		defines "LEMON_RELEASE"
		buildoptions "/MD"
	    optimize "On"
	filter "configurations:Shipping"
		defines "LEMON_SHIPPING"
		buildoptions "/MD"
        optimize "On"
