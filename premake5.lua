workspace "OakC"
	configurations { "Debug32", "Release32", "Debug64", "Release64" }

project "Compiler"
	
	kind "ConsoleApp"
	
	language "C++"
	
	files { "**.h", "**.cpp" }
	
	includedirs "include"
	
	filter { "not system:windows" }
		toolset "clang"
		buildoptions { "-std=c++11 -Wall -Wextra -pedantic-errors" }
		
	filter { "action:vs*" }
		disablewarnings { "4244" }
		
	filter {}
		
	filter { "configurations:Debug32 or configurations:Debug64" }
		defines { "DEBUG" }
		symbols "On"
		
	filter { "configurations:Release32 or configurations:Release64" }
		defines { "RELEASE" }
		optimize "On"
		
	filter { "configurations:Debug32 or configurations:Release32" }
		architecture "x86"
		
	filter { "configurations:Debug64 or configurations:Release64" }
		architecture "x86_64"
	
	