project(MiniMotor VERSION 0.1)

configure_file(Config.h.in Config.h)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp" "*.txt" "*.vert" "*.frag")

# Macro to group files in the IDE
macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})
        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

# Execute the macro
GroupSources("Sources")

if (NOT EMSCRIPTEN)
    find_package(EnTT CONFIG REQUIRED)

    find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
    find_package(ImGui-SFML CONFIG REQUIRED)

    find_package(vulkan REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(imgui CONFIG REQUIRED)
else ()
    set(EMSCRIPTEN_LIB_DIR ${CMAKE_SOURCE_DIR}/vcpkg_installed/wasm32-emscripten/lib)
    set(EMSCRIPTEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vcpkg_installed/wasm32-emscripten/include)   
endif ()

add_Library(${PROJECT_NAME} SHARED ${SOURCES})

if(WIN32)
    # Sous Windows, utiliser une commande PowerShell pour trouver les dossiers nommés "Public"
    execute_process(
        COMMAND powershell -Command "Get-ChildItem -Recurse -Directory | Where-Object { $_.Name -eq 'Public' } | ForEach-Object { $_.FullName }"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE PUBLIC_DIRS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    # Sous Linux/macOS, utiliser la commande Unix `find`
    execute_process(
        COMMAND find ${CMAKE_SOURCE_DIR} -type d -name Public
        OUTPUT_VARIABLE PUBLIC_DIRS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# Remplacer les nouvelles lignes par des espaces pour garantir que les chemins sont bien séparés
string(REPLACE "\n" " " PUBLIC_DIRS "${PUBLIC_DIRS}")

# Transformer le résultat en une liste CMake
separate_arguments(PUBLIC_DIRS)

# Ajouter chaque dossier trouvé dans les includes
foreach(DIR ${PUBLIC_DIRS})
    target_include_directories(${PROJECT_NAME} PUBLIC ${DIR})
endforeach()

# Permet d'aller chercher les fichiers générés par CMake
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

if(EMSCRIPTEN)
	message("emscripten")

	set(VCPKG_TARGET_ARCHITECTURE wasm32-emscripten)
	set(CMAKE_TOOLCHAIN_FILE $ENV{EMSDK_HOME}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
	
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")

	#set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-sUSE_GLFW=3 -sFULL_ES3=1 -sWASM=1 -sUSE_SDL=2 -sUSE_SDL_MIXER=2 -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sNO_DISABLE_EXCEPTION_CATCHING --preload-file shader")
	
	target_link_libraries(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_LIB_DIR})
    target_include_directories(${PROJECT_NAME} PRIVATE ${EMSCRIPTEN_INCLUDE_DIR})
else()

    target_link_libraries(${PROJECT_NAME} PUBLIC 
        EnTT::EnTT
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        MiniMotor_compiler_flags
        sfml-system sfml-graphics sfml-window ImGui-SFML::ImGui-SFML
        Vulkan::Vulkan
        glfw
    )
endif()



target_precompile_headers(${PROJECT_NAME} PRIVATE
    <algorithm>
    <array>
    <atomic>
    <chrono>
    <cmath>
    <cstdint>
    <functional>
    <fstream>
    <iostream>
    <limits>
    <map>
    <memory>
    <optional>
    <string>
    <thread>
    <variant>
    <vector>
    #====================================================
    #Need to be last cause they need the standard library
    #====================================================
    "Sources/Core/Public/CoreMinimal.h"
)

target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
