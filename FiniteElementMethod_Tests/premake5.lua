project "FiniteElementMethod_Tests"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir ("%{_WORKING_DIR}/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("%{_WORKING_DIR}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   staticruntime "off"
   dependson { "FiniteElementMethod_Runtime" }

   flags { "MultiProcessorCompile" }

   pchheader "pch.h"
   pchsource "../FiniteElementMethod_Runtime/src/pch.cpp"

   files { 
    "tests/**.cpp",

    "../FiniteElementMethod_Runtime/src/**.h",
    "../FiniteElementMethod_Runtime/src/**.cpp"
   }

   removefiles {
       "../FiniteElementMethod_Runtime/src/Application.cpp"
   }

   includedirs {
    "../FiniteElementMethod_Runtime/src",
    "../FiniteElementMethod_Runtime/src/global_data",
    "../FiniteElementMethod_Runtime/src/grid",
    "../FiniteElementMethod_Runtime/src/file_reader",
    "../FiniteElementMethod_Runtime/src/model",
    "../FiniteElementMethod_Runtime/src/simulation",
    "../FiniteElementMethod_Runtime/src/utils",
    "../FiniteElementMethod_Runtime/src/universal",

    -- spdlog
    "../FiniteElementMethod_Runtime/Dependencies/spdlog/include",

    -- GoogleTest
    "../Dependencies/googletest/googletest/include"
   }

   links {
    "GoogleTest"
   }

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

   filter "configurations:Debug"
       defines { "DEBUG", "RUNNING_TEST" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "NDEBUG" }
       runtime "Release"
       optimize "On"
       symbols "On"
       