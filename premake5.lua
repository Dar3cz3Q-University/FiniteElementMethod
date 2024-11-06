workspace "FiniteElementMethod"
    architecture "x64"
    startproject "FiniteElementMethod_Runtime"

    configurations {
        "Debug",
        "Release"
    }

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }
     
    OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    
    group "Dependencies"
        include "Dependencies/googletest/googletest/premake5.lua"
        include "FiniteElementMethod_Runtime/Dependencies/NumericalMethods/NumericalMethods_Core/premake5.lua"
    group ""

    include "FiniteElementMethod_Runtime/premake5.lua"
    include "FiniteElementMethod_Tests/premake5.lua"
