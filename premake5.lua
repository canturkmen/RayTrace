-- premake5.lua
workspace "RayTracingApp"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "RayTracingApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "RayTracingApp"