project "FiniteElementMethod_Runtime"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir ("%{_WORKING_DIR}/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("%{_WORKING_DIR}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   staticruntime "off"

   flags { "MultiProcessorCompile" }

   pchheader "pch.h"
   pchsource "src/pch.cpp"

   files { 
    "src/**.h", 
    "src/**.cpp" 
   }

   includedirs {
       "src",

       "src/model",
       "src/reader",
       "src/enum",
       "src/generator",
       "src/simulation",
       "src/utils",
       "src/math",

       -- Numerical Methods
       "Dependencies/NumericalMethods/NumericalMethods_Core/Source",

       -- GoogleTest
       "../Dependencies/googletest/googletest/include"
   }

   links {
      "NumericalMethods_Core"
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
