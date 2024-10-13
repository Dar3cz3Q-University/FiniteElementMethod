workspace "Finite Element Method"
    architecture "x64"
    startproject "Finite Element Method - Runtime"

    configurations {
        "Debug",
        "Release"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    group "Dependencies"
        include "Dependencies/googletest/googletest/premake5.lua"
        include "Finite Element Method - Runtime/Dependencies/NumericalMethods/Numerical methods - Core/premake5.lua"
    group ""

    include "Finite Element Method - Runtime/premake5.lua"
    include "Finite Element Method - Tests/premake5.lua"
