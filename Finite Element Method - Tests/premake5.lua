project "Finite Element Method - Tests"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir ("%{_WORKING_DIR}/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("%{_WORKING_DIR}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   staticruntime "off"

   flags { "MultiProcessorCompile" }

   files { 
    "tests/**.cpp",

    "../Finite Element Method - Runtime/src/**.h",
    "../Finite Element Method - Runtime/src/**.cpp"
   }

   removefiles {
       "../Finite Element Method - Runtime/src/Application.cpp"
   }

   includedirs {
    "../Dependencies/googletest/googletest/include",

    "../Finite Element Method - Runtime/src",
    "../Finite Element Method - Runtime/src/model",
    "../Finite Element Method - Runtime/src/reader",
    "../Finite Element Method - Runtime/src/enum",
    "../Finite Element Method - Runtime/src/generator",
    "../Finite Element Method - Runtime/src/simulation",
    "../Finite Element Method - Runtime/src/utils"
   }

   links {
    "GoogleTest"
   }

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "NDEBUG" }
       runtime "Release"
       optimize "On"
       symbols "On"
