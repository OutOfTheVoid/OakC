workspace "OakC"
	configurations { "Debug", "Release" }

project "Compiler"
	
	kind "ConsoleApp"
	
	language "C++"
	
	files { "**.h", "**.cpp" }
	
	includedirs "include"
	
	filter { "not system:windows" }
		toolset "gcc"
		buildoptions { "-std=c++11" }
		
	filter { "action:vs*" }
		buildoptions { "/std:c++11" }
		
	filter {}
		
	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"
		
	filter { "configurations:Release" }
		defines { "RELEASE" }
		optimize "On"
	
	