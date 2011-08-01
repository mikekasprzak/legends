-- Hello! I sync remote SVN, HG, and GIT repositories to a folder "Build".
-- Inside Build, I compile things. In the case of MSVC, I used the included
-- Solution file (VisualC/VC2008.sln), and left the files where they were.

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
	kind "WindowedApp"
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
	-- In my build system, the rule is that all files beginning with . or _ are ignored.
	excludes {
		"../../src/**/_**",
		"../../src/**/.**",
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
		"USES_GEL", "USES_FOUNDATION", 
		"USES_SDL", "USES_SDL_1_3", "NO_STDIO_REDIRECT", "NO_SDL_SUBDIR",
		"USES_IRRKLANG",
		"USES_OPENGL", "USES_GLEE",
		"USES_WINDOWS", 
		
		"USES_MSVC", "_CRT_SECURE_NO_WARNINGS",
	}
	
	configuration "Debug"
		kind "ConsoleApp"
		libdirs { 
			(SDL_LIB_ROOT .. "Debug/"),
		}
		postbuildcommands { 
			path.translate("copy " .. SDL_LIB_ROOT .. "Debug/SDL.dll Debug", "\\"),
		}
		defines {
			"DEBUG", "_DEBUG",
		}
		flags { "Symbols" }
		
	configuration "Release"
		libdirs {
			(SDL_LIB_ROOT .. "Release/"),
		}
		postbuildcommands {
			path.translate("copy " .. SDL_LIB_ROOT .. "Release/SDL.dll Release",  "\\"),
		}
		defines {
			"NDEBUG",
		} 
		flags { "Optimize" }
