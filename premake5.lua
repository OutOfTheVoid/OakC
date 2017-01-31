workspace "OakC"
	configurations { "Debug", "Release" }

project "Compiler"
	
	kind "ConsoleApp"
	
	language "C++"
	flags { "C++11" }
	
	files { "**.h", "**.cpp" }
	
	includedirs "include"
	
	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"
		
	filter { "configurations:Release" }
		defines { "RELEASE" }
		optimize "On"
	
	