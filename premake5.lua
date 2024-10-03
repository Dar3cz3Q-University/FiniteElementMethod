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
    
    include "Finite Element Method/premake5.lua"
