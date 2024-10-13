project "Finite Element Method - Tests"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir ("%{_WORKING_DIR}/Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("%{_WORKING_DIR}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   staticruntime "off"

   flags { "MultiProcessorCompile" }

   files { 
    "tests/**.cpp"
   }

   includedirs {
    "Finite Element Method - Runtime/src",
    "../Dependencies/googletest/googletest/include"
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
