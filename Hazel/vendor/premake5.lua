project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("%{prj.name}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{prj.name}/bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/imconfig.h",
		"%{prj.name}/imgui.cpp",
		"%{prj.name}/imgui.h",
		"%{prj.name}/imgui_demo.cpp",
		"%{prj.name}/imgui_draw.cpp",
		"%{prj.name}/imgui_internal.h",
		"%{prj.name}/imgui_tables.cpp",
		"%{prj.name}/imgui_widgets.cpp",
		"%{prj.name}/imgui_rectpack.h",
		"%{prj.name}/imgui_textedit.h",
		"%{prj.name}/imgui_truetype.h",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
		staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		staticruntime "on"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		staticruntime "on"
		optimize "on"

	filter "configurations:Dist"
		runtime "Release"
		staticruntime "on"
		optimize "on"
        symbols "off"
