project "Finite Element Method - Runtime"
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
       "src/simulation",
       "src/utils",

       -- Numerical Methods
       "Dependencies/NumericalMethods/Numerical methods - Core/Source"
   }

   links {
      "Numerical methods - Core"
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
