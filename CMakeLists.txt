cmake_minimum_required (VERSION 3.10)

add_library(LeafEngine_compiler_flags INTERFACE)
target_compile_features(LeafEngine_compiler_flags INTERFACE cxx_std_20)

project("LeafEngine")
add_subdirectory(LeafEngine)

include("${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LeafEngine)