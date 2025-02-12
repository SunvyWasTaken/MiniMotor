cmake_minimum_required (VERSION 3.30.1)

set(CMAKE_DEBUG_POSTFIX "-d")

add_library(MiniMotor_compiler_flags INTERFACE)
target_compile_features(MiniMotor_compiler_flags INTERFACE cxx_std_20)

project("MiniMotor")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(MiniMotor)
add_subdirectory(Sandbox)

include("${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)