project "Finite Element Method"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   flags { "MultiProcessorCompile" }

   files 
   { 
    "src/**.h", 
    "src/**.cpp" 
   }

--    pchheader "pch.h"
--    pchsource "pch.cpp"

   includedirs 
   {
       ".",
       "src/model",
       "src/reader",
       "src/enum",
       "src/simulation",
       "src/utils",

       -- Numerical Methods
       "Dependencies/NumericalMethods/Numerical methods - Core/Source"
   }

   links
   {
      "Numerical methods - Core"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

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
