workspace "Finite Element Method"
    architecture "x64"
    startproject "Finite Element Method"

    configurations {
        "Debug",
        "Release"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    group "Dependencies"
        include "Finite Element Method/Dependencies/NumericalMethods/Numerical methods - Core/premake5.lua"
    group ""

    include "Finite Element Method/premake5.lua"
