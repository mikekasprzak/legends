
SDL_ROOT 		= "D:/Build/SDL/"
SDL_LIB_ROOT	= SDL_ROOT .. "VisualC/SDL/"

--printf(SDL_LIB_ROOT .. "Debug")

solution "MySolution"
	configurations { "Debug", "Release" }
	location "Build"

	configuration "Debug"
		targetdir "Build/Debug"

	configuration "Release"
		targetdir "Build/Release"

	if _ACTION == "clean" then
		os.rmdir("Build/Debug")
		os.rmdir("Build/Release")
	end

	
project "Legends"
	kind "ConsoleApp"
	language "C++"
	location "build"

	files {
		"../../src/GEL/**.c*",
		"../../src/Foundation/**.c*",
		"../../src/GameLegends/**.c*",
		"../../src/Main/SDL/**.c*",
		
		"../../src/External/Squirrel/**.c*",
		"../../src/External/NVTriStrip/**.c*",
		"../../src/External/Bullet/**.c*",
		"../../src/External/cJSON/**.c*",
		"../../src/External/TinyXML/**.c*",
	}
	excludes {
		"../../src/**/_**",
		"../../src/**/.**",
		"../../src/GEL/Audio/_Legacy/**",
		"../../src/GEL/Graphics/_Temp/**",
	}
	
	links { 
		"SDL", "irrKlang", "opengl32", "winmm",
	}
	libdirs { 
		"../../src/External/irrKlang/lib/win32-VisualStudio/"
	}
	
	includedirs {
		"../../src/GEL/",
		"../../src/Foundation/",
		"../../src/GameLegends/",
		"../../src/Main/SDL/",

		"../../src/External/Squirrel/include/",
		"../../src/External/NVTriStrip/include/",
		"../../src/External/Bullet/",
		"../../src/External/cJSON/",
		"../../src/External/TinyXML/",
		
		(SDL_ROOT .. "/include"),
	}		
	
	defines {
		"PRODUCT_LEGENDS",
		"USES_GEL", "USES_FOUNDATION", "USES_SDL", "USES_SDL_1_3", "USES_IRRKLANG",
		"USES_WINDOWS", "NO_STDIO_REDIRECT", "USES_OPENGL", "USES_GLEE",
		"USES_MSVC", "NO_SDL_SUBDIR",
		
		"_CRT_SECURE_NO_WARNINGS",
	}
	
	configuration "Debug"
		libdirs { (SDL_LIB_ROOT .. "Debug/") }
		postbuildcommands { path.translate("copy " .. SDL_LIB_ROOT .. "Debug/SDL.dll Debug", "\\") }
		defines {
			"DEBUG", "_DEBUG",
		}
		flags { "Symbols" }
		
	configuration "Release"
		libdirs { (SDL_LIB_ROOT .. "Release/") }
		postbuildcommands { path.translate("copy " .. SDL_LIB_ROOT .. "Release/SDL.dll Release", "\\") }
		defines {
			"NDEBUG",
		} 
		flags { "Optimize" }

	