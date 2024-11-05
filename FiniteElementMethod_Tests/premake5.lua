project "FiniteElementMethod_Tests"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir ("%{_WORKING_DIR}/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("%{_WORKING_DIR}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   staticruntime "off"

   flags { "MultiProcessorCompile" }

   files { 
    "tests/**.cpp",

    "../FiniteElementMethod_Runtime/src/**.h",
    "../FiniteElementMethod_Runtime/src/**.cpp"
   }

   removefiles {
       "../FiniteElementMethod_Runtime/src/Application.cpp"
   }

   includedirs {
    "../Dependencies/googletest/googletest/include",

    "../FiniteElementMethod_Runtime/src",
    "../FiniteElementMethod_Runtime/src/model",
    "../FiniteElementMethod_Runtime/src/reader",
    "../FiniteElementMethod_Runtime/src/enum",
    "../FiniteElementMethod_Runtime/src/generator",
    "../FiniteElementMethod_Runtime/src/simulation",
    "../FiniteElementMethod_Runtime/src/utils",
    "../FiniteElementMethod_Runtime/src/math"
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
