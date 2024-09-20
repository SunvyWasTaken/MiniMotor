@echo off

ECHO Initializing CMake project
ECHO =============================
cd %cd%
cmake -DCMAKE_TOOLCHAIN_FILE=%cd%/vcpkg/scripts/buildsystems/vcpkg.cmake -S %cd% -B %cd%/build

ECHO =============================
ECHO Install done